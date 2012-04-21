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

#define PI 3.1415
#define radians(i) (i/180.0 * PI)
#define degrees(i) (i/PI * 180.0)

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
		int begin();
		float heightFunction(float i, float j);
	private:
	
		SoundEngine jetpack;
	
		double m_time;
		sf::RenderWindow* m_window;
		sf::Clock* m_clock;
		int frames;
		float time;
		float fps;
		float m_updateRate;
		float m_width;
		
		bool m_wireframe;
		int contact;
		bool moving;
		
		PostProcess p;
		Shader * sh;

		Planet * planet;
		Entity dude;
		DBody cursor;		
		
		Menu m_menu;
		
		float dist;
};
