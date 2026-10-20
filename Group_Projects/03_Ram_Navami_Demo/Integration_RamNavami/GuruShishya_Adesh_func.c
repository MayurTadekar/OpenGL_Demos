/*
 *************************************************
 * @file	: GuruShishya_Adesh_func.c
 * @brief	: Implementation of all the methods for
 *            Ram navami demo scene
 * @author	: Adesh Mohanrao Pathare 
 * 			  <adeshpathare8495@gmail.com>
 * @Date    : 31 March 2025
 *************************************************
 */

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
#include "GuruShishya_Adesh.h"

// Bazier curve variable declarations
static GLfloat x[4], y[4];
static GLfloat xt[100], yt[100], t;
static GLfloat xs[100], ys[100];

// Arrays for tree Circle 
static GLfloat xc[360], yc[360];

// Arrays for land
static GLfloat xl[100], yl[100];
static GLfloat xd[100], yd[100];

// Arrays for eye bros
static GLfloat xEb1[100], yEb1[100];
static GLfloat xEb2[100], yEb2[100];

// Array for eyes
static GLfloat xEye1[100], yEye1[100];
static GLfloat xEye2[100], yEye2[100];

// Array for Shal on guru body
static GLfloat xShal1[100], yShal1[100];
static GLfloat xShal2[100], yShal2[100];

// Array for Shishya
static GLfloat xShishya1[100], yShishya1[100];
static GLfloat xShishya2[100], yShishya2[100];

// Array for kutiya roof
static GLfloat xRoof[100], yRoof[100];
static GLfloat xDoor[100], yDoor[100];

// Array for River
static GLfloat xRiver1[200], yRiver1[200];
static GLfloat xRiver2[200], yRiver2[200];

/* function definitions */
void river(GLfloat x_pos, GLfloat y_pos)
{
	glColor3f(71.0/255.0f, 98.0/255.0f, 125.0/255.0f);
	glBegin(GL_TRIANGLE_STRIP);
	{
		for (i = 0; i < 200; i++)
		{
			glColor3f(71.0/255.0f, 98.0/255.0f, 125.0/255.0f);
			glVertex3f(xRiver1[i], yRiver1[i], 0.0f);
			glColor3f(135.0/255.0f, 156.0/255.0f, 177.0/255.0f);
			glVertex3f(xRiver2[i], yRiver2[i], 0.0f);
		}
	}
	glEnd();

}

void adesh_land(GLfloat x_pos, GLfloat y_pos)
{
	glBegin(GL_TRIANGLE_STRIP);
	{
		for (i = 0; i < 100; i++)
		{
			glColor3f(68.0/255.0f, 51.0/255.0f, 30.0/255.0f);
			glVertex3f(xl[i], yl[i], 0.0f);
			glColor3f(152.0/255.0f, 113.0/255.0f, 74.0/255.0f);
			glVertex3f(xd[i], yd[i], 0.0f);
		}
	}
	glEnd();
}

void adesh_guru_shishya(void)
{
	// Land draw here
	adesh_land(0.0f, 0.0f);
	
	// Quad for sky here
	adesh_sky(0.0f, 0.0f);

	// mountain and river here
	adesh_mountain_river(0.0f, 0.0f);

	// call to kutiya
	kutiya_all(-0.04f, 0.06f);

	// call to tree base here
	tree_base(0.0f, -0.10f);
	tree_base_line_loop(0.0f,-0.10f);
	tree_base(0.0f, 0.0f);
	tree_base_line_loop(0.0f, 0.0f);

	// Tree Wood
	adesh_tree_wood(0.0f, 0.0f);
	
	// circle for tree
	tree_circle(0.0f, 0.0f);

	// set to identity matrix
	glLoadIdentity();

	// translate triangle backwards by z-axis
	glTranslatef(-0.25f, -0.10f, -3.0f);
	
	// draw guru here
	teaching_guru(0.0f, 0.0f);

	// shishya draw here
	glLoadIdentity();

	// translate triangle backwards by z-axis
	glTranslatef(0.0f, -0.10f, -2.75f);
	
	shishya(0.2f, 0.2f);
	shishya(-0.2f, -0.1f);
	shishya(0.7f, 0.2f);
	shishya(0.35f, -0.1f);
	shishya(0.85f, -0.05f);

	// tulsi vrindavan
	Tulas_Adesh(1.3f, 0.3f, 90);
}

