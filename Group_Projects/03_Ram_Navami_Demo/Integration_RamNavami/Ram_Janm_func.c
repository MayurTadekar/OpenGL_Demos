
// Win32 standard header
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES 1
#include <math.h>

// OpenGL Related Header Files
#include <gl/GL.h>
#include <gl/GLU.h>

// Custom header file
#include "OGL.h"
#include "Ram_Janm.h"

/* function definitions */
void Window_Amol(float x_pos, float y_pos, float percent)
{

	glBegin(GL_POLYGON);
	{
		glColor3f(0.7f, 0.8f, 1.0f);  // Left main Bar 
		glVertex2f(VALUE_FROM_PERCENT(0.2f, percent) + x_pos, VALUE_FROM_PERCENT(0.6f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.75f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.2f, percent) + x_pos, VALUE_FROM_PERCENT(0.6f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.2f, percent) + x_pos, VALUE_FROM_PERCENT(0.1f, percent) + y_pos);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex2f(VALUE_FROM_PERCENT(0.2f, percent) + x_pos, VALUE_FROM_PERCENT(0.1f, percent) + y_pos);
	}
	glEnd();
}

void Pillar_Amol(float x_pos, float y_pos, float percent)
{

	glBegin(GL_POLYGON);
	{

		glColor3f(1.0f, 1.0f, 0.7f);// Pillar
		glVertex2f(VALUE_FROM_PERCENT(0.6f, percent) + x_pos, VALUE_FROM_PERCENT(1.0f, percent) + y_pos);
		glColor3f(1.0f, 0.8f, 0.6f);
		glVertex2f(VALUE_FROM_PERCENT(-0.1f, percent) + x_pos, VALUE_FROM_PERCENT(1.0f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.2f, percent) + x_pos, VALUE_FROM_PERCENT(0.7f, percent) + y_pos);
		glColor3f(1.0f, 1.0f, 0.7f);
		glVertex2f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(0.7f, percent) + y_pos);
	}
	glEnd();

	glBegin(GL_POLYGON);
	{

		glColor3f(1.0f, 1.0f, 0.7f);// Pillar
		glVertex2f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(0.7f, percent) + y_pos);
		glColor3f(1.0f, 0.8f, 0.6f);
		glVertex2f(VALUE_FROM_PERCENT(0.2f, percent) + x_pos, VALUE_FROM_PERCENT(0.7f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.2f, percent) + x_pos, VALUE_FROM_PERCENT(-0.1f, percent) + y_pos);
		glColor3f(1.0f, 1.0f, 0.7f);
		glVertex2f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(-0.1f, percent) + y_pos);
	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		glColor3f(1.0f, 1.0f, 0.7f);// Pillar
		glVertex2f(VALUE_FROM_PERCENT(0.32f, percent) + x_pos, VALUE_FROM_PERCENT(0.66f, percent) + y_pos);
		glColor3f(1.0f, 0.8f, 0.6f);
		glVertex2f(VALUE_FROM_PERCENT(0.18f, percent) + x_pos, VALUE_FROM_PERCENT(0.66f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.18f, percent) + x_pos, VALUE_FROM_PERCENT(0.64f, percent) + y_pos);
		glColor3f(1.0f, 1.0f, 0.7f);
		glVertex2f(VALUE_FROM_PERCENT(0.32f, percent) + x_pos, VALUE_FROM_PERCENT(0.64f, percent) + y_pos);
	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		glColor3f(1.0f, 1.0f, 0.7f);// Pillar
		glVertex2f(VALUE_FROM_PERCENT(0.32f, percent) + x_pos, VALUE_FROM_PERCENT(-0.04f, percent) + y_pos);
		glColor3f(1.0f, 0.8f, 0.6f);
		glVertex2f(VALUE_FROM_PERCENT(0.18f, percent) + x_pos, VALUE_FROM_PERCENT(-0.04f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.18f, percent) + x_pos, VALUE_FROM_PERCENT(-0.06f, percent) + y_pos);
		glColor3f(1.0f, 1.0f, 0.7f);
		glVertex2f(VALUE_FROM_PERCENT(0.32f, percent) + x_pos, VALUE_FROM_PERCENT(-0.06f, percent) + y_pos);
	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		glColor3f(1.0f, 1.0f, 0.7f);// Pillar
		glVertex2f(VALUE_FROM_PERCENT(0.32f, percent) + x_pos, VALUE_FROM_PERCENT(-0.07f, percent) + y_pos);
		glColor3f(1.0f, 0.8f, 0.6f);
		glVertex2f(VALUE_FROM_PERCENT(0.18f, percent) + x_pos, VALUE_FROM_PERCENT(-0.07f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.18f, percent) + x_pos, VALUE_FROM_PERCENT(-0.12f, percent) + y_pos);
		glColor3f(1.0f, 1.0f, 0.7f);
		glVertex2f(VALUE_FROM_PERCENT(0.32f, percent) + x_pos, VALUE_FROM_PERCENT(-0.12f, percent) + y_pos);
	}
	glEnd();

}

