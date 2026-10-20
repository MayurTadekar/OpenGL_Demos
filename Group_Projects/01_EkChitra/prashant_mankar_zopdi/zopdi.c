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
	glutCreateWindow("Prashant Doliram Mankar");

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
	// Function prototype
	void zopdi_prashant(float x_pos, float y_pos);
	// code
	glClear(GL_COLOR_BUFFER_BIT);

	zopdi_prashant(0.5f, 0.5f);

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

void zopdi_prashant(float x_pos, float y_pos)
{
	// Code
	glBegin(GL_QUADS);

	glColor3f(0.6f, 0.3f, 0.0f);
	glVertex3f(-0.8f + x_pos, -0.3f + y_pos, 0.0f); // left
	glVertex3f(-0.8f + x_pos, -0.6f + y_pos, 0.0f); // bottom
	glVertex3f(-0.4f + x_pos, -0.6f + y_pos, 0.0f); // right
	glVertex3f(-0.4f + x_pos, -0.3f + y_pos, 0.0f); // top

    glColor3f(0.9f, 0.9f, 0.9f);
	glVertex3f(-0.7f + x_pos, -0.45f + y_pos, 0.0f); // left
	glVertex3f(-0.7f + x_pos, -0.6f + y_pos, 0.0f); // bottom
	glVertex3f(-0.6f + x_pos, -0.6f + y_pos, 0.0f); // right
	glVertex3f(-0.6f + x_pos, -0.45f + y_pos, 0.0f); // top

	glVertex3f(-0.55f + x_pos, -0.4f + y_pos, 0.0f); // left
	glVertex3f(-0.55f + x_pos, -0.5f + y_pos, 0.0f); // bottom
	glVertex3f(-0.45f + x_pos, -0.5f + y_pos, 0.0f); // right
	glVertex3f(-0.45f + x_pos, -0.4f + y_pos, 0.0f); // top

	glEnd();

    glBegin(GL_LINES);

    glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-0.5f + x_pos, -0.4f + y_pos, 0.0f);
	glVertex3f(-0.5f + x_pos, -0.5f + y_pos, 0.0f);
    
	glVertex3f(-0.55f + x_pos, -0.45f + y_pos, 0.0f);
	glVertex3f(-0.45f + x_pos, -0.45f + y_pos, 0.0f);

    glColor3f(0.8f, 0.7f, 0.5f);
	glVertex3f(-0.65f + x_pos, -0.05f + y_pos, 0.0f);
	glVertex3f(-0.6f + x_pos, -0.1f + y_pos, 0.0f);

	glVertex3f(-0.6f + x_pos, -0.05f + y_pos, 0.0f);
	glVertex3f(-0.6f + x_pos, -0.1f + y_pos, 0.0f);

	glVertex3f(-0.55f + x_pos, -0.05f + y_pos, 0.0f);
	glVertex3f(-0.6f + x_pos, -0.1f + y_pos, 0.0f);

    glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-0.65f + x_pos, -0.15f + y_pos, 0.0f);
	glVertex3f(-0.63f + x_pos, -0.25f + y_pos, 0.0f);

    glEnd();

    glBegin(GL_TRIANGLES);
	
    glColor3f(0.8f, 0.7f, 0.5f);
	glVertex3f(-0.75f + x_pos, -0.3f + y_pos, 0.0f); //center
	glVertex3f(-0.6f + x_pos, -0.1f + y_pos, 0.0f); // right
	glVertex3f(-0.85f + x_pos, -0.35f + y_pos, 0.0f); //left

	glVertex3f(-0.75f + x_pos, -0.35f + y_pos, 0.0f); //center
	glVertex3f(-0.6f + x_pos, -0.1f + y_pos, 0.0f); // right
	glVertex3f(-0.75f + x_pos, -0.3f + y_pos, 0.0f); //left

	glVertex3f(-0.7f + x_pos, -0.35f + y_pos, 0.0f); //center
	glVertex3f(-0.6f + x_pos, -0.1f + y_pos, 0.0f); // right
	glVertex3f(-0.73f + x_pos, -0.3f + y_pos, 0.0f); //left

	glVertex3f(-0.6f + x_pos, -0.35f + y_pos, 0.0f); //center
	glVertex3f(-0.6f + x_pos, -0.1f + y_pos, 0.0f); // right
	glVertex3f(-0.7f + x_pos, -0.3f + y_pos, 0.0f); //left

	glVertex3f(-0.55f + x_pos, -0.35f + y_pos, 0.0f); //center
	glVertex3f(-0.6f + x_pos, -0.1f + y_pos, 0.0f); // right
	glVertex3f(-0.6f + x_pos, -0.3f + y_pos, 0.0f); //left

	glVertex3f(-0.45f + x_pos, -0.35f + y_pos, 0.0f); //center
	glVertex3f(-0.6f + x_pos, -0.1f + y_pos, 0.0f); // right
	glVertex3f(-0.57f + x_pos, -0.3f + y_pos, 0.0f); //left

	glVertex3f(-0.45f + x_pos, -0.3f + y_pos, 0.0f); //center
	glVertex3f(-0.6f + x_pos, -0.1f + y_pos, 0.0f); // right
	glVertex3f(-0.45f + x_pos, -0.35f + y_pos, 0.0f); //left

	glVertex3f(-0.35f + x_pos, -0.35f + y_pos, 0.0f); //center
	glVertex3f(-0.6f + x_pos, -0.1f + y_pos, 0.0f); // right
	glVertex3f(-0.45f + x_pos, -0.3f + y_pos, 0.0f); //left

    glEnd();

    glBegin(GL_LINES);

    glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-0.6f + x_pos, -0.15f + y_pos, 0.0f);
	glVertex3f(-0.7f + x_pos, -0.25f + y_pos, 0.0f);

	glVertex3f(-0.6f + x_pos, -0.2f + y_pos, 0.0f);
	glVertex3f(-0.6f + x_pos, -0.28f + y_pos, 0.0f);

	glVertex3f(-0.58f + x_pos, -0.15f + y_pos, 0.0f);
	glVertex3f(-0.5f + x_pos, -0.25f + y_pos, 0.0f);

    glEnd();
}
