#include "ParticleEngine.h"

ParticleEngine::ParticleEngine(){
	for (int i = 0; i< MAX_PARTICLES; i++){
		life[i] = 0;
		positions[i] = vec2(0,0);
		velocities[i] = vec2(0,0);;
	}

}

void ParticleEngine::update(){
	for (int i = 0; i<MAX_PARTICLES; i++){
		if (life[i] <= 0.0){
			continue;
		}
		
		positions[i] = positions[i] + velocities[i];
		life[i] --;
	}
}

void ParticleEngine::draw(){
	glBegin(GL_POINTS);
	
	for (int i =0; i < MAX_PARTICLES; i++){
		if (life[i] <= 0.0){
			continue;
		}
		glColor4f(0,0,1,life[i]/100.0);
		glVertex3f(positions[i].x, positions[i].y, 0);
	}
	
	glEnd();
}

void ParticleEngine::createParticles(vec2 pos, vec2 dir, int num){

	float x;
	float y;
	
	for (int i = 0; i < num; i++){
		x = (rand()%1000 - 500)/ 10000.0;
		y = (rand()%1000 - 500)/ 10000.0;
		life[current_particle] = 100;
		positions[current_particle] = pos;
		velocities[current_particle] = vec2(dir.x+x, dir.y+y);
		current_particle++;
		if (current_particle > MAX_PARTICLES-1){
			current_particle = 0;
		}
	}

}