void Aai_Amol(float x_pos, float y_pos, float percent)
{


	glBegin(GL_POLYGON);
	{
		glColor3f(0.0f, 1.0f, 0.0f);  // Left leg
		glVertex2f(VALUE_FROM_PERCENT(-0.22f, percent) + x_pos, VALUE_FROM_PERCENT(-0.32f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.18f, percent) + x_pos, VALUE_FROM_PERCENT(-0.32f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.15f, percent) + x_pos, VALUE_FROM_PERCENT(-0.34f, percent) + y_pos);

		glVertex2f(VALUE_FROM_PERCENT(-0.15f, percent) + x_pos, VALUE_FROM_PERCENT(-0.37f, percent) + y_pos);

		glVertex2f(VALUE_FROM_PERCENT(-0.16f, percent) + x_pos, VALUE_FROM_PERCENT(-0.42f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.26f, percent) + x_pos, VALUE_FROM_PERCENT(-0.44f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.24f, percent) + x_pos, VALUE_FROM_PERCENT(-0.35f, percent) + y_pos);
	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		glColor3f(1.0f, 0.1f, 0.1f);  //  shoulder Odhani front

		glVertex2f(VALUE_FROM_PERCENT(-0.2f, percent) + x_pos, VALUE_FROM_PERCENT(-0.28f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.25f, percent) + x_pos, VALUE_FROM_PERCENT(-0.34f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.14f, percent) + x_pos, VALUE_FROM_PERCENT(-0.45f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.1f, percent) + x_pos, VALUE_FROM_PERCENT(-0.4f, percent) + y_pos);

	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		glColor3f(1.0f, 1.0f, 1.0f);  // HAND

		glVertex2f(VALUE_FROM_PERCENT(-0.15f, percent) + x_pos, VALUE_FROM_PERCENT(-0.27f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.09f, percent) + x_pos, VALUE_FROM_PERCENT(-0.21f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.06f, percent) + x_pos, VALUE_FROM_PERCENT(-0.04f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.09f, percent) + x_pos, VALUE_FROM_PERCENT(-0.04f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.09f, percent) + x_pos, VALUE_FROM_PERCENT(-0.04f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.09f, percent) + x_pos, VALUE_FROM_PERCENT(-0.14f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.15f, percent) + x_pos, VALUE_FROM_PERCENT(-0.19f, percent) + y_pos);
	}
	glEnd();



	glBegin(GL_POLYGON);
	{
		glColor3f(1.0f, 1.0f, 1.0f);  // Hadacha panja

		glVertex2f(VALUE_FROM_PERCENT(-0.06f, percent) + x_pos, VALUE_FROM_PERCENT(-0.03f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.11f, percent) + x_pos, VALUE_FROM_PERCENT(-0.02f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.11f, percent) + x_pos, VALUE_FROM_PERCENT(-0.04f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.12f, percent) + x_pos, VALUE_FROM_PERCENT(-0.05f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.12f, percent) + x_pos, VALUE_FROM_PERCENT(-0.06f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.06f, percent) + x_pos, VALUE_FROM_PERCENT(-0.07f, percent) + y_pos);

	}
	glEnd();


	glBegin(GL_LINES);
	{
		glColor3f(0.2f, 0.4f, 0.0f);  // Bangdi 1 top
		glVertex2f(VALUE_FROM_PERCENT(-0.1f, percent) + x_pos, VALUE_FROM_PERCENT(-0.06f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.06f, percent) + x_pos, VALUE_FROM_PERCENT(-0.07f, percent) + y_pos);
	}
	glEnd();

	glBegin(GL_LINES);
	{
		glColor3f(0.2f, 0.4f, 0.0f);  // Bangdi 2 bottom
		glVertex2f(VALUE_FROM_PERCENT(-0.1f, percent) + x_pos, VALUE_FROM_PERCENT(-0.07f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.06f, percent) + x_pos, VALUE_FROM_PERCENT(-0.08f, percent) + y_pos);
	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		glColor3f(0.9f, 0.9f, 0.0f);  // HAND shoulder

		glVertex2f(VALUE_FROM_PERCENT(-0.24f, percent) + x_pos, VALUE_FROM_PERCENT(-0.32f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.15f, percent) + x_pos, VALUE_FROM_PERCENT(-0.27f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.15f, percent) + x_pos, VALUE_FROM_PERCENT(-0.19f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.23f, percent) + x_pos, VALUE_FROM_PERCENT(-0.23f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.22f, percent) + x_pos, VALUE_FROM_PERCENT(-0.31f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.25f, percent) + x_pos, VALUE_FROM_PERCENT(-0.39f, percent) + y_pos);

	}
	glEnd();


	glBegin(GL_POLYGON);
	{
		glColor3f(1.0f, 0.1f, 0.1f);  //  shoulder Odhani back

		glVertex2f(VALUE_FROM_PERCENT(-0.26f, percent) + x_pos, VALUE_FROM_PERCENT(-0.22f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.3f, percent) + x_pos, VALUE_FROM_PERCENT(-0.3f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.38f, percent) + x_pos, VALUE_FROM_PERCENT(-0.4f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.25f, percent) + x_pos, VALUE_FROM_PERCENT(-0.4f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.23f, percent) + x_pos, VALUE_FROM_PERCENT(-0.3f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.23f, percent) + x_pos, VALUE_FROM_PERCENT(-0.23f, percent) + y_pos);
	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		glColor3f(1.0f, 1.0f, 1.0f);  //  path
		glVertex2f(VALUE_FROM_PERCENT(-0.47f, percent) + x_pos, VALUE_FROM_PERCENT(-0.4f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.47f, percent) + x_pos, VALUE_FROM_PERCENT(-0.43f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.26f, percent) + x_pos, VALUE_FROM_PERCENT(-0.43f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.26f, percent) + x_pos, VALUE_FROM_PERCENT(-0.4f, percent) + y_pos);

	}
	glEnd();


	glBegin(GL_POLYGON);
	{
		glColor3f(1.0f, 1.0f, 1.0f);  // right leg
		glVertex2f(VALUE_FROM_PERCENT(-0.3f, percent) + x_pos, VALUE_FROM_PERCENT(-0.6f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.35f, percent) + x_pos, VALUE_FROM_PERCENT(-0.59f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.35f, percent) + x_pos, VALUE_FROM_PERCENT(-0.62f, percent) + y_pos);

		glVertex2f(VALUE_FROM_PERCENT(-0.31f, percent) + x_pos, VALUE_FROM_PERCENT(-0.67f, percent) + y_pos);

		glVertex2f(VALUE_FROM_PERCENT(-0.28f, percent) + x_pos, VALUE_FROM_PERCENT(-0.7f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.27f, percent) + x_pos, VALUE_FROM_PERCENT(-0.7f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.29f, percent) + x_pos, VALUE_FROM_PERCENT(-0.67f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.29f, percent) + x_pos, VALUE_FROM_PERCENT(-0.64f, percent) + y_pos);
	}
	glEnd();



	glBegin(GL_POLYGON);
	{
		glColor3f(0.0f, 1.0f, 0.0f);  //  lower body
		glVertex2f(VALUE_FROM_PERCENT(-0.47f, percent) + x_pos, VALUE_FROM_PERCENT(-0.43f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.26f, percent) + x_pos, VALUE_FROM_PERCENT(-0.43f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.13f, percent) + x_pos, VALUE_FROM_PERCENT(-0.4f, percent) + y_pos);

		glVertex2f(VALUE_FROM_PERCENT(-0.11f, percent) + x_pos, VALUE_FROM_PERCENT(-0.43f, percent) + y_pos);

		glVertex2f(VALUE_FROM_PERCENT(-0.18f, percent) + x_pos, VALUE_FROM_PERCENT(-0.6f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.26f, percent) + x_pos, VALUE_FROM_PERCENT(-0.68f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.45f, percent) + x_pos, VALUE_FROM_PERCENT(-0.5f, percent) + y_pos);
	}
	glEnd();


	glBegin(GL_LINES);
	{
		glColor3f(0.5f, 0.5f, 0.6f);  // right leg design
		glVertex2f(VALUE_FROM_PERCENT(-0.18f, percent) + x_pos, VALUE_FROM_PERCENT(-0.48f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.3f, percent) + x_pos, VALUE_FROM_PERCENT(-0.55f, percent) + y_pos);

	}
	glEnd();


	glBegin(GL_POLYGON);
	{
		glColor3f(1.0f, 0.1f, 0.1f);  //  shoulder Odhani
		glVertex2f(VALUE_FROM_PERCENT(-0.38f, percent) + x_pos, VALUE_FROM_PERCENT(-0.4f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.43f, percent) + x_pos, VALUE_FROM_PERCENT(-0.5f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.3f, percent) + x_pos, VALUE_FROM_PERCENT(-0.5f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.25f, percent) + x_pos, VALUE_FROM_PERCENT(-0.4f, percent) + y_pos);

	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		glVertex2f(VALUE_FROM_PERCENT(-0.43f, percent) + x_pos, VALUE_FROM_PERCENT(-0.5f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.58f, percent) + x_pos, VALUE_FROM_PERCENT(-0.58f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.45f, percent) + x_pos, VALUE_FROM_PERCENT(-0.7f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.41f, percent) + x_pos, VALUE_FROM_PERCENT(-0.65f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.35f, percent) + x_pos, VALUE_FROM_PERCENT(-0.6f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.3f, percent) + x_pos, VALUE_FROM_PERCENT(-0.5f, percent) + y_pos);

	}
	glEnd();

	glLineWidth(2);
	glBegin(GL_LINES);
	{
		glColor3f(1.0f, 1.0f, 0.0f);   //  odhani border

		glVertex2f(VALUE_FROM_PERCENT(-0.43f, percent) + x_pos, VALUE_FROM_PERCENT(-0.5f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.34f, percent) + x_pos, VALUE_FROM_PERCENT(-0.59f, percent) + y_pos);

	}
	glEnd();

	glLineWidth(3);
	glBegin(GL_LINES);
	{
		glColor3f(1.0f, 1.0f, 0.0f);   //  odhani border

		glVertex2f(VALUE_FROM_PERCENT(-0.45f, percent) + x_pos, VALUE_FROM_PERCENT(-0.51f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.36f, percent) + x_pos, VALUE_FROM_PERCENT(-0.6f, percent) + y_pos);

	}
	glEnd();

	glLineWidth(3);
	glBegin(GL_LINES);
	{
		glColor3f(1.0f, 1.0f, 0.0f);   //  odhani border

		glVertex2f(VALUE_FROM_PERCENT(-0.47f, percent) + x_pos, VALUE_FROM_PERCENT(-0.52f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.38f, percent) + x_pos, VALUE_FROM_PERCENT(-0.61f, percent) + y_pos);

	}
	glEnd();


	glLineWidth(5);
	glBegin(GL_LINES);
	{
		glColor3f(1.0f, 1.0f, 0.0f);   //  odhani border

		glVertex2f(VALUE_FROM_PERCENT(-0.55f, percent) + x_pos, VALUE_FROM_PERCENT(-0.56f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.43f, percent) + x_pos, VALUE_FROM_PERCENT(-0.68f, percent) + y_pos);

	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		glColor3f(1.0f, 1.0f, 1.0f);   //  Face


		glVertex2f(VALUE_FROM_PERCENT(-0.22f, percent) + x_pos, VALUE_FROM_PERCENT(-0.09f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.23f, percent) + x_pos, VALUE_FROM_PERCENT(-0.1f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.24f, percent) + x_pos, VALUE_FROM_PERCENT(-0.12f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.25f, percent) + x_pos, VALUE_FROM_PERCENT(-0.15f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.26f, percent) + x_pos, VALUE_FROM_PERCENT(-0.18f, percent) + y_pos);

		glVertex2f(VALUE_FROM_PERCENT(-0.21f, percent) + x_pos, VALUE_FROM_PERCENT(-0.13f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.21f, percent) + x_pos, VALUE_FROM_PERCENT(-0.16f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.21f, percent) + x_pos, VALUE_FROM_PERCENT(-0.16f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.22f, percent) + x_pos, VALUE_FROM_PERCENT(-0.18f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.28f, percent) + x_pos, VALUE_FROM_PERCENT(-0.2f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.26f, percent) + x_pos, VALUE_FROM_PERCENT(-0.23f, percent) + y_pos);
	}
	glEnd();

	glPointSize(2);

	glBegin(GL_POINTS);
	{
		glColor3f(1.0f, 0.0f, 0.0f);  // kanatale
		glVertex2f(VALUE_FROM_PERCENT(-0.24f, percent) + x_pos, VALUE_FROM_PERCENT(-0.18f, percent) + y_pos);
	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		glColor3f(0.9f, 0.9f, 0.0f);  // kanatale
		glVertex2f(VALUE_FROM_PERCENT(-0.24f, percent) + x_pos, VALUE_FROM_PERCENT(-0.18f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.25f, percent) + x_pos, VALUE_FROM_PERCENT(-0.2f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.23f, percent) + x_pos, VALUE_FROM_PERCENT(-0.2f, percent) + y_pos);
	}
	glEnd();

	glPointSize(2);
	glBegin(GL_POINTS);
	{
		glColor3f(1.0f, 0.0f, 0.0f);  // kanatale
		glVertex2f(VALUE_FROM_PERCENT(-0.25f, percent) + x_pos, VALUE_FROM_PERCENT(-0.2f, percent) + y_pos);
	}
	glEnd();

	glBegin(GL_POINTS);
	{
		glColor3f(1.0f, 0.0f, 0.0f);  // kanatale
		glVertex2f(VALUE_FROM_PERCENT(-0.23f, percent) + x_pos, VALUE_FROM_PERCENT(-0.2f, percent) + y_pos);
	}
	glEnd();

	glBegin(GL_POINTS);
	{
		glVertex2f(VALUE_FROM_PERCENT(-0.24f, percent) + x_pos, VALUE_FROM_PERCENT(-0.2f, percent) + y_pos);
	}
	glEnd();

	glLineWidth(1);
	glBegin(GL_LINES);
	{
		glColor3f(0.0f, 0.0f, 0.0f);   //  Eye line

		glVertex2f(VALUE_FROM_PERCENT(-0.215f, percent) + x_pos, VALUE_FROM_PERCENT(-0.13f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.21f, percent) + x_pos, VALUE_FROM_PERCENT(-0.13f, percent) + y_pos);

	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		glColor3f(0.6f, 0.2f, 0.0f);   //  Head

		glVertex2f(VALUE_FROM_PERCENT(-0.22f, percent) + x_pos, VALUE_FROM_PERCENT(-0.09f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.25f, percent) + x_pos, VALUE_FROM_PERCENT(-0.06f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.3f, percent) + x_pos, VALUE_FROM_PERCENT(-0.05f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.32f, percent) + x_pos, VALUE_FROM_PERCENT(-0.08f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.33f, percent) + x_pos, VALUE_FROM_PERCENT(-0.1f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.33f, percent) + x_pos, VALUE_FROM_PERCENT(-0.15f, percent) + y_pos);

		glVertex2f(VALUE_FROM_PERCENT(-0.26f, percent) + x_pos, VALUE_FROM_PERCENT(-0.19f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.25f, percent) + x_pos, VALUE_FROM_PERCENT(-0.15f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.24f, percent) + x_pos, VALUE_FROM_PERCENT(-0.12f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.23f, percent) + x_pos, VALUE_FROM_PERCENT(-0.1f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.22f, percent) + x_pos, VALUE_FROM_PERCENT(-0.09f, percent) + y_pos);

	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		glColor3f(1.6f, 0.4f, 1.0f);   //  Head

		glVertex2f(VALUE_FROM_PERCENT(-0.33f, percent) + x_pos, VALUE_FROM_PERCENT(-0.13f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.34f, percent) + x_pos, VALUE_FROM_PERCENT(-0.14f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.26f, percent) + x_pos, VALUE_FROM_PERCENT(-0.21f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.25f, percent) + x_pos, VALUE_FROM_PERCENT(-0.2f, percent) + y_pos);

	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		glColor3f(0.9f, 0.9f, 0.0f);    //  Left Shoulder

		glVertex2f(VALUE_FROM_PERCENT(-0.26f, percent) + x_pos, VALUE_FROM_PERCENT(-0.22f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.37f, percent) + x_pos, VALUE_FROM_PERCENT(-0.17f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.4f, percent) + x_pos, VALUE_FROM_PERCENT(-0.17f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.42f, percent) + x_pos, VALUE_FROM_PERCENT(-0.17f, percent) + y_pos);

		glVertex2f(VALUE_FROM_PERCENT(-0.43f, percent) + x_pos, VALUE_FROM_PERCENT(-0.2f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.45f, percent) + x_pos, VALUE_FROM_PERCENT(-0.25f, percent) + y_pos);

		glVertex2f(VALUE_FROM_PERCENT(-0.45f, percent) + x_pos, VALUE_FROM_PERCENT(-0.3f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.47f, percent) + x_pos, VALUE_FROM_PERCENT(-0.4f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.38f, percent) + x_pos, VALUE_FROM_PERCENT(-0.4f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.27f, percent) + x_pos, VALUE_FROM_PERCENT(-0.22f, percent) + y_pos);

	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		glColor3f(0.6f, 0.2f, 0.0f);   //  Hair

		glVertex2f(VALUE_FROM_PERCENT(-0.33f, percent) + x_pos, VALUE_FROM_PERCENT(-0.15f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.35f, percent) + x_pos, VALUE_FROM_PERCENT(-0.15f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.37f, percent) + x_pos, VALUE_FROM_PERCENT(-0.17f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.36f, percent) + x_pos, VALUE_FROM_PERCENT(-0.19f, percent) + y_pos);

		glVertex2f(VALUE_FROM_PERCENT(-0.35f, percent) + x_pos, VALUE_FROM_PERCENT(-0.22f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.33f, percent) + x_pos, VALUE_FROM_PERCENT(-0.22f, percent) + y_pos);

		glVertex2f(VALUE_FROM_PERCENT(-0.3f, percent) + x_pos, VALUE_FROM_PERCENT(-0.22f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.28f, percent) + x_pos, VALUE_FROM_PERCENT(-0.21f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(-0.26f, percent) + x_pos, VALUE_FROM_PERCENT(-0.21f, percent) + y_pos);

	}
	glEnd();





}


void Palna_SupportingBodyLeft_Amol(float x_pos, float y_pos, float percent)
{


	//3
	glBegin(GL_POLYGON);
	{
		glColor3f(0.8f, 0.0f, 0.0f);  // Left main Bar 
		glVertex2f(VALUE_FROM_PERCENT(0.12f, percent) + x_pos, VALUE_FROM_PERCENT(-0.0f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.12f, percent) + x_pos, VALUE_FROM_PERCENT(-0.5f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.14f, percent) + x_pos, VALUE_FROM_PERCENT(-0.5f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.14f, percent) + x_pos, VALUE_FROM_PERCENT(-0.0f, percent) + y_pos);

	}
	glEnd();
	//4
	glBegin(GL_POLYGON);
	{
		glColor3f(0.8f, 0.0f, 0.0f);
		glVertex2f(VALUE_FROM_PERCENT(0.07f, percent) + x_pos, VALUE_FROM_PERCENT(-0.51f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.07f, percent) + x_pos, VALUE_FROM_PERCENT(-0.54f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.17f, percent) + x_pos, VALUE_FROM_PERCENT(-0.5f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.17f, percent) + x_pos, VALUE_FROM_PERCENT(-0.47f, percent) + y_pos);

	}
	glEnd();

	glPointSize(10);
	//5
	glBegin(GL_POINTS);
	{
		glColor3f(0.0f, 0.0f, 0.0f);  // left PAYA front part
		glVertex2f(VALUE_FROM_PERCENT(0.07f, percent) + x_pos, VALUE_FROM_PERCENT(-0.52f, percent) + y_pos);
	}
	glEnd();

}

void Palna_Amol(float x_pos, float y_pos, float percent)
{


	//glRotatef(ASN_AngleTriangle, 0.0f, 0.0f, 0.1f);


	//1
	glLineWidth(2);
	glBegin(GL_LINES);
	{
		//glRotatef(ASN_AngleTriangle, 0.0f, 0.0f, 0.0f);
		glColor3f(0.4f, 0.1f, 0.1f);   // Hanging rope left back
		glVertex2f(VALUE_FROM_PERCENT(0.16f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos);
		//glRotatef(ASN_AngleTriangle, 0.0f, 0.0f, 0.1f);
		glVertex2f(VALUE_FROM_PERCENT(0.18f, percent) + x_pos, VALUE_FROM_PERCENT(-0.22f, percent) + y_pos);
	}
	glEnd();



	//2
	glLineWidth(2);
	glBegin(GL_LINES);
	{
		glColor3f(0.4f, 0.1f, 0.1f);   // Hanging rope right back
		//glRotatef(ASN_AngleTriangle, 0.0f, 0.0f, 0.0f);
		glVertex2f(VALUE_FROM_PERCENT(0.42f, percent) + x_pos, VALUE_FROM_PERCENT(-0.05f, percent) + y_pos);
		//glRotatef(ASN_AngleTriangle, 0.0f, 0.0f, 0.1f);
		glVertex2f(VALUE_FROM_PERCENT(0.48f, percent) + x_pos, VALUE_FROM_PERCENT(-0.28f, percent) + y_pos);
	}
	glEnd();



	//7
	glLineWidth(2);
	glBegin(GL_LINES);
	{
		glColor3f(0.4f, 0.1f, 0.1f);  // Hanging rope left front
		glVertex2f(VALUE_FROM_PERCENT(0.16f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos, VALUE_FROM_PERCENT(-0.21f, percent) + y_pos);
	}
	glEnd();


	//9



	glBegin(GL_POLYGON);
	{
		glColor3f(1.0f, 0.0f, 0.0f);  // Left body top side 
		glVertex2f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos, VALUE_FROM_PERCENT(-0.2f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos, VALUE_FROM_PERCENT(-0.22f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.18f, percent) + x_pos, VALUE_FROM_PERCENT(-0.24f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.18f, percent) + x_pos, VALUE_FROM_PERCENT(-0.22f, percent) + y_pos);

	}
	glEnd();

	//10

	glBegin(GL_POLYGON);
	{
		glColor3f(0.8f, 0.0f, 0.0f);  // middle back body top side 
		glVertex2f(VALUE_FROM_PERCENT(0.18f, percent) + x_pos, VALUE_FROM_PERCENT(-0.22f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.18f, percent) + x_pos, VALUE_FROM_PERCENT(-0.24f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.48f, percent) + x_pos, VALUE_FROM_PERCENT(-0.3f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.48f, percent) + x_pos, VALUE_FROM_PERCENT(-0.28f, percent) + y_pos);

	}
	glEnd();




	//Tej Kiran from Palna
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	// Triangle Drawing code

	for (float i = 0.0f; i < 0.17f; i = i + 0.01f)
	{
		glBegin(GL_TRIANGLES);
		glColor4f(1.0f, 1.0f, 0.7f, 0.1f);
		glVertex3f(VALUE_FROM_PERCENT(i + -0.12f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f - i, percent) + y_pos, 0.0f);
		//left bottom
		glColor4f(1.0f, 1.0f, 0.7f, 0.1f);
		glVertex3f(VALUE_FROM_PERCENT(i + -0.15f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f - i, percent) + y_pos, 0.0f);
		////Right bottom
		glColor4f(1.0f, 0.8f, 0.0f, 1.0f);
		glVertex3f(VALUE_FROM_PERCENT(0.2f, percent) + x_pos, VALUE_FROM_PERCENT(-0.4f, percent) + y_pos, 0.0f);
		glEnd();
	}

	//11
	glBegin(GL_POLYGON);
	{
		glColor3f(0.6f, 0.4f, 0.2f);  // Right full body 
		glVertex2f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(-0.26f, percent) + y_pos);

		glVertex2f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(-0.48f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.48f, percent) + x_pos, VALUE_FROM_PERCENT(-0.5f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.48f, percent) + x_pos, VALUE_FROM_PERCENT(-0.28f, percent) + y_pos);

	}
	glEnd();
	//12
	glBegin(GL_POLYGON);
	{
		glColor3f(0.9f, 0.6f, 0.0f);  // Right body top side 
		glVertex2f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(-0.26f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(-0.28f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.48f, percent) + x_pos, VALUE_FROM_PERCENT(-0.3f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.48f, percent) + x_pos, VALUE_FROM_PERCENT(-0.28f, percent) + y_pos);

	}
	glEnd();
	//13
	glBegin(GL_POLYGON);
	{
		glColor3f(0.6f, 0.4f, 0.2f);   // middle full body 
		glVertex2f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos, VALUE_FROM_PERCENT(-0.2f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos, VALUE_FROM_PERCENT(-0.42f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(-0.48f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(-0.26f, percent) + y_pos);

	}
	glEnd();
	//14

	glBegin(GL_POLYGON);
	{
		glColor3f(0.9f, 0.6f, 0.0f);   // middle front body top side 
		glVertex2f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos, VALUE_FROM_PERCENT(-0.2f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos, VALUE_FROM_PERCENT(-0.22f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(-0.28f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(-0.26f, percent) + y_pos);

	}
	glEnd();

	//15
	glBegin(GL_POLYGON);
	{
		glColor3f(0.9f, 0.6f, 0.0f); // Right body bottom side 
		glVertex2f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(-0.46f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(-0.48f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.48f, percent) + x_pos, VALUE_FROM_PERCENT(-0.5f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.48f, percent) + x_pos, VALUE_FROM_PERCENT(-0.48f, percent) + y_pos);

	}
	glEnd();
	//16
	glBegin(GL_POLYGON);
	{
		glColor3f(0.9f, 0.6f, 0.0f); // middle front body bottom side 
		glVertex2f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos, VALUE_FROM_PERCENT(-0.4f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos, VALUE_FROM_PERCENT(-0.42f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(-0.48f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(-0.46f, percent) + y_pos);

	}
	glEnd();
	//17

	glBegin(GL_POLYGON);
	{
		glColor3f(1.0f, 1.0f, 1.0f);  // Right body top 2 side 
		glVertex2f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(-0.32f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(-0.34f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.48f, percent) + x_pos, VALUE_FROM_PERCENT(-0.36f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.48f, percent) + x_pos, VALUE_FROM_PERCENT(-0.34f, percent) + y_pos);

	}
	glEnd();
	//18
	glBegin(GL_POLYGON);
	{
		glColor3f(1.0f, 1.0f, 1.0f);  // middle front body top 2 side 
		glVertex2f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos, VALUE_FROM_PERCENT(-0.26f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos, VALUE_FROM_PERCENT(-0.28f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(-0.34f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(-0.32f, percent) + y_pos);

	}
	glEnd();

	//19
	glBegin(GL_POLYGON);
	{
		glColor3f(1.0f, 1.0f, 1.0f);  // Right body top 3 side 
		glVertex2f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(-0.4f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(-0.42f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.48f, percent) + x_pos, VALUE_FROM_PERCENT(-0.44f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.48f, percent) + x_pos, VALUE_FROM_PERCENT(-0.42f, percent) + y_pos);

	}
	glEnd();
	//20
	glBegin(GL_POLYGON);
	{
		glColor3f(1.0f, 1.0f, 1.0f);  // middle front body top 3 side 
		glVertex2f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos, VALUE_FROM_PERCENT(-0.34f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos, VALUE_FROM_PERCENT(-0.36f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(-0.42f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(-0.4f, percent) + y_pos);

	}
	glEnd();
	//21
	glBegin(GL_POLYGON);
	{
		glColor3f(0.8f, 0.0f, 0.0f);  // Left body support 
		glVertex2f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos, VALUE_FROM_PERCENT(-0.2f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos, VALUE_FROM_PERCENT(-0.42f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.03f, percent) + x_pos, VALUE_FROM_PERCENT(-0.42f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.03f, percent) + x_pos, VALUE_FROM_PERCENT(-0.2f, percent) + y_pos);

	}
	glEnd();
	//22
	glPointSize(7);
	glBegin(GL_POINTS);
	{
		glColor3f(1.0f, 1.0f, 0.0f);  // Hanging rope left front
		glVertex2f(VALUE_FROM_PERCENT(0.025f, percent) + x_pos, VALUE_FROM_PERCENT(-0.21f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.18f, percent) + x_pos, VALUE_FROM_PERCENT(-0.22f, percent) + y_pos);
	}
	glEnd();
	//23
	glBegin(GL_POLYGON);
	{
		glColor3f(0.8f, 0.0f, 0.0f);  // middle front body support 
		glVertex2f(VALUE_FROM_PERCENT(0.29f, percent) + x_pos, VALUE_FROM_PERCENT(-0.26f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.29f, percent) + x_pos, VALUE_FROM_PERCENT(-0.48f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.32f, percent) + x_pos, VALUE_FROM_PERCENT(-0.48f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.32f, percent) + x_pos, VALUE_FROM_PERCENT(-0.26f, percent) + y_pos);

	}
	glEnd();
	//24
	glLineWidth(2);
	glBegin(GL_LINES);
	{
		glColor3f(0.4f, 0.1f, 0.1f);  // Hanging rope right front
		glVertex2f(VALUE_FROM_PERCENT(0.42f, percent) + x_pos, VALUE_FROM_PERCENT(-0.05f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(-0.26f, percent) + y_pos);
	}
	glEnd();

	//26
	glPointSize(7);
	glBegin(GL_POINTS);
	{
		glColor3f(1.0f, 1.0f, 0.0f);  // Hanging rope front golden support
		glVertex2f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(-0.26f, percent) + y_pos);
	}
	glEnd();
	//27
	glBegin(GL_POLYGON);
	{
		glColor3f(0.8f, 0.0f, 0.0f);  // Right back body support 
		glVertex2f(VALUE_FROM_PERCENT(0.48f, percent) + x_pos, VALUE_FROM_PERCENT(-0.28f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.48f, percent) + x_pos, VALUE_FROM_PERCENT(-0.5f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.49f, percent) + x_pos, VALUE_FROM_PERCENT(-0.5f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.49f, percent) + x_pos, VALUE_FROM_PERCENT(-0.28f, percent) + y_pos);

	}
	glEnd();
	//28
	glPointSize(7);
	glBegin(GL_POINTS);
	{
		glColor3f(1.0f, 1.0f, 0.0f);  // Hanging rope right back golden support
		glVertex2f(VALUE_FROM_PERCENT(0.48f, percent) + x_pos, VALUE_FROM_PERCENT(-0.28f, percent) + y_pos);
	}
	glEnd();

	//32
	glBegin(GL_LINES);
	{
		glColor3f(1.0f, 0.0f, 0.0f);  // Palanyachi dori
		glVertex2f(VALUE_FROM_PERCENT(-0.07f, percent) + x_pos, VALUE_FROM_PERCENT(-0.05f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.18f, percent) + x_pos, VALUE_FROM_PERCENT(-0.25f, percent) + y_pos);
	}
	glEnd();

	glBegin(GL_LINES);
	{
		glColor3f(1.0f, 0.0f, 0.0f);  // Palanyachi dori knot
		glVertex2f(VALUE_FROM_PERCENT(0.18f, percent) + x_pos, VALUE_FROM_PERCENT(-0.23f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.18f, percent) + x_pos, VALUE_FROM_PERCENT(-0.26f, percent) + y_pos);
	}
	glEnd();

}


void Palna_SupportingBodyRight_Amol(float x_pos, float y_pos, float percent)
{
	//6
	glBegin(GL_POLYGON);
	{
		glColor3f(0.5f, 0.2f, 0.0f);  // Top main support Bar 
		glVertex2f(VALUE_FROM_PERCENT(0.12f, percent) + x_pos, VALUE_FROM_PERCENT(-0.0f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.12f, percent) + x_pos, VALUE_FROM_PERCENT(-0.03f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.47f, percent) + x_pos, VALUE_FROM_PERCENT(-0.08f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.47f, percent) + x_pos, VALUE_FROM_PERCENT(-0.05f, percent) + y_pos);

	}
	glEnd();

	//8
	glPointSize(15);


	glBegin(GL_POINTS);
	{
		glColor3f(1.0f, 1.0f, 0.0f);  // Hanging rope left front
		glVertex2f(VALUE_FROM_PERCENT(0.16f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos);
	}
	glEnd();

	//25
	glPointSize(15);

	glBegin(GL_POINTS);
	{
		glColor3f(1.0f, 1.0f, 0.0f);  // Hanging rope left front
		glVertex2f(VALUE_FROM_PERCENT(0.42f, percent) + x_pos, VALUE_FROM_PERCENT(-0.04f, percent) + y_pos);
	}
	glEnd();
	//29
	glBegin(GL_POLYGON);
	{
		glColor3f(0.8f, 0.0f, 0.0f);   // Right main Bar 
		glVertex2f(VALUE_FROM_PERCENT(0.45f, percent) + x_pos, VALUE_FROM_PERCENT(-0.05f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.45f, percent) + x_pos, VALUE_FROM_PERCENT(-0.6f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.47f, percent) + x_pos, VALUE_FROM_PERCENT(-0.6f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.47f, percent) + x_pos, VALUE_FROM_PERCENT(-0.05f, percent) + y_pos);

	}
	glEnd();

	//30
	glBegin(GL_POLYGON);
	{
		glColor3f(0.8f, 0.0f, 0.0f);  // Right paya
		glVertex2f(VALUE_FROM_PERCENT(0.4f, percent) + x_pos, VALUE_FROM_PERCENT(-0.62f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.4f, percent) + x_pos, VALUE_FROM_PERCENT(-0.65f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.51f, percent) + x_pos, VALUE_FROM_PERCENT(-0.6f, percent) + y_pos);
		glVertex2f(VALUE_FROM_PERCENT(0.51f, percent) + x_pos, VALUE_FROM_PERCENT(-0.57f, percent) + y_pos);

	}
	glEnd();
	//31
	glPointSize(10);

	glBegin(GL_POINTS);
	{
		glColor3f(0.0f, 0.0f, 0.0f);  // left PAYA front part
		glVertex2f(VALUE_FROM_PERCENT(0.4f, percent) + x_pos, VALUE_FROM_PERCENT(-0.63f, percent) + y_pos);
	}
	glEnd();


}

void Background(float x_pos, float y_pos, float percent)
{
	// Set it to identity Matrix
	//glLoadIdentity();

	// Translate Triangle backwords by z
	//glTranslatef(0.0f, 0.0f, -0.10f);

	//Back wall
	glBegin(GL_QUADS);
	{
		// Background color
		glColor3f(1.0f, 1.0f, 0.9f);
		glVertex2f(0.9f, 1.0f);
		glVertex2f(-0.9f, 1.0f);
		glVertex2f(-0.9f, 0.0f);
		
		glVertex2f(0.9f, 0.0f);
	}
	glEnd();

	//// Set it to identity Matrix
	//glLoadIdentity();

	//// Translate Triangle backwords by z
	//glTranslatef(0.0f, 0.0f, -0.10f);

	glBegin(GL_QUADS);
	{
		//Floor
		 // floor color
		glColor3f(0.7f, 0.6f, 0.5f);
		glVertex2f(0.9f, 0.0f);
		glColor3f(0.8f, 0.7f, 0.7f);
		glVertex2f(-0.9f, 0.0f);
		glVertex2f(-1.51f, -1.0f);
		glVertex2f(1.51f, -1.0f);
	}
	glEnd();


	//// Set it to identity Matrix
	//glLoadIdentity();

	//// Translate Triangle backwords by z
	//glTranslatef(0.01f, 0.0f, -0.1f);

	glBegin(GL_QUADS);
	{ // Right wall
		  // Background color
		glColor3f(0.8f, 0.6f, 0.8f);
		glVertex2f(0.9f, 1.0f);
		glVertex2f(0.9f, 0.0f);
		glVertex2f(1.5f, -1.0f);
		glVertex2f(1.5f, 1.0f);
	}
	glEnd();


	//// Set it to identity Matrix
	//glLoadIdentity();

	//// Translate Triangle backwords by z
	//glTranslatef(-0.01f, 0.0f, -0.1f);
	glBegin(GL_QUADS);
	{ // Left wall
		  // Background color
		glColor3f(0.9f, 0.8f, 1.0f);
		glVertex2f(-0.9f, 1.0f);
		glVertex2f(-0.9f, 0.0f);
		glVertex2f(-1.5f, -1.0f);
		glVertex2f(-1.5f, 1.0f);
	}
	glEnd();
}

void Ram_Janm_Display_call_Amol(void)
{

	// Set it to identity Matrix
	glLoadIdentity();
	// Translate Triangle backwords by z
	glTranslatef(0.0f, 0.0f, -10.0f);
	glScalef(5.25f, 4.75f, 1.0f);
	Background(0.0f, 0.0f, 100.0f);


	// Set it to identity Matrix
	glLoadIdentity();
	// Translate Triangle backwords by z
	glTranslatef(0.0f, 0.02f, -0.9f);
	Window_Amol(0.0f, 0.0f, 30.0f);

	// Set it to identity Matrix
	glLoadIdentity();
	// Translate Triangle backwords by z
	glTranslatef(-0.3f, 0.02f, -0.9f);
	Window_Amol(0.0f, 0.0f, 30.0f);


	// Set it to identity Matrix
	glLoadIdentity();
	// Translate Triangle backwords by z
	glTranslatef(0.3f, 0.02f, -0.9f);
	Window_Amol(0.0f, 0.0f, 30.0f);


	// Set it to identity Matrix
	glLoadIdentity();
	// Translate Triangle backwords by z
	glTranslatef(0.0f, 0.0f, -0.8f);
	Pillar_Amol(0.05f, 0.0f, 35.0f);

	// Set it to identity Matrix
	glLoadIdentity();
	// Translate Triangle backwords by z
	glTranslatef(0.0f, 0.0f, -0.8f);
	Pillar_Amol(-0.2f, 0.0f, 35.0f);

	// Set it to identity Matrix
	glLoadIdentity();
	// Translate Triangle backwords by z
	glTranslatef(0.0f, 0.0f, -0.5f);
	Aai_Amol(0.0f, 0.0f, 20.0f);

	// Set it to identity Matrix
	glLoadIdentity();
	// Translate Triangle backwords by z
	glTranslatef(-0.0f, 0.0f, -0.6f);
	Palna_SupportingBodyLeft_Amol(0.0f, 0.0f, 20.0f);

	// Set it to identity Matrix
	glLoadIdentity();
	// Translate Triangle backwords by z
	glTranslatef(-0.0f, 0.0f, -0.6f);
	Palna_Amol(0.0f, 0.0f, 20.0f);

	// Set it to identity Matrix
	glLoadIdentity();
	// Translate Triangle backwords by z
	glTranslatef(-0.0f, 0.0f, -0.6f);
	Palna_SupportingBodyRight_Amol(0.0f, 0.0f, 20.0f);

}