// header files
#include<GL/freeglut.h>

extern void Boat_Amol(float x_pos, float y_pos, float percent);
extern void Bridge_Amol(float x_pos, float y_pos, float percent);
extern void Rope_Amol(float x_pos, float y_pos, float percent, float FadeFactor);

void Boat_Amol(float x_pos, float y_pos, float percent)
{

   /* //Background
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 1.5f);
    // 
    glVertex2f(VALUE_FROM_PERCENT(- 1.0f,percent) + x_pos, 1.0f + y_pos);
    glColor3f(0.5f, 1.0f, 1.0f);
    glVertex2f(-1.0f, -1.0f);  
    // glColor3f(0.6f, 0.4f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(1.0f + x_pos, -1.0f + y_pos);  
    glColor3f(1.0f, 1.0f, 1.5f);
    glVertex2f(1.0f + x_pos, 1.0f + y_pos);  
    glEnd(); 
    */

    //behind hold bar
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.2f, 0.0f);
    // 
    glVertex2f(VALUE_FROM_PERCENT(0.32f, percent) + x_pos, VALUE_FROM_PERCENT(-0.43f, percent) + y_pos);
    glVertex2f(VALUE_FROM_PERCENT(0.32f, percent)+ x_pos, VALUE_FROM_PERCENT(-0.48f, percent) + y_pos);
    // glColor3f(0.6f, 0.4f, 0.0f);
    glVertex2f(VALUE_FROM_PERCENT(0.34f, percent) + x_pos, VALUE_FROM_PERCENT(-0.48f, percent) + y_pos);
    glVertex2f(VALUE_FROM_PERCENT(0.34f, percent) + x_pos, VALUE_FROM_PERCENT(-0.43f, percent) + y_pos);
    glEnd();


    //Boat top Strip
    glBegin(GL_QUADS);
    glColor3f(0.3f, 0.0f, 0.0f);
    glVertex2f(VALUE_FROM_PERCENT(-0.17f, percent) + x_pos, VALUE_FROM_PERCENT(-0.48f, percent) + y_pos);
    glVertex2f(VALUE_FROM_PERCENT(-0.13f, percent) + x_pos, VALUE_FROM_PERCENT(-0.52f, percent) + y_pos);
    glVertex2f(VALUE_FROM_PERCENT(0.33f, percent) + x_pos, VALUE_FROM_PERCENT(-0.52f, percent) + y_pos);

    glVertex2f(VALUE_FROM_PERCENT(0.37f, percent) + x_pos, VALUE_FROM_PERCENT(-0.48f, percent) + y_pos);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.4f, 0.2f, 0.0f);
    glVertex2f(VALUE_FROM_PERCENT(-0.13f, percent) + x_pos, VALUE_FROM_PERCENT(-0.52f, percent) + y_pos);
    glVertex2f(VALUE_FROM_PERCENT(-0.12f, percent) + x_pos, VALUE_FROM_PERCENT(-0.57f, percent) + y_pos);
    glColor3f(0.3f, 0.0f, 0.0f);
    glVertex2f(VALUE_FROM_PERCENT(0.32f, percent) + x_pos, VALUE_FROM_PERCENT(-0.57f, percent) + y_pos);

    glVertex2f(VALUE_FROM_PERCENT(0.33f, percent) + x_pos, VALUE_FROM_PERCENT(-0.52f, percent) + y_pos);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.4f, 0.2f, 0.0f);
    glVertex2f(VALUE_FROM_PERCENT(-0.12f, percent) + x_pos, VALUE_FROM_PERCENT(-0.57f, percent) + y_pos);
    glVertex2f(VALUE_FROM_PERCENT(-0.11f, percent) + x_pos, VALUE_FROM_PERCENT(-0.61f, percent) + y_pos);
    glColor3f(0.3f, 0.0f, 0.0f);
    glVertex2f(VALUE_FROM_PERCENT(0.31f, percent) + x_pos, VALUE_FROM_PERCENT(-0.61f, percent) + y_pos);

    glVertex2f(VALUE_FROM_PERCENT(0.32f, percent) + x_pos, VALUE_FROM_PERCENT(-0.57f, percent) + y_pos);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.4f, 0.2f, 0.0f);
    glVertex2f(VALUE_FROM_PERCENT(-0.11f, percent) + x_pos, VALUE_FROM_PERCENT(-0.61f, percent) + y_pos);
    glVertex2f(VALUE_FROM_PERCENT(-0.10f, percent) + x_pos, VALUE_FROM_PERCENT(-0.65f, percent) + y_pos);
    glColor3f(0.3f, 0.0f, 0.0f);
    glVertex2f(VALUE_FROM_PERCENT(0.30f, percent) + x_pos, VALUE_FROM_PERCENT(-0.65f, percent) + y_pos);
    glVertex2f(VALUE_FROM_PERCENT(0.31f, percent) + x_pos, VALUE_FROM_PERCENT(-0.61f, percent) + y_pos);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.4f, 0.2f, 0.0f);
    glVertex2f(VALUE_FROM_PERCENT(-0.10f, percent) + x_pos, VALUE_FROM_PERCENT(-0.61f, percent) + y_pos);
    glVertex2f(VALUE_FROM_PERCENT(-0.09f, percent) + x_pos, VALUE_FROM_PERCENT(-0.64f, percent) + y_pos);
    glColor3f(0.3f, 0.0f, 0.0f);
    glVertex2f(VALUE_FROM_PERCENT(0.29f, percent) + x_pos, VALUE_FROM_PERCENT(-0.64f, percent) + y_pos);

    glVertex2f(VALUE_FROM_PERCENT(0.30f, percent) + x_pos, VALUE_FROM_PERCENT(-0.61f, percent) + y_pos);
    glEnd();


    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(VALUE_FROM_PERCENT(-0.12f, percent) + x_pos, VALUE_FROM_PERCENT(-0.57f, percent) + y_pos);
    glVertex2f(VALUE_FROM_PERCENT(0.32f, percent) + x_pos, VALUE_FROM_PERCENT(-0.57f, percent) + y_pos);

    glVertex2f(VALUE_FROM_PERCENT(-0.11f, percent) + x_pos, VALUE_FROM_PERCENT(-0.61f, percent) + y_pos);
    glVertex2f(VALUE_FROM_PERCENT(0.31f, percent) + x_pos, VALUE_FROM_PERCENT(-0.61f, percent) + y_pos);
    glEnd();


    //Vallav 
    //Vallav Bar
    glLineWidth(5);
    glBegin(GL_LINES);
    
    glColor3f(0.5f, 0.2f, 0.0f);
    glVertex2f(VALUE_FROM_PERCENT(0.05f, percent) + x_pos, VALUE_FROM_PERCENT(-0.4f, percent) + y_pos);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(-0.7f, percent) + y_pos);
    glEnd();

    //Vallav Top
    glPointSize(6.0f);
    glBegin(GL_POINTS);
    glColor3f(0.7f, 0.2f, 0.2f);
    glVertex2f(VALUE_FROM_PERCENT(0.05f, percent) + x_pos, VALUE_FROM_PERCENT(-0.4f, percent) + y_pos);
    glEnd();

    //Vallav bottom 
    glPointSize(18.0f);
    glBegin(GL_POINTS);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(-0.7f, percent) + y_pos);
    glEnd();


    // Vallav holder 
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(VALUE_FROM_PERCENT(0.1f, percent) + x_pos, VALUE_FROM_PERCENT(-0.45f, percent) + y_pos);
    glVertex2f(VALUE_FROM_PERCENT(0.1f, percent) + x_pos, VALUE_FROM_PERCENT(-0.48f, percent) + y_pos);

    glVertex2f(VALUE_FROM_PERCENT(0.1f, percent) + x_pos, VALUE_FROM_PERCENT(-0.45f, percent) + y_pos);
    glVertex2f(VALUE_FROM_PERCENT(0.12f, percent) + x_pos, VALUE_FROM_PERCENT(-0.45f, percent) + y_pos);

    glVertex2f(VALUE_FROM_PERCENT(0.12f, percent) + x_pos, VALUE_FROM_PERCENT(-0.45f, percent) + y_pos);
    glVertex2f(VALUE_FROM_PERCENT(0.12f, percent) + x_pos, VALUE_FROM_PERCENT(-0.48f, percent) + y_pos);
    glEnd();

}


