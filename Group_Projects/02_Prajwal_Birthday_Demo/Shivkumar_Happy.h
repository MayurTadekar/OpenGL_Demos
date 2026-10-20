// Header files
#include<GL/freeglut.h>


// Variable Declaration/ Prototype
extern void Prajwal_Happy(float x_pos, float y_pos, float percent, float FadeFactor);
extern void Prajwal_Birthday(float x_pos, float y_pos, float percent, float FadeFactor);
extern void Prajwal_Name(float x_pos, float y_pos, float percent, float FadeFactor);

////////////////////////////////////////////////////////////////////////////
// Local Function Declarations / Prototype
////////////////////////////////////////////////////////////////////////////
void Draw_H(float x_pos, float y_pos, float percent, float FadeFactor);
void Draw_A(float x_pos, float y_pos, float percent, float FadeFactor);   
void Draw_P(float x_pos, float y_pos, float percent, float FadeFactor);
void Draw_P(float x_pos, float y_pos, float percent, float FadeFactor);
void Draw_Y(float x_pos, float y_pos, float percent, float FadeFactor);

void Draw_B(float x_pos, float y_pos, float percent, float FadeFactor);
void Draw_I(float x_pos, float y_pos, float percent, float FadeFactor);   
void Draw_T(float x_pos, float y_pos, float percent, float FadeFactor);
void Draw_D(float x_pos, float y_pos, float percent, float FadeFactor);

void Draw_P(float x_pos, float y_pos, float percent, float FadeFactor);
void Draw_R(float x_pos, float y_pos, float percent, float FadeFactor);
void Draw_A(float x_pos, float y_pos, float percent, float FadeFactor);
void Draw_J(float x_pos, float y_pos, float percent, float FadeFactor);
void Draw_W(float x_pos, float y_pos, float percent, float FadeFactor);
void Draw_A(float x_pos, float y_pos, float percent, float FadeFactor);
void Draw_L(float x_pos, float y_pos, float percent, float FadeFactor);

////////////////////////////////////////////////////////////////////////////
// Head Function Declarations
////////////////////////////////////////////////////////////////////////////
void Prajwal_Happy(float x_pos, float y_pos, float percent, float FadeFactor)
{
	Draw_H(-0.35f + x_pos, 0.4f + y_pos, percent, FadeFactor);
	Draw_A(-0.35f + x_pos, 0.4f + y_pos, percent, FadeFactor);
	Draw_P(-0.35f + x_pos, 0.4f + y_pos, percent, FadeFactor);
	Draw_P(-0.29f + x_pos, 0.4f + y_pos, percent, FadeFactor);
    Draw_Y(-0.35f + x_pos, 0.4f + y_pos, percent, FadeFactor);
}

void Prajwal_Birthday(float x_pos, float y_pos, float percent, float FadeFactor)
{
    Draw_B(-0.025f + x_pos, 0.235f + y_pos, percent + 40 , FadeFactor);
	Draw_I(-0.35f + x_pos, 0.4f + y_pos, percent, FadeFactor);
	Draw_R(-0.35f + x_pos, 0.4f + y_pos, percent, FadeFactor);
	Draw_T(-0.35f + x_pos, 0.4f + y_pos, percent, FadeFactor);
	Draw_H(-0.11f + x_pos, 0.21f + y_pos, percent, FadeFactor);
	Draw_D(-0.35f + x_pos, 0.4f + y_pos, percent, FadeFactor);
	Draw_A(-0.037f + x_pos, 0.21f + y_pos, percent, FadeFactor);
	Draw_Y(-0.15f + x_pos, 0.21f + y_pos, percent, FadeFactor);
}

void Prajwal_Name(float x_pos, float y_pos, float percent, float FadeFactor)
{
    Draw_P(-0.40f + x_pos, -0.57f + y_pos, percent, FadeFactor);
	Draw_R(-0.25f + x_pos, -0.09f + y_pos, percent, FadeFactor);
	Draw_A(0.05f + x_pos, -0.57f + y_pos, percent, FadeFactor);
	Draw_J(0.20f + x_pos, -0.09f + y_pos, percent, FadeFactor);
	Draw_W(-0.10f + x_pos, -0.57f + y_pos, percent, FadeFactor);
	Draw_A(0.56f + x_pos, -0.57f + y_pos, percent, FadeFactor);
	Draw_L(-0.09f + x_pos, -0.57f + y_pos, percent, FadeFactor);
}

