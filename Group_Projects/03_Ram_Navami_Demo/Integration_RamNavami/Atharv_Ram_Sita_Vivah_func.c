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
#include "Atharv_Ram_Sita_Vivah.h"

#define VALUE_FROM_PERCENT(complete, percent) (complete * percent / 100.0f)

float percentage = 2.0f;
float anotherPercent = 2.7f;
float yetanotherPercent = 2.5f;


void Garland(void)
{
	glPointSize(20.0f);
	glBegin(GL_POINTS);
	{
		/// White flower
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f( -0.005f, 0.01f, 0.0f);
		glVertex3f( 0.0f, 0.015f, 0.0f);
		glVertex3f( 0.005f, 0.01f, 0.0f);

		glVertex3f(-0.0075f, 0.0075f, 0.0f);
		glVertex3f( 0.0f, 0.0075f, 0.0f);
		glVertex3f( 0.0075f,0.0075f, 0.0f);

		glVertex3f( -0.0075f, 0.0f, 0.0f);
		glVertex3f( 0.0f, 0.0f, 0.0f);
		glVertex3f( 0.0075f, 0.0f, 0.0f);

		glVertex3f(-0.0075f, -0.0075f, 0.0f);
		glVertex3f( 0.0f, -0.0075f, 0.0f);
		glVertex3f( 0.0075f, -0.0075f, 0.0f);

		/// White flower
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f( -0.0075f, -0.015f, 0.0f);
		glVertex3f( 0.0f, -0.015f, 0.0f);
		glVertex3f( 0.0075f, -0.015f, 0.0f);

		glVertex3f( -0.0075f, -0.0225f, 0.0f);
		glVertex3f( 0.0f, -0.0225f, 0.0f);
		glVertex3f( 0.0075f, -0.0225f, 0.0f);

		glVertex3f( -0.0075f, -0.03f, 0.0f);
		glVertex3f( 0.0f, -0.03f, 0.0f);
		glVertex3f( 0.0075f, -0.03f, 0.0f);

		/// White flower
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f( -0.0075f, -0.06f, 0.0f);
		glVertex3f( 0.0f, -0.06f, 0.0f);
		glVertex3f( 0.0075f, -0.06f, 0.0f);

		glVertex3f( -0.0075f, -0.0675f, 0.0f);
		glVertex3f( 0.0f, -0.0675f, 0.0f);
		glVertex3f( 0.0075f, -0.0675f, 0.0f);

		glVertex3f( -0.0075f, -0.075f, 0.0f);
		glVertex3f( 0.0f, -0.075f, 0.0f);
		glVertex3f( 0.0075f, -0.075f, 0.0f);


		/// White flower
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f( -0.0075f, -0.0825f, 0.0f);
		glVertex3f( 0.0f, -0.0825f, 0.0f);
		glVertex3f( 0.0075f, -0.0825f, 0.0f);

		glVertex3f( -0.0075f, -0.09f, 0.0f);
		glVertex3f( 0.0f, -0.09f, 0.0f);
		glVertex3f( 0.0075f, -0.09f, 0.0f);

		glVertex3f( -0.0075f, -0.0975f, 0.0f);
		glVertex3f( 0.0f, -0.0975f, 0.0f);
		glVertex3f( 0.0075f, -0.0975f, 0.0f);

		/// White flower
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f( -0.0075f, -0.1275f, 0.0f);
		glVertex3f( 0.0f, -0.1275f, 0.0f);
		glVertex3f( 0.0075f, -0.1275f, 0.0f);

		glVertex3f( -0.0075f, -0.135f, 0.0f);
		glVertex3f( 0.0f, -0.135f, 0.0f);
		glVertex3f( 0.0075f, -0.135f, 0.0f);

		glVertex3f( -0.0075f, -0.1425f, 0.0f);
		glVertex3f( 0.0f, -0.1425f, 0.0f);
		glVertex3f( 0.0075f, -0.1425f, 0.0f);

		/// Pink flower
		glColor3f(248.0f/255.0f, 3.0f/255.0f, 139.0f/255.0f);
		glVertex3f( -0.005f, -0.17f, 0.0f);
		glVertex3f( 0.0f, -0.1725f, 0.0f);
		glVertex3f( 0.005f, -0.17f, 0.0f);

		/// White flower
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f( -0.0075f, -0.15f, 0.0f);
		glVertex3f( 0.0f, -0.15f, 0.0f);
		glVertex3f( 0.0075f, -0.15f, 0.0f);

		glVertex3f( -0.0075f, -0.1575f, 0.0f);
		glVertex3f( 0.0f, -0.1575f, 0.0f);
		glVertex3f( 0.0075f, -0.1575f, 0.0f);

		glVertex3f( -0.0075f, -0.165f, 0.0f);
		glVertex3f( 0.0f, -0.165f, 0.0f);
		glVertex3f( 0.0075f, -0.165f, 0.0f);


		/// Pink flower
		glColor3f(248.0f/255.0f, 3.0f/255.0f, 139.0f/255.0f);
		glVertex3f( -0.0075f, -0.0375f, 0.0f);
		glVertex3f( 0.0f, -0.0375, 0.0f);
		glVertex3f( 0.0075f, -0.0375, 0.0f);

		glVertex3f( -0.0075f, -0.045f, 0.0f);
		glVertex3f( 0.0f, -0.045f, 0.0f);
		glVertex3f( 0.0075f, -0.045f, 0.0f);

		glVertex3f( -0.0075f, -0.0525f, 0.0f);
		glVertex3f( 0.0f, -0.0525f, 0.0f);
		glVertex3f( 0.0075f, -0.0525f, 0.0f);

		/// Pink flower
		glColor3f(248.0f/255.0f, 3.0f/255.0f, 139.0f/255.0f);
		glVertex3f( -0.0075f, -0.105f, 0.0f);
		glVertex3f( 0.0f, -0.105f, 0.0f);
		glVertex3f( 0.0075f, -0.105f, 0.0f);

		glVertex3f( -0.0075f, -0.1125f, 0.0f);
		glVertex3f( 0.0f, -0.1125f, 0.0f);
		glVertex3f( 0.0075f, -0.1125f, 0.0f);

		glVertex3f( -0.0075f, -0.12f, 0.0f);
		glVertex3f( 0.0f, -0.12f, 0.0f);
		glVertex3f( 0.0075f, -0.12f, 0.0f);

	}
	glEnd();

	glPointSize(8.0f);
	glBegin(GL_POINTS);
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f( 0.0f, -0.18f, 0.0f);
		glVertex3f( 0.0015f, -0.184f, 0.0f);
		glVertex3f( -0.0015f, -0.184f, 0.0f);
		glVertex3f( 0.0015f, -0.188f, 0.0f);
		glVertex3f( -0.0015f, -0.188f, 0.0f);
		glVertex3f( 0.0015f, -0.192f, 0.0f);
		glVertex3f( -0.0015f, -0.192f, 0.0f);

		glColor3f(0.0f/255.0f, 92.0f/255.0f, 0.0f/255.0f);
		glVertex3f( 0.0015f, -0.196f, 0.0f);
		glVertex3f( -0.0015f, -0.196f, 0.0f);

		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f( 0.0025f, -0.200f, 0.0f);
		glVertex3f( 0.0f, -0.200f, 0.0f);
		glVertex3f( -0.0025f, -0.200f, 0.0f);
	}
	glEnd();
}

