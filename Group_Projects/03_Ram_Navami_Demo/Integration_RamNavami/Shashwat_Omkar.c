// win32 headers
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

//OPENGL RELETED HEADER FILE
#include<gl/GL.h>
#include "OGL.h"
#include<gl/GLU.h>
#include<math.h>
#include "Shashwat_Omkar.h"

#define VALUE_FROM_PERCENT(complete, percent) (complete * percent/100.0f)


//global variable
 //variable declaration
 struct ouj_Curve 
 {
     float ouj_x1, ouj_x2, ouj_x3, ouj_x4;
     float ouj_y1, ouj_y2, ouj_y3, ouj_y4;
 };

 float ouj_Eat1[100] , ouj_Eat2[100];
 float ouj_Ebt1[100] , ouj_Ebt2[100];
 float ouj_Ect1[100] , ouj_Ect2[100];
 float ouj_Edt1[100] , ouj_Edt2[100];
 float ouj_Eet1[100] , ouj_Eet2[100];
 float ouj_Eft1[100] , ouj_Eft2[100];
 float ouj_Egt1[100] , ouj_Egt2[100];
 float ouj_Eht1[100] , ouj_Eht2[100];
 float ouj_Eit1[100] , ouj_Eit2[100];
 float ouj_Ejt1[100] , ouj_Ejt2[100];


void omkar_Shashwat(void)
{   
     //SET TO IDENTITY MATRIX
     glLoadIdentity();
 
    //translet triangle back word by Z
    glTranslatef(-0.55f, -0.1f, -1.5f);
 
    //sun(-1.0f,0.0f,100);
 
     Shashwat_sha1(0.05f, -0.23f, 90);//1
     Shashwat_sha2(0.0f, 0.0f, 90);//2
     Shashwat_sha1(-0.01f, -0.2f, 50);
     Shashwat_SH(0.09f,-0.15f,60);
     Shashwat_sha3(0.32f, 0.0f, 80);
     Shashwat_sha3(0.43f, 0.0f, 80);
 
     Shashwat_sha1(0.55f, -0.25f, 95);
     Shashwat_sha4(0.49f, 0.02f, 80);
     Shashwat_shwa(0.8f, 0.0f,80);
     Shashwat_sha3(0.89f, 0.0f, 80);
 
     Shashwat_sha5(1.1f, 0.0f, 60);
     Shashwat_sha3(1.2f, 0.0f, 80);
 
     Shashwat_sha6(0.3f, -0.15f, 140);
     Shashwat_sha6(0.8f, -0.15f, 140);
     Shashwat_sha6(1.1f, -0.15f, 140);
     //swap the Buffers
}