////////////////////////////////////////////////////////////////////////////
// Happy Function Defination
////////////////////////////////////////////////////////////////////////////
void Draw_H(float x_pos, float y_pos, float percent, float FadeFactor)
{
    glBegin(GL_QUADS);
	//color
	glColor4f(23.0f/ 255.0f, 35.0f / 255.0f, 106.0f/ 255.0f, FadeFactor);

	//set the vertices - H
    // Left vertical bar
    glVertex2d(VALUE_FROM_PERCENT(-1.0f, percent) + x_pos , VALUE_FROM_PERCENT(0.90f, percent) + y_pos);   // top left
    glVertex2d(VALUE_FROM_PERCENT(-0.95f, percent) + x_pos, VALUE_FROM_PERCENT(0.90f, percent) + y_pos);  // top right  
    glVertex2d(VALUE_FROM_PERCENT(-0.95f, percent) + x_pos, VALUE_FROM_PERCENT(0.10f, percent) + y_pos);  //bottom right
    glVertex2d(VALUE_FROM_PERCENT(-1.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.10f, percent) + y_pos);  //bottom left

    // Right vertical bar
    glVertex2d(VALUE_FROM_PERCENT(-0.8f, percent) + x_pos , VALUE_FROM_PERCENT(0.90f, percent) + y_pos);   // top left
    glVertex2d(VALUE_FROM_PERCENT(-0.75f, percent) + x_pos, VALUE_FROM_PERCENT(0.90f, percent) + y_pos);  // top right  
    glVertex2d(VALUE_FROM_PERCENT(-0.75f, percent) + x_pos, VALUE_FROM_PERCENT(0.10f, percent) + y_pos);  //bottom right
    glVertex2d(VALUE_FROM_PERCENT(-0.8f, percent) + x_pos, VALUE_FROM_PERCENT(0.10f, percent) + y_pos);  //bottom left

    // Middle horizontal bar
    glVertex2d(VALUE_FROM_PERCENT(-0.95f, percent) + x_pos , VALUE_FROM_PERCENT(0.55f, percent) + y_pos);   // top left
    glVertex2d(VALUE_FROM_PERCENT(-0.8f, percent) + x_pos, VALUE_FROM_PERCENT(0.55f, percent) + y_pos);  // top right  
    glVertex2d(VALUE_FROM_PERCENT(-0.8f, percent) + x_pos, VALUE_FROM_PERCENT(0.45f, percent) + y_pos);  //bottom right
    glVertex2d(VALUE_FROM_PERCENT(-0.95f, percent) + x_pos, VALUE_FROM_PERCENT(0.45f, percent) + y_pos);  //bottom left

	glEnd();
}

void Draw_A(float x_pos, float y_pos, float percent, float FadeFactor)
{
    glBegin(GL_QUADS);
    glColor4f(23.0f/ 255.0f, 35.0f / 255.0f, 106.0f/ 255.0f, FadeFactor);

    // left vertical bar
    glVertex2d(VALUE_FROM_PERCENT(-0.70f, percent) + x_pos , VALUE_FROM_PERCENT(0.90f, percent) + y_pos);   // top left
    glVertex2d(VALUE_FROM_PERCENT(-0.65f, percent) + x_pos, VALUE_FROM_PERCENT(0.90f, percent) + y_pos);  // top right  
    glVertex2d(VALUE_FROM_PERCENT(-0.65f, percent) + x_pos, VALUE_FROM_PERCENT(0.10f, percent) + y_pos);  //bottom right
    glVertex2d(VALUE_FROM_PERCENT(-0.70f, percent) + x_pos, VALUE_FROM_PERCENT(0.10f, percent) + y_pos);  //bottom left

    // right vertical bar
    glVertex2d(VALUE_FROM_PERCENT(-0.50f, percent) + x_pos , VALUE_FROM_PERCENT(0.90f, percent) + y_pos);   // top left
    glVertex2d(VALUE_FROM_PERCENT(-0.45f, percent) + x_pos, VALUE_FROM_PERCENT(0.90f, percent) + y_pos);  // top right  
    glVertex2d(VALUE_FROM_PERCENT(-0.45f, percent) + x_pos, VALUE_FROM_PERCENT(0.10f, percent) + y_pos);  //bottom right
    glVertex2d(VALUE_FROM_PERCENT(-0.50f, percent) + x_pos, VALUE_FROM_PERCENT(0.10f, percent) + y_pos);  //bottom left

    // middle horizontal bar
    glVertex2d(VALUE_FROM_PERCENT(-0.70f, percent) + x_pos , VALUE_FROM_PERCENT(0.55f, percent) + y_pos);   // top left
    glVertex2d(VALUE_FROM_PERCENT(-0.45f, percent) + x_pos, VALUE_FROM_PERCENT(0.55f, percent) + y_pos);  // top right  
    glVertex2d(VALUE_FROM_PERCENT(-0.45f, percent) + x_pos, VALUE_FROM_PERCENT(0.45f, percent) + y_pos);  //bottom right
    glVertex2d(VALUE_FROM_PERCENT(-0.70f, percent) + x_pos, VALUE_FROM_PERCENT(0.45f, percent) + y_pos);  //bottom left


    // Upper horizontal bar
    glVertex2d(VALUE_FROM_PERCENT(-0.70f, percent) + x_pos, VALUE_FROM_PERCENT(0.90f, percent) + y_pos);   // top left
    glVertex2d(VALUE_FROM_PERCENT(-0.45f, percent) + x_pos, VALUE_FROM_PERCENT(0.90f, percent) + y_pos);  // top right  
    glVertex2d(VALUE_FROM_PERCENT(-0.45f, percent) + x_pos, VALUE_FROM_PERCENT(0.80f, percent) + y_pos);  //bottom right
    glVertex2d(VALUE_FROM_PERCENT(-0.70f, percent) + x_pos, VALUE_FROM_PERCENT(0.80f, percent) + y_pos);  //bottom left

    glEnd();

}

