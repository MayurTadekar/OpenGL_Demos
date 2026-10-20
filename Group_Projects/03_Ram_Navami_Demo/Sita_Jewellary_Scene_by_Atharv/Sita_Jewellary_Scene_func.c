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
#include "Sita_Jewellary_Scene.h"

static BOOL GrassAnimation = TRUE;
static float GrassAnimateX = 0.0f;
static float x , y = 0.0f;

static BOOL initialCalculation = TRUE;


void Tree(float x_pos, float y_pos, float percentX, float percentY)
{
	// code
	// call to branch funciton
	Treeleaves(-0.5f + x_pos, 0.47f + y_pos, 0.0f + percentX, 0.0f + percentY, 12.0f, 55.0f, 31.0f);
	Treeleaves(-0.55f + x_pos, 0.8f + y_pos, 0.0f + percentX, 0.0f + percentY, 12.0f, 55.0f, 31.0f);
	Treeleaves(-0.79f + x_pos, 0.7f + y_pos, 10.0f + percentX, 0.0f + percentY, 12.0f, 55.0f, 31.0f);
	Treeleaves(-0.4f + x_pos, 0.53f + y_pos, 16.0f + percentX, 0.0f + percentY, 12.0f, 55.0f, 31.0f);
	Treeleaves(-0.75f + x_pos, 0.5f + y_pos, 10.0f + percentX, 0.0f + percentY, 12.0f, 55.0f, 31.0f);

	Treeleaves(-0.6f + x_pos, 0.75f + y_pos, 0.0f + percentX, 0.0f + percentY, 26.0f, 99.0f, 55.0f);
	Treeleaves(-0.44f + x_pos, 0.6f + y_pos, 7.0f + percentX, 0.0f + percentY, 26.0f, 99.0f, 55.0f);
	Treeleaves(-0.63f + x_pos, 0.62f + y_pos, 3.0f + percentX, 0.0f + percentY, 26.0f, 99.0f, 55.0f);
	
	// call here stem function
	draw_stem(-0.5+x_pos, -0.1+y_pos, 100.0);

	Treeleaves(-0.44f + x_pos, 0.57f + y_pos, 0.0f + percentX, 0.0f + percentY, 78.0f, 150.0f, 43.0f);
	Treeleaves(-0.66f + x_pos, 0.61f + y_pos, 9.0f + percentX, 0.0f + percentY, 78.0f, 150.0f, 43.0f);
	Treeleaves(-0.6f + x_pos, 0.51f + y_pos, 2.0f + percentX, 0.0f + percentY, 78.0f, 150.0f, 43.0f);
	Treeleaves(-0.75f + x_pos, 0.6f + y_pos, 2.0f + percentX, 0.0f + percentY, 78.0f, 150.0f, 43.0f);
}

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

