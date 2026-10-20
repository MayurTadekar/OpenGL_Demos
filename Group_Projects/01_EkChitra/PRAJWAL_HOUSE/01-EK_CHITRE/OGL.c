/*	|| Shree Swami Samarth ||	*/

// Code Length :- 477

// header files
#include<GL/freeglut.h>
#include<math.h>

// global variable declarations
BOOL bFullScreen = FALSE;

// Function Declaration
void House_Prajwal(float x_pos, float y_pos);

// Entry Point Function
int main(int argc, char* argv[])
{
	//local function declarations
	int initialize(void);
	void resize(int, int);
	void display(void);
	void keyboard(unsigned char, int, int);
	void mouse(int, int, int, int);
	void uninitialize(void);

	//code
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("RTR Project -> \'EK-CHITRE'.");

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
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	return(0);
}

void resize(int width, int height)
{
	// Code
	glViewport(0, 0, width, height);
}

void display(void)
{
	// Code
	glClear(GL_COLOR_BUFFER_BIT);

	//Variable declaration
	float fValue1 = 0.0f;
	float fValue2 = 0.0f;

	// function Call
	House_Prajwal(fValue1, fValue2);

	glutSwapBuffers();
}

void House_Prajwal(float x_pos, float y_pos)
{
	// Variable Declaration 
	float radius = 0.007f;
	float centerX = 0.440f;
	float centerY = -0.61f;

	/*
	x_pos = -0.4f;
	y_pos = 0.5f;
	*/

	// Base 
	glBegin(GL_QUADS);
	{
		glColor3f(0.20f, 0.0f, 0.0f);
		glVertex3f(0.10f + x_pos, -0.70f + y_pos, 0.0f);
		glVertex3f(0.70f + x_pos, -0.70f + y_pos, 0.0f);

		glColor3f(0.40f, 0.0f, 0.0f);
		glVertex3f(0.70f + x_pos, -0.75f + y_pos, 0.0f);
		glVertex3f(0.10f + x_pos, -0.75f + y_pos, 0.0f);
	}
	glEnd();

	// Wall 
	glBegin(GL_QUADS);
	{
		glColor3f(1.0f, 0.992f, 0.816f);
		glVertex3f(0.15f + x_pos, -0.45f + y_pos, 0.0f);
		glVertex3f(0.35f + x_pos, -0.45f + y_pos, 0.0f);
			
		glColor3f(1.0f, 0.992f, 0.816f);
		glVertex3f(0.35f + x_pos, -0.70f + y_pos, 0.0f);
		glVertex3f(0.15f + x_pos, -0.70f + y_pos, 0.0f);
	}
	glEnd();

	glBegin(GL_TRIANGLES);
	{
		glColor3f(1.0f, 0.992f, 0.816f);	
		glVertex3f(0.25f + x_pos, -0.30f + y_pos, 0.0f);
		glVertex3f(0.15f + x_pos, -0.45f + y_pos, 0.0f);
		glVertex3f(0.35f + x_pos, -0.45f + y_pos, 0.0f);
	}
	glEnd();

	glBegin(GL_QUADS);
	{
		glColor3f(0.531f, 0.992f, 0.816f);
		glVertex3f(0.35f + x_pos, -0.45f + y_pos, 0.0f);
		glVertex3f(0.65f + x_pos, -0.45f + y_pos, 0.0f);
		glVertex3f(0.65f + x_pos, -0.70f + y_pos, 0.0f);
		glVertex3f(0.35f + x_pos, -0.70f + y_pos, 0.0f);
	}
	glEnd();
	
	//Roof
	glBegin(GL_QUADS);
	{
		glColor3f(0.75f, 0.0f, 0.0f);
		glVertex3f(0.25f + x_pos, -0.30f + y_pos, 0.0f);
		glVertex3f(0.60f + x_pos, -0.30f + y_pos, 0.0f);

		glColor3f(0.5f, 0.0f, 0.0f);
		glVertex3f(0.70f + x_pos, -0.45f + y_pos, 0.0f);
		glVertex3f(0.35f + x_pos, -0.45f + y_pos, 0.0f);
	}
	glEnd();	

	glBegin(GL_QUADS);
	{
		glColor3f(0.75f, 0.0f, 0.0f);
		glVertex3f(0.12f + x_pos, -0.50f + y_pos, 0.0f);
		glVertex3f(0.25f + x_pos, -0.30f + y_pos, 0.0f);	

		glColor3f(0.5f, 0.0f, 0.0f);
		glVertex3f(0.25f + x_pos, -0.23f + y_pos, 0.0f);
		glVertex3f(0.10f + x_pos, -0.45f + y_pos, 0.0f); 
	}
	glEnd();

	glBegin(GL_QUADS);
	{
		glColor3f(0.5f, 0.0f, 0.0f);
		glVertex3f(0.25f + x_pos, -0.30f + y_pos, 0.0f);
		glVertex3f(0.38f + x_pos, -0.50f + y_pos, 0.0f);

		glColor3f(0.75f, 0.0f, 0.0f);
		glVertex3f(0.40f + x_pos, -0.45f + y_pos, 0.0f);
		glVertex3f(0.25f + x_pos, -0.23f + y_pos, 0.0f);
	}
	glEnd();

	// Square Window
	glBegin(GL_QUADS);
	{
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.217f + x_pos, -0.473f + y_pos, 0.0f);
		glVertex3f(0.283f + x_pos, -0.473f + y_pos, 0.0f);
		glVertex3f(0.283f + x_pos, -0.397f + y_pos, 0.0f);
		glVertex3f(0.217f + x_pos, -0.397f + y_pos, 0.0f);
	}
	glEnd();

	glBegin(GL_QUADS);
	{
		glColor3f(0.0f, 0.5f, 0.99f);
		glVertex3f(0.22f + x_pos, -0.47f + y_pos, 0.0f);	
		glVertex3f(0.28f + x_pos, -0.47f + y_pos, 0.0f);
		glColor3f(0.0f, 0.90f, 0.99f);
		glVertex3f(0.28f + x_pos, -0.40f + y_pos, 0.0f);
		glVertex3f(0.22f + x_pos, -0.40f + y_pos, 0.0f);
	}
	glEnd();

	glBegin(GL_LINES);
	{
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.25f + x_pos, -0.40f + y_pos, 0.0f);
		glVertex3f(0.25f + x_pos, -0.47f + y_pos, 0.0f);
	}
	glEnd();

	glBegin(GL_LINES);
	{
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.22f + x_pos, -0.435f + y_pos, 0.0f);
		glVertex3f(0.28f + x_pos, -0.435f + y_pos, 0.0f); 
	}
	glEnd();

	// Medium Window
	glBegin(GL_QUADS);
	{
		glColor3f(0.6f, 0.6f, 0.6f);
		glVertex3f(0.20f + x_pos, -0.535f + y_pos, 0.0f);
		glVertex3f(0.30f + x_pos, -0.535f + y_pos, 0.0f);
		glColor3f(0.6f, 0.6f, 0.6f);
		glVertex3f(0.30f + x_pos, -0.665f + y_pos, 0.0f);
		glVertex3f(0.20f + x_pos, -0.665f + y_pos, 0.0f);
	}
	glEnd();

	glBegin(GL_QUADS);
	{
		glColor3f(0.0f, 0.99f, 0.99f);
		glVertex3f(0.215f + x_pos, -0.55f + y_pos, 0.0f);
		glVertex3f(0.285f + x_pos, -0.55f + y_pos, 0.0f);
		glColor3f(0.0f, 0.75f, 0.99f);
		glVertex3f(0.285f + x_pos, -0.65f + y_pos, 0.0f);
		glVertex3f(0.215f + x_pos, -0.65f + y_pos, 0.0f);
	}
	glEnd();

	glBegin(GL_LINES);
	{
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.25f + x_pos, -0.55f + y_pos, 0.0f);
		glVertex3f(0.25f + x_pos, -0.65f + y_pos, 0.0f);
	}
	glEnd();

	glBegin(GL_LINES);
	{
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.215f + x_pos, -0.60f + y_pos, 0.0f);
		glVertex3f(0.285f + x_pos, -0.60f + y_pos, 0.0f);
	}
	glEnd();

	// Window White Platform
	glBegin(GL_QUADS);
	{
		glColor3f(0.8f, 0.8f, 0.8f);
		glVertex3f(0.185f + x_pos, -0.645f + y_pos, 0.0f);
		glVertex3f(0.315f + x_pos, -0.645f + y_pos, 0.0f);
		glColor3f(0.8f, 0.8f, 0.8f);
		glVertex3f(0.315f + x_pos, -0.675f + y_pos, 0.0f);
		glVertex3f(0.185f + x_pos, -0.675f + y_pos, 0.0f);
	}
	glEnd();

	// Large Window
	glBegin(GL_QUADS);
	{
		glColor3f(0.6f, 0.6f, 0.6f);
		glVertex3f(0.525f + x_pos, -0.54f + y_pos, 0.0f);
		glVertex3f(0.625f + x_pos, -0.54f + y_pos, 0.0f);
		glColor3f(0.6f, 0.6f, 0.6f);
		glVertex3f(0.625f + x_pos, -0.66f + y_pos, 0.0f);
		glVertex3f(0.525f + x_pos, -0.66f + y_pos, 0.0f);
	}
	glEnd();
	
	glBegin(GL_QUADS);
	{
		glColor3f(0.0f, 0.99f, 0.99f);
		glVertex3f(0.530f + x_pos, -0.55f + y_pos, 0.0f);
		glVertex3f(0.62f + x_pos, -0.55f + y_pos, 0.0f);
		glColor3f(0.0f, 0.75f, 0.99f);
		glVertex3f(0.62f + x_pos, -0.65f + y_pos, 0.0f);
		glVertex3f(0.530f + x_pos, -0.65f + y_pos, 0.0f);
	}
	glEnd();

	glBegin(GL_LINES);
	{
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.56f + x_pos, -0.55f + y_pos, 0.0f);
		glVertex3f(0.56f + x_pos, -0.65f + y_pos, 0.0f);
	}
	glEnd();

	glBegin(GL_LINES);
	{
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.59f + x_pos, -0.55f + y_pos, 0.0f);
		glVertex3f(0.59f + x_pos, -0.65f + y_pos, 0.0f);
	}
	glEnd();

	glBegin(GL_LINES);
	{
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.53f + x_pos, -0.59f + y_pos, 0.0f);
		glVertex3f(0.62f + x_pos, -0.59f + y_pos, 0.0f);
	}
	glEnd();

	// White Platform
	glBegin(GL_QUADS);
	{
		glColor3f(0.9f, 0.9f, 0.9f);
		glVertex3f(0.52f + x_pos, -0.63f + y_pos, 0.0f);
		glVertex3f(0.63f + x_pos, -0.63f + y_pos, 0.0f);
		glColor3f(0.7f, 0.7f, 0.7f);
		glVertex3f(0.63f + x_pos, -0.66f + y_pos, 0.0f);
		glVertex3f(0.52f + x_pos, -0.66f + y_pos, 0.0f);
	}
	glEnd();

	// Door
	glBegin(GL_QUADS);
	{
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.395f + x_pos, -0.520f + y_pos, 0.0f);
		glVertex3f(0.505f + x_pos, -0.520f + y_pos, 0.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.505f + x_pos, -0.70f + y_pos, 0.0f);
		glVertex3f(0.395f + x_pos, -0.70f + y_pos, 0.0f);
	}
	glEnd();
	
	// Internal Wall
	glBegin(GL_QUADS);
	{
		glColor3f(1.0f, 1.0f, 0.5f);
		glVertex3f(0.40f + x_pos, -0.525f + y_pos, 0.0f);
		glVertex3f(0.50f + x_pos, -0.525f + y_pos, 0.0f);
		glVertex3f(0.50f + x_pos, -0.70f + y_pos, 0.0f); 
		glVertex3f(0.40f + x_pos, -0.70f + y_pos, 0.0f);
	}
	glEnd();

	glBegin(GL_QUADS);
	{
		glColor3f(0.4f, 0.0f, 0.0f);
		glVertex3f(0.425f + x_pos, -0.54f + y_pos, 0.0f);
		glVertex3f(0.50f + x_pos, -0.525f + y_pos, 0.0f);

		glColor3f(0.8f, 0.0f, 0.0f);
		glVertex3f(0.50f + x_pos, -0.61f + y_pos, 0.0f);
		glVertex3f(0.425f + x_pos, -0.61f + y_pos, 0.0f);
	}
	glEnd();

	glBegin(GL_QUADS);
	{
		glColor3f(0.8f, 0.0f, 0.0f);
		glVertex3f(0.425f + x_pos, -0.61f + y_pos, 0.0f);
		glVertex3f(0.50f + x_pos, -0.61f + y_pos, 0.0f);

		glColor3f(0.4f, 0.0f, 0.0f);
		glVertex3f(0.50f + x_pos, -0.70f + y_pos, 0.0f);
		glVertex3f(0.425f + x_pos, -0.685f + y_pos, 0.0f);
	}
	glEnd();

	// Door Knob
	glBegin(GL_LINES);
	{
		glColor3f(0.0f, 0.0f, 0.0f);

		for (float Ang = 0.0f; Ang <= 2 * 3.14; Ang += 0.01f)
		{
			float x = radius * cos(Ang) + centerX;
			float y = radius * sin(Ang) + centerY;

			glVertex3f(0.44f + x_pos, -0.61f + y_pos, 0.0f);
			glVertex2f(x + x_pos, y + y_pos);
		}
	}
	glEnd();

	// steps
	glBegin(GL_QUADS);
	{
		glColor3f(0.5f, 0.5f, 0.5f);
		glVertex3f(0.40f + x_pos, -0.70f + y_pos, 0.0f);
		glVertex3f(0.50f + x_pos, -0.70f + y_pos, 0.0f);
		glColor3f(0.75f, 0.75f, 0.75f);
		glVertex3f(0.50f + x_pos, -0.725f + y_pos, 0.0f);
		glVertex3f(0.40f + x_pos, -0.725f + y_pos, 0.0f);
	}
	glEnd();

	glBegin(GL_QUADS);
	{
		glColor3f(0.5f, 0.5f, 0.5f);
		glVertex3f(0.38f + x_pos, -0.725f + y_pos, 0.0f);
		glVertex3f(0.52f + x_pos, -0.725f + y_pos, 0.0f);
		glColor3f(0.75f, 0.75f, 0.75f);
		glVertex3f(0.52f + x_pos, -0.755f + y_pos, 0.0f);
		glVertex3f(0.38f + x_pos, -0.755f + y_pos, 0.0f);
	}
	glEnd();

	// Chimney
	glBegin(GL_QUADS);
	{
		glColor3f(0.250f, 0.250f, 0.250f);
		glVertex3f(0.395f + x_pos, -0.25f + y_pos, 0.0f);
		glVertex3f(0.455f + x_pos, -0.25f + y_pos, 0.0f);

		glColor3f(0.5f, 0.5f, 0.5f);
		glVertex3f(0.455f + x_pos, -0.275f + y_pos, 0.0f);
		glVertex3f(0.395f + x_pos, -0.275f + y_pos, 0.0f);
	}
	glEnd();

	glBegin(GL_QUADS);
	{
		glColor3f(0.50f, 0.50f, 0.50f);
		glVertex3f(0.405f + x_pos, -0.275f + y_pos, 0.0f);
		glVertex3f(0.445f + x_pos, -0.275f + y_pos, 0.0f);

		glColor3f(0.75f, 0.75f, 0.75f);
		glVertex3f(0.445f + x_pos, -0.30f + y_pos, 0.0f);
		glVertex3f(0.405f + x_pos, -0.30f + y_pos, 0.0f);
	}
	glEnd();
}

void keyboard(unsigned char key, int x, int y)
{
	// Code
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
	// Code
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
	// Code
}
