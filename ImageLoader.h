#pragma once
#include <SFML/Graphics.hpp>
#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif
#include <stdio.h>
extern GLuint loadImage(char* file);
extern void bindImage(GLuint img);
