#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

//OPENGL RELETED HEADER FILE
#include<gl/GL.h>
#include "OGL.h"
#include<gl/GLU.h>
#include<math.h>
#include "Omkar_Texture_Text.h"

#define VALUE_FROM_PERCENT(complete, percent) (complete * percent/100.0f)

struct ouj_Curve 
 {
    float ouj_x1, ouj_x2, ouj_x3, ouj_x4;
    float ouj_y1, ouj_y2, ouj_y3, ouj_y4;

    
 };

float Cut1[100] , Cut2[100];
float Cvt1[100] , Cvt2[100];
float Cwt1[100] , Cwt2[100];
float Cxt1[100] , Cxt2[100];
float ouj_Dat1[100] , ouj_Dat2[100];
float ouj_Dbt1[100] , ouj_Dbt2[100];
float ouj_Dct1[100] , ouj_Dct2[100];
float ouj_Ddt1[100] , ouj_Ddt2[100];
float ouj_Det1[100] , ouj_Det2[100];
float ouj_Dft1[100] , ouj_Dft2[100];
float ouj_Dgt1[100] , ouj_Dgt2[100];
float ouj_Dht1[100] , ouj_Dht2[100];
float ouj_Dit1[100] , ouj_Dit2[100];
float ouj_Djt1[100] , ouj_Djt2[100];
float ouj_Dkt1[100] , ouj_Dkt2[100];
float ouj_Dlt1[100] , ouj_Dlt2[100];
float ouj_Dmt1[100] , ouj_Dmt2[100];
float ouj_Dnt1[100] , ouj_Dnt2[100];
float ouj_Dot1[100] , ouj_Dot2[100];
float ouj_Dpt1[100] , ouj_Dpt2[100];
float ouj_Dqt1[100] , ouj_Dqt2[100];
float ouj_Drt1[100] , ouj_Drt2[100];
float ouj_Dst1[100] , ouj_Dst2[100];
float ouj_Dtt1[100] , ouj_Dtt2[100];




void Omkar_Texture_Text(void)
{
    //set matrix to model view mode
    glMatrixMode(GL_MODELVIEW);
        
    
    //SET TO IDENTITY MATRIX
    glLoadIdentity();

    //translet triangle back word by Z
    glTranslatef(0.0f, 0.0f, -3.0f);

    Texture_T(-0.87f, -0.01f, 120);
    Texture_E(-0.7f, -0.01f, 115);
    Texture_X(-0.39f, -0.01f, 120);
    Texture_TT(0.0f, -0.01f, 120);
    Texture_U(0.3f, -0.16f, 160);
    Texture_RR(0.54f, 0.2f, 62);
    Texture_EE(0.75f, -0.01f, 115);

    Group_G(-0.23f, -0.32f, 35);
    Group_R(-0.14f, -0.27f, 20);
    Group_O(-0.0f, -0.34f, 45);
    Group_U(0.14f, -0.4f, 60);
    Group_P(0.25f, -0.27f, 20);

    Present_P(-0.70f, -0.64f, 35);
    Present_R(-0.52f, -0.65f, 35);
    Present_E(-0.34f, -0.78f, 70);
    Present_S(-0.05f, -0.66f, 35);
    Present_EE(0.11f, -0.78f, 70);
    Present_N(0.43f, -0.78f, 70);
    Present_T(0.67f, -0.79f, 78);
    Present_S(0.85f, -0.66f, 35);

}
     


void Texture_T(float x_pos, float y_pos, float percent)
{


    glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
    //***************************************************T*****************************************
    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f(VALUE_FROM_PERCENT(-0.02f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.02f, percent) + x_pos, VALUE_FROM_PERCENT(0.05f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos, VALUE_FROM_PERCENT(0.1f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.02f, percent) + x_pos, VALUE_FROM_PERCENT(0.15f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.02f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
    }
    glEnd();

   

   

    //T chi top side
    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f(VALUE_FROM_PERCENT(-0.09f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.09f, percent) + x_pos, VALUE_FROM_PERCENT(0.33f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.015f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.015f, percent) + x_pos, VALUE_FROM_PERCENT(0.33f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.09f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.09f, percent) + x_pos, VALUE_FROM_PERCENT(0.33f, percent) + y_pos, 0.0f);

       

    }
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    {
       
        glVertex3f(VALUE_FROM_PERCENT(0.09f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.07f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.09f, percent) + x_pos, VALUE_FROM_PERCENT(0.27f, percent) + y_pos, 0.0f);

       

    }
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    {
       
        glVertex3f(VALUE_FROM_PERCENT(-0.09f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.07f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.09f, percent) + x_pos, VALUE_FROM_PERCENT(0.27f, percent) + y_pos, 0.0f);

       

    }
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    {
       
        glVertex3f(VALUE_FROM_PERCENT(-0.035f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.0f, percent) + x_pos, VALUE_FROM_PERCENT(-0.015f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.035f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);

       

    }
    glEnd();

}
   

void Texture_E(float x_pos, float y_pos, float percent)
{


    glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
    //***************************************************E*****************************************
    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.1f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.15f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.25f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
    }
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.32f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.1f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.15f, percent) + x_pos, VALUE_FROM_PERCENT(0.32f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.2f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.23f, percent) + x_pos, VALUE_FROM_PERCENT(0.32f, percent) + y_pos, 0.0f);
        //glVertexf(VALUE_FROM_PERCENT(0.31f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
    }
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.16f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.1f, percent) + x_pos, VALUE_FROM_PERCENT(0.16f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.13f, percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.15f, percent) + x_pos, VALUE_FROM_PERCENT(0.16f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.15f, percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);

        
    }
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.035f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.1f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.15f, percent) + x_pos, VALUE_FROM_PERCENT(0.035f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.2f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.23f, percent) + x_pos, VALUE_FROM_PERCENT(0.035f, percent) + y_pos, 0.0f);
        //glVertexf(VALUE_FROM_PERCENT(0.31f, percent) + x_pos, VALUE_FROM_PERCENT(0.05f, percent) + y_pos, 0.0f);


    }
    glEnd();
}


void Texture_X(float x_pos, float y_pos, float percent)
{

    glColor4f(1.0f, 0.4f, 0.0f, 1.0f);

    //***************************************************X*****************************************
    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.07f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.05f, percent) + x_pos, VALUE_FROM_PERCENT(0.05f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.05f, percent) + x_pos, VALUE_FROM_PERCENT(0.12f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.15f, percent) + x_pos, VALUE_FROM_PERCENT(0.165f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.15f, percent) + x_pos, VALUE_FROM_PERCENT(0.23f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.2f, percent) + x_pos, VALUE_FROM_PERCENT(0.25f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.17f, percent) + x_pos, VALUE_FROM_PERCENT(0.27f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.2f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
        // glVertex3f(VALUE_FROM_PERCENT(0.15f, percent) + x_pos, VALUE_FROM_PERCENT(0.14f, percent) + y_pos, 0.0f);
        // glVertex3f(VALUE_FROM_PERCENT(0.15f, percent) + x_pos, VALUE_FROM_PERCENT(0.11f, percent) + y_pos, 0.0f);
    }
    glEnd();

    //X chi varachi side
    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f(VALUE_FROM_PERCENT(0.2f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.2f, percent) + x_pos, VALUE_FROM_PERCENT(0.07f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.15f, percent) + x_pos, VALUE_FROM_PERCENT(0.05f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.124f, percent) + x_pos, VALUE_FROM_PERCENT(0.14f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.1f, percent) + x_pos, VALUE_FROM_PERCENT(0.11f, percent) + y_pos, 0.0f);
        
    }
        glEnd();
       
        glBegin(GL_TRIANGLE_STRIP);
        {
            glVertex3f(VALUE_FROM_PERCENT(0.1f, percent) + x_pos, VALUE_FROM_PERCENT(0.16f, percent) + y_pos, 0.0f);
            glVertex3f(VALUE_FROM_PERCENT(0.065f, percent) + x_pos, VALUE_FROM_PERCENT(0.14f, percent) + y_pos, 0.0f);
            glVertex3f(VALUE_FROM_PERCENT(0.05f, percent) + x_pos, VALUE_FROM_PERCENT(0.23f, percent) + y_pos, 0.0f);
            glVertex3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.25f, percent) + y_pos, 0.0f);
            glVertex3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
        }
            glEnd();

    
}
   

