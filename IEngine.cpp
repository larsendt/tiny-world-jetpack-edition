//////////////////////////////////////////
///           IEngine.cpp
//////////////////////////////////////////

int mouse_x = 0;
int mouse_y = 0;
float gl_x = 0;
float gl_y = 0;

#include "IEngine.h"
#include "Level.h"

#include <stdlib.h>

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
	tex = loadImage("textures/shadedplanet2.png");
	cursor.tex = tex;
	cursor.bottom = -1.0;
	cursor.top = 1.0;
	cursor.left = -1.0;
	cursor.right = 1.0;
	
	tex = loadImage("textures/dude.png");

	curLevel = 0;
	loadLevels();	
	loadLevel(curLevel);
	
	contact = 0;
	won = false;
	
	fuel = 100.0;
	
	m_menu.setActive(true);
	
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
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glAlphaFunc(GL_GREATER,0.1f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

	if(m_menu.isActive())
		return; 

	bool jetpack;
	
	// This function deals with constant keypresses.
	
	const sf::Input& input = m_window->GetInput();
	bool lbutton = input.IsMouseButtonDown(sf::Mouse::Left);
	
	mouse_x = input.GetMouseX();
	mouse_y =  input.GetMouseY();

	bool space = input.IsKeyDown(sf::Key::Space);
	
	if (lbutton){
		weapon.shoot();
	}
	
	if (space && (fuel>=1.0)){	
		float x = cos(radians(dude.physics_object.rot))*.2;
		float y = sin(radians(dude.physics_object.rot))*.2;
		dude.physics_object.addForce(vec2(x, y));
		pengine.createParticles(dude.physics_object.pos,dude.physics_object.vel + vec2(-x*.5, -y*.5),5);
		jetpack = true;
		fuel --;
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
					dude.physics_object.pos = initialDudePos;
					dude.physics_object.vel = vec2(0,0);
					fuel = 100;
					sounds.Kill_Music();
					won = false;
				}
				if(Event.Key.Code == sf::Key::L)
				{
					curLevel = (curLevel + 1) % m_levels.size();
					loadLevel(curLevel);
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
	
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	glPointSize(3.0);
	
	weapon.drawParticles();
	
	glPointSize(5.0);
	
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);
	
	glDisable(GL_DEPTH_TEST);
	
	glLineWidth(5.0);
	glColor3f(0.0,1.0,.5);
	glBegin(GL_LINE_STRIP);
	
	for (int i =0; i< 100; i++){
		Position p = futurePositions[i];
		float speed = p.speed;
		if (p.active){
			glColor3f(0.0,speed/2.0,speed);
		}
		else glColor3f(1.0,0,0);
		glVertex2f(p.pos.x, p.pos.y);
	}

	glEnd();
	
	pengine.draw();
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);

	glColor3f(0.0,0.0,1.0);
	glBegin(GL_TRIANGLES);
	
	glVertex2f(100, -100);
	glVertex2f(100, (fuel/100.0 * 200)-100);
	glVertex2f(90, (fuel/100.0 * 200)-110);
	
	glVertex2f(100, -100);
	glVertex2f(90, -100);
	glVertex2f(90, (fuel/100.0 * 200)-110);
	
	glEnd();
	
	/*glPointSize(1.0);
	
	glBegin(GL_POINTS);	
	int d = 80;
	for(int i = 0; i < d; i++)
	{
		for(int j = 0; j < d; j++)
		{
			float x = (i-(d/2))*(100/(d/2.0))*m_width_ratio;
			float y = (j-(d/2))*(100/(d/2.0));
			float grav = sumForcesAt(vec2(x, y)).length()*4.0;
			glColor3f(grav, grav, -grav);
			glVertex3f(x, y, -0.1);
		}
	}
	glEnd();*/
	
	glColor3f(1.0, 1.0, 1.0);
	
	endzone.draw();
	
	dude.draw();	
	
	
	
	for(int i = 0; i < m_planets.size(); i++)
	{
		m_planets[i]->draw();
	}
	
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
		pengine.createParticles(dude.physics_object.pos,dude.physics_object.vel ,50);
		dude.physics_object.vel = vec2(0,0);
		dude.physics_object.pos = initialDudePos;
		fuel = 100;
		sounds.Kill_Music();
		won = false;
	}
	else
	{
		vec2 net_force = sumForcesAt(dude.physics_object.pos);
		dude.physics_object.addForce(net_force);		
	}
	
	vec2 p = dude.physics_object.pos;
	vec2 vel = dude.physics_object.vel;
	float mass = dude.physics_object.mass;
	float radius = dude.physics_object.rad;
	bool active = 1;
	vec2 force;
	
	for (int i = 0; i< 100; i++){
		
		for (int iterations = 0; iterations < 5; iterations ++){
			force = sumForcesAt(p);
			vel = vel + (force * (1/mass));
			p = p + vel;
		}
		active = active && !collidesWithAny(p, radius);
		futurePositions[i].active = active;
		futurePositions[i].speed = vel.length();
		futurePositions[i].pos = p;
	}
	if (endzone.checkIfInside(dude.physics_object.pos, dude.physics_object.rad) && !won){ 
		
		sounds.Play_Music();
		won = true;
	}
	
	if (fuel <= 99.9) fuel+= .2;
	
	dude.physics_object.update();//*multiplier;
	
	pengine.update();
	
	weapon.updateParticles();
	
	frames++;
	
}

vec2 IEngine::sumForcesAt(vec2 pos)
{
	vec2 total_force;
	for(int i = 0; i < m_planets.size(); i++)
	{
		vec2 grav_vector = m_planets[i]->pos - pos;
		float dist = grav_vector.length() * 1;
		grav_vector = grav_vector.normalize() * m_planets[i]->mass * (1/(dist*dist));
		if (dist < m_planets[i]->rad) grav_vector = vec2(0,0);
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
	gl_width = 200.0 * m_width_ratio;
	gl_height = 200.0;
	glOrtho(-100.0 * m_width_ratio,100.0 * m_width_ratio,-100.0,100.0,-100.0,100.0);
	//gluPerspective(45.0,m_width_ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	p.resize(width, height);
}

void IEngine::loadLevels()
{
	Level* level = new Level("levels/level1.jetworld");
	m_levels.push_back(level);

	level = new Level("levels/level2.jetworld");
	m_levels.push_back(level);

	level = new Level("levels/level3.jetworld");
	m_levels.push_back(level);
}

void IEngine::loadLevel(int levelid)
{
	Level* level = m_levels[levelid];
	printf("%s\n", level->name.c_str());
	
	m_planets = level->planets;
	endzone = level->goalZone;

	sounds.Load_Music();
	sounds.Load_Jetpack();
	
	dude = level->dude;
	weapon.init(&dude.physics_object);
	
	initialDudePos = dude.physics_object.pos;
	dude.physics_object.vel = vec2(0,0);
	fuel = 100;
	sounds.Kill_Music();
	won = false;

}
