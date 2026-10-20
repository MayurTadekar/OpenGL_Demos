#include <GL/freeglut.h>

extern void Swati_text(float x_pos, float y_pos, float percent, float FadeFactor);
extern void Swati_ure(float x_pos, float y_pos, float percent, float FadeFactor);

void Swati_text(float x_pos, float y_pos, float percent, float FadeFactor)
{
    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(-0.5f , percent) + x_pos , VALUE_FROM_PERCENT( 0.9f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.5f , percent) + x_pos , VALUE_FROM_PERCENT( 0.86f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.66f , percent) + x_pos , VALUE_FROM_PERCENT( 0.86f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.66f , percent) + x_pos , VALUE_FROM_PERCENT( 0.9f , percent) + y_pos , 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(-0.6f , percent) + x_pos , VALUE_FROM_PERCENT( 0.86f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.56f , percent) + x_pos , VALUE_FROM_PERCENT( 0.86f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.56f , percent) + x_pos , VALUE_FROM_PERCENT( 0.7f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.6f , percent) + x_pos , VALUE_FROM_PERCENT( 0.7f , percent) + y_pos , 0.0f);
    glEnd();

    // E

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(-0.32f , percent) + x_pos , VALUE_FROM_PERCENT( 0.9f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.42f , percent) + x_pos , VALUE_FROM_PERCENT( 0.9f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.42f , percent) + x_pos , VALUE_FROM_PERCENT( 0.86f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.32f , percent) + x_pos , VALUE_FROM_PERCENT( 0.86f , percent) + y_pos , 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(-0.42f , percent) + x_pos , VALUE_FROM_PERCENT( 0.9f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.46f , percent) + x_pos , VALUE_FROM_PERCENT( 0.9f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.46f , percent) + x_pos , VALUE_FROM_PERCENT( 0.7f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.42f , percent) + x_pos , VALUE_FROM_PERCENT( 0.7f , percent) + y_pos , 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(-0.42f , percent) + x_pos , VALUE_FROM_PERCENT( 0.74f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.42f , percent) + x_pos , VALUE_FROM_PERCENT( 0.7f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.32f , percent) + x_pos , VALUE_FROM_PERCENT( 0.7f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.32f , percent) + x_pos , VALUE_FROM_PERCENT( 0.74f , percent) + y_pos , 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(-0.42f , percent) + x_pos , VALUE_FROM_PERCENT( 0.82f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.42f , percent) + x_pos , VALUE_FROM_PERCENT( 0.78f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.36f , percent) + x_pos , VALUE_FROM_PERCENT( 0.78f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.36f , percent) + x_pos , VALUE_FROM_PERCENT( 0.82f , percent) + y_pos , 0.0f);
    glEnd();

   //x
    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(-0.19f , percent) + x_pos , VALUE_FROM_PERCENT( 0.77f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.18f , percent) + x_pos , VALUE_FROM_PERCENT( 0.80f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.12f , percent) + x_pos , VALUE_FROM_PERCENT( 0.7f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.16f , percent) + x_pos , VALUE_FROM_PERCENT( 0.7f , percent) + y_pos , 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(-0.24f, percent) + x_pos, VALUE_FROM_PERCENT(0.9f, percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.28f, percent) + x_pos, VALUE_FROM_PERCENT(0.9f, percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.22f, percent) + x_pos, VALUE_FROM_PERCENT(0.8f, percent) + y_pos, 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.2f, percent) + x_pos, VALUE_FROM_PERCENT(0.83f, percent) + y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(-0.11f, percent) + x_pos , VALUE_FROM_PERCENT( 0.9f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.16f, percent) + x_pos , VALUE_FROM_PERCENT( 0.9f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.28f, percent) + x_pos , VALUE_FROM_PERCENT( 0.7f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.24f, percent) + x_pos , VALUE_FROM_PERCENT( 0.7f , percent) + y_pos , 0.0f);
    glEnd();

    // T

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(-0.08f, percent) + x_pos , VALUE_FROM_PERCENT( 0.9f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.08f, percent) + x_pos , VALUE_FROM_PERCENT( 0.86f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.08f, percent) + x_pos , VALUE_FROM_PERCENT( 0.86f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.08f, percent) + x_pos , VALUE_FROM_PERCENT( 0.9f , percent) + y_pos , 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(-0.02f, percent) + x_pos , VALUE_FROM_PERCENT( 0.86f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos , VALUE_FROM_PERCENT( 0.86f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos , VALUE_FROM_PERCENT( 0.7f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(-0.02f, percent) + x_pos , VALUE_FROM_PERCENT( 0.7f , percent) + y_pos , 0.0f);
    glEnd();

    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

    glPointSize(12.0f);
    glBegin(GL_POINTS);
    {

        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.64f, percent) + x_pos, VALUE_FROM_PERCENT(0.88f, percent) + y_pos);
    }
    glEnd();

    glPointSize(5.0f);
    glBegin(GL_POINTS);
    {
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.56f, percent) + x_pos, VALUE_FROM_PERCENT(0.86f, percent) + y_pos);
    }
    glEnd();

    glPointSize(9.0f);
    glBegin(GL_POINTS);
    {
     
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.58f, percent) + x_pos, VALUE_FROM_PERCENT(0.8f, percent) + y_pos);
    }
    glEnd();

    glPointSize(8.0f);
    glBegin(GL_POINTS);
    {
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.58f, percent) + x_pos, VALUE_FROM_PERCENT(0.74f, percent) + y_pos);
    }
    glEnd();

    glPointSize(5.0f);
    glBegin(GL_POINTS);
    {
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.36f, percent) + x_pos, VALUE_FROM_PERCENT(0.88f, percent) + y_pos);
    }
    glEnd();

    glPointSize(7.0f);
    glBegin(GL_POINTS);
    {
    
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.44f, percent) + x_pos, VALUE_FROM_PERCENT(0.84f, percent) + y_pos);
    }
    glEnd();

    glPointSize(6.0f);
    glBegin(GL_POINTS);
    {
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.38f, percent) + x_pos, VALUE_FROM_PERCENT(0.8f, percent) + y_pos);
    }
    glEnd();

    glPointSize(8.0f);
    glBegin(GL_POINTS);
    {
       
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.4f, percent) + x_pos, VALUE_FROM_PERCENT(0.72f, percent) + y_pos);
    }
    glEnd();

    glPointSize(4.0f);
    glBegin(GL_POINTS);
    {

        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.24f, percent) + x_pos, VALUE_FROM_PERCENT(0.86f, percent) + y_pos);
    }
    glEnd();

    glPointSize(9.0f);
    glBegin(GL_POINTS);
    {
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.24f, percent) + x_pos, VALUE_FROM_PERCENT(0.74f, percent) + y_pos);
    }
    glEnd();

    glPointSize(7.0f);
    glBegin(GL_POINTS);
    {
       
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.16f, percent) + x_pos, VALUE_FROM_PERCENT(0.72f, percent) + y_pos);
    }
    glEnd();

    glPointSize(2.0f);
    glBegin(GL_POINTS);
    {
       
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.2f, percent) + x_pos, VALUE_FROM_PERCENT(0.78f, percent) + y_pos);
    }
    glEnd();

    glPointSize(6.0f);
    glBegin(GL_POINTS);
    {
       
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.16f, percent) + x_pos, VALUE_FROM_PERCENT(0.88f, percent) + y_pos);
    }
    glEnd();

    glPointSize(4.0f);
    glBegin(GL_POINTS);
    {
       
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.88f, percent) + y_pos);
    }
    glEnd();

    glPointSize(8.0f);
    glBegin(GL_POINTS);
    {
       
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(0.06f, percent) + x_pos, VALUE_FROM_PERCENT(0.88f, percent) + y_pos);
    }
    glEnd();

    glPointSize(9.0f);
    glBegin(GL_POINTS);
    {
       
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.8f, percent) + y_pos);
    }
    glEnd();

    glDisable(GL_POINT_SMOOTH);
}

