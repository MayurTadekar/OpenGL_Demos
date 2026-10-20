//header file 
#include<GL/freeglut.h>

// Macro 
#define VALUE_FROM_PERSENT(complete_value, persent) (complete_value * persent / 100)

// Function Prototype
extern void StraightCoconutTree_Atharv(float x_pos, float y_pos, int persent);
    


// Function Defination
/*
    @description : function for displaying Straight Coconut tree having 3 parameters :
                    1) x_pos -> to change x co-ordinate of object
                    2) y_pos -> to change y co-ordinate of object
                    3) persent -> to change scale of object 
*/

void StraightCoconutTree_Atharv(float x_pos, float y_pos, int persent)
{
        /*
            Stem of a Coconut Tree
        */
        {
            glBegin(GL_QUADS); // part 1
            {
                glColor3f(0.5f, 0.2f, 0.0f);
                glVertex2f(VALUE_FROM_PERSENT(0.11f, persent) + x_pos, VALUE_FROM_PERSENT(0.0f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.10f, persent) + x_pos, VALUE_FROM_PERSENT(-0.03f, persent) + y_pos);
                glColor3f(0.8f, 0.5f, 0.3f);
                glVertex2f(VALUE_FROM_PERSENT(0.13f, persent) + x_pos, VALUE_FROM_PERSENT(-0.03f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.123f, persent) + x_pos,VALUE_FROM_PERSENT( 0.0f , persent)+ y_pos);
            }
            glEnd();

            glBegin(GL_QUADS); // part 2
            {
                glColor3f(0.5f, 0.2f, 0.0f);
                glVertex2f(VALUE_FROM_PERSENT(0.10f, persent) + x_pos, VALUE_FROM_PERSENT(-0.03f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.10f, persent) + x_pos, VALUE_FROM_PERSENT(-0.07f, persent) + y_pos);
                glColor3f(0.8f, 0.5f, 0.3f);
                glVertex2f(VALUE_FROM_PERSENT(0.13f, persent) + x_pos, VALUE_FROM_PERSENT(-0.07f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.13f, persent) + x_pos, VALUE_FROM_PERSENT(-0.03f, persent) + y_pos);
            }
            glEnd();

            glBegin(GL_QUADS); // part 3
            {
                glColor3f(0.5f, 0.2f, 0.0f);
                glVertex2f(VALUE_FROM_PERSENT(0.10f, persent) + x_pos, VALUE_FROM_PERSENT(-0.07f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.10f, persent) + x_pos, VALUE_FROM_PERSENT(-0.12f, persent) + y_pos);
                glColor3f(0.8f, 0.5f, 0.3f);
                glVertex2f(VALUE_FROM_PERSENT(0.135f, persent) + x_pos,VALUE_FROM_PERSENT( -0.12f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.13f, persent) + x_pos, VALUE_FROM_PERSENT(-0.07f, persent) + y_pos);
            }
            glEnd();

            glBegin(GL_QUADS); // part 4
            {
                glColor3f(0.5f, 0.2f, 0.0f);
                glVertex2f(VALUE_FROM_PERSENT(0.10f, persent) + x_pos, VALUE_FROM_PERSENT(-0.12f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.095f, persent) + x_pos,VALUE_FROM_PERSENT( -0.17f, persent) + y_pos);
                glColor3f(0.8f, 0.5f, 0.3f);
                glVertex2f(VALUE_FROM_PERSENT(0.15f, persent) + x_pos, VALUE_FROM_PERSENT(-0.17f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.135f, persent) + x_pos,VALUE_FROM_PERSENT( -0.12f, persent) + y_pos);
            }
            glEnd();

            glBegin(GL_QUADS); // part 5
            {
                glColor3f(0.5f, 0.2f, 0.0f);
                glVertex2f(VALUE_FROM_PERSENT(0.095f, persent) + x_pos,VALUE_FROM_PERSENT( -0.17f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.103f, persent) + x_pos,VALUE_FROM_PERSENT( -0.235f, persent) + y_pos);
                glColor3f(0.8f, 0.5f, 0.3f);
                glVertex2f(VALUE_FROM_PERSENT(0.143f, persent) + x_pos,VALUE_FROM_PERSENT( -0.235f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.15f, persent) + x_pos, VALUE_FROM_PERSENT(-0.17f, persent) + y_pos);
            }
            glEnd();

            glBegin(GL_QUADS); // part 6
            {
                glColor3f(0.5f, 0.2f, 0.0f);
                glVertex2f(VALUE_FROM_PERSENT(0.103f, persent) + x_pos,VALUE_FROM_PERSENT( -0.235f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.095f, persent) + x_pos,VALUE_FROM_PERSENT( -0.315f, persent) + y_pos);
                glColor3f(0.8f, 0.5f, 0.3f);
                glVertex2f(VALUE_FROM_PERSENT(0.143f, persent) + x_pos,VALUE_FROM_PERSENT( -0.315f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.143f, persent) + x_pos,VALUE_FROM_PERSENT( -0.235f, persent) + y_pos);
            }
            glEnd();

            glBegin(GL_QUADS); // part 7
            {
                glColor3f(0.5f, 0.2f, 0.0f);
                glVertex2f(VALUE_FROM_PERSENT(0.095f, persent) + x_pos,VALUE_FROM_PERSENT( -0.315f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.095f, persent) + x_pos,VALUE_FROM_PERSENT( -0.39f, persent) + y_pos);
                glColor3f(0.8f, 0.5f, 0.3f);
                glVertex2f(VALUE_FROM_PERSENT(0.143f, persent) + x_pos,VALUE_FROM_PERSENT( -0.39f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.143f, persent) + x_pos,VALUE_FROM_PERSENT( -0.315f, persent) + y_pos);
            }
            glEnd();

            glBegin(GL_QUADS); // part 8
            {
                glColor3f(0.5f, 0.2f, 0.0f);
                glVertex2f(VALUE_FROM_PERSENT(0.095f, persent) + x_pos,VALUE_FROM_PERSENT( -0.39f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.09f, persent) + x_pos, VALUE_FROM_PERSENT(-0.465f, persent) + y_pos);
                glColor3f(0.8f, 0.5f, 0.3f);
                glVertex2f(VALUE_FROM_PERSENT(0.15f, persent) + x_pos, VALUE_FROM_PERSENT(-0.465f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.143f, persent) + x_pos,VALUE_FROM_PERSENT( -0.39f, persent) + y_pos);
            }
            glEnd();


            /*
                Lines to display division between parts of stem
            */
            glColor3f(0.5f, 0.2f, 0.0f);
            glLineWidth(3.0f);
            {

                glBegin(GL_LINES); // Division 1
                {
                    glVertex2f(VALUE_FROM_PERSENT(0.10f, persent) + x_pos, VALUE_FROM_PERSENT(-0.03f, persent) + y_pos);
                    glVertex2f(VALUE_FROM_PERSENT(0.13f, persent) + x_pos, VALUE_FROM_PERSENT(-0.03f, persent) + y_pos);
                }
                glEnd();


                glBegin(GL_LINES); // Division 2
                {
                    glVertex2f(VALUE_FROM_PERSENT(0.10f, persent) + x_pos, VALUE_FROM_PERSENT(-0.07f, persent) + y_pos);
                    glVertex2f(VALUE_FROM_PERSENT(0.13f, persent) + x_pos, VALUE_FROM_PERSENT(-0.07f, persent) + y_pos);
                }
                glEnd();


                glBegin(GL_LINES); // Division 3
                {
                    glVertex2f(VALUE_FROM_PERSENT(0.10f, persent) + x_pos, VALUE_FROM_PERSENT(-0.12f, persent) + y_pos);
                    glVertex2f(VALUE_FROM_PERSENT(0.135f, persent) + x_pos,VALUE_FROM_PERSENT(-0.12f, persent) + y_pos);
                }
                glEnd();


                glBegin(GL_LINES); // Division 4
                {
                    glVertex2f(VALUE_FROM_PERSENT(0.095f, persent) + x_pos,VALUE_FROM_PERSENT( -0.17f, persent) + y_pos);
                    glVertex2f(VALUE_FROM_PERSENT(0.15f, persent) + x_pos, VALUE_FROM_PERSENT(-0.17f, persent) + y_pos);
                }
                glEnd();


                glBegin(GL_LINES); // Division 5
                {
                    glVertex2f(VALUE_FROM_PERSENT(0.103f, persent) + x_pos,VALUE_FROM_PERSENT( -0.235f, persent) + y_pos);
                    glVertex2f(VALUE_FROM_PERSENT(0.143f, persent) + x_pos,VALUE_FROM_PERSENT( -0.235f, persent) + y_pos);
                }
                glEnd();

                glBegin(GL_LINES); // Division 6
                {
                    glVertex2f(VALUE_FROM_PERSENT(0.095f, persent) + x_pos,VALUE_FROM_PERSENT( -0.315f, persent) + y_pos);
                    glVertex2f(VALUE_FROM_PERSENT(0.143f, persent) + x_pos,VALUE_FROM_PERSENT( -0.315f, persent) + y_pos);
                }
                glEnd();


                glBegin(GL_LINES); // Division 7
                {
                    glVertex2f(VALUE_FROM_PERSENT(0.095f, persent) + x_pos,VALUE_FROM_PERSENT( -0.39f, persent) + y_pos);
                    glVertex2f(VALUE_FROM_PERSENT(0.143f, persent) + x_pos,VALUE_FROM_PERSENT( -0.39f, persent) + y_pos);
                }
                glEnd();


                glBegin(GL_LINES); // Division 8
                {
                    glVertex2f(VALUE_FROM_PERSENT(0.09f, persent) + x_pos, VALUE_FROM_PERSENT(-0.465f, persent) + y_pos);
                    glVertex2f(VALUE_FROM_PERSENT(0.15f, persent) + x_pos, VALUE_FROM_PERSENT(-0.465f, persent) + y_pos);
                }
                glEnd();
            }


            glLineWidth(1.0f); // Back to Default Value
        }


        /*
            Leaves of a Coconut Tree
        */
        glColor3f(0.5f, 0.8f, 0.1f);
        {
            glBegin(GL_POLYGON); // Leaf 1
            {
                glVertex2f(VALUE_FROM_PERSENT(0.10f, persent) + x_pos, VALUE_FROM_PERSENT(0.01f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.0f , persent)+ x_pos,  VALUE_FROM_PERSENT(0.0f  , persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(-0.07f, persent) + x_pos,VALUE_FROM_PERSENT(-0.06f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(-0.01f, persent) + x_pos,VALUE_FROM_PERSENT(-0.06f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.01f, persent) + x_pos, VALUE_FROM_PERSENT(-0.03f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.02f, persent) + x_pos, VALUE_FROM_PERSENT(-0.06f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.06f, persent) + x_pos, VALUE_FROM_PERSENT(-0.05f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.06f, persent) + x_pos, VALUE_FROM_PERSENT(-0.01f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.08f, persent) + x_pos, VALUE_FROM_PERSENT(-0.03f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.10f, persent) + x_pos, VALUE_FROM_PERSENT(0.0f ,  persent) + y_pos);
            }
            glEnd();

            glBegin(GL_POLYGON); // Leaf 2
            {
                glVertex2f(VALUE_FROM_PERSENT(0.11f, persent) + x_pos, VALUE_FROM_PERSENT(0.01f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.04f, persent) + x_pos, VALUE_FROM_PERSENT(0.07f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.07f, persent) + x_pos, VALUE_FROM_PERSENT(0.08f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.01f, persent) + x_pos, VALUE_FROM_PERSENT(0.06f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.03f, persent) + x_pos, VALUE_FROM_PERSENT(0.09f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.01f, persent) + x_pos, VALUE_FROM_PERSENT(0.14f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.04f, persent) + x_pos, VALUE_FROM_PERSENT(0.15f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.01f, persent) + x_pos, VALUE_FROM_PERSENT(0.16f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.0f , persent) + x_pos,  VALUE_FROM_PERSENT(0.21f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.07f, persent) + x_pos, VALUE_FROM_PERSENT(0.19f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.07f, persent) + x_pos, VALUE_FROM_PERSENT(0.15f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.09f, persent) + x_pos, VALUE_FROM_PERSENT(0.17f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.10f, persent) + x_pos, VALUE_FROM_PERSENT(0.14f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.10f, persent) + x_pos, VALUE_FROM_PERSENT(0.09f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.12f, persent) + x_pos, VALUE_FROM_PERSENT(0.11f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.12f, persent) + x_pos, VALUE_FROM_PERSENT(0.02f , persent)+ y_pos);
            }
            glEnd();

            glBegin(GL_POLYGON); // Leaf 3
            {
                glVertex2f(VALUE_FROM_PERSENT(0.11f, persent) + x_pos, VALUE_FROM_PERSENT(0.04f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.20f, persent) + x_pos, VALUE_FROM_PERSENT(0.13f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.29f, persent) + x_pos, VALUE_FROM_PERSENT(0.12f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.24f, persent) + x_pos, VALUE_FROM_PERSENT(0.09f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.21f, persent) + x_pos, VALUE_FROM_PERSENT(0.11f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.20f, persent) + x_pos, VALUE_FROM_PERSENT(0.08f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.18f, persent) + x_pos, VALUE_FROM_PERSENT(0.06f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.16f, persent) + x_pos, VALUE_FROM_PERSENT(0.06f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.16f, persent) + x_pos, VALUE_FROM_PERSENT(0.04f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.14f, persent) + x_pos, VALUE_FROM_PERSENT(0.03f , persent)+ y_pos);
            }
            glEnd();

        glBegin(GL_POLYGON); // Leaf 4
            {
                glVertex2f(VALUE_FROM_PERSENT(0.13f, persent) + x_pos, VALUE_FROM_PERSENT(0.04f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.25f, persent) + x_pos, VALUE_FROM_PERSENT(0.01f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.29f, persent) + x_pos, VALUE_FROM_PERSENT(-0.09f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.24f, persent) + x_pos, VALUE_FROM_PERSENT(-0.07f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.22f, persent) + x_pos, VALUE_FROM_PERSENT(-0.03f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.18f, persent) + x_pos, VALUE_FROM_PERSENT(-0.04f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERSENT(0.14f, persent) + x_pos, VALUE_FROM_PERSENT(-0.01f, persent) + y_pos);
            }
            glEnd();
        }

        /*
            Coconut on Straight coconut Tree
        */
        glColor3f(0.4f, 0.1f, 0.0f);
        {
            glEnable(GL_POINT_SMOOTH);
            glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
            glPointSize(15.0f);

            glBegin(GL_POINTS); // Coconut 1
            {
                glVertex2f(VALUE_FROM_PERSENT(0.10f, persent) + x_pos, VALUE_FROM_PERSENT(-0.02f , persent)+ y_pos);
            }
            glEnd();


            glBegin(GL_POINTS); // Coconut 2
            {
                glVertex2f(VALUE_FROM_PERSENT(0.13f, persent) + x_pos, VALUE_FROM_PERSENT(-0.02f , persent)+ y_pos);
            }
            glEnd();

            glPointSize(1.0f); // Back to Default Value
            glDisable(GL_POINT_SMOOTH); // Back to Default Style of Point
        }     
}