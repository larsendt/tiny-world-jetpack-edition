#pragma once

#include "Vec2.h"
#include "PBody.h"
#include "GLstuff.h"
#include <vector>

struct Particle{
	vec2 pos;
	vec2 vel;
	int life;
};

class Weapon{

	public:
		
		Weapon();
		void init(PBody * pb);
		void drawParticles();
		void updateParticles();
		void shoot();
		
	private:
		std::vector<Particle> particles;
		int num_particles;
		PBody * physics_object;
};
