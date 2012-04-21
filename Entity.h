#pragma once
#include "PBody.h"
#include "DBody.h"

class Entity{

	public:
	
		void setDBody(vec2 topleft, vec2 botright, unsigned int tex);
		void setPBody(vec2 pos, vec2 vel, float rot, float rad, float mass);
		
		void draw();
		void update();

		DBody drawable;
		PBody physics_object;

};
