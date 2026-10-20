// header files
#include<GL/freeglut.h>

// global variable declarations
BOOL bFullScreen = FALSE;

// Entry-point function
int main(int argc, char* argv[])
{
	//local function declarations
	int initialize(void);
	void resize(int, int);
	void display(void);
	void keyboard(unsigned char, int, int);
	void mouse(int, int, int, int);
	void uninitialize(void);

	// code
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Shivkumar Anil Ople");

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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	return(0);
}

void resize(int width, int height)
{
	// code
	glViewport(0, 0, width, height);
}

void FlowerPot_Shivkumar(float x_pos, float y_pos)
{
	//Perfect Pot with Quads
	glBegin(GL_QUADS);

	glColor3f(0.5f, 0.35f, 0.05f);
	glVertex2f(-0.02+x_pos, -0.08+y_pos);

	glColor3f(0.5f, 0.35f, 0.05f);
	glVertex2f(-0.06+x_pos, 0.09+y_pos);

	glColor3f(0.5f, 0.35f, 0.05f);
	glVertex2f(0.06 + x_pos, 0.09 + y_pos);

	glColor3f(0.5f, 0.35f, 0.05f);
	glVertex2f(0.02 + x_pos, -0.08+ y_pos);

	glEnd();

	glBegin(GL_LINES);

	// Trying Exact Middle Leaves
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.03f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.04f + x_pos, 0.15f + y_pos, 0.0f);


	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.03f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.02f + x_pos, 0.15f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.03f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.01f + x_pos, 0.15f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.03f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.01f + x_pos, 0.15f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.03f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.05f + x_pos, 0.15f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.03f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.06f + x_pos, 0.15f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.03f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.07f + x_pos, 0.15f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.03f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.08f + x_pos, 0.15f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.03f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.09f + x_pos, 0.15f + y_pos, 0.0f);




	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.01f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.01f + x_pos, 0.15f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.01f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.05f + x_pos, 0.15f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.01f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.06f + x_pos, 0.15f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.01f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.07f + x_pos, 0.15f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.01f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.08f + x_pos, 0.15f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.01f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.09f + x_pos, 0.15f + y_pos, 0.0f);



	//Trying Middle Right Leaves

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.05f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.04f + x_pos, 0.15f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.05f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.03f + x_pos, 0.15f+ y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.05f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.02f + x_pos, 0.15f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.05f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.01f + x_pos, 0.15f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.05f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.05f + x_pos, 0.15f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.05f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.06f + x_pos, 0.15f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.05f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.07f + x_pos, 0.15f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.05f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.08f + x_pos, 0.15f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.05f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.09f + x_pos, 0.15f + y_pos, 0.0f);

	// Trying Middle Leaves

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.04f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.02f + x_pos, 0.15f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.04f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.03f + x_pos, 0.15f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.04f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.04f + x_pos, 0.15f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.04f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.05f + x_pos, 0.15f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.04f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.06f + x_pos, 0.15f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.04f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.07f + x_pos, 0.15f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.04f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.08f + x_pos, 0.15f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.04f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.09f + x_pos, 0.15f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.04f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.001f + x_pos, 0.15f + y_pos, 0.0f);


	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.04f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.002f + x_pos, 0.15f + y_pos, 0.0f);


	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.04f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.003f + x_pos, 0.15f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.04f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.004f + x_pos, 0.15f + y_pos, 0.0f);


	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.04f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.003f + x_pos, 0.15f + y_pos, 0.0f); // These above are middle right one leaves


	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.04f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.005f + x_pos, 0.15f + y_pos, 0.0f);


	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.04f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.007f + x_pos, 0.15f + y_pos, 0.0f);


	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.04f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.008f + x_pos, 0.15f + y_pos, 0.0f);


	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.05f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.01f + x_pos, 0.1f + y_pos, 0.0f);


	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.05f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.02f + x_pos, 0.1f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.05f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.04f + x_pos, 0.03f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.05f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.04f + x_pos, 0.04f + y_pos, 0.0f);


	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.05f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.04f + x_pos, 0.05f + y_pos, 0.0f);



	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.05f + x_pos, 0.09f + y_pos, 0.0f);


	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.04f + x_pos, 0.06f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.05f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.04f + x_pos, 0.08f + y_pos, 0.0f);


	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.06f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.1f + x_pos, 0.02f + y_pos, 0.0f);


	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.06f + x_pos, 0.09f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.1f + x_pos, 0.02f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.1f + x_pos, 0.001f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.1f + x_pos, 0.1f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.1f + x_pos, 0.01f + y_pos, 0.0f);  ////  Seems Culprit

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.1f + x_pos, 0.02f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.1f + x_pos, 0.03f + y_pos, 0.0f);


	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.1f + x_pos, 0.04f + y_pos, 0.0f);



	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.1f + x_pos, 0.05f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.1f + x_pos, 0.06f + y_pos, 0.0f);



	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.1f + x_pos, 0.07f + y_pos, 0.0f);



	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.06f + x_pos, 0.08f + y_pos, 0.0f);
	//Left(X,Y)
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.1f + x_pos, 0.09f + y_pos, 0.0f);



	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.1f + x_pos, 0.001f + y_pos, 0.0f);


	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.1f + x_pos, 0.001f + y_pos, 0.0f);


	// RIGHT LEAVES

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.1f + x_pos, 0.01f + y_pos, 0.0f);


	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.1f + x_pos, 0.1f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.1f + x_pos, 0.02f + y_pos, 0.0f);  /// Seems Culprit

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.1f + x_pos, 0.02f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.1f + x_pos, 0.03f + y_pos, 0.0f);


	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.1f + x_pos, 0.04f + y_pos, 0.0f);



	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.1f + x_pos, 0.05f + y_pos, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.1f + x_pos, 0.06f + y_pos, 0.0f);



	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.1f + x_pos, 0.07f + y_pos, 0.0f);



	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.06f + x_pos, 0.08f + y_pos, 0.0f);
	//Left(X,Y)
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.1f + x_pos, 0.09f + y_pos, 0.0f);



	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.1f + x_pos, 0.001f + y_pos, 0.0f);


	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.1f + x_pos, 0.001f + y_pos, 0.0f);


	glEnd();

}


void display(void) 
{
	// code
	glClear(GL_COLOR_BUFFER_BIT);
    
	FlowerPot_Shivkumar(0.0, 0.0);
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
	case 'F':
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
	}
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
