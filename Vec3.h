#pragma once

#include <math.h>

#define PI 3.1415
#define radians(i) (i/180.0 * PI)
#define degrees(i) (i/PI * 180.0)

class vec3{
	public:
		vec3();
		vec3(double nx, double ny, double nz);
		vec3(const vec3& v);
		
		double length();
		double squaredLength();
		vec3 normalize();
		
		vec3 operator=(const vec3& source);
		vec3 operator+(const vec3& rhs);
		vec3 operator-(const vec3& rhs);
		vec3 operator*(double scalar);
		double operator*(const vec3& rhs);
		bool operator==(const vec3& rhs);
		
		double x;
		double y;
		double z;
		
		
};

double angle(vec3 a, vec3 b);
double dot(vec3 a, vec3 b);
vec3 cross(vec3 a, vec3 b);
