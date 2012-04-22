#include "GoalZone.h"

GoalZone::GoalZone(vec2 position, float l, float r, float u, float d){
	init(position,l,r,u,d);
}

void GoalZone::init(vec2 position, float l, float r, float u, float d){

	left = l; right = r; top = u; bottom = d;
	
	pos = position;
	
	vec2 lt, rb;
	lt = vec2(l, u);
	rb = vec2(r, d);
	
	roughradius = (lt-rb).length()/2.0;

}

bool GoalZone::checkIfInside(vec2 position, float objectrad){

	vec2 diff = pos - position;
	
	if (diff.length() < (objectrad + roughradius)){
		// We're roughly inside, check bounding box
		
		return true;  		
		/*if (position.x > left && position.x < right){
			
			if (position.y > bottom && position.y < top){
				return true;
			}
		}*/
	}
	return false;
}

void GoalZone::draw(){

	glPushMatrix();
	glTranslatef(pos.x, pos.y, 0);
	glBegin(GL_LINE_LOOP);
	
	glVertex2f(left, top);
	glVertex2f(left, bottom);
	glVertex2f(right, bottom);
	glVertex2f(right, top);
	
	glEnd();
	
	glPopMatrix();

}
