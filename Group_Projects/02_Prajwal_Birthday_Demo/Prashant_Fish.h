// Header File
#include <GL/freeglut.h>

// Function Declarations
extern void fish_one(float x_pos, float y_pos, float percent, float TailMoveUpdate);
extern void fish_two(float x_pos, float y_pos, float percent, float TailMoveUpdate);
extern void fish_three(float x_pos, float y_pos, float percent, float TailMoveUpdate);
extern void fish_four(float x_pos, float y_pos, float percent, float TailMoveUpdate);
extern void fish_bubble_two(float x_pos, float y_pos, float percent);
extern void bubble_two(float x_pos, float y_pos, float percent);
extern void fish_four(float x_pos, float y_pos, float percent, float TailMoveUpdate);

void fish_eye(float x_pos, float y_pos, float percent, float x, float y);
void fish_eye_dot(float x_pos, float y_pos, float percent, float x, float y);
void fish_circle(float x_pos, float y_pos, float percent);


// Function definations

void fish_one(float x_pos, float y_pos, float percent, float TailMoveUpdate)
{
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.9f, 0.2f);
	// Fish Rectangle
	glVertex3f(VALUE_FROM_PERCENT(-0.8f, percent) + x_pos, VALUE_FROM_PERCENT(-0.4f, percent) + y_pos, 0.0f); // left
	glVertex3f(VALUE_FROM_PERCENT(-0.6f, percent) + x_pos, VALUE_FROM_PERCENT(-0.55f, percent) + y_pos, 0.0f); // bottom
	glVertex3f(VALUE_FROM_PERCENT(-0.4f, percent) + x_pos, VALUE_FROM_PERCENT(-0.4f, percent) + y_pos, 0.0f); // right
	glVertex3f(VALUE_FROM_PERCENT(-0.6f, percent) + x_pos, VALUE_FROM_PERCENT(-0.25f, percent) + y_pos, 0.0f); // top
	glEnd();

	glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.5f, 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(-0.45f, percent) + x_pos, VALUE_FROM_PERCENT(-0.40f, percent) + y_pos, 0.0f); // left
	glVertex3f(VALUE_FROM_PERCENT(-0.35f, percent) + x_pos, (VALUE_FROM_PERCENT(-0.5f, percent) + y_pos) + TailMoveUpdate, 0.0f); // right
	glVertex3f(VALUE_FROM_PERCENT(-0.35f, percent) + x_pos, (VALUE_FROM_PERCENT(-0.3f, percent) + y_pos) + TailMoveUpdate, 0.0f); // top
	glEnd();

	fish_eye(x_pos, y_pos, percent, -0.74f, -0.39f);
	fish_eye_dot(x_pos, y_pos, percent, -0.74f, -0.38f);

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.5f, 0.0f);
	// Fish furr top
	glVertex3f(VALUE_FROM_PERCENT(-0.6f, percent) + x_pos, VALUE_FROM_PERCENT(-0.25f, percent) + y_pos, 0.0f); //center
	glVertex3f(VALUE_FROM_PERCENT(-0.5f, percent) + x_pos, (VALUE_FROM_PERCENT(-0.15f, percent) + y_pos) + TailMoveUpdate, 0.0f); // right
	glVertex3f(VALUE_FROM_PERCENT(-0.45f, percent) + x_pos, (VALUE_FROM_PERCENT(-0.2f, percent) + y_pos) + TailMoveUpdate, 0.0f); //left

	// Fish furr bottom
	glVertex3f(VALUE_FROM_PERCENT(-0.6f, percent) + x_pos, VALUE_FROM_PERCENT(-0.55f, percent) + y_pos, 0.0f); //center
	glVertex3f(VALUE_FROM_PERCENT(-0.5f, percent) + x_pos, (VALUE_FROM_PERCENT(-0.65f, percent) + y_pos) + TailMoveUpdate, 0.0f); // right
	glVertex3f(VALUE_FROM_PERCENT(-0.45f, percent) + x_pos, (VALUE_FROM_PERCENT(-0.6f, percent) + y_pos) + TailMoveUpdate, 0.0f); //left
    glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.5f, 0.0f);
	// Fish furr Middle
	glVertex3f(VALUE_FROM_PERCENT(-0.7f, percent) + x_pos, VALUE_FROM_PERCENT(-0.4f, percent) + y_pos, 0.0f); //center
	glVertex3f(VALUE_FROM_PERCENT(-0.66f, percent) + x_pos, VALUE_FROM_PERCENT(-0.35f, percent) + y_pos, 0.0f); // right
	glVertex3f(VALUE_FROM_PERCENT(-0.66f, percent) + x_pos, VALUE_FROM_PERCENT(-0.45f, percent) + y_pos, 0.0f); //left
    glEnd();

	// Fish shepti line
	glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(-0.44f, percent) + x_pos, VALUE_FROM_PERCENT(-0.4f, percent) + y_pos, 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(-0.37f, percent) + x_pos, (VALUE_FROM_PERCENT(-0.35f, percent) + y_pos) + TailMoveUpdate, 0.0f);

	glVertex3f(VALUE_FROM_PERCENT(-0.44f, percent) + x_pos, VALUE_FROM_PERCENT(-0.40f, percent) + y_pos, 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(-0.37f, percent) + x_pos, (VALUE_FROM_PERCENT(-0.4f, percent) + y_pos) + TailMoveUpdate, 0.0f);

	glVertex3f(VALUE_FROM_PERCENT(-0.44f, percent) + x_pos, VALUE_FROM_PERCENT(-0.40f, percent) + y_pos, 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(-0.37f, percent) + x_pos, (VALUE_FROM_PERCENT(-0.45f, percent) + y_pos) + TailMoveUpdate, 0.0f);
    glEnd();
}