void Shashwat_sha1(float x_pos, float y_pos, float percent)
{
    float t = 0.0f;
    int i = 0;

    struct ouj_Curve ouj_curve43;
    struct ouj_Curve ouj_curve44;
   
    
    //co-ordinate x,y
    ouj_curve43.ouj_x1 = 0.0f;
    ouj_curve43.ouj_x2 = -0.15f;
    ouj_curve43.ouj_x3 = -0.15f;
    ouj_curve43.ouj_x4 = 0.02f;

    ouj_curve43.ouj_y1 = 0.6f;
    ouj_curve43.ouj_y2 = 0.57f;
    ouj_curve43.ouj_y3 = 0.46f;
    ouj_curve43.ouj_y4= 0.44f;

    ouj_curve44.ouj_x1 = 0.0f;
    ouj_curve44.ouj_x2 = -0.09f;
    ouj_curve44.ouj_x3 = -0.09f;
    ouj_curve44.ouj_x4 = 0.02f;

    ouj_curve44.ouj_y1 = 0.55f;
    ouj_curve44.ouj_y2 = 0.52f;
    ouj_curve44.ouj_y3 = 0.48f;
    ouj_curve44.ouj_y4 = 0.47f;
  

    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        ouj_Eat1[i] = (((pow(1 - t, 3)) * ouj_curve43.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve43.ouj_x2)) + ((3 * (pow(t, 2) * (1 - t)) * ouj_curve43.ouj_x3)) + ((pow(t, 3)) * ouj_curve43.ouj_x4));
        ouj_Ebt1[i] = (((pow(1 - t, 3)) * ouj_curve43.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve43.ouj_y2)) + ((3 * (pow(t, 2) * (1 - t)) * ouj_curve43.ouj_y3)) + ((pow(t, 3)) * ouj_curve43.ouj_y4));
    }

    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        ouj_Eat2[i] = (((pow(1 - t, 3)) * ouj_curve44.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve44.ouj_x2)) + ((3 * (pow(t, 2) * (1 - t)) * ouj_curve44.ouj_x3)) + ((pow(t, 3)) * ouj_curve44.ouj_x4));
        ouj_Ebt2[i] = (((pow(1 - t, 3)) * ouj_curve44.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve44.ouj_y2)) + ((3 * (pow(t, 2) * (1 - t)) * ouj_curve44.ouj_y3)) + ((pow(t, 3)) * ouj_curve44.ouj_y4));
    }



    glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLE_STRIP);
    {
        for (i = 0; i < 100; i++)
        {
            glVertex3f(VALUE_FROM_PERCENT(ouj_Eat1[i], percent) + x_pos, VALUE_FROM_PERCENT( ouj_Ebt1[i], percent) + y_pos, 0.0f);
            glVertex3f(VALUE_FROM_PERCENT(ouj_Eat2[i], percent) + x_pos, VALUE_FROM_PERCENT( ouj_Ebt2[i], percent) + y_pos, 0.0f);

        }
    }
    glEnd();

    struct ouj_Curve ouj_curve45;
    struct ouj_Curve ouj_curve46;

    //Co-ordinate x,y 
    ouj_curve45.ouj_x1 = 0.0f;
    ouj_curve45.ouj_x2 = 0.15f;
    ouj_curve45.ouj_x3 = 0.15f;
    ouj_curve45.ouj_x4 = 0.0f;

    ouj_curve45.ouj_y1 = 0.6f;
    ouj_curve45.ouj_y2 = 0.57f;
    ouj_curve45.ouj_y3 = 0.46f;
    ouj_curve45.ouj_y4 = 0.44f;

    ouj_curve46.ouj_x1 = 0.0f;
    ouj_curve46.ouj_x2 = 0.09f;
    ouj_curve46.ouj_x3 = 0.09f;
    ouj_curve46.ouj_x4 = 0.0f;

    ouj_curve46.ouj_y1 = 0.55f;
    ouj_curve46.ouj_y2 = 0.52f;
    ouj_curve46.ouj_y3 = 0.48f;
    ouj_curve46.ouj_y4 = 0.47f;

    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        ouj_Ect1[i] = (((pow(1 - t, 3)) *  ouj_curve45.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve45.ouj_x2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve45.ouj_x3)) + ((pow(t, 3)) *  ouj_curve45.ouj_x4));
        ouj_Edt1[i] = (((pow(1 - t, 3)) *  ouj_curve45.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve45.ouj_y2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve45.ouj_y3)) + ((pow(t, 3)) *  ouj_curve45.ouj_y4));
    }

    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        ouj_Ect2[i] = (((pow(1 - t, 3)) *  ouj_curve46.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve46.ouj_x2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve46.ouj_x3)) + ((pow(t, 3)) *  ouj_curve46.ouj_x4));
        ouj_Edt2[i] = (((pow(1 - t, 3)) *  ouj_curve46.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve46.ouj_y2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve46.ouj_y3)) + ((pow(t, 3)) *  ouj_curve46.ouj_y4));
    }


    glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLE_STRIP);
    {
        for (i = 0; i < 100; i++)
        {
            glVertex3f(VALUE_FROM_PERCENT(ouj_Ect1[i], percent) + x_pos, VALUE_FROM_PERCENT(ouj_Edt1[i], percent) + y_pos, 0.0f);
            glVertex3f(VALUE_FROM_PERCENT(ouj_Ect2[i], percent) + x_pos, VALUE_FROM_PERCENT(ouj_Edt2[i], percent) + y_pos, 0.0f);
        }
    }
    glEnd();
}



