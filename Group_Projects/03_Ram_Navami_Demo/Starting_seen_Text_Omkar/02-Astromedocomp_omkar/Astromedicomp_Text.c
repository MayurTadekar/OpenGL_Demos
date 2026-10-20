#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

//OPENGL RELETED HEADER FILE
#include<gl/GL.h>
#include "OGL.h"
#include<gl/GLU.h>
#include<math.h>
#include "Astromedicomp_Text.h"

#define VALUE_FROM_PERCENT(complete, percent) (complete * percent/100.0f)

//global variable
 //variable declaration
 struct ouj_Curve 
 {
    float ouj_x1, ouj_x2, ouj_x3, ouj_x4;
    float ouj_y1, ouj_y2, ouj_y3, ouj_y4;

    
 };

float Cat1[100] , Cat2[100];
float Cbt1[100] , Cbt2[100];
float Cct1[100] , Cct2[100];
float Cdt1[100] , Cdt2[100];
float Cet1[100] , Cet2[100];
float Cft1[100] , Cft2[100];
float Cgt1[100] , Cgt2[100];
float Cht1[100] , Cht2[100];
float Cit1[100] , Cit2[100];
float Cjt1[100] , Cjt2[100];
float Ckt1[100] , Ckt2[100];
float Clt1[100] , Clt2[100];
float Cmt1[100] , Cmt2[100];
float Cnt1[100] , Cnt2[100];
float Cot1[100] , Cot2[100];
float Cpt1[100] , Cpt2[100];
float Cqt1[100] , Cqt2[100];
float Crt1[100] , Crt2[100];
float Cst1[100] , Cst2[100];
float Ctt1[100] , Ctt2[100];


void Astromedicomp_Text(void)
{
     //set matrix to model view mode
     glMatrixMode(GL_MODELVIEW);
    
   
     //SET TO IDENTITY MATRIX
     glLoadIdentity();
 
     //translet triangle back word by Z
     glTranslatef(0.0f, 0.0f, -3.0f);
 
     Astro_A(-1.63f,-0.17f,120);
     Astro_S(-1.35f, 0.01f, 60);
     Astro_T(-1.1f, -0.17f, 120);
     Astro_R(-0.9f, 0.02f, 60);
     Astro_O(-0.59f, -0.195f, 127);
     Astro_M(-0.26f, -0.16f, 115);
     Astro_E(-0.05f, -0.16f, 115);
     Astro_D(0.296f, -0.16f, 115);
     Astro_I(0.46f, -0.15f, 115);
     Astro_C(1.072f, -0.16f, 115);
     Astro_OO(1.25f, -0.17f, 120);
     Astro_MM(1.56f, -0.16f, 110);
     Astro_P(1.79f, 0.03f, 60);
}

void Astro_A(float x_pos, float y_pos, float percent)
{
         //***************************************************A*****************************************
    glBegin(GL_TRIANGLE_STRIP);
    {
        glColor4f(1.0f, 0.4f, 0.0f, 1.0f);

        glVertex3f(VALUE_FROM_PERCENT(-0.096f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.075f,percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.080f,percent) + x_pos, VALUE_FROM_PERCENT(0.05f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.05f, percent) + x_pos, VALUE_FROM_PERCENT(0.1f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.056f, percent) + x_pos, VALUE_FROM_PERCENT(0.15f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.025f,percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.016f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.33f, percent) + y_pos, 0.0f);
       



        glVertex3f(VALUE_FROM_PERCENT(0.12f, percent) + x_pos, VALUE_FROM_PERCENT( 0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.075f, percent) + x_pos, VALUE_FROM_PERCENT( 0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.092f, percent) + x_pos, VALUE_FROM_PERCENT( 0.05f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.05f, percent) + x_pos, VALUE_FROM_PERCENT( 0.1f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.068f, percent) + x_pos, VALUE_FROM_PERCENT( 0.15f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.026f, percent) + x_pos, VALUE_FROM_PERCENT( 0.2f,  percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.026f, percent) + x_pos, VALUE_FROM_PERCENT( 0.3f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f,  percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT( 0.33f,  percent) + y_pos,0.0f);


            
       
        glVertex3f(VALUE_FROM_PERCENT(-0.05f,percent) + x_pos, VALUE_FROM_PERCENT( 0.1f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.042f,percent) + x_pos, VALUE_FROM_PERCENT( 0.13f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.025f,percent) + x_pos, VALUE_FROM_PERCENT( 0.1f,  percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f,percent) + x_pos, VALUE_FROM_PERCENT( 0.13f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.025f,percent) + x_pos, VALUE_FROM_PERCENT( 0.1f,  percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.042f,percent) + x_pos, VALUE_FROM_PERCENT( 0.13f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.05f,percent) + x_pos, VALUE_FROM_PERCENT( 0.1f,  percent) + y_pos,0.0f);

    }
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f(VALUE_FROM_PERCENT(-0.116f,percent) + x_pos, VALUE_FROM_PERCENT( 0.0f,percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.08f,percent) + x_pos, VALUE_FROM_PERCENT( -0.01f,percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.08f,percent) + x_pos, VALUE_FROM_PERCENT( 0.0f, percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.06f,percent) + x_pos, VALUE_FROM_PERCENT( 0.0f, percent) + y_pos,0.0f);

    }
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    {

        glVertex3f(VALUE_FROM_PERCENT(0.06f,percent) + x_pos, VALUE_FROM_PERCENT( 0.0f, percent) + y_pos,0.0f);

       glVertex3f(VALUE_FROM_PERCENT(0.1f, percent) + x_pos, VALUE_FROM_PERCENT(-0.015f,percent) + y_pos, 0.0f);

        glVertex3f(VALUE_FROM_PERCENT(0.1f,percent) + x_pos, VALUE_FROM_PERCENT( 0.0f, percent) + y_pos,0.0f);

        glVertex3f(VALUE_FROM_PERCENT(0.14f,percent) + x_pos, VALUE_FROM_PERCENT( 0.0f,percent) + y_pos, 0.0f);
        
    }
    glEnd();
    
}