void leave(GLfloat x_pos, GLfloat y_pos, GLfloat percent)
{
	// leaf border
	glBegin(GL_QUADS);
	{
		glColor3f(0.0f, 0.0f, 0.0f);

		glVertex2d(VALUE_FROM_PERCENT(-1.19f, percent) + x_pos, VALUE_FROM_PERCENT(0.81f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(-1.245f, percent) + x_pos, VALUE_FROM_PERCENT(0.75f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(-1.31f, percent) + x_pos, VALUE_FROM_PERCENT(0.68f, percent) + y_pos); // base
		glVertex2d(VALUE_FROM_PERCENT(-1.265f, percent) + x_pos, VALUE_FROM_PERCENT(0.76f, percent) + y_pos);

	}
	glEnd();

	// leaf
	glBegin(GL_QUADS);
	{
		//glColor3f(0.1f, 0.8f, 0.1f);
		glColor3f(7.0/255.0f, 28.0/255.0f, 9.0/255.0f);
		glVertex2d(VALUE_FROM_PERCENT(-1.20f + x_pos, percent), VALUE_FROM_PERCENT(0.80f + y_pos, percent));
		glVertex2d(VALUE_FROM_PERCENT(-1.225f + x_pos, percent), VALUE_FROM_PERCENT(0.75f + y_pos, percent));
		glColor3f(0.1f, 0.8f, 0.1f);
		glVertex2d(VALUE_FROM_PERCENT(-1.30f + x_pos, percent), VALUE_FROM_PERCENT(0.70f + y_pos, percent)); // base
		glVertex2d(VALUE_FROM_PERCENT(-1.275f + x_pos, percent), VALUE_FROM_PERCENT(0.75f + y_pos, percent));

	}
	glEnd();
	
}

void tree_circle(GLfloat x_pos, GLfloat y_pos)
{
	// variable declarations
    GLfloat x_leaf;

    // code
	glColor3f(30.0/255.0f, 91.0/255.0f, 22.0/255.0f);
	glBegin(GL_POLYGON);
	{
		glVertex3f(-0.60f, 0.35f, 0.0f);
		glVertex3f(-0.80f, 1.10f, 0.0f);
		glVertex3f(-2.0f, 1.10f, 0.0f);
		glVertex3f(-2.0f, 0.35f, 0.0f);
	}
	glEnd();

	for (x_leaf = 0.70f; x_leaf > -0.75f; x_leaf = x_leaf - 0.05f)
	{
		if (x_leaf == 0.70f)
		{
			leave(x_leaf-0.250f, 0.30f, 100);
			leave(x_leaf-0.225f, 0.20f, 100);
			leave(x_leaf-0.200f, 0.10f, 100);
			leave(x_leaf-0.175f, 0.0f, 100);
			leave(x_leaf-0.150f, -0.10f, 100);
			leave(x_leaf-0.125f, -0.20f, 100);
			leave(x_leaf-0.100f, -0.30f, 100);
			leave(x_leaf-0.075f, -0.40f, 100);
		}
		else
		{
			leave(x_leaf-0.250f, 0.30f, 100);
			leave(x_leaf-0.225f, 0.20f, 100);
			leave(x_leaf-0.200f, 0.10f, 100);
			leave(x_leaf-0.175f, 0.0f, 100);
			leave(x_leaf-0.150f, -0.10f, 100);
			leave(x_leaf-0.125f, -0.20f, 100);
			leave(x_leaf-0.100f, -0.30f, 100);
			leave(x_leaf-0.075f, -0.40f, 100);
		}
	}
}

void tree_base(GLfloat x_pos, GLfloat y_pos)
{
	// variable declarations
	GLfloat angle = 0.0f, radiance = 0.0f;
	GLfloat radius_x = 0.60f;
	GLfloat radius_y = 0.15f;
	GLfloat center_x = -1.15f;
	GLfloat center_y = -0.35f + y_pos;
	
    // code
	glColor3f(97.0/255.0f, 64.0/255.0f, 29.0/255.0f);
	glBegin(GL_POLYGON);
	{
		for (i = 0; i < 360; i++)
		{
			radiance = i * (M_PI / 180.0f);
			xc[i] = center_x + radius_x * cos(radiance);
			yc[i] = center_y + radius_y * sin(radiance);

			// Draw circle here
			glVertex3f(xc[i] + x_pos, yc[i] + y_pos, 0.0f);
		}
	}
	glEnd();

	glColor3f(97.0/255.0f, 64.0/255.0f, 29.0/255.0f);
	glBegin(GL_QUADS);
	{
		glVertex3f(-1.75f, -0.55f, 0.0f);
		glVertex3f(-1.75f, -0.35f, 0.0f);
		glVertex3f(-0.55f, -0.35f, 0.0f);
		glVertex3f(-0.55f, -0.55f, 0.0f);
	}
	glEnd();

}

void tree_base_line_loop(GLfloat x_pos, GLfloat y_pos)
{
	// variable declarations
	GLfloat angle = 0.0f, radiance = 0.0f;
	GLfloat radius_x = 0.60f;
	GLfloat radius_y = 0.15f;
	GLfloat center_x = -1.15f;
	GLfloat center_y = -0.35f + y_pos;
	
    // code
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	{
		for (i = 0; i < 360; i++)
		{
			radiance = i * (M_PI / 180.0f);
			xc[i] = center_x + radius_x * cos(radiance);
			yc[i] = center_y + radius_y * sin(radiance);

			// Draw circle here
			glVertex3f(xc[i] + x_pos, yc[i] + y_pos, 0.0f);
		}
	}
	glEnd();

}

void guru_face(GLfloat x_pos, GLfloat y_pos)
{
	// variable declarations
	GLfloat radiance = 0.0f;
	GLfloat radius_x = 0.08f;
	GLfloat radius_y = 0.15f;
	GLfloat center_x = -1.120f;
	GLfloat center_y = 0.27f;

    // code

    // Hairs
	glColor3f(253.0/255.0f, 255.0/255.0f, 250.0/255.0f);
	glBegin(GL_POLYGON);
	{
		for (i = 0; i < 360; i++)
		{
			radiance = i * (M_PI / 180.0f);
			xc[i] = center_x + radius_x * cos(radiance);
			yc[i] = center_y + radius_y * sin(radiance);

			// Draw circle here
			glVertex3f(xc[i] + x_pos, yc[i] + y_pos, 0.0f);
		}
	}
	glEnd();

	// hairs upper circle
	radiance = 0.0f;
	radius_x = 0.03f;
	radius_y = 0.03f;
	center_x = -1.120f;
	center_y = 0.44f;

	glColor3f(253.0/255.0f, 255.0/255.0f, 250.0/255.0f);
	glBegin(GL_POLYGON);
	{
		for (i = 0; i < 360; i++)
		{
			radiance = i * (M_PI / 180.0f);
			xc[i] = center_x + radius_x * cos(radiance);
			yc[i] = center_y + radius_y * sin(radiance);

			// Draw circle here
			glVertex3f(xc[i] + x_pos, yc[i] + y_pos, 0.0f);
		}
	}
	glEnd();

	// border to hairs
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	{
		for (i = 0; i < 360; i++)
		{
			radiance = i * (M_PI / 180.0f);
			xc[i] = center_x + radius_x * cos(radiance);
			yc[i] = center_y + radius_y * sin(radiance);

			// Draw circle here
			glVertex3f(xc[i] + x_pos, yc[i] + y_pos, 0.0f);
		}
	}
	glEnd();

	// variable declarations
	radiance = 0.0f;
	radius_x = 0.05f;
	radius_y = 0.10f;
	center_x = -1.10f;
	center_y = 0.30f;
	
	glColor3f(243.0/255.0f, 195.0/255.0f, 146.0/255.0f);
	glBegin(GL_POLYGON);
	{
		for (i = 0; i < 360; i++)
		{
			radiance = i * (M_PI / 180.0f);
			xc[i] = center_x + radius_x * cos(radiance);
			yc[i] = center_y + radius_y * sin(radiance);

			// Draw circle here
			glVertex3f(xc[i] + x_pos, yc[i] + y_pos, 0.0f);
		}
	}
	glEnd();

	// leeps
	radiance = 0.0f;
	radius_x = 0.04f;
	radius_y = 0.04f;
	center_x = -1.087f;
	center_y = 0.21f;

	glColor3f(1.0f, 1.0f, 1.0f);
	glLineWidth(6.0f);
	glBegin(GL_LINE_STRIP);
	{
		for (i = 0; i < 180; i++)
		{
			radiance = i * (M_PI / 180.0f);
			xc[i] = center_x + radius_x * cos(radiance);
			yc[i] = center_y + radius_y * sin(radiance);

			// Draw circle here
			glVertex3f(xc[i] + x_pos, yc[i] + y_pos, 0.0f);
		}
	}
	glEnd();
	glLineWidth(1.0f);
}

void teaching_guru(GLfloat x_pos, GLfloat y_pos)
{
	// upper body
	guru_upper_body(x_pos, y_pos);

    // guruji face
	guru_face(x_pos, y_pos);

	// Eye bros
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLE_STRIP);
	{
		for (i = 0; i < 100; i++)
		{
			
			glVertex3f(xEb1[i], yEb1[i], 0.0f);
			glVertex3f(xEb2[i], yEb2[i], 0.0f);
		}
	}
	glEnd();

	// right eye bros
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	{
		glVertex3f(-1.05f + x_pos, 0.32f + y_pos, 0.0f);
		glVertex3f(-1.07f + x_pos, 0.32f + y_pos, 0.0f);
		glVertex3f(-1.07f + x_pos, 0.33f + y_pos, 0.0f);
		glVertex3f(-1.05f + x_pos, 0.33f + y_pos, 0.0f);
	}
	glEnd();

	// Left Eye 
	glColor3f(248.0/255.0f, 245.0/255.0f, 250.0/255.0f);
	glBegin(GL_TRIANGLE_STRIP);
	{
		for (i = 0; i < 100; i++)
		{
			
			glVertex3f(xEye1[i], yEye1[i], 0.0f);
			glVertex3f(xEye2[i], yEye2[i], 0.0f);
		}
	}
	glEnd();

	glColor3f(248.0/255.0f, 245.0/255.0f, 250.0/255.0f);
	glBegin(GL_TRIANGLES);
	{
		glVertex3f(-1.05f + x_pos, 0.32f + y_pos, 0.0f);
		glVertex3f(-1.05f + x_pos, 0.30f + y_pos, 0.0f);
		glVertex3f(-1.07f + x_pos, 0.31f + y_pos, 0.0f);
	}
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(4);
	glBegin(GL_POINTS);
	{
		glVertex3f(-1.120f + x_pos, 0.31f + y_pos, 0.0f);
		glVertex3f(-1.055f + x_pos, 0.31f + y_pos, 0.0f);
	}
	glEnd();
}

void guru_upper_body(GLfloat x_pos, GLfloat y_pos)
{
	glColor3f(243.0/255.0f, 195.0/255.0f, 146.0/255.0f);
	glBegin(GL_POLYGON);
	{
		glVertex3f(-1.20f, 0.22f, 0.0f);
		glVertex3f(-1.30f, 0.15f, 0.0f);
		glVertex3f(-1.30f, -0.25f, 0.0f);
		glVertex3f(-1.0f, -0.25f, 0.0f);
		glVertex3f(-1.00f, 0.13f, 0.0f);
		glVertex3f(-1.02f, 0.16f, 0.0f);
		glVertex3f(-1.10f, 0.22f, 0.0f);
	}
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	{
		glVertex3f(-1.20f, 0.22f, 0.0f);
		glVertex3f(-1.30f, 0.15f, 0.0f);
		glVertex3f(-1.30f, -0.25f, 0.0f);
		glVertex3f(-1.0f, -0.25f, 0.0f);
		glVertex3f(-1.0f, 0.15f, 0.0f);
		glVertex3f(-1.10f, 0.22f, 0.0f);
	}
	glEnd();

	// guru's legs in seating position
	guru_legs(x_pos, y_pos);

	// Shal on guru's body
	glColor3f(225.0/255.0f, 166.0/255.0f, 77.0/255.0f);
	glBegin(GL_POLYGON);
	{
		glVertex3f(-1.0f, 0.15f, 0.0f);
		for (i = 0; i < 100; i++)
		{
			
			glColor3f(225.0/255.0f, 166.0/255.0f, 77.0/255.0f);
			glVertex3f(xShal1[i], yShal1[i], 0.0f);
			//glColor3f(217.0/255.0f, 117.0/255.0f, 45.0/255.0f);
			glVertex3f(xShal2[i], yShal2[i], 0.0f);

		}
	}
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	{
		glVertex3f(-1.0f, 0.15f, 0.0f);
		for (i = 0; i < 100; i++)
			glVertex3f(xShal1[i], yShal1[i], 0.0f);
		for (i = 99; i >= 0; i--)
			glVertex3f(xShal2[i], yShal2[i], 0.0f);
	}
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_STRIP);
	{
		glVertex3f(-1.02f, 0.16f, 0.0f);
		glVertex3f(-1.04f, 0.10f, 0.0f);
		glVertex3f(-1.05f, 0.08f, 0.0f);
		glVertex3f(-1.06f, 0.05f, 0.0f);
		glVertex3f(-1.08f, 0.02f, 0.0f);
		glVertex3f(-1.10f, 0.0f, 0.0f);
		glVertex3f(-1.13f, -0.04f, 0.0f);
		glVertex3f(-1.20f, -0.11f, 0.0f);
		glVertex3f(-1.20f, -0.13f, 0.0f);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	{
		glVertex3f(-1.00f, -0.10f, 0.0f);
		glVertex3f(-1.02f, -0.11f, 0.0f);
		glVertex3f(-1.05f, -0.14f, 0.0f);
		glVertex3f(-1.09f, -0.18f, 0.0f);
		glVertex3f(-1.11f, -0.19f, 0.0f);
		glVertex3f(-1.21f, -0.22f, 0.0f);
		glVertex3f(-1.28f, -0.22f, 0.0f);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	{
		glVertex3f(-1.05f, -0.04f, 0.0f);
		glVertex3f(-1.06f, -0.06f, 0.0f);
		glVertex3f(-1.09f, -0.09f, 0.0f);
		glVertex3f(-1.15f, -0.12f, 0.0f);
		glVertex3f(-1.21f, -0.15f, 0.0f);
	}
	glEnd();

	// left hand
	glColor3f(243.0/255.0f, 195.0/255.0f, 146.0/255.0f);
	glBegin(GL_POLYGON);
	{
		glVertex3f(-1.30f, 0.15f, 0.0f);
		glVertex3f(-1.35f, -0.03f, 0.0f);
		glVertex3f(-1.34f, -0.06f, 0.0f);
		glVertex3f(-1.20f, 0.01f, 0.0f);
		glVertex3f(-1.15f, 0.01f, 0.0f);
		glVertex3f(-1.12f, 0.07f, 0.0f);
		glVertex3f(-1.13f, 0.07f, 0.0f);
		glVertex3f(-1.15f, 0.03f, 0.0f);
		glVertex3f(-1.20f, 0.04f, 0.0f);
		glVertex3f(-1.30f, 0.01f, 0.0f);
		glVertex3f(-1.25f, 0.15f, 0.0f);
		glColor3f(243.0/255.0f, 195.0/255.0f, 146.0/255.0f);
		glVertex3f(-1.30f, 0.15f, 0.0f);
	}
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	{
		glVertex3f(-1.30f, 0.15f, 0.0f);
		glVertex3f(-1.35f, -0.03f, 0.0f);
		glVertex3f(-1.34f, -0.06f, 0.0f);
		glVertex3f(-1.20f, 0.01f, 0.0f);
		glVertex3f(-1.15f, 0.01f, 0.0f);
		glVertex3f(-1.12f, 0.07f, 0.0f);
		glVertex3f(-1.13f, 0.07f, 0.0f);
		glVertex3f(-1.15f, 0.03f, 0.0f);
		glVertex3f(-1.20f, 0.04f, 0.0f);
		glVertex3f(-1.30f, 0.01f, 0.0f);
		glVertex3f(-1.25f, 0.15f, 0.0f);
		glColor3f(243.0/255.0f, 195.0/255.0f, 146.0/255.0f);
		glVertex3f(-1.30f, 0.15f, 0.0f);
	}
	glEnd();

	// Patrika in guru's hand
	glColor3f(97.0/255.0f, 64.0/255.0f, 29.0/255.0f);
	glBegin(GL_POLYGON);
	{
		glVertex3f(-0.73f, 0.18f, 0.0f);
		glVertex3f(-0.87f, 0.15f, 0.0f);
		glVertex3f(-0.90f, 0.04f, 0.0f);
		glVertex3f(-0.75f, 0.08f, 0.0f);
	}
	glEnd();

	// Patrika in guru's hand border
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	{
		glVertex3f(-0.73f, 0.18f, 0.0f);
		glVertex3f(-0.87f, 0.15f, 0.0f);
		glVertex3f(-0.90f, 0.04f, 0.0f);
		glVertex3f(-0.75f, 0.08f, 0.0f);
	}
	glEnd();

	// cloth for patrika 
	glColor3f(129.0/255.0f, 17.0/255.0f, 18.0/255.0f);
	glBegin(GL_POLYGON);
	{
		glColor3f(129.0/255.0f, 17.0/255.0f, 18.0/255.0f);
		glVertex3f(-0.88f, -0.28f, 0.0f);
		glVertex3f(-0.84f, -0.29f, 0.0f);
		glVertex3f(-0.82f, -0.30f, 0.0f);
		glVertex3f(-0.80f, -0.30f, 0.0f);
		glVertex3f(-0.78f, -0.31f, 0.0f);
		glVertex3f(-0.77f, -0.32f, 0.0f);
		glVertex3f(-0.74f, -0.33f, 0.0f);
		glVertex3f(-0.73f, -0.34f, 0.0f);
		glVertex3f(-0.72f, -0.36f, 0.0f);
		glVertex3f(-0.75f, -0.39f, 0.0f);
		glVertex3f(-0.77f, -0.40f, 0.0f);
		glVertex3f(-0.74f, -0.33f, 0.0f);
		glVertex3f(-0.79f, -0.42f, 0.0f);
		glVertex3f(-0.82f, -0.43f, 0.0f);
		glVertex3f(-0.85f, -0.46f, 0.0f);
		glVertex3f(-0.92f, -0.48f, 0.0f);
		glVertex3f(-0.95f, -0.50f, 0.0f);
		glVertex3f(-0.99f, -0.51f, 0.0f);
		glVertex3f(-1.03f, -0.50f, 0.0f);
		glVertex3f(-1.05f, -0.50f, 0.0f);
		glVertex3f(-1.03f, -0.50f, 0.0f);
		glVertex3f(-1.12f, -0.48f, 0.0f);
		glVertex3f(-1.14f, -0.45f, 0.0f);
		glVertex3f(-1.16f, -0.44f, 0.0f);
		glVertex3f(-1.19f, -0.44f, 0.0f);
		glVertex3f(-1.15f, -0.41f, 0.0f);
		glVertex3f(-0.88f, -0.28f, 0.0f);
	}
	glEnd();

	// cloth border
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	{
		glVertex3f(-0.88f, -0.28f, 0.0f);
		glVertex3f(-0.84f, -0.29f, 0.0f);
		glVertex3f(-0.82f, -0.30f, 0.0f);
		glVertex3f(-0.80f, -0.30f, 0.0f);
		glVertex3f(-0.78f, -0.31f, 0.0f);
		glVertex3f(-0.77f, -0.32f, 0.0f);
		glVertex3f(-0.74f, -0.33f, 0.0f);
		glVertex3f(-0.73f, -0.34f, 0.0f);
		glVertex3f(-0.72f, -0.36f, 0.0f);
		glVertex3f(-0.75f, -0.39f, 0.0f);
		glVertex3f(-0.77f, -0.40f, 0.0f);
		glVertex3f(-0.79f, -0.42f, 0.0f);
		glVertex3f(-0.82f, -0.43f, 0.0f);
		glVertex3f(-0.85f, -0.46f, 0.0f);
		glVertex3f(-0.92f, -0.48f, 0.0f);
		glVertex3f(-0.95f, -0.50f, 0.0f);
		glVertex3f(-0.99f, -0.51f, 0.0f);
		glVertex3f(-1.03f, -0.50f, 0.0f);
		glVertex3f(-1.05f, -0.50f, 0.0f);
		glVertex3f(-1.03f, -0.50f, 0.0f);
		glVertex3f(-1.12f, -0.48f, 0.0f);
		glVertex3f(-1.14f, -0.45f, 0.0f);
		glVertex3f(-1.16f, -0.44f, 0.0f);
		glVertex3f(-1.19f, -0.44f, 0.0f);
		glVertex3f(-1.15f, -0.41f, 0.0f);
		glVertex3f(-0.88f, -0.28f, 0.0f);
	}
	glEnd();

	// patrika on tree base
	glColor3f(116.0/255.0f, 66.0/255.0f, 33.0/255.0f);
	glBegin(GL_POLYGON);
	{
		glVertex3f(-0.89f, -0.30f, 0.0f);
		glVertex3f(-0.77f, -0.34f, 0.0f);
		glVertex3f(-0.98f, -0.44f, 0.0f);
		glVertex3f(-1.11f, -0.40f, 0.0f);
		glVertex3f(-1.11f, -0.43f, 0.0f);
		glVertex3f(-0.98f, -0.47f, 0.0f);
		glVertex3f(-0.98f, -0.44f, 0.0f);
		glVertex3f(-0.98f, -0.47f, 0.0f);
		glVertex3f(-0.77f, -0.37f, 0.0f);
		glVertex3f(-0.77f, -0.34f, 0.0f);
	}
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	// patrika order here
	glBegin(GL_LINE_LOOP);
	{
		glVertex3f(-0.89f, -0.30f, 0.0f);
		glVertex3f(-0.77f, -0.34f, 0.0f);
		glVertex3f(-0.98f, -0.44f, 0.0f);
		glVertex3f(-1.11f, -0.40f, 0.0f);
		glVertex3f(-1.11f, -0.43f, 0.0f);
		glVertex3f(-0.98f, -0.47f, 0.0f);
		glVertex3f(-0.98f, -0.44f, 0.0f);
		glVertex3f(-0.98f, -0.47f, 0.0f);
		glVertex3f(-0.77f, -0.37f, 0.0f);
		glVertex3f(-0.77f, -0.34f, 0.0f);
		glVertex3f(-0.89f, -0.30f, 0.0f);
		glVertex3f(-1.11f, -0.40f, 0.0f);
	}
	glEnd();

	// Right hand
	glColor3f(243.0/255.0f, 195.0/255.0f, 146.0/255.0f);
	glBegin(GL_POLYGON);
	{
		glVertex3f(-1.0f, -0.06f, 0.0f);
		glVertex3f(-1.0f, 0.01f, 0.0f);
		glVertex3f(-0.86f, 0.05f, 0.0f);
		glVertex3f(-0.86f, 0.02f, 0.0f);
	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		glVertex3f(-0.83f, 0.06f, 0.0f);
		glVertex3f(-0.83f, 0.09f, 0.0f);
		glVertex3f(-0.82f, 0.09f, 0.0f);
		glVertex3f(-0.82f, 0.06f, 0.0f);
		glVertex3f(-0.81f, 0.06f, 0.0f);
		glVertex3f(-0.81f, 0.10f, 0.0f);
		glVertex3f(-0.80f, 0.10f, 0.0f);
		glVertex3f(-0.80f, 0.06f, 0.0f);
		glVertex3f(-0.79f, 0.06f, 0.0f);
		glVertex3f(-0.79f, 0.11f, 0.0f);
		glVertex3f(-0.78f, 0.11f, 0.0f);
		glVertex3f(-0.78f, 0.06f, 0.0f);
		glVertex3f(-0.77f, 0.06f, 0.0f);
		glVertex3f(-0.77f, 0.10f, 0.0f);
		glVertex3f(-0.76f, 0.10f, 0.0f);
		glVertex3f(-0.76f, 0.06f, 0.0f);
		glVertex3f(-0.77f, 0.04f, 0.0f);
		glVertex3f(-0.84f, 0.02f, 0.0f);
		glVertex3f(-0.87f, 0.02f, 0.0f);
		glVertex3f(-0.87f, 0.05f, 0.0f);
	}
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	{
		glVertex3f(-1.0f, -0.06f, 0.0f);
		glVertex3f(-1.0f, 0.01f, 0.0f);
		glVertex3f(-0.86f, 0.05f, 0.0f);
		glVertex3f(-0.86f, 0.02f, 0.0f);
	}
	glEnd();

	glBegin(GL_LINE_LOOP);
	{
		glVertex3f(-0.83f, 0.06f, 0.0f);
		glVertex3f(-0.83f, 0.09f, 0.0f);
		glVertex3f(-0.82f, 0.09f, 0.0f);
		glVertex3f(-0.82f, 0.06f, 0.0f);
		glVertex3f(-0.81f, 0.06f, 0.0f);
		glVertex3f(-0.81f, 0.10f, 0.0f);
		glVertex3f(-0.80f, 0.10f, 0.0f);
		glVertex3f(-0.80f, 0.06f, 0.0f);
		glVertex3f(-0.79f, 0.06f, 0.0f);
		glVertex3f(-0.79f, 0.11f, 0.0f);
		glVertex3f(-0.78f, 0.11f, 0.0f);
		glVertex3f(-0.78f, 0.06f, 0.0f);
		glVertex3f(-0.77f, 0.06f, 0.0f);
		glVertex3f(-0.77f, 0.10f, 0.0f);
		glVertex3f(-0.76f, 0.10f, 0.0f);
		glVertex3f(-0.76f, 0.06f, 0.0f);
		glVertex3f(-0.77f, 0.04f, 0.0f);
		glVertex3f(-0.84f, 0.02f, 0.0f);
		glVertex3f(-0.87f, 0.02f, 0.0f);
		glVertex3f(-0.87f, 0.05f, 0.0f);
	}
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(4);
	glBegin(GL_POINTS);
	{
		glVertex3f(-1.20f, 0.06f, 0.0f);
	}
	glEnd();
}

void guru_legs(GLfloat x_pos, GLfloat y_pos)
{
	const int numSegments = 100;
	GLfloat x_final[100], y_final[100];
	GLfloat a = 0.25f; // Horizontal radius
	GLfloat b = 0.10f; // Vertical radius
	GLfloat phi = 10.0f * (M_PI / 180.0f); // Rotation angle (10 degrees in radians)
	GLfloat cx = -1.10f; // X-coordinate of the center
	GLfloat cy = -0.24f; // Y-coordinate of the center

	glColor3f(255.0/255.0f, 255.0/255.0f, 255.0/255.0f);
	glBegin(GL_POLYGON);
	for (int i = 0; i < numSegments; ++i) {
		GLfloat t = 2.0f * 3.1415926f * (GLfloat)i / (GLfloat)numSegments; // Parametric angle
		GLfloat x = a * cosf(t);
		GLfloat y = b * sinf(t);

		// Apply rotation
		float x_rot = x * cosf(phi) - y * sinf(phi);
		float y_rot = x * sinf(phi) + y * cosf(phi);

		// Translate to the new center
		x_final[i] = x_rot + cx;
		y_final[i] = y_rot + cy;

		glVertex2f(x_final[i], y_final[i]); // Specify the translated point
	}
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	{
		for (i = 0; i < numSegments; i++)
			glVertex2f(x_final[i], y_final[i]);
	}
	glEnd();
}


void shishya(GLfloat x_pos, GLfloat y_pos)
{
	// shishya_legs
	shishya_legs(x_pos, y_pos);

	// shishya_body
	shishya_body(x_pos, y_pos);

	//shishya face
	shishya_face(x_pos, y_pos);
}

void shishya_body(GLfloat x_pos, GLfloat y_pos)
{
	if (x_pos == 0.2f)
		glColor3f(163.0/255.0f, 190.0/255.0f, 220.0/255.0f);
	else
		glColor3f(243.0/255.0f, 196.0/255.0f, 150.0/255.0f);
	glBegin(GL_POLYGON);
	{
		for (i = 0; i < 100; i++)
		{
			
			glVertex3f(xShishya1[i] + x_pos, yShishya1[i] + y_pos, 0.0f);
			glVertex3f(xShishya2[i] + x_pos, yShishya2[i] + y_pos, 0.0f);
		}
	}
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	{
		glVertex3f(-0.36f + x_pos, -0.55f + y_pos, 0.0f);
		glVertex3f(-0.36f + x_pos, -0.69f + y_pos, 0.0f);
	}
	glEnd();
}

void shishya_legs(GLfloat x_pos, GLfloat y_pos)
{
	const int numSegments = 100;
	GLfloat x_final[100], y_final[100];
	GLfloat a = 0.20f; // Horizontal radius
	GLfloat b = 0.10f; // Vertical radius
	GLfloat phi = -10.0f * (M_PI / 180.0f); // Rotation angle (45 degrees in radians)
	GLfloat cx = -0.47f; // X-coordinate of the center
	GLfloat cy = -0.73f; // Y-coordinate of the center

	glColor3f(206.0/255.0f, 112.0/255.0f, 42.0/255.0f);
	glBegin(GL_POLYGON);
	for (int i = 0; i < numSegments; ++i) {
		GLfloat t = 2.0f * 3.1415926f * (GLfloat)i / (GLfloat)numSegments; // Parametric angle
		GLfloat x = a * cosf(t);
		GLfloat y = b * sinf(t);

		// Apply rotation
		float x_rot = x * cosf(phi) - y * sinf(phi);
		float y_rot = x * sinf(phi) + y * cosf(phi);

		// Translate to the new center
		x_final[i] = x_rot + cx;
		y_final[i] = y_rot + cy;

		glVertex2f(x_final[i] + x_pos, y_final[i] + y_pos); // Specify the translated point
	}
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	{
		for (i = 0; i < numSegments; i++)
			glVertex2f(x_final[i] + x_pos, y_final[i] + y_pos);
	}
	glEnd();
}

void shishya_face(GLfloat x_pos, GLfloat y_pos)
{
	// face
	if (x_pos == 0.2f)
		glColor3f(163.0/255.0f, 190.0/255.0f, 220.0/255.0f);
	else
		glColor3f(243.0/255.0f, 196.0/255.0f, 150.0/255.0f);
	glBegin(GL_POLYGON);
	{
		glVertex3f(-0.32f + x_pos, -0.34f + y_pos, 0.0f);
		glVertex3f(-0.40f + x_pos, -0.34f + y_pos, 0.0f);
		glVertex3f(-0.41f + x_pos, -0.37f + y_pos, 0.0f);
		glVertex3f(-0.41f + x_pos, -0.39f + y_pos, 0.0f);
		glVertex3f(-0.42f + x_pos, -0.42f + y_pos, 0.0f);
		glVertex3f(-0.41f + x_pos, -0.42f + y_pos, 0.0f);
		glVertex3f(-0.41f + x_pos, -0.43f + y_pos, 0.0f);
		glVertex3f(-0.39f + x_pos, -0.44f + y_pos, 0.0f);
		glVertex3f(-0.41f + x_pos, -0.44f + y_pos, 0.0f);
		glVertex3f(-0.40f + x_pos, -0.46f + y_pos, 0.0f);
		glVertex3f(-0.37f + x_pos, -0.46f + y_pos, 0.0f);
		glVertex3f(-0.36f + x_pos, -0.44f + y_pos, 0.0f);
		glVertex3f(-0.36f + x_pos, -0.48f + y_pos, 0.0f);
		glVertex3f(-0.32f + x_pos, -0.48f + y_pos, 0.0f);
	}
	glEnd();

	// Eye
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(3);
	glBegin(GL_POINTS);
	{	
		glVertex3f(-0.40f + x_pos, -0.39f + y_pos, 0.0f);
	}
	glEnd();

	glBegin(GL_LINES);
	{
		glVertex3f(-0.41f + x_pos, -0.38f + y_pos, 0.0f);
		glVertex3f(-0.39f + x_pos, -0.38f + y_pos, 0.0f);
	}
	glEnd();

	// Hairs
	glColor3f(7.0/255.0f, 8.0/255.0f, 6.0/255.0f);
	glBegin(GL_POLYGON);
	{
		glVertex3f(-0.40f + x_pos, -0.34f + y_pos, 0.0f);
		glVertex3f(-0.41f + x_pos, -0.32f + y_pos, 0.0f);
		glVertex3f(-0.37f + x_pos, -0.32f + y_pos, 0.0f);
		glVertex3f(-0.33f + x_pos, -0.32f + y_pos, 0.0f);
		glVertex3f(-0.31f + x_pos, -0.33f + y_pos, 0.0f);
		glVertex3f(-0.28f + x_pos, -0.37f + y_pos, 0.0f);
		glVertex3f(-0.28f + x_pos, -0.40f + y_pos, 0.0f);
		glVertex3f(-0.26f + x_pos, -0.45f + y_pos, 0.0f);
		glVertex3f(-0.27f + x_pos, -0.46f + y_pos, 0.0f);
		glVertex3f(-0.26f + x_pos, -0.47f + y_pos, 0.0f);
		glVertex3f(-0.26f + x_pos, -0.50f + y_pos, 0.0f);
		glVertex3f(-0.31f + x_pos, -0.50f + y_pos, 0.0f);
		glVertex3f(-0.34f + x_pos, -0.47f + y_pos, 0.0f);
		glVertex3f(-0.34f + x_pos, -0.45f + y_pos, 0.0f);
		glVertex3f(-0.33f + x_pos, -0.44f + y_pos, 0.0f);
		glVertex3f(-0.32f + x_pos, -0.42f + y_pos, 0.0f);
		glVertex3f(-0.32f + x_pos, -0.40f + y_pos, 0.0f);
		glVertex3f(-0.33f + x_pos, -0.40f + y_pos, 0.0f);
		glVertex3f(-0.33f + x_pos, -0.42f + y_pos, 0.0f);
		glVertex3f(-0.34f + x_pos, -0.42f + y_pos, 0.0f);
		glVertex3f(-0.34f + x_pos, -0.40f + y_pos, 0.0f);
		glVertex3f(-0.36f + x_pos, -0.39f + y_pos, 0.0f);
		glVertex3f(-0.36f + x_pos, -0.37f + y_pos, 0.0f);
		glVertex3f(-0.38f + x_pos, -0.36f + y_pos, 0.0f);
		glVertex3f(-0.38f + x_pos, -0.35f + y_pos, 0.0f);
		glVertex3f(-0.40f + x_pos, -0.34f + y_pos, 0.0f);
	}
	glEnd();

	// Left Hand
	if (x_pos == 0.2f)
		glColor3f(163.0/255.0f, 190.0/255.0f, 220.0/255.0f);
	else
		glColor3f(243.0/255.0f, 196.0/255.0f, 150.0/255.0f);
	glBegin(GL_POLYGON);
	{
		glVertex3f(-0.47f + x_pos, -0.52f + y_pos, 0.0f);
		glVertex3f(-0.49f + x_pos, -0.62f + y_pos, 0.0f);
		glVertex3f(-0.49f + x_pos, -0.67f + y_pos, 0.0f);
		glVertex3f(-0.47f + x_pos, -0.68f + y_pos, 0.0f);
		glVertex3f(-0.46f + x_pos, -0.67f + y_pos, 0.0f);
		glVertex3f(-0.45f + x_pos, -0.64f + y_pos, 0.0f);
		glVertex3f(-0.44f + x_pos, -0.53f + y_pos, 0.0f);
		glVertex3f(-0.47f + x_pos, -0.52f + y_pos, 0.0f);
	}
	glEnd();

	if (x_pos == 0.2f)
		glColor3f(163.0/255.0f, 190.0/255.0f, 220.0/255.0f);
	else
		glColor3f(243.0/255.0f, 196.0/255.0f, 150.0/255.0f);
	glBegin(GL_POLYGON);
	{
		glVertex3f(-0.49f + x_pos, -0.62f + y_pos, 0.0f);
		glVertex3f(-0.54f + x_pos, -0.61f + y_pos, 0.0f);
		glVertex3f(-0.57f + x_pos, -0.60f + y_pos, 0.0f);
		glVertex3f(-0.61f + x_pos, -0.58f + y_pos, 0.0f);
		glVertex3f(-0.61f + x_pos, -0.56f + y_pos, 0.0f);
		glVertex3f(-0.65f + x_pos, -0.54f + y_pos, 0.0f);
		glVertex3f(-0.65f + x_pos, -0.55f + y_pos, 0.0f);
		glVertex3f(-0.62f + x_pos, -0.57f + y_pos, 0.0f);
		glVertex3f(-0.69f + x_pos, -0.57f + y_pos, 0.0f);
		glVertex3f(-0.69f + x_pos, -0.58f + y_pos, 0.0f);
		glVertex3f(-0.65f + x_pos, -0.58f + y_pos, 0.0f);
		glVertex3f(-0.65f + x_pos, -0.60f + y_pos, 0.0f);
		glVertex3f(-0.64f + x_pos, -0.61f + y_pos, 0.0f);
		glVertex3f(-0.61f + x_pos, -0.61f + y_pos, 0.0f);
		glVertex3f(-0.57f + x_pos, -0.63f + y_pos, 0.0f);
		glVertex3f(-0.54f + x_pos, -0.65f + y_pos, 0.0f);
		glVertex3f(-0.52f + x_pos, -0.66f + y_pos, 0.0f);
		glVertex3f(-0.49f + x_pos, -0.67f + y_pos, 0.0f);	
	}
	glEnd();
}

void kutiya_all(GLfloat x_pos, GLfloat y_pos)
{
	// variable declarations
	const int NUM_POINTS = 2000;
	float amplitude = 0.03;
	float frequency = 40.0;
	unsigned char counter = 0;

	// Kutiya starts here
	glBegin(GL_POLYGON);
	{
		// front wall
		glColor3f(105.0/255.0f, 83.0/255.0f, 46.0/255.0f);

		// starts from left bottom
		glVertex3f(1.25f + x_pos, 0.0f + y_pos, 0.0f);
		glVertex3f(1.25f + x_pos, 0.45f + y_pos, 0.0f);
		glVertex3f(2.20f + x_pos, 0.45f + y_pos, 0.0f);
		glVertex3f(2.20f + x_pos, 0.0f + y_pos, 0.0f);
		glVertex3f(1.25f + x_pos, 0.0f + y_pos, 0.0f);
	}
	glEnd();

	// sine waves  on front wall
	glColor3f(26.0/255.0f, 21.0/255.0f, 15.0/255.0f);

	for (float k = 0.45f; k >= 0.05f; k -= 0.05f)
	{
		counter++;
		glBegin(GL_LINE_STRIP);
		{
			for (int i = 0; i < NUM_POINTS; ++i)
			{
				float x = (i / (float)(NUM_POINTS - 1)) * 2.0f * M_PI;
				float y = amplitude * sin(frequency * x);
				if (counter == 3 || counter == 6)
					continue;
				glVertex3f(x + 1.21f, y + k, 0.0f);
			}
		}
		glEnd();
	}

	// Roof
	glBegin(GL_POLYGON);
	{
		glColor3f(136.0/255.0f, 104.0/255.0f, 53.0/255.0f);

		for (i = 0; i < 100; i++)
			glVertex3f(xRoof[i] + x_pos, yRoof[i] + y_pos, 0.0f);
		glVertex3f(1.725f + x_pos, 0.48f + y_pos, 0.0f);
	}
	glEnd();

	glBegin(GL_LINE_LOOP);
	{	
		// Roof border
		glColor3f(0.0f, 0.0f, 0.0f);

		for (i = 0; i < 100; i++)
			glVertex3f(xRoof[i] + x_pos, yRoof[i] + y_pos, 0.0f);
		
	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		// Door
		glColor3f(26.0/255.0f, 21.0/255.0f, 15.0/255.0f);

		// starts from left bottom
		//glVertex3f(1.0f, 0.50f, 0.0f);
		glVertex3f(1.60f + x_pos, 0.0f + y_pos, 0.0f);
		glVertex3f(1.60f + x_pos, 0.35f + y_pos, 0.0f);
		glVertex3f(1.80f + x_pos, 0.35f + y_pos, 0.0f);
		glVertex3f(1.80f + x_pos, 0.0f + y_pos, 0.0f);

		for (i = 0; i < 100; i++)
			glVertex3f(xDoor[i] + x_pos, yDoor[i] + y_pos, 0.0f);
	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		// Bottom Base of kutiya
		glColor3f(68.0/255.0f, 51.0/255.0f, 30.0/255.0f);

		// starts from left Top
		glVertex3f(1.25f + x_pos, 0.0f + y_pos, 0.0f);
		glVertex3f(1.15f + x_pos, -0.10f + y_pos, 0.0f);
		glVertex3f(2.25f + x_pos, -0.10f + y_pos, 0.0f);
		glVertex3f(2.25f + x_pos, 0.0f + y_pos, 0.0f);
		glVertex3f(1.0f + x_pos, 0.0f + y_pos, 0.0f);
	}
	glEnd();

}

void adesh_sky(GLfloat x_pos, GLfloat y_pos)
{
    glBegin(GL_QUADS);
	{
		glColor3f(170.0/255.0f, 203.0/255.0f, 230.0/255.0f);

		// starts from right top (anti clockwise)
		glVertex3f(2.0f, 1.25f, 0.0f);
		glVertex3f(-2.25f, 1.25f, 0.0f);
		glVertex3f(-2.25f, 0.40f, 0.0f);
		glVertex3f(2.0f, 0.60f, 0.0f);
	}
	glEnd();
}

void adesh_mountain_river(GLfloat x_pos, GLfloat y_pos)
{
	glBegin(GL_POLYGON);
	{
		glColor3f(77.0/255.0f, 61.0/255.0f, 45.0/255.0f);

		// Right side mountain
		glVertex3f(0.35f, 0.50f, 0.0f);
		glColor3f(106.0/255.0f, 76.0/255.0f, 52.0/255.0f);
		glVertex3f(0.80f, 0.70f, 0.0f);
		glVertex3f(1.0f, 0.90f, 0.0f);
		glVertex3f(2.0f, 1.25f, 0.0f);
		glVertex3f(2.0f, 0.60f, 0.0f);
		glVertex3f(0.35f, 0.50f, 0.0f);
	}
	glEnd();

	// call to river
	river(0.0f, 0.0f);

	// Left mountain
	glBegin(GL_POLYGON);
	{
		glColor3f(82.0/255.0f, 60.0/255.0f, 46.0/255.0f);
		
		glVertex3f(0.50f, 0.50f, 0.0f);
		glVertex3f(-2.25f, 0.40f, 0.0f);
		glVertex3f(-2.25f, 1.25f, 0.0f);
		glVertex3f(0.0f, 0.75f, 0.0f);
		
		glColor3f(105.0/255.0f, 81.0/255.0f, 47.0/255.0f);
		glVertex3f(0.40f, 0.55f, 0.0f);
	}
	glEnd();

	glBegin(GL_TRIANGLES);
	{
		
		glColor3f(106.0/255.0f, 77.0/255.0f, 53.0/255.0f);
		glVertex3f(-2.25f, 1.25f, 0.0f);
		glColor3f(82.0/255.0f, 60.0/255.0f, 46.0/255.0f);
		glVertex3f(-2.25f, 0.75f, 0.0f);
		
		glVertex3f(0.0f, 0.75f, 0.0f);
	}
	glEnd();
}

void adesh_tree_wood(GLfloat x_pos, GLfloat y_pos)
{
	glBegin(GL_TRIANGLE_STRIP);
	{
		for (i = 0; i < 100; i++)
		{
			glColor3f(47.0/255.0f, 21.0/255.0f, 12.0/255.0f);
			glVertex3f(xt[i], yt[i], 0.0f);
			glColor3f(105.0/255.0f, 81.0/255.0f, 47.0/255.0f);
			glVertex3f(xs[i], ys[i], 0.0f);
		}
	}
	glEnd();
}

void adesh_curve_calculations(void)
{
	// bazier curve initialization for tree wood
	x[0] = -1.60f; 
	x[1] = -1.45f;
	x[2] = -1.45f;
	x[3] = -1.50f;

	y[0] = 0.60f;
	y[1] = 0.0f;
	y[2] = 0.0f;
	y[3] = -0.30f;

	for (i = 0, t = 0; i < 100; i++, t = t + 0.01)
	{
		xt[i] = pow(1-t, 3)*x[0] + 3*t*pow(1-t, 2)*x[1] + 3*pow(t, 2)*(1-t)*x[2] + pow(t, 3)*x[3];
		yt[i] = pow(1-t, 3)*y[0] + 3*t*pow(1-t, 2)*y[1] + 3*pow(t, 2)*(1-t)*y[2] + pow(t, 3)*y[3];
	}

	x[0] = -1.0f;
	x[1] = -1.15f;
	x[2] = -1.15f;
	x[3] = -1.10f;

	y[0] = 0.60f; 
	y[1] = 0.0f;
	y[2] = 0.0f;
	y[3] = -0.30f;

	for (i = 0, t = 0; i < 100; i++, t = t + 0.01)
	{
		xs[i] = pow(1-t, 3)*x[0] + 3*t*pow(1-t, 2)*x[1] + 3*pow(t, 2)*(1-t)*x[2] + pow(t, 3)*x[3];
		ys[i] = pow(1-t, 3)*y[0] + 3*t*pow(1-t, 2)*y[1] + 3*pow(t, 2)*(1-t)*y[2] + pow(t, 3)*y[3];
	}
	
	// Bazier curve for land
	x[0] = -2.0f; 
	x[1] = -2.0f;
	x[2] = 2.0f;
	x[3] = 2.0f;

	y[0] = -1.25f; 
	y[1] = -1.25f;
	y[2] = -1.25f;
	y[3] = -1.25f;

	for (i = 0, t = 0; i < 100; i++, t = t + 0.01)
	{
		xl[i] = pow(1-t, 3)*x[0] + 3*t*pow(1-t, 2)*x[1] + 3*pow(t, 2)*(1-t)*x[2] + pow(t, 3)*x[3];
		yl[i] = pow(1-t, 3)*y[0] + 3*t*pow(1-t, 2)*y[1] + 3*pow(t, 2)*(1-t)*y[2] + pow(t, 3)*y[3];
	}

	x[0] = -2.0f;
	x[1] = -2.0f;
	x[2] = 2.0f;
	x[3] = 2.0f;

	y[0] = -0.20f;
	y[1] = -0.20f;
	y[2] = 0.15f;
	y[3] = 0.15f;

	for (i = 0, t = 0; i < 100; i++, t = t + 0.01)
	{
		xd[i] = pow(1-t, 3)*x[0] + 3*t*pow(1-t, 2)*x[1] + 3*pow(t, 2)*(1-t)*x[2] + pow(t, 3)*x[3];
		yd[i] = pow(1-t, 3)*y[0] + 3*t*pow(1-t, 2)*y[1] + 3*pow(t, 2)*(1-t)*y[2] + pow(t, 3)*y[3];
	}

	// Bazier curve for Left Eye bros
	x[0] = -1.10f; 
	x[1] = -1.125f;
	x[2] = -1.125f;
	x[3] = -1.150f;

	y[0] = 0.33f; 
	y[1] = 0.34f;
	y[2] = 0.34f;
	y[3] = 0.32f;

	for (i = 0, t = 0; i < 100; i++, t = t + 0.01)
	{
		xEb1[i] = pow(1-t, 3)*x[0] + 3*t*pow(1-t, 2)*x[1] + 3*pow(t, 2)*(1-t)*x[2] + pow(t, 3)*x[3];
		yEb1[i] = pow(1-t, 3)*y[0] + 3*t*pow(1-t, 2)*y[1] + 3*pow(t, 2)*(1-t)*y[2] + pow(t, 3)*y[3];
	}

	x[0] = -1.10f; 
	x[1] = -1.125f;
	x[2] = -1.125f;
	x[3] = -1.150f;

	y[0] = 0.32f; 
	y[1] = 0.33f;
	y[2] = 0.33f;
	y[3] = 0.32f;

	for (i = 0, t = 0; i < 100; i++, t = t + 0.01)
	{
		xEb2[i] = pow(1-t, 3)*x[0] + 3*t*pow(1-t, 2)*x[1] + 3*pow(t, 2)*(1-t)*x[2] + pow(t, 3)*x[3];
		yEb2[i] = pow(1-t, 3)*y[0] + 3*t*pow(1-t, 2)*y[1] + 3*pow(t, 2)*(1-t)*y[2] + pow(t, 3)*y[3];
	}

	// Bazier curve for Left Eye bros
	x[0] = -1.10f;
	x[1] = -1.125f;
	x[2] = -1.125f;
	x[3] = -1.150f;

	y[0] = 0.33f; 
	y[1] = 0.34f;
	y[2] = 0.34f;
	y[3] = 0.32f;

	for (i = 0, t = 0; i < 100; i++, t = t + 0.01)
	{
		xEb1[i] = pow(1-t, 3)*x[0] + 3*t*pow(1-t, 2)*x[1] + 3*pow(t, 2)*(1-t)*x[2] + pow(t, 3)*x[3];
		yEb1[i] = pow(1-t, 3)*y[0] + 3*t*pow(1-t, 2)*y[1] + 3*pow(t, 2)*(1-t)*y[2] + pow(t, 3)*y[3];
	}

	x[0] = -1.10f; 
	x[1] = -1.125f;
	x[2] = -1.125f;
	x[3] = -1.150f;

	y[0] = 0.32f; 
	y[1] = 0.33f;
	y[2] = 0.33f;
	y[3] = 0.32f;

	for (i = 0, t = 0; i < 100; i++, t = t + 0.01)
	{
		xEb2[i] = pow(1-t, 3)*x[0] + 3*t*pow(1-t, 2)*x[1] + 3*pow(t, 2)*(1-t)*x[2] + pow(t, 3)*x[3];
		yEb2[i] = pow(1-t, 3)*y[0] + 3*t*pow(1-t, 2)*y[1] + 3*pow(t, 2)*(1-t)*y[2] + pow(t, 3)*y[3];
	}

	// Left Eye upper
	x[0] = -1.10f;
	x[1] = -1.125f;
	x[2] = -1.125f;
	x[3] = -1.140f;

	y[0] = 0.31f;
	y[1] = 0.32f;
	y[2] = 0.32f;
	y[3] = 0.31f;

	for (i = 0, t = 0; i < 100; i++, t = t + 0.01)
	{
		xEye1[i] = pow(1-t, 3)*x[0] + 3*t*pow(1-t, 2)*x[1] + 3*pow(t, 2)*(1-t)*x[2] + pow(t, 3)*x[3];
		yEye1[i] = pow(1-t, 3)*y[0] + 3*t*pow(1-t, 2)*y[1] + 3*pow(t, 2)*(1-t)*y[2] + pow(t, 3)*y[3];
	}

	// Left Eye lower
	x[0] = -1.10f; 
	x[1] = -1.125f;
	x[2] = -1.125f;
	x[3] = -1.140f;

	y[0] = 0.31f;
	y[1] = 0.30f;
	y[2] = 0.30f;
	y[3] = 0.31f;

	for (i = 0, t = 0; i < 100; i++, t = t + 0.01)
	{
		xEye2[i] = pow(1-t, 3)*x[0] + 3*t*pow(1-t, 2)*x[1] + 3*pow(t, 2)*(1-t)*x[2] + pow(t, 3)*x[3];
		yEye2[i] = pow(1-t, 3)*y[0] + 3*t*pow(1-t, 2)*y[1] + 3*pow(t, 2)*(1-t)*y[2] + pow(t, 3)*y[3];
	}

	// Shal on guru's upper body
	x[0] = -1.07f;
	x[1] = -1.10f;
	x[2] = -1.26f;
	x[3] = -1.34f;

	y[0] = 0.20f;
	y[1] = 0.05f;
	y[2] = -0.08f;
	y[3] = -0.25f;

	for (i = 0, t = 0; i < 100; i++, t = t + 0.01)
	{
		xShal1[i] = pow(1-t, 3)*x[0] + 3*t*pow(1-t, 2)*x[1] + 3*pow(t, 2)*(1-t)*x[2] + pow(t, 3)*x[3];
		yShal1[i] = pow(1-t, 3)*y[0] + 3*t*pow(1-t, 2)*y[1] + 3*pow(t, 2)*(1-t)*y[2] + pow(t, 3)*y[3];
	}

	x[0] = -1.0f; 
	x[1] = -1.05f;
	x[2] = -1.05f;
	x[3] = -1.28f;

	y[0] = -0.14f;
	y[1] = -0.20f;
	y[2] = -0.20f;
	y[3] = -0.25f;

	for (i = 0, t = 0; i < 100; i++, t = t + 0.01)
	{
		xShal2[i] = pow(1-t, 3)*x[0] + 3*t*pow(1-t, 2)*x[1] + 3*pow(t, 2)*(1-t)*x[2] + pow(t, 3)*x[3];
		yShal2[i] = pow(1-t, 3)*y[0] + 3*t*pow(1-t, 2)*y[1] + 3*pow(t, 2)*(1-t)*y[2] + pow(t, 3)*y[3];
	}


	// create the shishya back here
	x[0] = -0.45f;
	x[1] = -0.51f;
	x[2] = -0.44f;
	x[3] = -0.42f;

	y[0] = -0.47f;
	y[1] = -0.55f;
	y[2] = -0.66f;
	y[3] = -0.70f;

	for (i = 0, t = 0; i < 100; i++, t = t + 0.01)
	{
		xShishya1[i] = pow(1-t, 3)*x[0] + 3*t*pow(1-t, 2)*x[1] + 3*pow(t, 2)*(1-t)*x[2] + pow(t, 3)*x[3];
		yShishya1[i] = pow(1-t, 3)*y[0] + 3*t*pow(1-t, 2)*y[1] + 3*pow(t, 2)*(1-t)*y[2] + pow(t, 3)*y[3];
	}

	x[0] = -0.28f;
	x[1] = -0.21f;
	x[2] = -0.30f;
	x[3] = -0.29f;

	y[0] = -0.47f;
	y[1] = -0.53f;
	y[2] = -0.67f;
	y[3] = -0.72f;

	for (i = 0, t = 0; i < 100; i++, t = t + 0.01)
	{
		xShishya2[i] = pow(1-t, 3)*x[0] + 3*t*pow(1-t, 2)*x[1] + 3*pow(t, 2)*(1-t)*x[2] + pow(t, 3)*x[3];
		yShishya2[i] = pow(1-t, 3)*y[0] + 3*t*pow(1-t, 2)*y[1] + 3*pow(t, 2)*(1-t)*y[2] + pow(t, 3)*y[3];
	}

	// Kutiya roof
	x[0] = 1.05f;
	x[1] = 1.625f;
	x[2] = 1.825f;
	x[3] = 2.40f;

	y[0] = 0.45f;
	y[1] = 0.85f;
	y[2] = 0.85f;
	y[3] = 0.44f;

	for (i = 0, t = 0; i < 100; i++, t = t + 0.01)
	{
		xRoof[i] = pow(1-t, 3)*x[0] + 3*t*pow(1-t, 2)*x[1] + 3*pow(t, 2)*(1-t)*x[2] + pow(t, 3)*x[3];
		yRoof[i] = pow(1-t, 3)*y[0] + 3*t*pow(1-t, 2)*y[1] + 3*pow(t, 2)*(1-t)*y[2] + pow(t, 3)*y[3];
	}

	// Kutiya Door
	x[0] = 1.60f;
	x[1] = 1.70f;
	x[2] = 1.70f;
	x[3] = 1.80f;

	y[0] = 0.35f;
	y[1] = 0.40f;
	y[2] = 0.40f;
	y[3] = 0.35f;

	for (i = 0, t = 0; i < 100; i++, t = t + 0.01)
	{
		xDoor[i] = pow(1-t, 3)*x[0] + 3*t*pow(1-t, 2)*x[1] + 3*pow(t, 2)*(1-t)*x[2] + pow(t, 3)*x[3];
		yDoor[i] = pow(1-t, 3)*y[0] + 3*t*pow(1-t, 2)*y[1] + 3*pow(t, 2)*(1-t)*y[2] + pow(t, 3)*y[3];
	}

	// River calculations here
	x[0] = -2.25f;
	x[1] = -0.12f;
	x[2] = -0.12f;
	x[3] = 2.0f;

	y[0] = 0.40;
	y[1] = 0.48f;
	y[2] = 0.48f;
	y[3] = 0.60f;

	for (i = 0, t = 0; i < 200; i++, t = t + 0.01)
	{
		xRiver1[i] = pow(1-t, 3)*x[0] + 3*t*pow(1-t, 2)*x[1] + 3*pow(t, 2)*(1-t)*x[2] + pow(t, 3)*x[3];
		yRiver1[i] = pow(1-t, 3)*y[0] + 3*t*pow(1-t, 2)*y[1] + 3*pow(t, 2)*(1-t)*y[2] + pow(t, 3)*y[3];
	}

	x[0] = -2.25f;
	x[1] = -0.875f;
	x[2] = 0.625f;
	x[3] = 2.0f;

	y[0] = -0.25;
	y[1] = -0.20f;
	y[2] = 0.0f;
	y[3] = 0.15f;

	for (i = 0, t = 0; i < 200; i++, t = t + 0.01)
	{
		xRiver2[i] = pow(1-t, 3)*x[0] + 3*t*pow(1-t, 2)*x[1] + 3*pow(t, 2)*(1-t)*x[2] + pow(t, 3)*x[3];
		yRiver2[i] = pow(1-t, 3)*y[0] + 3*t*pow(1-t, 2)*y[1] + 3*pow(t, 2)*(1-t)*y[2] + pow(t, 3)*y[3];
	}
}

void Tulas_Adesh(float x_pos, float y_pos, float percent)
{
	// Call to design vrindavan
	Tulsi_Vrindavan(x_pos, y_pos, percent);
	
	// Call to design tulsi branches
	Tulsi_Branches(x_pos, y_pos, percent);

	// Call for tulsi leaf
	Tulsi_leaf(x_pos, y_pos, percent);
}

void Tulsi_Vrindavan(float x_pos, float y_pos, float percent)
{
	// main quad for tulsi
	glBegin(GL_QUADS);

	//import the color
	glColor3f(1.0f, 1.0f, 1.0f);

	//set the vertices
	glVertex2d(VALUE_FROM_PERCENT(0.51f, percent) + x_pos, VALUE_FROM_PERCENT( -0.20f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.51f, percent) + x_pos, VALUE_FROM_PERCENT( -0.40f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.65f, percent) + x_pos, VALUE_FROM_PERCENT( -0.40f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.65f, percent) + x_pos, VALUE_FROM_PERCENT( -0.20f , percent) + y_pos);

	glEnd();

	// Upper Rechangular Quad
	glBegin(GL_QUADS);

	//import the color
	glColor3f(0.9f, 0.0f, 0.0f);

	//set the vertices
	glVertex2d(VALUE_FROM_PERCENT(0.48f, percent) + x_pos, VALUE_FROM_PERCENT( -0.16f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.48f, percent) + x_pos, VALUE_FROM_PERCENT( -0.23f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.68f, percent) + x_pos, VALUE_FROM_PERCENT( -0.23f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.68f, percent) + x_pos, VALUE_FROM_PERCENT( -0.16f , percent) + y_pos);

	glEnd();

	//Set Triangles on upper quad
	glBegin(GL_TRIANGLES);

	//Set the color
	glColor3f(0.9f, 0.0f, 0.0f);

	// Set the vertices for right triangle
	glVertex3f(VALUE_FROM_PERCENT(0.68f, percent) + x_pos, VALUE_FROM_PERCENT( -0.11f, percent) + y_pos, 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(0.68f, percent) + x_pos, VALUE_FROM_PERCENT( -0.16f, percent) + y_pos, 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(0.64f, percent) + x_pos, VALUE_FROM_PERCENT( -0.16f, percent) + y_pos, 0.0f);

	// Set the vertice for left triangle
	glVertex3f(VALUE_FROM_PERCENT(0.48f, percent) + x_pos, VALUE_FROM_PERCENT( -0.11f, percent) + y_pos, 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(0.48f, percent) + x_pos, VALUE_FROM_PERCENT( -0.16f, percent) + y_pos, 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(0.52f, percent) + x_pos, VALUE_FROM_PERCENT( -0.16f, percent) + y_pos, 0.0f);

	glEnd();

	// Lower Rectangular Quad
	glBegin(GL_QUADS);

	//import the color
	glColor3f(0.9f, 0.0f, 0.0f);

	//set the vertices
	glVertex2d(VALUE_FROM_PERCENT(0.48f, percent) + x_pos, VALUE_FROM_PERCENT( -0.40f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.48f, percent) + x_pos, VALUE_FROM_PERCENT( -0.45f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.68f, percent) + x_pos, VALUE_FROM_PERCENT( -0.45f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.68f, percent) + x_pos, VALUE_FROM_PERCENT( -0.40f , percent) + y_pos);

	glEnd();
/*
	// Swastik using line strips and point
	glBegin(GL_LINE_STRIP);

	// Draw the lines
	glVertex2f(VALUE_FROM_PERCENT(0.60f, percent) + x_pos, VALUE_FROM_PERCENT( -0.26f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.26f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.30f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.56f, percent) + x_pos, VALUE_FROM_PERCENT( -0.30f , percent) + y_pos);

	glEnd();

	// 1. Dots inside swastik: right upper
	glBegin(GL_QUADS);

	// Draw the points
	glVertex2f(VALUE_FROM_PERCENT(0.587000, percent) + x_pos, VALUE_FROM_PERCENT( -0.267000 , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.593000, percent) + x_pos, VALUE_FROM_PERCENT( -0.267000 , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.593000, percent) + x_pos, VALUE_FROM_PERCENT( -0.273000 , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.587000, percent) + x_pos, VALUE_FROM_PERCENT( -0.273000 , percent) + y_pos);

	glEnd();

	// 2. Dots inside swastik: right lower
	glBegin(GL_QUADS);

	// Draw the points
	glVertex2f(VALUE_FROM_PERCENT(0.587000, percent) + x_pos, VALUE_FROM_PERCENT( -0.287000 , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.593000, percent) + x_pos, VALUE_FROM_PERCENT( -0.287000 , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.593000, percent) + x_pos, VALUE_FROM_PERCENT( -0.293000 , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.587000, percent) + x_pos, VALUE_FROM_PERCENT( -0.293000 , percent) + y_pos);

	glEnd();

	// 3. Dots inside swastik: left lower
	glBegin(GL_QUADS);

	// Draw the points
	glVertex2f(VALUE_FROM_PERCENT(0.567000, percent) + x_pos, VALUE_FROM_PERCENT( -0.287000 , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.573000, percent) + x_pos, VALUE_FROM_PERCENT( -0.287000 , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.573000, percent) + x_pos, VALUE_FROM_PERCENT( -0.293000 , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.567000, percent) + x_pos, VALUE_FROM_PERCENT( -0.293000 , percent) + y_pos);

	glEnd();

	// 4. Dots inside swastik: left upper
	glBegin(GL_QUADS);

	// Draw the points
	glVertex2f(VALUE_FROM_PERCENT(0.567000, percent) + x_pos, VALUE_FROM_PERCENT( -0.267000 , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.573000, percent) + x_pos, VALUE_FROM_PERCENT( -0.267000 , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.573000, percent) + x_pos, VALUE_FROM_PERCENT( -0.273000 , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.567000, percent) + x_pos, VALUE_FROM_PERCENT( -0.273000 , percent) + y_pos);

	glEnd();

	glBegin(GL_LINE_STRIP);

	glVertex2f(VALUE_FROM_PERCENT(0.56f, percent) + x_pos, VALUE_FROM_PERCENT( -0.26f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.56f, percent) + x_pos, VALUE_FROM_PERCENT( -0.28f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.60f, percent) + x_pos, VALUE_FROM_PERCENT( -0.28f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.60f, percent) + x_pos, VALUE_FROM_PERCENT( -0.30f , percent) + y_pos);

	glEnd();
*/
	// Middle Polygon for diya place
	glBegin(GL_POLYGON);

	//import the color
	glColor3f(0.1f, 0.1f, 0.1f);

	//set the vertices
	glVertex2d(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.25f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.56f, percent) + x_pos, VALUE_FROM_PERCENT( -0.28f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.56f, percent) + x_pos, VALUE_FROM_PERCENT( -0.35f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.60f, percent) + x_pos, VALUE_FROM_PERCENT( -0.35f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.60f, percent) + x_pos, VALUE_FROM_PERCENT( -0.28f , percent) + y_pos);

	glEnd();

	// Quad for diya
	glBegin(GL_QUADS);

	//import the color
	glColor3f(1.0f, 0.6470588235294, 0.0f);

	//set the vertices for diya
	glVertex2d(VALUE_FROM_PERCENT(0.5750f, percent) + x_pos, VALUE_FROM_PERCENT( -0.35f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.5850f, percent) + x_pos, VALUE_FROM_PERCENT( -0.35f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.59f, percent) + x_pos, VALUE_FROM_PERCENT( -0.33f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.57f, percent) + x_pos, VALUE_FROM_PERCENT( -0.33f , percent) + y_pos);

	//import the color for flame
	glColor3f(1.0f, 0.0, 0.0f);

	// set the vertices for flame
	glVertex2d(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.33f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.5825f, percent) + x_pos, VALUE_FROM_PERCENT( -0.31f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.29f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.5775f, percent) + x_pos, VALUE_FROM_PERCENT( -0.33f , percent) + y_pos);

	glEnd();
}

