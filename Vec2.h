#pragma once
#include <math.h>

#define PI 3.1415
#define radians(i) (i/180.0 * PI)
#define degrees(i) (i/PI * 180.0)

class vec2{
	public:
		vec2();
		vec2(double nx, double ny);
		vec2(const vec2& v);
		
		double length();
		double squaredLength();
		vec2 normalize();
		
		vec2 operator=(const vec2& source);
		vec2 operator+(const vec2& rhs);
		vec2 operator-(const vec2& rhs);
		vec2 operator*(double scalar);
		double operator*(const vec2& rhs);
		bool operator==(const vec2& rhs);
		
		double x;
		double y;
		
		
};

double angle(vec2 a, vec2 b);
double dot(vec2 a, vec2 b);