void HandCurveCalculation(void)
{
	struct Curvee curve1;
	struct Curvee curve2;
	struct Curvee curve3;

	curve1.x0 = 0.0f;
	curve1.x1 = 0.12f;
	curve1.x2 = 0.25f;
	curve1.x3 = 0.49f;

	curve1.y0 = -0.14f;
	curve1.y1 = -0.2f;
	curve1.y2 = -0.2f;
	curve1.y3 = 0.12f;

	curve2.x0 = 0.0f;
	curve2.x1 = 0.1f;
	curve2.x2 = 0.1f;
	curve2.x3 = 1.2f;

	curve2.y0 = 0.025f;
	curve2.y1 = -0.025f;
	curve2.y2 = -0.025f;
	curve2.y3 = -0.25f;

	curve3.x0 = -0.275f;
	curve3.x1 = 0.26f;
	curve3.x2 = 0.26f;
	curve3.x3 = 0.44f;

	curve3.y0 = -0.25f;
	curve3.y1 = 0.07f;
	curve3.y2 = 0.07f;
	curve3.y3 = 0.18f;

	int i = 0;
	for(float t = 0.0f; t < 1.0f; t = t + 0.00665f)
	{
		float u = (1 - t);
		lowerCurveOfHandX[i] = (((u * u * u ) * curve1.x0) + (3 * ( u * u ) * t * curve1.x1) + (3 * u * ( t * t ) * curve1.x2) + ((t * t * t ) * curve1.x3));
		lowerCurveOfHandY[i] = (((u * u * u ) * curve1.y0) + (3 * ( u * u ) * t * curve1.y1) + (3 * u * ( t * t ) * curve1.y2) + ((t * t * t ) * curve1.y3));  
		i++;
	}

	i = 0;
	for(float t = 0.0f; t < 1.0f; t = t + 0.00665f)
	{
		if ( i < 50)
		{
			float u = (1 - t);
			UpperCurveofHandX[i] = (((u * u * u ) * curve2.x0) + (3 * ( u * u ) * t * curve2.x1) + (3 * u * ( t * t ) * curve2.x2) + ((t * t * t ) * curve2.x3));
			UpperCurveofHandY[i] = (((u * u * u ) * curve2.y0) + (3 * ( u * u ) * t * curve2.y1) + (3 * u * ( t * t ) * curve2.y2) + ((t * t * t ) * curve2.y3));  
		}
		else
		{
			float u = (1 - t);
			UpperCurveofHandX[i] = (((u * u * u ) * curve3.x0) + (3 * ( u * u ) * t * curve3.x1) + (3 * u * ( t * t ) * curve3.x2) + ((t * t * t ) * curve3.x3));
			UpperCurveofHandY[i] = (((u * u * u ) * curve3.y0) + (3 * ( u * u ) * t * curve3.y1) + (3 * u * ( t * t ) * curve3.y2) + ((t * t * t ) * curve3.y3));  
		}
		i++;
	}

}

