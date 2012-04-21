#include <SFML/Graphics.hpp>
#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif
#include <stdio.h>
GLuint loadImage(char* file);
void bindImage(GLuint img);
