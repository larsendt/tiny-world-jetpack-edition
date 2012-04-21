#pragma once
#include "GLstuff.h"
#include "Vec2.h"
#include "ImageLoader.h"
#include <stdio.h>

class DBody{
	public:
		void draw();
		unsigned int tex;
		float top, bottom, left, right;
};
