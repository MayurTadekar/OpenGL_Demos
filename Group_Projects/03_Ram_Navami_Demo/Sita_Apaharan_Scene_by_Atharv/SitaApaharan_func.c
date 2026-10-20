// Win32 headers
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

#define _USE_MATH_DEFINES 1
#include <math.h>

// OpenGL related Header Files
#include <gl/GL.h>
#include <gl/GLU.h>

// Custom Header File
#include "OGL.h"
#include "SitaApaharan.h"

//////////////////////////////// Scene related Variable declaration ////////////////////////////////
// For Tree Stem
float Txt1[100], Txt2[100], Txt3[100], Txt4[100];
float Tyt1[100], Tyt2[100], Tyt3[100], Tyt4[100];

// For Mountain
float Mxt1[100], Mxt2[100], Mxt3[100], Mxt4[100];
float Myt1[100], Myt2[100], Myt3[100], Myt4[100];

// For Wings
BOOL WingAnimate;
float WingYUpdate;
float PushpakVimanMove;
float PushpakVimanUp;
float Wxt1[100], Wxt2[100];
float Wyt1[100], Wyt2[100];

// For Leaves
float Pxt1[100], Pxt2[100], Pxt3[100], Pxt4[100];
float Pyt1[100], Pyt2[100], Pyt3[100], Pyt4[100];

// For Jewwllery
float NecklaceMoveX, NecklaceMoveY, dt;
float BanglesMoveX, BanglesMoveY, dt2;
float Jxt[100], Jyt[100];

float i, x, y;
float radian;
static BOOL StartAnimation = TRUE;

//////////////////////////////////////////////////////////////////////////////////////////////////

extern HWND AAA_ghwnd;

/////////////////////////////////// Actual Objects Related Functions ///////////////////////////////////


// Blue Sky Quad as Background
void Sky(float x_pos, float y_pos, float percentX, float percentY)
{
	glBegin(GL_QUADS);
	{
		glColor4f( 185.0f/256.0f, 220.0f/256.0f, 247.0f/256.0f, 1.0f);
		glVertex3f( VALUE_FROM_PERCENT( -1.0f, percentX) + x_pos, VALUE_FROM_PERCENT( 1.0f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( 1.0f, percentX) + x_pos, VALUE_FROM_PERCENT( 1.0f, percentY) + y_pos, 0.0f);

		glColor4f( 228.0f/256.0f, 238.0f/256.0f, 247.0f/256.0f, 1.0f);
		glVertex3f( VALUE_FROM_PERCENT( 1.0f, percentX) + x_pos, VALUE_FROM_PERCENT( -0.5f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -1.0f, percentX) + x_pos, VALUE_FROM_PERCENT( -0.5f, percentY) + y_pos, 0.0f);
	}
	glEnd();
}

// Land on which Trees, fence etc are situated
void Land(float x_pos, float y_pos, float percentX, float percentY)
{
	glBegin(GL_QUADS);
	{
		glColor3f(0.564706, 0.780392, 0.235294);
		glVertex2f(VALUE_FROM_PERCENT(-1.0f, percentX) + x_pos, VALUE_FROM_PERCENT(0.2f, percentY) + y_pos);	
		glVertex2f(VALUE_FROM_PERCENT(1.0f, percentX) + x_pos, VALUE_FROM_PERCENT(0.2f, percentY) + y_pos);

		glColor3f(189.0f / 255.0f, 148.0f / 255.0f, 80.0f / 255.0f);
		glVertex2f(VALUE_FROM_PERCENT(1.0f, percentX) + x_pos, VALUE_FROM_PERCENT(-0.1f, percentY) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-1.0f, percentX) + x_pos, VALUE_FROM_PERCENT(-0.1f, percentY) + y_pos);
	}
	glEnd();
}

