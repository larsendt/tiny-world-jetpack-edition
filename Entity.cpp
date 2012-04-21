#include "Entity.h"

void Entity::setDBody(vec2 topleft, vec2 botright, unsigned int tex){
	drawable.top = topleft.y;
	drawable.left = topleft.x;
	drawable.right = botright.x;
	drawable.bottom = botright.y;
	drawable.tex = tex;
}

void Entity::setPBody(vec2 pos, vec2 vel, float rot, float rad, float mass){
	physics_object.pos = pos;
	physics_object.vel = vel;
	physics_object.rot = rot;
	physics_object.rad = rad;
	physics_object.mass = mass;
}

void Entity::draw(){
	glPushMatrix();
	glTranslatef(physics_object.pos.x, physics_object.pos.y, 0);
	glRotatef(physics_object.rot + 90, 0,0,1);
	drawable.draw();
	
	glPopMatrix();
}

void Entity::update(){
	physics_object.update();
}