void Texture_TT(float x_pos, float y_pos, float percent)
{


    glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
    //***************************************************T*****************************************
    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f(VALUE_FROM_PERCENT(-0.02f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.02f, percent) + x_pos, VALUE_FROM_PERCENT(0.05f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos, VALUE_FROM_PERCENT(0.1f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.02f, percent) + x_pos, VALUE_FROM_PERCENT(0.15f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.02f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
    }
    glEnd();

   

   

    //T chi top side
    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f(VALUE_FROM_PERCENT(-0.09f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.09f, percent) + x_pos, VALUE_FROM_PERCENT(0.33f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.015f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.015f, percent) + x_pos, VALUE_FROM_PERCENT(0.33f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.09f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.09f, percent) + x_pos, VALUE_FROM_PERCENT(0.33f, percent) + y_pos, 0.0f);

       

    }
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    {
       
        glVertex3f(VALUE_FROM_PERCENT(0.09f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.07f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.09f, percent) + x_pos, VALUE_FROM_PERCENT(0.27f, percent) + y_pos, 0.0f);

       

    }
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    {
       
        glVertex3f(VALUE_FROM_PERCENT(-0.09f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.07f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.09f, percent) + x_pos, VALUE_FROM_PERCENT(0.27f, percent) + y_pos, 0.0f);

       

    }
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    {
       
        glVertex3f(VALUE_FROM_PERCENT(-0.035f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.0f, percent) + x_pos, VALUE_FROM_PERCENT(-0.015f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.035f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);

       

    }
    glEnd();

}
  

void Texture_U(float x_pos, float y_pos, float percent)
{
   

    float t = 0.0f;
    int i = 0;

    struct ouj_Curve ouj_curve33;
    struct ouj_Curve ouj_curve34;
    
    //co-ordinate x,y
    ouj_curve33.ouj_x1 = -0.09f;
    ouj_curve33.ouj_x2 = -0.1f;
    ouj_curve33.ouj_x3 = 0.1f;
    ouj_curve33.ouj_x4 = 0.09f;

   
    ouj_curve33.ouj_y1 = 0.35f;
    ouj_curve33.ouj_y2 = 0.02f;
    ouj_curve33.ouj_y3 = 0.02f;
    ouj_curve33.ouj_y4 = 0.35f;

    ouj_curve34.ouj_x1 = -0.06;
    ouj_curve34.ouj_x2 = -0.075f;
    ouj_curve34.ouj_x3 = 0.075f;
    ouj_curve34.ouj_x4 = 0.06f;

    ouj_curve34.ouj_y1 = 0.35f;
    ouj_curve34.ouj_y2 = 0.07f;
    ouj_curve34.ouj_y3 = 0.07f;
    ouj_curve34.ouj_y4 = 0.35f;


    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        Cut1[i] = (((pow(1 - t, 3)) * ouj_curve33.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve33.ouj_x2)) + ((3 * (pow(t, 2) *(1-t)) * ouj_curve33.ouj_x3)) + ((pow(t, 3)) * ouj_curve33.ouj_x4));
        Cvt1[i] = (((pow(1 - t, 3)) * ouj_curve33.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve33.ouj_y2)) + ((3 * (pow(t, 2)*(1-t)) * ouj_curve33.ouj_y3)) + ((pow(t, 3)) * ouj_curve33.ouj_y4));
    }

    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
         Cut2[i] = (((pow(1 - t, 3)) * ouj_curve34.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve34.ouj_x2)) + ((3 * (pow(t, 2) *(1-t)) * ouj_curve34.ouj_x3)) + ((pow(t, 3)) * ouj_curve34.ouj_x4));
         Cvt2[i] = (((pow(1 - t, 3)) * ouj_curve34.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve34.ouj_y2)) + ((3 * (pow(t, 2) *(1-t)) * ouj_curve34.ouj_y3)) + ((pow(t, 3)) * ouj_curve34.ouj_y4));
     }

     glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLE_STRIP);
    {
        for (i = 0; i < 100; i++)
        {
            glVertex3f(VALUE_FROM_PERCENT(Cut1[i], percent) + x_pos, VALUE_FROM_PERCENT(Cvt1[i], percent) + y_pos, 0.0f);
            glVertex3f(VALUE_FROM_PERCENT(Cut2[i], percent) + x_pos, VALUE_FROM_PERCENT(Cvt2[i], percent) + y_pos, 0.0f);
        }
    }
    glEnd();
}


void Texture_RR(float x_pos, float y_pos, float percent)
{
   

    float t = 0.0f;
    int i = 0;
    
    struct ouj_Curve ouj_curve21;

    struct ouj_Curve ouj_curve22;

    //co-ordinate x,y
    ouj_curve21.ouj_x1 = 0.0f;
    ouj_curve21.ouj_y1 = 0.35f;
    ouj_curve21.ouj_x2 = 0.5f;
    ouj_curve21.ouj_y2 = 0.32f;
    ouj_curve21.ouj_x3 = 0.04f;
    ouj_curve21.ouj_y3 = 0.01f;
    ouj_curve21.ouj_x4 = 0.0f;
    ouj_curve21.ouj_y4 = 0.0f;

    ouj_curve22.ouj_x1 = 0.0f;
    ouj_curve22.ouj_y1 = 0.3f;
    ouj_curve22.ouj_x2 = 0.25f;
    ouj_curve22.ouj_y2 = 0.32f;
    ouj_curve22.ouj_x3 = 0.02f;
    ouj_curve22.ouj_y3 = 0.03f;
    ouj_curve22.ouj_x4= 0.0f;
    ouj_curve22.ouj_y4 = 0.05f;

    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        Cwt1[i] = (((pow(1 - t, 3)) * ouj_curve21.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve21.ouj_x2)) + ((3 * (pow(t, 2) * (1-t)) * ouj_curve21.ouj_x3)) + ((pow(t, 3)) * ouj_curve21.ouj_x4));
        Cxt1[i] = (((pow(1 - t, 3)) * ouj_curve21.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve21.ouj_y2)) + ((3 * (pow(t, 2) * (1-t)) * ouj_curve21.ouj_y3)) + ((pow(t, 3)) * ouj_curve21.ouj_y4));
    }

    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
         Cwt2[i] = (((pow(1 - t, 3)) * ouj_curve22.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve22.ouj_x2)) + ((3 * (pow(t, 2) * (1-t)) * ouj_curve22.ouj_x3)) + ((pow(t, 3)) * ouj_curve22.ouj_x4));
         Cxt2[i] = (((pow(1 - t, 3)) * ouj_curve22.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve22.ouj_y2)) + ((3 * (pow(t, 2) * (1-t)) * ouj_curve22.ouj_y3)) + ((pow(t, 3)) * ouj_curve22.ouj_y4));
     }

     glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLE_STRIP);
    {
        for (i = 0; i < 100; i++)
        {
            glVertex3f(VALUE_FROM_PERCENT(Cwt1[i], percent) + x_pos, VALUE_FROM_PERCENT(Cxt1[i], percent) + y_pos, 0.0f);
            glVertex3f(VALUE_FROM_PERCENT(Cwt2[i], percent) + x_pos, VALUE_FROM_PERCENT(Cxt2[i], percent) + y_pos, 0.0f);
        }
    }
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    {
        glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
        glVertex3f( VALUE_FROM_PERCENT(-0.06f,percent)+ x_pos, VALUE_FROM_PERCENT( -0.35f,percent)+ y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f,percent) + x_pos, VALUE_FROM_PERCENT(-0.35f,percent)+ y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.06f,percent)+ x_pos ,VALUE_FROM_PERCENT(0.1f,percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f,percent)+ x_pos, VALUE_FROM_PERCENT( 0.2f,percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.06f,percent)+x_pos , VALUE_FROM_PERCENT( 0.35f,percent)+ y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f,percent)+x_pos,   VALUE_FROM_PERCENT(0.35f,percent)+ y_pos, 0.0f);

      
        
    }
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f( VALUE_FROM_PERCENT(-0.079f,percent)+ x_pos, VALUE_FROM_PERCENT( -0.35f,percent)+ y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.023f,percent) + x_pos, VALUE_FROM_PERCENT(-0.37f,percent)+ y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.023f,percent)+ x_pos ,VALUE_FROM_PERCENT(-0.35f,percent) + y_pos,0.0f); 
        glVertex3f(VALUE_FROM_PERCENT(0.024f,percent) + x_pos, VALUE_FROM_PERCENT(-0.35f,percent)+ y_pos, 0.0f);

      
        
    }
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f( VALUE_FROM_PERCENT(-0.07f,percent)+ x_pos, VALUE_FROM_PERCENT(0.35f,percent)+ y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.1f,percent) + x_pos, VALUE_FROM_PERCENT(0.35f,percent)+ y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.06f,percent)+ x_pos ,VALUE_FROM_PERCENT(0.31f,percent) + y_pos,0.0f); 
    

      
        
    }
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f(VALUE_FROM_PERCENT(-0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.0001f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.05f, percent) + x_pos, VALUE_FROM_PERCENT(0.025f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.2f, percent) + x_pos, VALUE_FROM_PERCENT(-0.25f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(-0.35f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.4f, percent) + x_pos, VALUE_FROM_PERCENT(-0.45f, percent) + y_pos, 0.0f);
        //glVertexf(VALUE_FROM_PERCENT(0.5f, percent) + x_pos, VALUE_FROM_PERCENT(-0.5f, percent) + y_pos, 0.0f);
       
            



    }
    glEnd();
}

