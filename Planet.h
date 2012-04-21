#pragma once
#include "Vec2.h"
#include "GLstuff.h"
#include "DBody.h"
class Planet{
	public:
		Planet();
		Planet(vec2 pos, float rad, float mass, unsigned int tex, bool goal = false);
		
		void draw();
		vec2 pos;
		float rad;
		float mass;
		bool is_goal;
		
	private:
		DBody drawable;
};