void Shashwat_sha2(float x_pos, float y_pos, float percent)
{
   

    float t = 0.0f;
    int i = 0;

    struct ouj_Curve ouj_curve47;
    struct ouj_Curve ouj_curve48;
    //co-ordinate x,y
    ouj_curve47.ouj_x1 = 0.09f;
    ouj_curve47.ouj_y1 = 0.33f;
    ouj_curve47.ouj_x2 = 0.3f;
    ouj_curve47.ouj_y2 = 0.25f;
    ouj_curve47.ouj_x3 = 0.036f;
    ouj_curve47.ouj_y3 = 0.01f;
    ouj_curve47.ouj_x4 = 0.0f;
    ouj_curve47.ouj_y4 = 0.02f;

    ouj_curve48.ouj_x1 = 0.06f;
    ouj_curve48.ouj_y1 = 0.31f;
    ouj_curve48.ouj_x2 = 0.2f;
    ouj_curve48.ouj_y2 = 0.25f;
    ouj_curve48.ouj_x3 = 0.02f;
    ouj_curve48.ouj_y3 = 0.03f;
    ouj_curve48.ouj_x4 = 0.03f;
    ouj_curve48.ouj_y4 = 0.05f;

    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        ouj_Eet1[i] = (((pow(1 - t, 3)) * ouj_curve47.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve47.ouj_x2)) + ((3 * (pow(t, 2) * (1-t)) * ouj_curve47.ouj_x3)) + ((pow(t, 3)) * ouj_curve47.ouj_x4));
        ouj_Eft1[i] = (((pow(1 - t, 3)) * ouj_curve47.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve47.ouj_y2)) + ((3 * (pow(t, 2) * (1-t)) * ouj_curve47.ouj_y3)) + ((pow(t, 3)) * ouj_curve47.ouj_y4));
      
    }

    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        ouj_Eet2[i] = (((pow(1 - t, 3)) * ouj_curve48.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve48.ouj_x2)) + ((3 * (pow(t, 2) * (1-t)) * ouj_curve48.ouj_x3)) + ((pow(t, 3)) * ouj_curve48.ouj_x4));
        ouj_Eft2[i] = (((pow(1 - t, 3)) * ouj_curve48.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve48.ouj_y2)) + ((3 * (pow(t, 2) * (1-t)) * ouj_curve48.ouj_y3)) + ((pow(t, 3)) * ouj_curve48.ouj_y4));
     }

     glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLE_STRIP);
    {
        for (i = 0; i < 100; i++)
        {
            glVertex3f(VALUE_FROM_PERCENT(ouj_Eet1[i], percent) + x_pos, VALUE_FROM_PERCENT(ouj_Eft1[i], percent) + y_pos, 0.0f);
            glVertex3f(VALUE_FROM_PERCENT(ouj_Eet2[i], percent) + x_pos, VALUE_FROM_PERCENT(ouj_Eft2[i], percent) + y_pos, 0.0f);
        }
    }
    glEnd();



   

    

}

void Shashwat_SH(float x_pos, float y_pos, float percent)
{
    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f(VALUE_FROM_PERCENT(-0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.1f, percent) + x_pos, VALUE_FROM_PERCENT(0.34f, percent) + y_pos, 0.0f);
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
}