void Draw_P(float x_pos, float y_pos, float percent, float FadeFactor)
{
    glBegin(GL_QUADS);
    glColor4f(23.0f/ 255.0f, 35.0f / 255.0f, 106.0f/ 255.0f, FadeFactor);

        // left vertical bar
    glVertex2d(VALUE_FROM_PERCENT(-0.40f, percent) + x_pos, VALUE_FROM_PERCENT(0.90f, percent) + y_pos);   // top left
    glVertex2d(VALUE_FROM_PERCENT(-0.35f, percent) + x_pos, VALUE_FROM_PERCENT(0.90f, percent) + y_pos);  // top right  
    glVertex2d(VALUE_FROM_PERCENT(-0.35f, percent) + x_pos, VALUE_FROM_PERCENT(0.10f, percent) + y_pos);  //bottom right
    glVertex2d(VALUE_FROM_PERCENT(-0.40f, percent) + x_pos, VALUE_FROM_PERCENT(0.10f, percent) + y_pos);  //bottom left

    // right vertical bar
    glVertex2d(VALUE_FROM_PERCENT(-0.20f, percent) + x_pos , VALUE_FROM_PERCENT(0.90f, percent) + y_pos);   // top left
    glVertex2d(VALUE_FROM_PERCENT(-0.15f, percent) + x_pos, VALUE_FROM_PERCENT(0.90f, percent) + y_pos);  // top right  
    glVertex2d(VALUE_FROM_PERCENT(-0.15f, percent) + x_pos, VALUE_FROM_PERCENT(0.45f, percent) + y_pos);  //bottom right
    glVertex2d(VALUE_FROM_PERCENT(-0.20f, percent) + x_pos, VALUE_FROM_PERCENT(0.45f, percent) + y_pos);  //bottom left

    // middle horizontal bar
    glVertex2d(VALUE_FROM_PERCENT(-0.40f, percent) + x_pos , VALUE_FROM_PERCENT(0.55f, percent) + y_pos);   // top left
    glVertex2d(VALUE_FROM_PERCENT(-0.20f, percent) + x_pos, VALUE_FROM_PERCENT(0.55f, percent) + y_pos);  // top right  
    glVertex2d(VALUE_FROM_PERCENT(-0.20f, percent) + x_pos, VALUE_FROM_PERCENT(0.45f, percent) + y_pos);  //bottom right
    glVertex2d(VALUE_FROM_PERCENT(-0.40f, percent) + x_pos, VALUE_FROM_PERCENT(0.45f, percent) + y_pos);  //bottom left

    // Upper horizontal bar
    glVertex2d(VALUE_FROM_PERCENT(-0.40f, percent) + x_pos, VALUE_FROM_PERCENT(0.90f, percent) + y_pos);   // top left
    glVertex2d(VALUE_FROM_PERCENT(-0.20f, percent) + x_pos, VALUE_FROM_PERCENT(0.90f, percent) + y_pos);  // top right  
    glVertex2d(VALUE_FROM_PERCENT(-0.20f, percent) + x_pos, VALUE_FROM_PERCENT(0.80f, percent) + y_pos);  //bottom right
    glVertex2d(VALUE_FROM_PERCENT(-0.40f, percent) + x_pos, VALUE_FROM_PERCENT(0.80f, percent) + y_pos);  //bottom left

    glEnd();
}

void Draw_Y(float x_pos, float y_pos, float percent, float FadeFactor)
{
    glBegin(GL_QUADS);
    {
        glColor4f(23.0f/ 255.0f, 35.0f / 255.0f, 106.0f/ 255.0f, FadeFactor);

            // left vertical bar
        glVertex2d(VALUE_FROM_PERCENT( 0.20f, percent) + x_pos, VALUE_FROM_PERCENT(0.90f, percent) + y_pos);   // top left
        glVertex2d(VALUE_FROM_PERCENT( 0.25f, percent) + x_pos, VALUE_FROM_PERCENT(0.90f, percent) + y_pos);  // top right  
        glVertex2d(VALUE_FROM_PERCENT( 0.25f, percent) + x_pos, VALUE_FROM_PERCENT(0.45f, percent) + y_pos);  //bottom right
        glVertex2d(VALUE_FROM_PERCENT( 0.20f, percent) + x_pos, VALUE_FROM_PERCENT(0.45f, percent) + y_pos);  //bottom left

        // right vertical bar
        glVertex2d(VALUE_FROM_PERCENT(0.40f, percent) + x_pos , VALUE_FROM_PERCENT(0.90f, percent) + y_pos);   // top left
        glVertex2d(VALUE_FROM_PERCENT(0.45f, percent) + x_pos, VALUE_FROM_PERCENT(0.90f, percent) + y_pos);  // top right  
        glVertex2d(VALUE_FROM_PERCENT(0.45f, percent) + x_pos, VALUE_FROM_PERCENT(0.10f, percent) + y_pos);  //bottom right
        glVertex2d(VALUE_FROM_PERCENT(0.40f, percent) + x_pos, VALUE_FROM_PERCENT(0.10f, percent) + y_pos);  //bottom left

        // middle horizontal bar
        glVertex2d(VALUE_FROM_PERCENT( 0.20f, percent) + x_pos , VALUE_FROM_PERCENT(0.55f, percent) + y_pos);   // top left
        glVertex2d(VALUE_FROM_PERCENT( 0.40f, percent) + x_pos, VALUE_FROM_PERCENT(0.55f, percent) + y_pos);  // top right  
        glVertex2d(VALUE_FROM_PERCENT( 0.40f, percent) + x_pos, VALUE_FROM_PERCENT(0.45f, percent) + y_pos);  //bottom right
        glVertex2d(VALUE_FROM_PERCENT( 0.20f, percent) + x_pos, VALUE_FROM_PERCENT(0.45f, percent) + y_pos);  //bottom left

        // Lower horizontal bar
        glVertex2d(VALUE_FROM_PERCENT( 0.20f, percent) + x_pos, VALUE_FROM_PERCENT(0.10f, percent) + y_pos);   // top left
        glVertex2d(VALUE_FROM_PERCENT( 0.45f, percent) + x_pos, VALUE_FROM_PERCENT(0.10f, percent) + y_pos);  // top right  
        glVertex2d(VALUE_FROM_PERCENT( 0.45f, percent) + x_pos, VALUE_FROM_PERCENT(0.20f, percent) + y_pos);  //bottom right
        glVertex2d(VALUE_FROM_PERCENT( 0.20f, percent) + x_pos, VALUE_FROM_PERCENT(0.20f, percent) + y_pos);  //bottom left
    }
    glEnd();
}

