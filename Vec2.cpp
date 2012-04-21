#include "Vec2.h"

///////////////////// Initialization Functions ///////////////////

vec2::vec2(){
	x = y = 0;
}

vec2::vec2(double nx, double ny){
	x = nx;
	y = ny;
}

vec2::vec2(const vec2& v){
	x = v.x;
	y = v.y;
}

///////////////////////// Class Functions ///////////////////////

double vec2::length(){
	return sqrt(pow(x,2)+pow(y,2));
}

double vec2::squaredLength(){
	return pow(x,2)+pow(y,2);
}

vec2 vec2::normalize(){
	double l = length();
	return vec2(x/l, y/l);
}

/////////////// Overloaded Functions ///////////////////////

vec2 vec2::operator=(const vec2& source){

	x = source.x;
	y = source.y;
	return *this;

}

vec2 vec2::operator+(const vec2& rhs){

	vec2 v;
	v.x = x + rhs.x;
	v.y = y + rhs.y;
	return v;

}

vec2 vec2::operator-(const vec2& rhs){

	vec2 v;
	v.x = x - rhs.x;
	v.y = y - rhs.y;
	return v;

}

double vec2::operator*(const vec2& rhs){
	return ((x*rhs.x) + (y*rhs.y));
	
}

vec2 vec2::operator*(double scalar){

	return vec2(scalar*x, scalar*y);
	
}


////////////////// Non Class Functions ////////////////////

double angle(vec2 a, vec2 b){
	return ((a.x*b.x) - (a.y*b.y))/(a.length()*b.length());
}

double dot(vec2 a, vec2 b){
	return (a.x*b.x) + (a.y*b.y);

}
