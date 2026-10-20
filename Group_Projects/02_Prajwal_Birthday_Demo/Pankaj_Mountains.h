#include<GL/freeglut.h>

//Function Declaration
extern void pankaj_mountainS(float x_pos, float y_pos, float percent,float Fadefactor);

//Function Defination
void pankaj_mountainS(float x_pos, float y_pos, float percent, float Fadefactor)
{
    glBegin(GL_TRIANGLES);
    {
        glColor3f(5.0f / 255.0f, 32.0f / 255.0f, 105.0f / 255.0f);
        glVertex2f(VALUE_FROM_PERCENT(-1.0f , percent) + x_pos, VALUE_FROM_PERCENT(0.05f , percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(-0.51f , percent) + x_pos, VALUE_FROM_PERCENT(0.44f , percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(-0.04f , percent) + x_pos, VALUE_FROM_PERCENT(0.05f , percent) + y_pos);

    }
    glEnd();

    glBegin(GL_QUADS);
    {
        glColor3f(5.0f / 255.0f, 32.0f / 255.0f, 105.0f / 255.0f);
        glVertex2f(VALUE_FROM_PERCENT(-0.22f , percent) + x_pos, VALUE_FROM_PERCENT(0.0f , percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(0.64f , percent) + x_pos, VALUE_FROM_PERCENT(0.64f , percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(1.0f , percent) + x_pos, VALUE_FROM_PERCENT(0.32f , percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(1.0f , percent) + x_pos, VALUE_FROM_PERCENT(0.0f , percent) + y_pos);
    }
    glEnd();

    glBegin(GL_TRIANGLES);
    {
        glColor4f(1.0f, 1.0f, 1.0f, Fadefactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.51f , percent) + x_pos, VALUE_FROM_PERCENT(0.44f , percent) + y_pos);
        glColor4f(5.0f / 255.0f, 32.0f / 255.0f, 105.0f / 255.0f, Fadefactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.39f , percent) + x_pos, VALUE_FROM_PERCENT(0.34f , percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(-0.73f , percent) + x_pos, VALUE_FROM_PERCENT(0.27f , percent) + y_pos);

    }
    glEnd();

    glBegin(GL_TRIANGLES);
    {
        glColor4f(1.0f, 1.0f, 1.0f, Fadefactor);
        glVertex2f(VALUE_FROM_PERCENT(0.64f , percent) + x_pos, VALUE_FROM_PERCENT(0.64f , percent) + y_pos);
        glColor4f(5.0f / 255.0f, 32.0f / 255.0f, 105.0f / 255.0f, Fadefactor);
        glVertex2f(VALUE_FROM_PERCENT(0.82f  , percent) + x_pos, VALUE_FROM_PERCENT(0.48f , percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(0.012f , percent) + x_pos, VALUE_FROM_PERCENT(0.16f , percent) + y_pos);

    }
    glEnd();

   


}