void Astro_S(float x_pos, float y_pos, float percent)
{


    float t = 0.0f;
    int i = 0;

    struct ouj_Curve ouj_curve1;
    struct ouj_Curve ouj_curve2;

    //co-ordinate x,y
    ouj_curve1.ouj_x1 = 0.08f;
    ouj_curve1.ouj_x2 = -0.32f;
    ouj_curve1.ouj_x3 = -0.29f;
    ouj_curve1.ouj_x4 = 0.0f;

    ouj_curve1.ouj_y1 = 0.35f;
    ouj_curve1.ouj_y2 = 0.3f;
    ouj_curve1.ouj_y3 = 0.08f;
    ouj_curve1.ouj_y4 = 0.0f;

    ouj_curve2.ouj_x1 = 0.05f;
    ouj_curve2.ouj_x2 = -0.24f;
    ouj_curve2.ouj_x3 = -0.22f;
    ouj_curve2.ouj_x4 = 0.0f;

    ouj_curve2.ouj_y1 = 0.3f;
    ouj_curve2.ouj_y2 = 0.3f;
    ouj_curve2.ouj_y3 = 0.08f;
    ouj_curve2.ouj_y4 = 0.05f;


    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        Cat1[i] = (((pow(1 - t, 3)) *  ouj_curve1.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve1.ouj_x2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve1.ouj_x3)) + ((pow(t, 3)) *  ouj_curve1.ouj_x4));
        Cbt1[i] = (((pow(1 - t, 3)) *  ouj_curve1.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve1.ouj_y2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve1.ouj_y3)) + ((pow(t, 3)) *  ouj_curve1.ouj_y4));
    }

    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        Cat2[i] = (((pow(1 - t, 3)) *  ouj_curve2.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve2.ouj_x2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve2.ouj_x3)) + ((pow(t, 3)) *  ouj_curve2.ouj_x4));
        Cbt2[i] = (((pow(1 - t, 3)) *  ouj_curve2.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve2.ouj_y2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve2.ouj_y3)) + ((pow(t, 3)) *  ouj_curve2.ouj_y4));
    }



    glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLE_STRIP);
    {
        for (i = 0; i < 100; i++)
        {
            glVertex3f(VALUE_FROM_PERCENT(Cat1[i], percent) + x_pos, VALUE_FROM_PERCENT(Cbt1[i], percent) + y_pos, 0.0f);
            glVertex3f(VALUE_FROM_PERCENT(Cat2[i], percent) + x_pos, VALUE_FROM_PERCENT(Cbt2[i], percent) + y_pos, 0.0f);

        }
    }
    glEnd();

    struct ouj_Curve ouj_curve3;
    struct ouj_Curve ouj_curve4;
 
    //Co-ordinate x,y 
    ouj_curve3.ouj_x1 = -0.01f;
    ouj_curve3.ouj_x2 = 0.32f;
    ouj_curve3.ouj_x3 = 0.29f;
    ouj_curve3.ouj_x4 = -0.07f;


    ouj_curve3.ouj_y1 = 0.05f;
    ouj_curve3.ouj_y2 = -0.03f;
    ouj_curve3.ouj_y3 = -0.3f;
    ouj_curve3.ouj_y4 = -0.35f;

    ouj_curve4.ouj_x1 = -0.01f;
    ouj_curve4.ouj_x2 = 0.24f;
    ouj_curve4.ouj_x3 = 0.22f;
    ouj_curve4.ouj_x4 = -0.05f;

    ouj_curve4.ouj_y1 = -0.0f;
    ouj_curve4.ouj_y2 = -0.08f;
    ouj_curve4.ouj_y3 = -0.3f;
    ouj_curve4.ouj_y4= -0.3f;

    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        Cct1[i] = (((pow(1 - t, 3)) *  ouj_curve3.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve3.ouj_x2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve3.ouj_x3)) + ((pow(t, 3)) *  ouj_curve3.ouj_x4));
        Cdt1[i] = (((pow(1 - t, 3)) *  ouj_curve3.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve3.ouj_y2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve3.ouj_y3)) + ((pow(t, 3)) *  ouj_curve3.ouj_y4));
    }

    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        Cct2[i] = (((pow(1 - t, 3)) * ouj_curve4.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve4.ouj_x2)) + ((3 * (pow(t, 2) * (1 - t)) * ouj_curve4.ouj_x3)) + ((pow(t, 3)) * ouj_curve4.ouj_x4));
        Cdt2[i] = (((pow(1 - t, 3)) * ouj_curve4.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve4.ouj_y2)) + ((3 * (pow(t, 2) * (1 - t)) * ouj_curve4.ouj_y3)) + ((pow(t, 3)) * ouj_curve4.ouj_y4));
    }


    glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLE_STRIP);
    {
        for (i = 0; i < 100; i++)
        {
            glVertex3f(VALUE_FROM_PERCENT(Cct1[i], percent) + x_pos, VALUE_FROM_PERCENT(Cdt1[i], percent) + y_pos, 0.0f);
            glVertex3f(VALUE_FROM_PERCENT(Cct2[i], percent) + x_pos, VALUE_FROM_PERCENT(Cdt2[i], percent) + y_pos, 0.0f);
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
    
void Astro_T(float x_pos, float y_pos, float percent)
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
   
void Astro_R(float x_pos, float y_pos, float percent)
{
   

    float t = 0.0f;
    int i = 0;
    
    struct ouj_Curve ouj_curve5;

    struct ouj_Curve ouj_curve6;

    //co-ordinate x,y
    ouj_curve5.ouj_x1 = 0.0f;
    ouj_curve5.ouj_y1 = 0.35f;
    ouj_curve5.ouj_x2 = 0.5f;
    ouj_curve5.ouj_y2 = 0.32f;
    ouj_curve5.ouj_x3 = 0.04f;
    ouj_curve5.ouj_y3 = 0.01f;
    ouj_curve5.ouj_x4 = 0.0f;
    ouj_curve5.ouj_y4 = 0.0f;

    ouj_curve6.ouj_x1 = 0.0f;
    ouj_curve6.ouj_y1 = 0.3f;
    ouj_curve6.ouj_x2 = 0.25f;
    ouj_curve6.ouj_y2 = 0.32f;
    ouj_curve6.ouj_x3 = 0.02f;
    ouj_curve6.ouj_y3 = 0.03f;
    ouj_curve6.ouj_x4 = 0.0f;
    ouj_curve6.ouj_y4 = 0.05f;

    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        Cet1[i] = (((pow(1 - t, 3)) * ouj_curve5.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve5.ouj_x2)) + ((3 * (pow(t, 2) * (1-t)) * ouj_curve5.ouj_x3)) + ((pow(t, 3)) * ouj_curve5.ouj_x4));
        Cft1[i] = (((pow(1 - t, 3)) * ouj_curve5.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve5.ouj_y2)) + ((3 * (pow(t, 2) * (1-t)) * ouj_curve5.ouj_y3)) + ((pow(t, 3)) * ouj_curve5.ouj_y4));
    }

    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
         Cet2[i] = (((pow(1 - t, 3)) * ouj_curve6.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve6.ouj_x2)) + ((3 * (pow(t, 2) * (1-t)) * ouj_curve6.ouj_x3)) + ((pow(t, 3)) * ouj_curve6.ouj_x4));
         Cft2[i] = (((pow(1 - t, 3)) * ouj_curve6.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve6.ouj_y2)) + ((3 * (pow(t, 2) * (1-t)) * ouj_curve6.ouj_y3)) + ((pow(t, 3)) * ouj_curve6.ouj_y4));
     }

     glColor4f(1.0f, 0.4f, 0.0f, 1.0);
    glBegin(GL_TRIANGLE_STRIP);
    {
        for (i = 0; i < 100; i++)
        {
            glVertex3f(VALUE_FROM_PERCENT(Cet1[i], percent) + x_pos, VALUE_FROM_PERCENT(Cft1[i], percent) + y_pos, 0.0f);
            glVertex3f(VALUE_FROM_PERCENT(Cet2[i], percent) + x_pos, VALUE_FROM_PERCENT(Cft2[i], percent) + y_pos, 0.0f);
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
        //glVerteouj_x3f(VALUE_FROM_PERCENT(0.5f, percent) + x_pos, VALUE_FROM_PERCENT(-0.5f, percent) + y_pos, 0.0f);
       
            



    }
    glEnd();
}