// Blue, Dark Green & Light Green Mountains
void Mountains(float x_pos, float y_pos, float percentX, float percentY)
{
	// Variable declarations
	struct Curve curve1;
	struct Curve curve2;
	struct Curve curve3;
	GLfloat t = 0.0f;
	int i = 0;

	// code
	// Blue Mountains
	glBegin(GL_POLYGON);
	{
		glColor4f( 0.0f/256.0f, 104.0f/256.0f, 123.0f/256.0f, 1.0f);
		glVertex3f( VALUE_FROM_PERCENT( -1.0f, percentX) + x_pos, VALUE_FROM_PERCENT( -0.1f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -1.0f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.25f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.92f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.18f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.7f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.38f, percentY) + y_pos, 0.0f);
		glColor4f(2.0f/256.0f, 148.0f/256.0f, 169.0f/256.0f, 1.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.35f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.22f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.35f, percentX) + x_pos, VALUE_FROM_PERCENT( -0.1f, percentY) + y_pos, 0.0f);
	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		glColor4f( 0.0f/256.0f, 104.0f/256.0f, 123.0f/256.0f, 1.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.65f, percentX) + x_pos, VALUE_FROM_PERCENT( -0.1f , percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.1f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.5f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( 0.1f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.4f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( 0.27f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.56f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( 0.3f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.54f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( 0.37f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.6f, percentY) + y_pos, 0.0f);
		glColor4f(2.0f/256.0f, 148.0f/256.0f, 169.0f/256.0f, 1.0f);
		glVertex3f( VALUE_FROM_PERCENT( 0.6f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.35f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( 0.63f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.38f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( 0.7f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.33f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( 0.78f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.37f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( 1.0f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.28f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( 1.0f, percentX) + x_pos, VALUE_FROM_PERCENT( -0.1f, percentY) + y_pos, 0.0f);
	}
	glEnd();

	// Dark Green Mountains
	curve1.x1 = -1.0f;
	curve1.x2 = -0.6f;
	curve1.x3 = -0.15f;
	curve1.x4 = 0.0f;
	curve1.y1 = 0.05f;
	curve1.y2 = 0.17f;
	curve1.y3 = -0.05f;
	curve1.y4 = -0.05f;

	for(t = 0.0f, i = 0; t < 1.0f; t = t + 0.01f, i++)
	{
		Mxt1[i] = ((pow(1-t, 3) * curve1.x1) + ((3 * t) * pow(1-t, 2) * curve1.x2) + ((3 * pow(t, 2)) * (1 - t) * curve1.x3) + (pow(t, 3) * curve1.x4));
		Myt1[i] = ((pow(1-t, 3) * curve1.y1) + ((3 * t) * pow(1-t, 2) * curve1.y2) + ((3 * pow(t, 2)) * (1 - t) * curve1.y3) + (pow(t, 3) * curve1.y4));
	}	

	for(t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
	{
		Mxt2[i] = ((-1.0f) + ((float)i/100));
		Myt2[i] = -0.2f;
	}

	
	glColor4f( 96.0f/256.0f, 139.0f/256.0f, 74.0f/256.0f, 1.0f);
	glBegin(GL_TRIANGLE_STRIP);
	{
		for ( i = 0; i < 100; i++)
		{
			glVertex3f( VALUE_FROM_PERCENT( Mxt2[i], percentX) + x_pos, VALUE_FROM_PERCENT( Myt2[i], percentY) + y_pos, 0.0f);
			glVertex3f( VALUE_FROM_PERCENT( Mxt1[i], percentX) + x_pos, VALUE_FROM_PERCENT( Myt1[i] , percentY) + y_pos, 0.0f);
		}	
	}
	glEnd();
	
	// Light Green Mountain
	curve2.x1 = -1.0f;
	curve2.x2 = -0.3f;
	curve2.x3 = 0.5f;
	curve2.x4 = 1.1f;
	curve2.y1 = -0.1f;
	curve2.y2 = -0.09f;
	curve2.y3 = 0.15f;
	curve2.y4 = 0.0f;

	for(t = 0.0f, i = 0; t < 1.0f; t = t + 0.01f, i++)
	{
		Mxt3[i] = ((pow(1-t, 3) * curve2.x1) + ((3 * t) * pow(1-t, 2) * curve2.x2) + ((3 * pow(t, 2)) * (1 - t) * curve2.x3) + (pow(t, 3) * curve2.x4));
		Myt3[i] = ((pow(1-t, 3) * curve2.y1) + ((3 * t) * pow(1-t, 2) * curve2.y2) + ((3 * pow(t, 2)) * (1 - t) * curve2.y3) + (pow(t, 3) * curve2.y4));
	}

	for(t = 0.0f, i = 0; t < 1.0f; t = t + 0.01f, i++)
	{
		Mxt4[i] = ((-1.0f) + (2.1f *((float)i/100)));
		Myt4[i] = -0.2f;
	}

	glColor4f( 155.0f/256.0f, 185.0f/256.0f, 59.0f/256.0f, 1.0f);
	glBegin(GL_TRIANGLE_STRIP);
	{
		for ( i = 0; i < 100; i++)
		{
			glVertex3f( VALUE_FROM_PERCENT( Mxt4[i], percentX) + x_pos, VALUE_FROM_PERCENT( Myt4[i], percentY) + y_pos, 0.0f);
			glVertex3f( VALUE_FROM_PERCENT( Mxt3[i], percentX) + x_pos, VALUE_FROM_PERCENT( Myt3[i] , percentY) + y_pos, 0.0f);
		}	
	}
	glEnd();
}

// Complete Tree
void Tree(float x_pos, float y_pos, float percentX, float percentY)
{
	// code

	Treeleaves(-0.5f + x_pos, 0.47f + y_pos, -3.0f + percentX, 0.0f + percentY, 12.0f, 55.0f, 31.0f);
	Treeleaves(-0.55f + x_pos, 0.8f + y_pos, -3.0f + percentX, 0.0f + percentY, 12.0f, 55.0f, 31.0f);
	Treeleaves(-0.79f + x_pos, 0.7f + y_pos, 7.0f + percentX, 0.0f + percentY, 12.0f, 55.0f, 31.0f);
	Treeleaves(-0.4f + x_pos, 0.53f + y_pos, 13.0f + percentX, 0.0f + percentY, 12.0f, 55.0f, 31.0f);
	Treeleaves(-0.75f + x_pos, 0.5f + y_pos, 7.0f + percentX, 0.0f + percentY, 12.0f, 55.0f, 31.0f);

	Treeleaves(-0.6f + x_pos, 0.75f + y_pos, -3.0f + percentX, 0.0f + percentY, 26.0f, 99.0f, 55.0f);
	Treeleaves(-0.44f + x_pos, 0.6f + y_pos, 4.0f + percentX, 0.0f + percentY, 26.0f, 99.0f, 55.0f);
	Treeleaves(-0.63f + x_pos, 0.62f + y_pos, 0.0f + percentX, 0.0f + percentY, 26.0f, 99.0f, 55.0f);

	TreeStem(-0.25f + x_pos, 0.35f + y_pos, 45.0f + percentX, 120.0f + percentY);

	Treeleaves(-0.44f + x_pos, 0.57f + y_pos, -3.0f + percentX, 0.0f + percentY, 78.0f, 150.0f, 43.0f);
	Treeleaves(-0.66f + x_pos, 0.61f + y_pos, 6.0f + percentX, 0.0f + percentY, 78.0f, 150.0f, 43.0f);
	Treeleaves(-0.6f + x_pos, 0.51f + y_pos, -1.0f + percentX, 0.0f + percentY, 78.0f, 150.0f, 43.0f);
	Treeleaves(-0.75f + x_pos, 0.6f + y_pos, -1.0f + percentX, 0.0f + percentY, 78.0f, 150.0f, 43.0f);

}

// Blocks of Leaves of tree
void Treeleaves(float x_pos, float y_pos, float percentX, float percentY, float red, float green, float blue)
{
	// code
	Circle(0.0f + x_pos, 0.0f + y_pos,  20.0f + percentX, 0.0f + percentY, 0.2f, red, green, blue);
	Circle(0.08f + x_pos, 0.07f + y_pos,  20.0f + percentX, 0.0f + percentY, 0.2f, red, green, blue);
	Circle(0.12f + x_pos, 0.09f + y_pos,  20.0f + percentX, 0.0f + percentY, 0.2f, red, green, blue);
	Circle(0.05f + x_pos, 0.02f + y_pos,  20.0f + percentX, 0.0f + percentY, 0.2f, red, green, blue);
	Circle(0.13f + x_pos, 0.0f + y_pos,  40.0f + percentX, 0.0f + percentY, 0.2f, red, green, blue); 
	Circle(0.18f + x_pos, 0.07f + y_pos,  20.0f + percentX, 0.0f + percentY, 0.2f, red, green, blue);
	Circle(0.19f + x_pos, 0.0f + y_pos,  20.0f + percentX, 0.0f + percentY, 0.2f, red, green, blue);
	Circle(0.18f + x_pos, -0.07f + y_pos,  20.0f + percentX, 0.0f + percentY, 0.2f, red, green, blue);
	Circle(0.04f + x_pos, -0.06f + y_pos,  20.0f + percentX, 0.0f + percentY, 0.2f, red, green, blue);
	Circle(0.11f + x_pos, -0.06f + y_pos,  20.0f + percentX, 0.0f + percentY, 0.2f, red, green, blue);


}

// Small blocks for creating 1 big block of tree leaves 
void Circle(float x_pos, float y_pos, float percentX, float percentY, float radius, float red, float green, float blue)
{	
	glPointSize(63.0f);
	glBegin(GL_POINTS);
	glColor4f( red/ 256.0f, green/ 256.0f, blue / 256.0f, 1.0f);
	{
		glVertex3f(VALUE_FROM_PERCENT( x, percentX) + x_pos, VALUE_FROM_PERCENT( y, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( x + 0.05f, percentX) + x_pos, VALUE_FROM_PERCENT( y, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( x - 0.05f, percentX) + x_pos, VALUE_FROM_PERCENT( y, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( x, percentX) + x_pos, VALUE_FROM_PERCENT( y + 0.05f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( x, percentX) + x_pos, VALUE_FROM_PERCENT( y - 0.05f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( x + 0.1f, percentX) + x_pos, VALUE_FROM_PERCENT( y, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( x - 0.1f, percentX) + x_pos, VALUE_FROM_PERCENT( y, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( x, percentX) + x_pos, VALUE_FROM_PERCENT( y + 0.1f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( x, percentX) + x_pos, VALUE_FROM_PERCENT( y - 0.1f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( x + 0.1f, percentX) + x_pos, VALUE_FROM_PERCENT( y + 0.1f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( x - 0.1f, percentX) + x_pos, VALUE_FROM_PERCENT( y - 0.1f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( x - 0.1f, percentX) + x_pos, VALUE_FROM_PERCENT( y + 0.1f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( x + 0.1f, percentX) + x_pos, VALUE_FROM_PERCENT( y - 0.1f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( x + 0.15f, percentX) + x_pos, VALUE_FROM_PERCENT( y, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( x - 0.15f, percentX) + x_pos, VALUE_FROM_PERCENT( y, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( x, percentX) + x_pos, VALUE_FROM_PERCENT( y + 0.15f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( x, percentX) + x_pos, VALUE_FROM_PERCENT( y - 0.15f, percentY) + y_pos, 0.0f);
	}
	glEnd();
}

// Stem of tree
void TreeStem(float x_pos, float y_pos, float percentX, float percentY)
{
	// variable declaration
	struct Curve curve1;
	struct Curve curve2;
	struct Curve curve3;
	struct Curve curve4;

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
		Txt3[i] = ((pow(1-t, 3) * curve3.x1) + ((3 * t) * pow(1-t, 2) * curve3.x2) + ((3 * pow(t, 2)) * (1 - t) * curve3.x3) + (pow(t, 3) * curve3.x4));
		Tyt3[i] = ((pow(1-t, 3) * curve3.y1) + ((3 * t) * pow(1-t, 2) * curve3.y2) + ((3 * pow(t, 2)) * (1 - t) * curve3.y3) + (pow(t, 3) * curve3.y4));
	}	
	

	for(t = 0.0f, i = 0; t < 1.0f; t = t + 0.01f, i++)
	{
		Txt4[i] = ((pow(1-t, 3) * curve4.x1) + ((3 * t) * pow(1-t, 2) * curve4.x2) + ((3 * pow(t, 2)) * (1 - t) * curve4.x3) + (pow(t, 3) * curve4.x4));
		Tyt4[i] = ((pow(1-t, 3) * curve4.y1) + ((3 * t) * pow(1-t, 2) * curve4.y2) + ((3 * pow(t, 2)) * (1 - t) * curve4.y3) + (pow(t, 3) * curve4.y4));
	}

	glBegin(GL_TRIANGLE_STRIP);
	{
		glColor4f(82.0f/256.0f, 31.0f/256.0f, 19.0f/256.0f, 1.0f);
		for(i = 0; i < 100; i++)
		{
			glVertex3f(VALUE_FROM_PERCENT( Txt3[i], percentX) + x_pos, VALUE_FROM_PERCENT( Tyt3[i], percentY)+ y_pos, 0.0f);
			glVertex3f(VALUE_FROM_PERCENT( Txt4[i], percentX) + x_pos, VALUE_FROM_PERCENT( Tyt4[i], percentY)+ y_pos, 0.0f);
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
		Txt1[i] = ((pow(1-t, 3) * curve1.x1) + ((3 * t) * pow(1-t, 2) * curve1.x2) + ((3 * pow(t, 2)) * (1 - t) * curve1.x3) + (pow(t, 3) * curve1.x4));
		Tyt1[i] = ((pow(1-t, 3) * curve1.y1) + ((3 * t) * pow(1-t, 2) * curve1.y2) + ((3 * pow(t, 2)) * (1 - t) * curve1.y3) + (pow(t, 3) * curve1.y4));
	}	
	
	for(t = 0.0f, i = 0; t < 1.0f; t = t + 0.01f, i++)
	{
		Txt2[i] = ((pow(1-t, 3) * curve2.x1) + ((3 * t) * pow(1-t, 2) * curve2.x2) + ((3 * pow(t, 2)) * (1 - t) * curve2.x3) + (pow(t, 3) * curve2.x4));
		Tyt2[i] = ((pow(1-t, 3) * curve2.y1) + ((3 * t) * pow(1-t, 2) * curve2.y2) + ((3 * pow(t, 2)) * (1 - t) * curve2.y3) + (pow(t, 3) * curve2.y4));
	}

	glBegin(GL_TRIANGLE_STRIP);
	{
		for(i = 0; i < 100; i++)
		{
			glColor4f(217.0f/256.0f, 126.0f/256.0f, 57.0f/256.0f, 1.0f);
			glVertex3f(VALUE_FROM_PERCENT( Txt1[i], percentX) + x_pos, VALUE_FROM_PERCENT( Tyt1[i], percentY)+ y_pos, 0.0f);
			glColor4f(82.0f/256.0f, 31.0f/256.0f, 19.0f/256.0f, 1.0f);
			glVertex3f(VALUE_FROM_PERCENT( Txt2[i], percentX) + x_pos, VALUE_FROM_PERCENT( Tyt2[i], percentY)+ y_pos, 0.0f);
		}
	}
	glEnd();

}

// Fence for kutiya
void Fence(float x_pos, float y_pos, float percentX, float percentY)
{
	// code
	// Horizontal Start
	glBegin(GL_QUADS);
	{
		glColor4f( 159.0f/256.0f, 107.0f/256.0f, 27.0f/256.0f, 1.0f);
		glVertex3f( VALUE_FROM_PERCENT( -1.0f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.2f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.2f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.2f, percentY) + y_pos, 0.0f);
		glColor4f(46.0f/256.0f, 28.0f/256.0f, 8.0f/256.0f, 1.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.2f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.1f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -1.0f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.1f, percentY) + y_pos, 0.0f);
	}
	glEnd();

	// Vertical Left
	glBegin(GL_QUADS);
	{
		glColor4f( 159.0f/256.0f, 107.0f/256.0f, 27.0f/256.0f, 1.0f);
		glVertex3f( VALUE_FROM_PERCENT( -1.0f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.1f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -1.0f, percentX) + x_pos, VALUE_FROM_PERCENT( -0.35f, percentY) + y_pos, 0.0f);
		glColor4f(46.0f/256.0f, 28.0f/256.0f, 8.0f/256.0f, 1.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.95f, percentX) + x_pos, VALUE_FROM_PERCENT( -0.35f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.95f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.1f, percentY) + y_pos, 0.0f);
	}
	glEnd();

	// Tilted Backward left
	glBegin(GL_QUADS);
	{
		glColor4f( 159.0f/256.0f, 107.0f/256.0f, 27.0f/256.0f, 1.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.95f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.1f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.7f, percentX) + x_pos, VALUE_FROM_PERCENT( -0.35f, percentY) + y_pos, 0.0f);
		glColor4f(46.0f/256.0f, 28.0f/256.0f, 8.0f/256.0f, 1.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.65f, percentX) + x_pos, VALUE_FROM_PERCENT( -0.35f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.9f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.1f, percentY) + y_pos, 0.0f);
	}
	glEnd();

	// Tilted Forward left
	glBegin(GL_QUADS);
	{
		glColor4f( 159.0f/256.0f, 107.0f/256.0f, 27.0f/256.0f, 1.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.7f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.1f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.9f, percentX) + x_pos, VALUE_FROM_PERCENT( -0.35f, percentY) + y_pos, 0.0f);
		glColor4f(46.0f/256.0f, 28.0f/256.0f, 8.0f/256.0f, 1.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.85f, percentX) + x_pos, VALUE_FROM_PERCENT( -0.35f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.65f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.1f, percentY) + y_pos, 0.0f);
	}
	glEnd();

	// Fence Binding Left
	glLineWidth(5.0f);
	glBegin(GL_LINES);
	{
		glColor4f(0.0f, 0.0f, 0.0f, 1.0f);

		glVertex3f( VALUE_FROM_PERCENT( -0.79f, percentX) + x_pos, VALUE_FROM_PERCENT( -0.09f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT(-0.79f, percentX) + x_pos, VALUE_FROM_PERCENT( -0.22f, percentY) + y_pos, 0.0f);

		glVertex3f( VALUE_FROM_PERCENT( -0.82f, percentX) + x_pos, VALUE_FROM_PERCENT( -0.15f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.75, percentX) + x_pos, VALUE_FROM_PERCENT( -0.15f, percentY) + y_pos, 0.0f);
	}
	glEnd();

	// Vertical Middle
	glBegin(GL_QUADS);
	{
		glColor4f( 159.0f/256.0f, 107.0f/256.0f, 27.0f/256.0f, 1.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.65f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.1f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.65f, percentX) + x_pos, VALUE_FROM_PERCENT( -0.35f, percentY) + y_pos, 0.0f);
		glColor4f(46.0f/256.0f, 28.0f/256.0f, 8.0f/256.0f, 1.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.6f, percentX) + x_pos, VALUE_FROM_PERCENT( -0.35f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.6f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.1f, percentY) + y_pos, 0.0f);
	}
	glEnd();

	// Tilted Backward Right
	glBegin(GL_QUADS);
	{
		glColor4f( 159.0f/256.0f, 107.0f/256.0f, 27.0f/256.0f, 1.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.6f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.1f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.35f, percentX) + x_pos, VALUE_FROM_PERCENT( -0.35f, percentY) + y_pos, 0.0f);
		glColor4f(46.0f/256.0f, 28.0f/256.0f, 8.0f/256.0f, 1.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.3f, percentX) + x_pos, VALUE_FROM_PERCENT( -0.35f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.55f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.1f, percentY) + y_pos, 0.0f);
	}
	glEnd();
	
	// Tilted Forward Right
	glBegin(GL_QUADS);
	{
		glColor4f( 159.0f/256.0f, 107.0f/256.0f, 27.0f/256.0f, 1.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.35f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.1f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.6f, percentX) + x_pos, VALUE_FROM_PERCENT( -0.35f, percentY) + y_pos, 0.0f);
		glColor4f(46.0f/256.0f, 28.0f/256.0f, 8.0f/256.0f, 1.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.55f, percentX) + x_pos, VALUE_FROM_PERCENT( -0.35f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.3f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.1f, percentY) + y_pos, 0.0f);
	}
	glEnd();

	// Fence Binding Right
	glBegin(GL_LINES);
	{
		glColor4f(0.0f, 0.0f, 0.0f, 1.0f);

		glVertex3f( VALUE_FROM_PERCENT( -0.45f, percentX) + x_pos, VALUE_FROM_PERCENT( -0.08f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT(-0.45f, percentX) + x_pos, VALUE_FROM_PERCENT( -0.19f, percentY) + y_pos, 0.0f);

		glVertex3f( VALUE_FROM_PERCENT( -0.48f, percentX) + x_pos, VALUE_FROM_PERCENT( -0.13f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.42, percentX) + x_pos, VALUE_FROM_PERCENT( -0.13f, percentY) + y_pos, 0.0f);
	}
	glEnd();
	glLineWidth(1.0f);

	// Vertical End
	glBegin(GL_QUADS);
	{
		glColor4f( 159.0f/256.0f, 107.0f/256.0f, 27.0f/256.0f, 1.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.3f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.1f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.3f, percentX) + x_pos, VALUE_FROM_PERCENT( -0.35f, percentY) + y_pos, 0.0f);
		glColor4f(46.0f/256.0f, 28.0f/256.0f, 8.0f/256.0f, 1.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.25f, percentX) + x_pos, VALUE_FROM_PERCENT( -0.35f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.25f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.1f, percentY) + y_pos, 0.0f);
	}
	glEnd();

	// Horizontal End
	glBegin(GL_QUADS);
	{
		glColor4f( 159.0f/256.0f, 107.0f/256.0f, 27.0f/256.0f, 1.0f);
		glVertex3f( VALUE_FROM_PERCENT( -1.0f, percentX) + x_pos, VALUE_FROM_PERCENT( -0.35f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.2f, percentX) + x_pos, VALUE_FROM_PERCENT( -0.35f, percentY) + y_pos, 0.0f);
		glColor4f(46.0f/256.0f, 28.0f/256.0f, 8.0f/256.0f, 1.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.2f, percentX) + x_pos, VALUE_FROM_PERCENT( -0.4f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -1.0f, percentX) + x_pos, VALUE_FROM_PERCENT( -0.4f, percentY) + y_pos, 0.0f);
	}
	glEnd();
}

// Complete Pushpak Viman
void PushpakViman(float x_pos, float y_pos, float percentX, float percentY)
{
	// Wings
	WingsForViman(-0.3f + x_pos , -0.5f + y_pos, 150.0f + percentX, 150.0f + percentY, 150.0f + WingYUpdate);
	WingsForViman(0.3f + x_pos , -0.5f + y_pos, -350.0f + percentX, 150.0f + percentY, 150.0f + WingYUpdate);

	// Kalash
	KalashForViman(x_pos, y_pos + 0.50f, 10.0f, percentY);

	// Steps
	RoofForViman(x_pos, y_pos, percentX, percentY - 28.0f);
	RoofForViman(x_pos, y_pos + 0.15f, percentX - 20.0f, percentY - 28.0f);
	RoofForViman(x_pos, y_pos + 0.3f, percentX - 40.0f, percentY - 28.0f);
	RoofForViman(x_pos, y_pos + 0.45f, percentX - 60.0f, percentY - 28.0f);

	// Back Support
	glBegin(GL_QUADS);
	{
		glColor4f( 190.0/256.0f, 110.0/256.0f, 30.0/256.0f, 1.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.4f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.22f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.4f, percentX) + x_pos, VALUE_FROM_PERCENT( -0.3f, percentY) + y_pos, 0.0f);
		glColor4f( 235.0/256.0f, 198.0/256.0f, 94.0/256.0f, 1.0f);
		glVertex3f( VALUE_FROM_PERCENT( 0.0f, percentX) + x_pos, VALUE_FROM_PERCENT( -0.3f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( 0.0f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.22f, percentY) + y_pos, 0.0f);

		glVertex3f( VALUE_FROM_PERCENT( 0.0f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.22f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( 0.0f, percentX) + x_pos, VALUE_FROM_PERCENT( -0.3f, percentY) + y_pos, 0.0f);
		glColor4f( 190.0/256.0f, 110.0/256.0f, 30.0/256.0f, 1.0f);
		glVertex3f( VALUE_FROM_PERCENT( 0.4f, percentX) + x_pos, VALUE_FROM_PERCENT( -0.3f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( 0.4f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.22f, percentY) + y_pos, 0.0f);
	}
	glEnd();

	// Base Support
	BaseForViman(x_pos, y_pos + (-0.81f), percentX, percentY);

	// Wheels for Pushpak Viman
	// Left Wheel
	glBegin(GL_QUADS);
	{
		glColor3f(58.0/256.0f, 36.0/256.0f, 27.0/256.0f);
		glVertex3f( (x_pos - 0.55f) , (y_pos - 0.65f), 0.0f);
		glVertex3f( (x_pos - 0.55f), (y_pos - 0.65f) + 0.4f, 0.0f);
		glVertex3f( (x_pos - 0.55f) + 0.1f, (y_pos - 0.65f) + 0.4f, 0.0f);
		glVertex3f( (x_pos - 0.55f) + 0.1f, (y_pos - 0.65f), 0.0f);
	}
	glEnd();

	float radius = 0.05f;
	glBegin(GL_LINES);
	{
		glColor3f(58.0/256.0f, 36.0/256.0f, 27.0/256.0f);
		for(float i = 0; i < 180.0f; i = i + 0.1f)
		{
			float angle = i * (M_PI / 180.0f);
			float x = (radius) * cos(angle);
			float y = (radius) * sin(angle);

			glVertex3f((x_pos + 0.0f - 0.5f), (y_pos + 0.0f - 0.25f), 0.0f);
			glVertex3f((x_pos + x - 0.5f), (y_pos + y - 0.25f), 0.0f);
		}
	}
	glEnd();

	radius = 0.05f;
	glBegin(GL_LINES);
	{
		glColor3f(58.0/256.0f, 36.0/256.0f, 27.0/256.0f);
		for(float i = 180; i < 360.0f; i = i + 0.1f)
		{
			float angle = i * (M_PI / 180.0f);
			float x = (radius) * cos(angle);
			float y = (radius) * sin(angle);

			glVertex3f((x_pos + 0.0f - 0.5f), (y_pos + 0.0f - 0.65f), 0.0f);
			glVertex3f((x_pos + x - 0.5f), (y_pos + y - 0.65f), 0.0f);
		}
	}
	glEnd();

	// Right Wheel
	glBegin(GL_QUADS);
	{
		glColor3f(58.0/256.0f, 36.0/256.0f, 27.0/256.0f);
		glVertex3f( (x_pos + 0.45f) , (y_pos - 0.65f), 0.0f);
		glVertex3f( (x_pos + 0.45f), (y_pos - 0.65f) + 0.4f, 0.0f);
		glVertex3f( (x_pos + 0.45f) + 0.1f, (y_pos - 0.65f) + 0.4f, 0.0f);
		glVertex3f( (x_pos + 0.45f) + 0.1f, (y_pos - 0.65f), 0.0f);
	}
	glEnd();

	radius = 0.05f;
	glBegin(GL_LINES);
	{
		glColor3f(58.0/256.0f, 36.0/256.0f, 27.0/256.0f);
		for(float i = 0; i < 180.0f; i = i + 0.1f)
		{
			float angle = i * (M_PI / 180.0f);
			float x = (radius) * cos(angle);
			float y = (radius) * sin(angle);

			glVertex3f((x_pos + 0.0f + 0.5f), (y_pos + 0.0f - 0.25f), 0.0f);
			glVertex3f((x_pos + x + 0.5f), (y_pos + y - 0.25f), 0.0f);
		}
	}
	glEnd();

	radius = 0.05f;
	glBegin(GL_LINES);
	{
		glColor3f(58.0/256.0f, 36.0/256.0f, 27.0/256.0f);
		for(float i = 180; i < 360.0f; i = i + 0.1f)
		{
			float angle = i * (M_PI / 180.0f);
			float x = (radius) * cos(angle);
			float y = (radius) * sin(angle);

			glVertex3f((x_pos + 0.0f + 0.5f), (y_pos + 0.0f - 0.65f), 0.0f);
			glVertex3f((x_pos + x + 0.5f), (y_pos + y - 0.65f), 0.0f);
		}
	}
	glEnd();

}

// Roof part of Pushpak Viman
void RoofForViman(float x_pos, float y_pos, float percentX, float percentY)
{
	// code
	glBegin(GL_QUADS);
	{
		glColor4f( 235.0/256.0f, 198.0/256.0f, 94.0/256.0f, 1.0f);
		glVertex3f(VALUE_FROM_PERCENT( -0.4f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.5f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( -0.45f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.45f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( 0.45f, percentX) + x_pos, VALUE_FROM_PERCENT(  0.45f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( 0.4f, percentX) + x_pos, VALUE_FROM_PERCENT(  0.5f, percentY) + y_pos, 0.0f);
	}
	glEnd();

	glBegin(GL_QUADS);
	{
		glColor4f( 230.0/256.0f, 163.0/256.0f, 66.0/256.0f, 1.0f);
		glVertex3f(VALUE_FROM_PERCENT( -0.45f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.45f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( -0.45f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.35f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( 0.45f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.35f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( 0.45f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.45f, percentY) + y_pos, 0.0f);
	}
	glEnd();

	glBegin(GL_QUADS);
	{
		glColor4f( 190.0/256.0f, 110.0/256.0f, 30.0/256.0f, 1.0f);
		glVertex3f(VALUE_FROM_PERCENT( -0.45f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.35f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( -0.4f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.3f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( 0.4f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.3f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( 0.45f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.35f, percentY) + y_pos, 0.0f);
	}
	glEnd();

}

// Kalash part for Pushpak viman
void KalashForViman(float x_pos, float y_pos, float percentX, float percentY)
{
	// code
	glBegin(GL_TRIANGLES);
	{
		glColor4f( 235.0/256.0f, 198.0/256.0f, 94.0/256.0f, 1.0f);
		glVertex3f(VALUE_FROM_PERCENT( 0.0f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.5f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( -0.45f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.40f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( 0.45f, percentX) + x_pos, VALUE_FROM_PERCENT(  0.40f, percentY) + y_pos, 0.0f);
	}
	glEnd();

	glBegin(GL_QUADS);
	{
		glColor4f( 230.0/256.0f, 163.0/256.0f, 66.0/256.0f, 1.0f);
		glVertex3f(VALUE_FROM_PERCENT( -0.45f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.40f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( -0.45f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.35f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( 0.45f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.35f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( 0.45f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.40f, percentY) + y_pos, 0.0f);
	}
	glEnd();

	glBegin(GL_QUADS);
	{
		glColor4f( 190.0/256.0f, 110.0/256.0f, 30.0/256.0f, 1.0f);
		glVertex3f(VALUE_FROM_PERCENT( -0.45f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.35f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( -0.4f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.3f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( 0.4f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.3f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( 0.45f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.35f, percentY) + y_pos, 0.0f);
	}
	glEnd();
}

// Wing part for Pushpak Viman
void WingsForViman(float x_pos, float y_pos, float percentX, float percentY, float WingYUpdate)
{
	// Variable declarations
	struct Curve curve1;
	struct Curve curve2;
	GLfloat t = 0.0f;
	int i = 0;

	// code
	curve1.x1 = 0.1f;
	curve1.x2 = -0.05f;
	curve1.x3 = -0.55f;
	curve1.x4 = -0.93f;
	curve1.y1 = 0.18f;
	curve1.y2 = 0.2f;
	curve1.y3 = 0.35f;
	curve1.y4 = 0.33f;

	curve2.x1 = 0.09f;
	curve2.x2 = -0.28f;
	curve2.x3 = -0.57f;
	curve2.x4 = -0.93f;
	curve2.y1 = 0.05f;
	curve2.y2 = 0.08f;
	curve2.y3 = 0.13f;
	curve2.y4 = 0.33f;

	for(t = 0.0f, i = 0; t < 1.0f; t = t + 0.01f, i++)
	{
		Wxt1[i] = ((pow(1-t, 3) * curve1.x1) + ((3 * t) * pow(1-t, 2) * curve1.x2) + ((3 * pow(t, 2)) * (1 - t) * curve1.x3) + (pow(t, 3) * curve1.x4));
		Wyt1[i] = ((pow(1-t, 3) * curve1.y1) + ((3 * t) * pow(1-t, 2) * curve1.y2) + ((3 * pow(t, 2)) * (1 - t) * curve1.y3) + (pow(t, 3) * curve1.y4));
	}	

	for(t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
	{
		Wxt2[i] = ((pow(1-t, 3) * curve2.x1) + ((3 * t) * pow(1-t, 2) * curve2.x2) + ((3 * pow(t, 2)) * (1 - t) * curve2.x3) + (pow(t, 3) * curve2.x4));
		Wyt2[i] = ((pow(1-t, 3) * curve2.y1) + ((3 * t) * pow(1-t, 2) * curve2.y2) + ((3 * pow(t, 2)) * (1 - t) * curve2.y3) + (pow(t, 3) * curve2.y4));
	}

	glBegin(GL_TRIANGLE_STRIP);
	{
		for ( i = 0; i < 100; i++)
		{
			glColor4f( 218.0/256.0f, 218.0/256.0f, 218.0/256.0f, 1.0f);
			if(i == 0)
			{
				glVertex3f( VALUE_FROM_PERCENT( Wxt2[i], percentX) + x_pos, VALUE_FROM_PERCENT( Wyt2[i], percentY) + y_pos, 0.0f);

			}
			glVertex3f( VALUE_FROM_PERCENT( Wxt2[i], percentX) + x_pos, VALUE_FROM_PERCENT( Wyt2[i], WingYUpdate) + y_pos, 0.0f);
			
			glColor4f( 91.0/256.0f, 76.0/256.0f, 63.0/256.0f, 1.0f);
			if( i == 0)
			{
				glVertex3f( VALUE_FROM_PERCENT( Wxt1[i], percentX) + x_pos, VALUE_FROM_PERCENT( Wyt1[i] , percentY) + y_pos, 0.0f);
			}
			glVertex3f( VALUE_FROM_PERCENT( Wxt1[i], percentX) + x_pos, VALUE_FROM_PERCENT( Wyt1[i] , WingYUpdate) + y_pos, 0.0f);
		}	
	}
	glEnd();

}

// Base(Support) for Pushpak Viman
void BaseForViman(float x_pos, float y_pos, float percentX, float percentY)
{
	// code
	glBegin(GL_QUADS);
	{
		glColor4f( 235.0/256.0f, 198.0/256.0f, 94.0/256.0f, 1.0f);
		glVertex3f(VALUE_FROM_PERCENT( -0.4f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.5f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( -0.45f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.45f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( 0.45f, percentX) + x_pos, VALUE_FROM_PERCENT(  0.45f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( 0.4f, percentX) + x_pos, VALUE_FROM_PERCENT(  0.5f, percentY) + y_pos, 0.0f);
	}
	glEnd();

	glBegin(GL_QUADS);
	{
		glColor4f( 230.0/256.0f, 163.0/256.0f, 66.0/256.0f, 1.0f);
		glVertex3f(VALUE_FROM_PERCENT( -0.45f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.45f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( -0.45f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.25f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( 0.45f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.25f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( 0.45f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.45f, percentY) + y_pos, 0.0f);
	}
	glEnd();
}

// Necklace (Jewellary)
void Necklace(float x_pos, float y_pos, float percentX, float percentY)
{
	// code
	glPointSize(5.0f);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_POINTS);
	{
		glVertex3f( VALUE_FROM_PERCENT( -0.08f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.38f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.05f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.36f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.04, percentX) + x_pos, VALUE_FROM_PERCENT( 0.32f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.01f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.28f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( 0.03f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.26f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( 0.05f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.23f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( 0.04f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.18f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( 0.02f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.17f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.02f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.185f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.05f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.2f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.07f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.22f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.1f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.24f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.12f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.27f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.14f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.32f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.11f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.35f, percentY) + y_pos, 0.0f);
	}
	glEnd();
}

// Bangle (Jewellary)
void Bangles(float x_pos, float y_pos, float percentX, float percentY)
{
	float x, y = 0.0f;
	float radius = 0.2f;
	float angle = 0.0f;

	glColor4f(224.0f/256.0f, 179.0f/256.0f, 4.0f/256.0f, 1.0f);
	glLineWidth(3.0f);
	glBegin(GL_LINE_LOOP);
	{
		for (float i = 0.0f; i < 360.0f; i = i + 0.01f)
		{
			angle = i * (M_PI / 180.0f);
			x = radius * cos(angle);
			y = (radius * (5.0f / 9.0f)) * sin(angle);

			glVertex3f( VALUE_FROM_PERCENT( x, percentX) + x_pos, VALUE_FROM_PERCENT( y, percentY) + y_pos, 0.0f);
		}
	}
	glEnd();
}


/////////////////////////////////// Animation Related Functions ///////////////////////////////////

// Animation Function For Pushpak Viman Movement
void update(void)
{
	// For Viman
	if(WingAnimate)
	{
		WingYUpdate = WingYUpdate - 0.5f;
		if(WingYUpdate <= 20.0f)
		{
			WingAnimate = FALSE;
		}
	}
	else
	{
		WingYUpdate = WingYUpdate + 0.1f;
		if(WingYUpdate >= 100.0f)
		{
			WingAnimate = TRUE;
		}
	}

	if (PushpakVimanMove <= 100.0f)
	{
		PushpakVimanMove = PushpakVimanMove + 0.005f;
		PushpakVimanUp = PushpakVimanUp + 0.005f;
		if (PushpakVimanMove >= 3.0f)
		{
			// SetTimer(AAA_ghwnd, TIMER_ID_FOR_NECKLACE, 0, NULL);
			NecklaceMove();
		}
		if (PushpakVimanMove >= 5.0f)
		{
			// SetTimer(AAA_ghwnd, TIMER_ID_FOR_BANGLES, 0, NULL);
			BanglesMove();
		}
	}
}

// Animation Function For Necklace
void NecklaceMove(void)
{
	if (dt <= 1.0f)
	{
		// Jewelerry path
		struct Curve curve1;
		
		curve1.x1 = 0.05f; 
		curve1.y1 = 0.1f; 
		curve1.x2 = 0.86f; 
		curve1.y2 = 0.12f; 
		curve1.x3 = 0.95f; 
		curve1.y3 = -0.2f; 
		curve1.x4 = 1.15f; 
		curve1.y4 = -4.2f;

		
		NecklaceMoveX = ((pow(1- dt, 3) * curve1.x1) + ((3 * dt) * pow(1- dt, 2) * curve1.x2) + ((3 * pow(dt, 2)) * (1 - dt) * curve1.x3) + (pow(dt, 3) * curve1.x4));
		NecklaceMoveY = ((pow(1- dt, 3) * curve1.y1) + ((3 * dt) * pow(1- dt, 2) * curve1.y2) + ((3 * pow(dt, 2)) * (1 - dt) * curve1.y3) + (pow(dt, 3) * curve1.y4));	

		dt = dt + 0.001f;
	}
}

// Animation Function For Bangles
void BanglesMove(void)
{
	if (dt2 <= 1.0f)
	{
		// Jewelerry path
		struct Curve curve1;
		
		curve1.x1 = -0.05f; 
		curve1.y1 = 0.1f; 
		curve1.x2 = 0.61f; 
		curve1.y2 = 0.12f; 
		curve1.x3 = 0.75f; 
		curve1.y3 = -0.2f; 
		curve1.x4 = 0.8f; 
		curve1.y4 = -3.9f;

		
		BanglesMoveX = ((pow(1- dt2, 3) * curve1.x1) + ((3 * dt2) * pow(1- dt2, 2) * curve1.x2) + ((3 * pow(dt2, 2)) * (1 - dt2) * curve1.x3) + (pow(dt2, 3) * curve1.x4));
		BanglesMoveY = ((pow(1- dt2, 3) * curve1.y1) + ((3 * dt2) * pow(1- dt2, 2) * curve1.y2) + ((3 * pow(dt2, 2)) * (1 - dt2) * curve1.y3) + (pow(dt2, 3) * curve1.y4));	

		dt2 = dt2 + 0.001f;
	}
}


void Atharv_Sita_Apaharan(void)
{
	// if (StartAnimation == TRUE)
	// {
	// 	// SetTimer(AAA_ghwnd, TIMER_ID_FOR_PUSHPAK_VIMAN, 0, NULL);

	// 	StartAnimation = FALSE;
	// }

	/*---------------------------- SITA APAHARAN SCENE ----------------------------*/

	////////////////////////////////// LAND //////////////////////////////////

	// Set it to Identity Matrix
	glLoadIdentity();

	// Translate Land backward by z
	glTranslatef(0.0f, 0.0f, -2.0f);

	// Land 
	Land(0.0f, -0.7f, 220.0f, 125.0f);

	////////////////////////////////// SKY //////////////////////////////////

	// Set it to Identity Matrix
	glLoadIdentity();

	// Translate Sky backward by z
	glTranslatef(0.0f, 0.0f, -50.0f);
	
	// sky
	Sky(0.0f, 0.0f, 3850.0f, 2250.0f);

	////////////////////////////////// Mountains //////////////////////////////////

	// Set it to Identity Matrix
	glLoadIdentity();

	// Translate Mountain backward by z
	glTranslatef(0.0f, -6.0f, -40.0f);

	// Mountains
	Mountains(0.0f, -0.1f, 2950.0f, 1500.0f);

	////////////////////////////////// REAR TREES //////////////////////////////////

	glLoadIdentity();

	// Translate Trees backward by z
	glTranslatef(0.0f, 0.0f, -2.0f);

	// rear Trees
	Tree(-0.5f, -0.4f, 5.0f, 30.0f);
	Tree(1.5f, -0.4f, 5.0f, 30.0f);

	////////////////////////////////// FRONT TREES //////////////////////////////////
	
	// Set it to Identity Matrix
	glLoadIdentity();

	// Translate Trees backward by z
	glTranslatef(0.0f, 0.0f, -1.8f);

	// Front Trees
	Tree(-0.7f, -0.4f, 5.0f, 30.0f);
	Tree(1.7f, -0.4f, 5.0f, 30.0f);


	////////////////////////////////// FENCE //////////////////////////////////


	// Set it to Identity Matrix
	glLoadIdentity();

	// Translate Trees backward by z
	glTranslatef(0.0f, 0.0f, -1.5f);

	// Fence
	Fence(0.02f, -0.47f, -110.0f, 30.0f);
	Fence(-0.02f, -0.47f, 110.0f, 30.0f);

	////////////////////////////////// BANGLES //////////////////////////////////

	// Set it to Identity Matrix
	glLoadIdentity();

	// Translate Trees backward by z
	glTranslatef(0.0f, 2.0f, -12.5f);

	// Bangles
	Bangles((0.0f + BanglesMoveX), (0.0f + BanglesMoveY), 20.0f, 20.0f);

	////////////////////////////////// NECKLACE //////////////////////////////////

	// Set it to Identity Matrix
	glLoadIdentity();

	// Translate Trees backward by z
	glTranslatef(0.0f, 1.7f, -12.0f);

	// // NeckLace
	Necklace((0.0f + NecklaceMoveX ), (0.0f + NecklaceMoveY), 80.0f, 80.0f);

	////////////////////////////////// PUSHPAKVIMAN //////////////////////////////////

	// Set it to Identity Matrix
	glLoadIdentity();

	// Translate Trees backward by z
	glTranslatef(0.0f, 2.58f + (PushpakVimanUp), -7.0f - (PushpakVimanMove));

	// Pushpak Viman
	PushpakViman(0.0f, 0.0f, 100.0f, 100.0f);
}