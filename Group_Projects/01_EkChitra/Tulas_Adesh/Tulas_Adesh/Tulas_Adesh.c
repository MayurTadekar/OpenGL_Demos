// Header files
#include<GL/freeglut.h>

// Global variables declarations
BOOL bFullScreen = FALSE;

// Entry-point function
int main(int argc, char* argv[])
{
	// local function declarations
	int initialize(void);
	void resize(int, int);
	void display(void);
	void keyboard(unsigned char, int, int);
	void mouse(int, int, int, int);
	void uninitialize(void);
	void Tulas_Adesh(float x_pos, float y_pos);
	void Tulsi_Vrindavan(float x_pos, float y_pos);
	void Tulsi_leaf(float x_pos, float y_pos);
	void Tulsi_Branches(float x_pos, float y_pos);

	// Code
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Adesh Mohanrao Pathare");

	initialize();

	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutCloseFunc(uninitialize);

	glutMainLoop();

	return(0);
}

int initialize(void)
{
	// code
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
	
	return(0);
}

void resize(int width, int height)
{
	// code
	glViewport(0, 0, width, height);
}

void display(void)
{
	// variable declarations
	float x_pos = 0.0f;
	float y_pos = 0.0f;

	// code
	glClear(GL_COLOR_BUFFER_BIT);

	// Call to main function of Tulas
	Tulas_Adesh(x_pos, y_pos);
	
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	// code
	switch (key)
	{
	case 27:
		glutLeaveMainLoop();
		break;

	case'F':
	case 'f':
		if (bFullScreen == FALSE)
		{
			glutFullScreen();
			bFullScreen = TRUE;
		}
		else 
		{
			glutLeaveFullScreen();
			bFullScreen = FALSE;
		}
		break;
	default:
		break;
	} // switch end

}

void mouse(int button, int state, int x, int y)
{
	// code
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		glutLeaveMainLoop();
		break;
	default:
		break;
	}
}

void uninitialize(void)
{
	// code
}

void Tulas_Adesh(float x_pos, float y_pos)
{
	// Call to design vrindavan
	Tulsi_Vrindavan(x_pos, y_pos);
	
	// Call to design tulsi branches
	Tulsi_Branches(x_pos, y_pos);

	// Call for tulsi leaf
	Tulsi_leaf(x_pos, y_pos);

}

