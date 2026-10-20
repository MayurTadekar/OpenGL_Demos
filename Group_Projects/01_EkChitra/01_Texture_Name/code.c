/**************************************************
 * S.G.M.P
 * @file: code.c
 * @brief: TEXTURE name using only Triangles
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @Copyright ©2020-2023 MarshallingVoid
 * @date: 13 January 2025 (Monday) 07:54:20 PM
 **************************************************/

// Header Files
#define	_USE_MATH_DEFINES
#include <math.h>
#include <GL/freeglut.h>

//	Value From Percent
#define	VALUE_FROM_PERCENT(complete, percent)	(complete * percent / 100.0f)

#define	GOLDEN_RATIO 1.618033988

// Global Variable Declarations
BOOL bFullscreen = FALSE;

// Entry-point Function
int main(int argc, char *argv[])
{
	// Local Function Declaration
	int initialize(void);
	void resize(int, int);
	void display(void);
	void keyboard(unsigned char, int, int);
	void mouse(int, int, int, int);
	void uninitialize(void);

	// Code
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Mayur Tadekar");

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
	// Code
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	return(0);
}

void resize(int width, int height)
{
	// Code
	glViewport(0, 0, width, height);
}

void alphabet_T(float x_pos, float y_pos, float r, float g, float b, float percent)
{
	// Code
	const float width = 1.0f;
	const float height = GOLDEN_RATIO / width ;

	glBegin(GL_TRIANGLES);
	{
		glColor3f(r, g, b);
		glVertex3f(VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 25), percent) + x_pos, VALUE_FROM_PERCENT((height / 2.0f), percent) - VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(height, 10), percent) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 25), percent) + x_pos, VALUE_FROM_PERCENT((height/2.0f), percent) + y_pos, 0.0f);
		glVertex3f(-VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 25), percent) + x_pos, VALUE_FROM_PERCENT((height / 2.0f), percent) - VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(height, 10), percent) + y_pos, 0.0f);
		
		glVertex3f(VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 25), percent) + x_pos, VALUE_FROM_PERCENT((height/2.0f), percent) + y_pos, 0.0f);
		glVertex3f(-VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 25), percent) + x_pos, VALUE_FROM_PERCENT((height/2.0f), percent) + y_pos, 0.0f);
		glVertex3f(-VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 25), percent) + x_pos, VALUE_FROM_PERCENT((height / 2.0f), percent) - VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(height, 10), percent) + y_pos, 0.0f);

		glVertex3f(VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 3), percent) + x_pos, VALUE_FROM_PERCENT((height/2.0f), percent) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 3), percent) + x_pos, -VALUE_FROM_PERCENT((height/2.0f), percent) + y_pos, 0.0f);
		glVertex3f(-VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 3), percent) + x_pos, -VALUE_FROM_PERCENT((height/2.0f), percent) + y_pos, 0.0f);

		glVertex3f(-VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 3), percent) + x_pos, -VALUE_FROM_PERCENT((height/2.0f), percent) + y_pos, 0.0f);
		glVertex3f(-VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 3), percent) + x_pos, VALUE_FROM_PERCENT((height/2.0f), percent) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 3), percent) + x_pos, VALUE_FROM_PERCENT((height/2.0f), percent) + y_pos, 0.0f);

	}
	glEnd();
}

