//////////////////////////////////////////
///           IEngine.h
//////////////////////////////////////////

#pragma once

#define GL_GLEXT_PROTOTYPES
#include <math.h>
#include "Shader.h"
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <stdio.h>
#include "PostProcess.h"
#include "Vec3.h"
#include "Collision.h"
#include "Entity.h"
#include "Menu.h"
#include "Planet.h"
#include "SoundEngine.h"
#include "ParticleEngine.h"
#include "GoalZone.h"
#include "Weapon.h"
#include "Level.h"
#include <vector>

#define w_gl_to_pix(x) (int)(x * (m_width/gl_width)) + (m_width/2.0)
#define h_gl_to_pix(y) (int) -((y * (m_height/gl_height)) - (m_height/2.0))

#define w_pix_to_gl(x) (x-m_width/2.0) * (gl_width/m_width)
#define h_pix_to_gl(y) (-y+m_height/2.0) * (gl_height/m_height)

class IEngine
{
	public:
		IEngine(int argc, char** argv);
		void initGL(int argc, char** argv);
		void showCursor();
		void checkKeys();
		void drawScene();
		void update();
		void resize(int width, int height);
		void loadLevels();
		void loadLevel(int levelid);
		
		int begin();
		float heightFunction(float i, float j);
		vec2 sumForcesAt(vec2 pos);
		bool collidesWithAny(vec2 pos, float radius);
		
	private:
	
		ParticleEngine pengine;
		SoundEngine sounds;
		GoalZone endzone;
	
		Weapon weapon;
	
		vec2 futurePositions[100];
	
		double m_time;
		sf::RenderWindow* m_window;
		sf::Clock* m_clock;
		int frames;
		float time;
		float fps;
		float m_updateRate;
		
		float m_width_ratio;
		float m_width;
		float m_height;
		
		float gl_width;
		float gl_height;
		
		float fuel;
		
		bool m_wireframe;
		int contact;
		bool won;
		
		PostProcess p;
		Shader * sh;

		vec2 initialDudePos;
		
		std::vector<Planet*> m_planets;
		std::vector<Level*> m_levels;
		int curLevel;

		Entity dude;
		DBody cursor;		
		
		Menu m_menu;
		
		float dist;
};
