//Header file
#include<GL/freeglut.h>

// Macro
#define VALUE_FROM_PERSENT(complete_value, persent) (complete_value * persent / 100)

// Function Prototype
extern void TiltedCoconutTree_Atharv(float x_pos, float y_pos, int persent);

// Function Defination
/*
    @description : function for displaying Tilted Coconut tree having 3 parameters :
                    1) x_pos -> to change x co-ordinate of object
                    2) y_pos -> to change y co-ordinate of object
                    3) persent -> to change scale of object
*/
void TiltedCoconutTree_Atharv(float x_pos, float y_pos, int persent)
{   
        /*
            Stem of Tilted Coconut Tree
        */
        {
            glBegin(GL_QUADS); // Part 1
            {
                glColor3f(0.5f, 0.2f, 0.0f);
                glVertex2f(VALUE_FROM_PERSENT(0.44f, persent) + x_pos, VALUE_FROM_PERSENT(-0.13f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.41f, persent) + x_pos, VALUE_FROM_PERSENT(-0.19f, persent) + y_pos);
                glColor3f(0.8f, 0.5f, 0.3f);
                glVertex2f(VALUE_FROM_PERSENT(0.45f, persent) + x_pos, VALUE_FROM_PERSENT(-0.20f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.46f, persent) + x_pos, VALUE_FROM_PERSENT(-0.15f, persent) + y_pos);
            }
            glEnd();

             glBegin(GL_QUADS); // Part 2
            {
                glColor3f(0.5f, 0.2f, 0.0f);
                glVertex2f(VALUE_FROM_PERSENT(0.41f, persent) + x_pos, VALUE_FROM_PERSENT(-0.19f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.39f, persent) + x_pos, VALUE_FROM_PERSENT(-0.24f, persent) + y_pos);
                glColor3f(0.8f, 0.5f, 0.3f);
                glVertex2f(VALUE_FROM_PERSENT(0.44f, persent) + x_pos, VALUE_FROM_PERSENT(-0.26f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.45f, persent) + x_pos, VALUE_FROM_PERSENT(-0.20f, persent) + y_pos);
            }
            glEnd();

            glBegin(GL_QUADS); // Part 3
            {
                glColor3f(0.5f, 0.2f, 0.0f);
                glVertex2f(VALUE_FROM_PERSENT(0.39f, persent) + x_pos, VALUE_FROM_PERSENT(-0.24f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.37f, persent) + x_pos, VALUE_FROM_PERSENT(-0.32f, persent) + y_pos);
                glColor3f(0.8f, 0.5f, 0.3f);
                glVertex2f(VALUE_FROM_PERSENT(0.43f, persent) + x_pos, VALUE_FROM_PERSENT(-0.34f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.44f, persent) + x_pos, VALUE_FROM_PERSENT(-0.26f, persent) + y_pos);
            }
            glEnd();

            glBegin(GL_QUADS); // Part 4
            {
                glColor3f(0.5f, 0.2f, 0.0f);
                glVertex2f(VALUE_FROM_PERSENT(0.37f, persent) + x_pos, VALUE_FROM_PERSENT(-0.32f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.33f, persent) + x_pos, VALUE_FROM_PERSENT(-0.39f, persent) + y_pos);
                glColor3f(0.8f, 0.5f, 0.3f);
                glVertex2f(VALUE_FROM_PERSENT(0.43f, persent) + x_pos, VALUE_FROM_PERSENT(-0.41f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.43f, persent) + x_pos, VALUE_FROM_PERSENT(-0.34f, persent) + y_pos);
            }
            glEnd();

            glBegin(GL_QUADS); // Part 5
            {
                glColor3f(0.5f, 0.2f, 0.0f);
                glVertex2f(VALUE_FROM_PERSENT(0.33f, persent) + x_pos, VALUE_FROM_PERSENT(-0.39f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.33f, persent) + x_pos, VALUE_FROM_PERSENT(-0.46f, persent) + y_pos);
                glColor3f(0.8f, 0.5f, 0.3f);
                glVertex2f(VALUE_FROM_PERSENT(0.42f, persent) + x_pos, VALUE_FROM_PERSENT(-0.46f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.43f, persent) + x_pos, VALUE_FROM_PERSENT(-0.41f, persent) + y_pos);
            }
            glEnd();

            glBegin(GL_QUADS); // Part 6
            {
                glColor3f(0.5f, 0.2f, 0.0f);
                glVertex2f(VALUE_FROM_PERSENT(0.33f, persent) + x_pos, VALUE_FROM_PERSENT(-0.46f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.32f, persent) + x_pos, VALUE_FROM_PERSENT(-0.55f, persent) + y_pos);
                glColor3f(0.8f, 0.5f, 0.3f);
                glVertex2f(VALUE_FROM_PERSENT(0.43f, persent) + x_pos, VALUE_FROM_PERSENT(-0.55f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.42f, persent) + x_pos, VALUE_FROM_PERSENT(-0.46f, persent) + y_pos);
            }
            glEnd();


            /*
                Lines to display divsion between parts of stem
            */
            glColor3f(0.5f, 0.2f, 0.0f);
            glLineWidth(3.0f);
            {
                glBegin(GL_LINES); // Division 1
                {
                    glVertex2f(VALUE_FROM_PERSENT(0.41f, persent) + x_pos, VALUE_FROM_PERSENT(-0.19f, persent) + y_pos);
                    glVertex2f(VALUE_FROM_PERSENT(0.45f, persent) + x_pos, VALUE_FROM_PERSENT(-0.20f, persent) + y_pos);
                }
                glEnd();


                glBegin(GL_LINES); // Division 2
                {
                    glVertex2f(VALUE_FROM_PERSENT(0.39f, persent) + x_pos, VALUE_FROM_PERSENT(-0.24f, persent) + y_pos);
                    glVertex2f(VALUE_FROM_PERSENT(0.44f, persent) + x_pos, VALUE_FROM_PERSENT(-0.26f, persent) + y_pos);
                }
                glEnd();


                glBegin(GL_LINES); // Division 3
                {
                    glVertex2f(VALUE_FROM_PERSENT(0.37f, persent) + x_pos, VALUE_FROM_PERSENT(-0.32f, persent) + y_pos);
                    glVertex2f(VALUE_FROM_PERSENT(0.43f, persent) + x_pos, VALUE_FROM_PERSENT(-0.34f, persent) + y_pos);
                }
                glEnd();


                glBegin(GL_LINES); // Division 4
                {
                    glVertex2f(VALUE_FROM_PERSENT(0.33f, persent) + x_pos, VALUE_FROM_PERSENT(-0.39f, persent) + y_pos);
                    glVertex2f(VALUE_FROM_PERSENT(0.43f, persent) + x_pos, VALUE_FROM_PERSENT(-0.41f, persent) + y_pos);
                }
                glEnd();


                glBegin(GL_LINES); // Division 5
                {
                    glVertex2f(VALUE_FROM_PERSENT(0.33f, persent) + x_pos, VALUE_FROM_PERSENT(-0.46f, persent) + y_pos);
                    glVertex2f(VALUE_FROM_PERSENT(0.42f, persent) + x_pos, VALUE_FROM_PERSENT(-0.46f, persent) + y_pos);
                }
                glEnd();


                glBegin(GL_LINES); // Division 6
                {
                    glVertex2f(VALUE_FROM_PERSENT(0.32f, persent) + x_pos, VALUE_FROM_PERSENT(-0.55f, persent) + y_pos);
                    glVertex2f(VALUE_FROM_PERSENT(0.43f, persent) + x_pos, VALUE_FROM_PERSENT(-0.55f, persent) + y_pos);
                }
                glEnd();
            }
        }


        /*
            Leaves of Tilted Coconut Tree
        */
        glColor3f(0.5f, 0.8f, 0.1f);
        {
            glBegin(GL_POLYGON); // Leaf 1
            {
                glVertex2f(VALUE_FROM_PERSENT(0.43f, persent) + x_pos, VALUE_FROM_PERSENT(-0.12f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.33f, persent) + x_pos, VALUE_FROM_PERSENT(-0.13f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.26f, persent) + x_pos, VALUE_FROM_PERSENT(-0.19f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.32f, persent) + x_pos, VALUE_FROM_PERSENT(-0.19f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.31f, persent) + x_pos, VALUE_FROM_PERSENT(-0.16f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.35f, persent) + x_pos, VALUE_FROM_PERSENT(-0.18f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.39f, persent) + x_pos, VALUE_FROM_PERSENT(-0.18f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.39f, persent) + x_pos, VALUE_FROM_PERSENT(-0.15f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.41f, persent) + x_pos, VALUE_FROM_PERSENT(-0.16f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.43f, persent) + x_pos, VALUE_FROM_PERSENT(-0.13f, persent) + y_pos);
            }
            glEnd();


            glBegin(GL_POLYGON); // Leaf 2
            {
                glVertex2f(VALUE_FROM_PERSENT(0.45f, persent) + x_pos, VALUE_FROM_PERSENT(-0.12f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.38f, persent) + x_pos, VALUE_FROM_PERSENT(-0.06f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.41f, persent) + x_pos, VALUE_FROM_PERSENT(-0.05f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.37f, persent) + x_pos, VALUE_FROM_PERSENT(-0.04f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.35f, persent) + x_pos, VALUE_FROM_PERSENT(0.01f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.38f, persent) + x_pos, VALUE_FROM_PERSENT(0.01f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.34f, persent) + x_pos, VALUE_FROM_PERSENT(0.03f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.34f, persent) + x_pos, VALUE_FROM_PERSENT(0.08f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.41f, persent) + x_pos, VALUE_FROM_PERSENT(0.06f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.41f, persent) + x_pos, VALUE_FROM_PERSENT(0.02f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.43f, persent) + x_pos, VALUE_FROM_PERSENT(0.04f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.44f, persent) + x_pos, VALUE_FROM_PERSENT(0.01f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.44f, persent) + x_pos, VALUE_FROM_PERSENT(-0.04f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.46f, persent) + x_pos, VALUE_FROM_PERSENT(-0.02f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.46f, persent) + x_pos, VALUE_FROM_PERSENT(-0.11f, persent) + y_pos);
            }
            glEnd();


             glBegin(GL_POLYGON); // Leaf 3
            {
                glVertex2f(VALUE_FROM_PERSENT(0.47f, persent) + x_pos, VALUE_FROM_PERSENT(-0.13f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.52f, persent) + x_pos, VALUE_FROM_PERSENT(-0.05f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.53f, persent) + x_pos, VALUE_FROM_PERSENT(-0.08f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.55f, persent) + x_pos, VALUE_FROM_PERSENT(-0.03f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.57f, persent) + x_pos, VALUE_FROM_PERSENT(-0.01f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.59f, persent) + x_pos, VALUE_FROM_PERSENT(-0.04f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.60f, persent) + x_pos, VALUE_FROM_PERSENT(0.0f , persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.67f, persent) + x_pos, VALUE_FROM_PERSENT(-0.02f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.64f, persent) + x_pos, VALUE_FROM_PERSENT(-0.06f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.61f, persent) + x_pos, VALUE_FROM_PERSENT(-0.05f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.62f, persent) + x_pos, VALUE_FROM_PERSENT(-0.08f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.59f, persent) + x_pos, VALUE_FROM_PERSENT(-0.11f , persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.54f, persent) + x_pos, VALUE_FROM_PERSENT(-0.09f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.55f, persent) + x_pos, VALUE_FROM_PERSENT(-0.125, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.48f, persent) + x_pos, VALUE_FROM_PERSENT(-0.14f, persent) + y_pos);
            }
            glEnd();


            glBegin(GL_POLYGON); // Leaf 4
            {
                glVertex2f(VALUE_FROM_PERSENT(0.475f, persent) + x_pos,VALUE_FROM_PERSENT(-0.15f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.56f, persent) + x_pos, VALUE_FROM_PERSENT(-0.21f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.59f, persent) + x_pos, VALUE_FROM_PERSENT(-0.30f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.54f, persent) + x_pos, VALUE_FROM_PERSENT(-0.27f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.54f, persent) + x_pos, VALUE_FROM_PERSENT(-0.23f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.51f, persent) + x_pos, VALUE_FROM_PERSENT(-0.25f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.48f, persent) + x_pos, VALUE_FROM_PERSENT(-0.22f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.50f, persent) + x_pos, VALUE_FROM_PERSENT(-0.19f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.47f, persent) + x_pos, VALUE_FROM_PERSENT(-0.19f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.47f, persent) + x_pos, VALUE_FROM_PERSENT(-0.16f, persent) + y_pos);
            }
            glEnd();
        }


        /*
            Coconut on Coconut Tree
        */
        glColor3f(0.4f, 0.1f, 0.0f); 
        {
            glEnable(GL_POINT_SMOOTH);
            glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
            glPointSize(15.0f);

            glBegin(GL_POINTS); // Coconut 1
            {
                glVertex2f(VALUE_FROM_PERSENT(0.45f, persent) + x_pos, VALUE_FROM_PERSENT(-0.15f, persent) + y_pos);
            }
            glEnd();


            glBegin(GL_POINTS); // Coconut 2
            {
                glVertex2f(VALUE_FROM_PERSENT(0.42f, persent) + x_pos, VALUE_FROM_PERSENT(-0.15f, persent) + y_pos);
            }
            glEnd();


            glBegin(GL_POINTS); // Coconut 3
            {
                glVertex2f(VALUE_FROM_PERSENT(0.48f, persent) + x_pos, VALUE_FROM_PERSENT(-0.17f, persent) + y_pos);
            }
            glEnd();

            glPointSize(1.0f); // Back to Default Value
            glDisable(GL_POINT_SMOOTH); // Back to Default Style of Point
        }
}