#include <windows.h>	// Compiler la samajnarya environmental variable madhlya include file PATH  // Around 3.5 lack API's are present in windows.h either directly or indirectly.
#include <stdio.h>
#include <stdlib.h>		// Library for exit() function
#include <math.h>

// OpenGL Related Header Files
#include <gl/GL.h>
#include <gl/GLU.h>

// Custom Header Files

#include "vanvas.h"

#define	VALUE_FROM_PERCENT(complete, percent)	(complete * percent / 100.0f)

// Tree leaves variables
static float pt_x = 0.0f;
static float pt_y = 0.0f;

BOOL NRD_vanvasAnimation = TRUE;

float NRD_RLS_updatey = -0.9f;
float NRD_RLS_updatex;
float NRD_RLS_updateTransform = -3.0f;

float NRD_Birds_x = 1.5f;
float NRD_Birds_y = 1.1f;

// NRD_RLS_updatey = -0.9;
// NRD_RLS_updateTransform = -3.0f;
// NRD_Birds_x = 1.5f;
// NRD_Birds_y = 1.1f;

void NRD_vanvas(void)
{
	// Animation 
	NRD_update();

    // Set to Identity matrix
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -3.0f);
	glBegin(GL_QUADS);
	{
		glColor3f(95.0/256.0f, 161.0/256.0f, 191.0/256.0f);
		glVertex3f(2.5f, 2.5f, 0.0f);
		glVertex3f(-2.5f, 2.5f, 0.0f);
		glColor3f(95.0/256.0f, 161.0/256.0f, 191.0/256.0f);
		glVertex3f(-2.5f, -2.5f, 0.0f);
		glVertex3f(2.5f, -2.5f, 0.0f);
	}
	glEnd();

	// GreenField
	glBegin(GL_POLYGON);
	{
		glColor3f(133.0/256.0f, 104.0/256.0f, 74.0/256.0f);
		// glColor3f(137.0/256.0f, 95.0/256.0f, 79.0/256.0f);
		glVertex3f(3.0f, 0.3f, 0.0f);
		glVertex3f(-3.0f, 0.3f, 0.0f);
		glColor3f(133.0/256.0f, 104.0/256.0f, 74.0/256.0f);
		glVertex3f(-3.0f, -3.0f, 0.0f);
		glVertex3f(3.0f, -3.0f, 0.0f);
	}
	glEnd();

	// Translate Triangle backward by z for tree call
	NRD_draw_greenfield(0.10f, 0.3f, 100.0f);
	NRD_draw_greenfield(-2.5f, 0.3f, 100.0f);
	
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -3.0f);
	NRD_draw_way(0.0f, 0.02f, 50.0f);
		
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -10.0f);
	NRD_Tree(-0.4f, 1.4f, 10.0f, 60.0f);	// left
	NRD_Tree(1.1f, 1.2f, 10.0, 60.0);		// right

	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -8.5);
	NRD_Tree(-0.5f, 1.0f, 10.0f, 60.0f);	// left
	NRD_Tree(1.4f, 1.0f, 10.0, 60.0);		// right
	
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -5.0);
	NRD_Tree(-0.48f, -0.17f, 10.0f, 60.0f);	// left
	NRD_Tree(-1.4f, -0.27f, 10.0f, 60.0f);	// left
	NRD_Tree(-1.7f, -0.4f, 10.0f, 60.0f);	// left
	NRD_Tree(-2.5f, -0.3f, 10.0f, 60.0f);	// left

	NRD_Tree(1.1f, -0.4f, 10.0, 60.0);		// right
	NRD_Tree(2.1f, -0.6f, 10.0, 60.0);		// right
	NRD_Tree(2.8f, -0.7f, 10.0, 60.0);		// right
	NRD_Tree(3.4f, -0.6, 10.0, 60.0);		// right

	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -5.0);
	NRD_Birds_Amol(NRD_Birds_x, NRD_Birds_y);

	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -2.3);
	NRD_Tree(-0.25f, -0.31f, 10.0f, 60.0f);	// left
	NRD_Tree(-0.6f, -0.35f, 10.0f, 60.0f);	// left
	NRD_Tree(1.1f, -0.22f, 10.0, 60.0);		// right
	NRD_Tree(1.4f, -0.30f, 10.0, 60.0);		// right

	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -2.0);
	NRD_Tree(-0.9f, -0.1f, 10.0f, 60.0f);	// left
	NRD_Tree(1.7f, -0.15f, 10.0, 60.0);		// right

	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, NRD_RLS_updateTransform);

	NRD_draw_sita(-0.28f + NRD_RLS_updatex, NRD_RLS_updatey, 100.0f);
	NRD_draw_ram(-0.17f + NRD_RLS_updatex, NRD_RLS_updatey, 100.0f);
 	NRD_draw_laxman(-0.05f + NRD_RLS_updatex, NRD_RLS_updatey, 100.0f);
    
}

