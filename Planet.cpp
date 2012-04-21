#include "Planet.h"

Planet::Planet(vec2 position, float radius, float planetmass, unsigned int texhandle, bool goal){
	drawable.top = radius;
	drawable.bottom = -radius;
	drawable.left = -radius;
	drawable.right = radius;
	pos = position;
	rad = radius;
	mass = planetmass;
	drawable.tex = texhandle;
	is_goal = goal;
}

void Planet::draw(){

	glPushMatrix();
	glTranslatef(pos.x, pos.y,0);
	
	drawable.draw();
	
	glPopMatrix();
}