void Tulsi_Vrindavan(float x_pos, float y_pos)
{
	// main quad for tulsi
	glBegin(GL_QUADS);

	//import the color
	glColor3f(1.0f, 0.75f, 0.76f);

	//set the vertices
	glVertex2d(0.52f + x_pos, -0.20f + y_pos);
	glVertex2d(0.52f + x_pos, -0.50f + y_pos);
	glVertex2d(0.64f + x_pos, -0.50f + y_pos);
	glVertex2d(0.64f + x_pos, -0.20f + y_pos);

	glEnd();

	// Upper Rechangular Quad
	glBegin(GL_QUADS);

	//import the color
	glColor3f(0.9f, 0.0f, 0.0f);

	//set the vertices
	glVertex2d(0.48f + x_pos, -0.16f + y_pos);
	glVertex2d(0.48f + x_pos, -0.23f + y_pos);
	glVertex2d(0.68f + x_pos, -0.23f + y_pos);
	glVertex2d(0.68f + x_pos, -0.16f + y_pos);

	glEnd();

	//Set Triangles on upper quad
	glBegin(GL_TRIANGLES);

	//Set the color
	glColor3f(0.9f, 0.0f, 0.0f);

	// Set the vertices for right triangle
	glVertex3f(0.68f + x_pos, -0.11f + y_pos, 0.0f);
	glVertex3f(0.68f + x_pos, -0.16f + y_pos, 0.0f);
	glVertex3f(0.64f + x_pos, -0.16f + y_pos, 0.0f);

	// Set the vertice for left triangle
	glVertex3f(0.48f + x_pos, -0.11f + y_pos, 0.0f);
	glVertex3f(0.48f + x_pos, -0.16f + y_pos, 0.0f);
	glVertex3f(0.52f + x_pos, -0.16f + y_pos, 0.0f);

	glEnd();

	// Lower Rectangular Quad
	glBegin(GL_QUADS);

	//import the color
	glColor3f(0.9f, 0.0f, 0.0f);

	//set the vertices
	glVertex2d(0.48f + x_pos, -0.50f + y_pos);
	glVertex2d(0.48f + x_pos, -0.55f + y_pos);
	glVertex2d(0.68f + x_pos, -0.55f + y_pos);
	glVertex2d(0.68f + x_pos, -0.50f + y_pos);

	glEnd();

	// Swastik using line strips and point
	glBegin(GL_LINE_STRIP);

	// Draw the lines
	glVertex2f(0.60f + x_pos, -0.26f + y_pos);
	glVertex2f(0.58f + x_pos, -0.26f + y_pos);
	glVertex2f(0.58f + x_pos, -0.30f + y_pos);
	glVertex2f(0.56f + x_pos, -0.30f + y_pos);

	glEnd();

	// 1. Dots inside swastik: right upper
	glBegin(GL_QUADS);

	// Draw the points
	glVertex2f(0.587000 + x_pos, -0.267000 + y_pos);
	glVertex2f(0.593000 + x_pos, -0.267000 + y_pos);
	glVertex2f(0.593000 + x_pos, -0.273000 + y_pos);
	glVertex2f(0.587000 + x_pos, -0.273000 + y_pos);

	glEnd();

	// 2. Dots inside swastik: right lower
	glBegin(GL_QUADS);

	// Draw the points
	glVertex2f(0.587000 + x_pos, -0.287000 + y_pos);
	glVertex2f(0.593000 + x_pos, -0.287000 + y_pos);
	glVertex2f(0.593000 + x_pos, -0.293000 + y_pos);
	glVertex2f(0.587000 + x_pos, -0.293000 + y_pos);

	glEnd();

	// 3. Dots inside swastik: left lower
	glBegin(GL_QUADS);

	// Draw the points
	glVertex2f(0.567000 + x_pos, -0.287000 + y_pos);
	glVertex2f(0.573000 + x_pos, -0.287000 + y_pos);
	glVertex2f(0.573000 + x_pos, -0.293000 + y_pos);
	glVertex2f(0.567000 + x_pos, -0.293000 + y_pos);

	glEnd();

	// 4. Dots inside swastik: left upper
	glBegin(GL_QUADS);

	// Draw the points
	glVertex2f(0.567000 + x_pos, -0.267000 + y_pos);
	glVertex2f(0.573000 + x_pos, -0.267000 + y_pos);
	glVertex2f(0.573000 + x_pos, -0.273000 + y_pos);
	glVertex2f(0.567000 + x_pos, -0.273000 + y_pos);

	glEnd();

	glBegin(GL_LINE_STRIP);

	glVertex2f(0.56f + x_pos, -0.26f + y_pos);
	glVertex2f(0.56f + x_pos, -0.28f + y_pos);
	glVertex2f(0.60f + x_pos, -0.28f + y_pos);
	glVertex2f(0.60f + x_pos, -0.30f + y_pos);

	glEnd();

	// Middle Polygon for diya place
	glBegin(GL_POLYGON);

	//import the color
	glColor3f(0.1f, 0.1f, 0.1f);

	//set the vertices
	glVertex2d(0.58f + x_pos, -0.35f + y_pos);
	glVertex2d(0.56f + x_pos, -0.38f + y_pos);
	glVertex2d(0.56f + x_pos, -0.45f + y_pos);
	glVertex2d(0.60f + x_pos, -0.45f + y_pos);
	glVertex2d(0.60f + x_pos, -0.38f + y_pos);

	glEnd();

	// Quad for diya
	glBegin(GL_QUADS);

	//import the color
	glColor3f(1.0f, 0.6470588235294, 0.0f);

	//set the vertices for diya
	glVertex2d(0.5750f + x_pos, -0.45f + y_pos);
	glVertex2d(0.5850f + x_pos, -0.45f + y_pos);
	glVertex2d(0.59f + x_pos, -0.43f + y_pos);
	glVertex2d(0.57f + x_pos, -0.43f + y_pos);

	//import the color for flame
	glColor3f(1.0f, 0.0, 0.0f);

	// set the vertices for flame
	glVertex2d(0.58f + x_pos, -0.43f + y_pos);
	glVertex2d(0.5825f + x_pos, -0.41f + y_pos);
	glVertex2d(0.58f + x_pos, -0.39f + y_pos);
	glVertex2d(0.5775f + x_pos, -0.43f + y_pos);

	glEnd();
}

