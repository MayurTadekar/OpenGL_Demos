// Win32 headers
#include<windows.h> 
#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES 1
#include <math.h>

// OpenGL Related Header Files
#include <gl/GL.h>
#include <gl/GLU.h>

// Custom Header Files
#include "OGL.h"
#include "hanumansita_bhet.h"

void SitaHanumanBhet(void)
{
    // Set to identity matrix
	glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -10.0f);

	glPushMatrix();


	glTranslatef(0.0f, 0.0f, -20.0f);
	glScalef(22.0f, 12.5f, 1.0f);

	glBegin(GL_QUADS);

	glColor3f(243.0f/255.0f, 147.0f/255.0f, 50.0f/255.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);

	glColor3f(154.0f/255.0f, 45.0f/255.0f, 29.0f/255.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);

	glEnd();

	glPopMatrix();

	glPushMatrix();

	glTranslatef(0.0f, -4.75f, -5.0f);
	glScalef(15.0f, 2.0f, 1.0f);

	glBegin(GL_QUADS);

	glColor3f(0.0f, 0.0f, 0.0f); // Black color
	glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);

	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);

	glEnd();

	glPopMatrix();

	glPushMatrix();

	glTranslatef(-2.0f, 2.5f, -4.0f);
	glScalef(8.5f, 6.0f, 1.0f);
	
	drawSita();

	glPopMatrix();

	glPushMatrix();
	glTranslatef(-4.0f, -2.0f, -5.0f);
	glScalef(10.0f, 8.0f, 1.0f);

	BigTree_shivkumar(0.0f, 0.0f, 5.0f, 30.0f);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.0f, -2.0f, -8.0f);
	glScalef(9.0f, 7.0f, 1.0f);

	BigTree_shivkumar(0.0f, 0.0f, 5.0f, 30.0f);

	glPopMatrix();

	// glPushMatrix();
	// glTranslatef(-3.5f, 5.0f, -8.0f);
	// glScalef(17.0f, 16.0f, 1.0f);

	// //drawHanuman();

	// glPopMatrix();

	glPushMatrix();
	glTranslatef(0.55f, -0.5f, -8.0f);
	glScalef(0.3f, 0.3f, 0.3f);
	glRotatef(45.0f, 1.0f, 0.0f, 1.0f);

	drawRing(0.5f, 1.0f, 100);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.55f, -0.2f, -8.0f);
	glScalef(0.3f, 0.3f, 0.3f);

	drawRingStone(0.0f, 0.5f, 60);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.4f, 0.8f, -8.0f);
	glScalef(0.6f, 0.6f, 0.6f);

	drawSitaUpper(0.0f, 0.5f, 60);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.8f, -0.1f, -8.0f);
	glScalef(0.65f, 0.6f, 0.6f);

	drawHanumanMouthFront(0.0f, 0.7f, 60);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.2f, 0.2f, -8.0f);
	glScalef(1.0f, 1.0f, 1.0f);

	drawHanumanMouthBack(0.0f, 0.7f, 60);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.0f, 0.2f, -8.0f);
	glScalef(2.0f, 2.0f, 2.0f);

	drawHanumanCrown();

	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.25f, -1.6f, -3.0f);
	glScalef(7.5f, 7.5f, 7.5f);

	drawHanumanCrownTop();

	glPopMatrix();

	glPushMatrix();
	glTranslatef(7.4f, -2.0f, -3.0f);
	glScalef(6.0f, 5.7f, 6.0f);
	glRotatef(180.0f, 0.0f, 1.0f, 0.0f);

	drawHanumanNewBody();	

	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.6f, -2.1f, -3.0f);
	glScalef(2.8f, 3.0f, 3.0f);
	glRotatef(180.0f, 0.0f, 1.0f, 0.0f);

	drawHanumanHand();

	glPopMatrix();

    glPushMatrix();

	glTranslatef(5.3f, 1.0f, -3.0f);
	glScalef(6.0f, 12.1f, 9.0f);
	glRotatef(300.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(180.0f, 0.0f, 0.0f, 1.0f);


	Sheput();
	glPopMatrix();

}


