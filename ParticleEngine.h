#pragma once
#include "Vec2.h"
#include "GLstuff.h"
#include <stdlib.h>
#include <stdio.h>

#define MAX_PARTICLES 1028

class ParticleEngine{

	public:
		ParticleEngine();
		void update();
		void draw();
		void createParticles(vec2 pos, vec2 dir, int num);
	private:
		int current_particle;
		vec2 positions[MAX_PARTICLES];
		vec2 velocities[MAX_PARTICLES];
		int life[MAX_PARTICLES];
};