void Bridge_Amol(float x_pos, float y_pos, float percent)
{

    //******************* BRIDGE **********************************************

    // behind PILLERS
    for (float i = 0.0f; i < 6.0f; i += 0.2f)
    {
        glBegin(GL_QUADS);
        glColor3f(0.3f, 0.1f, 0.0f);  // 
        glVertex2f(VALUE_FROM_PERCENT((0.4f + i), percent) + x_pos, VALUE_FROM_PERCENT(-0.3f, percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT((0.4f + i), percent) + x_pos, VALUE_FROM_PERCENT(-0.6f, percent) + y_pos);
        glColor3f(0.3f, 0.2f, 0.2f);
        glVertex2f(VALUE_FROM_PERCENT((0.44f + i), percent) + x_pos, VALUE_FROM_PERCENT(-0.6f, percent) + y_pos);
        glColor3f(0.3f, 0.0f, 0.0f);
        glVertex2f(VALUE_FROM_PERCENT((0.44f + i), percent) + x_pos, VALUE_FROM_PERCENT(-0.3f, percent) + y_pos);
        glEnd();
    }

    //bridge patform
    
    for (float i = 0.0f; i < 10.0f; i += 0.05f)
    {
        glBegin(GL_QUADS);
        glColor3f(0.5f, 0.3f, 0.0f);
        glVertex2f(VALUE_FROM_PERCENT((0.4f + i), percent) + x_pos, VALUE_FROM_PERCENT(-0.4f, percent) + y_pos);
        glColor3f(0.4f, 0.3f, 0.0f);
        glVertex2f(VALUE_FROM_PERCENT((0.45f + i), percent) + x_pos, VALUE_FROM_PERCENT(-0.5f, percent) + y_pos);
        glColor3f(0.5f, 0.5f, 0.4f);
        glVertex2f(VALUE_FROM_PERCENT((0.5f + i), percent) + x_pos, VALUE_FROM_PERCENT(-0.5f, percent) + y_pos);
        glColor3f(0.5f, 0.5f, 0.4f);
        glVertex2f(VALUE_FROM_PERCENT((0.45f + i), percent) + x_pos, VALUE_FROM_PERCENT(-0.4f, percent) + y_pos);
        
        glEnd();
    }
    
    
    // try to extend bridge
    glBegin(GL_QUADS);
    glColor3f(0.4f, 0.3f, 0.0f);  // 
    glVertex2f(VALUE_FROM_PERCENT(0.95f, percent) + x_pos, VALUE_FROM_PERCENT(-0.4f, percent) + y_pos);
    glColor3f(0.4f, 0.3f, 0.0f);
    glVertex2f(VALUE_FROM_PERCENT(1.0f, percent) + x_pos, VALUE_FROM_PERCENT(-0.5f, percent) + y_pos);
    glColor3f(0.5f, 0.5f, 0.4f);
    glVertex2f(VALUE_FROM_PERCENT(1.0f, percent) + x_pos, VALUE_FROM_PERCENT(-0.5f, percent) + y_pos);
    glVertex2f(VALUE_FROM_PERCENT(1.0f, percent) + x_pos, VALUE_FROM_PERCENT(-0.4f, percent) + y_pos);
    glEnd();

    // Horizontal path strip
    glBegin(GL_QUADS);
    glColor3f(0.4f, 0.3f, 0.0f);  // 
    glVertex2f(VALUE_FROM_PERCENT(0.45f, percent) + x_pos, VALUE_FROM_PERCENT(-0.5f, percent) + y_pos);
    glColor3f(0.4f, 0.3f, 0.0f);
    glVertex2f(VALUE_FROM_PERCENT(0.45f, percent) + x_pos, VALUE_FROM_PERCENT(-0.52f, percent) + y_pos);
    glColor3f(0.5f, 0.5f, 0.4f);
    glVertex2f(VALUE_FROM_PERCENT(1.0f, percent) + x_pos, VALUE_FROM_PERCENT(-0.52f, percent) + y_pos);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(VALUE_FROM_PERCENT(1.0f, percent) + x_pos, VALUE_FROM_PERCENT(-0.5f, percent) + y_pos);
    glEnd();

    // FRONT PILLERS
    for (float i = 0.0f; i < 6.0f; i += 0.2f)
    {
        glBegin(GL_QUADS);
        glColor3f(0.3f, 0.1f, 0.0f);  // 
        glVertex2f(VALUE_FROM_PERCENT((0.45f + i), percent) + x_pos, VALUE_FROM_PERCENT(-0.4f, percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT((0.45f + i), percent) + x_pos, VALUE_FROM_PERCENT(-0.7f, percent) + y_pos);
        glColor3f(0.3f, 0.2f, 0.2f);
        glVertex2f(VALUE_FROM_PERCENT((0.49f +i), percent) + x_pos, VALUE_FROM_PERCENT(-0.7f, percent) + y_pos);
        glColor3f(0.3f, 0.0f, 0.0f);
        glVertex2f(VALUE_FROM_PERCENT((0.49f +i), percent) + x_pos, VALUE_FROM_PERCENT(-0.4f, percent) + y_pos);
        glEnd();
    }
   
   
}

void Rope_Amol(float x_pos, float y_pos, float percent, float FadeFactor)
{
    // ***************** Rope using triangle strips ****************

    glLineWidth(4);

    glBegin(GL_LINE_STRIP);
    glColor4f(1.0f, 1.0f, 0.9f, FadeFactor);  // 
    glVertex2f(VALUE_FROM_PERCENT(0.32f, percent) + x_pos, VALUE_FROM_PERCENT(-0.47f, percent) + y_pos);  // 
    glVertex2f(VALUE_FROM_PERCENT(0.49f, percent) + x_pos, VALUE_FROM_PERCENT(-0.48f, percent) + y_pos);  // 
    
    glVertex2f(VALUE_FROM_PERCENT(0.34f, percent) + x_pos, VALUE_FROM_PERCENT(-0.48f, percent) + y_pos); // 

    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2f(VALUE_FROM_PERCENT(0.49f, percent) + x_pos, VALUE_FROM_PERCENT(-0.48f, percent) + y_pos);
    glVertex2f(VALUE_FROM_PERCENT(0.45f, percent) + x_pos, VALUE_FROM_PERCENT(-0.49f, percent) + y_pos);
    glVertex2f(VALUE_FROM_PERCENT(0.49f, percent) + x_pos, VALUE_FROM_PERCENT(-0.50f, percent) + y_pos);
    glVertex2f(VALUE_FROM_PERCENT(0.48f, percent) + x_pos, VALUE_FROM_PERCENT(-0.49f, percent) + y_pos);

    glVertex2f(VALUE_FROM_PERCENT(0.47f, percent) + x_pos, VALUE_FROM_PERCENT(-0.50f, percent) + y_pos);
    glVertex2f(VALUE_FROM_PERCENT(0.48f, percent) + x_pos, VALUE_FROM_PERCENT(-0.51f, percent) + y_pos);
    glVertex2f(VALUE_FROM_PERCENT(0.47f, percent) + x_pos, VALUE_FROM_PERCENT(-0.52f, percent) + y_pos);
    glVertex2f(VALUE_FROM_PERCENT(0.48f, percent) + x_pos, VALUE_FROM_PERCENT(-0.53f, percent) + y_pos);
    glVertex2f(VALUE_FROM_PERCENT(0.47f, percent) + x_pos, VALUE_FROM_PERCENT(-0.54f, percent) + y_pos);
    glVertex2f(VALUE_FROM_PERCENT(0.48f, percent) + x_pos, VALUE_FROM_PERCENT(-0.55f, percent) + y_pos);
    glEnd();
    
    glLineWidth(1.0f);
}
