#include "DBody.h"

void DBody::draw(){

	bindImage(tex);
	glBegin(GL_TRIANGLES);

		glTexCoord2f(0,0);
		glVertex2f(left,bottom);
		glTexCoord2f(0,1);
		glVertex2f(left,top);
		glTexCoord2f(1,1);
		glVertex2f(right,top);
	
		glTexCoord2f(0,0);
		glVertex2f(left,bottom);
		glTexCoord2f(1,0);
		glVertex2f(right,bottom);
		glTexCoord2f(1,1);
		glVertex2f(right,top);

	glEnd();

}
