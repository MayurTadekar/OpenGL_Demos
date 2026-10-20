// header files
#include<GL/freeglut.h>

void Rangoli_Swati(float x_pos, float y_pos)
{
    glBegin(GL_QUADS);
    glColor3f(0.9f, 0.0f, 0.8f);
    glVertex3f(0.58f + x_pos, -0.89f + y_pos, 0.0f);  // 1 quad
    glVertex3f(0.53f + x_pos, -0.89f + y_pos, 0.0f);
    glColor3f(0.9f, 0.3f, 0.2f);
    glVertex3f(0.5f + x_pos, -0.91f + y_pos, 0.0f);
    glVertex3f(0.56f + x_pos, -0.91f+ y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.7f, 1.0f);
    glVertex3f(0.5f + x_pos, -0.91f+ y_pos, 0.0f);  // 2 quad
    glVertex3f(0.48f + x_pos, -0.93f+ y_pos, 0.0f);
    glVertex3f(0.5f+ x_pos, -0.97f+ y_pos, 0.0f);
    glVertex3f(0.53f+ x_pos, -0.93f+ y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);

    glColor3f(0.9f, 0.0f, 0.8f);
    glVertex3f(0.5f+ x_pos, -0.91f+ y_pos, 0.0f);  // 3 quad
    glVertex3f(0.48f+ x_pos, -0.89f+ y_pos, 0.0f);
    glColor3f(0.9f, 0.3f, 0.2f);
    glVertex3f(0.43f+ x_pos, -0.89f+ y_pos, 0.0f);
    glVertex3f(0.46f+ x_pos, -0.91f+ y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.8f, 0.9f, 1.0f);
    glVertex3f(0.43f+ x_pos, -0.89f+ y_pos, 0.0f);  // 4 quad
    glVertex3f(0.38f+ x_pos, -0.89f+ y_pos, 0.0f);
    glVertex3f(0.36f+ x_pos, -0.91f+ y_pos, 0.0f);
    glVertex3f(0.41f+ x_pos, -0.91f+ y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.9f, 0.0f, 0.8f);
    glVertex3f(0.43f+ x_pos, -0.89f+ y_pos, 0.0f);  // 5 quad
    glVertex3f(0.4f+ x_pos, -0.87f+ y_pos, 0.0f);
    glColor3f(0.9f, 0.3f, 0.2f);
    glVertex3f(0.42f+ x_pos, -0.85f+ y_pos, 0.0f);
    glVertex3f(0.45f+ x_pos, -0.87f+ y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.7f, 1.0f);
    glVertex3f(0.42f+ x_pos, -0.85f+ y_pos, 0.0f);  // 6 quad
    glVertex3f(0.38f+ x_pos, -0.85f+ y_pos, 0.0f);
    glVertex3f(0.35f+ x_pos, -0.83f+y_pos, 0.0f);
    glVertex3f(0.4f+ x_pos, -0.83f+ y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.9f, 0.0f, 0.8f);
    glVertex3f(0.42f+ x_pos, -0.85f+ y_pos, 0.0f);  // 7 quad
    glVertex3f(0.47f+ x_pos, -0.85f+ y_pos, 0.0f);
    glColor3f(0.9f, 0.3f, 0.2f);
    glVertex3f(0.5f+ x_pos, -0.83f+ y_pos, 0.0f);
    glVertex3f(0.45f+ x_pos, -0.83f+ y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.7f, 1.0f);
    glVertex3f(0.5f+ x_pos, -0.83f+ y_pos, 0.0f);  // 8 quad
    glVertex3f(0.47f+ x_pos, -0.81f+ y_pos, 0.0f);
    glVertex3f(0.5f+ x_pos, -0.79f+ y_pos, 0.0f);
    glVertex3f(0.52f+ x_pos, -0.81f+ y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.9f, 0.0f, 0.8f);
    glVertex3f(0.5f+ x_pos, -0.83f+ y_pos, 0.0f);  // 9 quad
    glVertex3f(0.55f+ x_pos, -0.83f+ y_pos, 0.0f);
    glColor3f(0.9f, 0.3f, 0.2f);
    glVertex3f(0.58f+ x_pos, -0.85f+ y_pos, 0.0f);
    glVertex3f(0.53f+ x_pos, -0.85f+ y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.7f, 1.0f);
    glVertex3f(0.58f+ x_pos, -0.85f+ y_pos, 0.0f);  // 10 quad
    glVertex3f(0.63f+ x_pos, -0.85f+ y_pos, 0.0f);
    glVertex3f(0.65f+ x_pos, -0.83f+ y_pos, 0.0f);
    glVertex3f(0.6f+ x_pos, -0.83f+ y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.9f, 0.0f, 0.8f);
    glVertex3f(0.58f+ x_pos, -0.85f+ y_pos, 0.0f);  // 11 quad
    glVertex3f(0.55f+ x_pos, -0.87f+ y_pos, 0.0f);
    glColor3f(0.9f, 0.3f, 0.2f);
    glVertex3f(0.58f+ x_pos, -0.89f+ y_pos, 0.0f);
    glVertex3f(0.6f+ x_pos, -0.87f+ y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.7f, 1.0f);
    glVertex3f(0.58f+ x_pos, -0.89f+ y_pos, 0.0f);  // 12 quad
    glVertex3f(0.63f+ x_pos, -0.89f+ y_pos, 0.0f);
    glVertex3f(0.65f+ x_pos, -0.91f+ y_pos, 0.0f);
    glVertex3f(0.6f+ x_pos, -0.91f+ y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.6f, 0.0f);
    glVertex3f(0.47f+ x_pos, -0.85f+ y_pos, 0.0f);  // middle  quad
    glVertex3f(0.53f+ x_pos, -0.85f+ y_pos, 0.0f);
    glVertex3f(0.53f+ x_pos, -0.89f+ y_pos, 0.0f);
    glVertex3f(0.48f+ x_pos, -0.89f+ y_pos, 0.0f);
    glEnd();

}

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
    glutCreateWindow("RTR2024-129 Swati Ladkat");

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
    //code
    glViewport(0, 0, width, height);
}

void display(void)
{
    void Rangoli_Swati(float, float);

    float x_pos = 0, y_pos = 0;

    //code
    glClear(GL_COLOR_BUFFER_BIT);

    Rangoli_Swati(x_pos, y_pos);

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
    case'F':
    case'f':
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


