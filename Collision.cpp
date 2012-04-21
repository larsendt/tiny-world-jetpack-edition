#include "Collision.h"

double distanceToPlane(PLANE p, vec2 pos, vec2 vel){

	vec2 N = p.n;
	vec2 a = p.a;
	vec2 b = p.b;
	
	float x = dot((a-pos), N);
	float y = dot(vel, N);
	if (y == 0) return 0;
	return x/y;
}
