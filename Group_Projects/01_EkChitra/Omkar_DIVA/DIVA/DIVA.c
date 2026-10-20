// header files
#include<GL/freeglut.h>

#define VALUE_FROM_PERCENT(complet,percent) (complet * percent / 100 )

//globle variable delaratoins
BOOL bFullscreen = FALSE;

//Entry-point function
int main(int argc, char* argv[])
{
	// local function declarations
	int initialize(void);
	void resize(int, int);
	void display(void);
	void keyboard(unsigned char, int, int);
	void mouse(int, int, int ,int);
	void uninitialize(void);

	// code
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Omkar Umesh Jadhav");

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
void DIVA_Omkar(float x_pos, float y_pos, float percent)
{
	// DIVA
	glBegin(GL_QUADS);
	{
		glColor3f(0.6f, 0.2f, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT( -0.225f,percent) + x_pos, VALUE_FROM_PERCENT(0.0f,percent) + y_pos, 0.0f);

		glColor3f(0.6f, 0.2f, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT(0.225f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);

		glColor3f(0.6f, 0.2f, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT(0.125f, percent) + x_pos, VALUE_FROM_PERCENT(-0.175f, percent) + y_pos, 0.0f);

		glColor3f(0.6f, 0.2f, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT(-0.125f, percent) + x_pos, VALUE_FROM_PERCENT(-0.175f, percent) + y_pos, 0.0f);
	}
	glEnd();

	//JYOT
	glBegin(GL_QUADS);
	{
		glColor3f(1.0f, 1.0f, 0.1f);
		glVertex3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);

		glColor3f(1.0f, 1.0f, 0.1f);
		glVertex3f(VALUE_FROM_PERCENT(-0.01875f, percent) + x_pos, VALUE_FROM_PERCENT(0.075f, percent) + y_pos, 0.0f);

		glColor3f(1.0f, 1.0f, 0.1f);
		glVertex3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.15f, percent) + y_pos, 0.0f);

		glColor3f(1.0f, 1.0f, 0.1f);
		glVertex3f(VALUE_FROM_PERCENT(0.01875f, percent) + x_pos, VALUE_FROM_PERCENT(0.075f, percent) + y_pos, 0.0f);
	}
	glEnd();

}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	DIVA_Omkar(0.0f,0.0f, 100);
	

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
		if (bFullscreen == FALSE)
		{
			glutFullScreen();
			bFullscreen = TRUE;
		}
		else
		{
			glutLeaveFullScreen();
			bFullscreen = FALSE;
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