void alphabet_E(float x_pos, float y_pos, float r, float g, float b, float percent)
{
	// Code
	const int width = 1.0f;
	const int height = GOLDEN_RATIO / width ;

	glBegin(GL_TRIANGLES);
	{
		glColor3f(r, g, b);

		// - Upper
		glVertex3f(VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 25), percent) + x_pos, VALUE_FROM_PERCENT((height / 2.0f), percent) - VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(height, 10), percent) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 25), percent) + x_pos, VALUE_FROM_PERCENT((height/2.0f), percent) + y_pos, 0.0f);
		glVertex3f(-VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 3), percent) + x_pos, VALUE_FROM_PERCENT((height / 2.0f), percent) - VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(height, 10), percent) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 25), percent) + x_pos, VALUE_FROM_PERCENT((height/2.0f), percent) + y_pos, 0.0f);
		glVertex3f(-VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 3), percent) + x_pos, VALUE_FROM_PERCENT((height/2.0f), percent) + y_pos, 0.0f);
		glVertex3f(-VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 3), percent) + x_pos, VALUE_FROM_PERCENT((height / 2.0f), percent) - VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(height, 10), percent) + y_pos, 0.0f);

		// - Middle
		glVertex3f(VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 15), percent) + x_pos, -VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(height, 4), percent) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 15), percent) + x_pos, VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(height, 4), percent) + y_pos, 0.0f);
		glVertex3f(-VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 3), percent) + x_pos, -VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(height, 4), percent) + y_pos, 0.0f);
		glVertex3f(-VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 3), percent) + x_pos, -VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(height, 4), percent) + y_pos, 0.0f);
		glVertex3f(-VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 3), percent) + x_pos, VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(height, 4), percent) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 15), percent) + x_pos, VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(height, 4), percent) + y_pos, 0.0f);

		// - Lower
		glVertex3f(VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 25), percent) + x_pos, -VALUE_FROM_PERCENT((height / 2.0f), percent) - VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(height, 10), percent) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 25), percent) + x_pos, -VALUE_FROM_PERCENT((height/2.0f), percent) + y_pos, 0.0f);
		glVertex3f(-VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 3), percent) + x_pos, -VALUE_FROM_PERCENT((height / 2.0f), percent) - VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(height, 10), percent) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 25), percent) + x_pos, -VALUE_FROM_PERCENT((height/2.0f), percent) + y_pos, 0.0f);
		glVertex3f(-VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 3), percent) + x_pos, -VALUE_FROM_PERCENT((height/2.0f), percent) + y_pos, 0.0f);
		glVertex3f(-VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 3), percent) + x_pos, -VALUE_FROM_PERCENT((height / 2.0f), percent) - VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(height, 10), percent) + y_pos, 0.0f);

		//	|
		glVertex3f(VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 3), percent) + x_pos, VALUE_FROM_PERCENT((height/2.0f), percent) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 3), percent) + x_pos, -VALUE_FROM_PERCENT((height/2.0f), percent) + y_pos, 0.0f);
		glVertex3f(-VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 3), percent) + x_pos, -VALUE_FROM_PERCENT((height/2.0f), percent) + y_pos, 0.0f);
		glVertex3f(-VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 3), percent) + x_pos, -VALUE_FROM_PERCENT((height/2.0f), percent) + y_pos, 0.0f);
		glVertex3f(-VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 3), percent) + x_pos, VALUE_FROM_PERCENT((height/2.0f), percent) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 3), percent) + x_pos, VALUE_FROM_PERCENT((height/2.0f), percent) + y_pos, 0.0f);
	}
	glEnd();
}

void alphabet_X(float x_pos, float y_pos, float r, float g, float b, float percent)
{
	// Code
	const int width = 1.0f;
	const int height = GOLDEN_RATIO / width ;

	glBegin(GL_TRIANGLES);
	{
		glColor3f(r, g, b);
		glVertex3f(VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 18), percent) + x_pos, VALUE_FROM_PERCENT((height / 2.0f), percent) - VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(height, 10), percent) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 13), percent) + x_pos, VALUE_FROM_PERCENT((height / 2.0f), percent) - VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(height, 10), percent) + y_pos, 0.0f);
		glVertex3f(-VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 18), percent) + x_pos, -VALUE_FROM_PERCENT((height / 2.0f), percent) - VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(height, 10), percent) + y_pos, 0.0f);
		glVertex3f(-VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 18), percent) + x_pos, -VALUE_FROM_PERCENT((height / 2.0f), percent) - VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(height, 10), percent) + y_pos, 0.0f);
		glVertex3f(-VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 13), percent) + x_pos, -VALUE_FROM_PERCENT((height / 2.0f), percent) - VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(height, 10), percent) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 18), percent) + x_pos, VALUE_FROM_PERCENT((height / 2.0f), percent) - VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(height, 10), percent) + y_pos, 0.0f);

		glVertex3f(-VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 18), percent) + x_pos, VALUE_FROM_PERCENT((height / 2.0f), percent) - VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(height, 10), percent) + y_pos, 0.0f);
		glVertex3f(-VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 13), percent) + x_pos, VALUE_FROM_PERCENT((height / 2.0f), percent) - VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(height, 10), percent) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 18), percent) + x_pos, -VALUE_FROM_PERCENT((height / 2.0f), percent) - VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(height, 10), percent) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 18), percent) + x_pos, -VALUE_FROM_PERCENT((height / 2.0f), percent) - VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(height, 10), percent) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 13), percent) + x_pos, -VALUE_FROM_PERCENT((height / 2.0f), percent) - VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(height, 10), percent) + y_pos, 0.0f);
		glVertex3f(-VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 18), percent) + x_pos, VALUE_FROM_PERCENT((height / 2.0f), percent) - VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(height, 10), percent) + y_pos, 0.0f);
		
	}
	glEnd();
}