void Texture_EE(float x_pos, float y_pos, float percent)
{


    glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
    //***************************************************E*****************************************
    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.1f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.15f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.25f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
    }
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.32f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.1f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.15f, percent) + x_pos, VALUE_FROM_PERCENT(0.32f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.2f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.23f, percent) + x_pos, VALUE_FROM_PERCENT(0.32f, percent) + y_pos, 0.0f);
        //glVertexf(VALUE_FROM_PERCENT(0.31f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
    }
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.16f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.1f, percent) + x_pos, VALUE_FROM_PERCENT(0.16f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.13f, percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.15f, percent) + x_pos, VALUE_FROM_PERCENT(0.16f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.15f, percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);

        
    }
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.035f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.1f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.15f, percent) + x_pos, VALUE_FROM_PERCENT(0.035f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.2f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.23f, percent) + x_pos, VALUE_FROM_PERCENT(0.035f, percent) + y_pos, 0.0f);
        //glVertexf(VALUE_FROM_PERCENT(0.31f, percent) + x_pos, VALUE_FROM_PERCENT(0.05f, percent) + y_pos, 0.0f);


    }
    glEnd();
}

void Group_G(float x_pos, float y_pos, float percent)


{
   

    float t = 0.0f;
    int i = 0;

    struct ouj_Curve ouj_curve23;
    struct ouj_Curve ouj_curve24;
    
    //co-ordinate x,y
    ouj_curve23.ouj_x1 = 0.07f;
    ouj_curve23.ouj_x2 = -0.3f;
    ouj_curve23.ouj_x3 = -0.27f;
    ouj_curve23.ouj_x4 = 0.0f;

   
    ouj_curve23.ouj_y1 = 0.35f;
    ouj_curve23.ouj_y2 = 0.3f;
    ouj_curve23.ouj_y3 = 0.08f;
    ouj_curve23.ouj_y4 = 0.03f;

    ouj_curve24.ouj_x1 = 0.03f;
    ouj_curve24.ouj_x2 = -0.22f;
    ouj_curve24.ouj_x3 = -0.20f;
    ouj_curve24.ouj_x4 = 0.0f;

    ouj_curve24.ouj_y1 = 0.3f;
    ouj_curve24.ouj_y2 = 0.3f;
    ouj_curve24.ouj_y3 = 0.08f;
    ouj_curve24.ouj_y4 = 0.05f;


    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        ouj_Dat1[i] = (((pow(1 - t, 3)) *  ouj_curve23.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve23.ouj_x2)) + ((3 * (pow(t, 2) *(1-t)) *  ouj_curve23.ouj_x3)) + ((pow(t, 3)) *  ouj_curve23.ouj_x4));
        ouj_Dbt1[i] = (((pow(1 - t, 3)) *  ouj_curve23.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve23.ouj_y2)) + ((3 * (pow(t, 2)*(1-t)) *  ouj_curve23.ouj_y3)) + ((pow(t, 3)) *  ouj_curve23.ouj_y4));
    }

    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
         ouj_Dat2[i] = (((pow(1 - t, 3)) *  ouj_curve24.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve24.ouj_x2)) + ((3 * (pow(t, 2) *(1-t)) *  ouj_curve24.ouj_x3)) + ((pow(t, 3)) *  ouj_curve24.ouj_x4));
         ouj_Dbt2[i] = (((pow(1 - t, 3)) *  ouj_curve24.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve24.ouj_y2)) + ((3 * (pow(t, 2) *(1-t)) *  ouj_curve24.ouj_y3)) + ((pow(t, 3)) *  ouj_curve24.ouj_y4));
     }

    glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLE_STRIP);
    {
        for (i = 0; i < 100; i++)
        {
            glVertex3f(VALUE_FROM_PERCENT(ouj_Dat1[i], percent) + x_pos, VALUE_FROM_PERCENT(ouj_Dbt1[i], percent) + y_pos, 0.0f);
            glVertex3f(VALUE_FROM_PERCENT(ouj_Dat2[i], percent) + x_pos, VALUE_FROM_PERCENT(ouj_Dbt2[i], percent) + y_pos, 0.0f);
        }
    }
    glEnd();

    

    glBegin(GL_TRIANGLE_STRIP);
    {
        glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
        glVertex3f( VALUE_FROM_PERCENT(-0.0f,percent)+ x_pos, VALUE_FROM_PERCENT( -0.06f,percent)+ y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.04f,percent) + x_pos, VALUE_FROM_PERCENT(-0.06f,percent)+ y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.0f,percent)+ x_pos ,VALUE_FROM_PERCENT(0.12f,percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.04f,percent)+ x_pos, VALUE_FROM_PERCENT( 0.12f,percent) + y_pos,0.0f);
        // glVertex3f(VALUE_FROM_PERCENT(0.0f,percent)+x_pos , VALUE_FROM_PERCENT( 0.22f,percent)+ y_pos, 0.0f);
        // glVertex3f(VALUE_FROM_PERCENT(0.04f,percent)+x_pos,   VALUE_FROM_PERCENT(0.22f,percent)+ y_pos, 0.0f);

      
        
    }
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
    {
        glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
        glVertex3f( VALUE_FROM_PERCENT(-0.04f,percent)+ x_pos, VALUE_FROM_PERCENT( 0.12f,percent)+ y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.04f,percent) + x_pos, VALUE_FROM_PERCENT(0.16f,percent)+ y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f,percent)+ x_pos ,VALUE_FROM_PERCENT(0.12f,percent) + y_pos,0.0f); 
        glVertex3f(VALUE_FROM_PERCENT(0.03f,percent) + x_pos, VALUE_FROM_PERCENT(0.16f,percent)+ y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.07f,percent)+ x_pos ,VALUE_FROM_PERCENT(0.12f,percent) + y_pos,0.0f); 
        glVertex3f(VALUE_FROM_PERCENT(0.07f,percent) + x_pos, VALUE_FROM_PERCENT(0.16f,percent)+ y_pos, 0.0f);

      
        
    }
    glEnd();

 
    
}

