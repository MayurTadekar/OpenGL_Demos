/*
 *************************************************
 * @file	: TreasureBox_Adesh.h
 * @brief	: Variable and Function declarations
 * @author	: Adesh Mohanrao Pathare 
 * 			  <adeshpathare8495@gmail.com>
 * @Date    : 19 February 2025
 *************************************************
 */

// Header file
#include<GL/freeglut.h>


// Function declarations
void Treasure_Adesh(float x_pos, float y_pos, float percent);
void Treasure_Box_Base(float x_pos, float y_pos, float percent);
void Coin(float x_pos, float y_pos, float x, float y, float percent);
void TreasureBox_Cover(float x_pos, float y_pos, float percent);
void TreasureBox_Lines(float x_pos, float y_pos, float percent);
void TreasureBox_Lock(float x_pos, float y_pos, float percent);
void TreasureBox_Coins(float x_pos, float y_pos, float percent);


void Treasure_Adesh(float x_pos, float y_pos, float percent)
{
	// Call to design box base square
	Treasure_Box_Base(x_pos, y_pos, percent);

	// call to treasure box cover
	TreasureBox_Cover(x_pos, y_pos, percent);

	// call to treasure box lines
	TreasureBox_Lines(x_pos, y_pos, percent);

	// Treasure box lock
	TreasureBox_Lock(x_pos, y_pos, percent);
	
	// call to coins placement function
	TreasureBox_Coins(x_pos, y_pos, percent);

	// Top view quad above coins(bottom)
	glBegin(GL_QUADS);
	{
		// import the color
		glColor3f(157.0/255.0f, 95.0/255.0f, 18.0/255.0f);

		//set the vertices
		glVertex2d(VALUE_FROM_PERCENT(0.51f, percent) + x_pos, VALUE_FROM_PERCENT(-0.76f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.97f, percent) + x_pos, VALUE_FROM_PERCENT(-0.76f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.98f, percent) + x_pos, VALUE_FROM_PERCENT(-0.78f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.52f, percent) + x_pos, VALUE_FROM_PERCENT(-0.78f, percent) + y_pos);
	}
	glEnd();

	// Top view quad above coins (right side)
	glBegin(GL_QUADS);
	{
		// import the color
		glColor3f(157.0/255.0f, 95.0/255.0f, 18.0/255.0f);

		//set the vertices
		glVertex2d(VALUE_FROM_PERCENT(0.89f, percent) + x_pos, VALUE_FROM_PERCENT(-0.64f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.97f, percent) + x_pos, VALUE_FROM_PERCENT(-0.76f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.95f, percent) + x_pos, VALUE_FROM_PERCENT(-0.76f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.88f, percent) + x_pos, VALUE_FROM_PERCENT(-0.66f, percent) + y_pos);
	}
	glEnd();

	// Top view quad above coins (left side)
	glBegin(GL_QUADS);
	{
		// import the color
		glColor3f(157.0/255.0f, 95.0/255.0f, 18.0/255.0f);

		//set the vertices
		glVertex2d(VALUE_FROM_PERCENT(0.48f, percent) + x_pos, VALUE_FROM_PERCENT(-0.66f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.45f, percent) + x_pos, VALUE_FROM_PERCENT(-0.66f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.51f, percent) + x_pos, VALUE_FROM_PERCENT(-0.76f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.53f, percent) + x_pos, VALUE_FROM_PERCENT(-0.76f, percent) + y_pos);
	}
	glEnd();

	// Top view quad above coins (top side)
	glBegin(GL_QUADS);
	{
		// import the color
		glColor3f(157.0/255.0f, 95.0/255.0f, 18.0/255.0f);

		//set the vertices
		glVertex2d(VALUE_FROM_PERCENT(0.84f, percent) + x_pos, VALUE_FROM_PERCENT(-0.64f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.89f, percent) + x_pos, VALUE_FROM_PERCENT(-0.64f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.88f, percent) + x_pos, VALUE_FROM_PERCENT(-0.66f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.84f, percent) + x_pos, VALUE_FROM_PERCENT(-0.66f, percent) + y_pos);
	}
	glEnd();
}

