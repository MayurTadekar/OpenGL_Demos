// header file
#include <GL/freeglut.h>


extern void Swati_astro(float x_pos, float y_pos, float percent, float FadeFactor);
extern void Swati_medi(float x_pos, float y_pos, float percent, float FadeFactor);
extern void Swati_comp(float x_pos, float y_pos, float percent, float FadeFactor);

void Swati_astro(float x_pos, float y_pos, float percent, float FadeFactor)
{
    //A
    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(-0.36f , percent) + x_pos, VALUE_FROM_PERCENT( 0.5f , percent) + y_pos, -0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.42f , percent) + x_pos, VALUE_FROM_PERCENT( 0.5f , percent) + y_pos, -0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.48f , percent) + x_pos, VALUE_FROM_PERCENT( 0.3f , percent) + y_pos, -0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.44f , percent) + x_pos, VALUE_FROM_PERCENT( 0.3f , percent) + y_pos, -0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(-0.41f , percent) + x_pos, VALUE_FROM_PERCENT( 0.38f , percent) + y_pos, -0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.36f , percent) + x_pos, VALUE_FROM_PERCENT( 0.38f , percent) + y_pos, -0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.34f , percent) + x_pos, VALUE_FROM_PERCENT( 0.34f , percent) + y_pos, -0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.42f , percent) + x_pos, VALUE_FROM_PERCENT( 0.34f , percent) + y_pos, -0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(-0.36f , percent) + x_pos, VALUE_FROM_PERCENT( 0.5f , percent) + y_pos, -0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.28f , percent) + x_pos, VALUE_FROM_PERCENT( 0.3f , percent) + y_pos, -0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.32f , percent) + x_pos, VALUE_FROM_PERCENT( 0.3f , percent) + y_pos, -0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.384f , percent) + x_pos, VALUE_FROM_PERCENT( 0.44f , percent) + y_pos, -0.0f);
    glEnd();

    //s

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(-0.28f , percent) + x_pos, VALUE_FROM_PERCENT( 0.5f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.28f , percent) + x_pos, VALUE_FROM_PERCENT( 0.46f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.14f , percent) + x_pos, VALUE_FROM_PERCENT( 0.46f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.14f , percent) + x_pos, VALUE_FROM_PERCENT( 0.5f , percent) + y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(-0.14f , percent) + x_pos, VALUE_FROM_PERCENT( 0.34f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.14f , percent) + x_pos, VALUE_FROM_PERCENT( 0.3f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.28f , percent) + x_pos, VALUE_FROM_PERCENT( 0.3f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.28f , percent) + x_pos, VALUE_FROM_PERCENT( 0.34f , percent) + y_pos, 0.0f);
    glEnd();


    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(-0.28f, percent) + x_pos, VALUE_FROM_PERCENT(0.46f, percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.24f, percent) + x_pos, VALUE_FROM_PERCENT(0.46f, percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.24f, percent) + x_pos, VALUE_FROM_PERCENT(0.38f, percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.28f, percent) + x_pos, VALUE_FROM_PERCENT(0.38f, percent) + y_pos, 0.0f);
    glEnd();


    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(-0.24f, percent) + x_pos, VALUE_FROM_PERCENT(0.38f, percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.18f, percent) + x_pos, VALUE_FROM_PERCENT(0.38f, percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.18f, percent) + x_pos, VALUE_FROM_PERCENT(0.42f, percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.24f, percent) + x_pos, VALUE_FROM_PERCENT(0.42f, percent) + y_pos, 0.0f);
    glEnd();


    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(-0.14f, percent) + x_pos, VALUE_FROM_PERCENT(0.42f, percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.18f, percent) + x_pos, VALUE_FROM_PERCENT(0.42f, percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.18f, percent) + x_pos, VALUE_FROM_PERCENT(0.34f, percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.14f, percent) + x_pos, VALUE_FROM_PERCENT(0.34f, percent) + y_pos, 0.0f);
    glEnd();

    //T
    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(-0.1f , percent) + x_pos, VALUE_FROM_PERCENT( 0.5f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.1f , percent) + x_pos, VALUE_FROM_PERCENT( 0.46f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.06f , percent) + x_pos, VALUE_FROM_PERCENT( 0.46f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.06f , percent) + x_pos, VALUE_FROM_PERCENT( 0.5f , percent) + y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(-0.04f , percent) + x_pos, VALUE_FROM_PERCENT( 0.46f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.0f , percent) + x_pos, VALUE_FROM_PERCENT( 0.46f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.0f , percent) + x_pos, VALUE_FROM_PERCENT( 0.3f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.04f , percent) + x_pos, VALUE_FROM_PERCENT( 0.3f , percent) + y_pos, 0.0f);
    glEnd();

    //R
    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(0.1f , percent) + x_pos, VALUE_FROM_PERCENT( 0.5f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.14f , percent) + x_pos, VALUE_FROM_PERCENT( 0.5f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.14f , percent) + x_pos, VALUE_FROM_PERCENT( 0.3f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.1f , percent) + x_pos, VALUE_FROM_PERCENT( 0.3f , percent) + y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(0.14f , percent) + x_pos, VALUE_FROM_PERCENT( 0.46f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.14f , percent) + x_pos, VALUE_FROM_PERCENT( 0.5f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.24f , percent) + x_pos, VALUE_FROM_PERCENT( 0.5f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.24f , percent) + x_pos, VALUE_FROM_PERCENT( 0.46f , percent) + y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(0.2f , percent) + x_pos, VALUE_FROM_PERCENT( 0.46f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.2f , percent) + x_pos, VALUE_FROM_PERCENT( 0.44f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.24f , percent) + x_pos, VALUE_FROM_PERCENT( 0.44f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.24f , percent) + x_pos, VALUE_FROM_PERCENT( 0.46f , percent) + y_pos, 0.0f);
    glEnd();


    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(0.14f , percent) + x_pos, VALUE_FROM_PERCENT( 0.44f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.14f , percent) + x_pos, VALUE_FROM_PERCENT( 0.4f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.24f , percent) + x_pos, VALUE_FROM_PERCENT( 0.4f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.24f , percent) + x_pos, VALUE_FROM_PERCENT( 0.44f , percent) + y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(0.18f , percent) + x_pos, VALUE_FROM_PERCENT( 0.4f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.14f , percent) + x_pos, VALUE_FROM_PERCENT( 0.4f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.2f , percent) + x_pos, VALUE_FROM_PERCENT( 0.3f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.24f , percent) + x_pos, VALUE_FROM_PERCENT( 0.3f , percent) + y_pos, 0.0f);
    glEnd();

    //o
    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(0.28f , percent) + x_pos, VALUE_FROM_PERCENT( 0.5f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.4f , percent) + x_pos, VALUE_FROM_PERCENT( 0.5f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.4f , percent) + x_pos, VALUE_FROM_PERCENT( 0.46f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.28f , percent) + x_pos, VALUE_FROM_PERCENT( 0.46f , percent) + y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(0.28f , percent) + x_pos, VALUE_FROM_PERCENT( 0.46f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.32f , percent) + x_pos, VALUE_FROM_PERCENT( 0.46f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.32f , percent) + x_pos, VALUE_FROM_PERCENT( 0.34f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.28f , percent) + x_pos, VALUE_FROM_PERCENT( 0.34f , percent) + y_pos, 0.0f);
    glEnd();


    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(0.28f , percent) + x_pos, VALUE_FROM_PERCENT( 0.34f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.28f , percent) + x_pos, VALUE_FROM_PERCENT( 0.3f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.4f , percent) + x_pos, VALUE_FROM_PERCENT( 0.3f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.4f , percent) + x_pos, VALUE_FROM_PERCENT( 0.34f , percent) + y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(0.36f , percent) + x_pos, VALUE_FROM_PERCENT( 0.34f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.4f , percent) + x_pos, VALUE_FROM_PERCENT( 0.34f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.4f , percent) + x_pos, VALUE_FROM_PERCENT( 0.46f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.36f , percent) + x_pos, VALUE_FROM_PERCENT( 0.46f , percent) + y_pos, 0.0f);
    glEnd();


    // moon spots on astro 

    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

    glPointSize(12.0f);
    glBegin(GL_POINTS);
    {

        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.4f, percent) + x_pos, VALUE_FROM_PERCENT(0.46f, percent) + y_pos); //1
    }
    glEnd();

    glPointSize(5.0f);
    glBegin(GL_POINTS);
    {
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.44f, percent) + x_pos, VALUE_FROM_PERCENT(0.36f, percent) + y_pos); //2
    }
    glEnd();

    glPointSize(9.0f);
    glBegin(GL_POINTS);
    {

        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.38f, percent) + x_pos, VALUE_FROM_PERCENT(0.36f, percent) + y_pos); //3
    }
    glEnd();

    glPointSize(8.0f);
    glBegin(GL_POINTS);
    {
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.36f, percent) + x_pos, VALUE_FROM_PERCENT(0.4f, percent) + y_pos); //4
    }
    glEnd();

    glPointSize(5.0f);
    glBegin(GL_POINTS);
    {
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.3f, percent) + x_pos, VALUE_FROM_PERCENT(0.32f, percent) + y_pos); //5
    }
    glEnd();

    glPointSize(14.0f);
    glBegin(GL_POINTS);
    {
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.2f, percent) + x_pos, VALUE_FROM_PERCENT(0.48f, percent) + y_pos);  //6
    }
    glEnd();

    glPointSize(7.0f);
    glBegin(GL_POINTS);
    {

        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.26f, percent) + x_pos, VALUE_FROM_PERCENT(0.46f, percent) + y_pos); //7
    }
    glEnd();

    glPointSize(6.0f);
    glBegin(GL_POINTS);
    {
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.2f, percent) + x_pos, VALUE_FROM_PERCENT(0.4f, percent) + y_pos);  //8
    }
    glEnd();

    // glPointSize(8.0f);
    // glBegin(GL_POINTS);
    // {

    //     glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
    //     glVertex2f(VALUE_FROM_PERCENT(-0.14f, percent) + x_pos, VALUE_FROM_PERCENT(0.32f, percent) + y_pos);  //9
    // }
    // glEnd();

    glPointSize(4.0f);
    glBegin(GL_POINTS);
    {

        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.22f, percent) + x_pos, VALUE_FROM_PERCENT(0.32f, percent) + y_pos);  //10
    }
    glEnd();

    glPointSize(9.0f);
    glBegin(GL_POINTS);
    {
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.48f, percent) + y_pos);  //11
    }
    glEnd();

    glPointSize(7.0f);
    glBegin(GL_POINTS);
    {

        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.48f, percent) + y_pos);  //12
    }
    glEnd();

    glPointSize(2.0f);
    glBegin(GL_POINTS);
    {

        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.02f, percent) + x_pos, VALUE_FROM_PERCENT(0.38f, percent) + y_pos);  //13
    }
    glEnd();

    glPointSize(6.0f);
    glBegin(GL_POINTS);
    {

        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.02f, percent) + x_pos, VALUE_FROM_PERCENT(0.32f, percent) + y_pos);  //14
    }
    glEnd();

    glPointSize(4.0f);
    glBegin(GL_POINTS);
    {

        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(0.12f, percent) + x_pos, VALUE_FROM_PERCENT(0.48f, percent) + y_pos);  //15
    }
    glEnd();

    glPointSize(8.0f);
    glBegin(GL_POINTS);
    {

        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(0.12f, percent) + x_pos, VALUE_FROM_PERCENT(0.36f, percent) + y_pos);  //16
    }
    glEnd();

    glPointSize(9.0f);
    glBegin(GL_POINTS);
    {

        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(0.2f, percent) + x_pos, VALUE_FROM_PERCENT(0.48f, percent) + y_pos);  //17
    }
    glEnd();

    glPointSize(11.0f);
    glBegin(GL_POINTS);
    {

        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(0.2f, percent) + x_pos, VALUE_FROM_PERCENT(0.42f, percent) + y_pos);  //18
    }
    glEnd();

    glPointSize(3.0f);
    glBegin(GL_POINTS);
    {
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(0.2f, percent) + x_pos, VALUE_FROM_PERCENT(0.34f, percent) + y_pos);  //19
    }
    glEnd();

    glPointSize(10.0f);
    glBegin(GL_POINTS);
    {

        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(0.48f, percent) + y_pos);  //20
    }
    glEnd();

    glPointSize(7.0f);
    glBegin(GL_POINTS);
    {
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(0.32f, percent) + y_pos);  //21
    }
    glEnd();

    glPointSize(5.0f);
    glBegin(GL_POINTS);
    {

        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(0.38f, percent) + x_pos, VALUE_FROM_PERCENT(0.48f, percent) + y_pos);  //22
    }
    glEnd();

    glPointSize(4.0f);
    glBegin(GL_POINTS);
    {

        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(0.38f, percent) + x_pos, VALUE_FROM_PERCENT(0.4f, percent) + y_pos);  //23
    }
    glEnd();
    glPointSize(1.0f);
    glDisable(GL_POINT_SMOOTH);



}

