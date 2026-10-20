#include <GL/freeglut.h>
#include <math.h>


extern void Bulbble_Nivrutti(const char* name, float x_pos, float y_pos, float radiusx, float radiusy, float percent, float text_x, float text_y);
/*Function to draw bubble only

	@params: 1st: const char* name : String to draw inside bubble
			 2nd: float x_pos	   : Change position on x axis
			 3rd: float y_pos	   : Change position on y axis
			 4th: float radiusx	   : Radius of the circle on x axis
			 5th: float radiusy	   : Radius of the circle on y axis
			 6th: float percent	   : Percentage of shape
			 7th: float text_x     : text coordinate on x axis
			 8th: float text_y	   : text coordinate on y axis
*/
void Bulbble_Nivrutti(const char* name, float x_pos, float y_pos, float radiusx, float radiusy, float percent, float text_x, float text_y)
{
	// Variable Declaration
	float x;
	float y;

	// Local Function declaration.
	void drawText_Nivrutti(const char* name, float x, float y, float x_pos, float y_pos, float scale);
	void drawArc_Nivrutti(float x_pos, float y_pos, float radiusx, float radiusy, float startAngle, float endAngle, float percent);


	// Outer White circle
	glPointSize(3.0);
	glColor3f(1.0, 1.0, 1.0);
	// glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glBegin(GL_POINTS);
	for (float angle = 0.0f; angle < (2 * 3.14); angle += 0.005)
	{
		y = radiusy * sin(angle);
		x = radiusx * cos(angle);
		glVertex3f(VALUE_FROM_PERCENT(x, percent) + x_pos, VALUE_FROM_PERCENT(y, percent) + y_pos, 0.0f);
	}
	glEnd();

	// Text draw function call
	glColor3f(1, 1, 1);
	drawText_Nivrutti(name, text_x , text_y-0.04, x_pos, y_pos, 0.0006); // Adjust scale

	// Draw arc in circle
	glPointSize(6.0);
	drawArc_Nivrutti(x_pos, y_pos, radiusx-0.05, radiusy - 0.05, 100, 160, percent);
	glPointSize(2.5);
	drawArc_Nivrutti(x_pos, y_pos, radiusx-0.06, radiusy - 0.06, 275, 360, percent);
}


/*
	Description: Function to draw curve inside the circle.
	@params: 1st: float x_pos	   : Change position on x axis
			 2nd: float y_pos	   : Change position on y axis
			 3rd: float radiusx	   : Radius of the circle on x axis
			 4th: float radiusy	   : Radius of the circle on y axis
			 5th: float startAngle : Starting angle of curve shape
			 6th: float endAngle   : End angle of curve shape
			 7th: float percent	   : percent of curve shape
*/
void drawArc_Nivrutti(float x_pos, float y_pos, float radiusx, float radiusy, float startAngle, float endAngle, float percent)
{
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(5.0f);
	glBegin(GL_POINTS);
	for (float angle = startAngle; angle <= endAngle; angle += 0.005)
	{
		float x = radiusx * cos(angle * 3.1415 / 180.0);		// Convert angle to radian
		float y = radiusy * sin(angle * 3.1415 / 180.0);		// Convert angle to radian
		glVertex3f(VALUE_FROM_PERCENT(x, percent) + x_pos, VALUE_FROM_PERCENT(y, percent) + y_pos, 0);
	}
	glEnd();
}


/*
	Description: Function to draw text using stroke
	@params: 1st: const char* name : Name to be drawn
			 2nd: float x		   : x coordinate of the name starting
			 3rd: float y		   : y coordinate of the name starting
			 4th: float x_pos	   : Change position on x axis
			 5th: float y_pos	   : Change position on y axis
			 6th: float scale	   : Scale factor needed for glScalef()
*/
void drawText_Nivrutti(const char* name, float x, float y, float x_pos, float y_pos, float scale)
{
	glPushMatrix();			//  current transformation matrix
	glTranslatef(x + x_pos, y + y_pos, 0);	// coordinate system
	glScalef(scale, scale, scale);		// Scales the text uniformly
	glLineWidth(3.5);
	glutStrokeString(GLUT_STROKE_ROMAN, name);
	glPopMatrix();
}