void Hand( float red1, float green1, float blue1, float red2, float green2, float blue2)
{
	glBegin(GL_TRIANGLE_STRIP);
	{
		for (int i = 0; i < 150; i++)
		{
			glColor3f(red1/255.0f, green1/255.0f, blue1/255.0f);
			glVertex3f( UpperCurveofHandX[i], UpperCurveofHandY[i], 0.0f);
			glColor3f(red2/255.0f, green2/255.0f, blue2/255.0f);
			glVertex3f( lowerCurveOfHandX[i], lowerCurveOfHandY[i], 0.0f);
		}
	}
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	{
		glColor3f(red1/255.0f, green1/255.0f, blue1/255.0f);
		glVertex3f( 0.42f, 0.17f, 0.0f);
		glColor3f(red2/255.0f, green2/255.0f, blue2/255.0f);
		glVertex3f( 0.48f, 0.11f, 0.0f);
		glColor3f(red1/255.0f, green1/255.0f, blue1/255.0f);
		glVertex3f( 0.46f, 0.24f, 0.0f);
		glColor3f(red2/255.0f, green2/255.0f, blue2/255.0f);
		glVertex3f( 0.55f, 0.14f, 0.0f);
		glColor3f(red1/255.0f, green1/255.0f, blue1/255.0f);
		glVertex3f( 0.5f, 0.28f, 0.0f);
	}
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	{
		glColor3f(red2/255.0f, green2/255.0f, blue2/255.0f);
		glVertex3f( 0.55f, 0.14f, 0.0f);
		glColor3f(red1/255.0f, green1/255.0f, blue1/255.0f);
		glVertex3f( 0.51f, 0.25f, 0.0f);
		glColor3f(red2/255.0f, green2/255.0f, blue2/255.0f);
		glVertex3f( 0.61f, 0.17f, 0.0f);
		glColor3f(red1/255.0f, green1/255.0f, blue1/255.0f);
		glVertex3f( 0.58f, 0.27f, 0.0f);
	}
	glEnd();
}

