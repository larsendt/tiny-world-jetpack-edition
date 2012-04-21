//////////////////////////////////////////
///           IEngine.cpp
//////////////////////////////////////////

#include "IEngine.h"

IEngine::IEngine(int argc, char** argv)
{
	printf("Initializing IEngine\n");
	initGL(argc, argv);
	resize(800, 600);
	m_time = 0.0;
	frames = 0;
	m_updateRate = 1/60.0;
	
	// TEST STUFF
	Shader * fbo_shader = new Shader((char*)"shaders/pp.vert",(char*)"shaders/sobel.frag");
	p.setShader(fbo_shader);
	p.init(m_window->GetWidth(), m_window->GetHeight());
	
	sh = new Shader((char*)"shaders/basic.vert", (char*)"shaders/basic.frag");
	
	planet.pos = vec2(-20,10);
	planet.rad = 5.0;
	planet.mass = 0.2;
	dude.rad = 2.0;
	dude.mass = 0.02;
	bones = boneLoadStructure("bones/zombie.bones");
	boneLoadAnimation(bones, "bones/zombie.anim");

	contact = 0;
	moving = false;
	
	// END TEST
}

void IEngine::initGL(int argc, char** argv)
{
	m_window = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "IEngine");
	m_window->PreserveOpenGLStates(true);	
	m_clock = new sf::Clock();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPointSize(5.0);
	glEnable(GL_POINT_SMOOTH);
	glLineWidth(2.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
}

void IEngine::checkKeys(){

	// This function deals with constant keypresses.
	
	const sf::Input& input = m_window->GetInput();
	bool a = input.IsKeyDown(sf::Key::A);
	bool d = input.IsKeyDown(sf::Key::D);
	//bool w = input.IsKeyDown(sf::Key::W);
	//bool s = input.IsKeyDown(sf::Key::S);
	
	//bool up = input.IsKeyDown(sf::Key::Up);
	//bool right = input.IsKeyDown(sf::Key::Right);
	//bool down = input.IsKeyDown(sf::Key::Down);
	//bool left = input.IsKeyDown(sf::Key::Left);

	bool space = input.IsKeyDown(sf::Key::Space);
	
	if (d){
		dude.rot -= 2;
	}
	
	if (a){
		dude.rot += 2;
	}
	
	if (space){	
		dude.vel.x += cos(radians(dude.rot)) * .02;
		dude.vel.y += sin(radians(dude.rot)) * .02;
	}
	
	if (space && contact){	
		dude.vel.x += cos(radians(dude.rot)) * .01;
		dude.vel.y += sin(radians(dude.rot)) * .01;
	}
	
}

int IEngine::begin()
{

	while(m_window->IsOpened())
	{
		sf::Event Event;
		while(m_window->GetEvent(Event))
		{
			if(Event.Type == sf::Event::Closed)
			{
				m_window->Close();
				return 0;
			}
			else if(Event.Type == sf::Event::MouseMoved)
			{
				if(m_menu.isActive())
				{
					m_menu.mouseHover(Event.MouseMove.X, Event.MouseMove.Y);
				}
			}
			else if(Event.Type == sf::Event::MouseButtonPressed)
			{
				m_menu.mouseClick(Event.MouseButton.X, Event.MouseButton.Y);
			}
			else if(Event.Type == sf::Event::KeyPressed)
			{
				// For one-press keys: (starts to repeat after a while)
				if(Event.Key.Code == sf::Key::Escape)
				{
					m_menu.setActive(!m_menu.isActive());
				}
				if(Event.Key.Code == sf::Key::M)
				{
					m_wireframe = true;
				}
				if(Event.Key.Code == sf::Key::N)
				{
					m_wireframe = false;
				}
				if(Event.Key.Code == sf::Key::R)
				{
					freeBoneTree(bones);
					bones = boneLoadStructure("bones/zombie.bones");
					boneLoadAnimation(bones, "bones/zombie.anim");
				}
			}
			else if(Event.Type == sf::Event::Resized)
			{
				resize(Event.Size.Width, Event.Size.Height);
			}
			
		}
		
		if(m_menu.hasAction())
		{
			MenuAction action = m_menu.getAction();
			if(action == Quit)
				m_window->Close();
		}
		
		update();
		
		drawScene();
		
		m_window->Display();
	}
	return 0;
}


void IEngine::drawScene()
{
	//p.startDraw();
	if (m_wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	if(m_menu.isActive())
	{
		m_window->Draw(m_menu);
	}
	//glTranslatef(-dotpos.x,-dotpos.y,0);
	glUseProgram(0);

	glPushMatrix();

	glRotatef(-dude.rot + 90, 0, 0, 1);
	glTranslatef(-dude.pos.x, -dude.pos.y, 0);
	glDisable(GL_TEXTURE_2D);

	glPushMatrix();
	glTranslatef(planet.pos.x, planet.pos.y,0);
	glBegin(GL_TRIANGLES);

		for (int i = 0; i < 73; i++){
			glColor3f(.5,.5,1.0);
			glVertex2f(sin(i/2.5)*planet.rad, cos(i/2.5)*planet.rad);
			glVertex2f(0,0);
			glVertex2f(sin((i+1)/2.5)*planet.rad, cos((i+1)/2.5)*planet.rad);
		}

	glEnd();
	glPopMatrix();

	glTranslatef(dude.pos.x, dude.pos.y, 0);
	glRotatef(dude.rot, 0,0,1);
	glColor3f(1.0,0.0,0.0);

	// rakkit shep

	//drawBoneTree(bones);

	glBegin(GL_TRIANGLES);
		glVertex2f(-1,-1);
		glVertex2f(-1,1);
		glVertex2f(1,1);
	
		glVertex2f(-1,-1);
		glVertex2f(1,-1);
		glVertex2f(1,1);
	
	glEnd();


	glPopMatrix();



	glPopMatrix();	

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//p.draw();
}


void IEngine::update()
{
	if(m_menu.isActive())
		return; 
		
	float newTime = m_clock->GetElapsedTime();
	float diff = newTime-time;
	
	float multiplier = 1.0;
	
	if (contact > 0) contact --;
	
	while(diff < m_updateRate)
	{
		newTime = m_clock->GetElapsedTime();
		diff = newTime-time;
    	continue;
    }
    time = newTime;

   	if(diff > m_updateRate)
	{
		multiplier = time / m_updateRate;
	}
	fps = 1/diff;
	
	checkKeys();	

	vec2 gravVector = planet.pos - dude.pos;
	
	vec2 gravNormal = (gravVector * -1).normalize();
	
	vec2 diffVector = planet.pos - (dude.pos + dude.vel);
	
	float dist = gravVector.length();
	
	//Check intersection
	if ((diffVector.length() < (dude.rad + planet.rad))){
		// Reflect on normal
		dude.vel = vec2(0,0);
	}
	else
	{
		//gravVector = gravVector.normalize() * (1/(dist * dist)) * planet.mass;
		gravVector = gravVector.normalize() * planet.mass;
		dude.addForce(gravVector);
	}
	
	dude.update();//*multiplier;
	
	float mult = (fabs(dude.vel.length()) > 2.0 ? 2.0: fabs(dude.vel.length()));
	boneAnimate(bones, frames, mult);
	
	frames++;
	
	moving = false;
}


void IEngine::resize(int width, int height)
{

	m_width = (height>0) ? (GLfloat)width/height : 1;
	
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50.0 * m_width,50.0 * m_width,-50.0,50.0,-50.0,50.0);
	//gluPerspective(45.0,m_width,1,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	p.resize(width, height);
}
