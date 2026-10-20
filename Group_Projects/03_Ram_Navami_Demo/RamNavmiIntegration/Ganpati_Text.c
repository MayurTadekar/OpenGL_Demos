// win32 headers
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

//OPENGL RELETED HEADER FILE
#include<gl/GL.h>
#include<gl/GLU.h>
#include<math.h>
#include"Ganpati_Text.h"

#define VALUE_FROM_PERCENT(complete, percent) (complete * percent/100.0f)

void Ganpati_Text(void)
{
    //set matrix to model view mode
    glMatrixMode(GL_MODELVIEW);
        
    
    //SET TO IDENTITY MATRIX
    glLoadIdentity();

    //translet triangle back word by Z
    glTranslatef(0.0f, 0.0f, -3.0f);


    Ganpati(0.0f, 0.0f, 150);

}

void Ganpati(float x_pos, float y_pos, float percent)
{
    glLineWidth(5.0f);
    glBegin(GL_LINES);//mukut
    {
        glColor4f(1.0f, 0.0f , 0.0f,1.0f);
        glVertex2f(VALUE_FROM_PERCENT(-0.01f,percent) + x_pos, VALUE_FROM_PERCENT(  0.61f, percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(0.01f,percent) + x_pos, VALUE_FROM_PERCENT(  0.61f, percent) + y_pos);

       
        glVertex2f(VALUE_FROM_PERCENT(-0.04f,percent) + x_pos, VALUE_FROM_PERCENT(  0.59f, percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(0.04f,percent) + x_pos, VALUE_FROM_PERCENT(  0.59f, percent) + y_pos);

       
        glVertex2f(VALUE_FROM_PERCENT(-0.07f,percent) + x_pos, VALUE_FROM_PERCENT(  0.57f, percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(0.07f,percent) + x_pos, VALUE_FROM_PERCENT(  0.57f, percent) + y_pos);

       
        glVertex2f(VALUE_FROM_PERCENT(-0.1f,percent) + x_pos, VALUE_FROM_PERCENT(  0.55f, percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(0.1f,percent) + x_pos, VALUE_FROM_PERCENT(  0.55f, percent) + y_pos);

       
        glVertex2f(VALUE_FROM_PERCENT(-0.13f,percent) + x_pos, VALUE_FROM_PERCENT(  0.53f, percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(0.13f,percent) + x_pos, VALUE_FROM_PERCENT(  0.53f, percent) + y_pos);

       // glColor3f(VALUE_FROM_PERCENT(0.9f,percent) + x_pos, VALUE_FROM_PERCENT( 1.0f, percent) + y_pos, 1.0f);
        //glVertex2f(-0.02f, 0.46f);
        //glVertex2f(-0.01f, 0.44f);


    }
    glEnd();
   

   glBegin(GL_QUADS); //mukotha(chehara)
    {
        glColor4f(1.0f, 0.0f, 0.0f,1.0f);//chehara
        glVertex3f(VALUE_FROM_PERCENT(-0.1f, percent) + x_pos, VALUE_FROM_PERCENT( 0.51f, percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.08f, percent) + x_pos, VALUE_FROM_PERCENT( 0.51f, percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.08f, percent) + x_pos, VALUE_FROM_PERCENT( 0.2f, percent) + y_pos,.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.1f, percent) + x_pos, VALUE_FROM_PERCENT( 0.2f, percent) + y_pos,.0f);

        glColor4f(1.0f, 0.0f, 0.0f,1.0f);//sond
        glVertex3f(VALUE_FROM_PERCENT(-0.1f, percent) + x_pos, VALUE_FROM_PERCENT( 0.26f, percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.17f, percent) + x_pos, VALUE_FROM_PERCENT( 0.26f, percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.17f, percent) + x_pos, VALUE_FROM_PERCENT( 0.2f, percent) + y_pos,.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.1f, percent) + x_pos, VALUE_FROM_PERCENT( 0.2f, percent) + y_pos,.0f);

        glColor4f(1.0f, 0.0f, 0.0f,1.0f);//sond
        glVertex3f(VALUE_FROM_PERCENT(0.14f, percent) + x_pos, VALUE_FROM_PERCENT( 0.25f, percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.17f, percent) + x_pos, VALUE_FROM_PERCENT( 0.25f, percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.17f, percent) + x_pos, VALUE_FROM_PERCENT( 0.17f, percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.14f, percent) + x_pos, VALUE_FROM_PERCENT( 0.17f, percent) + y_pos,0.0f);

        glColor4f(0.9f,1.0f, 1.0f,1.0f);// right eye
        glVertex3f(VALUE_FROM_PERCENT(-0.06f, percent) + x_pos, VALUE_FROM_PERCENT( 0.41f,percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.05f ,percent) + x_pos, VALUE_FROM_PERCENT( 0.42f,percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.04f, percent) + x_pos, VALUE_FROM_PERCENT( 0.41f,percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.05f, percent) + x_pos, VALUE_FROM_PERCENT( 0.40f,percent) + y_pos, 0.0f);

        glColor4f(0.9f, 1.0f, 1.0f,1.0f);// left eye
        glVertex3f(VALUE_FROM_PERCENT(0.03f, percent) + x_pos, VALUE_FROM_PERCENT( 0.41f, percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT( 0.42f, percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.05f, percent) + x_pos, VALUE_FROM_PERCENT( 0.41f, percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT( 0.40f, percent) + y_pos,0.0f);

        glColor4f(1.0f, 0.0f,  0.0f,1.0f);// right leg
        glVertex3f(VALUE_FROM_PERCENT(-0.055f, percent) + x_pos, VALUE_FROM_PERCENT( -0.15f,percent) + y_pos, 0.0f);//
        glVertex3f(VALUE_FROM_PERCENT(-0.0f, percent) + x_pos, VALUE_FROM_PERCENT( -0.1f, percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.0f, percent) + x_pos, VALUE_FROM_PERCENT( -0.18f,percent) + y_pos, 0.0f);//
        glVertex3f(VALUE_FROM_PERCENT(-0.055f, percent) + x_pos, VALUE_FROM_PERCENT( -0.27f,percent) + y_pos, 0.0f);//


        //glColor4f(VALUE_FROM_PERCENT(0.9f,percent) + x_pos, VALUE_FROM_PERCENT( 1.0f, percent) + y_pos, 1.0f,0.1f);// left leg
        glVertex3f(VALUE_FROM_PERCENT(0.07f, percent) + x_pos, VALUE_FROM_PERCENT( -0.19f,percent) + y_pos, 0.0f);//
        glVertex3f(VALUE_FROM_PERCENT(0.01f, percent) + x_pos, VALUE_FROM_PERCENT( -0.1f, percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.01f, percent) + x_pos, VALUE_FROM_PERCENT( -0.19f,percent) + y_pos, 0.0f);//
        glVertex3f(VALUE_FROM_PERCENT(0.07f, percent) + x_pos, VALUE_FROM_PERCENT( -0.26f,percent) + y_pos, 0.0f);//


    }
    glEnd();

    glBegin(GL_TRIANGLES);// 1 right side 2 left side kan
    {
        glColor4f(1.0f, 0.0f, 0.0f,1.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.29f, percent) + x_pos, VALUE_FROM_PERCENT( 0.51f,percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.11f, percent) + x_pos, VALUE_FROM_PERCENT( 0.51f,percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.11f, percent) + x_pos, VALUE_FROM_PERCENT( 0.2f, percent) + y_pos,0.0f);

      
        glVertex3f(VALUE_FROM_PERCENT(0.09f, percent) + x_pos, VALUE_FROM_PERCENT( 0.51f, percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.27f, percent) + x_pos, VALUE_FROM_PERCENT( 0.51f, percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.09f, percent) + x_pos, VALUE_FROM_PERCENT( 0.26f, percent) + y_pos,0.0f);

     //potacha bhag start(1)
        glVertex3f(VALUE_FROM_PERCENT(-0.19f, percent) + x_pos, VALUE_FROM_PERCENT( 0.19f,percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.165f, percent) + x_pos, VALUE_FROM_PERCENT( 0.26f,percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.115, percent) + x_pos, VALUE_FROM_PERCENT( 0.19f,percent) + y_pos, 0.0f);

       
        glVertex3f(VALUE_FROM_PERCENT(-0.19f, percent) + x_pos, VALUE_FROM_PERCENT( 0.19f,percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.115f, percent) + x_pos, VALUE_FROM_PERCENT( 0.19f,percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.115f, percent) + x_pos, VALUE_FROM_PERCENT( -0.04f,percent) + y_pos, 0.0f);

      
        glVertex3f(VALUE_FROM_PERCENT(-0.19f, percent) + x_pos, VALUE_FROM_PERCENT( 0.19f,percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.19f, percent) + x_pos, VALUE_FROM_PERCENT( -0.0f,percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.115f, percent) + x_pos, VALUE_FROM_PERCENT( -0.04f,percent) + y_pos, 0.0f);

      
        glVertex3f(VALUE_FROM_PERCENT(-0.115, percent) + x_pos, VALUE_FROM_PERCENT( 0.19f,percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.13f, percent) + x_pos, VALUE_FROM_PERCENT( 0.19f, percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.115f, percent) + x_pos, VALUE_FROM_PERCENT( -0.04f,percent) + y_pos, 0.0f);

       
        glVertex3f(VALUE_FROM_PERCENT(-0.109f, percent) + x_pos, VALUE_FROM_PERCENT(-0.04f,percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.13f, percent) + x_pos, VALUE_FROM_PERCENT( 0.18f, percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.13f, percent) + x_pos, VALUE_FROM_PERCENT( -0.0f, percent) + y_pos,0.0f);

       
        glVertex3f(VALUE_FROM_PERCENT(-0.109f, percent) + x_pos, VALUE_FROM_PERCENT( -0.04f,percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.13f, percent) + x_pos, VALUE_FROM_PERCENT( -0.0f, percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.08f, percent) + y_pos,0.0f);

        
        glVertex3f(VALUE_FROM_PERCENT(0.0f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.09f, percent) + y_pos,0.0f);//1
        glVertex3f(VALUE_FROM_PERCENT(-0.19f, percent) + x_pos, VALUE_FROM_PERCENT( -0.01f,percent) + y_pos, 0.0f);//2
        glVertex3f(VALUE_FROM_PERCENT(-0.19f, percent) + x_pos, VALUE_FROM_PERCENT( -0.27f,percent) + y_pos, 0.0f);//3

       // glColor3f(VALUE_FROM_PERCENT(0.9f,percent) + x_pos, VALUE_FROM_PERCENT( 0.2f, percent) + y_pos, 0.1f,0.1f);//7 right mandi(2)
        glVertex3f(VALUE_FROM_PERCENT(-0.27f, percent) + x_pos, VALUE_FROM_PERCENT( -0.01f,percent) + y_pos, 0.0f);//1
        glVertex3f(VALUE_FROM_PERCENT(-0.19f, percent) + x_pos, VALUE_FROM_PERCENT( -0.01f,percent) + y_pos, 0.0f);//2
        glVertex3f(VALUE_FROM_PERCENT(-0.19f, percent) + x_pos, VALUE_FROM_PERCENT( -0.27f,percent) + y_pos, 0.0f);//3

       // glColor3f(VALUE_FROM_PERCENT(0.9f,percent) + x_pos, VALUE_FROM_PERCENT( 0.2f, percent) + y_pos, 0.1f,0.1f);//7 right mandi(3)
        glVertex3f(VALUE_FROM_PERCENT(-0.27f, percent) + x_pos, VALUE_FROM_PERCENT( -0.01f,percent) + y_pos, 0.0f);//1
        glVertex3f(VALUE_FROM_PERCENT(-0.27f, percent) + x_pos, VALUE_FROM_PERCENT( -0.3f,percent) + y_pos, 0.0f);//2
        glVertex3f(VALUE_FROM_PERCENT(-0.19f, percent) + x_pos, VALUE_FROM_PERCENT( -0.27f,percent) + y_pos, 0.0f);//3

       // glColor3f(VALUE_FROM_PERCENT(0.9f,percent) + x_pos, VALUE_FROM_PERCENT( 0.2f, percent) + y_pos, 0.1f,0.1f);//7 left mandi(1)
        glVertex3f(VALUE_FROM_PERCENT(0.01f, percent) + x_pos, VALUE_FROM_PERCENT( -0.09f,percent) + y_pos, 0.0f);//1
        glVertex3f(VALUE_FROM_PERCENT(0.13f, percent) + x_pos, VALUE_FROM_PERCENT( -0.01f,percent) + y_pos, 0.0f);//2
        glVertex3f(VALUE_FROM_PERCENT(0.13f, percent) + x_pos, VALUE_FROM_PERCENT( -0.27f,percent) + y_pos, 0.0f);//3

        //glColor3f(VALUE_FROM_PERCENT(0.9f,percent) + x_pos, VALUE_FROM_PERCENT( 0.2f, percent) + y_pos, 0.1f,0.1f);//7 left mandi(2)
        glVertex3f(VALUE_FROM_PERCENT(0.13f, percent) + x_pos, VALUE_FROM_PERCENT( -0.01f,percent) + y_pos, 0.0f);//1
        glVertex3f(VALUE_FROM_PERCENT(0.24f, percent) + x_pos, VALUE_FROM_PERCENT( -0.01f,percent) + y_pos, 0.0f);//2
        glVertex3f(VALUE_FROM_PERCENT(0.13f, percent) + x_pos, VALUE_FROM_PERCENT( -0.27f,percent) + y_pos, 0.0f);//3

        //glColor3f(VALUE_FROM_PERCENT(0.9f,percent) + x_pos, VALUE_FROM_PERCENT( 0.2f, percent) + y_pos, 0.1f,0.1f);//7 left mandi(3)
        glVertex3f(VALUE_FROM_PERCENT(0.24f, percent) + x_pos, VALUE_FROM_PERCENT( -0.01f,percent) + y_pos, 0.0f);//1
        glVertex3f(VALUE_FROM_PERCENT(0.24f, percent) + x_pos, VALUE_FROM_PERCENT( -0.3f, percent) + y_pos,0.0f);//2
        glVertex3f(VALUE_FROM_PERCENT(0.13f, percent) + x_pos, VALUE_FROM_PERCENT( -0.27f,percent) + y_pos, 0.0f);//3



    }
    glEnd();

    glBegin(GL_POLYGON);
    {
        glColor4f(1.0f, 0.0f,0.0f,1.0f);
        glVertex2f(VALUE_FROM_PERCENT(-0.22f,percent) + x_pos, VALUE_FROM_PERCENT( 0.15f,percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(-0.27f,percent) + x_pos, VALUE_FROM_PERCENT( 0.12f,percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(-0.27f,percent) + x_pos, VALUE_FROM_PERCENT( 0.0f,percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(-0.22f,percent) + x_pos, VALUE_FROM_PERCENT( 0.0f,percent) + y_pos);
    }
    
    glEnd();

    glBegin(GL_POLYGON);
    {
        glColor4f(1.0f, 0.0f,0.0f,1.0f);
        glVertex2f(VALUE_FROM_PERCENT(-0.198f,percent) + x_pos, VALUE_FROM_PERCENT( 0.12f,percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(-0.22f,percent) + x_pos, VALUE_FROM_PERCENT( 0.09f,percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(-0.22f,percent) + x_pos, VALUE_FROM_PERCENT( 0.0f,percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(-0.198f,percent) + x_pos, VALUE_FROM_PERCENT( 0.0f,percent) + y_pos);
    }
    
    glEnd();

    
  
    glBegin(GL_POLYGON);
    {
        glColor4f(1.0f, 0.0f,0.0f,1.0f);
        glVertex2f(VALUE_FROM_PERCENT(0.14f,percent) + x_pos, VALUE_FROM_PERCENT( 0.03f,percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(0.16f,percent) + x_pos, VALUE_FROM_PERCENT( 0.0f,percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(0.22f,percent) + x_pos, VALUE_FROM_PERCENT( 0.0f,percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(0.24f,percent) + x_pos, VALUE_FROM_PERCENT( 0.03f,percent) + y_pos);
    }
    
    glEnd();

    glBegin(GL_TRIANGLES);
    {
        glColor4f(1.0f, 0.6f,0.1f,1.0f);
        glVertex2f(VALUE_FROM_PERCENT(0.14f,percent) + x_pos, VALUE_FROM_PERCENT( 0.04f,percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(0.19f,percent) + x_pos, VALUE_FROM_PERCENT( 0.1f,percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(0.24f,percent) + x_pos, VALUE_FROM_PERCENT( 0.04f,percent) + y_pos);
      
    }
    
    glEnd();
}