void Swati_medi(float x_pos, float y_pos, float percent, float FadeFactor)
{

    //E
    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(-0.16f , percent) + x_pos, VALUE_FROM_PERCENT( 0.1f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.16f , percent) + x_pos, VALUE_FROM_PERCENT( 0.06f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.04f , percent) + x_pos, VALUE_FROM_PERCENT( 0.06f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.04f , percent) + x_pos, VALUE_FROM_PERCENT( 0.1f , percent) + y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(-0.12f , percent) + x_pos, VALUE_FROM_PERCENT( 0.06f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.16f , percent) + x_pos, VALUE_FROM_PERCENT( 0.06f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.16f , percent) + x_pos, VALUE_FROM_PERCENT( -0.06f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.12f , percent) + x_pos, VALUE_FROM_PERCENT( -0.06f , percent) + y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(-0.16f , percent) + x_pos, VALUE_FROM_PERCENT( -0.06f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.16f , percent) + x_pos, VALUE_FROM_PERCENT( -0.1f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.04f , percent) + x_pos, VALUE_FROM_PERCENT( -0.1f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.04f , percent) + x_pos, VALUE_FROM_PERCENT( -0.06f , percent) + y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(-0.12f , percent) + x_pos, VALUE_FROM_PERCENT( 0.02f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.12f , percent) + x_pos, VALUE_FROM_PERCENT(-0.02f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.04f , percent) + x_pos, VALUE_FROM_PERCENT(-0.02f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.04f , percent) + x_pos, VALUE_FROM_PERCENT( 0.02f , percent) + y_pos, 0.0f);
    glEnd();

    //D
    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(0.04f , percent) + x_pos, VALUE_FROM_PERCENT( 0.06f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.04f , percent) + x_pos, VALUE_FROM_PERCENT( 0.1f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.1f , percent) + x_pos, VALUE_FROM_PERCENT( 0.1f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.1f , percent) + x_pos, VALUE_FROM_PERCENT( 0.06f , percent) + y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(0.04f , percent) + x_pos, VALUE_FROM_PERCENT( -0.06f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.04f , percent) + x_pos, VALUE_FROM_PERCENT( -0.1f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.1f , percent) + x_pos, VALUE_FROM_PERCENT( -0.1f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.1f , percent) + x_pos, VALUE_FROM_PERCENT( -0.06f , percent) + y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(0.04f , percent) + x_pos, VALUE_FROM_PERCENT( -0.1f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.0f , percent) + x_pos, VALUE_FROM_PERCENT( -0.1f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.0f , percent) + x_pos, VALUE_FROM_PERCENT( 0.1f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.04f , percent) + x_pos, VALUE_FROM_PERCENT( 0.1f , percent) + y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(0.1f, percent) + x_pos, VALUE_FROM_PERCENT(0.1f, percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.1f, percent) + x_pos, VALUE_FROM_PERCENT(0.06f, percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.12f, percent) + x_pos, VALUE_FROM_PERCENT(0.04f, percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.16f, percent) + x_pos, VALUE_FROM_PERCENT(0.04f, percent) + y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(0.12f, percent) + x_pos, VALUE_FROM_PERCENT(0.04f, percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.16f, percent) + x_pos, VALUE_FROM_PERCENT(0.04f, percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.16f, percent) + x_pos, VALUE_FROM_PERCENT(-0.04f, percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.12f, percent) + x_pos, VALUE_FROM_PERCENT(-0.04f, percent) + y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(0.12f, percent) + x_pos, VALUE_FROM_PERCENT(-0.04f, percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.16f, percent) + x_pos, VALUE_FROM_PERCENT(-0.04f, percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.1f, percent) + x_pos, VALUE_FROM_PERCENT(-0.1f, percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.1f, percent) + x_pos, VALUE_FROM_PERCENT(-0.06f, percent) + y_pos, 0.0f);
    glEnd();

    //I
    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(0.18f , percent) + x_pos, VALUE_FROM_PERCENT( 0.1f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.18f , percent) + x_pos, VALUE_FROM_PERCENT( 0.06f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.32f , percent) + x_pos, VALUE_FROM_PERCENT( 0.06f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.32f , percent) + x_pos, VALUE_FROM_PERCENT( 0.1f , percent) + y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(0.22f , percent) + x_pos, VALUE_FROM_PERCENT( 0.06f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.22f , percent) + x_pos, VALUE_FROM_PERCENT( -0.06f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.26f , percent) + x_pos, VALUE_FROM_PERCENT( -0.06f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.26f , percent) + x_pos, VALUE_FROM_PERCENT( 0.06f , percent) + y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(0.18f , percent) + x_pos, VALUE_FROM_PERCENT( -0.06f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.18f , percent) + x_pos, VALUE_FROM_PERCENT( -0.1f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.32f , percent) + x_pos, VALUE_FROM_PERCENT( -0.1f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.32f , percent) + x_pos, VALUE_FROM_PERCENT( -0.06f , percent) + y_pos, 0.0f);
    glEnd();

    //M
    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(-0.36f , percent) + x_pos, VALUE_FROM_PERCENT( 0.1f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.32f , percent) + x_pos, VALUE_FROM_PERCENT( 0.1f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.32f , percent) + x_pos, VALUE_FROM_PERCENT( -0.1f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.36f , percent) + x_pos, VALUE_FROM_PERCENT( -0.1f , percent) + y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(-0.32f , percent) + x_pos, VALUE_FROM_PERCENT( 0.1f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.32f , percent) + x_pos, VALUE_FROM_PERCENT( 0.04f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.28f , percent) + x_pos, VALUE_FROM_PERCENT( 0.02f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.28f , percent) + x_pos, VALUE_FROM_PERCENT( 0.06f , percent) + y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(-0.28f , percent) + x_pos, VALUE_FROM_PERCENT( 0.02f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.28f , percent) + x_pos, VALUE_FROM_PERCENT( 0.06f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.24f , percent) + x_pos, VALUE_FROM_PERCENT( 0.1f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.24f , percent) + x_pos, VALUE_FROM_PERCENT( 0.04f , percent) + y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(-0.24f , percent) + x_pos, VALUE_FROM_PERCENT( 0.1f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.2f , percent) + x_pos, VALUE_FROM_PERCENT( 0.1f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.2f , percent) + x_pos, VALUE_FROM_PERCENT( -0.1f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.24f , percent) + x_pos, VALUE_FROM_PERCENT( -0.1f , percent) + y_pos, 0.0f);
    glEnd();


    // moon spot on text

    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

    glPointSize(12.0f);
    glBegin(GL_POINTS);
    {

        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.32f, percent) + x_pos, VALUE_FROM_PERCENT(0.06f, percent) + y_pos); //1
    }
    glEnd();

    glPointSize(5.0f);
    glBegin(GL_POINTS);
    {
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.34f, percent) + x_pos, VALUE_FROM_PERCENT(-0.06f, percent) + y_pos);  //2
    }
    glEnd();

    glPointSize(9.0f);
    glBegin(GL_POINTS);
    {

        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.22f, percent) + x_pos, VALUE_FROM_PERCENT(0.06f, percent) + y_pos);  //3
    }
    glEnd();

    glPointSize(8.0f);
    glBegin(GL_POINTS);
    {
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.22f, percent) + x_pos, VALUE_FROM_PERCENT(-0.06f, percent) + y_pos); //4
    }
    glEnd();

    glPointSize(5.0f);
    glBegin(GL_POINTS);
    {
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.28f, percent) + x_pos, VALUE_FROM_PERCENT(0.04f, percent) + y_pos); //5
    }
    glEnd();

    glPointSize(14.0f);
    glBegin(GL_POINTS);
    {
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.1f, percent) + x_pos, VALUE_FROM_PERCENT(0.08f, percent) + y_pos); //6
    }
    glEnd();

    glPointSize(7.0f);
    glBegin(GL_POINTS);
    {

        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.1f, percent) + x_pos, VALUE_FROM_PERCENT(-0.08f, percent) + y_pos); //7
    }
    glEnd();

    glPointSize(6.0f);
    glBegin(GL_POINTS);
    {
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos); //8
    }
    glEnd();

    glPointSize(8.0f);
    glBegin(GL_POINTS);
    {

        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.14f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos); //9
    }
    glEnd();

    glPointSize(4.0f);
    glBegin(GL_POINTS);
    {

        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos, VALUE_FROM_PERCENT(0.08f, percent) + y_pos);  //10
    }
    glEnd();

    glPointSize(9.0f);
    glBegin(GL_POINTS);
    {
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos);  //11
    }
    glEnd();

    glPointSize(7.0f);
    glBegin(GL_POINTS);
    {

        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos, VALUE_FROM_PERCENT(-0.08f, percent) + y_pos);  //12
    }
    glEnd();

    glPointSize(2.0f);
    glBegin(GL_POINTS);
    {

        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(0.1f, percent) + x_pos, VALUE_FROM_PERCENT(0.08f, percent) + y_pos);  //13
    }
    glEnd();

    glPointSize(6.0f);
    glBegin(GL_POINTS);
    {

        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(0.1f, percent) + x_pos, VALUE_FROM_PERCENT(-0.08f, percent) + y_pos);  //14
    }
    glEnd();

    glPointSize(4.0f);
    glBegin(GL_POINTS);
    {

        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.12f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos); //15
    }
    glEnd();

    glPointSize(8.0f);
    glBegin(GL_POINTS);
    {

        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(0.24f, percent) + x_pos, VALUE_FROM_PERCENT(0.08f, percent) + y_pos);  //16
    }
    glEnd();

    glPointSize(9.0f);
    glBegin(GL_POINTS);
    {

        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(0.24f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos);  //17
    }
    glEnd();

    glPointSize(11.0f);
    glBegin(GL_POINTS);
    {

        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(0.08f, percent) + y_pos);  //18
    }
    glEnd();

    glPointSize(3.0f);
    glBegin(GL_POINTS);
    {
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(0.26f, percent) + x_pos, VALUE_FROM_PERCENT(-0.08f, percent) + y_pos);  //19
    }
    glEnd();

    glPointSize(10.0f);
    glBegin(GL_POINTS);
    {

        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(0.2f, percent) + x_pos, VALUE_FROM_PERCENT(-0.08f, percent) + y_pos);  //20
    }
    glEnd();

   
    glPointSize(1.0f);
    glDisable(GL_POINT_SMOOTH);

}
void Swati_comp(float x_pos, float y_pos, float percent, float FadeFactor)
{

    //C 
    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(-0.26f , percent) + x_pos, VALUE_FROM_PERCENT( -0.2f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.26f , percent) + x_pos, VALUE_FROM_PERCENT( -0.24f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.36f , percent) + x_pos, VALUE_FROM_PERCENT( -0.24f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.36f , percent) + x_pos, VALUE_FROM_PERCENT( -0.2f , percent) + y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(-0.32f , percent) + x_pos, VALUE_FROM_PERCENT( -0.24f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.36f , percent) + x_pos, VALUE_FROM_PERCENT( -0.24f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.36f , percent) + x_pos, VALUE_FROM_PERCENT( -0.36f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.32f , percent) + x_pos, VALUE_FROM_PERCENT( -0.36f , percent) + y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(-0.36f , percent) + x_pos, VALUE_FROM_PERCENT( -0.36f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.36f , percent) + x_pos, VALUE_FROM_PERCENT( -0.4f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.26f , percent) + x_pos, VALUE_FROM_PERCENT( -0.4f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.26f , percent) + x_pos, VALUE_FROM_PERCENT( -0.36f , percent) + y_pos, 0.0f);
    glEnd();

    //p
    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(0.18f , percent) + x_pos, VALUE_FROM_PERCENT( -0.2f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.14f , percent) + x_pos, VALUE_FROM_PERCENT( -0.2f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.14f , percent) + x_pos, VALUE_FROM_PERCENT( -0.4f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.18f , percent) + x_pos, VALUE_FROM_PERCENT( -0.4f , percent) + y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(0.18f , percent) + x_pos, VALUE_FROM_PERCENT( -0.2f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.18f , percent) + x_pos, VALUE_FROM_PERCENT( -0.24f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.28f , percent) + x_pos, VALUE_FROM_PERCENT( -0.24f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.28f , percent) + x_pos, VALUE_FROM_PERCENT( -0.2f , percent) + y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(0.28f , percent) + x_pos, VALUE_FROM_PERCENT( -0.24f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.28f , percent) + x_pos, VALUE_FROM_PERCENT( -0.28f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.24f , percent) + x_pos, VALUE_FROM_PERCENT( -0.28f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.24f , percent) + x_pos, VALUE_FROM_PERCENT( -0.24f , percent) + y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(0.18f , percent) + x_pos, VALUE_FROM_PERCENT( -0.28f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.18f , percent) + x_pos, VALUE_FROM_PERCENT( -0.32f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.28f , percent) + x_pos, VALUE_FROM_PERCENT( -0.32f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.28f , percent) + x_pos, VALUE_FROM_PERCENT( -0.28f , percent) + y_pos, 0.0f);
    glEnd();

   
    //M
    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(-0.02f , percent) + x_pos, VALUE_FROM_PERCENT( -0.2f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.06f , percent) + x_pos, VALUE_FROM_PERCENT( -0.2f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.06f , percent) + x_pos, VALUE_FROM_PERCENT( -0.4f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.02f , percent) + x_pos, VALUE_FROM_PERCENT( -0.4f , percent) + y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(-0.02f , percent) + x_pos, VALUE_FROM_PERCENT( -0.2f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.02f , percent) + x_pos, VALUE_FROM_PERCENT( -0.26f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.02f , percent) + x_pos, VALUE_FROM_PERCENT( -0.3f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.02f , percent) + x_pos, VALUE_FROM_PERCENT( -0.24f , percent) + y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(0.02f , percent) + x_pos, VALUE_FROM_PERCENT( -0.3f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.02f , percent) + x_pos, VALUE_FROM_PERCENT( -0.24f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.06f , percent) + x_pos, VALUE_FROM_PERCENT( -0.2f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.06f , percent) + x_pos, VALUE_FROM_PERCENT( -0.24f , percent) + y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(0.06f , percent) + x_pos, VALUE_FROM_PERCENT( -0.2f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.06f , percent) + x_pos, VALUE_FROM_PERCENT( -0.4f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.1f , percent) + x_pos, VALUE_FROM_PERCENT( -0.4f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.1f , percent) + x_pos, VALUE_FROM_PERCENT( -0.2f , percent) + y_pos, 0.0f);
    glEnd();
   
    //O
    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(-0.22f , percent) + x_pos, VALUE_FROM_PERCENT( -0.2f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.22f , percent) + x_pos, VALUE_FROM_PERCENT( -0.24f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.1f , percent) + x_pos, VALUE_FROM_PERCENT( -0.24f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.1f , percent) + x_pos, VALUE_FROM_PERCENT( -0.2f , percent) + y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(-0.22f , percent) + x_pos, VALUE_FROM_PERCENT( -0.24f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.18f , percent) + x_pos, VALUE_FROM_PERCENT( -0.24f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.18f , percent) + x_pos, VALUE_FROM_PERCENT( -0.36f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.22f , percent) + x_pos, VALUE_FROM_PERCENT( -0.36f , percent) + y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(-0.1f , percent) + x_pos, VALUE_FROM_PERCENT( -0.24f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.14f , percent) + x_pos, VALUE_FROM_PERCENT( -0.24f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.14f , percent) + x_pos, VALUE_FROM_PERCENT( -0.36f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.1f , percent) + x_pos, VALUE_FROM_PERCENT( -0.36f , percent) + y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(-0.1f , percent) + x_pos, VALUE_FROM_PERCENT( -0.36f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.1f , percent) + x_pos, VALUE_FROM_PERCENT( -0.4f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.22f , percent) + x_pos, VALUE_FROM_PERCENT( -0.4f , percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.22f , percent) + x_pos, VALUE_FROM_PERCENT( -0.36f , percent) + y_pos, 0.0f);
    glEnd();

    //moon spot on text

    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

    glPointSize(12.0f);
    glBegin(GL_POINTS);
    {

        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.3f, percent) + x_pos, VALUE_FROM_PERCENT(-0.22f, percent) + y_pos); //1
    }
    glEnd();

    glPointSize(5.0f);
    glBegin(GL_POINTS);
    {
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.3f, percent) + x_pos, VALUE_FROM_PERCENT(-0.38f, percent) + y_pos);  //2
    }
    glEnd();

    glPointSize(9.0f);
    glBegin(GL_POINTS);
    {

        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.34f, percent) + x_pos, VALUE_FROM_PERCENT(-0.24f, percent) + y_pos);  //3
    }
    glEnd();

    glPointSize(8.0f);
    glBegin(GL_POINTS);
    {
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.34f, percent) + x_pos, VALUE_FROM_PERCENT(-0.32f, percent) + y_pos); //4
    }
    glEnd();

    glPointSize(5.0f);
    glBegin(GL_POINTS);
    {
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.2f, percent) + x_pos, VALUE_FROM_PERCENT(-0.3f, percent) + y_pos); //5
    }
    glEnd();

    glPointSize(14.0f);
    glBegin(GL_POINTS);
    {
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.12f, percent) + x_pos, VALUE_FROM_PERCENT(-0.3f, percent) + y_pos); //6
    }
    glEnd();

    glPointSize(7.0f);
    glBegin(GL_POINTS);
    {

        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.12f, percent) + x_pos, VALUE_FROM_PERCENT(-0.38f, percent) + y_pos); //7
    }
    glEnd();

    glPointSize(6.0f);
    glBegin(GL_POINTS);
    {
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.14f, percent) + x_pos, VALUE_FROM_PERCENT(-0.22f, percent) + y_pos); //8
    }
    glEnd();

    glPointSize(8.0f);
    glBegin(GL_POINTS);
    {

        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.04f, percent) + x_pos, VALUE_FROM_PERCENT(-0.22f, percent) + y_pos); //9
    }
    glEnd();

    glPointSize(4.0f);
    glBegin(GL_POINTS);
    {

        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.04f, percent) + x_pos, VALUE_FROM_PERCENT(-0.3f, percent) + y_pos);  //10
    }
    glEnd();

    glPointSize(9.0f);
    glBegin(GL_POINTS);
    {
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.04f, percent) + x_pos, VALUE_FROM_PERCENT(-0.38f, percent) + y_pos);  //11
    }
    glEnd();

    glPointSize(7.0f);
    glBegin(GL_POINTS);
    {

        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(0.08f, percent) + x_pos, VALUE_FROM_PERCENT(-0.22f, percent) + y_pos);  //12
    }
    glEnd();

    glPointSize(2.0f);
    glBegin(GL_POINTS);
    {

        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(0.08f, percent) + x_pos, VALUE_FROM_PERCENT(-0.3f, percent) + y_pos);  //13
    }
    glEnd();

    glPointSize(6.0f);
    glBegin(GL_POINTS);
    {

        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(0.08f, percent) + x_pos, VALUE_FROM_PERCENT(-0.38f, percent) + y_pos);  //14
    }
    glEnd();

    glPointSize(4.0f);
    glBegin(GL_POINTS);
    {

        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos, VALUE_FROM_PERCENT(-0.26f, percent) + y_pos); //15
    }
    glEnd();

    glPointSize(8.0f);
    glBegin(GL_POINTS);
    {

        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(0.16f, percent) + x_pos, VALUE_FROM_PERCENT(-0.26f, percent) + y_pos);  //16
    }
    glEnd();

    glPointSize(9.0f);
    glBegin(GL_POINTS);
    {

        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(0.16f, percent) + x_pos, VALUE_FROM_PERCENT(-0.36f, percent) + y_pos);  //17
    }
    glEnd();

    glPointSize(11.0f);
    glBegin(GL_POINTS);
    {

        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(0.2f, percent) + x_pos, VALUE_FROM_PERCENT(-0.22f, percent) + y_pos);  //18
    }
    glEnd();

    glPointSize(3.0f);
    glBegin(GL_POINTS);
    {
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(0.26f, percent) + x_pos, VALUE_FROM_PERCENT(-0.22f, percent) + y_pos);  //19
    }
    glEnd();

    glPointSize(10.0f);
    glBegin(GL_POINTS);
    {

        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(0.26f, percent) + x_pos, VALUE_FROM_PERCENT(-0.26f, percent) + y_pos);  //20
    }
    glEnd();

    glPointSize(10.0f);
    glBegin(GL_POINTS);
    {

        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(0.26f, percent) + x_pos, VALUE_FROM_PERCENT(-0.3f, percent) + y_pos);  //21
    }
    glEnd();


    glPointSize(1.0f);
    glDisable(GL_POINT_SMOOTH);

}