void GoldenKada(void)
{
	glBegin(GL_TRIANGLE_STRIP);
	{
		glColor3f(240.0f/255.0f, 200.0f/255.0f, 38.0f/255.0f);
		glVertex3f( 0.0f, 0.0f, 0.0f);
		glVertex3f( 0.0f, 0.1f, 0.0f);
		glColor3f(245.0f/255.0f, 175.0f/255.0f, 40.0f/255.0f);
		glVertex3f( 0.02f, 0.0f, 0.0f);
		glVertex3f( 0.02f, 0.1f, 0.0f);
	}
	glEnd();
}

void Atharv_HandsOfRamAndSita(void)
{
	///////////////////////////////// Shree Ram rear hand /////////////////////////////////

	// Set it to Identity Matrix
	glLoadIdentity();

	// Translate Shree Ram hand backward by z
	glTranslatef(-0.75f * (percentage), 0.02f, -1.0f);

	// Scale Shree Ram hand
	glScalef(0.6f, 0.6f, 1.0f);

	Hand( 157.0f, 167.0f, 215.0f, 97.0f, 93.0f, 145.0f);

    ///////////////////////////////// Mata Sita rear hand /////////////////////////////////

	// Set it to Identity Matrix
	glLoadIdentity();

	// Translate Mata sita hand backward by z
	glTranslatef(0.78f * (percentage), 0.02f, -1.0f);

	// Scale Mata Sita hand
	glScalef(-0.55f, 0.35f, 1.0f);

	Hand( 221.0f, 211.0f, 162.0f, 173.0f, 122.0f, 79.0f);

    ///////////////////////////////// Shree Ram's Garland /////////////////////////////////

	// Set it to Identity Matrix
	glLoadIdentity();

	// Translate garland backward by z
	glTranslatef(-0.425f * (anotherPercent), 0.15f, -1.0f);

	// Scale to garland
	glScalef(1.5f, 2.6f, 1.0f);

	Garland();

    ///////////////////////////////// Mata Sita's Garland /////////////////////////////////

	// Set it to Identity Matrix
	glLoadIdentity();

	// Translate garland backward by z
	glTranslatef(0.47f * (anotherPercent), 0.1f, -1.0f);

	// Scale to garland
	glScalef(1.5f, 2.5f, 1.0f);

	Garland();

    ///////////////////////////////// Shree Ram rear hand Bracelet /////////////////////////////////

	// Set it to Identity Matrix
	glLoadIdentity();

	// Translate Golden Kada backward by z
	glTranslatef(-0.5f * (yetanotherPercent), 0.042f, -1.0f);

	// Scale Golden Kada
	glScalef(0.4f, 0.9f, 1.0f);

	// Rotate Golden Kada
	glRotatef(50.0f, 0.0f, 0.0f, 1.0f);

	GoldenKada();
    
    ///////////////////////////////// Shree Ram Front hand /////////////////////////////////

	// Set it to Identity Matrix
	glLoadIdentity();

	// Translate Shree Ram hand backward by z
	glTranslatef(-0.75f * (percentage), 0.0f, -1.0f);

	// Scale Shree Ram hand
	glScalef(0.6f, 0.6f, 1.0f);

	Hand( 157.0f, 167.0f, 215.0f, 97.0f, 93.0f, 145.0f);

    ///////////////////////////////// Mata Sita rear hand Bangle /////////////////////////////////

	// Set it to Identity Matrix
	glLoadIdentity();

	// Translate Golden Kada backward by z
	glTranslatef(0.54f * (yetanotherPercent), 0.04f, -1.0f);

	// Scale Golden Kada
	glScalef(0.2f, 0.7f, 1.0f);

	// Rotate Golden Kada
	glRotatef(40.0f, 0.0f, 0.0f, -1.0f);

	GoldenKada();

    ///////////////////////////////// Mata Sita Front hand /////////////////////////////////

	// Set it to Identity Matrix
	glLoadIdentity();

	// Translate Shree Ram hand backward by z
	glTranslatef(0.76f * (percentage), 0.0f, -1.0f);

	// Scale Shree Ram hand
	glScalef(-0.55f, 0.35f, 1.0f);

	Hand( 221.0f, 211.0f, 162.0f, 173.0f, 122.0f, 79.0f);

    ///////////////////////////////// Mata Sita Front hand bangle /////////////////////////////////

	// Set it to Identity Matrix
	glLoadIdentity();

	// Translate Golden Kada backward by z
	glTranslatef(0.52f * (yetanotherPercent), 0.02f, -1.0f);

	// Scale Golden Kada
	glScalef(0.2f, 0.7f, 1.0f);

	// Rotate Golden Kada
	glRotatef(40.0f, 0.0f, 0.0f, -1.0f);

	GoldenKada();

    ///////////////////////////////// Shree Ram Front hand Kada /////////////////////////////////

	// Set it to Identity Matrix
	glLoadIdentity();

	// Translate Golden Kada backward by z
	glTranslatef(-0.48f * (yetanotherPercent), 0.035f, -1.0f);

	// Scale Golden Kada
	glScalef(0.4f, 0.9f, 1.0f);

	// Rotate Golden Kada
	glRotatef(50.0f, 0.0f, 0.0f, 1.0f);

	GoldenKada();
}