////////////////////////////////////////////////////////////////////////////
// BirthDay Function Defination
////////////////////////////////////////////////////////////////////////////
void Draw_B(float x_pos, float y_pos, float percent, float FadeFactor)
{    
    glColor4f(23.0f/ 255.0f, 35.0f / 255.0f, 106.0f/ 255.0f, FadeFactor);
    glBegin(GL_QUADS);
    {
        glVertex2f(VALUE_FROM_PERCENT(-0.90f, percent) + x_pos, VALUE_FROM_PERCENT( 0.24f, percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(-0.90f, percent) + x_pos, VALUE_FROM_PERCENT( 0.00f, percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(-0.88f, percent) + x_pos, VALUE_FROM_PERCENT( 0.00f, percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(-0.88f, percent) + x_pos, VALUE_FROM_PERCENT( 0.24f, percent) + y_pos);

    }
    glEnd();

    glColor4f(23.0f/ 255.0f, 35.0f / 255.0f, 106.0f/ 255.0f, FadeFactor);
    glBegin(GL_QUADS);
    {
        glVertex2f(VALUE_FROM_PERCENT(-0.90f, percent) + x_pos, VALUE_FROM_PERCENT( 0.24f, percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(-0.90f, percent) + x_pos, VALUE_FROM_PERCENT( 0.22f, percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(-0.83f, percent) + x_pos, VALUE_FROM_PERCENT( 0.22f, percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(-0.85f, percent) + x_pos, VALUE_FROM_PERCENT( 0.24f, percent) + y_pos);

    }
    glEnd();

    glColor4f(23.0f/ 255.0f, 35.0f / 255.0f, 106.0f/ 255.0f, FadeFactor);
    glBegin(GL_QUADS);
    {
        glVertex2f(VALUE_FROM_PERCENT(-0.90f, percent) + x_pos, VALUE_FROM_PERCENT( 0.03f, percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(-0.90f, percent) + x_pos, VALUE_FROM_PERCENT( 0.00f, percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(-0.82f, percent) + x_pos, VALUE_FROM_PERCENT( 0.00f, percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(-0.80f, percent) + x_pos, VALUE_FROM_PERCENT( 0.03f, percent) + y_pos);

    }
    glEnd();

    glColor4f(23.0f/ 255.0f, 35.0f / 255.0f, 106.0f/ 255.0f, FadeFactor);
    glBegin(GL_QUADS);
    {
        glVertex2f(VALUE_FROM_PERCENT(-0.89f, percent) + x_pos, VALUE_FROM_PERCENT( 0.24f, percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(-0.85f, percent) + x_pos, VALUE_FROM_PERCENT( 0.20f, percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(-0.81f, percent) + x_pos, VALUE_FROM_PERCENT( 0.20f, percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(-0.85f, percent) + x_pos, VALUE_FROM_PERCENT( 0.24f, percent) + y_pos);

    }
    glEnd();

    glColor4f(23.0f/ 255.0f, 35.0f / 255.0f, 106.0f/ 255.0f, FadeFactor);
    glBegin(GL_QUADS);
    {
        glVertex2f(VALUE_FROM_PERCENT(-0.80f, percent) + x_pos, VALUE_FROM_PERCENT( 0.07f, percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(-0.86f, percent) + x_pos, VALUE_FROM_PERCENT( 0.00f, percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(-0.83f, percent) + x_pos, VALUE_FROM_PERCENT( 0.00f, percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(-0.77f, percent) + x_pos, VALUE_FROM_PERCENT( 0.07f, percent) + y_pos);
    }
    glEnd();

    glColor4f(23.0f/ 255.0f, 35.0f / 255.0f, 106.0f/ 255.0f, FadeFactor);
    glBegin(GL_QUADS);
    {
        glVertex2f(VALUE_FROM_PERCENT(-0.85f, percent) + x_pos, VALUE_FROM_PERCENT( 0.20f, percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(-0.88f, percent) + x_pos, VALUE_FROM_PERCENT( 0.16f, percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(-0.84f, percent) + x_pos, VALUE_FROM_PERCENT( 0.16f, percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(-0.81f, percent) + x_pos, VALUE_FROM_PERCENT( 0.20f, percent) + y_pos);
    }
    glEnd();

    glColor4f(23.0f/ 255.0f, 35.0f / 255.0f, 106.0f/ 255.0f, FadeFactor);
    glBegin(GL_QUADS);
    {
        glVertex2f(VALUE_FROM_PERCENT(-0.89f, percent) + x_pos, VALUE_FROM_PERCENT( 0.16f, percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(-0.80f, percent) + x_pos, VALUE_FROM_PERCENT( 0.07f, percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(-0.77f, percent) + x_pos, VALUE_FROM_PERCENT( 0.07f, percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(-0.86f, percent) + x_pos, VALUE_FROM_PERCENT( 0.16f, percent) + y_pos);
    }
    glEnd();
}



void Draw_I(float x_pos, float y_pos, float percent, float FadeFactor)
{
    glBegin(GL_QUADS);
    glColor4f(23.0f/ 255.0f, 35.0f / 255.0f, 106.0f/ 255.0f, FadeFactor);

    // left vertical bar
 
    glVertex2d(VALUE_FROM_PERCENT(-0.70f, percent) + x_pos, VALUE_FROM_PERCENT(-0.05f, percent) + y_pos);  
    glVertex2d(VALUE_FROM_PERCENT(-0.45f, percent) + x_pos, VALUE_FROM_PERCENT(-0.05f, percent) + y_pos);  
    glVertex2d(VALUE_FROM_PERCENT(-0.45f, percent) + x_pos , VALUE_FROM_PERCENT(-0.15f, percent) + y_pos);  
    glVertex2d(VALUE_FROM_PERCENT(-0.70f, percent) + x_pos, VALUE_FROM_PERCENT(-0.15f, percent) + y_pos);  
 
    glVertex2d(VALUE_FROM_PERCENT(-0.60f, percent) + x_pos, VALUE_FROM_PERCENT(-0.05f, percent) + y_pos);  
    glVertex2d(VALUE_FROM_PERCENT(-0.55f, percent) + x_pos, VALUE_FROM_PERCENT(-0.05f, percent) + y_pos);  
    glVertex2d(VALUE_FROM_PERCENT(-0.55f, percent) + x_pos , VALUE_FROM_PERCENT(-0.85f, percent) + y_pos);  
    glVertex2d(VALUE_FROM_PERCENT(-0.60f, percent) + x_pos, VALUE_FROM_PERCENT(-0.85f, percent) + y_pos);  
    
    glVertex2d(VALUE_FROM_PERCENT(-0.70f, percent) + x_pos, VALUE_FROM_PERCENT(-0.75f, percent) + y_pos);
    glVertex2d(VALUE_FROM_PERCENT(-0.45f, percent) + x_pos, VALUE_FROM_PERCENT(-0.75f, percent) + y_pos);  
    glVertex2d(VALUE_FROM_PERCENT(-0.45f, percent) + x_pos, VALUE_FROM_PERCENT(-0.85f, percent) + y_pos);  
    glVertex2d(VALUE_FROM_PERCENT(-0.70f, percent) + x_pos, VALUE_FROM_PERCENT(-0.85f, percent) + y_pos);  

    glEnd();
}

void Draw_R(float x_pos, float y_pos, float percent, float FadeFactor)
{
    glBegin(GL_QUADS);
    glColor4f(23.0f/ 255.0f, 35.0f / 255.0f, 106.0f/ 255.0f, FadeFactor);

        // left vertical bar
    glVertex2d(VALUE_FROM_PERCENT(-0.40f, percent) + x_pos, VALUE_FROM_PERCENT(-0.05f, percent) + y_pos);   // top left
    glVertex2d(VALUE_FROM_PERCENT(-0.35f, percent) + x_pos, VALUE_FROM_PERCENT(-0.05f, percent) + y_pos);  // top right  
    glVertex2d(VALUE_FROM_PERCENT(-0.35f, percent) + x_pos, VALUE_FROM_PERCENT(-0.85f, percent) + y_pos);  //bottom right
    glVertex2d(VALUE_FROM_PERCENT(-0.40f, percent) + x_pos, VALUE_FROM_PERCENT(-0.85f, percent) + y_pos);  //bottom left

    // right vertical bar
    glVertex2d(VALUE_FROM_PERCENT(-0.20f, percent) + x_pos , VALUE_FROM_PERCENT(-0.05f, percent) + y_pos);   // top left
    glVertex2d(VALUE_FROM_PERCENT(-0.15f, percent) + x_pos, VALUE_FROM_PERCENT(-0.05f, percent) + y_pos);  // top right  
    glVertex2d(VALUE_FROM_PERCENT(-0.15f, percent) + x_pos, VALUE_FROM_PERCENT(-0.45f, percent) + y_pos);  //bottom right
    glVertex2d(VALUE_FROM_PERCENT(-0.20f, percent) + x_pos, VALUE_FROM_PERCENT(-0.45f, percent) + y_pos);  //bottom left

    // middle horizontal bar
    glVertex2d(VALUE_FROM_PERCENT(-0.40f, percent) + x_pos , VALUE_FROM_PERCENT(-0.45f, percent) + y_pos);   // top left
    glVertex2d(VALUE_FROM_PERCENT(-0.20f, percent) + x_pos, VALUE_FROM_PERCENT(-0.45f, percent) + y_pos);  // top right  
    glVertex2d(VALUE_FROM_PERCENT(-0.20f, percent) + x_pos, VALUE_FROM_PERCENT(-0.35f, percent) + y_pos);  //bottom right
    glVertex2d(VALUE_FROM_PERCENT(-0.40f, percent) + x_pos, VALUE_FROM_PERCENT(-0.35f, percent) + y_pos);  //bottom left

    // Upper horizontal bar
    glVertex2d(VALUE_FROM_PERCENT(-0.40f, percent) + x_pos, VALUE_FROM_PERCENT(-0.05f, percent) + y_pos);   // top left 
    glVertex2d(VALUE_FROM_PERCENT(-0.20f, percent) + x_pos, VALUE_FROM_PERCENT(-0.05f, percent) + y_pos);  // top right  
    glVertex2d(VALUE_FROM_PERCENT(-0.20f, percent) + x_pos, VALUE_FROM_PERCENT(-0.15f, percent) + y_pos);  //bottom right
    glVertex2d(VALUE_FROM_PERCENT(-0.40f, percent) + x_pos, VALUE_FROM_PERCENT(-0.15f, percent) + y_pos);  //bottom left

    // Diagonal bar
    glVertex2d(VALUE_FROM_PERCENT(-0.40f, percent) + x_pos, VALUE_FROM_PERCENT(-0.40f, percent) + y_pos);   // top left
    glVertex2d(VALUE_FROM_PERCENT(-0.35f, percent) + x_pos, VALUE_FROM_PERCENT(-0.38f, percent) + y_pos);  // top right  
    glVertex2d(VALUE_FROM_PERCENT(-0.15f, percent) + x_pos, VALUE_FROM_PERCENT(-0.80f, percent) + y_pos);  //bottom right
    glVertex2d(VALUE_FROM_PERCENT(-0.20f, percent) + x_pos, VALUE_FROM_PERCENT(-0.85f, percent) + y_pos);  //bottom left

    glEnd();
}

void Draw_T(float x_pos, float y_pos, float percent, float FadeFactor)
{
    glBegin(GL_QUADS);
    glColor4f(23.0f/ 255.0f, 35.0f / 255.0f, 106.0f/ 255.0f, FadeFactor);

    glVertex2d(VALUE_FROM_PERCENT(-0.10f, percent) + x_pos, VALUE_FROM_PERCENT(-0.05f, percent) + y_pos);  
    glVertex2d(VALUE_FROM_PERCENT(0.15f, percent) + x_pos, VALUE_FROM_PERCENT(-0.05f, percent) + y_pos);  
    glVertex2d(VALUE_FROM_PERCENT(0.15f, percent) + x_pos , VALUE_FROM_PERCENT(-0.15f, percent) + y_pos);  
    glVertex2d(VALUE_FROM_PERCENT(-0.10f, percent) + x_pos, VALUE_FROM_PERCENT(-0.15f, percent) + y_pos);  
 
    glVertex2d(VALUE_FROM_PERCENT(-0.00f, percent) + x_pos, VALUE_FROM_PERCENT(-0.05f, percent) + y_pos);  
    glVertex2d(VALUE_FROM_PERCENT(0.05f, percent) + x_pos, VALUE_FROM_PERCENT(-0.05f, percent) + y_pos);  
    glVertex2d(VALUE_FROM_PERCENT(0.05f, percent) + x_pos , VALUE_FROM_PERCENT(-0.85f, percent) + y_pos);  
    glVertex2d(VALUE_FROM_PERCENT(-0.00f, percent) + x_pos, VALUE_FROM_PERCENT(-0.85f, percent) + y_pos);  
    
    glEnd();
}

void Draw_D(float x_pos, float y_pos, float percent, float FadeFactor)
{
    glBegin(GL_QUADS);
    glColor4f(23.0f/ 255.0f, 35.0f / 255.0f, 106.0f/ 255.0f, FadeFactor);

    // left vertical bar
    glVertex2d(VALUE_FROM_PERCENT(0.55f, percent) + x_pos, VALUE_FROM_PERCENT(-0.05f, percent) + y_pos);
    glVertex2d(VALUE_FROM_PERCENT(0.50f, percent) + x_pos, VALUE_FROM_PERCENT(-0.05f, percent) + y_pos);    
    glVertex2d(VALUE_FROM_PERCENT(0.50f, percent) + x_pos, VALUE_FROM_PERCENT(-0.85f, percent) + y_pos);  
    glVertex2d(VALUE_FROM_PERCENT(0.55f, percent) + x_pos, VALUE_FROM_PERCENT(-0.85f, percent) + y_pos);  
    
    // Upper Horizontal bar
    glVertex2d(VALUE_FROM_PERCENT(0.55f, percent) + x_pos, VALUE_FROM_PERCENT(-0.05f, percent) + y_pos);
    glVertex2d(VALUE_FROM_PERCENT(0.70f, percent) + x_pos, VALUE_FROM_PERCENT(-0.05f, percent) + y_pos);    
    glVertex2d(VALUE_FROM_PERCENT(0.70f, percent) + x_pos, VALUE_FROM_PERCENT(-0.15f, percent) + y_pos);  
    glVertex2d(VALUE_FROM_PERCENT(0.55f, percent) + x_pos, VALUE_FROM_PERCENT(-0.15f, percent) + y_pos);  

    // Lower Horizontal bar
    glVertex2d(VALUE_FROM_PERCENT(0.55f, percent) + x_pos, VALUE_FROM_PERCENT(-0.75f, percent) + y_pos);
    glVertex2d(VALUE_FROM_PERCENT(0.70f, percent) + x_pos, VALUE_FROM_PERCENT(-0.75f, percent) + y_pos);    
    glVertex2d(VALUE_FROM_PERCENT(0.70f, percent) + x_pos, VALUE_FROM_PERCENT(-0.85f, percent) + y_pos);  
    glVertex2d(VALUE_FROM_PERCENT(0.55f, percent) + x_pos, VALUE_FROM_PERCENT(-0.85f, percent) + y_pos);  

    // Upper slant bar
    glVertex2d(VALUE_FROM_PERCENT(0.70f, percent) + x_pos, VALUE_FROM_PERCENT(-0.05f, percent) + y_pos);    
    glVertex2d(VALUE_FROM_PERCENT(0.80f, percent) + x_pos, VALUE_FROM_PERCENT(-0.20f, percent) + y_pos);  
    glVertex2d(VALUE_FROM_PERCENT(0.72f, percent) + x_pos, VALUE_FROM_PERCENT(-0.20f, percent) + y_pos);  
    glVertex2d(VALUE_FROM_PERCENT(0.68f, percent) + x_pos, VALUE_FROM_PERCENT(-0.15f, percent) + y_pos);  

    // Lower Slant bar
    glVertex2d(VALUE_FROM_PERCENT(0.68f, percent) + x_pos, VALUE_FROM_PERCENT(-0.75f, percent) + y_pos);    
    glVertex2d(VALUE_FROM_PERCENT(0.72f, percent) + x_pos, VALUE_FROM_PERCENT(-0.70f, percent) + y_pos);  
    glVertex2d(VALUE_FROM_PERCENT(0.80f, percent) + x_pos, VALUE_FROM_PERCENT(-0.70f, percent) + y_pos);  
    glVertex2d(VALUE_FROM_PERCENT(0.70f, percent) + x_pos, VALUE_FROM_PERCENT(-0.85f, percent) + y_pos);  

    // Right Vertical bar
    glVertex2d(VALUE_FROM_PERCENT(0.72f, percent) + x_pos, VALUE_FROM_PERCENT(-0.20f, percent) + y_pos);  
    glVertex2d(VALUE_FROM_PERCENT(0.80f, percent) + x_pos, VALUE_FROM_PERCENT(-0.20f, percent) + y_pos); 
    glVertex2d(VALUE_FROM_PERCENT(0.80f, percent) + x_pos, VALUE_FROM_PERCENT(-0.70f, percent) + y_pos);  
    glVertex2d(VALUE_FROM_PERCENT(0.72f, percent) + x_pos, VALUE_FROM_PERCENT(-0.70f, percent) + y_pos); 

    glEnd();
}

////////////////////////////////////////////////////////////////////////////
// Prajwal Function Defination
////////////////////////////////////////////////////////////////////////////
void Draw_J(float x_pos, float y_pos, float percent, float FadeFactor)
{
    glBegin(GL_QUADS);
    glColor4f(23.0f/ 255.0f, 35.0f / 255.0f, 106.0f/ 255.0f, FadeFactor);

    glVertex2d(VALUE_FROM_PERCENT(-0.70f, percent) + x_pos, VALUE_FROM_PERCENT(-0.05f, percent) + y_pos);  
    glVertex2d(VALUE_FROM_PERCENT(-0.45f, percent) + x_pos, VALUE_FROM_PERCENT(-0.05f, percent) + y_pos);  
    glVertex2d(VALUE_FROM_PERCENT(-0.45f, percent) + x_pos , VALUE_FROM_PERCENT(-0.15f, percent) + y_pos);  
    glVertex2d(VALUE_FROM_PERCENT(-0.70f, percent) + x_pos, VALUE_FROM_PERCENT(-0.15f, percent) + y_pos);  
 
    glVertex2d(VALUE_FROM_PERCENT(-0.55f, percent) + x_pos, VALUE_FROM_PERCENT(-0.05f, percent) + y_pos);  
    glVertex2d(VALUE_FROM_PERCENT(-0.50f, percent) + x_pos, VALUE_FROM_PERCENT(-0.05f, percent) + y_pos);  
    glVertex2d(VALUE_FROM_PERCENT(-0.50f, percent) + x_pos , VALUE_FROM_PERCENT(-0.85f, percent) + y_pos);  
    glVertex2d(VALUE_FROM_PERCENT(-0.55f, percent) + x_pos, VALUE_FROM_PERCENT(-0.85f, percent) + y_pos);  
    
    glVertex2d(VALUE_FROM_PERCENT(-0.70f, percent) + x_pos, VALUE_FROM_PERCENT(-0.75f, percent) + y_pos);
    glVertex2d(VALUE_FROM_PERCENT(-0.55f, percent) + x_pos, VALUE_FROM_PERCENT(-0.75f, percent) + y_pos);  
    glVertex2d(VALUE_FROM_PERCENT(-0.55f, percent) + x_pos, VALUE_FROM_PERCENT(-0.85f, percent) + y_pos);  
    glVertex2d(VALUE_FROM_PERCENT(-0.70f, percent) + x_pos, VALUE_FROM_PERCENT(-0.85f, percent) + y_pos); 


    glVertex2d(VALUE_FROM_PERCENT(-0.70f, percent) + x_pos, VALUE_FROM_PERCENT(-0.75f, percent) + y_pos);
    glVertex2d(VALUE_FROM_PERCENT(-0.65f, percent) + x_pos, VALUE_FROM_PERCENT(-0.75f, percent) + y_pos);  
    glVertex2d(VALUE_FROM_PERCENT(-0.65f, percent) + x_pos, VALUE_FROM_PERCENT(-0.70f, percent) + y_pos);  
    glVertex2d(VALUE_FROM_PERCENT(-0.70f, percent) + x_pos, VALUE_FROM_PERCENT(-0.70f, percent) + y_pos); 

    glEnd();
}    

void Draw_W(float x_pos, float y_pos, float percent, float FadeFactor)
{
    glBegin(GL_QUADS);
    glColor4f(23.0f/ 255.0f, 35.0f / 255.0f, 106.0f/ 255.0f, FadeFactor);

     // left vertical bar
    glVertex2d(VALUE_FROM_PERCENT(0.25f, percent) + x_pos , VALUE_FROM_PERCENT(0.90f, percent) + y_pos);   // top left
    glVertex2d(VALUE_FROM_PERCENT(0.20f, percent) + x_pos, VALUE_FROM_PERCENT(0.90f, percent) + y_pos);  // top right  
    glVertex2d(VALUE_FROM_PERCENT(0.20f, percent) + x_pos, VALUE_FROM_PERCENT(0.10f, percent) + y_pos);  //bottom right
    glVertex2d(VALUE_FROM_PERCENT(0.25f, percent) + x_pos, VALUE_FROM_PERCENT(0.10f, percent) + y_pos);  //bottom left


    // right vertical bar
    glVertex2d(VALUE_FROM_PERCENT(0.55f, percent) + x_pos , VALUE_FROM_PERCENT(0.90f, percent) + y_pos);   // top left
    glVertex2d(VALUE_FROM_PERCENT(0.50f, percent) + x_pos, VALUE_FROM_PERCENT(0.90f, percent) + y_pos);  // top right  
    glVertex2d(VALUE_FROM_PERCENT(0.50f, percent) + x_pos, VALUE_FROM_PERCENT(0.10f, percent) + y_pos);  //bottom right
    glVertex2d(VALUE_FROM_PERCENT(0.55f, percent) + x_pos, VALUE_FROM_PERCENT(0.10f, percent) + y_pos);  //bottom left

    glVertex2d(VALUE_FROM_PERCENT(0.25f, percent) + x_pos, VALUE_FROM_PERCENT(0.20f, percent) + y_pos);  
    glVertex2d(VALUE_FROM_PERCENT(0.50f, percent) + x_pos, VALUE_FROM_PERCENT(0.20f, percent) + y_pos);  
    glVertex2d(VALUE_FROM_PERCENT(0.50f, percent) + x_pos, VALUE_FROM_PERCENT(0.10f, percent) + y_pos);  
    glVertex2d(VALUE_FROM_PERCENT(0.25f, percent) + x_pos, VALUE_FROM_PERCENT(0.10f, percent) + y_pos);

    glVertex2d(VALUE_FROM_PERCENT(0.35f, percent) + x_pos, VALUE_FROM_PERCENT(0.50f, percent) + y_pos);  
    glVertex2d(VALUE_FROM_PERCENT(0.40f, percent) + x_pos, VALUE_FROM_PERCENT(0.50f, percent) + y_pos);  
    glVertex2d(VALUE_FROM_PERCENT(0.40f, percent) + x_pos, VALUE_FROM_PERCENT(0.15f, percent) + y_pos);  
    glVertex2d(VALUE_FROM_PERCENT(0.35f, percent) + x_pos, VALUE_FROM_PERCENT(0.15f, percent) + y_pos);
    
    glEnd();
}

void Draw_L(float x_pos, float y_pos, float percent, float FadeFactor)
{
    glBegin(GL_QUADS);
    glColor4f(23.0f/ 255.0f, 35.0f / 255.0f, 106.0f/ 255.0f, FadeFactor);


     // left vertical bar
    glVertex2d(VALUE_FROM_PERCENT(0.95f, percent) + x_pos , VALUE_FROM_PERCENT(0.90f, percent) + y_pos);  
    glVertex2d(VALUE_FROM_PERCENT(0.90f, percent) + x_pos, VALUE_FROM_PERCENT(0.90f, percent) + y_pos);   
    glVertex2d(VALUE_FROM_PERCENT(0.90f, percent) + x_pos, VALUE_FROM_PERCENT(0.10f, percent) + y_pos); 
    glVertex2d(VALUE_FROM_PERCENT(0.95f, percent) + x_pos, VALUE_FROM_PERCENT(0.10f, percent) + y_pos);  

    // Lower Horizontal bar
    glVertex2d(VALUE_FROM_PERCENT(0.95f, percent) + x_pos , VALUE_FROM_PERCENT(0.20f, percent) + y_pos);  
    glVertex2d(VALUE_FROM_PERCENT(1.25f, percent) + x_pos, VALUE_FROM_PERCENT(0.20f, percent) + y_pos);   
    glVertex2d(VALUE_FROM_PERCENT(1.25f, percent) + x_pos, VALUE_FROM_PERCENT(0.10f, percent) + y_pos); 
    glVertex2d(VALUE_FROM_PERCENT(0.95f, percent) + x_pos, VALUE_FROM_PERCENT(0.10f, percent) + y_pos);  

    glEnd();
}