void Swati_ure(float x_pos, float y_pos, float percent, float FadeFactor)
{
    // U

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(0.12f, percent) + x_pos , VALUE_FROM_PERCENT( 0.9f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.16f, percent) + x_pos , VALUE_FROM_PERCENT( 0.9f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.16f, percent) + x_pos , VALUE_FROM_PERCENT( 0.7f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.12f, percent) + x_pos , VALUE_FROM_PERCENT( 0.7f , percent) + y_pos , 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(0.16f, percent) + x_pos , VALUE_FROM_PERCENT( 0.74f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.16f, percent) + x_pos , VALUE_FROM_PERCENT( 0.7f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.22f, percent) + x_pos , VALUE_FROM_PERCENT( 0.7f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.22f, percent) + x_pos , VALUE_FROM_PERCENT( 0.74f , percent) + y_pos , 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(0.22f, percent) + x_pos , VALUE_FROM_PERCENT( 0.7f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.22f, percent) + x_pos , VALUE_FROM_PERCENT( 0.9f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.26f, percent) + x_pos , VALUE_FROM_PERCENT( 0.9f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.26f, percent) + x_pos , VALUE_FROM_PERCENT( 0.7f , percent) + y_pos , 0.0f);
    glEnd();

    // R

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos , VALUE_FROM_PERCENT( 0.9f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos , VALUE_FROM_PERCENT( 0.7f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.34f, percent) + x_pos , VALUE_FROM_PERCENT( 0.7f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.34f, percent) + x_pos , VALUE_FROM_PERCENT( 0.9f , percent) + y_pos , 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(0.34f, percent) + x_pos , VALUE_FROM_PERCENT( 0.9f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.34f, percent) + x_pos , VALUE_FROM_PERCENT( 0.86f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.44f, percent) + x_pos , VALUE_FROM_PERCENT( 0.86f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.44f, percent) + x_pos , VALUE_FROM_PERCENT( 0.9f , percent) + y_pos , 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(0.4f, percent) + x_pos , VALUE_FROM_PERCENT( 0.86f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.4f, percent) + x_pos , VALUE_FROM_PERCENT( 0.82f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.44f, percent) + x_pos , VALUE_FROM_PERCENT( 0.82f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.44f, percent) + x_pos , VALUE_FROM_PERCENT( 0.86f , percent) + y_pos , 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(0.44f, percent) + x_pos , VALUE_FROM_PERCENT( 0.82f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.44f, percent) + x_pos , VALUE_FROM_PERCENT( 0.78f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.34f, percent) + x_pos , VALUE_FROM_PERCENT( 0.78f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.34f, percent) + x_pos , VALUE_FROM_PERCENT( 0.82f , percent) + y_pos , 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(0.38f, percent) + x_pos , VALUE_FROM_PERCENT( 0.78f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.34f, percent) + x_pos , VALUE_FROM_PERCENT( 0.78f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.38f, percent) + x_pos , VALUE_FROM_PERCENT( 0.7f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.42f, percent) + x_pos , VALUE_FROM_PERCENT( 0.7f , percent) + y_pos , 0.0f);
    glEnd();

    //E

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(0.46f, percent) + x_pos , VALUE_FROM_PERCENT( 0.9f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.52f, percent) + x_pos , VALUE_FROM_PERCENT( 0.9f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.52f, percent) + x_pos , VALUE_FROM_PERCENT( 0.7f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.46f, percent) + x_pos , VALUE_FROM_PERCENT( 0.7f , percent) + y_pos , 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(0.52f, percent) + x_pos , VALUE_FROM_PERCENT( 0.9f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.6f, percent) + x_pos , VALUE_FROM_PERCENT( 0.9f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.6f, percent) + x_pos , VALUE_FROM_PERCENT( 0.86f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.52f, percent) + x_pos , VALUE_FROM_PERCENT( 0.86f , percent) + y_pos , 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(0.52f, percent) + x_pos , VALUE_FROM_PERCENT( 0.82f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos , VALUE_FROM_PERCENT( 0.82f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos , VALUE_FROM_PERCENT( 0.78f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.52f, percent) + x_pos , VALUE_FROM_PERCENT( 0.78f , percent) + y_pos , 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, FadeFactor);
    glVertex3f(VALUE_FROM_PERCENT(0.52f, percent) + x_pos , VALUE_FROM_PERCENT( 0.74f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.6f, percent) + x_pos , VALUE_FROM_PERCENT( 0.74f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.6f, percent) + x_pos , VALUE_FROM_PERCENT( 0.7f , percent) + y_pos , 0.0f);
    glVertex3f(VALUE_FROM_PERCENT(0.52f, percent) + x_pos , VALUE_FROM_PERCENT( 0.7f , percent) + y_pos , 0.0f);
    glEnd();

    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

    glPointSize(14.0f);
    glBegin(GL_POINTS);
    {
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(0.24f, percent) + x_pos, VALUE_FROM_PERCENT(0.86f, percent) + y_pos);
    }
    glEnd();

    glPointSize(11.0f);
    glBegin(GL_POINTS);
    {
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(0.14f, percent) + x_pos, VALUE_FROM_PERCENT(0.84f, percent) + y_pos);
    }
    glEnd();

    glPointSize(3.0f);
    glBegin(GL_POINTS);
    {
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(0.24f, percent) + x_pos, VALUE_FROM_PERCENT(0.72f, percent) + y_pos);
    }
    glEnd();

    glPointSize(10.0f);
    glBegin(GL_POINTS);
    {
      
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(0.33f, percent) + x_pos, VALUE_FROM_PERCENT(0.88f, percent) + y_pos);
    }
    glEnd();

    glPointSize(7.0f);
    glBegin(GL_POINTS);
    {
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(0.33f, percent) + x_pos, VALUE_FROM_PERCENT(0.74f, percent) + y_pos);
    }
    glEnd();

    glPointSize(5.0f);
    glBegin(GL_POINTS);
    {
        
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(0.4f, percent) + x_pos, VALUE_FROM_PERCENT(0.8f, percent) + y_pos);
    }
    glEnd();

    glPointSize(4.0f);
    glBegin(GL_POINTS);
    {
        
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(0.5f, percent) + x_pos, VALUE_FROM_PERCENT(0.88f, percent) + y_pos);
    }
    glEnd();

    glPointSize(9.0f);
    glBegin(GL_POINTS);
    {
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(0.52f, percent) + x_pos, VALUE_FROM_PERCENT(0.8f, percent) + y_pos);
    }
    glEnd();

    glPointSize(8.0f);
    glBegin(GL_POINTS);
    {
       
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(0.5f, percent) + x_pos, VALUE_FROM_PERCENT(0.72f, percent) + y_pos);
    }
    glEnd();

    glPointSize(6.0f);
    glBegin(GL_POINTS);
    {
       
        glColor4f(0.76f, 0.74f, 0.71f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(0.56f, percent) + x_pos, VALUE_FROM_PERCENT(0.72f, percent) + y_pos);
    }
    glEnd();

    glDisable(GL_POINT_SMOOTH);
}