void HandsAnimation(void)
{
	if ( percentage > 1.0f)
	{
		percentage = percentage - (0.00098f * (10.0f/100.0f));
	}
}

void GarlandAnimation(void)
{
	if (anotherPercent > 1.0f)
	{
		anotherPercent = anotherPercent - (0.001655f* (10.0f/100.0f));
	}
}

void BracletAnimation(void)
{
	if (yetanotherPercent > 1.0f)
	{
		yetanotherPercent = yetanotherPercent - (0.00147f * (10.0f/100.0f));
	}
}

void shivdhanushya(float x_pos, float y_pos, float percent)
{
	float x[10], y[10], t,xt[200],yt[200];
	float x1[4], y1[4], xt1[200], yt1[200];
	float x2[4], y2[4], xt2[200], yt2[200];
	float x3[4], y3[4], xt3[200], yt3[200];
	int i;
	
	x[0] = -0.9; y[0] = 0.0;
	x[1] = -0.6; y[1] = 0.1;
	x[2] = -0.3; y[2] = 0.02;
	x[3] = -0.03;  y[3] = -0.04;
		
	x1[0] = -0.9; y1[0] = 0.0;
	x1[1] = -0.6; y1[1] = 0.21;
	x1[2] = -0.3; y1[2] = 0.21;
	x1[3] = -0.03;  y1[3] = -0.02;

	for (i = 0, t = 0; t < 1; i++, t = t + 0.01)
	{
		
		xt[i] = pow(1 - t, 3) * x[0] + 3 * t * pow(1 - t, 2) * x[1] + 3 * pow(t, 2) * (1 - t) * x[2] + pow(t, 3) * x[3];
		yt[i] = pow(1 - t, 3) * y[0] + 3 * t * pow(1 - t, 2) * y[1] + 3 * pow(t, 2) * (1 - t) * y[2] + pow(t, 3) * y[3];

		xt1[i] = pow(1 - t, 3) * x1[0] + 3 * t * pow(1 - t, 2) * x1[1] + 3 * pow(t, 2) * (1 - t) * x1[2] + pow(t, 3) * x1[3];
		yt1[i] = pow(1 - t, 3) * y1[0] + 3 * t * pow(1 - t, 2) * y1[1] + 3 * pow(t, 2) * (1 - t) * y1[2] + pow(t, 3) * y1[3];
	}
	//glPointSize(5);

	//धनुष्य वरचा भाग 
	glBegin(GL_TRIANGLE_STRIP);
	for (i = 0; i < 100; i++)
	{
		
		glColor3f(1.0, 0.0, 0.0);
		glVertex2f(VALUE_FROM_PERCENT(xt[i], percent) + x_pos, VALUE_FROM_PERCENT(yt[i], percent) + y_pos);
		glColor3f(1.0, 1.0, 0.0);
		glVertex2f(VALUE_FROM_PERCENT(xt1[i], percent) + x_pos, VALUE_FROM_PERCENT(yt1[i], percent) + y_pos);

	}
	glEnd();

	///////////////////////////

	x2[0] = 0.0; y2[0] = 0.06;
	x2[1] = 0.3; y2[1] = 0.1;
	x2[2] = 0.6; y2[2] = 0.02;
	x2[3] = 0.9; y2[3] = 0.0;

	x3[0] = 0.0; y3[0] = 0.08;
	x3[1] = 0.3; y3[1] = 0.21;
	x3[2] = 0.6; y3[2] = 0.21;
	x3[3] = 0.9; y3[3] = 0.0;

	for (i = 0, t = 0; t < 1; i++, t = t + 0.01)
	{

		xt2[i] = pow(1 - t, 3) * x2[0] + 3 * t * pow(1 - t, 2) * x2[1] + 3 * pow(t, 2) * (1 - t) * x2[2] + pow(t, 3) * x2[3];
		yt2[i] = pow(1 - t, 3) * y2[0] + 3 * t * pow(1 - t, 2) * y2[1] + 3 * pow(t, 2) * (1 - t) * y2[2] + pow(t, 3) * y2[3];

		xt3[i] = pow(1 - t, 3) * x3[0] + 3 * t * pow(1 - t, 2) * x3[1] + 3 * pow(t, 2) * (1 - t) * x3[2] + pow(t, 3) * x3[3];
		yt3[i] = pow(1 - t, 3) * y3[0] + 3 * t * pow(1 - t, 2) * y3[1] + 3 * pow(t, 2) * (1 - t) * y3[2] + pow(t, 3) * y3[3];
	}
	
	//धनुष्य खालचा  भाग 
	glBegin(GL_TRIANGLE_STRIP);
	for (i = 0; i < 100; i++)
	{
		glColor3f(1.0, 0.0, 0.0);
		glVertex2f(VALUE_FROM_PERCENT(xt2[i], percent) + x_pos, VALUE_FROM_PERCENT(yt2[i], percent) + y_pos);
		glColor3f(1.0, 1.0, 0.0);
		glVertex2f(VALUE_FROM_PERCENT(xt3[i], percent) + x_pos, VALUE_FROM_PERCENT(yt3[i], percent) + y_pos);

	}
	glEnd();

	// दोरी 

	glBegin(GL_QUADS);
	{

		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(VALUE_FROM_PERCENT(-0.9, percent) + x_pos, VALUE_FROM_PERCENT( 0.0, percent) + y_pos, 0.0);
		glVertex3f(VALUE_FROM_PERCENT(0.0, percent) + x_pos, VALUE_FROM_PERCENT( -0.05, percent) + y_pos, 0.0);
		glVertex3f(VALUE_FROM_PERCENT(0.0, percent) + x_pos, VALUE_FROM_PERCENT( -0.06, percent) + y_pos, 0.0);
		glVertex3f(VALUE_FROM_PERCENT(-0.9, percent) + x_pos, VALUE_FROM_PERCENT( -0.01, percent) + y_pos, 0.0);
        
		glVertex3f(VALUE_FROM_PERCENT(0.9, percent) + x_pos, VALUE_FROM_PERCENT( 0.0, percent) + y_pos, 0.0);
		glVertex3f(VALUE_FROM_PERCENT(0.0, percent) + x_pos, VALUE_FROM_PERCENT( -0.05, percent) + y_pos, 0.0);
		glVertex3f(VALUE_FROM_PERCENT(0.0, percent) + x_pos, VALUE_FROM_PERCENT( -0.06, percent) + y_pos, 0.0);
		glVertex3f(VALUE_FROM_PERCENT(0.9, percent) + x_pos, VALUE_FROM_PERCENT( -0.01, percent) + y_pos, 0.0);

	}
	glEnd();

	

}