void Group_R(float x_pos, float y_pos, float percent)
{
    float t = 0.0f;
    int i = 0;
    
    struct ouj_Curve ouj_curve25;

    struct ouj_Curve ouj_curve26;

    //co-ordinate x,y
    ouj_curve25.ouj_x1 = 0.0f;
    ouj_curve25.ouj_y1 = 0.35f;
    ouj_curve25.ouj_x2 = 0.5f;
    ouj_curve25.ouj_y2 = 0.32f;
    ouj_curve25.ouj_x3 = 0.04f;
    ouj_curve25.ouj_y3 = 0.01f;
    ouj_curve25.ouj_x4 = 0.0f;
    ouj_curve25.ouj_y4 = -0.02f;

    ouj_curve26.ouj_x1 = 0.0f;
    ouj_curve26.ouj_y1 = 0.3f;
    ouj_curve26.ouj_x2 = 0.25f;
    ouj_curve26.ouj_y2 = 0.32f;
    ouj_curve26.ouj_x3 = 0.02f;
    ouj_curve26.ouj_y3 = 0.03f;
    ouj_curve26.ouj_x4= 0.0f;
    ouj_curve26.ouj_y4 = 0.025f;

    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        ouj_Dct1[i] = (((pow(1 - t, 3)) * ouj_curve25.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve25.ouj_x2)) + ((3 * (pow(t, 2) * (1-t)) * ouj_curve25.ouj_x3)) + ((pow(t, 3)) * ouj_curve26.ouj_x4));
        ouj_Ddt1[i] = (((pow(1 - t, 3)) * ouj_curve25.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve25.ouj_y2)) + ((3 * (pow(t, 2) * (1-t)) * ouj_curve25.ouj_y3)) + ((pow(t, 3)) * ouj_curve26.ouj_y4));
    }

    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
         ouj_Dct2[i] = (((pow(1 - t, 3)) * ouj_curve26.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve26.ouj_x2)) + ((3 * (pow(t, 2) * (1-t)) * ouj_curve26.ouj_x3)) + ((pow(t, 3)) * ouj_curve26.ouj_x4));
         ouj_Ddt2[i] = (((pow(1 - t, 3)) * ouj_curve26.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve26.ouj_y2)) + ((3 * (pow(t, 2) * (1-t)) * ouj_curve26.ouj_y3)) + ((pow(t, 3)) * ouj_curve26.ouj_y4));
     }

     glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLE_STRIP);
    {
        for (i = 0; i < 100; i++)
        {
            glVertex3f(VALUE_FROM_PERCENT(ouj_Dct1[i], percent) + x_pos, VALUE_FROM_PERCENT(ouj_Ddt1[i], percent) + y_pos, 0.0f);
            glVertex3f(VALUE_FROM_PERCENT(ouj_Dct2[i], percent) + x_pos, VALUE_FROM_PERCENT(ouj_Ddt2[i], percent) + y_pos, 0.0f);
        }
    }
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    {
        glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
        glVertex3f( VALUE_FROM_PERCENT(-0.06f,percent)+ x_pos, VALUE_FROM_PERCENT( -0.35f,percent)+ y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f,percent) + x_pos, VALUE_FROM_PERCENT(-0.35f,percent)+ y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.06f,percent)+ x_pos ,VALUE_FROM_PERCENT(0.1f,percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f,percent)+ x_pos, VALUE_FROM_PERCENT( 0.2f,percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.06f,percent)+x_pos , VALUE_FROM_PERCENT( 0.35f,percent)+ y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f,percent)+x_pos,   VALUE_FROM_PERCENT(0.35f,percent)+ y_pos, 0.0f);

      
        
    }
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f( VALUE_FROM_PERCENT(-0.079f,percent)+ x_pos, VALUE_FROM_PERCENT( -0.35f,percent)+ y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.023f,percent) + x_pos, VALUE_FROM_PERCENT(-0.37f,percent)+ y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.023f,percent)+ x_pos ,VALUE_FROM_PERCENT(-0.35f,percent) + y_pos,0.0f); 
        glVertex3f(VALUE_FROM_PERCENT(0.024f,percent) + x_pos, VALUE_FROM_PERCENT(-0.35f,percent)+ y_pos, 0.0f);

      
        
    }
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f( VALUE_FROM_PERCENT(-0.07f,percent)+ x_pos, VALUE_FROM_PERCENT(0.35f,percent)+ y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.1f,percent) + x_pos, VALUE_FROM_PERCENT(0.35f,percent)+ y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.06f,percent)+ x_pos ,VALUE_FROM_PERCENT(0.31f,percent) + y_pos,0.0f); 
    

      
        
    }
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f(VALUE_FROM_PERCENT(-0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.02f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.05f, percent) + x_pos, VALUE_FROM_PERCENT(0.027f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.2f, percent) + x_pos, VALUE_FROM_PERCENT(-0.25f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(-0.35f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.4f, percent) + x_pos, VALUE_FROM_PERCENT(-0.45f, percent) + y_pos, 0.0f);
        //glVertexf(VALUE_FROM_PERCENT(0.5f, percent) + x_pos, VALUE_FROM_PERCENT(-0.5f, percent) + y_pos, 0.0f);
       
            



    }
    glEnd();
}

void Group_O(float x_pos, float y_pos, float percent)
{
    float t = 0.0f;
    int i = 0;

    struct ouj_Curve ouj_curve27;
    struct ouj_Curve ouj_curve28;
   
    
    //co-ordinate x,y
    ouj_curve27.ouj_x1 = 0.0f;
    ouj_curve27.ouj_x2 = -0.15f;
    ouj_curve27.ouj_x3 = -0.15f;
    ouj_curve27.ouj_x4 = 0.02f;

    ouj_curve27.ouj_y1 = 0.34f;
    ouj_curve27.ouj_y2 = 0.32f;
    ouj_curve27.ouj_y3 = 0.03f;
    ouj_curve27.ouj_y4= 0.0f;

    ouj_curve28.ouj_x1 = 0.0f;
    ouj_curve28.ouj_x2 = -0.1f;
    ouj_curve28.ouj_x3 = -0.1f;
    ouj_curve28.ouj_x4 = 0.02f;

    ouj_curve28.ouj_y1 = 0.3f;
    ouj_curve28.ouj_y2 = 0.32f;
    ouj_curve28.ouj_y3 = 0.05f;
    ouj_curve28.ouj_y4 = 0.03f;


    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        ouj_Det1[i] = (((pow(1 - t, 3)) * ouj_curve27.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve27.ouj_x2)) + ((3 * (pow(t, 2) * (1 - t)) * ouj_curve27.ouj_x3)) + ((pow(t, 3)) * ouj_curve27.ouj_x4));
        ouj_Dft1[i] = (((pow(1 - t, 3)) * ouj_curve27.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve27.ouj_y2)) + ((3 * (pow(t, 2) * (1 - t)) * ouj_curve27.ouj_y3)) + ((pow(t, 3)) * ouj_curve27.ouj_y4));
    }

    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        ouj_Det2[i] = (((pow(1 - t, 3)) * ouj_curve28.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve28.ouj_x2)) + ((3 * (pow(t, 2) * (1 - t)) * ouj_curve28.ouj_x3)) + ((pow(t, 3)) * ouj_curve28.ouj_x4));
        ouj_Dft2[i] = (((pow(1 - t, 3)) * ouj_curve28.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve28.ouj_y2)) + ((3 * (pow(t, 2) * (1 - t)) * ouj_curve28.ouj_y3)) + ((pow(t, 3)) * ouj_curve28.ouj_y4));
    }



    glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLE_STRIP);
    {
        for (i = 0; i < 100; i++)
        {
            glVertex3f(VALUE_FROM_PERCENT(ouj_Det1[i], percent) + x_pos, VALUE_FROM_PERCENT( ouj_Dft1[i], percent) + y_pos, 0.0f);
            glVertex3f(VALUE_FROM_PERCENT(ouj_Det2[i], percent) + x_pos, VALUE_FROM_PERCENT( ouj_Dft2[i], percent) + y_pos, 0.0f);

        }
    }
    glEnd();

    struct ouj_Curve ouj_curve29;
    struct ouj_Curve ouj_curve30;

    //Co-ordinate x,y 
    ouj_curve29.ouj_x1 = 0.0f;
    ouj_curve29.ouj_x2 = 0.15f;
    ouj_curve29.ouj_x3 = 0.15f;
    ouj_curve29.ouj_x4 = 0.0f;

    ouj_curve29.ouj_y1 = 0.34f;
    ouj_curve29.ouj_y2 = 0.3f;
    ouj_curve29.ouj_y3 = 0.03f;
    ouj_curve29.ouj_y4 = 0.0f;

    ouj_curve30.ouj_x1 = 0.0f;
    ouj_curve30.ouj_x2 = 0.1f;
    ouj_curve30.ouj_x3 = 0.1f;
    ouj_curve30.ouj_x4 = 0.0f;

    ouj_curve30.ouj_y1 = 0.3f;
    ouj_curve30.ouj_y2 = 0.3f;
    ouj_curve30.ouj_y3 = 0.05f;
    ouj_curve30.ouj_y4 = 0.03f;

    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        ouj_Dgt1[i] = (((pow(1 - t, 3)) *  ouj_curve29.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve29.ouj_x2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve29.ouj_x3)) + ((pow(t, 3)) *  ouj_curve29.ouj_x4));
        ouj_Dht1[i] = (((pow(1 - t, 3)) *  ouj_curve29.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve29.ouj_y2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve29.ouj_y3)) + ((pow(t, 3)) *  ouj_curve29.ouj_y4));
    }

    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        ouj_Dgt2[i] = (((pow(1 - t, 3)) *  ouj_curve30.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve30.ouj_x2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve30.ouj_x3)) + ((pow(t, 3)) *  ouj_curve30.ouj_x4));
        ouj_Dht2[i] = (((pow(1 - t, 3)) *  ouj_curve30.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve30.ouj_y2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve30.ouj_y3)) + ((pow(t, 3)) *  ouj_curve30.ouj_y4));
    }


    glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLE_STRIP);
    {
        for (i = 0; i < 100; i++)
        {
            glVertex3f(VALUE_FROM_PERCENT(ouj_Dgt1[i], percent) + x_pos, VALUE_FROM_PERCENT(ouj_Dht1[i], percent) + y_pos, 0.0f);
            glVertex3f(VALUE_FROM_PERCENT(ouj_Dgt2[i], percent) + x_pos, VALUE_FROM_PERCENT(ouj_Dht2[i], percent) + y_pos, 0.0f);
        }
    }
    glEnd();
}