void Sheput_Calculation(void)
{
    struct curve_shivkumar curve1;

    curve1.x0 = 0.0f;
    curve1.x1 = 0.25f;
    curve1.x2 = 0.29f;
    curve1.x3 = 0.5f;

    curve1.y0 = 0.0f;
    curve1.y1 = -0.1f;
    curve1.y2 = 0.47f;
    curve1.y3 = 0.5f;


    int i = 0;
    for(float t = 0.0f; t <= 1.0f; t = t + 0.01f)
    {
        float u = (1 - t);

        Sheput_xt[i] = ((pow(u, 3) * curve1.x0) + (3 * t * pow(u, 2) * curve1.x1) + (3 * pow(t, 2) * u * curve1.x2) + (pow(t, 3) * curve1.x3));
        Sheput_yt[i] = ((pow(u, 3) * curve1.y0) + (3 * t * pow(u, 2) * curve1.y1) + (3 * pow(t, 2) * u * curve1.y2) + (pow(t, 3) * curve1.y3)); 
        i++;
    }
    

}

void SheputTura_Calculate(void)
{
    struct curve_shivkumar curve1;

    curve1.x0 = 0.0f;
    curve1.x1 = -0.06f;
    curve1.x2 = 0.0f;
    curve1.x3 = 0.0f;

    curve1.y0 = 0.0f;
    curve1.y1 = 0.06f;
    curve1.y2 = 0.13f;
    curve1.y3 = 0.17f;


    int i = 0;
    for(float t = 0.0f; t <= 1.0f; t = t + 0.01f)
    {
        float u = (1 - t);

        SheputTura_xt[i] = ((pow(u, 3) * curve1.x0) + (3 * t * pow(u, 2) * curve1.x1) + (3 * pow(t, 2) * u * curve1.x2) + (pow(t, 3) * curve1.x3));
        SheputTura_yt[i] = ((pow(u, 3) * curve1.y0) + (3 * t * pow(u, 2) * curve1.y1) + (3 * pow(t, 2) * u * curve1.y2) + (pow(t, 3) * curve1.y3)); 
        i++;
    }
}

void SheputTura(float x_pos, float y_pos, float percentX, float percentY)
{
    glBegin(GL_LINE_STRIP);
    {
        for (int i = 0; i < 100; i++)
        {
            glVertex3f( VALUE_FROM_PERCENT( SheputTura_xt[i], percentX), VALUE_FROM_PERCENT( SheputTura_yt[i], percentY), 0.0f);
        }
    }
    glEnd();
}
void Sheput(void)
{
    glLineWidth(9.0f);
    glColor3f(0.0f, 0.0f, 0.0f); // black
    glBegin(GL_LINE_STRIP);
    {
        for ( int i = 0; i <= 100; i++)
        {
            glVertex3f(Sheput_xt[i], Sheput_yt[i], 0.0f);
        }
    }
    glEnd();

    glRotatef(70.0f, 0.0f, 0.0f, 1.0f);
    glLineWidth(3.0f);
    glColor3f(0.0f, 0.0f, 0.0f); // black
    SheputTura(0.0f, 0.0f, 150.0f, 100.0f);
    SheputTura(0.0f, 0.0f, 110.0f, 100.0f);
    SheputTura(0.0f, 0.0f, 60.0f, 100.0f);
    SheputTura(0.0f, 0.0f, 10.0f, 100.0f);

    SheputTura(0.0f, 0.0f, -150.0f, 100.0f);
    SheputTura(0.0f, 0.0f, -110.0f, 100.0f);
    SheputTura(0.0f, 0.0f, -60.0f, 100.0f);
    SheputTura(0.0f, 0.0f, -10.0f, 100.0f);
}


void drawSita(){
        drawFace();
        drawNose();
        drawEyeBrows();
        drawEye();
        drawHair();
        drawCloth();
        drawNeck();
        drawDress();
        drawLowerDress();
        drawHandStart();
        drawForearm();
        drawFoot();
        drawBindi();

}

void drawHanumanCrown(){
	glBegin(GL_QUADS);
	
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.20f, 0.2f);
	glVertex2f(0.85f, 0.2f);
	glVertex2f(0.85f, 0.38f);
	glVertex2f(0.20f, 0.38f);

	glEnd();

}

void drawHanumanCrownTop(){

	glBegin(GL_TRIANGLE_STRIP);
	
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.25f, 0.25f);
	glVertex2f(0.30f, 0.25f);
	glVertex2f(0.275f, 0.35f);

	glEnd();

}


