// header files
#include<GL/freeglut.h>

// global variable declarations
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

	// code
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Dr. Prasad R. Joshi");

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

void display(void)
{
	// function declaration
	void Boat_Prasad(float x_pos, float y_pos);

	glClear(GL_COLOR_BUFFER_BIT);


	Boat_Prasad(0.0f, 0.0f);


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

void Boat_Prasad(float x_pos, float y_pos)
{
	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(0.35882f, 0.227451f, 0.2f);
	glVertex3f(-0.1f + x_pos, 0.1f + y_pos, 0.0f);
	glColor3f(0.35882f, 0.227451f, 0.2f);
	glVertex3f(0.0f + x_pos, -0.1f + y_pos, 0.0f);
	glColor3f(0.35882f, 0.227451f, 0.2f);
	glVertex3f(0.0f + x_pos, 0.05f + y_pos, 0.0f);
	glColor3f(0.35882f, 0.227451f, 0.2f);
	glVertex3f(0.25f + x_pos, -0.1f + y_pos, 0.0f);
	glColor3f(0.35882f, 0.227451f, 0.2f);
	glVertex3f(0.25f + x_pos, 0.05f + y_pos, 0.0f);
	glColor3f(0.35882f, 0.227451f, 0.2f);
	glVertex3f(0.35f + x_pos, 0.1f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.5f, 0.4f, 0.1f);
	glVertex3f(0.05f + x_pos, 0.11f + y_pos, 0.0f);
	glColor3f(0.71f, 0.4f, 0.1f);
	glVertex3f(0.06f + x_pos, 0.11f + y_pos, 0.0f);
	glColor3f(0.7f, 0.4f, 0.1f);
	glVertex3f(0.145f + x_pos, -0.1f + y_pos, 0.0f);
	glColor3f(0.5f, 0.4f, 0.1f);
	glVertex3f(0.155f + x_pos, -0.1f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.5f, 0.3f, 0.1f);
	glVertex3f(0.15f + x_pos, -0.1f + y_pos, 0.0f);
	glColor3f(0.5f, 0.4f, 0.1f);
	glVertex3f(0.145f + x_pos, -0.15f + y_pos, 0.0f);
	glColor3f(0.5f, 0.4f, 0.1f);
	glVertex3f(0.2f + x_pos, -0.12f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.5f, 0.4f, 0.1f);
	glVertex3f(0.145f + x_pos, -0.15f + y_pos, 0.0f);
	glColor3f(0.5f, 0.4f, 0.1f);
	glVertex3f(0.2f + x_pos, -0.12f + y_pos, 0.0f);
	glColor3f(0.5f, 0.3f, 0.1f);
	glVertex3f(0.220f + x_pos, -0.17f + y_pos, 0.0f);
	glColor3f(0.5f, 0.3f, 0.1f);
	glVertex3f(0.165f + x_pos, -0.2f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.5f, 0.4f, 0.1f);
	glVertex3f(0.2f + x_pos, 0.05f + y_pos, 0.0f);
	glColor3f(0.51f, 0.4f, 0.1f);
	glVertex3f(0.21f + x_pos, 0.05f + y_pos, 0.0f);
	glColor3f(0.5f, 0.4f, 0.1f);
	glVertex3f(0.21f + x_pos, 0.4f + y_pos, 0.0f);
	glColor3f(0.5f, 0.4f, 0.1f);
	glVertex3f(0.2f + x_pos, 0.4f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.8f, 0.1f, 0.1f);
	glVertex3f(0.3f + x_pos, 0.32f + y_pos, 0.0f);
	glColor3f(0.8f, 0.1f, 0.1f);
	glVertex3f(0.2f + x_pos, 0.32f + y_pos, 0.0f);
	glColor3f(0.8f + x_pos, 0.1f, 0.1f);
	glVertex3f(0.3f + x_pos, 0.4f + y_pos, 0.0f);
	glColor3f(0.8f, 0.1f, 0.1f);
	glVertex3f(0.2f + x_pos, 0.4f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.8f, 1.0f, 1.0f);
	glVertex3f(0.1f + x_pos, 0.1f + y_pos, 0.0f);
	glColor3f(0.8f, 1.0f, 1.0f);
	glVertex3f(0.2f + x_pos, 0.1f + y_pos, 0.0f);
	glColor3f(0.8f, 1.0f, 1.0f);
	glVertex3f(0.2f + x_pos, 0.3f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.5f, 0.4f, 0.1f);
	glVertex3f(0.07f + x_pos, 0.05f + y_pos, 0.0f);
	glColor3f(0.5f, 0.4f, 0.1f);
	glVertex3f(0.07f + x_pos, 0.06f + y_pos, 0.0f);
	glColor3f(0.5f, 0.3f, 0.1f);
	glVertex3f(0.1f + x_pos, 0.05f + y_pos, 0.0f);
	glColor3f(0.5f, 0.3f, 0.1f);
	glVertex3f(0.1f + x_pos, 0.06f + y_pos, 0.0f);
	glEnd();
}