void Tulsi_leaf(float x_pos, float y_pos, float percent)
{
	// Quads for leafs
	glBegin(GL_QUADS);

	// Set the color for leaf
    //glColor3f(0.0f, 0.4f, 0.1f);
	glColor3f(0.1f, 0.8f, 0.1f);

	// set the vertices

	// 1. bottom right first from down
	glVertex2d(VALUE_FROM_PERCENT(0.63f, percent) + x_pos, VALUE_FROM_PERCENT( -0.13f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.64f, percent) + x_pos, VALUE_FROM_PERCENT( -0.12f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.65f, percent) + x_pos, VALUE_FROM_PERCENT( -0.13f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.64f, percent) + x_pos, VALUE_FROM_PERCENT( -0.14f , percent) + y_pos);

	glVertex2d(VALUE_FROM_PERCENT(0.62f, percent) + x_pos, VALUE_FROM_PERCENT( -0.10f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.62f, percent) + x_pos, VALUE_FROM_PERCENT( -0.09f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.64f, percent) + x_pos, VALUE_FROM_PERCENT( -0.08f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.63f, percent) + x_pos, VALUE_FROM_PERCENT( -0.10f , percent) + y_pos);

	glVertex2d(VALUE_FROM_PERCENT(0.66f, percent) + x_pos, VALUE_FROM_PERCENT( -0.11f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.67f, percent) + x_pos, VALUE_FROM_PERCENT( -0.10f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.69f, percent) + x_pos, VALUE_FROM_PERCENT( -0.11f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.67f, percent) + x_pos, VALUE_FROM_PERCENT( -0.12f , percent) + y_pos);

	glVertex2d(VALUE_FROM_PERCENT(0.67f, percent) + x_pos, VALUE_FROM_PERCENT( -0.07f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.67f, percent) + x_pos, VALUE_FROM_PERCENT( -0.06f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.69f, percent) + x_pos, VALUE_FROM_PERCENT( -0.05f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.68f, percent) + x_pos, VALUE_FROM_PERCENT( -0.07f , percent) + y_pos);

	glVertex2d(VALUE_FROM_PERCENT(0.70f, percent) + x_pos, VALUE_FROM_PERCENT( -0.09f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.71f, percent) + x_pos, VALUE_FROM_PERCENT( -0.08f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.73f, percent) + x_pos, VALUE_FROM_PERCENT( -0.09f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.71f, percent) + x_pos, VALUE_FROM_PERCENT( -0.10f , percent) + y_pos);

	glVertex2d(VALUE_FROM_PERCENT(0.70f, percent) + x_pos, VALUE_FROM_PERCENT( -0.07f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.70f, percent) + x_pos, VALUE_FROM_PERCENT( -0.06f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.72f, percent) + x_pos, VALUE_FROM_PERCENT( -0.05f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.71f, percent) + x_pos, VALUE_FROM_PERCENT( -0.07f , percent) + y_pos);

	// 2. Middle Right branch
	glVertex2d(VALUE_FROM_PERCENT(0.62f, percent) + x_pos, VALUE_FROM_PERCENT( -0.06f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.63f, percent) + x_pos, VALUE_FROM_PERCENT( -0.05f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.65f, percent) + x_pos, VALUE_FROM_PERCENT( -0.06f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.63f, percent) + x_pos, VALUE_FROM_PERCENT( -0.07f , percent) + y_pos);

	glVertex2d(VALUE_FROM_PERCENT(0.61f, percent) + x_pos, VALUE_FROM_PERCENT( -0.03f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.60f, percent) + x_pos, VALUE_FROM_PERCENT( -0.02f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.61f, percent) + x_pos, VALUE_FROM_PERCENT( -0.00f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.62f, percent) + x_pos, VALUE_FROM_PERCENT( -0.02f , percent) + y_pos);

	glVertex2d(VALUE_FROM_PERCENT(0.65f, percent) + x_pos, VALUE_FROM_PERCENT( -0.03f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.66f, percent) + x_pos, VALUE_FROM_PERCENT( -0.02f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.68f, percent) + x_pos, VALUE_FROM_PERCENT( -0.03f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.66f, percent) + x_pos, VALUE_FROM_PERCENT( -0.04f , percent) + y_pos);

	glVertex2d(VALUE_FROM_PERCENT(0.64f, percent) + x_pos, VALUE_FROM_PERCENT( -0.02f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.64f, percent) + x_pos, VALUE_FROM_PERCENT( -0.01f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.66f, percent) + x_pos, VALUE_FROM_PERCENT( -0.00f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.65f, percent) + x_pos, VALUE_FROM_PERCENT( -0.02f , percent) + y_pos);

	// 3. Third right left from bottom
	glVertex2d(VALUE_FROM_PERCENT(0.59f, percent) + x_pos, VALUE_FROM_PERCENT( -0.04f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.59f, percent) + x_pos, VALUE_FROM_PERCENT( -0.03f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.60f, percent) + x_pos, VALUE_FROM_PERCENT( -0.02f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.60f, percent) + x_pos, VALUE_FROM_PERCENT( -0.04f , percent) + y_pos);

	// 4. Second top right leaf
	glVertex2d(VALUE_FROM_PERCENT(0.59f, percent) + x_pos, VALUE_FROM_PERCENT( -0.00f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.59f, percent) + x_pos, VALUE_FROM_PERCENT( +0.01f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.61f, percent) + x_pos, VALUE_FROM_PERCENT( +0.02f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.60f, percent) + x_pos, VALUE_FROM_PERCENT( -0.00f , percent) + y_pos);

	// 5. Top leaf
	glVertex2d(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( +0.01f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.57f, percent) + x_pos, VALUE_FROM_PERCENT( +0.02f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( +0.04f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.59f, percent) + x_pos, VALUE_FROM_PERCENT( +0.02f , percent) + y_pos);

	// 6. Bottom left first from down
	glVertex2d(VALUE_FROM_PERCENT(0.54f, percent) + x_pos, VALUE_FROM_PERCENT( -0.13f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.53f, percent) + x_pos, VALUE_FROM_PERCENT( -0.12f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.51f, percent) + x_pos, VALUE_FROM_PERCENT( -0.13f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.53f, percent) + x_pos, VALUE_FROM_PERCENT( -0.14f , percent) + y_pos);

	glVertex2d(VALUE_FROM_PERCENT(0.54f, percent) + x_pos, VALUE_FROM_PERCENT( -0.10f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.54f, percent) + x_pos, VALUE_FROM_PERCENT( -0.09f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.52f, percent) + x_pos, VALUE_FROM_PERCENT( -0.08f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.53f, percent) + x_pos, VALUE_FROM_PERCENT( -0.10f , percent) + y_pos);

	glVertex2d(VALUE_FROM_PERCENT(0.49f, percent) + x_pos, VALUE_FROM_PERCENT( -0.10f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.48f, percent) + x_pos, VALUE_FROM_PERCENT( -0.09f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.46f, percent) + x_pos, VALUE_FROM_PERCENT( -0.10f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.48f, percent) + x_pos, VALUE_FROM_PERCENT( -0.11f , percent) + y_pos);

	glVertex2d(VALUE_FROM_PERCENT(0.49f, percent) + x_pos, VALUE_FROM_PERCENT( -0.07f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.49f, percent) + x_pos, VALUE_FROM_PERCENT( -0.06f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.47f, percent) + x_pos, VALUE_FROM_PERCENT( -0.05f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.48f, percent) + x_pos, VALUE_FROM_PERCENT( -0.07f , percent) + y_pos);

	glVertex2d(VALUE_FROM_PERCENT(0.46f, percent) + x_pos, VALUE_FROM_PERCENT( -0.07f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.46f, percent) + x_pos, VALUE_FROM_PERCENT( -0.06f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.43f, percent) + x_pos, VALUE_FROM_PERCENT( -0.05f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.45f, percent) + x_pos, VALUE_FROM_PERCENT( -0.07f , percent) + y_pos);

	// 7. Bottom left second from down branch
	glVertex2d(VALUE_FROM_PERCENT(0.57f, percent) + x_pos, VALUE_FROM_PERCENT( -0.09f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.56f, percent) + x_pos, VALUE_FROM_PERCENT( -0.09f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.55f, percent) + x_pos, VALUE_FROM_PERCENT( -0.10f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.56f, percent) + x_pos, VALUE_FROM_PERCENT( -0.10f , percent) + y_pos);

	glVertex2d(VALUE_FROM_PERCENT(0.57f, percent) + x_pos, VALUE_FROM_PERCENT( -0.09f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.09f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.08f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.57f, percent) + x_pos, VALUE_FROM_PERCENT( -0.08f , percent) + y_pos);

	glVertex2d(VALUE_FROM_PERCENT(0.56f, percent) + x_pos, VALUE_FROM_PERCENT( -0.08f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.55f, percent) + x_pos, VALUE_FROM_PERCENT( -0.08f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.54f, percent) + x_pos, VALUE_FROM_PERCENT( -0.06f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.56f, percent) + x_pos, VALUE_FROM_PERCENT( -0.07f , percent) + y_pos);

	// 8. Top left second from up branch
	glVertex2d(VALUE_FROM_PERCENT(0.54f, percent) + x_pos, VALUE_FROM_PERCENT( -0.05f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.53f, percent) + x_pos, VALUE_FROM_PERCENT( -0.04f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.51f, percent) + x_pos, VALUE_FROM_PERCENT( -0.05f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.53f, percent) + x_pos, VALUE_FROM_PERCENT( -0.06f , percent) + y_pos);

	glVertex2d(VALUE_FROM_PERCENT(0.54f, percent) + x_pos, VALUE_FROM_PERCENT( -0.02f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.53f, percent) + x_pos, VALUE_FROM_PERCENT( -0.02f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.52f, percent) + x_pos, VALUE_FROM_PERCENT( -0.00f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.54f, percent) + x_pos, VALUE_FROM_PERCENT( -0.01f , percent) + y_pos);

	glVertex2d(VALUE_FROM_PERCENT(0.51f, percent) + x_pos, VALUE_FROM_PERCENT( -0.02f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.50f, percent) + x_pos, VALUE_FROM_PERCENT( -0.02f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.48f, percent) + x_pos, VALUE_FROM_PERCENT( -0.00f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.51f, percent) + x_pos, VALUE_FROM_PERCENT( -0.01f , percent) + y_pos);

	// 9. Top left branch with single leaf
	glVertex2d(VALUE_FROM_PERCENT(0.56f, percent) + x_pos, VALUE_FROM_PERCENT( -0.01f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.55f, percent) + x_pos, VALUE_FROM_PERCENT( -0.01f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.54f, percent) + x_pos, VALUE_FROM_PERCENT( +0.01f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.56f, percent) + x_pos, VALUE_FROM_PERCENT( -0.00f , percent) + y_pos);

	glEnd();
}

void Tulsi_Branches(float x_pos, float y_pos, float percent)
{
	//Tulas plant branches
	glBegin(GL_LINE_STRIP);

	// Set the color
	glColor3f(0.40f, 0.0f, 0.0f);
	//glColor3f(0.0f, 0.9f, 0.0f);

	// Virtical strip
	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( 0.01f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.16f , percent) + y_pos);

	// Sub-strip from right bottom branch
	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.14f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.70f, percent) + x_pos, VALUE_FROM_PERCENT( -0.07f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.14f , percent) + y_pos);

	glVertex2f(VALUE_FROM_PERCENT(0.60f, percent) + x_pos, VALUE_FROM_PERCENT( -0.13f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.63f, percent) + x_pos, VALUE_FROM_PERCENT( -0.13f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.60f, percent) + x_pos, VALUE_FROM_PERCENT( -0.13f , percent) + y_pos);

	glVertex2f(VALUE_FROM_PERCENT(0.61f, percent) + x_pos, VALUE_FROM_PERCENT( -0.12f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.62f, percent) + x_pos, VALUE_FROM_PERCENT( -0.10f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.61f, percent) + x_pos, VALUE_FROM_PERCENT( -0.12f , percent) + y_pos);

	glVertex2f(VALUE_FROM_PERCENT(0.63f, percent) + x_pos, VALUE_FROM_PERCENT( -0.11f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.66f, percent) + x_pos, VALUE_FROM_PERCENT( -0.11f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.63f, percent) + x_pos, VALUE_FROM_PERCENT( -0.11f , percent) + y_pos);

	glVertex2f(VALUE_FROM_PERCENT(0.65f, percent) + x_pos, VALUE_FROM_PERCENT( -0.10f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.67f, percent) + x_pos, VALUE_FROM_PERCENT( -0.07f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.65f, percent) + x_pos, VALUE_FROM_PERCENT( -0.10f , percent) + y_pos);

	glVertex2f(VALUE_FROM_PERCENT(0.67f, percent) + x_pos, VALUE_FROM_PERCENT( -0.09f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.70f, percent) + x_pos, VALUE_FROM_PERCENT( -0.09f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.67f, percent) + x_pos, VALUE_FROM_PERCENT( -0.09f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.14f , percent) + y_pos);

	// #################################

	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.08f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.64f, percent) + x_pos, VALUE_FROM_PERCENT( -0.02f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.08f , percent) + y_pos);

	glVertex2f(VALUE_FROM_PERCENT(0.60f, percent) + x_pos, VALUE_FROM_PERCENT( -0.06f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.62f, percent) + x_pos, VALUE_FROM_PERCENT( -0.06f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.60f, percent) + x_pos, VALUE_FROM_PERCENT( -0.06f , percent) + y_pos);

	glVertex2f(VALUE_FROM_PERCENT(0.61f, percent) + x_pos, VALUE_FROM_PERCENT( -0.05f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.61f, percent) + x_pos, VALUE_FROM_PERCENT( -0.03f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.61f, percent) + x_pos, VALUE_FROM_PERCENT( -0.05f , percent) + y_pos);

	glVertex2f(VALUE_FROM_PERCENT(0.63f, percent) + x_pos, VALUE_FROM_PERCENT( -0.03f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.66f, percent) + x_pos, VALUE_FROM_PERCENT( -0.03f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.63f, percent) + x_pos, VALUE_FROM_PERCENT( -0.03f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.08f , percent) + y_pos);

	// #################################

	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.05f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.59f, percent) + x_pos, VALUE_FROM_PERCENT( -0.04f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.05f , percent) + y_pos);

	// #################################

	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.01f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.59f, percent) + x_pos, VALUE_FROM_PERCENT( 0.00f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.01f , percent) + y_pos);

	// Sub-strip for left branch
	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.14f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.46f, percent) + x_pos, VALUE_FROM_PERCENT( -0.07f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.14f , percent) + y_pos);

	glVertex2f(VALUE_FROM_PERCENT(0.56f, percent) + x_pos, VALUE_FROM_PERCENT( -0.13f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.54f, percent) + x_pos, VALUE_FROM_PERCENT( -0.13f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.56f, percent) + x_pos, VALUE_FROM_PERCENT( -0.13f , percent) + y_pos);

	glVertex2f(VALUE_FROM_PERCENT(0.55f, percent) + x_pos, VALUE_FROM_PERCENT( -0.12f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.54f, percent) + x_pos, VALUE_FROM_PERCENT( -0.10f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.55f, percent) + x_pos, VALUE_FROM_PERCENT( -0.12f , percent) + y_pos);

	glVertex2f(VALUE_FROM_PERCENT(0.51f, percent) + x_pos, VALUE_FROM_PERCENT( -0.10f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.49f, percent) + x_pos, VALUE_FROM_PERCENT( -0.10f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.51f, percent) + x_pos, VALUE_FROM_PERCENT( -0.10f , percent) + y_pos);

	glVertex2f(VALUE_FROM_PERCENT(0.50f, percent) + x_pos, VALUE_FROM_PERCENT( -0.09f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.49f, percent) + x_pos, VALUE_FROM_PERCENT( -0.07f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.50f, percent) + x_pos, VALUE_FROM_PERCENT( -0.09f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.14f , percent) + y_pos);

	// #################################

	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.11f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.56f, percent) + x_pos, VALUE_FROM_PERCENT( -0.08f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.11f , percent) + y_pos);

	// #################################

	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.06f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.51f, percent) + x_pos, VALUE_FROM_PERCENT( -0.02f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.06f , percent) + y_pos);

	glVertex2f(VALUE_FROM_PERCENT(0.56f, percent) + x_pos, VALUE_FROM_PERCENT( -0.05f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.54f, percent) + x_pos, VALUE_FROM_PERCENT( -0.05f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.56f, percent) + x_pos, VALUE_FROM_PERCENT( -0.05f , percent) + y_pos);

	glVertex2f(VALUE_FROM_PERCENT(0.55f, percent) + x_pos, VALUE_FROM_PERCENT( -0.04f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.54f, percent) + x_pos, VALUE_FROM_PERCENT( -0.02f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.55f, percent) + x_pos, VALUE_FROM_PERCENT( -0.04f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.06f , percent) + y_pos);

	// #################################

	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.03f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.56f, percent) + x_pos, VALUE_FROM_PERCENT( -0.01f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.03f , percent) + y_pos);

	glEnd();
}

//EOF