void drawHanumanMouthFront(float innerRadius, float outerRadius, int segments) {

   float angleStep = 2.0f * M_PI / segments;

    glBegin(GL_TRIANGLE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
    for (int i = 0; i <= segments; ++i) {
        float angle = i * angleStep;
        float xOuter = cos(angle) * outerRadius;
        float yOuter = sin(angle) * outerRadius;
        float xInner = cos(angle) * innerRadius;
        float yInner = sin(angle) * innerRadius;

        glVertex2f(xOuter, yOuter); // outer point
        glVertex2f(xInner, yInner); // inner point
    }

    glEnd();

}


void drawHanumanMouthBack(float innerRadius, float outerRadius, int segments) {

   float angleStep = 2.0f * M_PI / segments;

    glBegin(GL_TRIANGLE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
    for (int i = 0; i <= segments; ++i) {
        float angle = i * angleStep;
        float xOuter = cos(angle) * outerRadius;
        float yOuter = sin(angle) * outerRadius;
        float xInner = cos(angle) * innerRadius;
        float yInner = sin(angle) * innerRadius;

        glVertex2f(xOuter, yOuter); // outer point
        glVertex2f(xInner, yInner); // inner point
    }

    glEnd();

}

void drawSitaUpper(float innerRadius, float outerRadius, int segments) {

   float angleStep = 2.0f * M_PI / segments;

    glBegin(GL_TRIANGLE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
    for (int i = 0; i <= segments; ++i) {
        float angle = i * angleStep;
        float xOuter = cos(angle) * outerRadius;
        float yOuter = sin(angle) * outerRadius;
        float xInner = cos(angle) * innerRadius;
        float yInner = sin(angle) * innerRadius;

        glVertex2f(xOuter, yOuter); // outer point
        glVertex2f(xInner, yInner); // inner point
    }

    glEnd();

}



void drawRingStone(float innerRadius, float outerRadius, int segments) {
    float angleStep = 2.0f * M_PI / segments;

    glBegin(GL_TRIANGLE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
    for (int i = 0; i <= segments; ++i) {
        float angle = i * angleStep;
        float xOuter = cos(angle) * outerRadius;
        float yOuter = sin(angle) * outerRadius;
        float xInner = cos(angle) * innerRadius;
        float yInner = sin(angle) * innerRadius;

        glVertex2f(xOuter, yOuter); // outer point
        glVertex2f(xInner, yInner); // inner point
    }

    glEnd();

}


    void drawFace() {
        glBegin(GL_POLYGON);
        glColor3f(0.0f, 0.0f, 0.0f);     // Black
        glVertex2f(0.03f, -0.17f);      // Vertex 1
        glVertex2f(0.09f, -0.16f);      // Vertex 2
        glVertex2f(0.11f, -0.16f);      // Vertex 3
        glVertex2f(0.12f, -0.14f);      // Vertex 4
        glVertex2f(0.12f, -0.08f);      // Vertex 5
        glVertex2f(0.12f, -0.07f);      // Vertex 6
        glVertex2f(0.11f, -0.04f);      // Vertex 7
        glVertex2f(0.11f, -0.03f);      // Vertex 8
        glVertex2f(0.03f, -0.09f);      // Vertex 9
        glEnd();
    }

    void drawNose() {
        glBegin(GL_POLYGON);
        glColor3f(0.0f, 0.0f, 0.0f);  // Black
        glVertex2f(0.12f, -0.12f);      // Vertex 1
        glVertex2f(0.13f, -0.12f);      // Vertex 2
        glVertex2f(0.13f, -0.11f);      // Vertex 3
        glVertex2f(0.13f, -0.11f);      // Vertex 4
        glVertex2f(0.12f, -0.09f);      // Vertex 5
        glEnd();
    }

    void drawEyeBrows() {
        glBegin(GL_LINES);
        glColor3f(0.0f, 0.0f, 0.0f);  // Black
        glVertex2f(0.1f, -0.075f);
        glVertex2f(0.11111222f, -0.075f);
        glEnd();
    }

      void drawBindi() {
        glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 0.0f);  // Black
        glVertex2f(0.11f, -0.054345f);
        glVertex2f(0.1123455f, -0.054345f);
        glVertex2f(0.1123455f, -0.064345f);
        glVertex2f(0.11f, -0.064345f);
        glEnd();
    }

    void drawEye() {
        glBegin(GL_POLYGON);
        glColor3f(0.0f, 0.0f, 0.0f);  // Black
        glVertex2f(0.10f, -0.09f);
        glColor3f(0.0f, 0.0f, 0.0f);  // Black
        glVertex2f(0.11f, -0.09f);
        glColor3f(0.0f, 0.0f, 0.0f);  // Black
        glVertex2f(0.11f, -0.08f);
        glColor3f(0.0f, 0.0f, 0.0f);  // Black
        glVertex2f(0.10f, -0.08f);
        glEnd();
    }

    void drawHair() {
        glBegin(GL_POLYGON);

        glColor3f(0.0f, 0.0f, 0.0f);  // Black
        glVertex2f(0.01f, -0.2f);         // Vertex 1
        glVertex2f(0.02f, -0.18f);       // Vertex 2
        glVertex2f(0.05f, -0.11f);      // Vertex 3
        glVertex2f(0.04f, -0.07f);      // Vertex 4
        glVertex2f(0.11f, -0.05f);     // Vertex 5
        glVertex2f(0.11f, -0.03f);     // Vertex 6
        glVertex2f(0.05f, -0.04f);     // Vertex 7
        glVertex2f(0.02f, -0.11f);    // Vertex 8
        glVertex2f(0.01f, -0.2f);    // Vertex 9
        glVertex2f(0.01f, -0.3f);    // Vertex 10
        glVertex2f(0.01f, -0.4f);    // Vertex 11
        glVertex2f(0.0f, -0.5f);    // Vertex 12
        glVertex2f(-0.01f, -0.4f);    // Vertex 13
        glVertex2f(-0.02f, -0.4f);    // Vertex 14
        glVertex2f(-0.03f, -0.5f);    // Vertex 15
        glVertex2f(-0.04f, -0.5f);    // Vertex 16
        glVertex2f(0.01f, -0.5f);    // Vertex 17
        glEnd();
    }

    void drawCloth() {
        glBegin(GL_POLYGON);
        glColor3f(0.0f, 0.0f, 0.0f); // Black
        glVertex2f(0.01f, -0.2f);         // Vertex 1
        glVertex2f(0.02f, -0.18f);       // Vertex 2
        glVertex2f(0.04f, -0.11f);      // Vertex 3
        glVertex2f(0.03f, -0.07f);      // Vertex 4
        glVertex2f(0.09f, -0.05f);     // Vertex 5
        glVertex2f(0.09f, -0.03f);     // Vertex 6
        glVertex2f(0.08f, -0.04f);     // Vertex 7
        glVertex2f(0.07f, -0.11f);    // Vertex 8
        glVertex2f(0.08f, -0.2f);    // Vertex 9
        glVertex2f(0.08f, -0.3f);    // Vertex 10
        glVertex2f(0.08f, -0.6f);    // Vertex 11
        glVertex2f(0.09f, -0.8f);    // Vertex 12
        glVertex2f(0.03f, -0.7f);    // Vertex 13
        glVertex2f(0.01f, -0.7f);    // Vertex 14
        glVertex2f(0.01f, -0.6f);    // Vertex 15
        glVertex2f(0.05f, -0.8f);    // Vertex 16
        glVertex2f(0.06f, -0.7f);    // Vertex 17
        glEnd();
    }

    void drawNeck() {
        glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 0.0f);  // Black
        glVertex2f(0.05f, -0.20f);      // Vertex 1
        glVertex2f(0.09f, -0.20f);     // Vertex 2
        glVertex2f(0.09f, -0.16f);      // Vertex 3
        glVertex2f(0.05f, -0.16f);      // Vertex 4
        glEnd();
    }

    void drawDress() {
        glBegin(GL_POLYGON);
        glColor3f(0.0f, 0.0f, 0.0f); // Black
        glVertex2f(0.02f, -0.4f);      // Vertex 1
        glVertex2f(0.13f, -0.4f);     //  Vertex 2

        glVertex2f(0.10f, -0.20f);     // Vertex 3
        glVertex2f(0.04f, -0.20f);     // Vertex 4
        glEnd();
    }

    void drawLowerDress() {
        glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 0.0f); // Black
        glVertex2f(0.01f, -0.8f);      // Vertex 1
        glVertex2f(0.14f, -0.8f);     //  Vertex 2
        glVertex2f(0.12f, -0.25f);     // Vertex 3
        glVertex2f(0.03f, -0.29f);     // Vertex 4
        glEnd();
    }

    void drawFoot() {
        glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 0.0f);  // Black

        glVertex2f(0.03f, -0.85f);
        glVertex2f(0.07f, -0.85f);
        glVertex2f(0.07f, -0.8f);
        glVertex2f(0.03f, -0.8f);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 0.0f);  // Black

        glVertex2f(0.07f, -0.85f);
        glVertex2f(0.08f, -0.85f);
        glVertex2f(0.08f, -0.83f);
        glVertex2f(0.07f, -0.83f);

        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 0.0f);  // Black

        glVertex2f(0.09f, -0.85f);
        glVertex2f(0.13f, -0.85f);
        glVertex2f(0.13f, -0.8f);
        glVertex2f(0.09f, -0.8f);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 0.0f);  // Black

        glVertex2f(0.13f, -0.85f);
        glVertex2f(0.14f, -0.85f);
        glVertex2f(0.14f, -0.83f);
        glVertex2f(0.13f, -0.83f);
        glEnd();

    }

    void drawHandStart() {
        glBegin(GL_QUADS);

        glColor3f(0.0f, 0.0f, 0.0f); // black
        glVertex2f(0.09f, -0.28f);

        glColor3f(0.0f, 0.0f, 0.0f);  // black
        glVertex2f(0.16f, -0.32f);

        glColor3f(0.0f, 0.0f, 0.0f);  // black
        glVertex2f(0.21f, -0.30f);

        glColor3f(0.0f, 0.0f, 0.0f); // black
        glVertex2f(0.07f, -0.20f);

        glEnd();
    }

    void drawForearm() {

        glBegin(GL_QUADS);
		{

			glColor3f(0.0f, 0.0f, 0.0f);  // black
			glVertex2f(0.16f, -0.32f);

			glColor3f(0.0f, 0.0f, 0.0f);  // black
			glVertex2f(0.25f, -0.32f);

			glColor3f(0.0f, 0.0f, 0.0f);  // black
			glVertex2f(0.28f, -0.30f);

			glColor3f(0.0f, 0.0f, 0.0f);  // black
			glVertex2f(0.19f, -0.28f);
		}
        glEnd();

		glBegin(GL_TRIANGLES);
		{
			glColor3f(0.0f, 0.0f, 0.0f);  // black
			glVertex2f(0.28f, -0.30f);

			glColor3f(0.0f, 0.0f, 0.0f);  // black
			glVertex2f(0.24f, -0.32f);

			glColor3f(0.0f, 0.0f, 0.0f);  // black
			glVertex2f(0.33f, -0.33f);
			
		}
		glEnd();

		glBegin(GL_TRIANGLES);
		{
			glColor3f(0.0f, 0.0f, 0.0f);  // black
			glVertex2f(0.28f, -0.31f);

			glColor3f(0.0f, 0.0f, 0.0f);  // black
			glVertex2f(0.25f, -0.32f);

			glColor3f(0.0f, 0.0f, 0.0f);  // black
			glVertex2f(0.28f, -0.35f);
		}
		glEnd();

    }

	
