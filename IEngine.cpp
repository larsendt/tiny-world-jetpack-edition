//////////////////////////////////////////
///           IEngine.cpp
//////////////////////////////////////////

int mouse_x = 0;
int mouse_y = 0;
float gl_x = 0;
float gl_y = 0;

#include "IEngine.h"

IEngine::IEngine(int argc, char** argv)
{
	printf("Initializing IEngine\n");
	initGL(argc, argv);
	m_width = 800;
	m_height = 600;
	resize(m_width, m_height);
	m_time = 0.0;
	frames = 0;
	m_updateRate = 1/60.0;
	//m_window->ShowMouseCursor(false);
	m_window->SetCursorPosition(m_width/2.0,m_height/2.0);
	
	// TEST STUFF
	Shader * fbo_shader = new Shader((char*)"shaders/pp.vert",(char*)"shaders/sobel.frag");
	p.setShader(fbo_shader);
	p.init(m_width, m_height);
	
	sh = new Shader((char*)"shaders/basic.vert", (char*)"shaders/basic.frag");
	unsigned int tex = loadImage("textures/shadedplanet.png");
	
	Planet* planet = new Planet(vec2(20,20), 20.0, 1000.0, tex);
	m_planets.push_back(planet);
	planet = new Planet(vec2(-30,-30), 10, 500.0, tex);
	m_planets.push_back(planet);
	
	cursor.tex = tex;
	cursor.bottom = -1.0;
	cursor.top = 1.0;
	cursor.left = -1.0;
	cursor.right = 1.0;
	
	tex = loadImage("textures/dude.png");
	
	sounds.Load_Music();
		//sounds.Play_Music();
	sounds.Load_Jetpack();
	
	dude.setPBody(vec2(-20,-20), vec2(0,0), 0, 4.0, .001);
	dude.setDBody(vec2(-2,4), vec2(2,-4), tex);
	
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
	
	glPointSize(1.0);
	glEnable(GL_POINT_SMOOTH);
	glLineWidth(2.0);
	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
}

void IEngine::showCursor(){
	gl_x = w_pix_to_gl(mouse_x);
	gl_y = h_pix_to_gl(mouse_y);
	
	vec2 pos = dude.physics_object.pos;
	vec2 diff = vec2(gl_x, gl_y)- pos;
	
	
	
	if (diff.length() > 20.0){
		diff = diff.normalize() * 20.0;
	}
	
	dude.physics_object.rot = degrees(atan2(diff.y, diff.x));
	
	int x = w_gl_to_pix(pos.x + diff.x);
	int y = h_gl_to_pix(pos.y + diff.y);
	
	//printf("calculated pixel coordinates %3.3i,%3.3i\n", x, y);
	//printf("actual pixel coordinates %3.3i,%3.3i\n", mouse_x, mouse_y);
	//printf("gl coordinates %f %f\n", pos.x + diff.x, pos.y + diff.y);
	
	//m_window->SetCursorPosition(x, );
	glPushMatrix();
	glTranslatef(pos.x + diff.x, pos.y + diff.y, 0);
	cursor.draw();

	glPopMatrix();
	
}

void IEngine::checkKeys(){

	bool jetpack;
	
	// This function deals with constant keypresses.
	
	const sf::Input& input = m_window->GetInput();
	bool a = input.IsKeyDown(sf::Key::A);
	bool d = input.IsKeyDown(sf::Key::D);
	//bool w = input.IsKeyDown(sf::Key::W);
	//bool s = input.IsKeyDown(sf::Key::S);
	
	mouse_x = input.GetMouseX();
	mouse_y =  input.GetMouseY();
	
	//bool up = input.IsKeyDown(sf::Key::Up);
	//bool right = input.IsKeyDown(sf::Key::Right);
	//bool down = input.IsKeyDown(sf::Key::Down);
	//bool left = input.IsKeyDown(sf::Key::Left);

	bool space = input.IsKeyDown(sf::Key::Space);
	
	if (d){
		dude.physics_object.rot -= 2;
	}
	
	if (a){
		dude.physics_object.rot += 2;
	}
	
	if (space){	
		dude.physics_object.addForce(vec2(cos(radians(dude.physics_object.rot)) * 5, sin(radians(dude.physics_object.rot)) * 5));
		jetpack = true;
	}
	
	if (!space){
		jetpack = false;
	}
	
	sounds.Play_Jetpack(jetpack);
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
		
		checkKeys();
		
		update();
		
		drawScene();
		
		showCursor();
		
		m_window->Display();
	}
	return 0;
}


void IEngine::drawScene()
{
	gl_x = ((50 * 400) / (mouse_x - 50));
	gl_y = ((50 * 300) / (mouse_y - 50));
	
	glPointSize(1.0);
	
	glPushMatrix();
	glTranslatef(mouse_x, mouse_y,0);
	
	glBegin(GL_POINTS);
	glVertex2f(0,0);
	
	glEnd();
	glPopMatrix();
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	
	for(int i = 0; i < m_planets.size(); i++)
	{
		m_planets[i]->draw();
	}
	
	dude.draw();	

	glBindTexture(GL_TEXTURE_2D, 0);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POINTS);	
	
	int d = 40;
	for(int i = 0; i < d; i++)
	{
		for(int j = 0; j < d; j++)
		{
			float x = (i-(d/2))*(50/(d/2.0))*m_width_ratio;
			float y = (j-(d/2))*(50/(d/2.0));
			float grav = sumForcesAt(vec2(x, y)).length();
			glColor3f(grav, grav, grav);
			glVertex3f(x, y, -0.1);
		}
	}
	glEnd();
	
	glColor3f(1, 1, 1);

	if(m_menu.isActive())
	{
		m_window->Draw(m_menu);
	}
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
	
	if(collidesWithAny(dude.physics_object.pos + dude.physics_object.vel, dude.physics_object.rad))
	{
		dude.physics_object.vel = vec2(0,0);
	}
	else
	{
		vec2 net_force = sumForcesAt(dude.physics_object.pos);
		dude.physics_object.addForce(net_force);		
	}
	
	dude.physics_object.update();//*multiplier;
	
	frames++;
	
	moving = false;
}

vec2 IEngine::sumForcesAt(vec2 pos)
{
	vec2 total_force;
	for(int i = 0; i < m_planets.size(); i++)
	{
		vec2 grav_vector = m_planets[i]->pos - pos;
		float dist = grav_vector.length() * 1;
		grav_vector = grav_vector.normalize() * m_planets[i]->mass * (1/(dist*dist));
		total_force = total_force + grav_vector;
	}
	return total_force;		
}

bool IEngine::collidesWithAny(vec2 pos, float radius)
{
	for(int i = 0; i < m_planets.size(); i++)
	{
		vec2 diff_vector = m_planets[i]->pos - pos;
		if(diff_vector.length() < (radius + m_planets[i]->rad))
		{
			return true;
		}	
	}
	
	return false;
}

void IEngine::resize(int width, int height)
{

	m_width_ratio = (height>0) ? (GLfloat)width/height : 1;
	m_width = width;
	m_height = height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gl_width = 100.0 * m_width_ratio;
	gl_height = 100.0;
	glOrtho(-50.0 * m_width_ratio,50.0 * m_width_ratio,-50.0,50.0,-50.0,50.0);
	//gluPerspective(45.0,m_width_ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	p.resize(width, height);
}