void alphabet_U(float x_pos, float y_pos, float r, float g, float b, float percent)
{
	// Code
	const int width = 1.0f;
	const int height = GOLDEN_RATIO / width ;

	glBegin(GL_TRIANGLES);
	{
		glColor3f(r, g, b);
		
		//	| Left
		glVertex3f(-VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 12), percent) + x_pos, VALUE_FROM_PERCENT((height/2.0f), percent) + y_pos, 0.0f);
		glVertex3f(-VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 12), percent) + x_pos, -VALUE_FROM_PERCENT((height/4.0f), percent) + y_pos, 0.0f);
		glVertex3f(-VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 15), percent) + x_pos, -VALUE_FROM_PERCENT((height/4.0f), percent) + y_pos, 0.0f);
		glVertex3f(-VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 15), percent) + x_pos, -VALUE_FROM_PERCENT((height/4.0f), percent) + y_pos, 0.0f);
		glVertex3f(-VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 15), percent) + x_pos, VALUE_FROM_PERCENT((height/2.0f), percent) + y_pos, 0.0f);
		glVertex3f(-VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 12), percent) + x_pos, VALUE_FROM_PERCENT((height/2.0f), percent) + y_pos, 0.0f);
		
		//	| Right
		glVertex3f(VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 12), percent) + x_pos, VALUE_FROM_PERCENT((height/2.0f), percent) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 12), percent) + x_pos, -VALUE_FROM_PERCENT((height/4.0f), percent) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 15), percent) + x_pos, -VALUE_FROM_PERCENT((height/4.0f), percent) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 15), percent) + x_pos, -VALUE_FROM_PERCENT((height/4.0f), percent) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 15), percent) + x_pos, VALUE_FROM_PERCENT((height/2.0f), percent) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 12), percent) + x_pos, VALUE_FROM_PERCENT((height/2.0f), percent) + y_pos, 0.0f);
	}
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	{
		for(int le = 9; le <= 27; ++le)
		{
			float angle = 2.0f * M_PI * le / 36;
			glVertex3f(	VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 12), percent) * sinf(angle) + x_pos, 
						VALUE_FROM_PERCENT((height/6.0f), percent) * cosf(angle) - VALUE_FROM_PERCENT((height/4.0f), percent) + y_pos, 
						0.0f);

			glVertex3f(	VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 15), percent) * sinf(angle) + x_pos, 
						VALUE_FROM_PERCENT((height/4.0f), percent) * cosf(angle) - VALUE_FROM_PERCENT((height/4.0f), percent) + y_pos, 
						0.0f);
		}
	}
	glEnd();
}

void alphabet_R(float x_pos, float y_pos, float r, float g, float b, float percent)
{
	// Code
	const int width = 1.0f;
	const int height = GOLDEN_RATIO / width ;

	glBegin(GL_TRIANGLES);
	{
		glColor3f(r, g, b);
		
		//	| Left
		glVertex3f(-VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 12), percent) + x_pos, VALUE_FROM_PERCENT((height/2.0f), percent) + y_pos, 0.0f);
		glVertex3f(-VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 12), percent) + x_pos, -VALUE_FROM_PERCENT((height/2.0f), percent) + y_pos, 0.0f);
		glVertex3f(-VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 15), percent) + x_pos, -VALUE_FROM_PERCENT((height/2.0f), percent) + y_pos, 0.0f);
		glVertex3f(-VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 15), percent) + x_pos, -VALUE_FROM_PERCENT((height/2.0f), percent) + y_pos, 0.0f);
		glVertex3f(-VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 15), percent) + x_pos, VALUE_FROM_PERCENT((height/2.0f), percent) + y_pos, 0.0f);
		glVertex3f(-VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 12), percent) + x_pos, VALUE_FROM_PERCENT((height/2.0f), percent) + y_pos, 0.0f);

	}
	glEnd();


	glBegin(GL_TRIANGLE_STRIP);
	{
		float angle = 0.0f;


		glVertex3f(	-VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 15), percent) + x_pos, 
					VALUE_FROM_PERCENT((height/6.0f), percent) * cosf(angle) + VALUE_FROM_PERCENT((height/4.0f), percent) + y_pos, 
					0.0f);

		glVertex3f(	-VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 15), percent) + x_pos, 
					VALUE_FROM_PERCENT((height/4.0f), percent) * cosf(angle) + VALUE_FROM_PERCENT((height/4.0f), percent) + y_pos, 
					0.0f);

		for(int le = 0; le <= 18; ++le)
		{
			angle = 2.0f * M_PI * le / 36;
			glVertex3f(	VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 12), percent) * sinf(angle) + x_pos, 
						VALUE_FROM_PERCENT((height/6.0f), percent) * cosf(angle) + VALUE_FROM_PERCENT((height/4.0f), percent) + y_pos, 
						0.0f);

			glVertex3f(	VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 15), percent) * sinf(angle) + x_pos, 
						VALUE_FROM_PERCENT((height/4.0f), percent) * cosf(angle) + VALUE_FROM_PERCENT((height/4.0f), percent) + y_pos, 
						0.0f);
		}

		glVertex3f(	-VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 15), percent) + x_pos, 
					VALUE_FROM_PERCENT((height/6.0f), percent) * cosf(angle) + VALUE_FROM_PERCENT((height/4.0f), percent) + y_pos, 
					0.0f);

		glVertex3f(	-VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 15), percent) + x_pos, 
					VALUE_FROM_PERCENT((height/4.0f), percent) * cosf(angle) + VALUE_FROM_PERCENT((height/4.0f), percent) + y_pos, 
					0.0f);


		glVertex3f(	VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 15), percent) + x_pos, 
					VALUE_FROM_PERCENT((height/6.0f), percent) * cosf(angle) - VALUE_FROM_PERCENT((height/4.0f), percent) + y_pos, 
					0.0f);

		glVertex3f(	VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(width, 15), percent) + x_pos, 
					VALUE_FROM_PERCENT((height/4.0f), percent) * cosf(angle) - VALUE_FROM_PERCENT((height/4.0f), percent) + y_pos, 
					0.0f);
	}
	glEnd();
}

