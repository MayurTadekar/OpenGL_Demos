// header files
#include<GL/freeglut.h>

// global variable declarations
BOOL bFullScreen = FALSE;

// Entry-point function
int main(int argc, char* argv[])
{
	// local function declararions
	int initialize(void);
	void resize(int, int);
	void display(void);
	void keyboard(unsigned char, int, int);
	void mouse(int, int, int, int);
	void uninitialize(void);
    void Birds_Amol(float, float );

	// code
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Amol Suresh Nandkar");

	initialize();

	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutCloseFunc(uninitialize);

	glutMainLoop();

	return(0);
}


void Birds_Amol(float x_pos, float y_pos)
{
    //******************** Draw Bird *****************************************************

    //Bird Shape 1/2 feather
    glBegin(GL_QUADS);
    glColor3f(0.6f, 0.4f, 0.6f);  //
    glVertex2f(0.6f + x_pos, 0.65f+ y_pos);  // 
    glVertex2f(0.57f + x_pos, 0.63f+ y_pos);
    //glColor3f(-0.36f, 0.58f, 0.0f);
    glVertex2f(0.57f + x_pos, 0.58f + y_pos);
    glVertex2f(0.58f + x_pos, 0.58f + y_pos);

    glEnd();



    //Bird Shape 2 feather shape line
    glBegin(GL_LINES);
    glColor3f(0.1f, 0.1f, 0.1f);  //
    glVertex2f(0.58f + x_pos, 0.62f + y_pos);  // 
    glVertex2f(0.6f + x_pos, 0.64f + y_pos);
    glEnd();


    //Bird Shape 2 feather shape line
    glBegin(GL_LINES);
    glColor3f(0.1f, 0.1f, 0.1f);  //
    glVertex2f(0.58f + x_pos, 0.60f + y_pos);  // 
    glVertex2f(0.6f + x_pos, 0.62f + y_pos);
    glEnd();

    //Bird Shape 2 body
    glBegin(GL_QUADS);
    glColor3f(0.6f, 0.4f, 0.6f);  // 
    glVertex2f(0.55f + x_pos, 0.57f + y_pos);  // 
    glVertex2f(0.55f + x_pos, 0.59f + y_pos);
    //glColor3f(-0.36f, 0.58f, 0.0f);
    glVertex2f(0.60f + x_pos, 0.56f + y_pos);
    glVertex2f(0.61f + x_pos, 0.57f + y_pos);

    glEnd();

    //Bird Shape 2 beak
    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.4f, 0.6f);  // 
    glVertex2f(0.55f + x_pos, 0.59f + y_pos);  // 
    glVertex2f(0.53f + x_pos, 0.58f + y_pos);
    //glColor3f(-0.36f, 0.58f, 0.0f);
    glVertex2f(0.55f + x_pos, 0.57f + y_pos);

    glEnd();

    //Bird Shape 2 eye shape 
    glBegin(GL_LINES);
    glColor3f(0.1f, 0.1f, 0.1f);  //
    glVertex2f(0.545f + x_pos, 0.58f + y_pos);  // 
    glVertex2f(0.548f + x_pos, 0.581f + y_pos);
    glEnd();

    /////////////////////////////*********************

    //Bird Shape 2/2 feather
    glBegin(GL_QUADS);
    glColor3f(0.6f, 0.4f, 0.6f);  // 
    glVertex2f(0.7f + x_pos, 0.65f + y_pos);  // 
    glVertex2f(0.67f + x_pos, 0.63f + y_pos);
    //glColor3f(-0.36f, 0.58f, 0.0f);
    glVertex2f(0.67f + x_pos, 0.58f + y_pos);
    glVertex2f(0.68f + x_pos, 0.58f + y_pos);
    glEnd();



    //Bird Shape feather shape
    glBegin(GL_LINES);
    glColor3f(0.1f, 0.1f, 0.1f);  // 
    glVertex2f(0.68f + x_pos, 0.62f + y_pos);  // 
    glVertex2f(0.7f + x_pos, 0.64f + y_pos);
    glEnd();


    //Bird Shape feather shape
    glBegin(GL_LINES);
    glColor3f(0.1f, 0.1f, 0.1f);  // 
    glVertex2f(0.68f + x_pos, 0.60f + y_pos);  // 
    glVertex2f(0.7f + x_pos, 0.62f + y_pos);
    glEnd();

    //Bird Shape 2 body
    glBegin(GL_QUADS);
    glColor3f(0.6f, 0.4f, 0.6f);  // 
    glVertex2f(0.65f + x_pos, 0.57f + y_pos);  // 
    glVertex2f(0.65f + x_pos, 0.59f + y_pos);
    //glColor3f(-0.36f, 0.58f, 0.0f);
    glVertex2f(0.70f + x_pos, 0.56f + y_pos);
    glVertex2f(0.71f + x_pos, 0.57f + y_pos);

    glEnd();

    //Bird Shape 2 beak
    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.4f, 0.6f);  // 
    glVertex2f(0.65f + x_pos, 0.59f + y_pos);  // 
    glVertex2f(0.63f + x_pos, 0.58f + y_pos);
    //glColor3f(-0.36f, 0.58f, 0.0f);
    glVertex2f(0.65f + x_pos, 0.57f + y_pos);

    glEnd();

    //Bird Shape 2 eye shape 
    glBegin(GL_LINES);
    glColor3f(0.1f, 0.1f, 0.1f);  //
    glVertex2f(0.645f + x_pos, 0.58f + y_pos);  // 
    glVertex2f(0.648f + x_pos, 0.581f + y_pos);
    glEnd();


    ///*********** Simple Birds flying in groups ***********************************************


  //Bird Shape 1
    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.4f, 0.6f);  // 
    glVertex2f(-0.4f + x_pos, 0.6f + y_pos);  // 
    glVertex2f(-0.37f + x_pos, 0.57f + y_pos);
    //glColor3f(-0.36f, 0.58f, 0.0f);
    glVertex2f(-0.36f + x_pos, 0.58f + y_pos);

    glEnd();


    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.4f, 0.6f);  // 
    glVertex2f(-0.3f + x_pos, 0.6f + y_pos);  // 
    glVertex2f(-0.37f + x_pos, 0.57f + y_pos);
    //glColor3f(-0.36f, 0.58f, 0.0f);
    glVertex2f(-0.36f + x_pos, 0.58f + y_pos);

    glEnd();


    // Bird Shape 2
    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.4f, 0.6f);  // 
    glVertex2f(-0.2f + x_pos, 0.6f + y_pos);  // 
    glVertex2f(-0.17f + x_pos, 0.57f + y_pos);
    //glColor3f(-0.36f, 0.58f, 0.0f);
    glVertex2f(-0.16f + x_pos, 0.58f + y_pos);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.4f, 0.6f);  // 
    glVertex2f(-0.1f, 0.6f + y_pos);  // 
    glVertex2f(-0.17f, 0.57f + y_pos);
    //glColor3f(-0.36f, 0.58f, 0.0f);
    glVertex2f(-0.16f, 0.58f + y_pos);
    glEnd();

    ///****************************

   // Bird Shape 3
    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.4f, 0.6f);  // 
    glVertex2f(-0.2f + x_pos, 0.8f + y_pos);  // 
    glVertex2f(-0.17f + x_pos, 0.77f + y_pos);
    //glColor3f(-0.36f, 0.58f, 0.0f);
    glVertex2f(-0.16f + x_pos, 0.78f + y_pos);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.4f, 0.6f);  // 
    glVertex2f(-0.1f + x_pos, 0.8f + y_pos);  // 
    glVertex2f(-0.17f + x_pos, 0.77f + y_pos);
    //glColor3f(-0.36f, 0.58f, 0.0f);
    glVertex2f(-0.16f + x_pos, 0.78f + y_pos);
    glEnd();



    //******************** Draw Bird *****************************************************

   //Bird Shape 1
    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.4f, 0.6f);  // 
    glVertex2f(0.4f + x_pos, 0.6f + y_pos);  // 
    glVertex2f(0.37f + x_pos, 0.57f + y_pos);
    //glColor3f(-0.36f, 0.58f, 0.0f);
    glVertex2f(0.36f + x_pos, 0.58f + y_pos);

    glEnd();


    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.4f, 0.6f);  // 
    glVertex2f(0.3f + x_pos, 0.6f + y_pos);  // 
    glVertex2f(0.37f + x_pos, 0.57f + y_pos);
    //glColor3f(-0.36f, 0.58f, 0.0f);
    glVertex2f(0.36f + x_pos, 0.58f + y_pos);

    glEnd();


    // Bird Shape 2
    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.4f, 0.6f);  // 
    glVertex2f(0.2f + x_pos, 0.6f + y_pos);  //
    glVertex2f(0.17f + x_pos, 0.57f + y_pos);
    //glColor3f(-0.36f, 0.58f, 0.0f);
    glVertex2f(0.16f + x_pos, 0.58f + y_pos);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.4f, 0.6f);  // 
    glVertex2f(0.1f + x_pos, 0.6f + y_pos);  // 
    glVertex2f(0.17f + x_pos, 0.57f + y_pos);
    //glColor3f(-0.36f, 0.58f, 0.0f);
    glVertex2f(0.16f + x_pos, 0.58f + y_pos);
    glEnd();

    ///****************************

   // Bird Shape 3
    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.4f, 0.6f);  // 
    glVertex2f(0.2f + x_pos, 0.8f + y_pos);  // 
    glVertex2f(0.17f + x_pos, 0.77f + y_pos);
    //glColor3f(-0.36f, 0.58f, 0.0f);
    glVertex2f(0.16f + x_pos, 0.78f + y_pos);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.4f, 0.6f);  // 
    glVertex2f(0.1f + x_pos, 0.8f + y_pos);  // 
    glVertex2f(0.17f + x_pos, 0.77f + y_pos);
    //glColor3f(-0.36f, 0.58f, 0.0f);
    glVertex2f(0.16f + x_pos, 0.78f + y_pos);
    glEnd();
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
	// code
	glClear(GL_COLOR_BUFFER_BIT);

	/*glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glEnd();*/

    Birds_Amol(0.0f,0.0f);

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
