#pragma once
#include "Vec2.h"
#include "GLstuff.h"
#include <stdio.h>

class GoalZone{
	public:
		GoalZone(){};
		GoalZone(vec2 position, float l, float r, float u, float d);
		void init(vec2 position, float l, float r, float u, float d);
		bool checkIfInside(vec2 position, float objectrad);
		void draw();
	private:
		vec2 pos;
		float roughradius;
		float left;
		float right;
		float top;
		float bottom;

};
