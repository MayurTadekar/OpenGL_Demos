// header files
#include<GL/freeglut.h>
#include <math.h>


// Global variable declerations
BOOL bFullScreen = FALSE;


// Entry-point function
int main(int argc, char* argv[])
{
	// local function declerations
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
	glutCreateWindow("Gauri Nidan :Ek Chitra");

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

void display()
{
	void tactor(float,float);
	
	
	// code
	glClear(GL_COLOR_BUFFER_BIT);

	tactor(0.0f,0.0f);
	
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


void tactor(float x_pos,float y_pos)
{
	float x, y, radius, theta;
	///grass
	glBegin(GL_POLYGON);  
	

	glColor3f(0.741176, 0.121569, 0.180392);
	glVertex3f(0.41f+ x_pos, -0.85f+ y_pos, 0.0f);

	glColor3f(0.741176, 0.121569, 0.180392);
	glVertex3f(0.41f + x_pos, -0.73f + y_pos, 0.0f);

	glColor3f(0.741176, 0.121569, 0.180392);
	glVertex3f(0.45f + x_pos, -0.65f + y_pos, 0.0f);

	glColor3f(0.741176, 0.121569, 0.180392);
	glVertex3f(0.58f + x_pos, -0.65f + y_pos, 0.0f);


	glColor3f(0.741176, 0.121569, 0.180392);
	glVertex3f(0.58f + x_pos, -0.58f + y_pos, 0.0f);

	

	glColor3f(0.741176, 0.121569, 0.180392);
	glVertex3f(0.61f + x_pos, -0.58f + y_pos, 0.0f);

	glColor3f(0.741176, 0.121569, 0.180392);
	glVertex3f(0.61f + x_pos, -0.68f + y_pos, 0.0f);

	glColor3f(0.741176, 0.121569, 0.180392);
	glVertex3f(0.62f + x_pos, -0.71f + y_pos, 0.0f);

	glColor3f(0.741176, 0.121569, 0.180392);
	glVertex3f(0.68f + x_pos, -0.71f + y_pos, 0.0f);

	glColor3f(0.741176, 0.121569, 0.180392);
	glVertex3f(0.68f + x_pos, -0.75f + y_pos, 0.0f);

	glColor3f(0.741176, 0.121569, 0.180392);
	glVertex3f(0.71f + x_pos, -0.75f + y_pos, 0.0f);

	glColor3f(0.741176, 0.121569, 0.180392);
	glVertex3f(0.71f + x_pos, -0.68f + y_pos, 0.0f);

	glColor3f(0.741176, 0.121569, 0.180392);
	glVertex3f(0.88f + x_pos, -0.68f + y_pos, 0.0f);

	glColor3f(0.741176, 0.121569, 0.180392);
	glVertex3f(0.91f + x_pos, -0.71f + y_pos, 0.0f);

	glColor3f(0.741176, 0.121569, 0.180392);
	glVertex3f(0.91f + x_pos, -0.82f + y_pos, 0.0f);

	glColor3f(0.741176, 0.121569, 0.180392);
	glVertex3f(0.90f + x_pos, -0.83f + y_pos, 0.0f);


	glColor3f(0.741176, 0.121569, 0.180392);
	glVertex3f(0.41f + x_pos, -0.82f + y_pos, 0.0f);
	glEnd();

	/////////////////////////////// 1st big tire

	glBegin(GL_POLYGON);

	radius = 0.119f;
	glColor3f(0.0, 0.0, 0.0);
	for (int i = 0; i < 360; i++)
	{
		theta = i * 3.142 / 180;//convert into degree
		glVertex2f((0.54f + x_pos) + radius * cos(theta), (-0.8f + y_pos) + radius * sin(theta));
	}

	glEnd();


	/////////////////
	glBegin(GL_POLYGON);
	
	radius = 0.1f;
	glColor3f(0.243137, 0.235294, 0.247059);
	for (int i = 0; i < 360; i++)
	{
		theta = i * 3.142 / 180;//convert into degree
		glVertex2f((0.54f + x_pos) + radius * cos(theta), (-0.8f + y_pos) + radius * sin(theta));
	}

	glEnd();

	glBegin(GL_POLYGON);

	radius = 0.05f;
	glColor3f(0.788235, 0.792157, 0.800000);
	for (int i = 0; i < 360; i++)
	{
		theta = i * 3.142 / 180;//convert into degree
		glVertex2f((0.54f + x_pos) + radius * cos(theta), (-0.8f + y_pos) + radius * sin(theta));
	}

	glEnd();


	/////////////////////////////// 2end small tire

	glBegin(GL_POLYGON);

	radius = 0.08f;
	glColor3f(0.0, 0.0, 0.0);
	for (int i = 0; i < 360; i++)
	{
		theta = i * 3.142 / 180;//convert into degree
		glVertex2f((0.81f + x_pos) + radius * cos(theta), (-0.8f + y_pos) + radius * sin(theta));
	}

	glEnd();


	/////////////////
	glBegin(GL_POLYGON);

	radius = 0.07f;
	glColor3f(0.243137, 0.235294, 0.247059);
	for (int i = 0; i < 360; i++)
	{
		theta = i * 3.142 / 180;//convert into degree
		glVertex2f((0.81f + x_pos) + radius * cos(theta), (-0.8f + y_pos) + radius * sin(theta));
	}

	glEnd();

	glBegin(GL_POLYGON);

	radius = 0.03f;
	glColor3f(0.788235, 0.792157, 0.800000);
	for (int i = 0; i < 360; i++)
	{
		theta = i * 3.142 / 180;//convert into degree
		glVertex2f((0.81f + x_pos) + radius * cos(theta), (-0.8f + y_pos) + radius * sin(theta));
	}

	glEnd();

	

	//////////////footware gap
	glBegin(GL_QUADS);

	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(0.68f + x_pos, -0.68f + y_pos, 0.0f);

	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(0.68f + x_pos, -0.76f + y_pos, 0.0f);

	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(0.71f + x_pos, -0.76f + y_pos, 0.0f);

	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(0.71f + x_pos, -0.68f + y_pos, 0.0f);

	glEnd();

	/////////////////////sit gap

	glBegin(GL_QUADS);

	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(0.58f + x_pos, -0.57f + y_pos, 0.0f);

	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(0.58f + x_pos, -0.65f + y_pos, 0.0f);

	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(0.52f + x_pos, -0.65f + y_pos, 0.0f);

	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(0.52 + x_posf, -0.57f + y_pos, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.84f + x_pos, -0.68f + y_pos, 0.0f);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.84f + x_pos, -0.66f + y_pos, 0.0f);

	
	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.86f + x_pos, -0.66f + y_pos, 0.0f);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.86f + x_pos, -0.68f + y_pos, 0.0f);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.84f + x_pos, -0.68f + y_pos, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.83f + x_pos, -0.66f + y_pos, 0.0f);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.83f + x_pos, -0.56f + y_pos, 0.0f);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.87f + x_pos, -0.56f + y_pos, 0.0f);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.87f + x_pos, -0.66f + y_pos, 0.0f);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.83f + x_pos, -0.66f + y_pos, 0.0f);

	glEnd();

	
	glBegin(GL_POLYGON);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.84f + x_pos, -0.56f + y_pos, 0.0f);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.84f + x_pos, -0.52f + y_pos, 0.0f);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.86f + x_pos, -0.53f + y_pos, 0.0f);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.86f + x_pos, -0.56f + y_pos, 0.0f);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.84f + x_pos, -0.56f + y_pos, 0.0f);

	glEnd();

	
	///////////roof
	glBegin(GL_POLYGON);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.44f + x_pos, -0.54f + y_pos, 0.0f);

	glColor3f(0.788235, 0.792157, 0.800000);
	glVertex3f(0.44f + x_pos, -0.45f + y_pos, 0.0f);

	glColor3f(0.788235, 0.792157, 0.800000);
	glVertex3f(0.56f + x_pos, -0.45f + y_pos, 0.0f);

	glColor3f(0.788235, 0.792157, 0.800000);
	glVertex3f(0.56f + x_pos, -0.54f + y_pos, 0.0f);

	glColor3f(0.788235, 0.792157, 0.800000);
	glVertex3f(0.44f + x_pos, -0.54f + y_pos, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(0.788235, 0.792157, 0.800000);
	glVertex3f(0.56f + x_pos, -0.54f + y_pos, 0.0f);

	glColor3f(0.788235, 0.792157, 0.800000);
	glVertex3f(0.56f + x_pos, -0.45f + y_pos, 0.0f);

	glColor3f(0.788235, 0.792157, 0.800000);
	glVertex3f(0.72f + x_pos, -0.45f + y_pos, 0.0f);

	glColor3f(0.788235, 0.792157, 0.800000);
	glVertex3f(0.60f + x_pos, -0.54f + y_pos, 0.0f);

	glColor3f(0.788235, 0.792157, 0.800000);
	glVertex3f(0.56f + x_pos, -0.54f + y_pos, 0.0f);

	glEnd();


	glBegin(GL_POLYGON);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.72f + x_pos, -0.45f + y_pos, 0.0f);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.75f + x_pos, -0.48f + y_pos, 0.0f);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.68f + x_pos, -0.59f + y_pos, 0.0f);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.60f + x_pos, -0.54f + y_pos, 0.0f);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.72f + x_pos, -0.45f + y_pos, 0.0f);

	glEnd();
	////////roof bar 1
	glBegin(GL_QUADS);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.46f + x_pos, -0.65f + y_pos, 0.0f);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.46f + x_pos, -0.54f + y_pos, 0.0f);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.47f + x_pos, -0.54f + y_pos, 0.0f);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.47f + x_pos, -0.65f + y_pos, 0.0f);

	glEnd();

	//////roof bar 2
	glBegin(GL_QUADS);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.49f + x_pos, -0.65f + y_pos, 0.0f);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.49f + x_pos, -0.54f + y_pos, 0.0f);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.5f + x_pos, -0.54f + y_pos, 0.0f);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.5f + x_pos, -0.65f + y_pos, 0.0f);

	glEnd();



	//////roof bar 3
	glBegin(GL_QUADS);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.56f + x_pos, -0.65f + y_pos, 0.0f);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.56f + x_pos, -0.54f + y_pos, 0.0f);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.57f + x_pos, -0.54f + y_pos, 0.0f);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.57f + x_pos, -0.65f + y_pos, 0.0f);

	glEnd();

	//////roof bar 4
	glBegin(GL_QUADS);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.59f + x_pos, -0.58f + y_pos, 0.0f);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.59f + x_pos, -0.54f + y_pos, 0.0f);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.60f + x_pos, -0.54f + y_pos, 0.0f);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.60f + x_pos, -0.58f + y_pos, 0.0f);

	glEnd();


	//////roof bar 5
	glBegin(GL_QUADS);

	glColor3f(0.788235, 0.792157, 0.800000);
	glVertex3f(0.68f + x_pos, -0.58f + y_pos, 0.0f);

	glColor3f(0.788235, 0.792157, 0.800000);
	glVertex3f(0.67f + x_pos, -0.58f + y_pos, 0.0f);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.61f + x_pos, -0.66f + y_pos, 0.0f);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.61f + x_pos, -0.68f + y_pos, 0.0f);

	glEnd();


	//////stering
	glBegin(GL_QUADS);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.71f + x_pos, -0.68f + y_pos, 0.0f);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.69f + x_pos, -0.66f + y_pos, 0.0f);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.68f + x_pos, -0.67f + y_pos, 0.0f);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.71f + x_pos, -0.70f + y_pos, 0.0f);

	glEnd();

	//////stering
	glBegin(GL_QUADS);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.70f + x_pos, -0.65f + y_pos, 0.0f);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.69f + x_pos, -0.64f + y_pos, 0.0f);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.66f + x_pos, -0.67f + y_pos, 0.0f);

	glColor3f(0.243137, 0.235294, 0.247059);
	glVertex3f(0.67f + x_pos, -0.68f + y_pos, 0.0f);

	glEnd();

}


void uninitialize()
{
	// code

}