// Complete Tree
void BigTree_shivkumar(float x_pos, float y_pos, float percentX, float percentY)
{
	// code

	BigTreeleaves_shivkumar(-0.5f + x_pos, 0.47f + y_pos, -3.0f + percentX, 0.0f + percentY, 12.0f, 55.0f, 31.0f);
	BigTreeleaves_shivkumar(-0.55f + x_pos, 0.8f + y_pos, -3.0f + percentX, 0.0f + percentY, 12.0f, 55.0f, 31.0f);
	BigTreeleaves_shivkumar(-0.79f + x_pos, 0.7f + y_pos, 7.0f + percentX, 0.0f + percentY, 12.0f, 55.0f, 31.0f);
	BigTreeleaves_shivkumar(-0.4f + x_pos, 0.53f + y_pos, 13.0f + percentX, 0.0f + percentY, 12.0f, 55.0f, 31.0f);
	BigTreeleaves_shivkumar(-0.75f + x_pos, 0.5f + y_pos, 7.0f + percentX, 0.0f + percentY, 12.0f, 55.0f, 31.0f);

	BigTreeleaves_shivkumar(-0.6f + x_pos, 0.75f + y_pos, -3.0f + percentX, 0.0f + percentY, 26.0f, 99.0f, 55.0f);
	BigTreeleaves_shivkumar(-0.44f + x_pos, 0.6f + y_pos, 4.0f + percentX, 0.0f + percentY, 26.0f, 99.0f, 55.0f);
	BigTreeleaves_shivkumar(-0.63f + x_pos, 0.62f + y_pos, 0.0f + percentX, 0.0f + percentY, 26.0f, 99.0f, 55.0f);

	BigTreeStem_shivkumar(-0.25f + x_pos, 0.35f + y_pos, 45.0f + percentX, 120.0f + percentY);

	BigTreeleaves_shivkumar(-0.44f + x_pos, 0.57f + y_pos, -3.0f + percentX, 0.0f + percentY, 78.0f, 150.0f, 43.0f);
	BigTreeleaves_shivkumar(-0.66f + x_pos, 0.61f + y_pos, 6.0f + percentX, 0.0f + percentY, 78.0f, 150.0f, 43.0f);
	BigTreeleaves_shivkumar(-0.6f + x_pos, 0.51f + y_pos, -1.0f + percentX, 0.0f + percentY, 78.0f, 150.0f, 43.0f);
	BigTreeleaves_shivkumar(-0.75f + x_pos, 0.6f + y_pos, -1.0f + percentX, 0.0f + percentY, 78.0f, 150.0f, 43.0f);

}