void Group_U(float x_pos, float y_pos, float percent)
{
   

    float t = 0.0f;
    int i = 0;

    struct ouj_Curve ouj_curve31;
    struct ouj_Curve ouj_curve32;
    
    //co-ordinate x,y
    ouj_curve31.ouj_x1 = -0.09f;
    ouj_curve31.ouj_x2 = -0.1f;
    ouj_curve31.ouj_x3 = 0.1f;
    ouj_curve31.ouj_x4 = 0.09f;

   
    ouj_curve31.ouj_y1 = 0.35f;
    ouj_curve31.ouj_y2 = 0.02f;
    ouj_curve31.ouj_y3 = 0.02f;
    ouj_curve31.ouj_y4 = 0.35f;

    ouj_curve32.ouj_x1 = -0.06;
    ouj_curve32.ouj_x2 = -0.075f;
    ouj_curve32.ouj_x3 = 0.075f;
    ouj_curve32.ouj_x4 = 0.06f;

    ouj_curve32.ouj_y1 = 0.35f;
    ouj_curve32.ouj_y2 = 0.07f;
    ouj_curve32.ouj_y3 = 0.07f;
    ouj_curve32.ouj_y4 = 0.35f;


    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        ouj_Dit1[i] = (((pow(1 - t, 3)) * ouj_curve31.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve31.ouj_x2)) + ((3 * (pow(t, 2) *(1-t)) * ouj_curve31.ouj_x3)) + ((pow(t, 3)) * ouj_curve31.ouj_x4));
        ouj_Djt1[i] = (((pow(1 - t, 3)) * ouj_curve31.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve31.ouj_y2)) + ((3 * (pow(t, 2)*(1-t)) * ouj_curve31.ouj_y3)) + ((pow(t, 3)) * ouj_curve31.ouj_y4));
    }

    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        ouj_Dit2[i] = (((pow(1 - t, 3)) * ouj_curve32.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve32.ouj_x2)) + ((3 * (pow(t, 2) *(1-t)) * ouj_curve32.ouj_x3)) + ((pow(t, 3)) * ouj_curve32.ouj_x4));
        ouj_Djt2[i] = (((pow(1 - t, 3)) * ouj_curve32.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve32.ouj_y2)) + ((3 * (pow(t, 2) *(1-t)) * ouj_curve32.ouj_y3)) + ((pow(t, 3)) * ouj_curve32.ouj_y4));
     }

     glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLE_STRIP);
    {
        for (i = 0; i < 100; i++)
        {
            glVertex3f(VALUE_FROM_PERCENT( ouj_Dit1[i], percent) + x_pos, VALUE_FROM_PERCENT( ouj_Djt1[i], percent) + y_pos, 0.0f);
            glVertex3f(VALUE_FROM_PERCENT( ouj_Dit2[i], percent) + x_pos, VALUE_FROM_PERCENT( ouj_Djt2[i], percent) + y_pos, 0.0f);
        }
    }
    glEnd();
}

void Group_P(float x_pos, float y_pos, float percent)
{
   

    float t = 0.0f;
    int i = 0;

    struct ouj_Curve ouj_curve33;
    struct ouj_Curve ouj_curve34;
    //co-ordinate x,y
    ouj_curve33.ouj_x1 = 0.0f;
    ouj_curve33.ouj_y1 = 0.35f;
    ouj_curve33.ouj_x2 = 0.5f;
    ouj_curve33.ouj_y2 = 0.25f;
    ouj_curve33.ouj_x3 = 0.04f;
    ouj_curve33.ouj_y3 = 0.01f;
    ouj_curve33.ouj_x4 = 0.0f;
    ouj_curve33.ouj_y4 = 0.0f;

    ouj_curve34.ouj_x1 = 0.0f;
    ouj_curve34.ouj_y1 = 0.3f;
    ouj_curve34.ouj_x2 = 0.25f;
    ouj_curve34.ouj_y2 = 0.25f;
    ouj_curve34.ouj_x3 = 0.02f;
    ouj_curve34.ouj_y3 = 0.03f;
    ouj_curve34.ouj_x4 = 0.0f;
    ouj_curve34.ouj_y4 = 0.05f;

    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        ouj_Dkt1[i] = (((pow(1 - t, 3)) * ouj_curve33.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve33.ouj_x2)) + ((3 * (pow(t, 2) * (1-t)) * ouj_curve33.ouj_x3)) + ((pow(t, 3)) * ouj_curve33.ouj_x4));
        ouj_Dlt1[i] = (((pow(1 - t, 3)) * ouj_curve33.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve33.ouj_y2)) + ((3 * (pow(t, 2) * (1-t)) * ouj_curve33.ouj_y3)) + ((pow(t, 3)) * ouj_curve33.ouj_y4));
      
    }

    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        ouj_Dkt2[i] = (((pow(1 - t, 3)) * ouj_curve34.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve34.ouj_x2)) + ((3 * (pow(t, 2) * (1-t)) * ouj_curve34.ouj_x3)) + ((pow(t, 3)) * ouj_curve34.ouj_x4));
        ouj_Dlt2[i] = (((pow(1 - t, 3)) * ouj_curve34.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve34.ouj_y2)) + ((3 * (pow(t, 2) * (1-t)) * ouj_curve34.ouj_y3)) + ((pow(t, 3)) * ouj_curve34.ouj_y4));
     }

     glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLE_STRIP);
    {
        for (i = 0; i < 100; i++)
        {
            glVertex3f(VALUE_FROM_PERCENT(ouj_Dkt1[i], percent) + x_pos, VALUE_FROM_PERCENT(ouj_Dlt1[i], percent) + y_pos, 0.0f);
            glVertex3f(VALUE_FROM_PERCENT(ouj_Dkt2[i], percent) + x_pos, VALUE_FROM_PERCENT(ouj_Dlt2[i], percent) + y_pos, 0.0f);
        }
    }
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    {
        glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
        glVertex3f( VALUE_FROM_PERCENT(-0.065f,percent)+ x_pos, VALUE_FROM_PERCENT( -0.35f,percent)+ y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f,percent) + x_pos, VALUE_FROM_PERCENT(-0.35f,percent)+ y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.065f,percent)+ x_pos ,VALUE_FROM_PERCENT(0.1f,percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f,percent)+ x_pos, VALUE_FROM_PERCENT( 0.2f,percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.065f,percent)+x_pos , VALUE_FROM_PERCENT( 0.35f,percent)+ y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f,percent)+x_pos,   VALUE_FROM_PERCENT(0.35f,percent)+ y_pos, 0.0f);

      
        
    }
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f( VALUE_FROM_PERCENT(-0.079f,percent)+ x_pos, VALUE_FROM_PERCENT( -0.35f,percent)+ y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.023f,percent) + x_pos, VALUE_FROM_PERCENT(-0.37f,percent)+ y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.023f,percent)+ x_pos ,VALUE_FROM_PERCENT(-0.35f,percent) + y_pos,0.0f); 
        glVertex3f(VALUE_FROM_PERCENT(0.024f,percent) + x_pos, VALUE_FROM_PERCENT(-0.35f,percent)+ y_pos, 0.0f);

      
        
    }
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f( VALUE_FROM_PERCENT(-0.065f,percent)+ x_pos, VALUE_FROM_PERCENT(0.35f,percent)+ y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.1f,percent) + x_pos, VALUE_FROM_PERCENT(0.35f,percent)+ y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.065f,percent)+ x_pos ,VALUE_FROM_PERCENT(0.31f,percent) + y_pos,0.0f); 
    

      
        
    }
    glEnd();

}