void fish_two(float x_pos, float y_pos, float percent, float TailMoveUpdate)
{
	fish_circle(x_pos, y_pos, percent);

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.3f, 0.4f);
	// Fish furr back
	glVertex3f(VALUE_FROM_PERCENT(0.12f, percent) + x_pos, VALUE_FROM_PERCENT(-0.2f, percent) + y_pos, 0.0f); //center
	glVertex3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, (VALUE_FROM_PERCENT(-0.15f, percent) + y_pos) + TailMoveUpdate, 0.0f); // right
	glVertex3f(VALUE_FROM_PERCENT(0.05f, percent) + x_pos, (VALUE_FROM_PERCENT(-0.25f, percent) + y_pos) + TailMoveUpdate, 0.0f); //left
	glVertex3f(VALUE_FROM_PERCENT(0.12f, percent) + x_pos, (VALUE_FROM_PERCENT(-0.3f, percent) + y_pos) + TailMoveUpdate, 0.0f); //center
	glVertex3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, (VALUE_FROM_PERCENT(-0.35f, percent) + y_pos) + TailMoveUpdate, 0.0f); // right
	glVertex3f(VALUE_FROM_PERCENT(0.05f, percent) + x_pos, VALUE_FROM_PERCENT(-0.25f, percent) + y_pos, 0.0f); //left
	glVertex3f(VALUE_FROM_PERCENT(0.12f, percent) + x_pos, VALUE_FROM_PERCENT(-0.2f, percent) + y_pos, 0.0f); //center
	glVertex3f(VALUE_FROM_PERCENT(0.12f, percent) + x_pos, VALUE_FROM_PERCENT(-0.3f, percent) + y_pos, 0.0f); // right
	glVertex3f(VALUE_FROM_PERCENT(0.05f, percent) + x_pos, VALUE_FROM_PERCENT(-0.25f, percent) + y_pos, 0.0f); //left
	glEnd();

	glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.3f, 0.4f);
	// Fish furr top
	glVertex3f(VALUE_FROM_PERCENT(0.25f, percent) + x_pos, VALUE_FROM_PERCENT(-0.16f, percent) + y_pos, 0.0f); //center
	glVertex3f(VALUE_FROM_PERCENT(0.15f, percent) + x_pos, VALUE_FROM_PERCENT(-0.1f, percent) + y_pos, 0.0f); // right
	glVertex3f(VALUE_FROM_PERCENT(0.19f, percent) + x_pos, VALUE_FROM_PERCENT(-0.15f, percent) + y_pos, 0.0f); //left

	// Fish furr bottom
	glVertex3f(VALUE_FROM_PERCENT(0.25f, percent) + x_pos, VALUE_FROM_PERCENT(-0.34f, percent) + y_pos, 0.0f); //center
	glVertex3f(VALUE_FROM_PERCENT(0.15f, percent) + x_pos, VALUE_FROM_PERCENT(-0.4f, percent) + y_pos, 0.0f); // right
	glVertex3f(VALUE_FROM_PERCENT(0.19f, percent) + x_pos, VALUE_FROM_PERCENT(-0.35f, percent) + y_pos, 0.0f); //left
    glEnd();

	glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);

	glVertex3f(VALUE_FROM_PERCENT(0.12f, percent) + x_pos, VALUE_FROM_PERCENT(-0.22f, percent) + y_pos, 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(0.05f, percent) + x_pos, (VALUE_FROM_PERCENT(-0.2f, percent) + y_pos) + TailMoveUpdate, 0.0f);

	glVertex3f(VALUE_FROM_PERCENT(0.12f, percent) + x_pos, VALUE_FROM_PERCENT(-0.26f, percent) + y_pos, 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(0.05f, percent) + x_pos, (VALUE_FROM_PERCENT(-0.3f, percent) + y_pos) + TailMoveUpdate, 0.0f);

	glVertex3f(VALUE_FROM_PERCENT(0.12f, percent) + x_pos, VALUE_FROM_PERCENT(-0.24f, percent) + y_pos, 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(0.056f, percent) + x_pos, (VALUE_FROM_PERCENT(-0.25f, percent) + y_pos) + TailMoveUpdate, 0.0f);
    glEnd();

	// Fish eye
	fish_eye(x_pos, y_pos, percent, 0.25f, -0.22f);
	fish_eye_dot(x_pos, y_pos, percent, 0.25f, -0.21f);
}