void Circle(float x_pos, float y_pos, float percentX, float percentY, float radius, float red, float green, float blue)
{	
	glPointSize(20.0f);
	glBegin(GL_POINTS);
	glColor4f( red/ 256.0f, green/ 256.0f, blue / 256.0f, 1.0f);
	{
		glVertex3f(VALUE_FROM_PERCENT( x, percentX) + x_pos, VALUE_FROM_PERCENT( y, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( x + 0.03f, percentX) + x_pos, VALUE_FROM_PERCENT( y, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( x - 0.03f, percentX) + x_pos, VALUE_FROM_PERCENT( y, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( x, percentX) + x_pos, VALUE_FROM_PERCENT( y + 0.03f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( x, percentX) + x_pos, VALUE_FROM_PERCENT( y - 0.03f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( x + 0.08f, percentX) + x_pos, VALUE_FROM_PERCENT( y, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( x - 0.08f, percentX) + x_pos, VALUE_FROM_PERCENT( y, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( x, percentX) + x_pos, VALUE_FROM_PERCENT( y + 0.08f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( x, percentX) + x_pos, VALUE_FROM_PERCENT( y - 0.08f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( x + 0.08f, percentX) + x_pos, VALUE_FROM_PERCENT( y + 0.08f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( x - 0.08f, percentX) + x_pos, VALUE_FROM_PERCENT( y - 0.08f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( x - 0.08f, percentX) + x_pos, VALUE_FROM_PERCENT( y + 0.08f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( x + 0.08f, percentX) + x_pos, VALUE_FROM_PERCENT( y - 0.08f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( x + 0.13f, percentX) + x_pos, VALUE_FROM_PERCENT( y, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( x - 0.13f, percentX) + x_pos, VALUE_FROM_PERCENT( y, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( x, percentX) + x_pos, VALUE_FROM_PERCENT( y + 0.13f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( x, percentX) + x_pos, VALUE_FROM_PERCENT( y - 0.13f, percentY) + y_pos, 0.0f);
	}
	glEnd();
}

void Land(void)
{
	glBegin(GL_TRIANGLE_STRIP);
	{
		glColor3f(95.0/256.0f, 116.0/256.0f, 2.0/256.0f);
		glVertex3f( 1.0f, 1.0f, 0.0f);
		glVertex3f( 0.84f, 1.2f, 0.0f);
		glColor3f(90.0/256.0f, 45.0/256.0f, 33.0/256.0f);
		glVertex3f( 1.0f, -1.0f, 0.0f);
		glVertex3f( 0.80f, -1.0f, 0.0f);
		
		glColor3f(95.0/256.0f, 116.0/256.0f, 2.0/256.0f);
		glVertex3f( 0.84f, 1.2f, 0.0f);
		glVertex3f( 0.74f, 1.05f, 0.0f);
		glColor3f(90.0/256.0f, 45.0/256.0f, 33.0/256.0f);
		glVertex3f( 0.80f, -1.0f, 0.0f);
		glVertex3f( 0.60f, -1.0f, 0.0f);

		glColor3f(95.0/256.0f, 116.0/256.0f, 2.0/256.0f);
		glVertex3f( 0.74f, 1.05f, 0.0f);
		glVertex3f( 0.33f, 1.11f, 0.0f);
		glColor3f(90.0/256.0f, 45.0/256.0f, 33.0/256.0f);
		glVertex3f( 0.60f, -1.0f, 0.0f);
		glVertex3f( 0.10f, -1.0f, 0.0f);

		glColor3f(95.0/256.0f, 116.0/256.0f, 2.0/256.0f);
		glVertex3f( 0.33f, 1.11f, 0.0f);
		glVertex3f( -0.25f, 1.0f, 0.0f);
		glColor3f(90.0/256.0f, 45.0/256.0f, 33.0/256.0f);
		glVertex3f( 0.10f, -1.0f, 0.0f);
		glVertex3f( -0.62f, -1.0f, 0.0f);

		
		glColor3f(95.0/256.0f, 116.0/256.0f, 2.0/256.0f);
		glVertex3f( -0.25f, 1.0f, 0.0f);
		glVertex3f( -0.50f, 1.12f, 0.0f);
		glColor3f(90.0/256.0f, 45.0/256.0f, 33.0/256.0f);
		glVertex3f( -0.62f, -1.0f, 0.0f);
		glVertex3f( -0.72f, -1.0f, 0.0f);

		glColor3f(95.0/256.0f, 116.0/256.0f, 2.0/256.0f);
		glVertex3f( -0.50f, 1.12f, 0.0f);
		glVertex3f( -0.74f, 1.07f, 0.0f);
		glColor3f(90.0/256.0f, 45.0/256.0f, 33.0/256.0f);
		glVertex3f( -0.72f, -1.0f, 0.0f);
		glVertex3f( -0.89f, -1.0f, 0.0f);

		glColor3f(95.0/256.0f, 116.0/256.0f, 2.0/256.0f);
		glVertex3f( -0.74f, 1.07f, 0.0f);
		glVertex3f( -1.0f, 1.13f, 0.0f);
		glColor3f(90.0/256.0f, 45.0/256.0f, 33.0/256.0f);
		glVertex3f( -0.89f, -1.0f, 0.0f);
		glVertex3f( -1.0f, -1.0f, 0.0f);


	}
	glEnd();
}

void Grass(void)
{
	for(int i = 0; i < NUMBEROFGRASSBLADE; i++)
	{
		GrassBlade(x_postion[i], y_postion[i], z_postion[i]);
	}
}

void GrassBlade(float x_pos, float y_pos, float z_pos)
{
	glBegin(GL_TRIANGLES);
	{
		glColor3f(36.0/256.0f, 114.0/256.0f, 0.0/256.0f);
		glVertex3f(x_pos + 0.0f, y_pos + 0.0f, z_pos + 0.0f);
		glColor3f(137.0/256.0f, 188.0/256.0f, 46.0/256.0f);
		glVertex3f((x_pos + 0.00875f) + GrassAnimateX, y_pos + 0.06f,z_pos + 0.0f);
		glColor3f(36.0/256.0f, 114.0/256.0f, 0.0/256.0f);
		glVertex3f(x_pos + 0.0175f, y_pos + 0.0f, z_pos + 0.0f);
	}
	glEnd();
}


void RandomGrassGeneration(void)
{
	for(int i = 0; i < NUMBEROFGRASSBLADE; i++)
	{
		y_postion[i] = (((rand() % 10000) - 5000)/12000.0f); // -0.41 to 0.41
		if ((y_postion[i] > -0.2f) && (y_postion[i] < 0.2f))
		{
			x_postion[i] = (((rand() % 10000) - 7000)/4000.0f); // -0.83 to 083
		}
		else if ((y_postion[i] > -0.3f) && (y_postion[i] < 0.3f))
		{
			x_postion[i] = (((rand() % 10000) - 6000)/4000.0f); // -0.83 to 083
		}
		else
		{
			x_postion[i] = (((rand() % 10000) - 5000)/4000.0f); // -1.25f to 1.25f
		}
		z_postion[i] = (((rand() % 10000) - 5000)/10000.0f); // -0.5 to 0.5f
	}
}

void Mountains(float red, float green, float blue)
{
	// Variable declarations
	struct Curve curve1;
	struct Curve curve2;
	struct Curve curve3;
	GLfloat t = 0.0f;
	int i = 0;

	// code
	
	// Dark Green Mountain
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

	glColor3f(red, green, blue);
	glBegin(GL_TRIANGLE_STRIP);
	{
		for ( i = 0; i < 100; i++)
		{
			glVertex3f(  Mxt4[i],  Myt4[i], 0.0f);
			glVertex3f(  Mxt3[i],  Myt3[i] , 0.0f);
		}	
	}
	glEnd();
}

void NightSky(void)
{
	glBegin(GL_QUADS);
	{
		glColor3f(9.0/256.0f, 8.0/256.0f, 14.0/256.0f);
		glVertex3f( 1.0f, 1.0f, 0.0f);
		glVertex3f( -1.0f, 1.0f, 0.0f);
		glColor3f(12.0/256.0f, 67.0/256.0f, 136.0/256.0f);
		glVertex3f( -1.0f, -2.0f, 0.0f);
		glVertex3f( 1.0f, -2.0f, 0.0f);
	}
	glEnd();
}

void Necklace(float x_pos, float y_pos, float percentX, float percentY)
{
	// code
	glLineWidth(0.8f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	{
		glVertex3f( VALUE_FROM_PERCENT( -0.08f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.38f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.05f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.36f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.04, percentX) + x_pos, VALUE_FROM_PERCENT( 0.32f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.01f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.28f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( 0.03f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.26f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( 0.05f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.23f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( 0.04f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.18f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( 0.02f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.17f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( 0.05f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.19f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.02f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.185f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.05f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.2f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.07f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.22f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.1f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.24f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.12f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.27f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.14f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.32f, percentY) + y_pos, 0.0f);
		glVertex3f( VALUE_FROM_PERCENT( -0.11f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.35f, percentY) + y_pos, 0.0f);
	
	}
	glEnd();

	glPointSize(11.0f);
	glColor4f(185.0f/256.0f, 207.0f/256.0f, 240.0f/256.0f , 1.0f);
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
		glVertex3f( VALUE_FROM_PERCENT( 0.05f, percentX) + x_pos, VALUE_FROM_PERCENT( 0.19f, percentY) + y_pos, 0.0f);
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


void draw_stem(float x_pos, float y_pos, float percent)
{
	// Variable Declarations
	// Variables for left curve
	GLfloat xl[4], yl[4];
	GLfloat xtl[200], ytl[200];
	GLfloat tl=0.0f;
	int il;

	// Variables for right curve
	GLfloat xr[4], yr[4];
	GLfloat xtr[200], ytr[200];
	GLfloat tr=0.0f;
	int ir;

	//********************** left curve of tree ********************************************** */
	xl[0] = -0.14;  xl[1] = -0.07;  xl[2] = -0.07;  xl[3] = -0.1;
	yl[0] = -0.6;  yl[1] = -0.7;  yl[2] = 0.7;  yl[3] = 0.7;

	for(il=0, tl=0; tl<=1.0f; il++, tl+=0.008)	// here (1/0.008) = 125 so in array 125 points will be filled
	{
		xtl[il] = (pow(1-tl, 3)*xl[0]) + (3*tl*pow(1-tl, 2)*xl[1]) + (3*pow(tl,2)*pow(1-tl, 2)*xl[2]) + (pow(tl,3)*xl[3]);
		ytl[il] = (pow(1-tl, 3)*yl[0]) + (3*tl*pow(1-tl, 2)*yl[1]) + (3*pow(tl,2)*pow(1-tl, 2)*yl[2]) + (pow(tl,3)*yl[3]);
	}
	/******************************************************************************************* */

	//********************** Right curve of tree stem ********************************************** */
	xr[0] = 0.17;  xr[1] = 0.07;  xr[2] = 0.07;  xr[3] = 0.1;
	yr[0] = -0.6;  yr[1] = -0.7;  yr[2] = 0.7;  yr[3] = 0.7;

	for(ir=0, tr =0; tr<=1.0f; ir++, tr+=0.008)		// here (1/0.008) = 125 so in array 125 points will be filled
	{
		xtr[ir] = (pow(1-tr, 3)*xr[0]) + (3*tr*pow(1-tr, 2)*xr[1]) + (3*pow(tr,2)*pow(1-tr, 2)*xr[2]) + (pow(tr,3)*xr[3]);
		ytr[ir] = (pow(1-tr, 3)*yr[0]) + (3*tr*pow(1-tr, 2)*yr[1]) + (3*pow(tr,2)*pow(1-tr, 2)*yr[2]) + (pow(tr,3)*yr[3]);
	}
	/******************************************************************************************* */

	glBegin(GL_TRIANGLE_STRIP);
	for(ir=0, il=0; ir<125, il<125; ir++, il++)
	{
		glColor3f(93.0/255.0f, 62.0/255.0f, 14.0/255.0f);
		glVertex3f(VALUE_FROM_PERCENT(xtr[ir]+x_pos, percent), VALUE_FROM_PERCENT(ytr[ir]+y_pos, percent), 0.0f);

		glColor3f(93.0/255.0f, 62.0/255.0f, 14.0/255.0f);
		glVertex3f(xtl[il]+x_pos, ytl[il]+y_pos, 0.0f);
	}
	glEnd();
}

void draw_branch(float x_pos, float y_pos, float percent)
{
	// Variables for branch
	GLfloat xb[4], yb[4];
	GLfloat xtb[200], ytb[200];
	GLfloat tb=0.0f;
	int ib;

	//****************************** Drawing Branches ************************************/
	xb[0] = 0.0;  xb[1] = 0.11;  xb[2] = 0.01;  xb[3] = 0.15;
	yb[0] = -0.1;  yb[1] = 0.1;  yb[2] = 0.14;  yb[3] = 0.35;

	for(ib=0, tb =0; tb<=1.0f; ib++, tb+=0.008)		// here (1/0.008) = 125 so in array 125 points will be filled
	{
		xtb[ib] = (pow(1-tb, 3)*xb[0]) + (3*tb*pow(1-tb, 2)*xb[1]) + (3*pow(tb,2)*pow(1-tb, 2)*xb[2]) + (pow(tb,3)*xb[3]);
		ytb[ib] = (pow(1-tb, 3)*yb[0]) + (3*tb*pow(1-tb, 2)*yb[1]) + (3*pow(tb,2)*pow(1-tb, 2)*yb[2]) + (pow(tb,3)*yb[3]);
	}
	/*************************************************************************************/
	glPointSize(20.0);
	glBegin(GL_POINTS);
	glColor3f(93.0/255.0f, 62.0/255.0f, 14.0/255.0f);
	for(ib=0, tb =0; tb<=1.0f; ib++, tb+=0.008)
	{
		glVertex3f(xtb[ib]+x_pos, ytb[ib]+y_pos, 0.0f);
	}
	glEnd();
}


void Stars(void)
{
    glColor4f(0.8f, 1.0f, 1.0f, 1.0f);

    glPointSize(2.0f);
    glBegin(GL_POINTS);
	{
		glVertex3f(0.2f, 0.1f, 0.0f);
		glVertex3f(-0.3f, 0.1f, 0.0f);
		glVertex3f(0.5f, 0.2f, 0.0f);
		glVertex3f(-0.1f, 0.3f, 0.0f);
		glVertex3f(0.3f, 0.1f, 0.0f);
		glVertex3f(-0.2f, 0.2f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.1f, 0.2f, 0.0f);
		glVertex3f(-0.3f, 0.3f, 0.0f);
		glVertex3f(-0.1f, 0.1f, 0.0f);
		glVertex3f(0.3f, 0.3f, 0.0f);
		glVertex3f(-0.5f, 0.0f, 0.0f);
		glVertex3f(0.2f, -0.1f, 0.0f);
		glVertex3f(-0.3f, -0.1f, 0.0f);
		glVertex3f(0.5f, -0.2f, 0.0f);
		glVertex3f(-0.1f, -0.3f, 0.0f);
		glVertex3f(0.3f, -0.1f, 0.0f);
		glVertex3f(-0.2f, -0.2f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.1f, -0.2f, 0.0f);
		glVertex3f(-0.3f, -0.3f, 0.0f);
		glVertex3f(-0.1f, -0.1f, 0.0f);
		glVertex3f(0.3f, -0.3f, 0.0f);
		glVertex3f(-0.5f, 0.0f, 0.0f);
	}
    glEnd();

    glPointSize(1.5f);
    glBegin(GL_POINTS);
    {
		glVertex3f(0.25f, -0.05f, 0.0f);
		glVertex3f(-0.15f, -0.2f, 0.0f);
		glVertex3f(0.4f, 0.1f, 0.0f);
		glVertex3f(-0.1f, 0.25f, 0.0f);
		glVertex3f(0.2f, -0.3f, 0.0f);
		glVertex3f(-0.35f, 0.15f, 0.0f);
		glVertex3f(0.15f, 0.15f, 0.0f);
		glVertex3f(-0.25f, -0.25f, 0.0f);
		glVertex3f(0.35f, -0.2f, 0.0f);
		glVertex3f(-0.4f, -0.1f, 0.0f);
		glVertex3f(0.1f, 0.3f, 0.0f);
		glVertex3f(-0.1f, -0.35f, 0.0f);
		glVertex3f(0.3f, -0.3f, 0.0f);
		glVertex3f(-0.2f, 0.35f, 0.0f);
		glVertex3f(0.0f, -0.4f, 0.0f);
		glVertex3f(-0.1f, 0.4f, 0.0f);
		glVertex3f(0.4f, -0.25f, 0.0f);
		glVertex3f(-0.3f, -0.15f, 0.0f);
		glVertex3f(0.2f, 0.35f, 0.0f);
		glVertex3f(-0.25f, 0.25f, 0.0f);
	}
    glEnd();

    glPointSize(1.2f);
    glBegin(GL_POINTS);
	{
    	glVertex3f(0.45f, -0.15f, 0.0f);
	}
    glEnd();
}

void update(void)
{
	// code
	if(GrassAnimation)
	{
		GrassAnimateX = GrassAnimateX + 0.0001f;
		if(GrassAnimateX >= 0.02f)
		{
			GrassAnimation = FALSE;
		}
	}
	else
	{
		GrassAnimateX = GrassAnimateX - 0.0001f;
		if(GrassAnimateX <= -0.02f)
		{
			GrassAnimation = TRUE;
		}
	}
}

void Atharv_Sita_Jewellary_Scene(void)
{
    if(initialCalculation == TRUE)
    {
        srand(time(0));
    	RandomGrassGeneration();

        initialCalculation = FALSE;
    }
    // Set it to Identity Matrix
	glLoadIdentity();

	// Translate Sky backward by z
	glTranslatef(0.0f, 1.8f, -13.0f);

	// Scale
	glScalef(9.7f, 6.0f, 1.0f);

	NightSky();

	// Set it to Identity Matrix
	glLoadIdentity();

	// Translate Stars
	glTranslatef(0.0f, 0.5f, -12.9f);

	// Scale
	glScalef(23.0f, 10.0f, 1.0f);

	// Stars
	Stars();
	
	// Set it to Identity Matrix
	glLoadIdentity();

	// Translate Mountains backward by z
	glTranslatef(-0.6f, 0.7f, -12.0f);

	// Scale Mountains in x and y axis
	glScalef(-10.0f, 11.0f, 0.0f);

	// Mountain 
	Mountains(36.0/256.0f, 114.0/256.0f, 0.0/256.0f);

	// Set it to Identity Matrix
	glLoadIdentity();

	// Translate Green Forests backward by z
	glTranslatef(0.0f, 0.175f, -11.0f);

	glScalef(1.00f, 0.75f, 1.00f);

	Tree(-4.0f, 0.5f, 5.0f, 30.0f);
	Tree(-4.9f, 0.3f, 5.0f, 30.0f);
	Tree(-5.5f, 1.0f, 5.0f, 30.0f);
	Tree(-6.2f, 0.8f, 5.0f, 30.0f);
	Tree(-7.2f, 0.7f, 5.0f, 30.0f);
	Tree(-6.7f, 0.3f, 5.0f, 30.0f);

	Tree(-2.0f, 0.2f, 5.0f, 30.0f);
	Tree(-2.9f, 0.3f, 5.0f, 30.0f);
	Tree(-3.5f, 0.2f, 5.0f, 30.0f);
	Tree(-5.2f, 0.1f, 5.0f, 30.0f);
	Tree(-6.7f, 0.3f, 5.0f, 30.0f);

	Tree(-7.0f, 0.1f, 5.0f, 30.0f);


	// Set it to Identity Matrix
	glLoadIdentity();

	// Translate Mountains backward by z
	glTranslatef(0.0f, 0.2f, -3.0f);

	// Scale Mountains in x and y axis
	glScalef(2.5f, 3.0f, 0.0f);

	// Mountain 
	Mountains(8.0f/255.0f, 108.0f/255.0f, 20.0f/255.0f);

	// Set it to Identity Matrix
	glLoadIdentity();

	// Translate Green Forests backward by z
	glTranslatef(-0.2f, -0.175f, -3.0f);

	glScalef(0.35f, 0.25f, 1.0f);

	Tree(4.0f, 0.5f, 5.0f, 30.0f);
	Tree(4.7f, 0.8f, 5.0f, 30.0f);
	Tree(5.7f, 0.3f, 5.0f, 30.0f);
	Tree(2.0f, 0.2f, 5.0f, 30.0f);
	Tree(3.5f, 0.2f, 5.0f, 30.0f);
	Tree(6.7f, 0.3f, 5.0f, 30.0f);

	Tree(0.0f, 0.1f, 5.0f, 30.0f);

	// Set it to Identity Matrix
	glLoadIdentity();

	// Translate Land backward by z
	glTranslatef(0.0f, -0.8f, -3.0f);

	// Scale Land in x and y direction
	glScalef(2.4f, 0.7f, 0.0f);

	// Rotate land in x axis
	glRotatef(50.0f, 1.0f, 0.0f, 0.0f);

	// Grass
	Land();

	// Set it to Identity Matrix
	glLoadIdentity();

	// Translate Grass backward by z
	glTranslatef(-1.6f, -0.75f, -3.0f);

	// Grass
	Grass();

	// Set it to Identity Matrix
	glLoadIdentity();

	// Translate Grass backward by z
	glTranslatef(2.1f, -0.75f, -3.0f);	

	// scale grass 
	glScalef(1.0f, 1.0f, 1.0f);

	// Grass
	Grass();

	// Set it to Identity Matrix
	glLoadIdentity();

	// Translate Necklace backward by z
	glTranslatef(0.0f, -0.9f, -2.8f);

	// Scale necklace
	glScalef(1.75f, 1.2f, 1.0f);

	// Rotate Necklace
	glRotatef(45.0f, 1.0f, 0.0f, 0.0f);

	// Necklace
	Necklace(0.0f, 0.0f, 100.0f, 100.0f);
}