// Blocks of Leaves of tree
void BigTreeleaves_shivkumar(float x_pos, float y_pos, float percentX, float percentY, float red, float green, float blue)
{
	// codeCircle(0.0f + x_pos, 0.0f + y_pos,  20.0f + percentX, 0.0f + percentY, 0.2f, red, green, blue);
	BigTreeCircle_shivkumar(0.08f + x_pos, 0.07f + y_pos,  20.0f + percentX, 0.0f + percentY, 0.2f, red, green, blue);
	BigTreeCircle_shivkumar(0.12f + x_pos, 0.09f + y_pos,  20.0f + percentX, 0.0f + percentY, 0.2f, red, green, blue);
	BigTreeCircle_shivkumar(0.05f + x_pos, 0.02f + y_pos,  20.0f + percentX, 0.0f + percentY, 0.2f, red, green, blue);
	BigTreeCircle_shivkumar(0.13f + x_pos, 0.0f + y_pos,  40.0f + percentX, 0.0f + percentY, 0.2f, red, green, blue); 
	BigTreeCircle_shivkumar(0.18f + x_pos, 0.07f + y_pos,  20.0f + percentX, 0.0f + percentY, 0.2f, red, green, blue);
	BigTreeCircle_shivkumar(0.19f + x_pos, 0.0f + y_pos,  20.0f + percentX, 0.0f + percentY, 0.2f, red, green, blue);
	BigTreeCircle_shivkumar(0.18f + x_pos, -0.07f + y_pos,  20.0f + percentX, 0.0f + percentY, 0.2f, red, green, blue);
	BigTreeCircle_shivkumar(0.04f + x_pos, -0.06f + y_pos,  20.0f + percentX, 0.0f + percentY, 0.2f, red, green, blue);
	BigTreeCircle_shivkumar(0.11f + x_pos, -0.06f + y_pos,  20.0f + percentX, 0.0f + percentY, 0.2f, red, green, blue);
}

