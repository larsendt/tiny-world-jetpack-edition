#include "PBody.h"

PBody::PBody(){
	pos.x = 0;
	pos.y = 0;
	vel.x = 0;
	vel.y = 0;
	rad = 1.0;
	mass = 1.0;
}

void PBody::addForce(vec2 force){
	vel = vel + force * (1.0/mass);
}

void PBody::update(){

	pos = pos + vel;

}

vec2 PBody::nextPos(vec2 force){
	vec2 tempVel = vel + force * mass;
	return pos + tempVel;
}