void Treasure_Box_Base(float x_pos, float y_pos, float percent)
{
	//code
	// main quad for top view
	glBegin(GL_QUADS);
	{
		//import the color
		glColor3f(157.0/255.0f, 95.0/255.0f, 18.0/255.0f);

		//set the vertices
		glVertex2d(VALUE_FROM_PERCENT(0.44f, percent) + x_pos, VALUE_FROM_PERCENT(-0.64f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.89f, percent) + x_pos, VALUE_FROM_PERCENT(-0.64f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.98f, percent) + x_pos, VALUE_FROM_PERCENT(-0.78f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.52f, percent) + x_pos, VALUE_FROM_PERCENT(-0.78f, percent) + y_pos);
	}
	glEnd();

	// sub-quad for top view
	glBegin(GL_QUADS);
	{
		//import the color
		glColor3f(107.0/255.0f, 64.0/255.0f, 9.0/255.0f);

		//set the vertices
		glVertex2d(VALUE_FROM_PERCENT(0.48f, percent) + x_pos, VALUE_FROM_PERCENT(-0.66f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.88f, percent) + x_pos, VALUE_FROM_PERCENT(-0.66f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.95f, percent) + x_pos, VALUE_FROM_PERCENT(-0.76f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.53f, percent) + x_pos, VALUE_FROM_PERCENT(-0.76f, percent) + y_pos);
	}
	glEnd();

	// side-quad for left side view
	glBegin(GL_QUADS);
	{
		//import the color
		glColor3f(191.0/255.0f, 163.0/255.0f, 48.0/255.0f);

		//set the vertices
		glVertex2d(VALUE_FROM_PERCENT(0.44f, percent) + x_pos, VALUE_FROM_PERCENT(-0.64f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.52f, percent) + x_pos, VALUE_FROM_PERCENT(-0.78f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.52f, percent) + x_pos, VALUE_FROM_PERCENT(-1.00f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.46f, percent) + x_pos, VALUE_FROM_PERCENT(-0.94f, percent) + y_pos);
	}
	glEnd();

	// sub-quad for left side view
	glBegin(GL_QUADS);
	{
		//import the color
		glColor3f(158.0/255.0f, 94.0/255.0f, 21.0/255.0f);

		//set the vertices
		glVertex2d(VALUE_FROM_PERCENT(0.46f, percent) + x_pos, VALUE_FROM_PERCENT(-0.70f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.51f, percent) + x_pos, VALUE_FROM_PERCENT(-0.79f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.51f, percent) + x_pos, VALUE_FROM_PERCENT(-0.97f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.48f, percent) + x_pos, VALUE_FROM_PERCENT(-0.94f, percent) + y_pos);
	}	
	glEnd();

	// main-quad for front view
	glBegin(GL_QUADS);
	{
		//import the color
		glColor3f(233.0/255.0f, 188.0/255.0f, 45.0/255.0f);

		//set the vertices
		glVertex2d(VALUE_FROM_PERCENT(0.52f, percent) + x_pos, VALUE_FROM_PERCENT(-0.78f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.98f, percent) + x_pos, VALUE_FROM_PERCENT(-0.78f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.93f, percent) + x_pos, VALUE_FROM_PERCENT(-0.98f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.52f, percent) + x_pos, VALUE_FROM_PERCENT(-1.00f, percent) + y_pos);
	}
	glEnd();

	// left sub-quad for front view
	glBegin(GL_QUADS);
	{
		//import the color
		glColor3f(157.0/255.0f, 95.0/255.0f, 18.0/255.0f);

		//set the vertices
		glVertex2d(VALUE_FROM_PERCENT(0.55f, percent) + x_pos, VALUE_FROM_PERCENT(-0.81f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.72f, percent) + x_pos, VALUE_FROM_PERCENT(-0.81f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.72f, percent) + x_pos, VALUE_FROM_PERCENT(-0.96f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.55f, percent) + x_pos, VALUE_FROM_PERCENT(-0.97f, percent) + y_pos);
	}
	glEnd();

	// right sub-quad for front view
	glBegin(GL_QUADS);
	{
		//import the color
		glColor3f(157.0/255.0f, 95.0/255.0f, 18.0/255.0f);

		//set the vertices
		glVertex2d(VALUE_FROM_PERCENT(0.76f, percent) + x_pos, VALUE_FROM_PERCENT(-0.81f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.94f, percent) + x_pos, VALUE_FROM_PERCENT(-0.81f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.91f, percent) + x_pos, VALUE_FROM_PERCENT(-0.95f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.76f, percent) + x_pos, VALUE_FROM_PERCENT(-0.96f, percent) + y_pos);
	}
	glEnd();
}

