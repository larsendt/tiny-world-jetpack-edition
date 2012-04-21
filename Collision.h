// Collision.h
#include "Vec2.h"
typedef struct {
	vec2 a;
	vec2 b;
	vec2 n;
}PLANE;

typedef struct {
	vec2 center;
	float halfheight;
	float halfwidth;
	float angle;
}OBB;

typedef struct{
	vec2 center;
	float halfheight;
	float halfwidth;
}AABB;

double distanceToPlane(PLANE p, vec2 pos, vec2 vel);
