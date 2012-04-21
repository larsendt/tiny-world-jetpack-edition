//////////////////////////////////////////
///           IEngine.h
//////////////////////////////////////////

#define GL_GLEXT_PROTOTYPES
#include <math.h>
#include "Shader.h"
#include "ImageLoader.h"
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <stdio.h>
#include "PostProcess.h"
#include "Vec3.h"
#include "Collision.h"
#include "Bone.h"
#include "PBody.h"
#include "Menu.h"


#ifndef IEngine_H
#define IEngine_H

#define PI 3.1415
#define radians(i) (i/180.0 * PI)
#define degrees(i) (i/PI * 180.0)

struct Planet{
	vec2 pos;
	float rad;
	float mass;
};

class IEngine
{
	public:
		IEngine(int argc, char** argv);
		void initGL(int argc, char** argv);
		void checkKeys();
		void drawScene();
		void update();
		void resize(int width, int height);
		int begin();
		float heightFunction(float i, float j);
	private:
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
		Bone * bones;

		Planet planet;
		Planet planet2;
		PBody dude;		
		
		Menu m_menu;
		
		float dist;
};

#endif