void table(float x_pos, float y_pos, float percent)
{
	float xCircle=0.0,yCircle=0.0,xRedius=0.29,yRedius=0.1,theta=0.0;
	float x1Circle=0.0,y1Circle=0.0,x1Redius=0.29,y1Redius=0.1;
	int i,j;

    glColor3f(0.384313,0.192156,0.0);
    glBegin(GL_QUAD_STRIP);  
	{
	   for(j=0;j<360;j++)
	   {

		glVertex2f((x_pos),(y_pos-0.02)); //center	

		theta = j * 3.142 / 180;//convert into radian
		x1Circle = (x1Redius * (cos(theta)));
		y1Circle = (y1Redius * (sin(theta)));
		glVertex2f((x_pos+x1Circle),((y_pos-0.02)+y1Circle));
	    
	   }
	  
	}  
	glEnd();

	glBegin(GL_QUAD_STRIP);  
	{
	   for(i=0;i<360;i++)
	   {

		glColor3f(15.0f/255.0f, 83.0f/255.0f, 22.0f/255.0f);
		glVertex2f((x_pos),(y_pos)); //center	

		theta = i * 3.142 / 180;//convert into radian
		xCircle = (xRedius * (cos(theta)));
		yCircle = (yRedius * (sin(theta)));
		glColor3f(6.0f/255.0f, 58.0f/255.0f, 19.0f/255.0f);
		glVertex2f((x_pos+xCircle),((y_pos)+yCircle)); 
	    
	   }
	}

	glEnd();
	//outer blck line

    glColor3f(0.0,0.0,0.0);

	glBegin(GL_LINE_STRIP);  
	{
		
	   for(i=0;i<360;i++)
	   {

		theta = i * 3.142 / 180;//convert into radian
		xCircle = (xRedius * (cos(theta)));
		yCircle = (yRedius * (sin(theta)));
		glVertex2f((x_pos+xCircle),(y_pos+yCircle)); 
	    
	   }
	}
	glEnd();

	glBegin(GL_LINE_STRIP);  
	{
	   for(j=180;j<360;j++)
	   {

		//glVertex2f((x_pos),(y_pos-0.02)); //center	

		theta = j * 3.142 / 180;//convert into radian
		x1Circle = (x1Redius * (cos(theta)));
		y1Circle = (y1Redius * (sin(theta)));
		glVertex2f((x_pos+x1Circle),((y_pos-0.02)+y1Circle));
	    
	   }
	  
	}   
	
	glEnd();
}

void SwayamvarAnimation(void)
{
	HandsAnimation();
	GarlandAnimation();
	BracletAnimation();
}

void RamSitaVivah(void)
{
	// Animation
	SwayamvarAnimation();
	
	// Set it to Identity Matrix
	glLoadIdentity();

	// Translate Triangle backward by z
	glTranslatef(0.0f, 0.0f, -2.0f);

	glScalef(1.5f, 1.0f, 1.0f);

	glBindTexture(GL_TEXTURE_2D, texture_Raj_mahal);

	glColor4f(1.0f, 1.0f, 1.0f, 0.4f);

	// Triangle Drawing code
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);
	}
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);

	// Set it to Identity Matrix
	glLoadIdentity();

	// Translate Triangle backward by z
	glTranslatef(0.0f, 0.0f, -10.0f);
	
	Atharv_HandsOfRamAndSita();

	// Set it to Identity Matrix
	glLoadIdentity();

	// Translate Triangle backward by z
	glTranslatef(0.0f, -0.65f, -2.0f);

	glRotatef(-60.0f, 1.0f, 0.0f, 0.0f);

	table(0.0f, 0.0f, 10.0f);
	shivdhanushya(0.0f, 0.0f, 20.0f);
}