void Tulsi_leaf(float x_pos, float y_pos)
{
	// Quads for leafs
	glBegin(GL_QUADS);

	// Set the color for leaf
	glColor3f(0.1f, 0.8f, 0.1f);

	// set the vertices

	// 1. bottom right first from down
	glVertex2d(0.63f + x_pos, -0.13f + y_pos);
	glVertex2d(0.64f + x_pos, -0.12f + y_pos);
	glVertex2d(0.65f + x_pos, -0.13f + y_pos);
	glVertex2d(0.64f + x_pos, -0.14f + y_pos);

	glVertex2d(0.62f + x_pos, -0.10f + y_pos);
	glVertex2d(0.62f + x_pos, -0.09f + y_pos);
	glVertex2d(0.64f + x_pos, -0.08f + y_pos);
	glVertex2d(0.63f + x_pos, -0.10f + y_pos);

	glVertex2d(0.66f + x_pos, -0.11f + y_pos);
	glVertex2d(0.67f + x_pos, -0.10f + y_pos);
	glVertex2d(0.69f + x_pos, -0.11f + y_pos);
	glVertex2d(0.67f + x_pos, -0.12f + y_pos);

	glVertex2d(0.67f + x_pos, -0.07f + y_pos);
	glVertex2d(0.67f + x_pos, -0.06f + y_pos);
	glVertex2d(0.69f + x_pos, -0.05f + y_pos);
	glVertex2d(0.68f + x_pos, -0.07f + y_pos);

	glVertex2d(0.70f + x_pos, -0.09f + y_pos);
	glVertex2d(0.71f + x_pos, -0.08f + y_pos);
	glVertex2d(0.73f + x_pos, -0.09f + y_pos);
	glVertex2d(0.71f + x_pos, -0.10f + y_pos);

	glVertex2d(0.70f + x_pos, -0.07f + y_pos);
	glVertex2d(0.70f + x_pos, -0.06f + y_pos);
	glVertex2d(0.72f + x_pos, -0.05f + y_pos);
	glVertex2d(0.71f + x_pos, -0.07f + y_pos);

	// 2. Middle Right branch
	glVertex2d(0.62f + x_pos, -0.06f + y_pos);
	glVertex2d(0.63f + x_pos, -0.05f + y_pos);
	glVertex2d(0.65f + x_pos, -0.06f + y_pos);
	glVertex2d(0.63f + x_pos, -0.07f + y_pos);

	glVertex2d(0.61f + x_pos, -0.03f + y_pos);
	glVertex2d(0.60f + x_pos, -0.02f + y_pos);
	glVertex2d(0.61f + x_pos, -0.00f + y_pos);
	glVertex2d(0.62f + x_pos, -0.02f + y_pos);

	glVertex2d(0.65f + x_pos, -0.03f + y_pos);
	glVertex2d(0.66f + x_pos, -0.02f + y_pos);
	glVertex2d(0.68f + x_pos, -0.03f + y_pos);
	glVertex2d(0.66f + x_pos, -0.04f + y_pos);

	glVertex2d(0.64f + x_pos, -0.02f + y_pos);
	glVertex2d(0.64f + x_pos, -0.01f + y_pos);
	glVertex2d(0.66f + x_pos, -0.00f + y_pos);
	glVertex2d(0.65f + x_pos, -0.02f + y_pos);

	// 3. Third right left from bottom
	glVertex2d(0.59f + x_pos, -0.04f + y_pos);
	glVertex2d(0.59f + x_pos, -0.03f + y_pos);
	glVertex2d(0.60f + x_pos, -0.02f + y_pos);
	glVertex2d(0.60f + x_pos, -0.04f + y_pos);

	// 4. Second top right leaf
	glVertex2d(0.59f + x_pos, -0.00f + y_pos);
	glVertex2d(0.59f + x_pos, +0.01f + y_pos);
	glVertex2d(0.61f + x_pos, +0.02f + y_pos);
	glVertex2d(0.60f + x_pos, -0.00f + y_pos);

	// 5. Top leaf
	glVertex2d(0.58f + x_pos, +0.01f + y_pos);
	glVertex2d(0.57f + x_pos, +0.02f + y_pos);
	glVertex2d(0.58f + x_pos, +0.04f + y_pos);
	glVertex2d(0.59f + x_pos, +0.02f + y_pos);

	// 6. Bottom left first from down
	glVertex2d(0.54f + x_pos, -0.13f + y_pos);
	glVertex2d(0.53f + x_pos, -0.12f + y_pos);
	glVertex2d(0.51f + x_pos, -0.13f + y_pos);
	glVertex2d(0.53f + x_pos, -0.14f + y_pos);

	glVertex2d(0.54f + x_pos, -0.10f + y_pos);
	glVertex2d(0.54f + x_pos, -0.09f + y_pos);
	glVertex2d(0.52f + x_pos, -0.08f + y_pos);
	glVertex2d(0.53f + x_pos, -0.10f + y_pos);

	glVertex2d(0.49f + x_pos, -0.10f + y_pos);
	glVertex2d(0.48f + x_pos, -0.09f + y_pos);
	glVertex2d(0.46f + x_pos, -0.10f + y_pos);
	glVertex2d(0.48f + x_pos, -0.11f + y_pos);

	glVertex2d(0.49f + x_pos, -0.07f + y_pos);
	glVertex2d(0.49f + x_pos, -0.06f + y_pos);
	glVertex2d(0.47f + x_pos, -0.05f + y_pos);
	glVertex2d(0.48f + x_pos, -0.07f + y_pos);

	glVertex2d(0.46f + x_pos, -0.07f + y_pos);
	glVertex2d(0.46f + x_pos, -0.06f + y_pos);
	glVertex2d(0.43f + x_pos, -0.05f + y_pos);
	glVertex2d(0.45f + x_pos, -0.07f + y_pos);

	// 7. Bottom left second from down branch
	glVertex2d(0.57f + x_pos, -0.09f + y_pos);
	glVertex2d(0.56f + x_pos, -0.09f + y_pos);
	glVertex2d(0.55f + x_pos, -0.10f + y_pos);
	glVertex2d(0.56f + x_pos, -0.10f + y_pos);

	glVertex2d(0.57f + x_pos, -0.09f + y_pos);
	glVertex2d(0.58f + x_pos, -0.09f + y_pos);
	glVertex2d(0.58f + x_pos, -0.08f + y_pos);
	glVertex2d(0.57f + x_pos, -0.08f + y_pos);

	glVertex2d(0.56f + x_pos, -0.08f + y_pos);
	glVertex2d(0.55f + x_pos, -0.08f + y_pos);
	glVertex2d(0.54f + x_pos, -0.06f + y_pos);
	glVertex2d(0.56f + x_pos, -0.07f + y_pos);

	// 8. Top left second from up branch
	glVertex2d(0.54f + x_pos, -0.05f + y_pos);
	glVertex2d(0.53f + x_pos, -0.04f + y_pos);
	glVertex2d(0.51f + x_pos, -0.05f + y_pos);
	glVertex2d(0.53f + x_pos, -0.06f + y_pos);

	glVertex2d(0.54f + x_pos, -0.02f + y_pos);
	glVertex2d(0.53f + x_pos, -0.02f + y_pos);
	glVertex2d(0.52f + x_pos, -0.00f + y_pos);
	glVertex2d(0.54f + x_pos, -0.01f + y_pos);

	glVertex2d(0.51f + x_pos, -0.02f + y_pos);
	glVertex2d(0.50f + x_pos, -0.02f + y_pos);
	glVertex2d(0.48f + x_pos, -0.00f + y_pos);
	glVertex2d(0.51f + x_pos, -0.01f + y_pos);

	// 9. Top left branch with single leaf
	glVertex2d(0.56f + x_pos, -0.01f + y_pos);
	glVertex2d(0.55f + x_pos, -0.01f + y_pos);
	glVertex2d(0.54f + x_pos, +0.01f + y_pos);
	glVertex2d(0.56f + x_pos, -0.00f + y_pos);

	glEnd();
}

