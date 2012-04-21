#include <stdio.h>
#include <stdlib.h>
#define GL_GLEXT_PROTOTYPES
#include "GLstuff.h"

#ifndef SHADER_FUNCS
#define SHADER_FUNCS

char* file_read(const char* filename);
void print_log(GLuint object);
GLint create_shader(const char* filename, GLenum type);

#endif
