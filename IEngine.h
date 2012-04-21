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
		
		float m_width_ratio;
		float m_width;
		float m_height;
		
		float gl_width;
		float gl_height;
		
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