void NRD_draw_ram(float x_pos, float y_pos, float percent)
{
	// Variable Declarations
    float x = 0.0f;
    float y = 0.0f;

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
	
	//********************** left curve of body ********************************************** */
	xl[0] = -0.02;  xl[1] = -0.075; xl[2] = -0.08;  xl[3] = -0.03;
	yl[0] =  0.05;  yl[1] =  0.11; yl[2] = -0.12;  yl[3] = -0.08;

	for(il=0, tl=0; tl<=1.0f; il++, tl+=0.008)	// here (1/0.008) = 125 so in array 125 points will be filled
	{
		xtl[il] = (pow(1-tl, 3)*xl[0]) + (3*tl*pow(1-tl, 2)*xl[1]) + (3*pow(tl,2)*pow(1-tl, 2)*xl[2]) + (pow(tl,3)*xl[3]);
		ytl[il] = (pow(1-tl, 3)*yl[0]) + (3*tl*pow(1-tl, 2)*yl[1]) + (3*pow(tl,2)*pow(1-tl, 2)*yl[2]) + (pow(tl,3)*yl[3]);
	}
	/******************************************************************************************* */

	//********************** Right curve of body ********************************************** */
	xr[0] = 0.02;  xr[1] = 0.075; xr[2] = 0.08;  xr[3] = 0.03;
	yr[0] = 0.05;  yr[1] = 0.11; yr[2] = -0.12;  yr[3] = -0.08;

	for(ir=0, tr =0; tr<=1.0f; ir++, tr+=0.008)		// here (1/0.008) = 125 so in array 125 points will be filled
	{
		xtr[ir] = (pow(1-tr, 3)*xr[0]) + (3*tr*pow(1-tr, 2)*xr[1]) + (3*pow(tr,2)*pow(1-tr, 2)*xr[2]) + (pow(tr,3)*xr[3]);
		ytr[ir] = (pow(1-tr, 3)*yr[0]) + (3*tr*pow(1-tr, 2)*yr[1]) + (3*pow(tr,2)*pow(1-tr, 2)*yr[2]) + (pow(tr,3)*yr[3]);
	}
	/******************************************************************************************* */

	glBegin(GL_TRIANGLE_STRIP);
	for(ir=0, il=0; ir<125, il<125; ir++, il++)
	{
		glColor3f(1.0f/255.0f, 58.0f/255.0f, 100.0f/255.0f);
		glVertex3f(VALUE_FROM_PERCENT(xtr[ir]+x_pos, percent), VALUE_FROM_PERCENT(ytr[ir]+y_pos, percent), 0.0f);
		glVertex3f(VALUE_FROM_PERCENT(xtl[il]+x_pos, percent), VALUE_FROM_PERCENT(ytl[il]+y_pos, percent), 0.0f);
	}
	glEnd();

	//********************** left curve of body ********************************************** */
	xl[0] = -0.02;  xl[1] = -0.065; xl[2] = -0.08;  xl[3] = -0.02;
	yl[0] = -0.07;  yl[1] = -0.12; yl[2] =  0.12;  yl[3] =  0.07;

	for(il=0, tl=0; tl<=1.0f; il++, tl+=0.008)	// here (1/0.008) = 125 so in array 125 points will be filled
	{
		xtl[il] = (pow(1-tl, 3)*xl[0]) + (3*tl*pow(1-tl, 2)*xl[1]) + (3*pow(tl,2)*pow(1-tl, 2)*xl[2]) + (pow(tl,3)*xl[3]);
		ytl[il] = (pow(1-tl, 3)*yl[0]) + (3*tl*pow(1-tl, 2)*yl[1]) + (3*pow(tl,2)*pow(1-tl, 2)*yl[2]) + (pow(tl,3)*yl[3]);
	}
	/******************************************************************************************* */

	//********************** Right curve of body ********************************************** */
	xr[0] = 0.02;  xr[1] = 0.065; xr[2] = 0.08;  xr[3] = 0.02;
	yr[0] = -0.07;  yr[1] = -0.12; yr[2] = 0.12;  yr[3] =  0.07;

	for(ir=0, tr =0; tr<=1.0f; ir++, tr+=0.008)		// here (1/0.008) = 125 so in array 125 points will be filled
	{
		xtr[ir] = (pow(1-tr, 3)*xr[0]) + (3*tr*pow(1-tr, 2)*xr[1]) + (3*pow(tr,2)*pow(1-tr, 2)*xr[2]) + (pow(tr,3)*xr[3]);
		ytr[ir] = (pow(1-tr, 3)*yr[0]) + (3*tr*pow(1-tr, 2)*yr[1]) + (3*pow(tr,2)*pow(1-tr, 2)*yr[2]) + (pow(tr,3)*yr[3]);
	}
	/******************************************************************************************* */

	glBegin(GL_TRIANGLE_STRIP);
	for(ir=0, il=0; ir<125, il<125; ir++, il++)
	{
		if(ir>95 && il>95)
		{
			glColor3f(0.0f, 0.0f, 0.0f);
		}
		else
		{
			glColor3f(1.0f/255.0f, 58.0f/255.0f, 100.0f/255.0f);
		}
		glVertex3f(VALUE_FROM_PERCENT(xtr[ir]+x_pos, percent), VALUE_FROM_PERCENT(ytr[ir]+y_pos, percent), 0.0f);
		glVertex3f(VALUE_FROM_PERCENT(xtl[il]+x_pos, percent), VALUE_FROM_PERCENT(ytl[il]+y_pos, percent), 0.0f);
	}
	glEnd();

	//********************************************** Dhanushya ********************************************** */
	xl[0] = -0.07;  xl[1] = -0.111; xl[2] = -0.087;  xl[3] = -0.059;
	yl[0] = -0.05;  yl[1] = -0.012; yl[2] = 0.079;  yl[3] = 0.0863;

	for(il=0, tl=0; tl<=1.0f; il++, tl+=0.008)	// here (1/0.008) = 125 so in array 125 points will be filled
	{
		xtl[il] = (pow(1-tl, 3)*xl[0]) + (3*tl*pow(1-tl, 2)*xl[1]) + (3*pow(tl,2)*pow(1-tl, 2)*xl[2]) + (pow(tl,3)*xl[3]);
		ytl[il] = (pow(1-tl, 3)*yl[0]) + (3*tl*pow(1-tl, 2)*yl[1]) + (3*pow(tl,2)*pow(1-tl, 2)*yl[2]) + (pow(tl,3)*yl[3]);
	}
	/**********************************************************************************************************/

	if(NRD_RLS_updatey < 0.0f)
		glPointSize(2.0);
	else
		glPointSize(1.0f);

	glBegin(GL_POINTS);
	for(il=0, tl =0; tl<=1.0f; il++, tl+=0.008)
	{
		if(tl> 0.80f)
		{
			break;
		}
		glColor3f(160.0f/255.0f, 54.0f/255.0f, 8.0f/255.0f);
		glVertex3f(VALUE_FROM_PERCENT(xtl[il]+x_pos, percent), VALUE_FROM_PERCENT(ytl[il]+y_pos, percent), 0.0f);
	}
	glEnd(); 

	//********************************************** Dhanushya ********************************************** */
	xl[0] = -0.02;  xl[1] = -0.119; xl[2] = -0.119;  xl[3] = -0.07;
	yl[0] = -0.17;    yl[1] = -0.079; yl[2] = -0.0995; yl[3] = -0.03;

	for(il=0, tl=0; tl<=1.0f; il++, tl+=0.008)	// here (1/0.008) = 125 so in array 125 points will be filled
	{
		xtl[il] = (pow(1-tl, 3)*xl[0]) + (3*tl*pow(1-tl, 2)*xl[1]) + (3*pow(tl,2)*pow(1-tl, 2)*xl[2]) + (pow(tl,3)*xl[3]);
		ytl[il] = (pow(1-tl, 3)*yl[0]) + (3*tl*pow(1-tl, 2)*yl[1]) + (3*pow(tl,2)*pow(1-tl, 2)*yl[2]) + (pow(tl,3)*yl[3]);
	}
	/**********************************************************************************************************/

	if(NRD_RLS_updatey < 0.0f)
		glPointSize(2.0);
	else
		glPointSize(1.0f);

	glBegin(GL_POINTS);
	for(il=0, tl =0; tl<=1.0f; il++, tl+=0.008)
	{
		if(tl > 0.67f)
		{
			break;
		}
		glVertex3f(VALUE_FROM_PERCENT(xtl[il]+x_pos, percent), VALUE_FROM_PERCENT(ytl[il]+y_pos, percent), 0.0f);
	}
	glEnd();

	/********************************************** legs ************************************************ */
	glColor3f(231.0f/255.0f, 123.0f/255.0f, 31.0f/255.0f);
	glBegin(GL_POLYGON);
	glVertex3f(VALUE_FROM_PERCENT(-0.040f + x_pos, percent), VALUE_FROM_PERCENT(-0.076f + y_pos, percent),  0.0f);
	glVertex3f(VALUE_FROM_PERCENT(-0.037f + x_pos, percent), VALUE_FROM_PERCENT(-0.150f + y_pos, percent),  0.0f);
	glVertex3f(VALUE_FROM_PERCENT(-0.030f + x_pos, percent), VALUE_FROM_PERCENT(-0.230f + y_pos, percent),  0.0f);
	glVertex3f(VALUE_FROM_PERCENT(-0.018f + x_pos, percent), VALUE_FROM_PERCENT(-0.230f + y_pos, percent),  0.0f);
	glVertex3f(VALUE_FROM_PERCENT(-0.004f + x_pos, percent), VALUE_FROM_PERCENT(-0.150f + y_pos, percent),  0.0f);
	glVertex3f(VALUE_FROM_PERCENT(-0.000f + x_pos, percent), VALUE_FROM_PERCENT(-0.076f + y_pos, percent),  0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(VALUE_FROM_PERCENT(0.040f + x_pos, percent), VALUE_FROM_PERCENT(-0.076f + y_pos, percent), 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(0.037f + x_pos, percent), VALUE_FROM_PERCENT(-0.150f + y_pos, percent), 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(0.030f + x_pos, percent), VALUE_FROM_PERCENT(-0.230f + y_pos, percent), 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(0.018f + x_pos, percent), VALUE_FROM_PERCENT(-0.230f + y_pos, percent), 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(0.004f + x_pos, percent), VALUE_FROM_PERCENT(-0.150f + y_pos, percent), 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(0.000f + x_pos, percent), VALUE_FROM_PERCENT(-0.076f + y_pos, percent), 0.0f);
	glEnd();
	/**************************************************************************************************** */

	/********************************************** head ************************************************ */
	// hairs
	float radius = 0.027;
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (float angle = 0.0f; angle < (2 * 3.14); angle += 0.005)
	{
		y = radius * sin(angle);
		x = radius * cos(angle);
		glVertex3f(VALUE_FROM_PERCENT(x+x_pos, percent), VALUE_FROM_PERCENT(0.09+y+y_pos, percent), 0.0f);
	}
	glEnd();
	/**************************************************************************************************** */
	
	/********************************************** jata ************************************************ */
	// hairs
	radius = 0.015;
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (float angle = 0.0f; angle < (2 * 3.14); angle += 0.005)
	{
		y = radius * sin(angle);
		x = radius * cos(angle);
		glVertex3f(VALUE_FROM_PERCENT(x+x_pos+0.013, percent), VALUE_FROM_PERCENT(y+y_pos+0.12, percent), 0.0f);
	}
	glEnd();
	/**************************************************************************************************** */
}

void NRD_draw_sita(float x_pos, float y_pos, float percent)
{
	// Variable Declarations
    float x = 0.0f;
    float y = 0.0f;
        
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
	
	glBegin(GL_QUADS);
	{
		glColor3f(255.0f/255.0f, 118.0f/255.0f, 56.0f/255.0f);
		glVertex3f(VALUE_FROM_PERCENT( 0.030f+x_pos, percent), VALUE_FROM_PERCENT(-0.10f + y_pos, percent), 0.0f);
		glVertex3f(VALUE_FROM_PERCENT(-0.040f+x_pos, percent), VALUE_FROM_PERCENT(-0.10f + y_pos, percent), 0.0f);
		glVertex3f(VALUE_FROM_PERCENT(-0.055f+x_pos, percent), VALUE_FROM_PERCENT(-0.22f + y_pos, percent), 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( 0.040f+x_pos, percent), VALUE_FROM_PERCENT(-0.21f + y_pos, percent), 0.0f);
	}
	glEnd();

	//********************** left curve of body ********************************************** */
	xl[0] = -0.074;  xl[1] = 0.0020; xl[2] = -0.18; xl[3] = 0.0;
	yl[0] = -0.1850;  yl[1] = -0.051; yl[2] =  0.21; yl[3] = 0.1565;

	for(il=0, tl=0; tl<=1.0f; il++, tl+=0.008)	// here (1/0.008) = 125 so in array 125 points will be filled
	{
		xtl[il] = (pow(1-tl, 3)*xl[0]) + (3*tl*pow(1-tl, 2)*xl[1]) + (3*pow(tl,2)*pow(1-tl, 2)*xl[2]) + (pow(tl,3)*xl[3]);
		ytl[il] = (pow(1-tl, 3)*yl[0]) + (3*tl*pow(1-tl, 2)*yl[1]) + (3*pow(tl,2)*pow(1-tl, 2)*yl[2]) + (pow(tl,3)*yl[3]);
	}
	/******************************************************************************************* */

	//********************** Right curve of body ********************************************** */
	xr[0] = 0.064;  xr[1] = -0.0020; xr[2] = 0.18; xr[3] = 0.0;
	yr[0] = -0.180;  yr[1] = -0.051; yr[2] = 0.21; yr[3] = 0.1565;

	for(ir=0, tr =0; tr<=1.0f; ir++, tr+=0.008)		// here (1/0.008) = 125 so in array 125 points will be filled
	{
		xtr[ir] = (pow(1-tr, 3)*xr[0]) + (3*tr*pow(1-tr, 2)*xr[1]) + (3*pow(tr,2)*pow(1-tr, 2)*xr[2]) + (pow(tr,3)*xr[3]);
		ytr[ir] = (pow(1-tr, 3)*yr[0]) + (3*tr*pow(1-tr, 2)*yr[1]) + (3*pow(tr,2)*pow(1-tr, 2)*yr[2]) + (pow(tr,3)*yr[3]);
	}
	/******************************************************************************************* */

	glBegin(GL_TRIANGLE_STRIP);
	for(ir=0, il=0; ir<125, il<125; ir++, il++)
	{
		if(ir > 100 && il > 100)
			break;
		glColor3f(255.0f/255.0f, 118.0f/255.0f, 56.0f/255.0f);
		glVertex3f(VALUE_FROM_PERCENT(xtr[ir]+x_pos, percent), VALUE_FROM_PERCENT(ytr[ir]+y_pos, percent), 0.0f);
		glVertex3f(VALUE_FROM_PERCENT(xtl[il]+x_pos, percent), VALUE_FROM_PERCENT(ytl[il]+y_pos, percent), 0.0f);
	}
	glEnd();
	
	glPointSize(1.0);
	glBegin(GL_POINTS);
	for(ir=0, il=0; ir<40, il<40; ir++, il++)
	{
		glColor3f(214.0f/255.0f, 34.0f/255.0f, 8.0f/255.0f);
		glVertex3f(VALUE_FROM_PERCENT(xtr[ir]+x_pos, percent), VALUE_FROM_PERCENT(ytr[ir]+y_pos, percent), 0.0f);
		glVertex3f(VALUE_FROM_PERCENT(xtl[il]+x_pos, percent), VALUE_FROM_PERCENT(ytl[il]+y_pos, percent), 0.0f);
	}
	glEnd();

	/********************************************** Head ************************************************ */
	// hairs
	float radius = 0.018;
	glColor3f(255.0f/255.0f, 118.0f/255.0f, 56.0f/255.0f);
	glBegin(GL_POLYGON);
	for (float angle = 0.0f; angle < (2 * 3.14); angle += 0.005)
	{
		y = radius * sin(angle);
		x = radius * cos(angle);
		glVertex3f(VALUE_FROM_PERCENT(x+x_pos+0.0, percent), VALUE_FROM_PERCENT(y+y_pos+0.085, percent), 0.0f);
	}
	glEnd();
	/**************************************************************************************************** */

	if(NRD_RLS_updatey < 0.0f)
		glLineWidth(2.0);
	else
		glLineWidth(1.0);

	glBegin(GL_LINE_STRIP);
	{
		glColor3f(214.0f/255.0f, 34.0f/255.0f, 8.0f/255.0f);

		glVertex3f(VALUE_FROM_PERCENT(-0.040f + x_pos, percent), VALUE_FROM_PERCENT(-0.10f + y_pos, percent), 0.0f);
		glVertex3f(VALUE_FROM_PERCENT(-0.055f + x_pos, percent), VALUE_FROM_PERCENT(-0.22f + y_pos, percent), 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( 0.040f + x_pos, percent), VALUE_FROM_PERCENT(-0.21f + y_pos, percent), 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( 0.030f + x_pos, percent), VALUE_FROM_PERCENT(-0.10f + y_pos, percent), 0.0f);
	}
	glEnd();

	if(NRD_RLS_updatey < 0.0f)
		glLineWidth(2.0);
	else
		glLineWidth(1.0);
		
	glBegin(GL_LINE_STRIP);
	{
		glColor3f(214.0f/255.0f, 34.0f/255.0f, 8.0f/255.0f);

		glVertex3f(VALUE_FROM_PERCENT(-0.040f/2.5f + x_pos, percent), VALUE_FROM_PERCENT(-0.07f + y_pos, percent), 0.0f);
		glVertex3f(VALUE_FROM_PERCENT(-0.055f/2.5f + x_pos, percent), VALUE_FROM_PERCENT(-0.22f + y_pos, percent), 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( 0.040f/2.5f + x_pos, percent), VALUE_FROM_PERCENT(-0.21f + y_pos, percent), 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( 0.030f/2.5f + x_pos, percent), VALUE_FROM_PERCENT(-0.07f + y_pos, percent), 0.0f);
	}
	glEnd();
}

void NRD_draw_laxman(float x_pos, float y_pos, float percent)
{
	// Variable Declarations
    float x = 0.0f;
    float y = 0.0f;

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

	//********************** left curve of body ********************************************** */
	xl[0] = -0.02;  xl[1] = -0.075; xl[2] = -0.08;  xl[3] = -0.03;
	yl[0] =  0.05;  yl[1] =  0.11; yl[2] = -0.12;  yl[3] = -0.08;

	for(il=0, tl=0; tl<=1.0f; il++, tl+=0.008)	// here (1/0.008) = 125 so in array 125 points will be filled
	{
		xtl[il] = (pow(1-tl, 3)*xl[0]) + (3*tl*pow(1-tl, 2)*xl[1]) + (3*pow(tl,2)*pow(1-tl, 2)*xl[2]) + (pow(tl,3)*xl[3]);
		ytl[il] = (pow(1-tl, 3)*yl[0]) + (3*tl*pow(1-tl, 2)*yl[1]) + (3*pow(tl,2)*pow(1-tl, 2)*yl[2]) + (pow(tl,3)*yl[3]);
	}
	/******************************************************************************************* */

	//********************** Right curve of body ********************************************** */
	xr[0] = 0.02;  xr[1] = 0.075; xr[2] = 0.08;  xr[3] = 0.03;
	yr[0] = 0.05;  yr[1] = 0.11; yr[2] = -0.12;  yr[3] = -0.08;

	for(ir=0, tr =0; tr<=1.0f; ir++, tr+=0.008)		// here (1/0.008) = 125 so in array 125 points will be filled
	{
		xtr[ir] = (pow(1-tr, 3)*xr[0]) + (3*tr*pow(1-tr, 2)*xr[1]) + (3*pow(tr,2)*pow(1-tr, 2)*xr[2]) + (pow(tr,3)*xr[3]);
		ytr[ir] = (pow(1-tr, 3)*yr[0]) + (3*tr*pow(1-tr, 2)*yr[1]) + (3*pow(tr,2)*pow(1-tr, 2)*yr[2]) + (pow(tr,3)*yr[3]);
	}
	/******************************************************************************************* */

	glBegin(GL_TRIANGLE_STRIP);
	for(ir=0, il=0; ir<125, il<125; ir++, il++)
	{
		glColor3f(240.0f/255.0f, 164.0f/255.0f, 133.0f/255.0f);
		glVertex3f(VALUE_FROM_PERCENT(xtr[ir]+x_pos, percent), VALUE_FROM_PERCENT(ytr[ir]+y_pos, percent), 0.0f);
		glVertex3f(VALUE_FROM_PERCENT(xtl[il]+x_pos, percent), VALUE_FROM_PERCENT(ytl[il]+y_pos, percent), 0.0f);
	}
	glEnd();

	//********************** left curve of body ********************************************** */
	xl[0] = -0.02;  xl[1] = -0.065; xl[2] = -0.08;  xl[3] = -0.02;
	yl[0] = -0.07;  yl[1] = -0.12; yl[2] =  0.12;  yl[3] =  0.07;

	for(il=0, tl=0; tl<=1.0f; il++, tl+=0.008)	// here (1/0.008) = 125 so in array 125 points will be filled
	{
		xtl[il] = (pow(1-tl, 3)*xl[0]) + (3*tl*pow(1-tl, 2)*xl[1]) + (3*pow(tl,2)*pow(1-tl, 2)*xl[2]) + (pow(tl,3)*xl[3]);
		ytl[il] = (pow(1-tl, 3)*yl[0]) + (3*tl*pow(1-tl, 2)*yl[1]) + (3*pow(tl,2)*pow(1-tl, 2)*yl[2]) + (pow(tl,3)*yl[3]);
	}
	/******************************************************************************************* */

	//********************** Right curve of body ********************************************** */
	xr[0] = 0.02;  xr[1] = 0.065; xr[2] = 0.08;  xr[3] = 0.02;
	yr[0] = -0.07;  yr[1] = -0.12; yr[2] = 0.12;  yr[3] =  0.07;

	for(ir=0, tr =0; tr<=1.0f; ir++, tr+=0.008)		// here (1/0.008) = 125 so in array 125 points will be filled
	{
		xtr[ir] = (pow(1-tr, 3)*xr[0]) + (3*tr*pow(1-tr, 2)*xr[1]) + (3*pow(tr,2)*pow(1-tr, 2)*xr[2]) + (pow(tr,3)*xr[3]);
		ytr[ir] = (pow(1-tr, 3)*yr[0]) + (3*tr*pow(1-tr, 2)*yr[1]) + (3*pow(tr,2)*pow(1-tr, 2)*yr[2]) + (pow(tr,3)*yr[3]);
	}
	/******************************************************************************************* */

	glBegin(GL_TRIANGLE_STRIP);
	for(ir=0, il=0; ir<125, il<125; ir++, il++)
	{
		if(ir>95 && il>95)
		{
			glColor3f(0.0f, 0.0f, 0.0f);
		}
		else
		{
            glColor3f(240.0f/255.0f, 164.0f/255.0f, 133.0f/255.0f);
		}
		glVertex3f(VALUE_FROM_PERCENT(xtr[ir]+x_pos, percent), VALUE_FROM_PERCENT(ytr[ir]+y_pos, percent), 0.0f);
		glVertex3f(VALUE_FROM_PERCENT(xtl[il]+x_pos, percent), VALUE_FROM_PERCENT(ytl[il]+y_pos, percent), 0.0f);
	}
	glEnd();

	//********************************************** Dhanushya ********************************************** */
	xl[0] = -0.07;  xl[1] = -0.111; xl[2] = -0.087;  xl[3] = -0.059;
	yl[0] = -0.05;  yl[1] = -0.012; yl[2] = 0.079;  yl[3] = 0.0863;

	for(il=0, tl=0; tl<=1.0f; il++, tl+=0.008)	// here (1/0.008) = 125 so in array 125 points will be filled
	{
		xtl[il] = (pow(1-tl, 3)*xl[0]) + (3*tl*pow(1-tl, 2)*xl[1]) + (3*pow(tl,2)*pow(1-tl, 2)*xl[2]) + (pow(tl,3)*xl[3]);
		ytl[il] = (pow(1-tl, 3)*yl[0]) + (3*tl*pow(1-tl, 2)*yl[1]) + (3*pow(tl,2)*pow(1-tl, 2)*yl[2]) + (pow(tl,3)*yl[3]);
	}
	/**********************************************************************************************************/

	if(NRD_RLS_updatey < 0.0f)
		glPointSize(2.0);
	else
		glPointSize(1.0f);

	glBegin(GL_POINTS);
	for(il=0, tl =0; tl<=1.0f; il++, tl+=0.008)
	{
		if(tl> 0.80f)
		{
			break;
		}
		glColor3f(160.0f/255.0f, 54.0f/255.0f, 8.0f/255.0f);
		glVertex3f(VALUE_FROM_PERCENT(xtl[il]+x_pos, percent), VALUE_FROM_PERCENT(ytl[il]+y_pos, percent), 0.0f);
	}
	glEnd(); 

	//********************************************** Dhanushya ********************************************** */
	xl[0] = -0.02;  xl[1] = -0.119; xl[2] = -0.119;  xl[3] = -0.07;
	yl[0] = -0.17;    yl[1] = -0.079; yl[2] = -0.0995; yl[3] = -0.03;

	for(il=0, tl=0; tl<=1.0f; il++, tl+=0.008)	// here (1/0.008) = 125 so in array 125 points will be filled
	{
		xtl[il] = (pow(1-tl, 3)*xl[0]) + (3*tl*pow(1-tl, 2)*xl[1]) + (3*pow(tl,2)*pow(1-tl, 2)*xl[2]) + (pow(tl,3)*xl[3]);
		ytl[il] = (pow(1-tl, 3)*yl[0]) + (3*tl*pow(1-tl, 2)*yl[1]) + (3*pow(tl,2)*pow(1-tl, 2)*yl[2]) + (pow(tl,3)*yl[3]);
	}
	/**********************************************************************************************************/

	if(NRD_RLS_updatey < 0.0f)
		glPointSize(2.0);
	else
		glPointSize(1.0f);

	glBegin(GL_POINTS);
	for(il=0, tl =0; tl<=1.0f; il++, tl+=0.008)
	{
		if(tl > 0.67f)
		{
			break;
		}
		glVertex3f(VALUE_FROM_PERCENT(xtl[il]+x_pos, percent), VALUE_FROM_PERCENT(ytl[il]+y_pos, percent), 0.0f);
	}
	glEnd();

	/********************************************** legs ************************************************ */
	glColor3f(231.0f/255.0f, 123.0f/255.0f, 31.0f/255.0f);
	glBegin(GL_POLYGON);
	glVertex3f(VALUE_FROM_PERCENT(-0.040f + x_pos, percent), VALUE_FROM_PERCENT(-0.076f + y_pos, percent),  0.0f);
	glVertex3f(VALUE_FROM_PERCENT(-0.037f + x_pos, percent), VALUE_FROM_PERCENT(-0.150f + y_pos, percent),  0.0f);
	glVertex3f(VALUE_FROM_PERCENT(-0.030f + x_pos, percent), VALUE_FROM_PERCENT(-0.230f + y_pos, percent),  0.0f);
	glVertex3f(VALUE_FROM_PERCENT(-0.018f + x_pos, percent), VALUE_FROM_PERCENT(-0.230f + y_pos, percent),  0.0f);
	glVertex3f(VALUE_FROM_PERCENT(-0.004f + x_pos, percent), VALUE_FROM_PERCENT(-0.150f + y_pos, percent),  0.0f);
	glVertex3f(VALUE_FROM_PERCENT(-0.000f + x_pos, percent), VALUE_FROM_PERCENT(-0.076f + y_pos, percent),  0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(VALUE_FROM_PERCENT(0.040f + x_pos, percent), VALUE_FROM_PERCENT(-0.076f + y_pos, percent), 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(0.037f + x_pos, percent), VALUE_FROM_PERCENT(-0.150f + y_pos, percent), 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(0.030f + x_pos, percent), VALUE_FROM_PERCENT(-0.230f + y_pos, percent), 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(0.018f + x_pos, percent), VALUE_FROM_PERCENT(-0.230f + y_pos, percent), 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(0.004f + x_pos, percent), VALUE_FROM_PERCENT(-0.150f + y_pos, percent), 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(0.000f + x_pos, percent), VALUE_FROM_PERCENT(-0.076f + y_pos, percent), 0.0f);
	glEnd();
	/**************************************************************************************************** */

	/********************************************** head ************************************************ */
	// Outer White circle
	float radius = 0.027;
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (float angle = 0.0f; angle < (2 * 3.14); angle += 0.005)
	{
		y = radius * sin(angle);
		x = radius * cos(angle);
		glVertex3f(VALUE_FROM_PERCENT(x+x_pos, percent), VALUE_FROM_PERCENT(0.09+y+y_pos, percent), 0.0f);
	}
	glEnd();
	/**************************************************************************************************** */
	
	/********************************************** hairs ************************************************ */
	// Outer White circle
	radius = 0.015;
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (float angle = 0.0f; angle < (2 * 3.14); angle += 0.005)
	{
		y = radius * sin(angle);
		x = radius * cos(angle);
		glVertex3f(VALUE_FROM_PERCENT(x+x_pos+0.013, percent), VALUE_FROM_PERCENT(y+y_pos+0.12, percent), 0.0f);
	}
	glEnd();
	/**************************************************************************************************** */
}

void NRD_draw_stem(float x_pos, float y_pos, float percent)
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

void NRD_draw_branch(float x_pos, float y_pos, float percent)
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

void NRD_draw_greenfield(float x_pos, float y_pos, float percent)
{
	GLfloat xl[4], yl[4];
	GLfloat xtl[200], ytl[200];
	GLfloat tl=0.0f;
	int il;

	//******************************************** below greenfield curve  ************************************************/
	xl[0] = 0.0;  xl[1] = 0.5;  xl[2] = 4.2;  xl[3] = 3.0;
	yl[0] = 0.0;  yl[1] = 0.5;  yl[2] = 1.0;  yl[3] = 0.0;

	// xl[0] = -2.0;  xl[1] = -1.0;  xl[2] = 3.0;  xl[3] = 2.0;
	// yl[0] = -1.0;  yl[1] = 0.5;  yl[2] = 0.5;  yl[3] = -1.0;
	
	for(il=0, tl=0; tl<=1.0f; il++, tl+=0.008)	// here (1/0.008) = 125 so in array 125 points will be filled
	{
		xtl[il] = (pow(1-tl, 3)*xl[0]) + (3*tl*pow(1-tl, 2)*xl[1]) + (3*pow(tl,2)*pow(1-tl, 2)*xl[2]) + (pow(tl,3)*xl[3]);
		ytl[il] = (pow(1-tl, 3)*yl[0]) + (3*tl*pow(1-tl, 2)*yl[1]) + (3*pow(tl,2)*pow(1-tl, 2)*yl[2]) + (pow(tl,3)*yl[3]);
	}
	//**************************************************************************************************************/

	glBegin(GL_POLYGON);
	glColor3f(0.1490, 0.5450, 0.0274);
	for(il=0; il<125; il++)
	{
		glVertex3f(VALUE_FROM_PERCENT(xtl[il]+x_pos, percent), VALUE_FROM_PERCENT(ytl[il]+y_pos, percent), 0.0f);
	}
	glEnd();
}

void NRD_draw_way(float x_pos, float y_pos, float percent)
{
	// Variables for way left curce
	GLfloat xl[4], yl[4];
	GLfloat xtl[200], ytl[200];
	GLfloat tl=0.0f;
	int il;

	// Variables for way right curce
	GLfloat xr[4], yr[4];
	GLfloat xtr[200], ytr[200];
	GLfloat tr=0.0f;
	int ir;

	//******************************************** left curve of way ************************************************/
	xl[0] = -1.0;  xl[1] = 0.7;  xl[2] = -3.0;  xl[3] = -0.02;
	yl[0] = -2.0;  yl[1] = 0.0;  yl[2] = -0.8;  yl[3] = 0.32;
	
	for(il=0, tl=0; tl<=1.0f; il++, tl+=0.008)	// here (1/0.008) = 125 so in array 125 points will be filled
	{
		xtl[il] = (pow(1-tl, 3)*xl[0]) + (3*tl*pow(1-tl, 2)*xl[1]) + (3*pow(tl,2)*pow(1-tl, 2)*xl[2]) + (pow(tl,3)*xl[3]);
		ytl[il] = (pow(1-tl, 3)*yl[0]) + (3*tl*pow(1-tl, 2)*yl[1]) + (3*pow(tl,2)*pow(1-tl, 2)*yl[2]) + (pow(tl,3)*yl[3]);
	}
	//**************************************************************************************************************/

	
	//******************************************** Right curve of way ************************************************/
	xr[0] = 0.4;  xr[1] = 1.0;  xr[2] = -1.8;  xr[3] = 0.1;
	yr[0] = -2.0;  yr[1] = -0.6;  yr[2] = -0.8;  yr[3] = 0.31;
	
	for(ir=0, tr=0; tr<=1.0f; ir++, tr+=0.008)	// here (1/0.008) = 125 so in array 125 points will be filled
	{
		xtr[ir] = (pow(1-tr, 3)*xr[0]) + (3*tr*pow(1-tr, 2)*xr[1]) + (3*pow(tr,2)*pow(1-tr, 2)*xr[2]) + (pow(tr,3)*xr[3]);
		ytr[ir] = (pow(1-tr, 3)*yr[0]) + (3*tr*pow(1-tr, 2)*yr[1]) + (3*pow(tr,2)*pow(1-tr, 2)*yr[2]) + (pow(tr,3)*yr[3]);
	}
	//**************************************************************************************************************/

	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	for(ir=0, il=0; ir<125, il<125; ir++, il++)
	{
		
		glColor3f(155.0f/256.0f, 149.0f/256.0f, 89.0f/256.0f);
		glVertex3f(VALUE_FROM_PERCENT(xtr[ir]+x_pos, percent), VALUE_FROM_PERCENT(ytr[ir]+y_pos, percent), 0.0f);

		glColor3f(141.0f/256.0f, 127.0f/256.0f, 87.0f/256.0f);
		glVertex3f(VALUE_FROM_PERCENT(xtl[ir]+x_pos, percent), VALUE_FROM_PERCENT(ytl[ir]+y_pos, percent), 0.0f);
	}
	glEnd();
}

void NRD_Tree(float x_pos, float y_pos, float percentX, float percentY)
{
	// code
	// call to branch funciton
	NRD_draw_branch(-0.5+x_pos, -0.1+y_pos, 100.0);
	NRD_Treeleaves(-0.5f + x_pos, 0.37f + y_pos, 0.0f + percentX, 0.0f + percentY, 12.0f, 55.0f, 31.0f);
	NRD_Treeleaves(-0.55f + x_pos, 0.7f + y_pos, 0.0f + percentX, 0.0f + percentY, 12.0f, 55.0f, 31.0f);
	NRD_Treeleaves(-0.79f + x_pos, 0.6f + y_pos, 10.0f + percentX, 0.0f + percentY, 12.0f, 55.0f, 31.0f);
	NRD_Treeleaves(-0.4f + x_pos, 0.43f + y_pos, 16.0f + percentX, 0.0f + percentY, 12.0f, 55.0f, 31.0f);
	NRD_Treeleaves(-0.75f + x_pos, 0.4f + y_pos, 10.0f + percentX, 0.0f + percentY, 12.0f, 55.0f, 31.0f);

	NRD_Treeleaves(-0.6f + x_pos, 0.65f + y_pos, 0.0f + percentX, 0.0f + percentY, 26.0f, 99.0f, 55.0f);
	NRD_Treeleaves(-0.44f + x_pos, 0.5f + y_pos, 7.0f + percentX, 0.0f + percentY, 26.0f, 99.0f, 55.0f);
	NRD_Treeleaves(-0.63f + x_pos, 0.52f + y_pos, 3.0f + percentX, 0.0f + percentY, 26.0f, 99.0f, 55.0f);
	
	// call here stem function
	NRD_draw_stem(-0.5+x_pos, -0.1+y_pos, 100.0);

	NRD_Treeleaves(-0.44f + x_pos, 0.47f + y_pos, 0.0f + percentX, 0.0f + percentY, 78.0f, 150.0f, 43.0f);
	NRD_Treeleaves(-0.66f + x_pos, 0.51f + y_pos, 9.0f + percentX, 0.0f + percentY, 78.0f, 150.0f, 43.0f);
	NRD_Treeleaves(-0.6f + x_pos, 0.41f + y_pos, 2.0f + percentX, 0.0f + percentY, 78.0f, 150.0f, 43.0f);
	NRD_Treeleaves(-0.75f + x_pos, 0.5f + y_pos, 2.0f + percentX, 0.0f + percentY, 78.0f, 150.0f, 43.0f);
}

void NRD_Treeleaves(float x_pos, float y_pos, float percentX, float percentY, float red, float green, float blue)
{
	// code
	NRD_Circle(0.0f + x_pos, 0.0f + y_pos,  20.0f + percentX, 0.0f + percentY, 0.2f, red, green, blue);
	NRD_Circle(0.08f + x_pos, 0.07f + y_pos,  20.0f + percentX, 0.0f + percentY, 0.2f, red, green, blue);
	NRD_Circle(0.12f + x_pos, 0.09f + y_pos,  20.0f + percentX, 0.0f + percentY, 0.2f, red, green, blue);
	NRD_Circle(0.05f + x_pos, 0.02f + y_pos,  20.0f + percentX, 0.0f + percentY, 0.2f, red, green, blue);
	NRD_Circle(0.13f + x_pos, 0.0f + y_pos,  40.0f + percentX, 0.0f + percentY, 0.2f, red, green, blue); 
	NRD_Circle(0.18f + x_pos, 0.07f + y_pos,  20.0f + percentX, 0.0f + percentY, 0.2f, red, green, blue);
	NRD_Circle(0.19f + x_pos, 0.0f + y_pos,  20.0f + percentX, 0.0f + percentY, 0.2f, red, green, blue);
	NRD_Circle(0.18f + x_pos, -0.07f + y_pos,  20.0f + percentX, 0.0f + percentY, 0.2f, red, green, blue);
	NRD_Circle(0.04f + x_pos, -0.06f + y_pos,  20.0f + percentX, 0.0f + percentY, 0.2f, red, green, blue);
	NRD_Circle(0.11f + x_pos, -0.06f + y_pos,  20.0f + percentX, 0.0f + percentY, 0.2f, red, green, blue);
}

void NRD_Circle(float x_pos, float y_pos, float percentX, float percentY, float radius, float red, float green, float blue)
{	
	glPointSize(63.0f);
	glBegin(GL_POINTS);
	glColor4f( red/ 256.0f, green/ 256.0f, blue / 256.0f, 1.0f);
	{
		glVertex3f(VALUE_FROM_PERCENT( pt_x, percentX) + x_pos, VALUE_FROM_PERCENT( pt_y, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( pt_x + 0.03f, percentX) + x_pos, VALUE_FROM_PERCENT( pt_y, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( pt_x - 0.03f, percentX) + x_pos, VALUE_FROM_PERCENT( pt_y, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( pt_x, percentX) + x_pos, VALUE_FROM_PERCENT( pt_y + 0.03f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( pt_x, percentX) + x_pos, VALUE_FROM_PERCENT( pt_y - 0.03f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( pt_x + 0.08f, percentX) + x_pos, VALUE_FROM_PERCENT( pt_y, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( pt_x - 0.08f, percentX) + x_pos, VALUE_FROM_PERCENT( pt_y, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( pt_x, percentX) + x_pos, VALUE_FROM_PERCENT( pt_y + 0.08f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( pt_x, percentX) + x_pos, VALUE_FROM_PERCENT( pt_y - 0.08f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( pt_x + 0.08f, percentX) + x_pos, VALUE_FROM_PERCENT( pt_y + 0.08f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( pt_x - 0.08f, percentX) + x_pos, VALUE_FROM_PERCENT( pt_y - 0.08f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( pt_x - 0.08f, percentX) + x_pos, VALUE_FROM_PERCENT( pt_y + 0.08f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( pt_x + 0.08f, percentX) + x_pos, VALUE_FROM_PERCENT( pt_y - 0.08f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( pt_x + 0.13f, percentX) + x_pos, VALUE_FROM_PERCENT( pt_y, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( pt_x - 0.13f, percentX) + x_pos, VALUE_FROM_PERCENT( pt_y, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( pt_x, percentX) + x_pos, VALUE_FROM_PERCENT( pt_y + 0.13f, percentY) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( pt_x, percentX) + x_pos, VALUE_FROM_PERCENT( pt_y - 0.13f, percentY) + y_pos, 0.0f);
	}
	glEnd();
}

void NRD_Birds_Amol(float x_pos, float y_pos)
{
    //******************** Draw Bird *****************************************************
    //Bird Shape 1/2 feather
    glBegin(GL_QUADS);
    glColor3f(0.6f, 0.4f, 0.6f);  //
    glVertex2f(0.6f + x_pos, 0.65f+ y_pos);  // 
    glVertex2f(0.57f + x_pos, 0.63f+ y_pos);
    //glColor3f(-0.36f, 0.58f, 0.0f);
    glVertex2f(0.57f + x_pos, 0.58f + y_pos);
    glVertex2f(0.58f + x_pos, 0.58f + y_pos);
    glEnd();

    //Bird Shape 2 feather shape line
    glBegin(GL_LINES);
    glColor3f(0.1f, 0.1f, 0.1f);  //
    glVertex2f(0.58f + x_pos, 0.62f + y_pos);  // 
    glVertex2f(0.6f + x_pos, 0.64f + y_pos);
    glEnd();

    //Bird Shape 2 feather shape line
    glBegin(GL_LINES);
    glColor3f(0.1f, 0.1f, 0.1f);  //
    glVertex2f(0.58f + x_pos, 0.60f + y_pos);  // 
    glVertex2f(0.6f + x_pos, 0.62f + y_pos);
    glEnd();

    //Bird Shape 2 body
    glBegin(GL_QUADS);
    glColor3f(0.6f, 0.4f, 0.6f);  // 
    glVertex2f(0.55f + x_pos, 0.57f + y_pos);  // 
    glVertex2f(0.55f + x_pos, 0.59f + y_pos);
    //glColor3f(-0.36f, 0.58f, 0.0f);
    glVertex2f(0.60f + x_pos, 0.56f + y_pos);
    glVertex2f(0.61f + x_pos, 0.57f + y_pos);
    glEnd();

    //Bird Shape 2 beak
    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.4f, 0.6f);  // 
    glVertex2f(0.55f + x_pos, 0.59f + y_pos);  // 
    glVertex2f(0.53f + x_pos, 0.58f + y_pos);
    //glColor3f(-0.36f, 0.58f, 0.0f);
    glVertex2f(0.55f + x_pos, 0.57f + y_pos);
    glEnd();

    //Bird Shape 2 eye shape 
    glBegin(GL_LINES);
    glColor3f(0.1f, 0.1f, 0.1f);  //
    glVertex2f(0.545f + x_pos, 0.58f + y_pos);  // 
    glVertex2f(0.548f + x_pos, 0.581f + y_pos);
    glEnd();

    /////////////////////////////*********************

    //Bird Shape 2/2 feather
    glBegin(GL_QUADS);
    glColor3f(0.6f, 0.4f, 0.6f);  // 
    glVertex2f(0.7f + x_pos, 0.65f + y_pos);  // 
    glVertex2f(0.67f + x_pos, 0.63f + y_pos);
    //glColor3f(-0.36f, 0.58f, 0.0f);
    glVertex2f(0.67f + x_pos, 0.58f + y_pos);
    glVertex2f(0.68f + x_pos, 0.58f + y_pos);
    glEnd();

    //Bird Shape feather shape
    glBegin(GL_LINES);
    glColor3f(0.1f, 0.1f, 0.1f);  // 
    glVertex2f(0.68f + x_pos, 0.62f + y_pos);  // 
    glVertex2f(0.7f + x_pos, 0.64f + y_pos);
    glEnd();

    //Bird Shape feather shape
    glBegin(GL_LINES);
    glColor3f(0.1f, 0.1f, 0.1f);  // 
    glVertex2f(0.68f + x_pos, 0.60f + y_pos);  // 
    glVertex2f(0.7f + x_pos, 0.62f + y_pos);
    glEnd();

    //Bird Shape 2 body
    glBegin(GL_QUADS);
    glColor3f(0.6f, 0.4f, 0.6f);  // 
    glVertex2f(0.65f + x_pos, 0.57f + y_pos);  // 
    glVertex2f(0.65f + x_pos, 0.59f + y_pos);
    //glColor3f(-0.36f, 0.58f, 0.0f);
    glVertex2f(0.70f + x_pos, 0.56f + y_pos);
    glVertex2f(0.71f + x_pos, 0.57f + y_pos);
    glEnd();

    //Bird Shape 2 beak
    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.4f, 0.6f);  // 
    glVertex2f(0.65f + x_pos, 0.59f + y_pos);  // 
    glVertex2f(0.63f + x_pos, 0.58f + y_pos);
    //glColor3f(-0.36f, 0.58f, 0.0f);
    glVertex2f(0.65f + x_pos, 0.57f + y_pos);
    glEnd();

    //Bird Shape 2 eye shape 
    glBegin(GL_LINES);
    glColor3f(0.1f, 0.1f, 0.1f);  //
    glVertex2f(0.645f + x_pos, 0.58f + y_pos);  // 
    glVertex2f(0.648f + x_pos, 0.581f + y_pos);
    glEnd();

    ///*********** Simple Birds flying in groups ***********************************************
	//Bird Shape 1
    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.4f, 0.6f);  // 
    glVertex2f(-0.4f + x_pos, 0.6f + y_pos);  // 
    glVertex2f(-0.37f + x_pos, 0.57f + y_pos);
    //glColor3f(-0.36f, 0.58f, 0.0f);
    glVertex2f(-0.36f + x_pos, 0.58f + y_pos);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.4f, 0.6f);  // 
    glVertex2f(-0.3f + x_pos, 0.6f + y_pos);  // 
    glVertex2f(-0.37f + x_pos, 0.57f + y_pos);
    //glColor3f(-0.36f, 0.58f, 0.0f);
    glVertex2f(-0.36f + x_pos, 0.58f + y_pos);
    glEnd();

    // Bird Shape 2
    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.4f, 0.6f);  // 
    glVertex2f(-0.2f + x_pos, 0.6f + y_pos);  // 
    glVertex2f(-0.17f + x_pos, 0.57f + y_pos);
    //glColor3f(-0.36f, 0.58f, 0.0f);
    glVertex2f(-0.16f + x_pos, 0.58f + y_pos);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.4f, 0.6f);  // 
    glVertex2f(-0.1f + x_pos, 0.6f + y_pos);  // 
    glVertex2f(-0.17f + x_pos, 0.57f + y_pos);
    //glColor3f(-0.36f, 0.58f, 0.0f);
    glVertex2f(-0.16f + x_pos, 0.58f + y_pos);
    glEnd();

    ///****************************

	// Bird Shape 3
    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.4f, 0.6f);  // 
    glVertex2f(-0.2f + x_pos, 0.8f + y_pos);  // 
    glVertex2f(-0.17f + x_pos, 0.77f + y_pos);
    //glColor3f(-0.36f, 0.58f, 0.0f);
    glVertex2f(-0.16f + x_pos, 0.78f + y_pos);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.4f, 0.6f);  // 
    glVertex2f(-0.1f + x_pos, 0.8f + y_pos);  // 
    glVertex2f(-0.17f + x_pos, 0.77f + y_pos);
    //glColor3f(-0.36f, 0.58f, 0.0f);
    glVertex2f(-0.16f + x_pos, 0.78f + y_pos);
    glEnd();


    //******************** Draw Bird *****************************************************

   //Bird Shape 1
    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.4f, 0.6f);  // 
    glVertex2f(0.4f + x_pos, 0.6f + y_pos);  // 
    glVertex2f(0.37f + x_pos, 0.57f + y_pos);
    //glColor3f(-0.36f, 0.58f, 0.0f);
    glVertex2f(0.36f + x_pos, 0.58f + y_pos);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.4f, 0.6f);  // 
    glVertex2f(0.3f + x_pos, 0.6f + y_pos);  // 
    glVertex2f(0.37f + x_pos, 0.57f + y_pos);
    //glColor3f(-0.36f, 0.58f, 0.0f);
    glVertex2f(0.36f + x_pos, 0.58f + y_pos);
    glEnd();

    // Bird Shape 2
    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.4f, 0.6f);  // 
    glVertex2f(0.2f + x_pos, 0.6f + y_pos);  //
    glVertex2f(0.17f + x_pos, 0.57f + y_pos);
    //glColor3f(-0.36f, 0.58f, 0.0f);
    glVertex2f(0.16f + x_pos, 0.58f + y_pos);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.4f, 0.6f);  // 
    glVertex2f(0.1f + x_pos, 0.6f + y_pos);  // 
    glVertex2f(0.17f + x_pos, 0.57f + y_pos);
    //glColor3f(-0.36f, 0.58f, 0.0f);
    glVertex2f(0.16f + x_pos, 0.58f + y_pos);
    glEnd();
    ///****************************

   // Bird Shape 3
    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.4f, 0.6f);  // 
    glVertex2f(0.2f + x_pos, 0.8f + y_pos);  // 
    glVertex2f(0.17f + x_pos, 0.77f + y_pos);
    //glColor3f(-0.36f, 0.58f, 0.0f);
    glVertex2f(0.16f + x_pos, 0.78f + y_pos);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.4f, 0.6f);  // 
    glVertex2f(0.1f + x_pos, 0.8f + y_pos);  // 
    glVertex2f(0.17f + x_pos, 0.77f + y_pos);
    //glColor3f(-0.36f, 0.58f, 0.0f);
    glVertex2f(0.16f + x_pos, 0.78f + y_pos);
    glEnd();
}

void NRD_update(void)
{
	if(NRD_RLS_updatey >= 1.15)
	{
		// add code here for next scene change

		NRD_vanvasAnimation = FALSE;
	}

	if(NRD_vanvasAnimation)
	{
		// code
		// Update Ram Lakxman Sita on Y axis 
		if(NRD_RLS_updatey < 1.15)
		{
			NRD_RLS_updatey+= 0.0002;
		}

		if(NRD_RLS_updatey > -0.1 && NRD_RLS_updatey < 1.15)    // Movement of objects over x-axis upper part
		{
			NRD_RLS_updatex += 0.00011;		// Decrease this factor if speed on y axis changed (minimized)
		}
		if(NRD_RLS_updatey < -0.1 && NRD_RLS_updatey >= -0.9) 	// Movement of objects over x-axis
		{
			NRD_RLS_updatex -= 0.00005;
		}

		if(NRD_RLS_updatey > 0.07)					// Transformation matrix related variable update
		{
			NRD_RLS_updateTransform -= 0.001;
		}
		else if(NRD_RLS_updateTransform > -8.0f)	// Transformation matrix related variable update
		{
			NRD_RLS_updateTransform -= 0.001;
		}

		if(NRD_Birds_x > -4.0f)					// Birds positon changes on x axis
		{
			NRD_Birds_x -= 0.008;
		}

		if(NRD_Birds_y >= 1.1f)					// Birds positon slightly change on Y axis
		{
			NRD_Birds_y += 0.00015;
		}
	}

}