void Astro_O(float x_pos, float y_pos, float percent)
{


    float t = 0.0f;
    int i = 0;

    struct ouj_Curve ouj_curve7;
    struct ouj_Curve ouj_curve8;
   
    
    //co-ordinate x,y
    ouj_curve7.ouj_x1 = 0.0f;
    ouj_curve7.ouj_x2 = -0.15f;
    ouj_curve7.ouj_x3 = -0.15f;
    ouj_curve7.ouj_x4 = 0.02f;

    ouj_curve7.ouj_y1 = 0.34f;
    ouj_curve7.ouj_y2 = 0.32f;
    ouj_curve7.ouj_y3 = 0.03f;
    ouj_curve7.ouj_y4= 0.0f;

    ouj_curve8.ouj_x1 = 0.0f;
    ouj_curve8.ouj_x2 = -0.1f;
    ouj_curve8.ouj_x3 = -0.1f;
    ouj_curve8.ouj_x4 = 0.02f;

    ouj_curve8.ouj_y1 = 0.3f;
    ouj_curve8.ouj_y2 = 0.32f;
    ouj_curve8.ouj_y3 = 0.05f;
    ouj_curve8.ouj_y4 = 0.03f;


    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        Cgt1[i] = (((pow(1 - t, 3)) * ouj_curve7.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve7.ouj_x2)) + ((3 * (pow(t, 2) * (1 - t)) * ouj_curve7.ouj_x3)) + ((pow(t, 3)) * ouj_curve7.ouj_x4));
        Cht1[i] = (((pow(1 - t, 3)) * ouj_curve7.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve7.ouj_y2)) + ((3 * (pow(t, 2) * (1 - t)) * ouj_curve7.ouj_y3)) + ((pow(t, 3)) * ouj_curve7.ouj_y4));
    }

    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        Cgt2[i] = (((pow(1 - t, 3)) * ouj_curve8.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve8.ouj_x2)) + ((3 * (pow(t, 2) * (1 - t)) * ouj_curve8.ouj_x3)) + ((pow(t, 3)) * ouj_curve8.ouj_x4));
        Cht2[i] = (((pow(1 - t, 3)) * ouj_curve8.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve8.ouj_y2)) + ((3 * (pow(t, 2) * (1 - t)) * ouj_curve8.ouj_y3)) + ((pow(t, 3)) * ouj_curve8.ouj_y4));
    }



    glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLE_STRIP);
    {
        for (i = 0; i < 100; i++)
        {
            glVertex3f(VALUE_FROM_PERCENT(Cgt1[i], percent) + x_pos, VALUE_FROM_PERCENT(Cht1[i], percent) + y_pos, 0.0f);
            glVertex3f(VALUE_FROM_PERCENT(Cgt2[i], percent) + x_pos, VALUE_FROM_PERCENT(Cht2[i], percent) + y_pos, 0.0f);

        }
    }
    glEnd();

    struct ouj_Curve ouj_curve9;
    struct ouj_Curve ouj_curve10;

    //Co-ordinate x,y 
    ouj_curve9.ouj_x1 = 0.0f;
    ouj_curve9.ouj_x2 = 0.15f;
    ouj_curve9.ouj_x3 = 0.15f;
    ouj_curve9.ouj_x4 = 0.0f;

    ouj_curve9.ouj_y1 = 0.34f;
    ouj_curve9.ouj_y2 = 0.3f;
    ouj_curve9.ouj_y3 = 0.03f;
    ouj_curve9.ouj_y4 = 0.0f;

    ouj_curve10.ouj_x1 = 0.0f;
    ouj_curve10.ouj_x2 = 0.1f;
    ouj_curve10.ouj_x3 = 0.1f;
    ouj_curve10.ouj_x4 = 0.0f;

    ouj_curve10.ouj_y1 = 0.3f;
    ouj_curve10.ouj_y2 = 0.3f;
    ouj_curve10.ouj_y3 = 0.05f;
    ouj_curve10.ouj_y4 = 0.03f;

    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        Cit1[i] = (((pow(1 - t, 3)) *  ouj_curve9.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve9.ouj_x2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve9.ouj_x3)) + ((pow(t, 3)) *  ouj_curve9.ouj_x4));
        Cjt1[i] = (((pow(1 - t, 3)) *  ouj_curve9.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve9.ouj_y2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve9.ouj_y3)) + ((pow(t, 3)) *  ouj_curve9.ouj_y4));
    }

    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        Cit2[i] = (((pow(1 - t, 3)) *  ouj_curve10.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve10.ouj_x2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve10.ouj_x3)) + ((pow(t, 3)) *  ouj_curve10.ouj_x4));
        Cjt2[i] = (((pow(1 - t, 3)) *  ouj_curve10.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve10.ouj_y2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve10.ouj_y3)) + ((pow(t, 3)) *  ouj_curve10.ouj_y4));
    }


    glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLE_STRIP);
    {
        for (i = 0; i < 100; i++)
        {
            glVertex3f(VALUE_FROM_PERCENT(Cit1[i], percent) + x_pos, VALUE_FROM_PERCENT(Cjt1[i], percent) + y_pos, 0.0f);
            glVertex3f(VALUE_FROM_PERCENT(Cit2[i], percent) + x_pos, VALUE_FROM_PERCENT(Cjt2[i], percent) + y_pos, 0.0f);
        }
    }
    glEnd();
}
void Astro_M(float x_pos, float y_pos, float percent)

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
        glVertex3f(VALUE_FROM_PERCENT(-0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.29f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.03f, percent) + x_pos, VALUE_FROM_PERCENT(0.29f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.03f, percent) + x_pos, VALUE_FROM_PERCENT(0.24f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.24f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);
        
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
    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f(VALUE_FROM_PERCENT(0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.29f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.03f, percent) + x_pos, VALUE_FROM_PERCENT(0.29f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.03f, percent) + x_pos, VALUE_FROM_PERCENT(0.24f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.24f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);
        
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
        glVertex3f(VALUE_FROM_PERCENT(0.14f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.1f, percent) + x_pos, VALUE_FROM_PERCENT(-0.015f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.1f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.06f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
      
    }
     
    glEnd();
   
}
void Astro_E(float x_pos, float y_pos, float percent)
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
        //glVerteouj_x3f(VALUE_FROM_PERCENT(0.31f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
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
        //glVerteouj_x3f(VALUE_FROM_PERCENT(0.31f, percent) + x_pos, VALUE_FROM_PERCENT(0.05f, percent) + y_pos, 0.0f);


    }
    glEnd();
}
void Astro_D(float x_pos, float y_pos, float percent)
{
   

    float t = 0.0f;
    int i = 0;

    struct ouj_Curve ouj_curve11;
    struct ouj_Curve ouj_curve12;

    //co-ordinate x,y
    //co-ordinate x,y
    ouj_curve11.ouj_x1 = 0.0f;
    ouj_curve11.ouj_x2 = 0.25f;
    ouj_curve11.ouj_x3 = 0.20f;
    ouj_curve11.ouj_x4 =- 0.01f;


    ouj_curve11.ouj_y1 = 0.35f;
    ouj_curve11.ouj_y2 = 0.3f;
    ouj_curve11.ouj_y3 = 0.08f;
    ouj_curve11.ouj_y4 = 0.0f;

    ouj_curve12.ouj_x1 = 0.0f;
    ouj_curve12.ouj_x2 = 0.19f;
    ouj_curve12.ouj_x3 = 0.17f;
    ouj_curve12.ouj_x4 = -0.01f;

    ouj_curve12.ouj_y1 = 0.3f;
    ouj_curve12.ouj_y2 = 0.3f;
    ouj_curve12.ouj_y3 = 0.08f;
    ouj_curve12.ouj_y4 = 0.04f;


    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        
        Ckt1[i] = (((pow(1 - t, 3)) *  ouj_curve11.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve11.ouj_x2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve11.ouj_x3)) + ((pow(t, 3)) *  ouj_curve11.ouj_x4));
        Clt1[i] = (((pow(1 - t, 3)) *  ouj_curve11.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve11.ouj_y2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve11.ouj_y3)) + ((pow(t, 3)) *  ouj_curve11.ouj_y4));
    }

    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        Ckt2[i] = (((pow(1 - t, 3)) *  ouj_curve12.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve12.ouj_x2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve12.ouj_x3)) + ((pow(t, 3)) *  ouj_curve12.ouj_x4));
        Clt2[i] = (((pow(1 - t, 3)) *  ouj_curve12.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve12.ouj_y2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve12.ouj_y3)) + ((pow(t, 3)) *  ouj_curve12.ouj_y4));
    }

    glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLE_STRIP);
    {
        for (i = 0; i < 100; i++)
        {
            glVertex3f(VALUE_FROM_PERCENT(Ckt1[i], percent) + x_pos, VALUE_FROM_PERCENT(Clt1[i], percent) + y_pos, 0.0f);
            glVertex3f(VALUE_FROM_PERCENT(Ckt2[i], percent) + x_pos, VALUE_FROM_PERCENT(Clt2[i], percent) + y_pos, 0.0f);
        }
    }
    glEnd();


    // ubhi line
    glBegin(GL_TRIANGLE_STRIP);
    {
        glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
        //Verteouj_x3f( VALUE_FROM_PERCENT(-0.055f,percent)+ x_pos, VALUE_FROM_PERCENT( -0.35f,percent)+ y_pos, 0.0f);
       //glVerteouj_x3f(VALUE_FROM_PERCENT(0.0f,percent) + x_pos, VALUE_FROM_PERCENT(-0.35f,percent)+ y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.03f,percent)+ x_pos ,VALUE_FROM_PERCENT(0.0f,percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f,percent)+ x_pos, VALUE_FROM_PERCENT( 0.0f,percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.03f,percent)+x_pos , VALUE_FROM_PERCENT( 0.35f,percent)+ y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f,percent)+x_pos,   VALUE_FROM_PERCENT(0.35f,percent)+ y_pos, 0.0f);

      
        
    }
    glEnd();

    //top head
    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f(VALUE_FROM_PERCENT(-0.03f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.06f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.03f, percent) + x_pos, VALUE_FROM_PERCENT(0.33f, percent) + y_pos, 0.0f);




    }
    glEnd();

    //top head
    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f(VALUE_FROM_PERCENT(-0.03f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.06f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.03f, percent) + x_pos, VALUE_FROM_PERCENT(0.02f, percent) + y_pos, 0.0f);




    }
    glEnd();
}
void Astro_I(float x_pos, float y_pos, float percent)


