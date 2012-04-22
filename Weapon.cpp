#include "Weapon.h"

Weapon::Weapon(){
	particles.reserve(512);
}

void Weapon::init(PBody * pb){
	physics_object = pb;
}

void Weapon::drawParticles(){
	vec2 p;
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POINTS);
	std::vector<Particle>::iterator it;
	for(it = particles.begin(); it!= particles.end(); it++){
		
		Particle p = *it;
		if (p.life <= 0) {
			continue;
		}
		
		glVertex2f(p.pos.x, p.pos.y);	
	}
	glEnd();
}

void Weapon::updateParticles(){

	std::vector<Particle>::iterator it;
	for(it = particles.begin(); it!= particles.end(); it++){
		
		Particle p = *it;
		
		if (p.life <= 0) {
			continue;
		}
		
		p.pos = p.pos + p.vel;
		p.life --;
		*it = p;
	}

}

void Weapon::shoot(){
	float x = cos(radians(physics_object->rot));
	float y = sin(radians(physics_object->rot));
	
	Particle p;
	p.vel = vec2(x, y);
	p.pos = physics_object->pos;
	p.life = 100;
	
	particles.push_back(p);
	num_particles ++;
	
}