void Shashwat_sha3(float x_pos, float y_pos, float percent)

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


    glBegin(GL_TRIANGLE_STRIP);//left
    {
        glVertex3f(VALUE_FROM_PERCENT(-0.14f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.1f, percent) + x_pos, VALUE_FROM_PERCENT(-0.015f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.1f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.06f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
      
    }
    glEnd();
}

void Shashwat_sha4(float x_pos, float y_pos, float percent)
{
        glColor4f(1.0f, 0.4f, 0.0f, 1.0f);

    //***************************************************X*****************************************
    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.07f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.06f, percent) + x_pos, VALUE_FROM_PERCENT(0.05f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.06f, percent) + x_pos, VALUE_FROM_PERCENT(0.12f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.16f, percent) + x_pos, VALUE_FROM_PERCENT(0.17f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.16f, percent) + x_pos, VALUE_FROM_PERCENT(0.24f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.2f, percent) + x_pos, VALUE_FROM_PERCENT(0.25f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.17f, percent) + x_pos, VALUE_FROM_PERCENT(0.27f, percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.2f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
        // glVertex3f(VALUE_FROM_PERCENT(0.15f, percent) + x_pos, VALUE_FROM_PERCENT(0.14f, percent) + y_pos, 0.0f);
        // glVertex3f(VALUE_FROM_PERCENT(0.15f, percent) + x_pos, VALUE_FROM_PERCENT(0.11f, percent) + y_pos, 0.0f);
    }
    glEnd();
   
}

void Shashwat_shwa(float x_pos, float y_pos, float percent)
{
   

    float t = 0.0f;
    int i = 0;

    struct ouj_Curve ouj_curve49;
    struct ouj_Curve ouj_curve50;
    
    //co-ordinate x,y
    ouj_curve49.ouj_x1 = 0.0f;
    ouj_curve49.ouj_x2 = -0.34f;
    ouj_curve49.ouj_x3 = -0.27f;
    ouj_curve49.ouj_x4 = 0.0f;

   
    ouj_curve49.ouj_y1 = 0.3f;
    ouj_curve49.ouj_y2 = 0.34f;
    ouj_curve49.ouj_y3 = 0.02f;
    ouj_curve49.ouj_y4 = 0.06f;

    ouj_curve50.ouj_x1 = 0.0f;
    ouj_curve50.ouj_x2 = -0.22f;
    ouj_curve50.ouj_x3 = -0.24f;
    ouj_curve50.ouj_x4 = 0.0f;

    ouj_curve50.ouj_y1 = 0.25f;
    ouj_curve50.ouj_y2 = 0.3f;
    ouj_curve50.ouj_y3 = 0.02f;
    ouj_curve50.ouj_y4 = 0.08f;


    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        ouj_Egt1[i] = (((pow(1 - t, 3)) *  ouj_curve49.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve49.ouj_x2)) + ((3 * (pow(t, 2) *(1-t)) *  ouj_curve49.ouj_x3)) + ((pow(t, 3)) *  ouj_curve49.ouj_x4));
        ouj_Eht1[i] = (((pow(1 - t, 3)) *  ouj_curve49.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve49.ouj_y2)) + ((3 * (pow(t, 2)*(1-t)) *  ouj_curve49.ouj_y3)) + ((pow(t, 3)) *  ouj_curve49.ouj_y4));
    }

    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
         ouj_Egt2[i] = (((pow(1 - t, 3)) *  ouj_curve50.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve50.ouj_x2)) + ((3 * (pow(t, 2) *(1-t)) *  ouj_curve50.ouj_x3)) + ((pow(t, 3)) *  ouj_curve50.ouj_x4));
         ouj_Eht2[i] = (((pow(1 - t, 3)) *  ouj_curve50.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve50.ouj_y2)) + ((3 * (pow(t, 2) *(1-t)) *  ouj_curve50.ouj_y3)) + ((pow(t, 3)) *  ouj_curve50.ouj_y4));
     }

     glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLE_STRIP);
    {
        for (i = 0; i < 100; i++)
        {
            glVertex3f(VALUE_FROM_PERCENT(ouj_Egt1[i], percent) + x_pos, VALUE_FROM_PERCENT(ouj_Eht1[i], percent) + y_pos, 0.0f);
            glVertex3f(VALUE_FROM_PERCENT(ouj_Egt2[i], percent) + x_pos, VALUE_FROM_PERCENT(ouj_Eht2[i], percent) + y_pos, 0.0f);
        }
    }
    glEnd();

    

}

