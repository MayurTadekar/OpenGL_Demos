// header files
#include<GL/freeglut.h>

// global variable declarations
BOOL bFullScreen = FALSE;

// Macro
#define VALUE_FROM_POINT(complete, percent) (complete * percent  / 100)

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
	glutCreateWindow("PATI");

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
    // Function declaration
    void Pati(float x_pos, float y_pos, float percent, char * msg);
	// code
	glClear(GL_COLOR_BUFFER_BIT);
	
    Pati(0.0f, 0.0f, 70.0f, "BUDRUK");
    Pati(0.50f, 0.0f, 70.0f, "KHURD");

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


void Pati_Atharv(float x_pos, float y_pos, float percent, char * msg)
{
    glBegin(GL_QUADS);
    {
        glColor3f(0.6f, 0.3f, 0.0f);
        glVertex2f(VALUE_FROM_POINT(-0.29, percent) + x_pos, VALUE_FROM_POINT(-0.38, percent) + y_pos);
        glVertex2f(VALUE_FROM_POINT(-0.29, percent) + x_pos, VALUE_FROM_POINT(-0.75, percent) + y_pos);
        glColor3f(0.7f, 0.5f, 0.0f);
        glVertex2f(VALUE_FROM_POINT(-0.25, percent) + x_pos, VALUE_FROM_POINT(-0.75, percent) + y_pos);
        glVertex2f(VALUE_FROM_POINT(-0.25, percent) + x_pos, VALUE_FROM_POINT(-0.38, percent) + y_pos);
    }
    glEnd();

    glColor3f(0.7f, 0.5f, 0.0f);
    glBegin(GL_QUADS);
    {
        glVertex2f(VALUE_FROM_POINT(-0.40, percent) + x_pos, VALUE_FROM_POINT(-0.40, percent) + y_pos);
        glVertex2f(VALUE_FROM_POINT(-0.40, percent) + x_pos, VALUE_FROM_POINT(-0.53, percent) + y_pos);
        glVertex2f(VALUE_FROM_POINT(-0.12, percent) + x_pos, VALUE_FROM_POINT(-0.53, percent) + y_pos);
        glVertex2f(VALUE_FROM_POINT(-0.12, percent) + x_pos, VALUE_FROM_POINT(-0.40, percent) + y_pos);
    }
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2f(VALUE_FROM_POINT(-0.34f , percent)+ x_pos, VALUE_FROM_POINT( -0.48f, percent) + y_pos);
    char *string1 = msg;

    for (int i = 0; i < strlen(string1); i++) 
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string1[i]); 
    }
}