void fish_three(float x_pos, float y_pos, float percent, float TailMoveUpdate)
{
	glBegin(GL_QUADS);
    glColor3f(0.2f, 0.3f, 0.6f);
	// Fish back
	glVertex3f(VALUE_FROM_PERCENT(0.4f, percent) + x_pos, VALUE_FROM_PERCENT(0.4f, percent) + y_pos, 0.0f); //center
	glVertex3f(VALUE_FROM_PERCENT(0.7f, percent) + x_pos, VALUE_FROM_PERCENT(0.5f, percent) + y_pos, 0.0f); // right
	glVertex3f(VALUE_FROM_PERCENT(0.65f, percent) + x_pos, VALUE_FROM_PERCENT(0.4f, percent) + y_pos, 0.0f); //left
	glVertex3f(VALUE_FROM_PERCENT(0.7f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f); //center

	// Fish front
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(VALUE_FROM_PERCENT(0.8f, percent) + x_pos, VALUE_FROM_PERCENT(0.4f, percent) + y_pos, 0.0f); // right
	glVertex3f(VALUE_FROM_PERCENT(0.7f, percent) + x_pos, VALUE_FROM_PERCENT(0.5f, percent) + y_pos, 0.0f); // right
	glVertex3f(VALUE_FROM_PERCENT(0.65f, percent) + x_pos, VALUE_FROM_PERCENT(0.4f, percent) + y_pos, 0.0f); //left
	glVertex3f(VALUE_FROM_PERCENT(0.7f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f); //center
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.8f, 0.8f, 0.4f);
	// Fish furr back
	glVertex3f(VALUE_FROM_PERCENT(0.35f, percent) + x_pos, (VALUE_FROM_PERCENT(0.45f, percent) + y_pos) + TailMoveUpdate, 0.0f); //center
	glVertex3f(VALUE_FROM_PERCENT(0.35f, percent) + x_pos, (VALUE_FROM_PERCENT(0.35f, percent) + y_pos) + TailMoveUpdate, 0.0f); // right
	glVertex3f(VALUE_FROM_PERCENT(0.45f, percent) + x_pos, VALUE_FROM_PERCENT(0.40f, percent) + y_pos, 0.0f); //left

	// Fish furr bottom
	glVertex3f(VALUE_FROM_PERCENT(0.55f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f); //center
	glVertex3f(VALUE_FROM_PERCENT(0.6f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f); // right
	glVertex3f(VALUE_FROM_PERCENT(0.55f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f); //left

	// Fish furr top
	glVertex3f(VALUE_FROM_PERCENT(0.55f, percent) + x_pos, VALUE_FROM_PERCENT(0.45f, percent) + y_pos, 0.0f); //center
	glVertex3f(VALUE_FROM_PERCENT(0.6f, percent) + x_pos, VALUE_FROM_PERCENT(0.45f, percent) + y_pos, 0.0f); // right
	glVertex3f(VALUE_FROM_PERCENT(0.55f, percent) + x_pos, VALUE_FROM_PERCENT(0.5f, percent) + y_pos, 0.0f); //left
    glEnd();

	// Fish eye
	fish_eye(x_pos, y_pos, percent, 0.75f, 0.4f);
	fish_eye_dot(x_pos, y_pos, percent, 0.75f, 0.39f);

}

void fish_eye(float x_pos, float y_pos, float percent, float x, float y)
{
	int i;
	float x_val, y_val;
    double radius = 0.02;
	double twicePi = 2.0 * 3.142;
    
	glBegin(GL_TRIANGLE_FAN); //BEGIN CIRCLE
	glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(VALUE_FROM_PERCENT(x, percent) + x_pos, VALUE_FROM_PERCENT( y, percent) + y_pos); // center of circle
    
	for (i = 0; i <= 20; i++) {
		x_val =  (x + (radius * cos(i * twicePi / 20)));
		y_val = (y + (radius * sin(i * twicePi / 20)));
        
		glVertex3f( VALUE_FROM_PERCENT( x_val, percent) + x_pos, VALUE_FROM_PERCENT( y_val, percent) + y_pos, 0.0f);
    }

    glEnd();
}

void fish_eye_dot(float x_pos, float y_pos, float percent, float x, float y)
{
	int i;
	float x_val, y_val;
    double radius = 0.005;
	double twicePi = 2.0 * 3.142;
    
	glBegin(GL_TRIANGLE_FAN); //BEGIN CIRCLE
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(VALUE_FROM_PERCENT(x, percent) + x_pos, VALUE_FROM_PERCENT( y, percent) + y_pos); // center of circle
    
	for (i = 0; i <= 20; i++) {
		x_val =  (x + (radius * cos(i * twicePi / 20)));
		y_val = (y + (radius * sin(i * twicePi / 20)));
        
		glVertex3f( VALUE_FROM_PERCENT( x_val, percent) + x_pos, VALUE_FROM_PERCENT( y_val, percent) + y_pos, 0.0f);
    }

    glEnd();
}


void fish_circle(float x_pos, float y_pos, float percent)
{
	int i;
	float x, y;
	float x_val, y_val;
    double radius = 0.10;
	double twicePi = 2.0 * 3.142;
	x = 0.2f, y = -0.25f;
    
	glBegin(GL_TRIANGLE_FAN); //BEGIN CIRCLE
	glColor3f(0.9f, 0.9f, 0.6f);
    glVertex2f(x + x_pos, y + y_pos); // center of circle
    
	for (i = 0; i <= 20; i++) {
		x_val =  (x + (radius * cos(i * twicePi / 20)));
		y_val = (y + (radius * sin(i * twicePi / 20)));
        
		glVertex3f(x_val + x_pos, y_val + y_pos, 0.0f);
    }

    glEnd();
}

void fish_bubble_two(float x_pos, float y_pos, float percent)
{
	float i;
	float x, y;
    double radius = 0.040f;
	double twicePi = 2.0f * 3.142;

	glLineWidth(0.8);
    glBegin(GL_LINE_LOOP); //BEGIN CIRCLE
	glColor3f(1.0f, 1.0f, 1.0f);
    for (i = 0.0f; i <= twicePi; i+= 0.01f)   {
		x = radius * cos(i);
		y = radius * sin(i);
        glVertex3f(VALUE_FROM_PERCENT( x , percent)+ x_pos, VALUE_FROM_PERCENT( y , percent)+ y_pos, 0.0f);
    }
    glEnd();

	glBegin(GL_QUADS);
	
    glColor3f(1.0f, 1.0f, 1.0f);
	// Fish back
	glVertex3f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos, VALUE_FROM_PERCENT(0.03f, percent) + y_pos, 0.0f); //center
	glVertex3f(VALUE_FROM_PERCENT(0.015f, percent) + x_pos, VALUE_FROM_PERCENT(0.04f, percent) + y_pos, 0.0f); // right
	glVertex3f(VALUE_FROM_PERCENT(0.005f, percent) + x_pos, VALUE_FROM_PERCENT(0.03f, percent) + y_pos, 0.0f); //left
	glVertex3f(VALUE_FROM_PERCENT(0.015f, percent) + x_pos, VALUE_FROM_PERCENT(0.02f, percent) + y_pos, 0.0f); //center
	glEnd();
}


void bubble_two(float x_pos, float y_pos, float percent)
{
	float i;
	float x, y;
    double radius = 0.040f;
	double twicePi = 2.0f * 3.142;

	glLineWidth(0.8);
    glBegin(GL_LINE_LOOP); //BEGIN CIRCLE
	glColor3f(1.0f, 1.0f, 1.0f);
    for (i = 0.0f; i <= twicePi; i+= 0.01f)   {
		x = radius * cos(i);
		y = radius * sin(i);
        glVertex3f(VALUE_FROM_PERCENT( x , percent)+ x_pos, VALUE_FROM_PERCENT( y , percent)+ y_pos, 0.0f);
    }
    glEnd();

	glBegin(GL_QUADS);
	
    glColor3f(1.0f, 1.0f, 1.0f);
	// Fish back
	glVertex3f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos, VALUE_FROM_PERCENT(0.03f, percent) + y_pos, 0.0f); //center
	glVertex3f(VALUE_FROM_PERCENT(0.015f, percent) + x_pos, VALUE_FROM_PERCENT(0.04f, percent) + y_pos, 0.0f); // right
	glVertex3f(VALUE_FROM_PERCENT(0.005f, percent) + x_pos, VALUE_FROM_PERCENT(0.03f, percent) + y_pos, 0.0f); //left
	glVertex3f(VALUE_FROM_PERCENT(0.015f, percent) + x_pos, VALUE_FROM_PERCENT(0.02f, percent) + y_pos, 0.0f); //center
	glEnd();
}


void fish_four(float x_pos, float y_pos, float percent, float TailMoveUpdate)
{
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.5f, 0.0f);
	// Fish Rectangle
	glVertex3f(VALUE_FROM_PERCENT(-0.8f, percent) + x_pos, VALUE_FROM_PERCENT(-0.4f, percent) + y_pos, 0.0f); // left
	glVertex3f(VALUE_FROM_PERCENT(-0.6f, percent) + x_pos, VALUE_FROM_PERCENT(-0.55f, percent) + y_pos, 0.0f); // bottom
	glVertex3f(VALUE_FROM_PERCENT(-0.4f, percent) + x_pos, VALUE_FROM_PERCENT(-0.4f, percent) + y_pos, 0.0f); // right
	glVertex3f(VALUE_FROM_PERCENT(-0.6f, percent) + x_pos, VALUE_FROM_PERCENT(-0.25f, percent) + y_pos, 0.0f); // top
	glEnd();

	glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.9f, 0.2f);
	glVertex3f(VALUE_FROM_PERCENT(-0.45f, percent) + x_pos, VALUE_FROM_PERCENT(-0.40f, percent) + y_pos, 0.0f); // left
	glVertex3f(VALUE_FROM_PERCENT(-0.35f, percent) + x_pos, (VALUE_FROM_PERCENT(-0.5f, percent) + y_pos) + TailMoveUpdate, 0.0f); // right
	glVertex3f(VALUE_FROM_PERCENT(-0.35f, percent) + x_pos, (VALUE_FROM_PERCENT(-0.3f, percent) + y_pos) + TailMoveUpdate, 0.0f); // top
	glEnd();

	fish_eye(x_pos, y_pos, percent, -0.74f, -0.39f);
	fish_eye_dot(x_pos, y_pos, percent, -0.74f, -0.38f);

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.9f, 0.2f);
	// Fish furr top
	glVertex3f(VALUE_FROM_PERCENT(-0.6f, percent) + x_pos, VALUE_FROM_PERCENT(-0.25f, percent) + y_pos, 0.0f); //center
	glVertex3f(VALUE_FROM_PERCENT(-0.5f, percent) + x_pos, (VALUE_FROM_PERCENT(-0.15f, percent) + y_pos) + TailMoveUpdate, 0.0f); // right
	glVertex3f(VALUE_FROM_PERCENT(-0.45f, percent) + x_pos, (VALUE_FROM_PERCENT(-0.2f, percent) + y_pos) + TailMoveUpdate, 0.0f); //left

	// Fish furr bottom
	glVertex3f(VALUE_FROM_PERCENT(-0.6f, percent) + x_pos, VALUE_FROM_PERCENT(-0.55f, percent) + y_pos, 0.0f); //center
	glVertex3f(VALUE_FROM_PERCENT(-0.5f, percent) + x_pos, (VALUE_FROM_PERCENT(-0.65f, percent) + y_pos) + TailMoveUpdate, 0.0f); // right
	glVertex3f(VALUE_FROM_PERCENT(-0.45f, percent) + x_pos, (VALUE_FROM_PERCENT(-0.6f, percent) + y_pos) + TailMoveUpdate, 0.0f); //left
    glEnd();

	glBegin(GL_QUADS);
	// Fish furr Middle
	glVertex3f(VALUE_FROM_PERCENT(-0.7f, percent) + x_pos, VALUE_FROM_PERCENT(-0.4f, percent) + y_pos, 0.0f); //center
	glVertex3f(VALUE_FROM_PERCENT(-0.66f, percent) + x_pos, VALUE_FROM_PERCENT(-0.35f, percent) + y_pos, 0.0f); // right
	glVertex3f(VALUE_FROM_PERCENT(-0.68f, percent) + x_pos, VALUE_FROM_PERCENT(-0.4f, percent) + y_pos, 0.0f); //left
	glVertex3f(VALUE_FROM_PERCENT(-0.65f, percent) + x_pos, VALUE_FROM_PERCENT(-0.45f, percent) + y_pos, 0.0f); //left
    glEnd();

	// Fish shepti line
	glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(-0.44f, percent) + x_pos, VALUE_FROM_PERCENT(-0.4f, percent) + y_pos, 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(-0.37f, percent) + x_pos, (VALUE_FROM_PERCENT(-0.35f, percent) + y_pos) + TailMoveUpdate, 0.0f);

	glVertex3f(VALUE_FROM_PERCENT(-0.44f, percent) + x_pos, VALUE_FROM_PERCENT(-0.40f, percent) + y_pos, 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(-0.37f, percent) + x_pos, (VALUE_FROM_PERCENT(-0.4f, percent) + y_pos) + TailMoveUpdate, 0.0f);

	glVertex3f(VALUE_FROM_PERCENT(-0.44f, percent) + x_pos, VALUE_FROM_PERCENT(-0.40f, percent) + y_pos, 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(-0.37f, percent) + x_pos, (VALUE_FROM_PERCENT(-0.45f, percent) + y_pos) + TailMoveUpdate, 0.0f);
    glEnd();
}