// function definition for coin design
void Coin(float x_pos, float y_pos, float x, float y, float percent) // x = 0.62, y = -0.73
{
	// Treasure box lock
	glBegin(GL_POLYGON);
	{
		// import the color
		glColor3f(225.0/255.0f, 216.0/255.0f, 51.0/255.0f);

		//corrected y axis
		glVertex2d(VALUE_FROM_PERCENT(0.000f + x , percent) + x_pos, VALUE_FROM_PERCENT(-0.00f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.010f + x , percent) + x_pos, VALUE_FROM_PERCENT(-0.0025f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.0137f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0049f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.0160f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0078f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.0181f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0117f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.0194f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0156f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.0200f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.018f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.0199f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0225f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.0184f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0284f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.0163f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0315f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.0121f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0357f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.0100f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0373f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.0148f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0391f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.0000f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0399f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(-0.0056f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0391f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(-0.01f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0375f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(-0.0129f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0352f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(-0.0166f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0307f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(-0.0192f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.025f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(-0.0197f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0232f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(-0.02f + x, percent)  + x_pos, VALUE_FROM_PERCENT(-0.02f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(-0.0197f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0156f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(-0.0184f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0317f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(-0.0158f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0078f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(-0.0132f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0047f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(-0.01f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0028f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(-0.0064f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0001f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(-0.0043f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0005f + y, percent) + y_pos);
	}
	glEnd();

	// Border for coins
	glBegin(GL_LINES);
	{
		// import the color
		glColor3f(107.0/255.0f, 64.0/255.0f, 9.0/255.0f);

		// set the vertices
		glVertex2d(VALUE_FROM_PERCENT(0.010f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0025f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.0137f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0049f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.0160f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0078f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.0181f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0117f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.0194f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0156f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.0200f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.018f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.0199f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0225f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.0184f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0284f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.0163f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0315f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.0121f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0357f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.0100f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0373f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.0148f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0391f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.0000f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0399f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(-0.0056f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0391f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(-0.01f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0375f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(-0.0129f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0352f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(-0.0166f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0307f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(-0.0192f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.025f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(-0.0197f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0232f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(-0.02f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.02f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(-0.0197f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0156f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(-0.0184f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0317f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(-0.0158f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0078f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(-0.0132f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0047f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(-0.01f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0028f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(-0.0064f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0001f + y, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(-0.0043f + x, percent) + x_pos, VALUE_FROM_PERCENT(-0.0005f + y, percent) + y_pos);
	}
	glEnd();
}

// function definition for upper cover
void TreasureBox_Cover(float x_pos, float y_pos, float percent)
{
	//code
	// quad for main Box-Cover
	glBegin(GL_QUADS);
	{
		//import the color
		glColor3f(157.0/255.0f, 95.0/255.0f, 18.0/255.0f);

		//set the vertices
		glVertex2d(VALUE_FROM_PERCENT(0.40f, percent) + x_pos, VALUE_FROM_PERCENT(-0.46f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.85f, percent) + x_pos, VALUE_FROM_PERCENT(-0.46f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.88f, percent) + x_pos, VALUE_FROM_PERCENT(-0.62f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.43f, percent) + x_pos, VALUE_FROM_PERCENT(-0.62f, percent) + y_pos);

		//import the color
		glColor3f(233.0/255.0f, 193.0/255.0f, 60.0/255.0f);

		// Left Clip for cover
		glVertex2d(VALUE_FROM_PERCENT(0.52f, percent) + x_pos, VALUE_FROM_PERCENT(-0.62f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.56f, percent) + x_pos, VALUE_FROM_PERCENT(-0.62f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.57f, percent) + x_pos, VALUE_FROM_PERCENT(-0.64f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.53f, percent) + x_pos, VALUE_FROM_PERCENT(-0.64f, percent) + y_pos);

		// Left Clip for cover
		glVertex2d(VALUE_FROM_PERCENT(0.74f, percent) + x_pos, VALUE_FROM_PERCENT(-0.64f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.79f, percent) + x_pos, VALUE_FROM_PERCENT(-0.64f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.78f, percent) + x_pos, VALUE_FROM_PERCENT(-0.62f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.73f, percent) + x_pos, VALUE_FROM_PERCENT(-0.62f, percent) + y_pos);
	}
	glEnd();

	// quad for left-side view of cover
	glBegin(GL_QUADS);
	{
		//import the color
		glColor3f(233.0/255.0f, 193.0/255.0f, 60.0/255.0f);

		//set the vertices
		glVertex2d(VALUE_FROM_PERCENT(0.40f, percent) + x_pos, VALUE_FROM_PERCENT(-0.46f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.37f, percent) + x_pos, VALUE_FROM_PERCENT(-0.53f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.38f, percent) + x_pos, VALUE_FROM_PERCENT(-0.58f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.43f, percent) + x_pos, VALUE_FROM_PERCENT(-0.62f, percent) + y_pos);
	}
	glEnd();

	// inner quad for box cover
	glBegin(GL_QUADS);
	{
		//import the color
		glColor3f(126.0/255.0f, 76.0/255.0f, 15.0/255.0f);

		//set the vertices
		glVertex2d(VALUE_FROM_PERCENT(0.41f, percent) + x_pos, VALUE_FROM_PERCENT(-0.47f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.84f, percent) + x_pos, VALUE_FROM_PERCENT(-0.47f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.87f, percent) + x_pos, VALUE_FROM_PERCENT(-0.61f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.44f, percent) + x_pos, VALUE_FROM_PERCENT(-0.61f, percent) + y_pos);
	}
	glEnd();

	// quad for right-side shadow of cover
	glBegin(GL_QUADS);
	{
		//import the color
		glColor3f(107.0/255.0f, 64.0/255.0f, 9.0/255.0f);

		//set the vertices
		glVertex2d(VALUE_FROM_PERCENT(0.84f, percent) + x_pos, VALUE_FROM_PERCENT(-0.47f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.81f, percent) + x_pos, VALUE_FROM_PERCENT(-0.53f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.82f, percent) + x_pos, VALUE_FROM_PERCENT(-0.58f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.87f, percent) + x_pos, VALUE_FROM_PERCENT(-0.61f, percent) + y_pos);
	}
	glEnd();

}

// function definition for lines
void TreasureBox_Lines(float x_pos, float y_pos, float percent)
{
	// lines inside the box cover
	glBegin(GL_LINES);
	{
		//import the color
		glColor3f(107.0/255.0f, 64.0/255.0f, 9.0/255.0f);

		//set the vertices
		glVertex2d(VALUE_FROM_PERCENT(0.4250f, percent) + x_pos, VALUE_FROM_PERCENT(-0.53f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.81f, percent) + x_pos, VALUE_FROM_PERCENT(-0.53f, percent) + y_pos);
		
		glVertex2d(VALUE_FROM_PERCENT(0.81f, percent) + x_pos, VALUE_FROM_PERCENT(-0.53f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.82f, percent) + x_pos, VALUE_FROM_PERCENT(-0.58f, percent) + y_pos);

		glVertex2d(VALUE_FROM_PERCENT(0.81f, percent) + x_pos, VALUE_FROM_PERCENT(-0.53f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.84f, percent) + x_pos, VALUE_FROM_PERCENT(-0.47f, percent) + y_pos);

		glVertex2d(VALUE_FROM_PERCENT(0.44f, percent) + x_pos, VALUE_FROM_PERCENT(-0.58f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.82f, percent) + x_pos, VALUE_FROM_PERCENT(-0.58f, percent) + y_pos);

		glVertex2d(VALUE_FROM_PERCENT(0.82f, percent) + x_pos, VALUE_FROM_PERCENT(-0.58f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.87f, percent) + x_pos, VALUE_FROM_PERCENT(-0.61f, percent) + y_pos);

		// lines for main box front view (Left Side quad)
		glVertex2d(VALUE_FROM_PERCENT(0.5550f, percent) + x_pos, VALUE_FROM_PERCENT(-0.85f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.72f, percent) + x_pos, VALUE_FROM_PERCENT(-0.85f, percent) + y_pos);

		glVertex2d(VALUE_FROM_PERCENT(0.5550f, percent) + x_pos, VALUE_FROM_PERCENT(-0.90f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.72f, percent) + x_pos, VALUE_FROM_PERCENT(-0.90f, percent) + y_pos);

		glVertex2d(VALUE_FROM_PERCENT(0.5550f, percent) + x_pos, VALUE_FROM_PERCENT(-0.95f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.72f, percent) + x_pos, VALUE_FROM_PERCENT(-0.94f, percent) + y_pos);

		// lines for main box front view (Right Side quad)
		glVertex2d(VALUE_FROM_PERCENT(0.76f, percent) + x_pos, VALUE_FROM_PERCENT(-0.85f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.93f, percent) + x_pos, VALUE_FROM_PERCENT(-0.85f, percent) + y_pos);

		glVertex2d(VALUE_FROM_PERCENT(0.76f, percent) + x_pos, VALUE_FROM_PERCENT(-0.89f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.92f, percent) + x_pos, VALUE_FROM_PERCENT(-0.89f, percent) + y_pos);

		glVertex2d(VALUE_FROM_PERCENT(0.76f, percent) + x_pos, VALUE_FROM_PERCENT(-0.93f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.91f, percent) + x_pos, VALUE_FROM_PERCENT(-0.93f, percent) + y_pos);
	}
	glEnd();
}

// function definition for lock
void TreasureBox_Lock(float x_pos, float y_pos, float percent)
{
	glBegin(GL_POLYGON);
	{
		// import the color
		glColor3f(203.0/255.0f, 161.0/255.0f, 17.0/255.0f);

		// set the vertices
		glVertex2d(VALUE_FROM_PERCENT(0.70f, percent) + x_pos, VALUE_FROM_PERCENT(-0.81f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.71f, percent) + x_pos, VALUE_FROM_PERCENT(-0.80f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.74f, percent) + x_pos, VALUE_FROM_PERCENT(-0.79f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.77f, percent) + x_pos, VALUE_FROM_PERCENT(-0.80f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.78f, percent) + x_pos, VALUE_FROM_PERCENT(-0.81f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.77f, percent) + x_pos, VALUE_FROM_PERCENT(-0.84f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.71f, percent) + x_pos, VALUE_FROM_PERCENT(-0.84f, percent) + y_pos);
	}
	glEnd();

	// Treasure box lock-key point
	glBegin(GL_POINTS);
	{
		// import the color
		glColor3f(0.0/255.0f, 0.0/255.0f, 0.0/255.0f);

		glVertex2f(VALUE_FROM_PERCENT(0.74f, percent) + x_pos, VALUE_FROM_PERCENT(-0.81f, percent) + y_pos);
	}
	glEnd();

	// Lock key place
	glBegin(GL_LINES);
	{
		// import the color
		glColor3f(0.0/255.0f, 0.0/255.0f, 0.0/255.0f);

		glVertex2d(VALUE_FROM_PERCENT(0.74f, percent) + x_pos, VALUE_FROM_PERCENT(-0.81f, percent) + y_pos);
		glVertex2d(VALUE_FROM_PERCENT(0.74f, percent) + x_pos, VALUE_FROM_PERCENT(-0.83f, percent) + y_pos);
	}
	glEnd();
}

// function definition for Coins placement
void TreasureBox_Coins(float x_pos, float y_pos, float percent)
{
	//code
	Coin(x_pos, y_pos, 0.62, -0.73, percent);
	Coin(x_pos, y_pos, 0.65, -0.69, percent);
	Coin(x_pos, y_pos, 0.62, -0.70, percent);
	Coin(x_pos, y_pos, 0.62, -0.67, percent);
	Coin(x_pos, y_pos, 0.66, -0.6575, percent);
	Coin(x_pos, y_pos, 0.70, -0.66, percent);
	Coin(x_pos, y_pos, 0.60, -0.67, percent);
	Coin(x_pos, y_pos, 0.57, -0.67, percent);
	Coin(x_pos, y_pos, 0.51, -0.66, percent);
	Coin(x_pos, y_pos, 0.68, -0.67, percent);
	Coin(x_pos, y_pos, 0.79, -0.66, percent);
	Coin(x_pos, y_pos, 0.79, -0.73, percent);
	Coin(x_pos, y_pos, 0.76, -0.66, percent);
	Coin(x_pos, y_pos, 0.86, -0.67, percent);
	Coin(x_pos, y_pos, 0.85, -0.69, percent);
	Coin(x_pos, y_pos, 0.88, -0.67, percent);
	Coin(x_pos, y_pos, 0.89, -0.70, percent);
	Coin(x_pos, y_pos, 0.86, -0.67, percent);
	Coin(x_pos, y_pos, 0.89, -0.73, percent);
	Coin(x_pos, y_pos, 0.86, -0.73, percent);
	Coin(x_pos, y_pos, 0.73, -0.72, percent);
	Coin(x_pos, y_pos, 0.53, -0.72, percent);
	Coin(x_pos, y_pos, 0.53, -0.69, percent);
	Coin(x_pos, y_pos, 0.60, -0.74, percent);
	Coin(x_pos, y_pos, 0.60, -0.71, percent);
	Coin(x_pos, y_pos, 0.68, -0.71, percent);
	Coin(x_pos, y_pos, 0.73, -0.74, percent);
	Coin(x_pos, y_pos, 0.76, -0.69, percent);
	Coin(x_pos, y_pos, 0.81, -0.70, percent);
	Coin(x_pos, y_pos, 0.83, -0.69, percent);
	Coin(x_pos, y_pos, 0.85, -0.71, percent);
	Coin(x_pos, y_pos, 0.80, -0.70, percent);
	Coin(x_pos, y_pos, 0.75, -0.69, percent);
	Coin(x_pos, y_pos, 0.76, -0.74, percent);
	Coin(x_pos, y_pos, 0.79, -0.73, percent);
	Coin(x_pos, y_pos, 0.91, -0.73, percent);
	Coin(x_pos, y_pos, 0.93, -0.75, percent);

	Coin(x_pos, y_pos, 0.67, -0.67, percent);
	Coin(x_pos, y_pos, 0.64, -0.68, percent);
	Coin(x_pos, y_pos, 0.64, -0.65, percent);
	Coin(x_pos, y_pos, 0.68, -0.6375, percent);
	Coin(x_pos, y_pos, 0.72, -0.64, percent);
	Coin(x_pos, y_pos, 0.62, -0.65, percent);
	Coin(x_pos, y_pos, 0.59, -0.65, percent);
	Coin(x_pos, y_pos, 0.53, -0.64, percent);
	Coin(x_pos, y_pos, 0.70, -0.65, percent);
	Coin(x_pos, y_pos, 0.81, -0.64, percent);
	Coin(x_pos, y_pos, 0.81, -0.71, percent);
	Coin(x_pos, y_pos, 0.78, -0.64, percent);
	Coin(x_pos, y_pos, 0.88, -0.65, percent);
	Coin(x_pos, y_pos, 0.87, -0.67, percent);
	Coin(x_pos, y_pos, 0.91, -0.71, percent);
	Coin(x_pos, y_pos, 0.88, -0.71, percent);
	Coin(x_pos, y_pos, 0.75, -0.70, percent);
	Coin(x_pos, y_pos, 0.55, -0.70, percent);
	Coin(x_pos, y_pos, 0.55, -0.67, percent);
	Coin(x_pos, y_pos, 0.56, -0.73, percent);
	Coin(x_pos, y_pos, 0.62, -0.72, percent);
	Coin(x_pos, y_pos, 0.62, -0.69, percent);
	Coin(x_pos, y_pos, 0.70, -0.69, percent);
	Coin(x_pos, y_pos, 0.75, -0.72, percent);
	Coin(x_pos, y_pos, 0.78, -0.67, percent);

	Coin(x_pos, y_pos, 0.67, -0.75, percent);
	Coin(x_pos, y_pos, 0.64, -0.64, percent);
	Coin(x_pos, y_pos, 0.64, -0.63, percent);
	Coin(x_pos, y_pos, 0.68, -0.6175, percent);
	Coin(x_pos, y_pos, 0.72, -0.62, percent);
	Coin(x_pos, y_pos, 0.62, -0.63, percent);
	Coin(x_pos, y_pos, 0.59, -0.63, percent);
	Coin(x_pos, y_pos, 0.53, -0.62, percent);
	Coin(x_pos, y_pos, 0.70, -0.63, percent);
	Coin(x_pos, y_pos, 0.81, -0.62, percent);
	Coin(x_pos, y_pos, 0.81, -0.69, percent);
	Coin(x_pos, y_pos, 0.78, -0.62, percent);
	Coin(x_pos, y_pos, 0.88, -0.63, percent);
	Coin(x_pos, y_pos, 0.87, -0.65, percent);
	Coin(x_pos, y_pos, 0.91, -0.69, percent);
	Coin(x_pos, y_pos, 0.88, -0.69, percent);
	Coin(x_pos, y_pos, 0.75, -0.68, percent);
	Coin(x_pos, y_pos, 0.55, -0.68, percent);
	Coin(x_pos, y_pos, 0.55, -0.65, percent);
	Coin(x_pos, y_pos, 0.56, -0.71, percent);
	Coin(x_pos, y_pos, 0.62, -0.70, percent);
	Coin(x_pos, y_pos, 0.62, -0.67, percent);
	Coin(x_pos, y_pos, 0.70, -0.67, percent);
	Coin(x_pos, y_pos, 0.75, -0.70, percent);
	Coin(x_pos, y_pos, 0.78, -0.65, percent);
}
//EOF