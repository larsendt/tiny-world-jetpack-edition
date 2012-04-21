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
	
	dotpos = dotspeed = vec2(0,0);
	dotspeed.y = .2;
	bones = boneLoadStructure("bones/zombie.bones");
	boneLoadAnimation(bones, "bones/zombie.anim");

	contact = 0;
	moving = false;
	
	// END TEST
}

void IEngine::initGL(int argc, char** argv)
{
	m_window = new sf::Window(sf::VideoMode(800, 600, 32), "IEngine");
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
		dotspeed.x += cos(radians(rotation)) * .005;
		dotspeed.y -= sin(radians(rotation)) * .005;
	}
	
	if (a){
		dotspeed.x -= sin(radians(rotation)) * .005;
		dotspeed.y += cos(radians(rotation)) * .005;
	}
	
	if (space){	
		dotspeed.x += cos(radians(rotation)) * .01;
		dotspeed.y += sin(radians(rotation)) * .01;
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
			
			else if(Event.Type == sf::Event::KeyPressed)
			{
				// For one-press keys: (starts to repeat after a while)
				if(Event.Key.Code == sf::Key::Escape)
				{
					m_window->Close();
					return 0;
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
		
		checkKeys();
		
		update();
		
		drawScene();
		
		m_window->Display();
	}
	return 0;
}


void IEngine::drawScene()
{
	//p.startDraw();
	
	vec2 gravVector = vec2(0,0) - dotpos;
	
	if ((gravVector.length() < .1)){
		gravVector = vec2(0,0);
	}
	
	else{
		gravVector = gravVector.normalize() * .005;
	}
	
	rotation = 180 + degrees(atan2(gravVector.y,gravVector.x));
	
	dotspeed = dotspeed + gravVector;
	
	dotpos = dotpos + dotspeed;//*multiplier;
	
	
	
	if (m_wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//glTranslatef(-dotpos.x,-dotpos.y,0);
	glUseProgram(0);
	
	glDisable(GL_TEXTURE_2D);
	glColor3f(1.0,1.0,1.0);
	glPushMatrix();
	glTranslatef(dotpos.x, dotpos.y, 0);
	
	glBegin(GL_LINES);
	glVertex2f(0,0);
	glVertex2f(gravVector.x*300, gravVector.y*300);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	
	glBegin(GL_TRIANGLES);
	
		for (int i = 0; i < 157; i++){
			glVertex2f(sin(i/5.0)*5, cos(i/5.0)*5);
			glVertex2f(0,0);
			glVertex2f(sin((i+1)/5.0)*5, cos((i+1)/5.0)*5);
		}
	
	glEnd();
	
	glTranslatef(dotpos.x, dotpos.y, 0);
	glRotatef(rotation, 0,0,1);
	glColor3f(1.0,0.0,0.0);
	//glBegin(GL_LINES);
		//glVertex2f(0,0);
	//	glVertex2f(10.0,0);
	
//	glEnd();
	
	
	
	glBegin(GL_TRIANGLES);
		glVertex2f(-1,-1);
		glVertex2f(-1,1);
		glVertex2f(2,0);
		
	glEnd();
	
	//drawBoneTree(bones);
	glPopMatrix();
	
	glEnable(GL_TEXTURE_2D);
	float sx = 2.0 / m_window->GetWidth();
	float sy = 2.0 / m_window->GetHeight();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	//p.draw();
	
}


void IEngine::update()
{
	float newTime = m_clock->GetElapsedTime();
	float diff = newTime-time;
	
	float multiplier = 1.0;
	
	
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
	

	//float mult = (fabs(dotspeed.x) > 2.0 ? 2.0: fabs(dotspeed.x));
	//boneAnimate(bones, frames, mult);
	
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