void Texture(float x_pos, float y_pos, float r, float g, float b, float percent)
{
	// Code	

	x_pos -= VALUE_FROM_PERCENT(VALUE_FROM_PERCENT(1.32f, 50.0f), percent);

	alphabet_T(	0.0f + x_pos, 
				0.0f + y_pos, 
				r, g, b, VALUE_FROM_PERCENT(42.0f, percent));
	
	alphabet_E(	VALUE_FROM_PERCENT(0.15f, percent) + x_pos, 
				VALUE_FROM_PERCENT(0.03f, percent) + y_pos, 
				r, g, b, VALUE_FROM_PERCENT(62.0f, percent));
	
	alphabet_X(	VALUE_FROM_PERCENT(0.45f, percent) + x_pos, 
				VALUE_FROM_PERCENT(0.07f, percent) + y_pos, 
				r, g, b, VALUE_FROM_PERCENT(67.0f, percent));
	
	alphabet_T(	VALUE_FROM_PERCENT(0.7f, percent) + x_pos, 
				0.0f + y_pos, 
				r, g, b, VALUE_FROM_PERCENT(42.0f, percent));
	
	alphabet_U(	VALUE_FROM_PERCENT(0.93f, percent) + x_pos,
				0.0f + y_pos, 
				r, g, b, VALUE_FROM_PERCENT(68.0f, percent));
	
	alphabet_R(	VALUE_FROM_PERCENT(1.17f, percent) + x_pos, 
				0.0f + y_pos, 
				r, g, b, VALUE_FROM_PERCENT(68.0f, percent));
	
	alphabet_E(	VALUE_FROM_PERCENT(1.32f, percent) + x_pos, 
				VALUE_FROM_PERCENT(0.03f, percent) + y_pos, 
				r, g, b, VALUE_FROM_PERCENT(62.0f, percent));

}

float scale_factor = 0.0f;

void display(void)
{
	// Code
	glClear(GL_COLOR_BUFFER_BIT);
	
	Texture(0.0f, 0.0f, 249.0f / 255.0f, 98.0f / 255.0f, 41.0f / 255.0f, scale_factor);

	glutSwapBuffers();
}

void factorFunc(int value)
{
	// Code
	scale_factor += 0.5f;

	glutPostRedisplay();

	if(scale_factor < 100.0f)
		glutTimerFunc(100, factorFunc, 0);
}

void keyboard(unsigned char key, int x, int y)
{
	// Code
	switch(key)
	{
	case 27:
		glutLeaveMainLoop();
		break;

	case 'f':
	case 'F':
		if(bFullscreen == FALSE)
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

	case 'p':
	case 'P':
		glutTimerFunc(0, factorFunc, 0);
		break;

	default:
		break;
	}
}

void mouse(int button, int state, int x, int y)
{
	// Code
	switch(button)
	{
	default:
		break;
	}
}

void uninitialize(void)
{
	// Code
}