void Present_P(float x_pos, float y_pos, float percent)
{
   

    float t = 0.0f;
    int i = 0;

    struct ouj_Curve ouj_curve35;
    struct ouj_Curve ouj_curve36;
    //co-ordinate x,y
    ouj_curve35.ouj_x1 = 0.0f;
    ouj_curve35.ouj_y1 = 0.35f;
    ouj_curve35.ouj_x2 = 0.5f;
    ouj_curve35.ouj_y2 = 0.25f;
    ouj_curve35.ouj_x3 = 0.04f;
    ouj_curve35.ouj_y3 = 0.01f;
    ouj_curve35.ouj_x4 = 0.0f;
    ouj_curve35.ouj_y4 = 0.0f;

    ouj_curve36.ouj_x1 = 0.0f;
    ouj_curve36.ouj_y1 = 0.3f;
    ouj_curve36.ouj_x2 = 0.25f;
    ouj_curve36.ouj_y2 = 0.25f;
    ouj_curve36.ouj_x3 = 0.02f;
    ouj_curve36.ouj_y3 = 0.03f;
    ouj_curve36.ouj_x4 = 0.0f;
    ouj_curve36.ouj_y4 = 0.05f;

    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        ouj_Dmt1[i] = (((pow(1 - t, 3)) * ouj_curve35.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve35.ouj_x2)) + ((3 * (pow(t, 2) * (1-t)) * ouj_curve35.ouj_x3)) + ((pow(t, 3)) * ouj_curve35.ouj_x4));
        ouj_Dnt1[i] = (((pow(1 - t, 3)) * ouj_curve35.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve35.ouj_y2)) + ((3 * (pow(t, 2) * (1-t)) * ouj_curve35.ouj_y3)) + ((pow(t, 3)) * ouj_curve35.ouj_y4));
      
    }

    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        ouj_Dmt2[i] = (((pow(1 - t, 3)) * ouj_curve36.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve36.ouj_x2)) + ((3 * (pow(t, 2) * (1-t)) * ouj_curve36.ouj_x3)) + ((pow(t, 3)) * ouj_curve36.ouj_x4));
        ouj_Dnt2[i] = (((pow(1 - t, 3)) * ouj_curve36.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve36.ouj_y2)) + ((3 * (pow(t, 2) * (1-t)) * ouj_curve36.ouj_y3)) + ((pow(t, 3)) * ouj_curve36.ouj_y4));
     }

     glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLE_STRIP);
    {
        for (i = 0; i < 100; i++)
        {
            glVertex3f(VALUE_FROM_PERCENT(ouj_Dmt1[i], percent) + x_pos, VALUE_FROM_PERCENT(ouj_Dnt1[i], percent) + y_pos, 0.0f);
            glVertex3f(VALUE_FROM_PERCENT(ouj_Dmt2[i], percent) + x_pos, VALUE_FROM_PERCENT(ouj_Dnt2[i], percent) + y_pos, 0.0f);
        }
    }
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    {
        glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
        glVertex3f( VALUE_FROM_PERCENT(-0.065f,percent)+ x_pos, VALUE_FROM_PERCENT( -0.35f,percent)+ y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f,percent) + x_pos, VALUE_FROM_PERCENT(-0.35f,percent)+ y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.065f,percent)+ x_pos ,VALUE_FROM_PERCENT(0.1f,percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f,percent)+ x_pos, VALUE_FROM_PERCENT( 0.2f,percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.065f,percent)+x_pos , VALUE_FROM_PERCENT( 0.35f,percent)+ y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f,percent)+x_pos,   VALUE_FROM_PERCENT(0.35f,percent)+ y_pos, 0.0f);

      
        
    }
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f( VALUE_FROM_PERCENT(-0.079f,percent)+ x_pos, VALUE_FROM_PERCENT( -0.35f,percent)+ y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.023f,percent) + x_pos, VALUE_FROM_PERCENT(-0.37f,percent)+ y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.023f,percent)+ x_pos ,VALUE_FROM_PERCENT(-0.35f,percent) + y_pos,0.0f); 
        glVertex3f(VALUE_FROM_PERCENT(0.024f,percent) + x_pos, VALUE_FROM_PERCENT(-0.35f,percent)+ y_pos, 0.0f);

      
        
    }
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f( VALUE_FROM_PERCENT(-0.065f,percent)+ x_pos, VALUE_FROM_PERCENT(0.35f,percent)+ y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.1f,percent) + x_pos, VALUE_FROM_PERCENT(0.35f,percent)+ y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.065f,percent)+ x_pos ,VALUE_FROM_PERCENT(0.31f,percent) + y_pos,0.0f); 
    

      
        
    }
    glEnd();

}

void Present_R(float x_pos, float y_pos, float percent)
{
   

    float t = 0.0f;
    int i = 0;
    
    struct ouj_Curve ouj_curve37;

    struct ouj_Curve ouj_curve38;

    //co-ordinate x,y
    ouj_curve37.ouj_x1 = 0.0f;
    ouj_curve37.ouj_y1 = 0.35f;
    ouj_curve37.ouj_x2 = 0.5f;
    ouj_curve37.ouj_y2 = 0.32f;
    ouj_curve37.ouj_x3 = 0.04f;
    ouj_curve37.ouj_y3 = 0.01f;
    ouj_curve37.ouj_x4 = 0.0f;
    ouj_curve37.ouj_y4 = 0.0f;

    ouj_curve38.ouj_x1 = 0.0f;
    ouj_curve38.ouj_y1 = 0.3f;
    ouj_curve38.ouj_x2 = 0.25f;
    ouj_curve38.ouj_y2 = 0.32f;
    ouj_curve38.ouj_x3 = 0.02f;
    ouj_curve38.ouj_y3 = 0.03f;
    ouj_curve38.ouj_x4= 0.0f;
    ouj_curve38.ouj_y4 = 0.05f;

    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        ouj_Dot1[i] = (((pow(1 - t, 3)) * ouj_curve37.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve37.ouj_x2)) + ((3 * (pow(t, 2) * (1-t)) * ouj_curve37.ouj_x3)) + ((pow(t, 3)) * ouj_curve37.ouj_x4));
        ouj_Dpt1[i] = (((pow(1 - t, 3)) * ouj_curve37.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve37.ouj_y2)) + ((3 * (pow(t, 2) * (1-t)) * ouj_curve37.ouj_y3)) + ((pow(t, 3)) * ouj_curve37.ouj_y4));
    }

    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
         ouj_Dot2[i] = (((pow(1 - t, 3)) * ouj_curve38.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve38.ouj_x2)) + ((3 * (pow(t, 2) * (1-t)) * ouj_curve38.ouj_x3)) + ((pow(t, 3)) * ouj_curve38.ouj_x4));
         ouj_Dpt2[i] = (((pow(1 - t, 3)) * ouj_curve38.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve38.ouj_y2)) + ((3 * (pow(t, 2) * (1-t)) * ouj_curve38.ouj_y3)) + ((pow(t, 3)) * ouj_curve38.ouj_y4));
     }

     glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLE_STRIP);
    {
        for (i = 0; i < 100; i++)
        {
            glVertex3f(VALUE_FROM_PERCENT(ouj_Dot1[i], percent) + x_pos, VALUE_FROM_PERCENT(ouj_Dpt1[i], percent) + y_pos, 0.0f);
            glVertex3f(VALUE_FROM_PERCENT(ouj_Dot2[i], percent) + x_pos, VALUE_FROM_PERCENT(ouj_Dpt2[i], percent) + y_pos, 0.0f);
        }
    }
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    {
        glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
        glVertex3f( VALUE_FROM_PERCENT(-0.06f,percent)+ x_pos, VALUE_FROM_PERCENT( -0.35f,percent)+ y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f,percent) + x_pos, VALUE_FROM_PERCENT(-0.35f,percent)+ y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.06f,percent)+ x_pos ,VALUE_FROM_PERCENT(0.1f,percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f,percent)+ x_pos, VALUE_FROM_PERCENT( 0.2f,percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.06f,percent)+x_pos , VALUE_FROM_PERCENT( 0.35f,percent)+ y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f,percent)+x_pos,   VALUE_FROM_PERCENT(0.35f,percent)+ y_pos, 0.0f);

      
        
    }
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f( VALUE_FROM_PERCENT(-0.079f,percent)+ x_pos, VALUE_FROM_PERCENT( -0.35f,percent)+ y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.023f,percent) + x_pos, VALUE_FROM_PERCENT(-0.37f,percent)+ y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.023f,percent)+ x_pos ,VALUE_FROM_PERCENT(-0.35f,percent) + y_pos,0.0f); 
        glVertex3f(VALUE_FROM_PERCENT(0.024f,percent) + x_pos, VALUE_FROM_PERCENT(-0.35f,percent)+ y_pos, 0.0f);

      
        
    }
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f( VALUE_FROM_PERCENT(-0.07f,percent)+ x_pos, VALUE_FROM_PERCENT(0.35f,percent)+ y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.1f,percent) + x_pos, VALUE_FROM_PERCENT(0.35f,percent)+ y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.06f,percent)+ x_pos ,VALUE_FROM_PERCENT(0.31f,percent) + y_pos,0.0f); 
    

      
        
    }
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f(VALUE_FROM_PERCENT(-0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.0001f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.05f, percent) + x_pos, VALUE_FROM_PERCENT(0.025f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.2f, percent) + x_pos, VALUE_FROM_PERCENT(-0.25f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(-0.35f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.4f, percent) + x_pos, VALUE_FROM_PERCENT(-0.45f, percent) + y_pos, 0.0f);
        //glVertexf(VALUE_FROM_PERCENT(0.5f, percent) + x_pos, VALUE_FROM_PERCENT(-0.5f, percent) + y_pos, 0.0f);
       
            



    }
    glEnd();
}