void Tulsi_Branches(float x_pos, float y_pos)
{
	//Tulas plant branches
	glBegin(GL_LINE_STRIP);

	// Set the color
	glColor3f(0.0f, 0.9f, 0.0f);

	// Virtical strip
	glVertex2f(0.58f + x_pos, 0.01f + y_pos);
	glVertex2f(0.58f + x_pos, -0.16f + y_pos);

	// Sub-strip from right bottom branch
	glVertex2f(0.58f + x_pos, -0.14f + y_pos);
	glVertex2f(0.70f + x_pos, -0.07f + y_pos);
	glVertex2f(0.58f + x_pos, -0.14f + y_pos);

	glVertex2f(0.60f + x_pos, -0.13f + y_pos);
	glVertex2f(0.63f + x_pos, -0.13f + y_pos);
	glVertex2f(0.60f + x_pos, -0.13f + y_pos);

	glVertex2f(0.61f + x_pos, -0.12f + y_pos);
	glVertex2f(0.62f + x_pos, -0.10f + y_pos);
	glVertex2f(0.61f + x_pos, -0.12f + y_pos);

	glVertex2f(0.63f + x_pos, -0.11f + y_pos);
	glVertex2f(0.66f + x_pos, -0.11f + y_pos);
	glVertex2f(0.63f + x_pos, -0.11f + y_pos);

	glVertex2f(0.65f + x_pos, -0.10f + y_pos);
	glVertex2f(0.67f + x_pos, -0.07f + y_pos);
	glVertex2f(0.65f + x_pos, -0.10f + y_pos);

	glVertex2f(0.67f + x_pos, -0.09f + y_pos);
	glVertex2f(0.70f + x_pos, -0.09f + y_pos);
	glVertex2f(0.67f + x_pos, -0.09f + y_pos);
	glVertex2f(0.58f + x_pos, -0.14f + y_pos);

	// #################################

	glVertex2f(0.58f + x_pos, -0.08f + y_pos);
	glVertex2f(0.64f + x_pos, -0.02f + y_pos);
	glVertex2f(0.58f + x_pos, -0.08f + y_pos);

	glVertex2f(0.60f + x_pos, -0.06f + y_pos);
	glVertex2f(0.62f + x_pos, -0.06f + y_pos);
	glVertex2f(0.60f + x_pos, -0.06f + y_pos);

	glVertex2f(0.61f + x_pos, -0.05f + y_pos);
	glVertex2f(0.61f + x_pos, -0.03f + y_pos);
	glVertex2f(0.61f + x_pos, -0.05f + y_pos);

	glVertex2f(0.63f + x_pos, -0.03f + y_pos);
	glVertex2f(0.66f + x_pos, -0.03f + y_pos);
	glVertex2f(0.63f + x_pos, -0.03f + y_pos);
	glVertex2f(0.58f + x_pos, -0.08f + y_pos);

	// #################################

	glVertex2f(0.58f + x_pos, -0.05f + y_pos);
	glVertex2f(0.59f + x_pos, -0.04f + y_pos);
	glVertex2f(0.58f + x_pos, -0.05f + y_pos);

	// #################################

	glVertex2f(0.58f + x_pos, -0.01f + y_pos);
	glVertex2f(0.59f + x_pos, 0.00f + y_pos);
	glVertex2f(0.58f + x_pos, -0.01f + y_pos);

	// Sub-strip for left branch
	glVertex2f(0.58f + x_pos, -0.14f + y_pos);
	glVertex2f(0.46f + x_pos, -0.07f + y_pos);
	glVertex2f(0.58f + x_pos, -0.14f + y_pos);

	glVertex2f(0.56f + x_pos, -0.13f + y_pos);
	glVertex2f(0.54f + x_pos, -0.13f + y_pos);
	glVertex2f(0.56f + x_pos, -0.13f + y_pos);

	glVertex2f(0.55f + x_pos, -0.12f + y_pos);
	glVertex2f(0.54f + x_pos, -0.10f + y_pos);
	glVertex2f(0.55f + x_pos, -0.12f + y_pos);

	glVertex2f(0.51f + x_pos, -0.10f + y_pos);
	glVertex2f(0.49f + x_pos, -0.10f + y_pos);
	glVertex2f(0.51f + x_pos, -0.10f + y_pos);

	glVertex2f(0.50f + x_pos, -0.09f + y_pos);
	glVertex2f(0.49f + x_pos, -0.07f + y_pos);
	glVertex2f(0.50f + x_pos, -0.09f + y_pos);
	glVertex2f(0.58f + x_pos, -0.14f + y_pos);

	// #################################

	glVertex2f(0.58f + x_pos, -0.11f + y_pos);
	glVertex2f(0.56f + x_pos, -0.08f + y_pos);
	glVertex2f(0.58f + x_pos, -0.11f + y_pos);

	// #################################

	glVertex2f(0.58f + x_pos, -0.06f + y_pos);
	glVertex2f(0.51f + x_pos, -0.02f + y_pos);
	glVertex2f(0.58f + x_pos, -0.06f + y_pos);

	glVertex2f(0.56f + x_pos, -0.05f + y_pos);
	glVertex2f(0.54f + x_pos, -0.05f + y_pos);
	glVertex2f(0.56f + x_pos, -0.05f + y_pos);

	glVertex2f(0.55f + x_pos, -0.04f + y_pos);
	glVertex2f(0.54f + x_pos, -0.02f + y_pos);
	glVertex2f(0.55f + x_pos, -0.04f + y_pos);
	glVertex2f(0.58f + x_pos, -0.06f + y_pos);

	// #################################

	glVertex2f(0.58f + x_pos, -0.03f + y_pos);
	glVertex2f(0.56f + x_pos, -0.01f + y_pos);
	glVertex2f(0.58f + x_pos, -0.03f + y_pos);

	glEnd();
}

//EOF