// Small blocks for creating 1 big block of tree leaves 
void BigTreeCircle_shivkumar(float x_pos, float y_pos, float percentX, float percentY, float radius, float red, float green, float blue)
{	
	glPointSize(63.0f);
	glBegin(GL_POINTS);
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f); // Black color
	{
		glVertex3f(VALUE_FROM_PERCENT( 0.0f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.0f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( 0.0f + 0.05f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.0f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( 0.0f - 0.05f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.0f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( 0.0f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.0f + 0.05f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( 0.0f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.0f - 0.05f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( 0.0f + 0.1f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.0f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( 0.0f - 0.1f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.0f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( 0.0f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.0f + 0.1f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( 0.0f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.0f - 0.1f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( 0.0f + 0.1f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.0f + 0.1f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( 0.0f - 0.1f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.0f - 0.1f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( 0.0f - 0.1f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.0f + 0.1f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( 0.0f + 0.1f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.0f - 0.1f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( 0.0f + 0.15f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.0f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( 0.0f - 0.15f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.0f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( 0.0f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.0f + 0.15f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( 0.0f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.0f - 0.15f, percentY) + y_pos, 0.0f);
	}
	glEnd();
}

// Stem of tree
void BigTreeStem_shivkumar(float x_pos, float y_pos, float percentX, float percentY)
{
	// variable declaration
	struct BigTreeCurve_shivkumar curve1;
	struct BigTreeCurve_shivkumar curve2;
	struct BigTreeCurve_shivkumar curve3;
	struct BigTreeCurve_shivkumar curve4;

	GLfloat t = 0.0f;
	int i = 0;

	// code
	/////////////////////////////////////////////////////////////////////

	curve3.x1 = -0.4f;
	curve3.y1 = -0.40f;
	curve3.x2 = -0.45f;
	curve3.y2 = -0.28f;
	curve3.x3 = -0.5f;
	curve3.y3 = -0.05f;
	curve3.x4 = -0.58f;
	curve3.y4 = 0.1f;

	curve4.x1 = -0.7f;
	curve4.x2 = -0.6f;
	curve4.x3 = -0.68f;
	curve4.x4 = -0.65f;
	curve4.y1 = -0.40f;
	curve4.y2 = -0.2f;
	curve4.y3 = -0.2f;
	curve4.y4 = 0.13f;

	for(t = 0.0f, i = 0; t < 1.0f; t = t + 0.01f, i++)
	{
		BigTxt3[i] = ((pow(1-t, 3) * curve3.x1) + ((3 * t) * pow(1-t, 2) * curve3.x2) + ((3 * pow(t, 2)) * (1 - t) * curve3.x3) + (pow(t, 3) * curve3.x4));
		BigTyt3[i] = ((pow(1-t, 3) * curve3.y1) + ((3 * t) * pow(1-t, 2) * curve3.y2) + ((3 * pow(t, 2)) * (1 - t) * curve3.y3) + (pow(t, 3) * curve3.y4));
	}	
	

	for(t = 0.0f, i = 0; t < 1.0f; t = t + 0.01f, i++)
	{
		BigTxt4[i] = ((pow(1-t, 3) * curve4.x1) + ((3 * t) * pow(1-t, 2) * curve4.x2) + ((3 * pow(t, 2)) * (1 - t) * curve4.x3) + (pow(t, 3) * curve4.x4));
		BigTyt4[i] = ((pow(1-t, 3) * curve4.y1) + ((3 * t) * pow(1-t, 2) * curve4.y2) + ((3 * pow(t, 2)) * (1 - t) * curve4.y3) + (pow(t, 3) * curve4.y4));
	}

	glBegin(GL_TRIANGLE_STRIP);
	{
		glColor4f(0.0f, 0.0f, 0.0f, 1.0f); // Black color
		for(int i = 0; i < 100; i++)
		{
			glVertex3f(VALUE_FROM_PERCENT( BigTxt3[i], percentX) + x_pos, VALUE_FROM_PERCENT( BigTyt3[i], percentY)+ y_pos, 0.0f);
			glVertex3f(VALUE_FROM_PERCENT( BigTxt4[i], percentX) + x_pos, VALUE_FROM_PERCENT( BigTyt4[i], percentY)+ y_pos, 0.0f);
		}
	}
	glEnd();

	/////////////////////////////////////////////////////////////
	curve1.x1 = -0.4f;
	curve1.y1 = -0.40f;
	curve1.x2 = -0.45f;
	curve1.y2 = -0.33f;
	curve1.x3 = -0.42f;
	curve1.y3 = -0.03f;
	curve1.x4 = -0.3f;
	curve1.y4 = 0.18f;

	curve2.x1 = -0.7f;
	curve2.x2 = -0.55f;
	curve2.x3 = -0.55f;
	curve2.x4 = -0.4f;
	curve2.y1 = -0.40f;
	curve2.y2 = -0.06f;
	curve2.y3 = -0.06f;
	curve2.y4 = 0.17f;

	for(t = 0.0f, i = 0; t < 1.0f; t = t + 0.01f, i++)
	{
		BigTxt1[i] = ((pow(1-t, 3) * curve1.x1) + ((3 * t) * pow(1-t, 2) * curve1.x2) + ((3 * pow(t, 2)) * (1 - t) * curve1.x3) + (pow(t, 3) * curve1.x4));
		BigTyt1[i] = ((pow(1-t, 3) * curve1.y1) + ((3 * t) * pow(1-t, 2) * curve1.y2) + ((3 * pow(t, 2)) * (1 - t) * curve1.y3) + (pow(t, 3) * curve1.y4));
	}	
	
	for(t = 0.0f, i = 0; t < 1.0f; t = t + 0.01f, i++)
	{
		BigTxt2[i] = ((pow(1-t, 3) * curve2.x1) + ((3 * t) * pow(1-t, 2) * curve2.x2) + ((3 * pow(t, 2)) * (1 - t) * curve2.x3) + (pow(t, 3) * curve2.x4));
		BigTyt2[i] = ((pow(1-t, 3) * curve2.y1) + ((3 * t) * pow(1-t, 2) * curve2.y2) + ((3 * pow(t, 2)) * (1 - t) * curve2.y3) + (pow(t, 3) * curve2.y4));
	}

	glBegin(GL_TRIANGLE_STRIP);
	{
		for(int i = 0; i < 100; i++)
		{
                glColor4f(0.0f, 0.0f, 0.0f, 1.0f); // Black color
                glVertex3f(VALUE_FROM_PERCENT( BigTxt1[i], percentX) + x_pos, VALUE_FROM_PERCENT( BigTyt1[i], percentY)+ y_pos, 0.0f);
			glColor4f(0.0f, 0.0f, 0.0f, 1.0f); // Black color
			glVertex3f(VALUE_FROM_PERCENT( BigTxt2[i], percentX) + x_pos, VALUE_FROM_PERCENT( BigTyt2[i], percentY)+ y_pos, 0.0f);
		}
	}
	glEnd();

}


void drawHanumanHand() {

        glBegin(GL_QUADS);
		{
			glColor3f(0.0f, 0.0f, 0.0f); // black color
			glVertex2f(0.1f, 0.3f);

			glColor3f(0.0f, 0.0f, 0.0f); // black color
			glVertex2f(0.5f, 0.2f);

			glColor3f(0.0f, 0.0f, 0.0f); // black color
			glVertex2f(0.5f, 0.3f);

			glColor3f(0.0f, 0.0f, 0.0f); // black color
			glVertex2f(0.1f, 0.5f);
		}
        glEnd();
	
        glBegin(GL_QUADS);
		{
			
			glColor3f(0.0f, 0.0f, 0.0f); // black color
			glVertex2f(0.65f, 0.55f);

			glColor3f(0.0f, 0.0f, 0.0f); // black color
			glVertex2f(0.42f, 0.3f);

			glColor3f(0.0f, 0.0f, 0.0f); // black color
			glVertex2f(0.5f, 0.2f);

			glColor3f(0.0f, 0.0f, 0.0f); // black color
			glVertex2f(0.65f, 0.43f);

		}
        glEnd();

		 glBegin(GL_QUADS);
		{
			glColor3f(0.0f, 0.0f, 0.0f); // black color
			glVertex2f(0.65f, 0.43f);

			glColor3f(0.0f, 0.0f, 0.0f); // black color
			glVertex2f(0.65f, 0.55f);

			glColor3f(0.0f, 0.0f, 0.0f); // black color
			glVertex2f(0.89f, 0.55f);

			glColor3f(0.0f, 0.0f, 0.0f); // black color
			glVertex2f(0.75f, 0.47f);

		}
        glEnd();

    }

void drawHanumanForearm() {

        glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 0.0f); // Black color
        glVertex2f(0.26f, -0.43f);
        glVertex2f(0.36f, -0.43f);
        glVertex2f(0.36f, -0.40f);
        glVertex2f(0.26f, -0.40f);

        glEnd();
    }

void drawHanumanBody() {

    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f); // Black color

    glVertex2f(0.36f, -0.55f); // org 1
    glVertex2f(0.38f, -0.56f);
    glVertex2f(0.39f, -0.57f);
    glVertex2f(0.40f, -0.58f);
    glVertex2f(0.41f, -0.57f);
    glVertex2f(0.45f, -0.56f);

    glVertex2f(0.40f, -0.55f);

    glVertex2f(0.46f, -0.55f); // org 2
    glVertex2f(0.46f, -0.30f); // org 3
    glVertex2f(0.36f, -0.33f); // org 4

    glEnd();

    }


void drawHanumanNewBody() {

    // Draw the neck
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f); // black color
	glVertex2f(0.55f, -0.10f);

	glColor3f(0.0f, 0.0f, 0.0f); // black color
	glVertex2f(0.7f, 0.29f);
	
	glColor3f(0.0f, 0.0f, 0.0f); // black color
	glVertex2f(0.80f, 0.34f);
	
    glColor3f(0.0f, 0.0f, 0.0f); // black color
	glVertex2f(0.85f, 0.3f);

    glColor3f(0.0f, 0.0f, 0.0f); // black color
	glVertex2f(0.9f, -0.10f); 

	// draw 
    glColor3f(0.0f, 0.0f, 0.0f); // blue color
	glVertex2f(0.91f, -0.10f); 

	glColor3f(0.0f, 0.0f, 0.0f); // red color
	glVertex2f(0.98f, 0.01f); 

	// glColor3f(0.0f, 0.0f, 0.0f);
	// glVertex2f(0.9f, -0.0f);

	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(1.1f, -0.10f);

	// glColor3f(0.0f, 0.0f, 0.0f);
	// glVertex2f(1.1f, -0.10f);


 
	// glVertex2f(0.5f, -0.10f);

    glEnd();

}

void drawRing(float innerRadius, float outerRadius, int segments) {
    float angleStep = 2.0f * M_PI / segments;

    glBegin(GL_TRIANGLE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
    for (int i = 0; i <= segments; ++i) {
        float angle = i * angleStep;
        float xOuter = cos(angle) * outerRadius;
        float yOuter = sin(angle) * outerRadius;
        float xInner = cos(angle) * innerRadius;
        float yInner = sin(angle) * innerRadius;

        glVertex2f(xOuter, yOuter); // outer point
        glVertex2f(xInner, yInner); // inner point
    }

    glEnd();

}
