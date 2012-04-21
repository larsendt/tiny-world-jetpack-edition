#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Vec2.h"
#define MAX_CHILDREN 			8
#define MAX_FRAMES 16
#define BONE_ABSOLUTE_ANGLE 	0x01
#define BONE_ABSOLUTE_POSITION 	0x02
#define BONE_ABSOLUTE (BONE_ABSOLUTE_ANGLE | BONE_ABSOLUTE_POSITION)

#define PI 3.1415

#define RAD2DEG(a) (((a) * 180.0) / PI)

#ifndef BONE
#define BONE

typedef unsigned int uint;

typedef struct _KeyFrame{
	uint time;
	float angle;
}KeyFrame;

typedef struct _Bone{

	vec2 p;
	
	float maxangle, minangle;
	float a;
	float defaulta;
	
	float l;
	float depth;
	int level;
	uint children;
	uint ID;
	
	struct _Bone * child[MAX_CHILDREN];
	struct _Bone * parent;
	
	uint anim_length;
	uint num_frames;
	KeyFrame animation[MAX_FRAMES];

}Bone;



Bone *addBoneChild(Bone * root, vec2 pos, float a, float maxangle, float minangle, float l, float depth, uint ID);

void freeBoneTree(Bone * root);

void printBoneTree(Bone * root, uint level);

void drawBoneTree(Bone * root);

Bone *boneLoadStructure(char *path);

void boneLoadAnimation(Bone * bones, char * path);

Bone * getBoneByID(Bone * bones, unsigned int id);

void boneAnimate(Bone * root, int time, float multiplier);

#endif