void Present_E(float x_pos, float y_pos, float percent)
{


    glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
    //***************************************************E*****************************************
    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.1f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.15f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.25f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
    }
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.32f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.1f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.15f, percent) + x_pos, VALUE_FROM_PERCENT(0.32f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.2f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.23f, percent) + x_pos, VALUE_FROM_PERCENT(0.32f, percent) + y_pos, 0.0f);
        //glVertexf(VALUE_FROM_PERCENT(0.31f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
    }
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.16f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.1f, percent) + x_pos, VALUE_FROM_PERCENT(0.16f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.13f, percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.15f, percent) + x_pos, VALUE_FROM_PERCENT(0.16f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.15f, percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);

        
    }
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.035f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.1f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.15f, percent) + x_pos, VALUE_FROM_PERCENT(0.035f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.2f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.23f, percent) + x_pos, VALUE_FROM_PERCENT(0.035f, percent) + y_pos, 0.0f);
        //glVertexf(VALUE_FROM_PERCENT(0.31f, percent) + x_pos, VALUE_FROM_PERCENT(0.05f, percent) + y_pos, 0.0f);


    }
    glEnd();
}

void Present_S(float x_pos, float y_pos, float percent)
{


    float t = 0.0f;
    int i = 0;

    struct ouj_Curve ouj_curve39;
    struct ouj_Curve ouj_curve40;

    //co-ordinate x,y
    ouj_curve39.ouj_x1 = 0.08f;
    ouj_curve39.ouj_x2 = -0.32f;
    ouj_curve39.ouj_x3 = -0.29f;
    ouj_curve39.ouj_x4 = 0.0f;

    ouj_curve39.ouj_y1 = 0.35f;
    ouj_curve39.ouj_y2 = 0.3f;
    ouj_curve39.ouj_y3 = 0.08f;
    ouj_curve39.ouj_y4 = 0.0f;

    ouj_curve40.ouj_x1 = 0.05f;
    ouj_curve40.ouj_x2 = -0.24f;
    ouj_curve40.ouj_x3 = -0.22f;
    ouj_curve40.ouj_x4 = 0.0f;

    ouj_curve40.ouj_y1 = 0.3f;
    ouj_curve40.ouj_y2 = 0.3f;
    ouj_curve40.ouj_y3 = 0.08f;
    ouj_curve40.ouj_y4 = 0.05f;


    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        ouj_Dqt1[i] = (((pow(1 - t, 3)) *  ouj_curve39.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve39.ouj_x2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve39.ouj_x3)) + ((pow(t, 3)) *  ouj_curve39.ouj_x4));
        ouj_Drt1[i] = (((pow(1 - t, 3)) *  ouj_curve39.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve39.ouj_y2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve39.ouj_y3)) + ((pow(t, 3)) *  ouj_curve39.ouj_y4));
    }

    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        ouj_Dqt2[i] = (((pow(1 - t, 3)) *  ouj_curve40.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve40.ouj_x2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve40.ouj_x3)) + ((pow(t, 3)) *  ouj_curve40.ouj_x4));
        ouj_Drt2[i] = (((pow(1 - t, 3)) *  ouj_curve40.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve40.ouj_y2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve40.ouj_y3)) + ((pow(t, 3)) *  ouj_curve40.ouj_y4));
    }



    glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLE_STRIP);
    {
        for (i = 0; i < 100; i++)
        {
            glVertex3f(VALUE_FROM_PERCENT(ouj_Dqt1[i], percent) + x_pos, VALUE_FROM_PERCENT(ouj_Drt1[i], percent) + y_pos, 0.0f);
            glVertex3f(VALUE_FROM_PERCENT(ouj_Dqt2[i], percent) + x_pos, VALUE_FROM_PERCENT(ouj_Drt2[i], percent) + y_pos, 0.0f);

        }
    }
    glEnd();

    struct ouj_Curve ouj_curve41;
    struct ouj_Curve ouj_curve42;
 
    //Co-ordinate x,y 
    ouj_curve41.ouj_x1 = -0.01f;
    ouj_curve41.ouj_x2 = 0.32f;
    ouj_curve41.ouj_x3 = 0.29f;
    ouj_curve41.ouj_x4 = -0.07f;


    ouj_curve41.ouj_y1 = 0.05f;
    ouj_curve41.ouj_y2 = -0.03f;
    ouj_curve41.ouj_y3 = -0.3f;
    ouj_curve41.ouj_y4 = -0.35f;

    ouj_curve42.ouj_x1 = -0.01f;
    ouj_curve42.ouj_x2 = 0.24f;
    ouj_curve42.ouj_x3 = 0.22f;
    ouj_curve42.ouj_x4 = -0.05f;

    ouj_curve42.ouj_y1 = -0.0f;
    ouj_curve42.ouj_y2 = -0.08f;
    ouj_curve42.ouj_y3 = -0.3f;
    ouj_curve42.ouj_y4= -0.3f;

    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        ouj_Dst1[i] = (((pow(1 - t, 3)) *  ouj_curve41.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve41.ouj_x2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve41.ouj_x3)) + ((pow(t, 3)) *  ouj_curve41.ouj_x4));
        ouj_Dtt1[i] = (((pow(1 - t, 3)) *  ouj_curve41.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve41.ouj_y2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve41.ouj_y3)) + ((pow(t, 3)) *  ouj_curve41.ouj_y4));
    }

    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        ouj_Dst2[i] = (((pow(1 - t, 3)) * ouj_curve42.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve42.ouj_x2)) + ((3 * (pow(t, 2) * (1 - t)) * ouj_curve42.ouj_x3)) + ((pow(t, 3)) * ouj_curve42.ouj_x4));
        ouj_Dtt2[i] = (((pow(1 - t, 3)) * ouj_curve42.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve42.ouj_y2)) + ((3 * (pow(t, 2) * (1 - t)) * ouj_curve42.ouj_y3)) + ((pow(t, 3)) * ouj_curve42.ouj_y4));
    }


    glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLE_STRIP);
    {
        for (i = 0; i < 100; i++)
        {
            glVertex3f(VALUE_FROM_PERCENT(ouj_Dst1[i], percent) + x_pos, VALUE_FROM_PERCENT(ouj_Dtt1[i], percent) + y_pos, 0.0f);
            glVertex3f(VALUE_FROM_PERCENT(ouj_Dst2[i], percent) + x_pos, VALUE_FROM_PERCENT(ouj_Dtt2[i], percent) + y_pos, 0.0f);
        }
    }
    glEnd();


    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f(VALUE_FROM_PERCENT(-0.04f, percent) + x_pos, VALUE_FROM_PERCENT(-0.3f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.06f, percent) + x_pos, VALUE_FROM_PERCENT(-0.35f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.12f, percent) + x_pos, VALUE_FROM_PERCENT(-0.28f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.18f, percent) + x_pos, VALUE_FROM_PERCENT(-0.25f, percent) + y_pos, 0.0f);



    }
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f(VALUE_FROM_PERCENT(0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.05f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.12f, percent) + x_pos, VALUE_FROM_PERCENT(0.295f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.16f, percent) + x_pos, VALUE_FROM_PERCENT(0.26f, percent) + y_pos, 0.0f);




    }
    glEnd(); 
}