void Shashwat_sha5(float x_pos, float y_pos, float percent)
{
   

    float t = 0.0f;
    int i = 0;

    struct ouj_Curve ouj_curve51;
    struct ouj_Curve ouj_curve52;
    
    //co-ordinate x,y
    ouj_curve51.ouj_x1 = 0.0f;
    ouj_curve51.ouj_x2 = -0.5f;
    ouj_curve51.ouj_x3 = -0.27f;
    ouj_curve51.ouj_x4 = -0.27f;

   
    ouj_curve51.ouj_y1 = 0.35f;
    ouj_curve51.ouj_y2 = 0.3f;
    ouj_curve51.ouj_y3 = 0.07f;
    ouj_curve51.ouj_y4 = 0.0f;

    ouj_curve52.ouj_x1 = 0.0f;
    ouj_curve52.ouj_x2 = -0.35f;
    ouj_curve52.ouj_x3 = -0.27f;
    ouj_curve52.ouj_x4 = -0.24f;

    ouj_curve52.ouj_y1 = 0.3f;
    ouj_curve52.ouj_y2 = 0.3f;
    ouj_curve52.ouj_y3 = 0.08f;
    ouj_curve52.ouj_y4 = 0.0f;


    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        ouj_Eit1[i] = (((pow(1 - t, 3)) *  ouj_curve51.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve51.ouj_x2)) + ((3 * (pow(t, 2) *(1-t)) *  ouj_curve51.ouj_x3)) + ((pow(t, 3)) *  ouj_curve51.ouj_x4));
        ouj_Ejt1[i] = (((pow(1 - t, 3)) *  ouj_curve51.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve51.ouj_y2)) + ((3 * (pow(t, 2)*(1-t)) *  ouj_curve51.ouj_y3)) + ((pow(t, 3)) *  ouj_curve51.ouj_y4));
    }

    for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
    {
        ouj_Eit2[i] = (((pow(1 - t, 3)) *  ouj_curve52.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve52.ouj_x2)) + ((3 * (pow(t, 2) *(1-t)) *  ouj_curve52.ouj_x3)) + ((pow(t, 3)) *  ouj_curve52.ouj_x4));
        ouj_Ejt2 [i] = (((pow(1 - t, 3)) *  ouj_curve52.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve52.ouj_y2)) + ((3 * (pow(t, 2) *(1-t)) *  ouj_curve52.ouj_y3)) + ((pow(t, 3)) *  ouj_curve52.ouj_y4));
     }

     glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLE_STRIP);
    {
        for (i = 0; i < 100; i++)
        {
            glVertex3f(VALUE_FROM_PERCENT(ouj_Eit1[i], percent) + x_pos, VALUE_FROM_PERCENT( ouj_Ejt1[i], percent) + y_pos, 0.0f);
            glVertex3f(VALUE_FROM_PERCENT(ouj_Eit2[i], percent) + x_pos, VALUE_FROM_PERCENT( ouj_Ejt2[i], percent) + y_pos, 0.0f);
        }
    }
    glEnd();

    

}

void Shashwat_sha6(float x_pos, float y_pos, float percent)
{
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
}
// void sun(float x_pos, float y_pos, float percent)
// {
//     glBegin(GL_LINES);
//     {

    
//         float i;
//         float x, y, radius = 0.5f, angle;
//         //float x1, y1, radius1 = 0.5f;

        
        

//         for (i = 0.0f; i < 360; i = i + 0.1f)
//         {

//         angle = i * (3.14 / 180);

//         x = (radius * (cos(angle)));
//         y = (radius * (sin(angle)));

//         // x1 = (radius1 * (cos(angle)));
//         // y1 = (radius1 * (sin(angle)));

//         //glColor3f(0.0f, 1.0f, 0.0f);//green
//         glVertex2f(0.0f, 0.0f);
       
//         glColor3f(1.0f, 0.8f, 0.0f);//red
//         glVertex2f(x, y);

//        // glColor3f(1.0f, 0.0f, 0.0f);
//         glVertex2f(x, y);
//         //glColor3f(0.0f, 0.0f, 0.1f);//blue
//        //glVertex2f(x1, y1);
//         }
    


//     }
//     glEnd();
// }