{


    glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
    //***************************************************I*****************************************
    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f(VALUE_FROM_PERCENT(0.15f, percent) + x_pos, VALUE_FROM_PERCENT(0.032f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.19f, percent) + x_pos, VALUE_FROM_PERCENT(0.032f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.15f, percent) + x_pos, VALUE_FROM_PERCENT(0.1f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.19f, percent) + x_pos, VALUE_FROM_PERCENT(0.15f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.15f, percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.19f, percent) + x_pos, VALUE_FROM_PERCENT(0.25f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.15f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.19f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
    }
    glEnd();

    //E chi varachi side
    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f(VALUE_FROM_PERCENT(0.06f, percent) + x_pos, VALUE_FROM_PERCENT(0.33f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.06f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.1f, percent) + x_pos, VALUE_FROM_PERCENT(0.33f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.15f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.25f, percent) + x_pos, VALUE_FROM_PERCENT(0.33f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(0.33f, percent) + y_pos, 0.0f);
        //glVerteouj_x3f(VALUE_FROM_PERCENT(0.31f, percent) + x_pos, VALUE_FROM_PERCENT(0.33f, percent) + y_pos, 0.0f);
    }
    glEnd();

   

    //E chi Khalachi  side
    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f(VALUE_FROM_PERCENT(0.06f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.06f, percent) + x_pos, VALUE_FROM_PERCENT(0.03f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.1f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.15f, percent) + x_pos, VALUE_FROM_PERCENT(0.03f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.25f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(0.03f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);


    }
    glEnd();

     //T chi Corner side
     glBegin(GL_TRIANGLE_STRIP);
     {
         glVertex3f(VALUE_FROM_PERCENT(0.06f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
         glVertex3f(VALUE_FROM_PERCENT(0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
         glVertex3f(VALUE_FROM_PERCENT(0.06f, percent) + x_pos, VALUE_FROM_PERCENT(0.27f, percent) + y_pos, 0.0f);
     }
     glEnd();

      //T chi Corner side
      glBegin(GL_TRIANGLE_STRIP);
      {
          glVertex3f(VALUE_FROM_PERCENT(0.06f, percent) + x_pos, VALUE_FROM_PERCENT(0.03f, percent) + y_pos, 0.0f);
          glVertex3f(VALUE_FROM_PERCENT(0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.03f, percent) + y_pos, 0.0f);
          glVertex3f(VALUE_FROM_PERCENT(0.06f, percent) + x_pos, VALUE_FROM_PERCENT(0.05f, percent) + y_pos, 0.0f);
 
         
      glEnd();

       //T chi Corner side
     glBegin(GL_TRIANGLE_STRIP);
     {
         glVertex3f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
         glVertex3f(VALUE_FROM_PERCENT(0.28f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
         glVertex3f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(0.27f, percent) + y_pos, 0.0f);

        
     }
     glEnd();

      

       //T chi Corner side
     glBegin(GL_TRIANGLE_STRIP);
     {
         glVertex3f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(0.03f, percent) + y_pos, 0.0f);
         glVertex3f(VALUE_FROM_PERCENT(0.28f, percent) + x_pos, VALUE_FROM_PERCENT(0.03f, percent) + y_pos, 0.0f);
         glVertex3f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(0.05f, percent) + y_pos, 0.0f);
     }
     glEnd();

    }  
}
void Astro_C(float x_pos, float y_pos, float percent)
{
   

    float t = 0.0f;
    int i = 0;

    struct ouj_Curve ouj_curve13;
    struct ouj_Curve ouj_curve14;
    
    //co-ordinate x,y
    ouj_curve13.ouj_x1 = 0.0f;
    ouj_curve13.ouj_x2 = -0.3f;
    ouj_curve13.ouj_x3 = -0.27f;
    ouj_curve13.ouj_x4 = 0.0f;

   
    ouj_curve13.ouj_y1 = 0.35f;
    ouj_curve13.ouj_y2 = 0.3f;
    ouj_curve13.ouj_y3 = 0.08f;
    ouj_curve13.ouj_y4 = 0.0f;

    ouj_curve14.ouj_x1 = 0.0f;
    ouj_curve14.ouj_x2 = -0.22f;
    ouj_curve14.ouj_x3 = -0.20f;
    ouj_curve14.ouj_x4 = 0.0f;

    ouj_curve14.ouj_y1 = 0.3f;
    ouj_curve14.ouj_y2 = 0.3f;
    ouj_curve14.ouj_y3 = 0.08f;
    ouj_curve14.ouj_y4 = 0.05f;


    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        Cmt1[i] = (((pow(1 - t, 3)) *  ouj_curve13.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve13.ouj_x2)) + ((3 * (pow(t, 2) *(1-t)) *  ouj_curve13.ouj_x3)) + ((pow(t, 3)) *  ouj_curve13.ouj_x4));
        Cnt1[i] = (((pow(1 - t, 3)) *  ouj_curve13.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve13.ouj_y2)) + ((3 * (pow(t, 2)*(1-t)) *  ouj_curve13.ouj_y3)) + ((pow(t, 3)) *  ouj_curve13.ouj_y4));
    }

    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
         Cmt2[i] = (((pow(1 - t, 3)) *  ouj_curve14.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve14.ouj_x2)) + ((3 * (pow(t, 2) *(1-t)) *  ouj_curve14.ouj_x3)) + ((pow(t, 3)) *  ouj_curve14.ouj_x4));
         Cnt2[i] = (((pow(1 - t, 3)) *  ouj_curve14.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve14.ouj_y2)) + ((3 * (pow(t, 2) *(1-t)) *  ouj_curve14.ouj_y3)) + ((pow(t, 3)) *  ouj_curve14.ouj_y4));
     }

     glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLE_STRIP);
    {
        for (i = 0; i < 100; i++)
        {
            glVertex3f(VALUE_FROM_PERCENT(Cmt1[i], percent) + x_pos, VALUE_FROM_PERCENT(Cnt1[i], percent) + y_pos, 0.0f);
            glVertex3f(VALUE_FROM_PERCENT(Cmt2[i], percent) + x_pos, VALUE_FROM_PERCENT(Cnt2[i], percent) + y_pos, 0.0f);
        }
    }
    glEnd();

    

}
void Astro_OO(float x_pos, float y_pos, float percent)
{


    float t = 0.0f;
    int i = 0;

    struct ouj_Curve ouj_curve15;
    struct ouj_Curve ouj_curve16;
   
    //co-ordinate x,y
    ouj_curve15.ouj_x1 = 0.0f;
    ouj_curve15.ouj_x2 = -0.15f;
    ouj_curve15.ouj_x3 = -0.15f;
    ouj_curve15.ouj_x4 = 0.02f;

    ouj_curve15.ouj_y1 = 0.34f;
    ouj_curve15.ouj_y2 = 0.32f;
    ouj_curve15.ouj_y3 = 0.03f;
    ouj_curve15.ouj_y4 = 0.0f;

    ouj_curve16.ouj_x1 = 0.0f;
    ouj_curve16.ouj_x2 = -0.1f;
    ouj_curve16.ouj_x3 = -0.1f;
    ouj_curve16.ouj_x4 = 0.02f;

    ouj_curve16.ouj_y1 = 0.3f;
    ouj_curve16.ouj_y2 = 0.32f;
    ouj_curve16.ouj_y3 = 0.05f;
    ouj_curve16.ouj_y4 = 0.03f;

  


    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        Cot1[i] = (((pow(1 - t, 3)) * ouj_curve15.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve15.ouj_x2)) + ((3 * (pow(t, 2) * (1 - t)) * ouj_curve15.ouj_x3)) + ((pow(t, 3)) * ouj_curve15.ouj_x4));
        Cpt1[i] = (((pow(1 - t, 3)) * ouj_curve15.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve15.ouj_y2)) + ((3 * (pow(t, 2) * (1 - t)) * ouj_curve15.ouj_y3)) + ((pow(t, 3)) * ouj_curve15.ouj_y4));
    }

    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        Cot2[i] = (((pow(1 - t, 3)) * ouj_curve16.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve16.ouj_x2)) + ((3 * (pow(t, 2) * (1 - t)) * ouj_curve16.ouj_x3)) + ((pow(t, 3)) * ouj_curve16.ouj_x4));
        Cpt2[i] = (((pow(1 - t, 3)) * ouj_curve16.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve16.ouj_y2)) + ((3 * (pow(t, 2) * (1 - t)) * ouj_curve16.ouj_y3)) + ((pow(t, 3)) * ouj_curve16.ouj_y4));
    }



    glColor4f(1.0f, 0.4f, 0.0f,1.0f);
    glBegin(GL_TRIANGLE_STRIP);
    {
        for (i = 0; i < 100; i++)
        {
            glVertex3f(VALUE_FROM_PERCENT(Cot1[i], percent) + x_pos, VALUE_FROM_PERCENT(Cpt1[i], percent) + y_pos, 0.0f);
            glVertex3f(VALUE_FROM_PERCENT(Cot2[i], percent) + x_pos, VALUE_FROM_PERCENT(Cpt2[i], percent) + y_pos, 0.0f);

        }
    }
    glEnd();

    struct ouj_Curve ouj_curve17;
    struct ouj_Curve ouj_curve18;

 //Co-ordinate x,y 
 ouj_curve17.ouj_x1 = 0.0f;
 ouj_curve17.ouj_x2 = 0.15f;
 ouj_curve17.ouj_x3 = 0.15f;
 ouj_curve17.ouj_x4 = 0.0f;

 ouj_curve17.ouj_y1 = 0.34f;
 ouj_curve17.ouj_y2 = 0.3f;
 ouj_curve17.ouj_y3 = 0.03f;
 ouj_curve17.ouj_y4 = 0.0f;

 ouj_curve18.ouj_x1 = 0.0f;
 ouj_curve18.ouj_x2 = 0.1f;
 ouj_curve18.ouj_x3 = 0.1f;
 ouj_curve18.ouj_x4 = 0.0f;

 ouj_curve18.ouj_y1 = 0.3f;
 ouj_curve18.ouj_y2 = 0.3f;
 ouj_curve18.ouj_y3 = 0.05f;
 ouj_curve18.ouj_y4 = 0.03f;

   
    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        Cqt1[i] = (((pow(1 - t, 3)) *  ouj_curve17.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve17.ouj_x2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve17.ouj_x3)) + ((pow(t, 3)) *  ouj_curve17.ouj_x4));
        Crt1[i] = (((pow(1 - t, 3)) *  ouj_curve17.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve17.ouj_y2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve17.ouj_y3)) + ((pow(t, 3)) *  ouj_curve17.ouj_y4));
    }

    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        Cqt2[i] = (((pow(1 - t, 3)) *  ouj_curve18.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve18.ouj_x2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve18.ouj_x3)) + ((pow(t, 3)) *  ouj_curve18.ouj_x4));
        Crt2[i] = (((pow(1 - t, 3)) *  ouj_curve18.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve18.ouj_y2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve18.ouj_y3)) + ((pow(t, 3)) *  ouj_curve18.ouj_y4));
    }


    glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLE_STRIP);
    {
        for (i = 0; i < 100; i++)
        {
            glVertex3f(VALUE_FROM_PERCENT(Cqt1[i], percent) + x_pos, VALUE_FROM_PERCENT(Crt1[i], percent) + y_pos, 0.0f);
            glVertex3f(VALUE_FROM_PERCENT(Cqt2[i], percent) + x_pos, VALUE_FROM_PERCENT(Crt2[i], percent) + y_pos, 0.0f);
        }
    }
    glEnd();

}
void Astro_MM(float x_pos, float y_pos, float percent)
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
         glVertex3f(VALUE_FROM_PERCENT(-0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.29f, percent) + y_pos, 0.0f);
         glVertex3f(VALUE_FROM_PERCENT(-0.03f, percent) + x_pos, VALUE_FROM_PERCENT(0.29f, percent) + y_pos, 0.0f);
         glVertex3f(VALUE_FROM_PERCENT(-0.03f, percent) + x_pos, VALUE_FROM_PERCENT(0.24f, percent) + y_pos, 0.0f);
         glVertex3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.24f, percent) + y_pos, 0.0f);
         glVertex3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);
         
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
     glBegin(GL_TRIANGLE_STRIP);
     {
         glVertex3f(VALUE_FROM_PERCENT(0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
         glVertex3f(VALUE_FROM_PERCENT(0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.29f, percent) + y_pos, 0.0f);
         glVertex3f(VALUE_FROM_PERCENT(0.03f, percent) + x_pos, VALUE_FROM_PERCENT(0.29f, percent) + y_pos, 0.0f);
         glVertex3f(VALUE_FROM_PERCENT(0.03f, percent) + x_pos, VALUE_FROM_PERCENT(0.24f, percent) + y_pos, 0.0f);
         glVertex3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.24f, percent) + y_pos, 0.0f);
         glVertex3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);
         
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
         glVertex3f(VALUE_FROM_PERCENT(0.14f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
         glVertex3f(VALUE_FROM_PERCENT(0.1f, percent) + x_pos, VALUE_FROM_PERCENT(-0.015f, percent) + y_pos, 0.0f);
         glVertex3f(VALUE_FROM_PERCENT(0.1f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
         glVertex3f(VALUE_FROM_PERCENT(0.06f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
       
     }
      
     glEnd();

     
}
 void Astro_P(float x_pos, float y_pos, float percent)
{
   

    float t = 0.0f;
    int i = 0;

    struct ouj_Curve ouj_curve19;
    struct ouj_Curve ouj_curve20;
    //co-ordinate x,y
    ouj_curve19.ouj_x1 = 0.0f;
    ouj_curve19.ouj_y1 = 0.35f;
    ouj_curve19.ouj_x2 = 0.5f;
    ouj_curve19.ouj_y2 = 0.25f;
    ouj_curve19.ouj_x3 = 0.04f;
    ouj_curve19.ouj_y3 = 0.01f;
    ouj_curve19.ouj_x4 = 0.0f;
    ouj_curve19.ouj_y4 = 0.0f;

    ouj_curve20.ouj_x1 = 0.0f;
    ouj_curve20.ouj_y1 = 0.3f;
    ouj_curve20.ouj_x2 = 0.25f;
    ouj_curve20.ouj_y2 = 0.25f;
    ouj_curve20.ouj_x3 = 0.02f;
    ouj_curve20.ouj_y3 = 0.03f;
    ouj_curve20.ouj_x4 = 0.0f;
    ouj_curve20.ouj_y4 = 0.05f;

    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        Cst1[i] = (((pow(1 - t, 3)) * ouj_curve19.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve19.ouj_x2)) + ((3 * (pow(t, 2) * (1-t)) * ouj_curve19.ouj_x3)) + ((pow(t, 3)) * ouj_curve19.ouj_x4));
        Ctt1[i] = (((pow(1 - t, 3)) * ouj_curve19.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve19.ouj_y2)) + ((3 * (pow(t, 2) * (1-t)) * ouj_curve19.ouj_y3)) + ((pow(t, 3)) * ouj_curve19.ouj_y4));
      
    }

    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        Cst2[i] = (((pow(1 - t, 3)) * ouj_curve20.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve20.ouj_x2)) + ((3 * (pow(t, 2) * (1-t)) * ouj_curve20.ouj_x3)) + ((pow(t, 3)) * ouj_curve20.ouj_x4));
        Ctt2[i] = (((pow(1 - t, 3)) * ouj_curve20.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve20.ouj_y2)) + ((3 * (pow(t, 2) * (1-t)) * ouj_curve20.ouj_y3)) + ((pow(t, 3)) * ouj_curve20.ouj_y4));
     }

     glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLE_STRIP);
    {
        for (i = 0; i < 100; i++)
        {
            glVertex3f(VALUE_FROM_PERCENT(Cst1[i], percent) + x_pos, VALUE_FROM_PERCENT(Ctt1[i], percent) + y_pos, 0.0f);
            glVertex3f(VALUE_FROM_PERCENT(Cst2[i], percent) + x_pos, VALUE_FROM_PERCENT(Ctt2[i], percent) + y_pos, 0.0f);
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