void Present_EE(float x_pos, float y_pos, float percent)
{


    glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
    //***************************************************E*****************************************
    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.1f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.15f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.25f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
    }
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.32f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.1f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.15f, percent) + x_pos, VALUE_FROM_PERCENT(0.32f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.2f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.23f, percent) + x_pos, VALUE_FROM_PERCENT(0.32f, percent) + y_pos, 0.0f);
        //glVertexf(VALUE_FROM_PERCENT(0.31f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
    }
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.16f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.1f, percent) + x_pos, VALUE_FROM_PERCENT(0.16f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.13f, percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.15f, percent) + x_pos, VALUE_FROM_PERCENT(0.16f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.15f, percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);

        
    }
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.035f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.1f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.15f, percent) + x_pos, VALUE_FROM_PERCENT(0.035f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.2f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.23f, percent) + x_pos, VALUE_FROM_PERCENT(0.035f, percent) + y_pos, 0.0f);
        //glVertexf(VALUE_FROM_PERCENT(0.31f, percent) + x_pos, VALUE_FROM_PERCENT(0.05f, percent) + y_pos, 0.0f);


    }
    glEnd();
}


void Present_N(float x_pos, float y_pos, float percent)
{
    glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
    //***************************************************M*****************************************
    glBegin(GL_TRIANGLE_STRIP);//left
        {
            glVertex3f(VALUE_FROM_PERCENT(-0.12f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
            glVertex3f(VALUE_FROM_PERCENT(-0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
            glVertex3f(VALUE_FROM_PERCENT(-0.12f, percent) + x_pos, VALUE_FROM_PERCENT(0.15f, percent) + y_pos, 0.0f);
            glVertex3f(VALUE_FROM_PERCENT(-0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);
            glVertex3f(VALUE_FROM_PERCENT(-0.12f, percent) + x_pos, VALUE_FROM_PERCENT(0.25f, percent) + y_pos, 0.0f);
            glVertex3f(VALUE_FROM_PERCENT(-0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
            glVertex3f(VALUE_FROM_PERCENT(-0.12f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
            glVertex3f(VALUE_FROM_PERCENT(-0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
         }
         glEnd();
         glBegin(GL_TRIANGLE_STRIP);
         {
             glVertex3f(VALUE_FROM_PERCENT(-0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
             glVertex3f(VALUE_FROM_PERCENT(-0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.25f, percent) + y_pos, 0.0f);
             glVertex3f(VALUE_FROM_PERCENT(-0.03f, percent) + x_pos, VALUE_FROM_PERCENT(0.27f, percent) + y_pos, 0.0f);
             glVertex3f(VALUE_FROM_PERCENT(-0.03f, percent) + x_pos, VALUE_FROM_PERCENT(0.19f, percent) + y_pos, 0.0f);
             glVertex3f(VALUE_FROM_PERCENT(0.03f, percent) + x_pos, VALUE_FROM_PERCENT(0.18f, percent) + y_pos, 0.0f);
             glVertex3f(VALUE_FROM_PERCENT(-0.03f, percent) + x_pos, VALUE_FROM_PERCENT(0.19f, percent) + y_pos, 0.0f);
             glVertex3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.19f, percent) + y_pos, 0.0f);
             glVertex3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.14f, percent) + y_pos, 0.0f);
             glVertex3f(VALUE_FROM_PERCENT(0.03f, percent) + x_pos, VALUE_FROM_PERCENT(0.18f, percent) + y_pos, 0.0f);
             glVertex3f(VALUE_FROM_PERCENT(0.03f, percent) + x_pos, VALUE_FROM_PERCENT(0.09f, percent) + y_pos, 0.0f);
             glVertex3f(VALUE_FROM_PERCENT(0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.09f, percent) + y_pos, 0.0f);
             glVertex3f(VALUE_FROM_PERCENT(0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);

             
         }
         glEnd();
     
         glBegin(GL_TRIANGLE_STRIP);//right
         {
             glVertex3f(VALUE_FROM_PERCENT(0.12f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
             glVertex3f(VALUE_FROM_PERCENT(0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
             glVertex3f(VALUE_FROM_PERCENT(0.12f, percent) + x_pos, VALUE_FROM_PERCENT(0.15f, percent) + y_pos, 0.0f);
             glVertex3f(VALUE_FROM_PERCENT(0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);
             glVertex3f(VALUE_FROM_PERCENT(0.12f, percent) + x_pos, VALUE_FROM_PERCENT(0.25f, percent) + y_pos, 0.0f);
             glVertex3f(VALUE_FROM_PERCENT(0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
             glVertex3f(VALUE_FROM_PERCENT(0.12f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
             glVertex3f(VALUE_FROM_PERCENT(0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
         }
         glEnd();
    
    
         glBegin(GL_TRIANGLE_STRIP);//left
         {
             glVertex3f(VALUE_FROM_PERCENT(-0.14f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
             glVertex3f(VALUE_FROM_PERCENT(-0.1f, percent) + x_pos, VALUE_FROM_PERCENT(-0.015f, percent) + y_pos, 0.0f);
             glVertex3f(VALUE_FROM_PERCENT(-0.1f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
             glVertex3f(VALUE_FROM_PERCENT(-0.06f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
           
         }
         glEnd();
         glBegin(GL_TRIANGLE_STRIP);
         {
             glVertex3f(VALUE_FROM_PERCENT(0.14f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
             glVertex3f(VALUE_FROM_PERCENT(0.1f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
             glVertex3f(VALUE_FROM_PERCENT(0.1f, percent) + x_pos, VALUE_FROM_PERCENT(0.36f, percent) + y_pos, 0.0f);
             glVertex3f(VALUE_FROM_PERCENT(0.06f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
           
         }
          
         glEnd();
}

void Present_T(float x_pos, float y_pos, float percent)
{


    glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
    //***************************************************T*****************************************
    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f(VALUE_FROM_PERCENT(-0.02f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.02f, percent) + x_pos, VALUE_FROM_PERCENT(0.05f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos, VALUE_FROM_PERCENT(0.1f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.02f, percent) + x_pos, VALUE_FROM_PERCENT(0.15f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.02f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
    }
    glEnd();

   

   

    //T chi top side
    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f(VALUE_FROM_PERCENT(-0.09f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.09f, percent) + x_pos, VALUE_FROM_PERCENT(0.33f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.015f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.015f, percent) + x_pos, VALUE_FROM_PERCENT(0.33f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.09f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.09f, percent) + x_pos, VALUE_FROM_PERCENT(0.33f, percent) + y_pos, 0.0f);

       

    }
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    {
       
        glVertex3f(VALUE_FROM_PERCENT(0.09f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.07f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.09f, percent) + x_pos, VALUE_FROM_PERCENT(0.27f, percent) + y_pos, 0.0f);

       

    }
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    {
       
        glVertex3f(VALUE_FROM_PERCENT(-0.09f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.07f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.09f, percent) + x_pos, VALUE_FROM_PERCENT(0.27f, percent) + y_pos, 0.0f);

       

    }
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    {
       
        glVertex3f(VALUE_FROM_PERCENT(-0.035f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.0f, percent) + x_pos, VALUE_FROM_PERCENT(-0.015f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.035f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);

       

    }
    glEnd();

}