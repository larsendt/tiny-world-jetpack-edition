#include "Vec2.h"
class PBody{

	public:
		PBody();
		
		void addForce(vec2 force);
		void update();
		vec2 nextPos(vec2 force);

		vec2 pos;
		vec2 vel;
		float rot;
		float rad;
		float mass;

};
