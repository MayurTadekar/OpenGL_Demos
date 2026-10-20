// header files
#include<GL/freeglut.h>

// global variable declarations
BOOL bFullScreen = FALSE;

// Entry-Point function
int main(int argc, char *argv[])
{
	// local function declarations
	int initialize(void);
	void resize(int, int);
	void display(void);
	void keyboard(unsigned char, int, int);
	void mouse(int, int, int, int);
	void uninitialize(void);
	void Grass(float,float);
	void Farming(float, float);

	// code
	glutInit(&argc, argv);


	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);


	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("OGL Assignment");

	initialize();

	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutCloseFunc(uninitialize);

	glutMainLoop();

	return (0);

}

int initialize(void)
{
	// code
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	return(0);

}

void resize(int width, int height)
{
	//code
	glViewport(0, 0, width, height);

}

void display(void)
{
	// code
	glClear(GL_COLOR_BUFFER_BIT);
	
	Farming();

	glutSwapBuffers();

}


void Farming_Pankaj(float x_offset, float y_offset)
{
	glLineWidth(3.0f);
	
	//Ground
	glBegin(GL_QUADS);
	{
	glColor3f(0.6f, 0.3f, 0.0f);
	glVertex3f(0.3f + x_offset, 0.0f + y_offset, 0.0f);
	glVertex3f(0.7f + x_offset, 0.0f + y_offset, 0.0f);
	glVertex3f(0.7f + x_offset, 0.6f + y_offset, 0.0f);
	glVertex3f(0.3f + x_offset, 0.6f + y_offset, 0.0f);

	}
	glEnd();
		
	
//1st Row	
Grass_Pankaj(0.0f + x_offset, 0.0f + y_offset);
Grass_Pankaj(0.10f + x_offset, 0.0f + y_offset);
Grass_Pankaj(0.20f + x_offset, 0.0f + y_offset);
Grass_Pankaj(0.30f + x_offset, 0.0f + y_offset);

//2nd Row	
Grass_Pankaj(0.0f + x_offset, -0.15f + y_offset);
Grass_Pankaj(0.10f + x_offset, -0.15f + y_offset);
Grass_Pankaj(0.20f + x_offset, -0.15f + y_offset);
Grass_Pankaj(0.30f + x_offset, -0.15f + y_offset);

//3rd Row
Grass_Pankaj(0.0f + x_offset, -0.30f + y_offset);
Grass_Pankaj(0.10f + x_offset, -0.30f + y_offset);
Grass_Pankaj(0.20f + x_offset, -0.30f + y_offset);
Grass_Pankaj(0.30f + x_offset, -0.30f + y_offset);


//4th Row
Grass_Pankaj(0.0f + x_offset, -0.45f + y_offset);
Grass_Pankaj(0.10f + x_offset, -0.45f + y_offset);
Grass_Pankaj(0.20f + x_offset, -0.45f + y_offset);
Grass_Pankaj(0.30f + x_offset, -0.45f + y_offset);



//First Line
glBegin(GL_LINES);
{
glColor3f(0.5f, 0.1f, 0.1f);
glVertex3f(0.3f + x_offset, 0.5f + y_offset, 0.0f);
glVertex3f(0.7f + x_offset, 0.5f + y_offset, 0.0f);

}
glEnd();

//Second Line
glBegin(GL_LINES);
{
glColor3f(0.5f, 0.1f, 0.1f);
glVertex3f(0.3f + x_offset, 0.35f + y_offset, 0.0f);
glVertex3f(0.7f + x_offset, 0.35f + y_offset, 0.0f);

}
glEnd();

//Third Line
glBegin(GL_LINES);
{
glColor3f(0.5f, 0.1f, 0.1f);
glVertex3f(0.3f+ x_offset, 0.2f + y_offset, 0.0f);
glVertex3f(0.7f + x_offset, 0.2f + y_offset, 0.0f);

}
glEnd();


//Forth Line
glBegin(GL_LINES);
{
glColor3f(0.5f, 0.1f, 0.1f);
glVertex3f(0.3f + x_offset,0.04f + y_offset, 0.0f);
glVertex3f(0.7f + x_offset, 0.04f + y_offset, 0.0f);

}
glEnd();

	glLineWidth(1.0f);
}


void Grass_Pankaj(float x_offset, float y_offset)
{
	//First Line
	glBegin(GL_LINES);
	{
	glColor3f(0.6f,1.0f, 0.0f);
	glVertex3f(0.35f + x_offset, 0.5f + y_offset, 0.0f);
	glVertex3f(0.32f + x_offset, 0.6f + y_offset, 0.0f);

	}
	glEnd();
	
	//Second Line
	glBegin(GL_LINES);
	{
	glColor3f(0.6f, 1.0f, 0.0f);
	glVertex3f(0.35f + x_offset, 0.5f + y_offset, 0.0f);
	glVertex3f(0.35f + x_offset, 0.6f + y_offset, 0.0f);
}
	glEnd();

	//Third Line
	glBegin(GL_LINES);
	{
	glColor3f(0.6f, 1.0f, 0.0f);
	glVertex3f(0.35f + x_offset, 0.5f + y_offset, 0.0f);
	glVertex3f(0.38f + x_offset, 0.6f + y_offset, 0.0f);

	}
	glEnd();
			
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
	//  code
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
