//header file
#include<GL/freeglut.h>


// Macro
#define VALUE_FROM_PERSENT(complete_value, persent) (complete_value * persent / 100)

// Function Prototype
extern void ChristmasTree_Atharv(float x_pos, float y_pos, int persent);


// Function Defination
/*
    @description : function for displaying Christmas tree having 3 parameters :
                    1) x_pos -> to change x co-ordinate of object
                    2) y_pos -> to change y co-ordinate of object
                    3) persent -> to change scale of object
*/
void ChristmasTree_Atharv(float x_pos, float y_pos, int persent)
{
    /*
        Stem of Christmas tree
    */
    glBegin(GL_QUADS);
    {
        glColor3f(0.4f, 0.1f, 0.0f);
        glVertex2f(VALUE_FROM_PERSENT(-0.52f, persent) + x_pos, VALUE_FROM_PERSENT(0.0f, persent) + y_pos);      
        glVertex2f(VALUE_FROM_PERSENT(-0.52f, persent) + x_pos, VALUE_FROM_PERSENT(-0.09f, persent) + y_pos);         
        glColor3f(0.6f, 0.4f, 0.1f);
        glVertex2f(VALUE_FROM_PERSENT(-0.49f, persent) + x_pos, VALUE_FROM_PERSENT(-0.09f, persent) + y_pos);        
        glVertex2f(VALUE_FROM_PERSENT(-0.49f, persent) + x_pos, VALUE_FROM_PERSENT(0.0f, persent) + y_pos);  
    }
    glEnd();


    /*
        Leaves of Christmas Tree
    */
    glBegin(GL_TRIANGLES); // Last Part
    {
        glColor3f(0.6f, 0.9f, 0.1f);
        glVertex2f(VALUE_FROM_PERSENT(-0.51f, persent) + x_pos, VALUE_FROM_PERSENT(0.18f, persent) + y_pos);       
        glColor3f(0.6f, 0.6f, 0.0f);
        glVertex2f(VALUE_FROM_PERSENT(-0.63f, persent) + x_pos, VALUE_FROM_PERSENT(0.0f, persent) + y_pos);      
        glColor3f(0.6f, 0.6f, 0.0f);
        glVertex2f(VALUE_FROM_PERSENT(-0.38f, persent) + x_pos, VALUE_FROM_PERSENT(0.0f, persent) + y_pos);
    }
    glEnd();

    glBegin(GL_TRIANGLES); // Middel Part
    {
        glColor3f(0.6f, 0.9f, 0.1f);
        glVertex2f(VALUE_FROM_PERSENT(-0.51f, persent) + x_pos, VALUE_FROM_PERSENT(0.28f , persent) + y_pos);       
        glColor3f(0.6f, 0.6f, 0.0f);
        glVertex2f(VALUE_FROM_PERSENT(-0.60f, persent) + x_pos, VALUE_FROM_PERSENT(0.12f , persent) + y_pos);       
        glColor3f(0.6f, 0.6f, 0.0f);
        glVertex2f(VALUE_FROM_PERSENT(-0.41f, persent) + x_pos, VALUE_FROM_PERSENT(0.12f , persent) + y_pos);   
    }
    glEnd();

    glBegin(GL_TRIANGLES); // First Part
    {
        glColor3f(0.6f, 0.9f, 0.1f);
        glVertex2f(VALUE_FROM_PERSENT(-0.51f, persent) + x_pos, VALUE_FROM_PERSENT(0.34f , persent) + y_pos);       
        glColor3f(0.6f, 0.6f, 0.0f);
        glVertex2f(VALUE_FROM_PERSENT(-0.55f, persent) + x_pos, VALUE_FROM_PERSENT(0.24f , persent) + y_pos);       
        glColor3f(0.6f, 0.6f, 0.0f);
        glVertex2f(VALUE_FROM_PERSENT(-0.46f, persent) + x_pos, VALUE_FROM_PERSENT(0.24f , persent) + y_pos);   
    }
    glEnd();
}