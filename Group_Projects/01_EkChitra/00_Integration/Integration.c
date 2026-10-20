/**************************************************
 * S.G.M.P
 * @file: Integration.c
 * @brief: Implementation of Integration code for 'Ek Chitr' Demo
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @Copyright ©2020-2023 MarshallingVoid
 * @date: 16 January 2025 (Thursday) 11:54:38 PM
 **************************************************/

// Header Files
#include <GL/freeglut.h>
#include <mmsystem.h>

#define	_USE_MATH_DEFINES
#include <math.h>

#define	VALUE_FROM_PERCENT(complete, percent)	(complete * percent / 100.0f)

#define	GOLDEN_RATIO 1.618033988

// Global Variable Declarations
BOOL bFullscreen = FALSE;

// Global Declaration
float fly_birds_factor = 0.0f;
float boat_pos_factor = -1.4f;
float texture_scale_factor = 0.0f;
float texture_pos_factor = 0.7f;
float sky_color_factor = 0.0f;

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

void keyboard(unsigned char key, int x, int y)
{
	//	Function Declaration
	void timer_Nivrutti(int value);
	void TextureScaleUpdate(int value);
	void TexturePosUpdate(int value);
	void SkyColorUpdate(int value);

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
		glutTimerFunc(0, timer_Nivrutti, 0);
		glutTimerFunc(0, TextureScaleUpdate, 0);
		glutTimerFunc(0, TexturePosUpdate, 0);
		glutTimerFunc(0, SkyColorUpdate, 0);
		PlaySound(".\\song.wav", NULL, SND_ASYNC);
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

void FlyBirdsUpdate(int value)
{
	// Code
	fly_birds_factor -= 0.01f;
	
	glutPostRedisplay();

	glutTimerFunc(50, FlyBirdsUpdate, value);
}

void BoatMoveUpdate(int value)
{
	// Code
	boat_pos_factor += 0.008f;
	
	glutPostRedisplay();

	if(0.6f > boat_pos_factor)
		glutTimerFunc(50, BoatMoveUpdate, value);
}

void TextureScaleUpdate(int value)
{
	// Code
	texture_scale_factor += 20.0f/ 200.0f;
	
	glutPostRedisplay();

	if(20.0f > texture_scale_factor)
		glutTimerFunc(50, TextureScaleUpdate, value);
}

void TexturePosUpdate(int value)
{
	// Code
	texture_pos_factor += (0.86f - 0.7f) / 200.0f;

	glutPostRedisplay();

	if(0.86f > texture_pos_factor)
		glutTimerFunc(50, TexturePosUpdate, value);

}

void SkyColorUpdate(int value)
{
	// Function Declaration
	void FlyBirdsUpdate(int value);
	void BoatMoveUpdate(int value);

	// Code
	sky_color_factor += 0.5f;

	glutPostRedisplay();

	if(100.0f <= sky_color_factor)
	{
		glutTimerFunc(0, FlyBirdsUpdate, 0);
		glutTimerFunc(0, BoatMoveUpdate, 0);
		glutPostRedisplay();
	}

	if(100.0f > sky_color_factor)
		glutTimerFunc(50, SkyColorUpdate, value);
}


void display(void)
{
	// Function Declaration
	void Hill_Gauri(float x_pos,float y_pos);
	void River_Nivrutti(float x_pos, float y_pos);
	void House_Prajwal(float x_pos, float y_pos);
	void Tulas_Adesh(float x_pos, float y_pos, float percent);
	void ChristmasTree_Atharv(float x_pos, float y_pos, int persent);
	void StraightCoconutTree_Atharv(float x_pos, float y_pos, int persent);
	void DIVA_Omkar(float x_pos, float y_pos, float percent, float percent2);
	void zopdi_prashant(float x_pos, float y_pos, float percent);
	void TiltedCoconutTree_Atharv(float x_pos, float y_pos, int persent);
	void Birds_Amol(float x_pos, float y_pos);
	void Texture_Mayur(float x_pos, float y_pos, float r, float g, float b, float percent);
	void Rangoli_Swati(float x_pos, float y_pos);
	void Grass_Mayur(float x_pos, float y_pos, float percent);
	void tactor(float x_pos,float y_pos);
	void Boat_Prasad(float x_pos, float y_pos);
	void Morning_Sky_Mayur(float x_pos, float y_pos, float percent);
	void Farming_Pankaj(float x_offset, float y_offset, float percent);
	void Pati_Atharv(float x_pos, float y_pos, float percent, char * msg);
	void FlowerPot_Shivkumar(float x_pos, float y_pos);


	// Code
	glClear(GL_COLOR_BUFFER_BIT);

	//	Call to Grass_Mayur(); 
	Grass_Mayur(0.0f, 0.0f, 140.0f);

	//	Call To River_Nivrutti()
    glPointSize(6.0);	
	River_Nivrutti(0.0f, -0.045f);
    glPointSize(1.0);

	//	Call To Draw Morning_Sky_Mayur()
    Morning_Sky_Mayur(0.0f, 0.8f, 120.0f);

	//	Call To Draw Hill_Gauri()
	Hill_Gauri(0.0f, -0.045f);

    // Call to StraightCoconutTree_Atharv
    StraightCoconutTree_Atharv(-0.98f, 0.35f, 100);

    //	Call to House_Prajwal()
    House_Prajwal(-1.0f, 0.6f);

    //	Call to Tulas_Adesh();
    Tulas_Adesh(-0.8f, -0.20f, 65.0f);

    // Call to DIVA_Omkar()
    DIVA_Omkar(-0.81f, -0.03f, 10.0f, 20.0f);
    DIVA_Omkar(-0.69f, -0.03f, 10.0f, 20.0f);
    DIVA_Omkar(-0.38f, -0.03f, 10.0f, 20.0f);
    DIVA_Omkar(-0.47f, -0.03f, 10.0f, 20.0f);

    // Call TiltedCoconutTree_Atharv
    TiltedCoconutTree_Atharv(0.15f, 0.6f, 100);

    // Call to zopdi_prashant
    zopdi_prashant(1.2f, 0.4f, 80.0f);

    // Call to Texture();
	Texture_Mayur(0.3f, texture_pos_factor, 255.0f / 255.0f, 95.0f / 255.0f, 21.0f / 255.0f, texture_scale_factor);

    //	Call to Birds_Amol
    Birds_Amol(0.5f + fly_birds_factor, 0.2f);

    // 	Call to Rangoli_Swati
    Rangoli_Swati(-1.2f, 0.6f);

    //	Call to Boat_Prasad
    Boat_Prasad(boat_pos_factor, -0.7f); 
    	
    //	Call to Farming_Pankaj()
	Farming_Pankaj(-0.3f, 0.2f, 23);
	Farming_Pankaj(-0.2f, 0.2f, 23);
	Farming_Pankaj(-0.1f, 0.2f, 23);
	Farming_Pankaj(0.0f, 0.2f, 23);

	Farming_Pankaj(-0.3f, 0.065f, 23);
	Farming_Pankaj(-0.2f, 0.065f, 23);
	Farming_Pankaj(-0.1f, 0.065f, 23);
	Farming_Pankaj(0.0f, 0.065f, 23);

	Farming_Pankaj(-0.3f, -0.0f, 23);
	Farming_Pankaj(-0.2f, -0.0f, 23);
	Farming_Pankaj(-0.1f, -0.0f, 23);
	Farming_Pankaj(0.0f, -0.0f, 23);

	Farming_Pankaj(-0.3f, -0.138f, 23);
	Farming_Pankaj(-0.2f, -0.138f, 23);
	Farming_Pankaj(-0.1f, -0.138f, 23);
	Farming_Pankaj(0.0f, -0.138f, 23);

	FlowerPot_Shivkumar(0.9f, -0.2f);
	FlowerPot_Shivkumar(0.55f, -0.2f);

	glutSwapBuffers();
}


void uninitialize(void)
{
	// Code
}


/**
 * 
 * 
 * 	CODE OF ALL GROUP MEMBERS BELOW
 * 
 * 
 */



void Hill_Gauri(float x_pos,float y_pos)
{	
	//////////1st hill

	{
		glBegin(GL_QUADS);
		glColor3f(0.498039, 0.333333, 0.278431);
		glVertex3f(-0.9999f + x_pos, 0.49f + y_pos, 0.0f);

		glColor3f(0.991157f, 0.466667f, 0.329412f);
		glVertex3f(-0.9999f + x_pos, 0.61f + y_pos, 0.0f);

		glColor3f(0.498039, 0.333333, 0.278431);
		glVertex3f(-0.18f + x_pos, 0.61f + y_pos, 0.0f);

		glColor3f(0.498039, 0.333333, 0.278431);
		glVertex3f(-0.08f + x_pos, 0.49f + y_pos, 0.0f);

		glEnd();

		glBegin(GL_QUADS);

		glColor3f(0.498039, 0.333333, 0.278431);
		glVertex3f(-0.9999f + x_pos, 0.61f + y_pos, 0.0f);

		glColor3f(0.991157f, 0.466667f, 0.329412f);
		glVertex3f(-0.85f + x_pos, 0.76 + y_pos, 0.0f);

		glColor3f(0.991157f, 0.466667f, 0.329412f);
		glVertex3f(-0.30f + x_pos, 0.75f + y_pos, 0.0f);

		glColor3f(0.498039, 0.333333, 0.278431);
		glVertex3f(-0.18f + x_pos, 0.57f + y_pos, 0.0f);


		glEnd();


		glBegin(GL_QUADS);

		glColor3f(0.498039, 0.333333, 0.278431);
		glVertex3f(-0.85f + x_pos, 0.76f + y_pos, 0.0f);

		glColor3f(0.991157f, 0.466667f, 0.329412f);
		glVertex3f(-0.76f + x_pos, 0.85 + y_pos, 0.0f);

		glColor3f(0.991157f, 0.466667f, 0.329412f);
		glVertex3f(-0.34f + x_pos, 0.84f + y_pos, 0.0f);

		glColor3f(0.498039, 0.333333, 0.278431);
		glVertex3f(-0.30f + x_pos, 0.75f + y_pos, 0.0f);


		glEnd();



		glBegin(GL_QUADS);

		glColor3f(0.498039, 0.333333, 0.278431);
		glVertex3f(-0.76f + x_pos, 0.85f + y_pos, 0.0f);

		glColor3f(0.991157f, 0.466667f, 0.329412f);
		glVertex3f(-0.68f + x_pos, 0.90 + y_pos, 0.0f);

		glColor3f(0.991157f, 0.466667f, 0.329412f);
		glVertex3f(-0.45f + x_pos, 0.91f + y_pos, 0.0f);

		glColor3f(0.498039, 0.333333, 0.278431);
		glVertex3f(-0.34f + x_pos, 0.84f + y_pos, 0.0f);


		glEnd();



		glBegin(GL_QUADS);

		glColor3f(0.991157f, 0.466667f, 0.329412f);
		glVertex3f(-0.68f + x_pos, 0.90 + y_pos, 0.0f);

		glColor3f(0.600000, 0.600000, 0.600000);
		glVertex3f(-0.59f + x_pos,0.95 + y_pos, 0.0f);

		glColor3f(0.600000, 0.600000, 0.600000);
		glVertex3f(-0.57f + x_pos, 0.95 + y_pos, 0.0f);

		glColor3f(0.991157f, 0.466667f, 0.329412f);
		glVertex3f(-0.45f + x_pos, 0.91f + y_pos, 0.0f);


		glEnd();
	}

	////////////////////////2ed hill

	glBegin(GL_QUADS);
	//2 ed 
	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(-0.12f + x_pos, 0.53f + y_pos, 0.0f);

	glColor3f(0.991157f, 0.466667f, 0.329412f);
	glVertex3f(-0.22f + x_pos, 0.62f + y_pos, 0.0f);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(0.24f + x_pos, 0.61f + y_pos, 0.0f);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(0.34f + x_pos, 0.53f + y_pos, 0.0f);

	glEnd();

	glBegin(GL_QUADS);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(-0.22f + x_pos, 0.62f + y_pos, 0.0f);

	glColor3f(0.991157f, 0.466667f, 0.329412f);
	glVertex3f(-0.26f + x_pos, 0.68 + y_pos, 0.0f);

	glColor3f(0.991157f, 0.466667f, 0.329412f);
	glVertex3f(0.16f + x_pos, 0.68f + y_pos, 0.0f);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(0.24f + x_pos, 0.61f + y_pos, 0.0f);


	glEnd();


	glBegin(GL_QUADS);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(-0.26f + x_pos, 0.68 + y_pos, 0.0f);

	glColor3f(0.991157f, 0.466667f, 0.329412f);
	glVertex3f(-0.29f + x_pos, 0.73 + y_pos, 0.0f);

	glColor3f(0.991157f, 0.466667f, 0.329412f);
	glVertex3f(0.10f + x_pos, 0.72 + y_pos, 0.0f);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(0.16f + x_pos, 0.68f + y_pos, 0.0f);

	glEnd();


	glBegin(GL_QUADS);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(-0.29f + x_pos, 0.73 + y_pos, 0.0f);

	glColor3f(0.991157f, 0.466667f, 0.329412f);
	glVertex3f(-0.15f + x_pos, 0.79 + y_pos, 0.0f);

	glColor3f(0.991157f, 0.466667f, 0.329412f);
	glVertex3f(0.05f + x_pos, 0.78 + y_pos, 0.0f);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(0.10f + x_pos, 0.72 + y_pos, 0.0f);

	glEnd();


	glBegin(GL_QUADS);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(-0.15f + x_pos, 0.79 + y_pos, 0.0f);

	glColor3f(0.600000, 0.600000, 0.600000);
	glVertex3f(-0.08f + x_pos, 0.83 + y_pos, 0.0f);

	glColor3f(0.600000, 0.600000, 0.600000);
	glVertex3f(-0.06f + x_pos, 0.83f + y_pos, 0.0f);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(0.05f + x_pos, 0.78 + y_pos, 0.0f);


	glEnd();
	

	////////////3rd hill
	glBegin(GL_QUADS);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(0.25f + x_pos, 0.59f + y_pos, 0.0f);

	glColor3f(0.991157f, 0.466667f, 0.329412f);
	glVertex3f(0.16f + x_pos, 0.66f + y_pos, 0.0f);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(0.49f + x_pos, 0.66f + y_pos, 0.0f);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(0.49f + x_pos, 0.59f + y_pos, 0.0f);

	glEnd();

	glBegin(GL_QUADS);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(0.16f + x_pos, 0.66f + y_pos, 0.0f);

	glColor3f(0.991157f, 0.466667f, 0.329412f);
	glVertex3f(0.10f + x_pos, 0.72 + y_pos, 0.0f);

	glColor3f(0.991157f, 0.466667f, 0.329412f);
	glVertex3f(0.40f + x_pos, 0.72f + y_pos, 0.0f);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(0.49f + x_pos, 0.66f + y_pos, 0.0f);


	glEnd();

	glBegin(GL_QUADS);

	glColor3f(0.991157f, 0.466667f, 0.329412f);
	glVertex3f(0.10f + x_pos, 0.72 + y_pos, 0.0f);

	glColor3f(0.600000, 0.600000, 0.600000);
	glVertex3f(0.20f + x_pos, 0.76 + y_pos, 0.0f);

	glColor3f(0.600000, 0.600000, 0.600000);
	glVertex3f(0.21f + x_pos, 0.76 + y_pos, 0.0f);

	glColor3f(0.991157f, 0.466667f, 0.329412f);
	glVertex3f(0.40f + x_pos, 0.72f + y_pos, 0.0f);

	glEnd();

	


	//////////////////4th  hill

	glBegin(GL_QUADS);
	//4 last ed 
	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(0.39f + x_pos, 0.57f + y_pos, 0.0f);

	glColor3f(0.991157f, 0.466667f, 0.329412f);
	glVertex3f(0.45f + x_pos, 0.68f + y_pos, 0.0f);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(0.9999f + x_pos, 0.69f + y_pos, 0.0f);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(0.9999f + x_pos, 0.57f + y_pos, 0.0f);

	glEnd();

	glBegin(GL_QUADS);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(0.45f + x_pos, 0.68f + y_pos, 0.0f);

	glColor3f(0.991157f, 0.466667f, 0.329412f);
	glVertex3f(0.49f + x_pos, 0.74 + y_pos, 0.0f);

	glColor3f(0.991157f, 0.466667f, 0.329412f);
	glVertex3f(0.96f + x_pos, 0.75f + y_pos, 0.0f);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(0.9999f + x_pos, 0.69f + y_pos, 0.0f);


	glEnd();


	glBegin(GL_QUADS);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(0.49f + x_pos, 0.74 + y_pos, 0.0f);

	glColor3f(0.991157f, 0.466667f, 0.329412f);
	glVertex3f(0.54f + x_pos, 0.80 + y_pos, 0.0f);

	glColor3f(0.991157f, 0.466667f, 0.329412f);
	glVertex3f(0.90f + x_pos, 0.81 + y_pos, 0.0f);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(0.96f + x_pos, 0.75f + y_pos, 0.0f);

	glEnd();



	glBegin(GL_QUADS);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(0.54f + x_pos, 0.80 + y_pos, 0.0f);

	glColor3f(0.600000, 0.600000, 0.600000);
	glVertex3f(0.68f + x_pos, 0.86 + y_pos, 0.0f);

	glColor3f(0.600000, 0.600000, 0.600000);
	glVertex3f(0.73f + x_pos, 0.87f + y_pos, 0.0f);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(0.90f + x_pos, 0.81 + y_pos, 0.0f);


	glEnd();
}



// Wave parameters
float amp_first_wave = 0.035f;
float amp_second_wave = 0.025f;
float BASE_HEIGHT = -0.6f;

// Timer settings
int increasing = 1; //  1 for increasing, 0 for decreasing Directon

// River Object Function Defination
void River_Nivrutti(float x_pos, float y_pos) 
{
    glColor3f(0.53f, 0.81f, 0.92f);

	// Draw wave like structue usng sine wave
    glBegin(GL_POINTS);
    float x, y, wave;
    for (x = -1.0; x <= 1.0; x += 0.005) 
	{
        wave = amp_first_wave * sin(x * 10) + amp_second_wave * sin(x * 20);

        for (y = -1.0; y <= (BASE_HEIGHT + wave); y += 0.005)
		{
            glVertex3f( x+x_pos, y+y_pos, 0.0f);
        }
    }
    glEnd();



	//************************* Quads for river lower Gradient ****************************** 
	glBegin(GL_QUADS);

	glColor3f(0.136f, 0.535f, 0.85f);
	glVertex3f(-1.0f+x_pos, -1.0f+y_pos, 0.0f);

	glColor3f(0.109f, 0.636f, 0.921f);
	glVertex3f(-1.0f+x_pos, -0.90f+y_pos, 0.0f);

	glColor3f(0.109f, 0.636f, 0.921f);
	glVertex3f(1.0f+x_pos, -0.90f+y_pos, 0.0f);
	
	glColor3f(0.136f, 0.535f, 0.85f);
	glVertex3f(1.0f+x_pos, -1.0f+y_pos, 0.0f);
	glEnd();


	glBegin(GL_QUADS);
	glColor3f(0.109f, 0.636f, 0.921f);
	glVertex3f(-1.0f+x_pos, -0.90f+y_pos, 0.0f);
	
	glColor3f(0.351, 0.734, 0.843);
	glVertex3f(-1.0f+x_pos, -0.85f+y_pos, 0.0f);
	
	glColor3f(0.351, 0.734, 0.843);
	glVertex3f(1.0f+x_pos, -0.85f+y_pos, 0.0f);
	
	glColor3f(0.109f, 0.636f, 0.921f);
	glVertex3f(1.0f+x_pos, -0.90f+y_pos, 0.0f);
	glEnd();


	glBegin(GL_QUADS);
	glColor3f(0.351, 0.734, 0.843);
	glVertex3f(-1.0f+x_pos, -0.85f+y_pos, 0.0f);
	
	glColor3f(0.53f, 0.81f, 0.92f);
	glVertex3f(-1.0f+x_pos, -0.75f+y_pos, 0.0f);
	
	glColor3f(0.53f, 0.81f, 0.92f);
	glVertex3f(1.0f+x_pos, -0.75f+y_pos, 0.0f);

	glColor3f(0.351, 0.734, 0.843);
	glVertex3f(1.0f+x_pos, -0.85f+y_pos, 0.0f);
	glEnd();
	//**************************************************************************************** 


	// lower water flow starts here (waterfall like structure)
	glBegin(GL_QUADS);
	glColor3f(0.43, 0.79, 0.953);
	glVertex3f(0.20f+x_pos, 0.61f+y_pos, 0.0f);
	
	glColor3f(0.43, 0.79, 0.953);
	glVertex3f(0.40f+x_pos, 0.61f+y_pos, 0.0f);
	
	glColor3f(0.43, 0.79, 0.953);
	glVertex3f(0.41f+x_pos, 0.54f+y_pos, 0.0f);

	glColor3f(0.43, 0.79, 0.953);
	glVertex3f(0.32f+x_pos, 0.54f+y_pos, 0.0f);
	glEnd();


	glBegin(GL_QUAD_STRIP);
	glColor3f(0.43, 0.79, 0.953);
	glVertex3f(0.31f+x_pos, 0.54f+y_pos, 0.0f);
	glVertex3f(0.41f+x_pos, 0.54f+y_pos, 0.0f);

	glVertex3f(0.32f+x_pos, 0.48f+y_pos, 0.0f);
	glVertex3f(0.41f+x_pos, 0.44f+y_pos, 0.0f);
	
	glVertex3f(0.30f+x_pos, 0.34f+y_pos, 0.0f);
	glVertex3f(0.40f+x_pos, 0.34f+y_pos, 0.0f);

	glVertex3f(0.30f+x_pos, 0.24f+y_pos, 0.0f);
	glVertex3f(0.41f+x_pos, 0.23f+y_pos, 0.0f);

	glVertex3f(0.28f+x_pos, 0.17f+y_pos, 0.0f);
	glVertex3f(0.42f+x_pos, 0.15f+y_pos, 0.0f);

	glVertex3f(0.26f+x_pos, 0.03f+y_pos, 0.0f);
	glVertex3f(0.43f+x_pos, 0.02f+y_pos, 0.0f);
	
	glVertex3f(0.24f+x_pos, -0.09f+y_pos, 0.0f);
	glVertex3f(0.435f+x_pos, -0.1f+y_pos, 0.0f);
	
	glVertex3f(0.23f+x_pos, -0.19f+y_pos, 0.0f);
	glVertex3f(0.43f+x_pos, -0.20f+y_pos, 0.0f);
	
	glVertex3f(0.21f+x_pos, -0.31f+y_pos, 0.0f);
	glVertex3f(0.44f+x_pos, -0.32f+y_pos, 0.0f);

	glColor3f(0.53f, 0.81f, 0.92f);
	glVertex3f(0.19f+x_pos, -0.47f+y_pos, 0.0f);
	glVertex3f(0.45f+x_pos, -0.58f+y_pos, 0.0f);

	glColor3f(0.53f, 0.81f, 0.92f);
	glVertex3f(0.16f+x_pos, -0.60f+y_pos, 0.0f);
	glVertex3f(0.47f+x_pos, -0.73f+y_pos, 0.0f);
	
	glEnd();
}

// Timer callback function Defination
void timer_Nivrutti(int value) 
{
    if (increasing) 
	{
        amp_first_wave =amp_first_wave + 0.001f;
        amp_second_wave =amp_second_wave + 0.001f;

        if (amp_first_wave >= 0.04f)
		{
            increasing = 0;
        }
    } 
	else 
	{
        amp_first_wave = amp_first_wave - 0.001f;
        amp_second_wave = amp_second_wave - 0.001f;

        if (amp_first_wave <= 0.03f)
		{ 
            increasing = 1;
        }
    }

    glutPostRedisplay();

    glutTimerFunc(100, timer_Nivrutti, 0); // 100 milliseconds
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
	// glBegin(GL_QUADS);
	// {
	// 	glColor3f(0.250f, 0.250f, 0.250f);
	// 	glVertex3f(0.395f + x_pos, -0.25f + y_pos, 0.0f);
	// 	glVertex3f(0.455f + x_pos, -0.25f + y_pos, 0.0f);

	// 	glColor3f(0.5f, 0.5f, 0.5f);
	// 	glVertex3f(0.455f + x_pos, -0.275f + y_pos, 0.0f);
	// 	glVertex3f(0.395f + x_pos, -0.275f + y_pos, 0.0f);
	// }
	// glEnd();

	// glBegin(GL_QUADS);
	// {
	// 	glColor3f(0.50f, 0.50f, 0.50f);
	// 	glVertex3f(0.405f + x_pos, -0.275f + y_pos, 0.0f);
	// 	glVertex3f(0.445f + x_pos, -0.275f + y_pos, 0.0f);

	// 	glColor3f(0.75f, 0.0f, 0.0f);
	// 	glVertex3f(0.445f + x_pos, -0.30f + y_pos, 0.0f);
	// 	glVertex3f(0.405f + x_pos, -0.30f + y_pos, 0.0f);
	// }
	// glEnd();
}


void Tulas_Adesh(float x_pos, float y_pos, float percent)
{
	// Function Prototype
	void Tulsi_Vrindavan(float x_pos, float y_pos, float percent);
	void Tulsi_leaf(float x_pos, float y_pos, float percent);
	void Tulsi_Branches(float x_pos, float y_pos, float percent);

	// Call to design vrindavan
	Tulsi_Vrindavan(x_pos, y_pos, percent);
	
	// Call to design tulsi branches
	Tulsi_Branches(x_pos, y_pos, percent);

	// Call for tulsi leaf
	Tulsi_leaf(x_pos, y_pos, percent);

}


void Tulsi_Vrindavan(float x_pos, float y_pos, float percent)
{
	// main quad for tulsi
	glBegin(GL_QUADS);

	//import the color
	glColor3f(1.0f, 1.0f, 1.0f);

	//set the vertices
	glVertex2d(VALUE_FROM_PERCENT(0.52f, percent) + x_pos, VALUE_FROM_PERCENT( -0.20f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.52f, percent) + x_pos, VALUE_FROM_PERCENT( -0.50f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.64f, percent) + x_pos, VALUE_FROM_PERCENT( -0.50f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.64f, percent) + x_pos, VALUE_FROM_PERCENT( -0.20f , percent) + y_pos);

	glEnd();

	// Upper Rechangular Quad
	glBegin(GL_QUADS);

	//import the color
	glColor3f(0.9f, 0.0f, 0.0f);

	//set the vertices
	glVertex2d(VALUE_FROM_PERCENT(0.48f, percent) + x_pos, VALUE_FROM_PERCENT( -0.16f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.48f, percent) + x_pos, VALUE_FROM_PERCENT( -0.23f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.68f, percent) + x_pos, VALUE_FROM_PERCENT( -0.23f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.68f, percent) + x_pos, VALUE_FROM_PERCENT( -0.16f , percent) + y_pos);

	glEnd();

	//Set Triangles on upper quad
	glBegin(GL_TRIANGLES);

	//Set the color
	glColor3f(0.9f, 0.0f, 0.0f);

	// Set the vertices for right triangle
	glVertex3f(VALUE_FROM_PERCENT(0.68f, percent) + x_pos, VALUE_FROM_PERCENT( -0.11f, percent) + y_pos, 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(0.68f, percent) + x_pos, VALUE_FROM_PERCENT( -0.16f, percent) + y_pos, 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(0.64f, percent) + x_pos, VALUE_FROM_PERCENT( -0.16f, percent) + y_pos, 0.0f);

	// Set the vertice for left triangle
	glVertex3f(VALUE_FROM_PERCENT(0.48f, percent) + x_pos, VALUE_FROM_PERCENT( -0.11f, percent) + y_pos, 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(0.48f, percent) + x_pos, VALUE_FROM_PERCENT( -0.16f, percent) + y_pos, 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(0.52f, percent) + x_pos, VALUE_FROM_PERCENT( -0.16f, percent) + y_pos, 0.0f);

	glEnd();

	// Lower Rectangular Quad
	glBegin(GL_QUADS);

	//import the color
	glColor3f(0.9f, 0.0f, 0.0f);

	//set the vertices
	glVertex2d(VALUE_FROM_PERCENT(0.48f, percent) + x_pos, VALUE_FROM_PERCENT( -0.50f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.48f, percent) + x_pos, VALUE_FROM_PERCENT( -0.55f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.68f, percent) + x_pos, VALUE_FROM_PERCENT( -0.55f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.68f, percent) + x_pos, VALUE_FROM_PERCENT( -0.50f , percent) + y_pos);

	glEnd();

	// Swastik using line strips and point
	glBegin(GL_LINE_STRIP);

	// Draw the lines
	glVertex2f(VALUE_FROM_PERCENT(0.60f, percent) + x_pos, VALUE_FROM_PERCENT( -0.26f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.26f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.30f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.56f, percent) + x_pos, VALUE_FROM_PERCENT( -0.30f , percent) + y_pos);

	glEnd();

	// 1. Dots inside swastik: right upper
	glBegin(GL_QUADS);

	// Draw the points
	glVertex2f(VALUE_FROM_PERCENT(0.587000, percent) + x_pos, VALUE_FROM_PERCENT( -0.267000 , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.593000, percent) + x_pos, VALUE_FROM_PERCENT( -0.267000 , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.593000, percent) + x_pos, VALUE_FROM_PERCENT( -0.273000 , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.587000, percent) + x_pos, VALUE_FROM_PERCENT( -0.273000 , percent) + y_pos);

	glEnd();

	// 2. Dots inside swastik: right lower
	glBegin(GL_QUADS);

	// Draw the points
	glVertex2f(VALUE_FROM_PERCENT(0.587000, percent) + x_pos, VALUE_FROM_PERCENT( -0.287000 , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.593000, percent) + x_pos, VALUE_FROM_PERCENT( -0.287000 , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.593000, percent) + x_pos, VALUE_FROM_PERCENT( -0.293000 , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.587000, percent) + x_pos, VALUE_FROM_PERCENT( -0.293000 , percent) + y_pos);

	glEnd();

	// 3. Dots inside swastik: left lower
	glBegin(GL_QUADS);

	// Draw the points
	glVertex2f(VALUE_FROM_PERCENT(0.567000, percent) + x_pos, VALUE_FROM_PERCENT( -0.287000 , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.573000, percent) + x_pos, VALUE_FROM_PERCENT( -0.287000 , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.573000, percent) + x_pos, VALUE_FROM_PERCENT( -0.293000 , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.567000, percent) + x_pos, VALUE_FROM_PERCENT( -0.293000 , percent) + y_pos);

	glEnd();

	// 4. Dots inside swastik: left upper
	glBegin(GL_QUADS);

	// Draw the points
	glVertex2f(VALUE_FROM_PERCENT(0.567000, percent) + x_pos, VALUE_FROM_PERCENT( -0.267000 , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.573000, percent) + x_pos, VALUE_FROM_PERCENT( -0.267000 , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.573000, percent) + x_pos, VALUE_FROM_PERCENT( -0.273000 , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.567000, percent) + x_pos, VALUE_FROM_PERCENT( -0.273000 , percent) + y_pos);

	glEnd();

	glBegin(GL_LINE_STRIP);

	glVertex2f(VALUE_FROM_PERCENT(0.56f, percent) + x_pos, VALUE_FROM_PERCENT( -0.26f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.56f, percent) + x_pos, VALUE_FROM_PERCENT( -0.28f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.60f, percent) + x_pos, VALUE_FROM_PERCENT( -0.28f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.60f, percent) + x_pos, VALUE_FROM_PERCENT( -0.30f , percent) + y_pos);

	glEnd();

	// Middle Polygon for diya place
	glBegin(GL_POLYGON);

	//import the color
	glColor3f(0.1f, 0.1f, 0.1f);

	//set the vertices
	glVertex2d(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.35f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.56f, percent) + x_pos, VALUE_FROM_PERCENT( -0.38f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.56f, percent) + x_pos, VALUE_FROM_PERCENT( -0.45f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.60f, percent) + x_pos, VALUE_FROM_PERCENT( -0.45f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.60f, percent) + x_pos, VALUE_FROM_PERCENT( -0.38f , percent) + y_pos);

	glEnd();

	// Quad for diya
	glBegin(GL_QUADS);

	//import the color
	glColor3f(1.0f, 0.6470588235294, 0.0f);

	//set the vertices for diya
	glVertex2d(VALUE_FROM_PERCENT(0.5750f, percent) + x_pos, VALUE_FROM_PERCENT( -0.45f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.5850f, percent) + x_pos, VALUE_FROM_PERCENT( -0.45f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.59f, percent) + x_pos, VALUE_FROM_PERCENT( -0.43f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.57f, percent) + x_pos, VALUE_FROM_PERCENT( -0.43f , percent) + y_pos);

	//import the color for flame
	glColor3f(1.0f, 0.0, 0.0f);

	// set the vertices for flame
	glVertex2d(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.43f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.5825f, percent) + x_pos, VALUE_FROM_PERCENT( -0.41f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.39f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.5775f, percent) + x_pos, VALUE_FROM_PERCENT( -0.43f , percent) + y_pos);

	glEnd();
}

void Tulsi_leaf(float x_pos, float y_pos, float percent)
{
	// Quads for leafs
	glBegin(GL_QUADS);

	// Set the color for leaf
    glColor3f(0.0f, 0.4f, 0.1f);

	// set the vertices

	// 1. bottom right first from down
	glVertex2d(VALUE_FROM_PERCENT(0.63f, percent) + x_pos, VALUE_FROM_PERCENT( -0.13f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.64f, percent) + x_pos, VALUE_FROM_PERCENT( -0.12f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.65f, percent) + x_pos, VALUE_FROM_PERCENT( -0.13f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.64f, percent) + x_pos, VALUE_FROM_PERCENT( -0.14f , percent) + y_pos);

	glVertex2d(VALUE_FROM_PERCENT(0.62f, percent) + x_pos, VALUE_FROM_PERCENT( -0.10f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.62f, percent) + x_pos, VALUE_FROM_PERCENT( -0.09f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.64f, percent) + x_pos, VALUE_FROM_PERCENT( -0.08f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.63f, percent) + x_pos, VALUE_FROM_PERCENT( -0.10f , percent) + y_pos);

	glVertex2d(VALUE_FROM_PERCENT(0.66f, percent) + x_pos, VALUE_FROM_PERCENT( -0.11f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.67f, percent) + x_pos, VALUE_FROM_PERCENT( -0.10f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.69f, percent) + x_pos, VALUE_FROM_PERCENT( -0.11f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.67f, percent) + x_pos, VALUE_FROM_PERCENT( -0.12f , percent) + y_pos);

	glVertex2d(VALUE_FROM_PERCENT(0.67f, percent) + x_pos, VALUE_FROM_PERCENT( -0.07f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.67f, percent) + x_pos, VALUE_FROM_PERCENT( -0.06f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.69f, percent) + x_pos, VALUE_FROM_PERCENT( -0.05f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.68f, percent) + x_pos, VALUE_FROM_PERCENT( -0.07f , percent) + y_pos);

	glVertex2d(VALUE_FROM_PERCENT(0.70f, percent) + x_pos, VALUE_FROM_PERCENT( -0.09f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.71f, percent) + x_pos, VALUE_FROM_PERCENT( -0.08f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.73f, percent) + x_pos, VALUE_FROM_PERCENT( -0.09f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.71f, percent) + x_pos, VALUE_FROM_PERCENT( -0.10f , percent) + y_pos);

	glVertex2d(VALUE_FROM_PERCENT(0.70f, percent) + x_pos, VALUE_FROM_PERCENT( -0.07f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.70f, percent) + x_pos, VALUE_FROM_PERCENT( -0.06f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.72f, percent) + x_pos, VALUE_FROM_PERCENT( -0.05f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.71f, percent) + x_pos, VALUE_FROM_PERCENT( -0.07f , percent) + y_pos);

	// 2. Middle Right branch
	glVertex2d(VALUE_FROM_PERCENT(0.62f, percent) + x_pos, VALUE_FROM_PERCENT( -0.06f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.63f, percent) + x_pos, VALUE_FROM_PERCENT( -0.05f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.65f, percent) + x_pos, VALUE_FROM_PERCENT( -0.06f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.63f, percent) + x_pos, VALUE_FROM_PERCENT( -0.07f , percent) + y_pos);

	glVertex2d(VALUE_FROM_PERCENT(0.61f, percent) + x_pos, VALUE_FROM_PERCENT( -0.03f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.60f, percent) + x_pos, VALUE_FROM_PERCENT( -0.02f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.61f, percent) + x_pos, VALUE_FROM_PERCENT( -0.00f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.62f, percent) + x_pos, VALUE_FROM_PERCENT( -0.02f , percent) + y_pos);

	glVertex2d(VALUE_FROM_PERCENT(0.65f, percent) + x_pos, VALUE_FROM_PERCENT( -0.03f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.66f, percent) + x_pos, VALUE_FROM_PERCENT( -0.02f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.68f, percent) + x_pos, VALUE_FROM_PERCENT( -0.03f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.66f, percent) + x_pos, VALUE_FROM_PERCENT( -0.04f , percent) + y_pos);

	glVertex2d(VALUE_FROM_PERCENT(0.64f, percent) + x_pos, VALUE_FROM_PERCENT( -0.02f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.64f, percent) + x_pos, VALUE_FROM_PERCENT( -0.01f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.66f, percent) + x_pos, VALUE_FROM_PERCENT( -0.00f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.65f, percent) + x_pos, VALUE_FROM_PERCENT( -0.02f , percent) + y_pos);

	// 3. Third right left from bottom
	glVertex2d(VALUE_FROM_PERCENT(0.59f, percent) + x_pos, VALUE_FROM_PERCENT( -0.04f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.59f, percent) + x_pos, VALUE_FROM_PERCENT( -0.03f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.60f, percent) + x_pos, VALUE_FROM_PERCENT( -0.02f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.60f, percent) + x_pos, VALUE_FROM_PERCENT( -0.04f , percent) + y_pos);

	// 4. Second top right leaf
	glVertex2d(VALUE_FROM_PERCENT(0.59f, percent) + x_pos, VALUE_FROM_PERCENT( -0.00f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.59f, percent) + x_pos, VALUE_FROM_PERCENT( +0.01f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.61f, percent) + x_pos, VALUE_FROM_PERCENT( +0.02f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.60f, percent) + x_pos, VALUE_FROM_PERCENT( -0.00f , percent) + y_pos);

	// 5. Top leaf
	glVertex2d(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( +0.01f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.57f, percent) + x_pos, VALUE_FROM_PERCENT( +0.02f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( +0.04f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.59f, percent) + x_pos, VALUE_FROM_PERCENT( +0.02f , percent) + y_pos);

	// 6. Bottom left first from down
	glVertex2d(VALUE_FROM_PERCENT(0.54f, percent) + x_pos, VALUE_FROM_PERCENT( -0.13f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.53f, percent) + x_pos, VALUE_FROM_PERCENT( -0.12f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.51f, percent) + x_pos, VALUE_FROM_PERCENT( -0.13f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.53f, percent) + x_pos, VALUE_FROM_PERCENT( -0.14f , percent) + y_pos);

	glVertex2d(VALUE_FROM_PERCENT(0.54f, percent) + x_pos, VALUE_FROM_PERCENT( -0.10f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.54f, percent) + x_pos, VALUE_FROM_PERCENT( -0.09f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.52f, percent) + x_pos, VALUE_FROM_PERCENT( -0.08f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.53f, percent) + x_pos, VALUE_FROM_PERCENT( -0.10f , percent) + y_pos);

	glVertex2d(VALUE_FROM_PERCENT(0.49f, percent) + x_pos, VALUE_FROM_PERCENT( -0.10f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.48f, percent) + x_pos, VALUE_FROM_PERCENT( -0.09f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.46f, percent) + x_pos, VALUE_FROM_PERCENT( -0.10f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.48f, percent) + x_pos, VALUE_FROM_PERCENT( -0.11f , percent) + y_pos);

	glVertex2d(VALUE_FROM_PERCENT(0.49f, percent) + x_pos, VALUE_FROM_PERCENT( -0.07f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.49f, percent) + x_pos, VALUE_FROM_PERCENT( -0.06f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.47f, percent) + x_pos, VALUE_FROM_PERCENT( -0.05f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.48f, percent) + x_pos, VALUE_FROM_PERCENT( -0.07f , percent) + y_pos);

	glVertex2d(VALUE_FROM_PERCENT(0.46f, percent) + x_pos, VALUE_FROM_PERCENT( -0.07f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.46f, percent) + x_pos, VALUE_FROM_PERCENT( -0.06f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.43f, percent) + x_pos, VALUE_FROM_PERCENT( -0.05f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.45f, percent) + x_pos, VALUE_FROM_PERCENT( -0.07f , percent) + y_pos);

	// 7. Bottom left second from down branch
	glVertex2d(VALUE_FROM_PERCENT(0.57f, percent) + x_pos, VALUE_FROM_PERCENT( -0.09f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.56f, percent) + x_pos, VALUE_FROM_PERCENT( -0.09f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.55f, percent) + x_pos, VALUE_FROM_PERCENT( -0.10f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.56f, percent) + x_pos, VALUE_FROM_PERCENT( -0.10f , percent) + y_pos);

	glVertex2d(VALUE_FROM_PERCENT(0.57f, percent) + x_pos, VALUE_FROM_PERCENT( -0.09f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.09f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.08f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.57f, percent) + x_pos, VALUE_FROM_PERCENT( -0.08f , percent) + y_pos);

	glVertex2d(VALUE_FROM_PERCENT(0.56f, percent) + x_pos, VALUE_FROM_PERCENT( -0.08f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.55f, percent) + x_pos, VALUE_FROM_PERCENT( -0.08f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.54f, percent) + x_pos, VALUE_FROM_PERCENT( -0.06f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.56f, percent) + x_pos, VALUE_FROM_PERCENT( -0.07f , percent) + y_pos);

	// 8. Top left second from up branch
	glVertex2d(VALUE_FROM_PERCENT(0.54f, percent) + x_pos, VALUE_FROM_PERCENT( -0.05f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.53f, percent) + x_pos, VALUE_FROM_PERCENT( -0.04f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.51f, percent) + x_pos, VALUE_FROM_PERCENT( -0.05f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.53f, percent) + x_pos, VALUE_FROM_PERCENT( -0.06f , percent) + y_pos);

	glVertex2d(VALUE_FROM_PERCENT(0.54f, percent) + x_pos, VALUE_FROM_PERCENT( -0.02f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.53f, percent) + x_pos, VALUE_FROM_PERCENT( -0.02f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.52f, percent) + x_pos, VALUE_FROM_PERCENT( -0.00f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.54f, percent) + x_pos, VALUE_FROM_PERCENT( -0.01f , percent) + y_pos);

	glVertex2d(VALUE_FROM_PERCENT(0.51f, percent) + x_pos, VALUE_FROM_PERCENT( -0.02f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.50f, percent) + x_pos, VALUE_FROM_PERCENT( -0.02f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.48f, percent) + x_pos, VALUE_FROM_PERCENT( -0.00f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.51f, percent) + x_pos, VALUE_FROM_PERCENT( -0.01f , percent) + y_pos);

	// 9. Top left branch with single leaf
	glVertex2d(VALUE_FROM_PERCENT(0.56f, percent) + x_pos, VALUE_FROM_PERCENT( -0.01f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.55f, percent) + x_pos, VALUE_FROM_PERCENT( -0.01f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.54f, percent) + x_pos, VALUE_FROM_PERCENT( +0.01f , percent) + y_pos);
	glVertex2d(VALUE_FROM_PERCENT(0.56f, percent) + x_pos, VALUE_FROM_PERCENT( -0.00f , percent) + y_pos);

	glEnd();
}

void Tulsi_Branches(float x_pos, float y_pos, float percent)
{
	//Tulas plant branches
	glBegin(GL_LINE_STRIP);

	// Set the color
	glColor3f(0.40f, 0.0f, 0.0f);

	// Virtical strip
	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( 0.01f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.16f , percent) + y_pos);

	// Sub-strip from right bottom branch
	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.14f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.70f, percent) + x_pos, VALUE_FROM_PERCENT( -0.07f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.14f , percent) + y_pos);

	glVertex2f(VALUE_FROM_PERCENT(0.60f, percent) + x_pos, VALUE_FROM_PERCENT( -0.13f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.63f, percent) + x_pos, VALUE_FROM_PERCENT( -0.13f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.60f, percent) + x_pos, VALUE_FROM_PERCENT( -0.13f , percent) + y_pos);

	glVertex2f(VALUE_FROM_PERCENT(0.61f, percent) + x_pos, VALUE_FROM_PERCENT( -0.12f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.62f, percent) + x_pos, VALUE_FROM_PERCENT( -0.10f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.61f, percent) + x_pos, VALUE_FROM_PERCENT( -0.12f , percent) + y_pos);

	glVertex2f(VALUE_FROM_PERCENT(0.63f, percent) + x_pos, VALUE_FROM_PERCENT( -0.11f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.66f, percent) + x_pos, VALUE_FROM_PERCENT( -0.11f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.63f, percent) + x_pos, VALUE_FROM_PERCENT( -0.11f , percent) + y_pos);

	glVertex2f(VALUE_FROM_PERCENT(0.65f, percent) + x_pos, VALUE_FROM_PERCENT( -0.10f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.67f, percent) + x_pos, VALUE_FROM_PERCENT( -0.07f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.65f, percent) + x_pos, VALUE_FROM_PERCENT( -0.10f , percent) + y_pos);

	glVertex2f(VALUE_FROM_PERCENT(0.67f, percent) + x_pos, VALUE_FROM_PERCENT( -0.09f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.70f, percent) + x_pos, VALUE_FROM_PERCENT( -0.09f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.67f, percent) + x_pos, VALUE_FROM_PERCENT( -0.09f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.14f , percent) + y_pos);

	// #################################

	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.08f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.64f, percent) + x_pos, VALUE_FROM_PERCENT( -0.02f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.08f , percent) + y_pos);

	glVertex2f(VALUE_FROM_PERCENT(0.60f, percent) + x_pos, VALUE_FROM_PERCENT( -0.06f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.62f, percent) + x_pos, VALUE_FROM_PERCENT( -0.06f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.60f, percent) + x_pos, VALUE_FROM_PERCENT( -0.06f , percent) + y_pos);

	glVertex2f(VALUE_FROM_PERCENT(0.61f, percent) + x_pos, VALUE_FROM_PERCENT( -0.05f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.61f, percent) + x_pos, VALUE_FROM_PERCENT( -0.03f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.61f, percent) + x_pos, VALUE_FROM_PERCENT( -0.05f , percent) + y_pos);

	glVertex2f(VALUE_FROM_PERCENT(0.63f, percent) + x_pos, VALUE_FROM_PERCENT( -0.03f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.66f, percent) + x_pos, VALUE_FROM_PERCENT( -0.03f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.63f, percent) + x_pos, VALUE_FROM_PERCENT( -0.03f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.08f , percent) + y_pos);

	// #################################

	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.05f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.59f, percent) + x_pos, VALUE_FROM_PERCENT( -0.04f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.05f , percent) + y_pos);

	// #################################

	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.01f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.59f, percent) + x_pos, VALUE_FROM_PERCENT( 0.00f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.01f , percent) + y_pos);

	// Sub-strip for left branch
	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.14f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.46f, percent) + x_pos, VALUE_FROM_PERCENT( -0.07f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.14f , percent) + y_pos);

	glVertex2f(VALUE_FROM_PERCENT(0.56f, percent) + x_pos, VALUE_FROM_PERCENT( -0.13f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.54f, percent) + x_pos, VALUE_FROM_PERCENT( -0.13f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.56f, percent) + x_pos, VALUE_FROM_PERCENT( -0.13f , percent) + y_pos);

	glVertex2f(VALUE_FROM_PERCENT(0.55f, percent) + x_pos, VALUE_FROM_PERCENT( -0.12f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.54f, percent) + x_pos, VALUE_FROM_PERCENT( -0.10f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.55f, percent) + x_pos, VALUE_FROM_PERCENT( -0.12f , percent) + y_pos);

	glVertex2f(VALUE_FROM_PERCENT(0.51f, percent) + x_pos, VALUE_FROM_PERCENT( -0.10f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.49f, percent) + x_pos, VALUE_FROM_PERCENT( -0.10f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.51f, percent) + x_pos, VALUE_FROM_PERCENT( -0.10f , percent) + y_pos);

	glVertex2f(VALUE_FROM_PERCENT(0.50f, percent) + x_pos, VALUE_FROM_PERCENT( -0.09f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.49f, percent) + x_pos, VALUE_FROM_PERCENT( -0.07f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.50f, percent) + x_pos, VALUE_FROM_PERCENT( -0.09f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.14f , percent) + y_pos);

	// #################################

	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.11f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.56f, percent) + x_pos, VALUE_FROM_PERCENT( -0.08f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.11f , percent) + y_pos);

	// #################################

	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.06f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.51f, percent) + x_pos, VALUE_FROM_PERCENT( -0.02f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.06f , percent) + y_pos);

	glVertex2f(VALUE_FROM_PERCENT(0.56f, percent) + x_pos, VALUE_FROM_PERCENT( -0.05f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.54f, percent) + x_pos, VALUE_FROM_PERCENT( -0.05f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.56f, percent) + x_pos, VALUE_FROM_PERCENT( -0.05f , percent) + y_pos);

	glVertex2f(VALUE_FROM_PERCENT(0.55f, percent) + x_pos, VALUE_FROM_PERCENT( -0.04f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.54f, percent) + x_pos, VALUE_FROM_PERCENT( -0.02f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.55f, percent) + x_pos, VALUE_FROM_PERCENT( -0.04f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.06f , percent) + y_pos);

	// #################################

	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.03f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.56f, percent) + x_pos, VALUE_FROM_PERCENT( -0.01f , percent) + y_pos);
	glVertex2f(VALUE_FROM_PERCENT(0.58f, percent) + x_pos, VALUE_FROM_PERCENT( -0.03f , percent) + y_pos);

	glEnd();
}


// Function Defination
/*
    @description : function for displaying Christmas tree having 3 parameters :
                    1) x_pos -> to change x co-ordinate of object
                    2) y_pos -> to change y co-ordinate of object
                    3) persent -> to change scale of object
*/
void ChristmasTree_Atharv(float x_pos, float y_pos, int persent)
{
    /*
        Stem of Christmas tree
    */
    glBegin(GL_QUADS);
    {
        glColor3f(0.4f, 0.1f, 0.0f);
        glVertex2f(VALUE_FROM_PERCENT(-0.52f, persent) + x_pos, VALUE_FROM_PERCENT(0.0f, persent) + y_pos);      
        glVertex2f(VALUE_FROM_PERCENT(-0.52f, persent) + x_pos, VALUE_FROM_PERCENT(-0.09f, persent) + y_pos);         
        glColor3f(0.6f, 0.4f, 0.1f);
        glVertex2f(VALUE_FROM_PERCENT(-0.49f, persent) + x_pos, VALUE_FROM_PERCENT(-0.09f, persent) + y_pos);        
        glVertex2f(VALUE_FROM_PERCENT(-0.49f, persent) + x_pos, VALUE_FROM_PERCENT(0.0f, persent) + y_pos);  
    }
    glEnd();


    /*
        Leaves of Christmas Tree
    */
    glBegin(GL_TRIANGLES); // Last Part
    {
        glColor3f(0.6f, 0.9f, 0.1f);
        glVertex2f(VALUE_FROM_PERCENT(-0.51f, persent) + x_pos, VALUE_FROM_PERCENT(0.18f, persent) + y_pos);       
        glColor3f(0.6f, 0.6f, 0.0f);
        glVertex2f(VALUE_FROM_PERCENT(-0.63f, persent) + x_pos, VALUE_FROM_PERCENT(0.0f, persent) + y_pos);      
        glColor3f(0.6f, 0.6f, 0.0f);
        glVertex2f(VALUE_FROM_PERCENT(-0.38f, persent) + x_pos, VALUE_FROM_PERCENT(0.0f, persent) + y_pos);
    }
    glEnd();

    glBegin(GL_TRIANGLES); // Middel Part
    {
        glColor3f(0.6f, 0.9f, 0.1f);
        glVertex2f(VALUE_FROM_PERCENT(-0.51f, persent) + x_pos, VALUE_FROM_PERCENT(0.28f , persent) + y_pos);       
        glColor3f(0.6f, 0.6f, 0.0f);
        glVertex2f(VALUE_FROM_PERCENT(-0.60f, persent) + x_pos, VALUE_FROM_PERCENT(0.12f , persent) + y_pos);       
        glColor3f(0.6f, 0.6f, 0.0f);
        glVertex2f(VALUE_FROM_PERCENT(-0.41f, persent) + x_pos, VALUE_FROM_PERCENT(0.12f , persent) + y_pos);   
    }
    glEnd();

    glBegin(GL_TRIANGLES); // First Part
    {
        glColor3f(0.3f, 0.5f, 0.0f);
		// glColor3f(0.0f, 0.4f, 0.1f);
        glVertex2f(VALUE_FROM_PERCENT(-0.51f, persent) + x_pos, VALUE_FROM_PERCENT(0.34f , persent) + y_pos);       
        glColor3f(0.3f, 0.5f, 0.0f);
        // glColor3f(0.6f, 0.6f, 0.0f);
        glVertex2f(VALUE_FROM_PERCENT(-0.55f, persent) + x_pos, VALUE_FROM_PERCENT(0.24f , persent) + y_pos);       
        glColor3f(0.3f, 0.5f, 0.0f);
        // glColor3f(0.6f, 0.6f, 0.0f);
        glVertex2f(VALUE_FROM_PERCENT(-0.46f, persent) + x_pos, VALUE_FROM_PERCENT(0.24f , persent) + y_pos);   
    }
    glEnd();
}

void StraightCoconutTree_Atharv(float x_pos, float y_pos, int persent)
{
        /*
            Stem of a Coconut Tree
        */
        {
            glBegin(GL_QUADS); // part 1
            {
                glColor3f(0.5f, 0.2f, 0.0f);
                glVertex2f(VALUE_FROM_PERCENT(0.11f, persent) + x_pos, VALUE_FROM_PERCENT(0.0f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.10f, persent) + x_pos, VALUE_FROM_PERCENT(-0.03f, persent) + y_pos);
                glColor3f(0.8f, 0.5f, 0.3f);
                glVertex2f(VALUE_FROM_PERCENT(0.13f, persent) + x_pos, VALUE_FROM_PERCENT(-0.03f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.123f, persent) + x_pos,VALUE_FROM_PERCENT( 0.0f , persent)+ y_pos);
            }
            glEnd();

            glBegin(GL_QUADS); // part 2
            {
                glColor3f(0.5f, 0.2f, 0.0f);
                glVertex2f(VALUE_FROM_PERCENT(0.10f, persent) + x_pos, VALUE_FROM_PERCENT(-0.03f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.10f, persent) + x_pos, VALUE_FROM_PERCENT(-0.07f, persent) + y_pos);
                glColor3f(0.8f, 0.5f, 0.3f);
                glVertex2f(VALUE_FROM_PERCENT(0.13f, persent) + x_pos, VALUE_FROM_PERCENT(-0.07f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.13f, persent) + x_pos, VALUE_FROM_PERCENT(-0.03f, persent) + y_pos);
            }
            glEnd();

            glBegin(GL_QUADS); // part 3
            {
                glColor3f(0.5f, 0.2f, 0.0f);
                glVertex2f(VALUE_FROM_PERCENT(0.10f, persent) + x_pos, VALUE_FROM_PERCENT(-0.07f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.10f, persent) + x_pos, VALUE_FROM_PERCENT(-0.12f, persent) + y_pos);
                glColor3f(0.8f, 0.5f, 0.3f);
                glVertex2f(VALUE_FROM_PERCENT(0.135f, persent) + x_pos,VALUE_FROM_PERCENT( -0.12f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.13f, persent) + x_pos, VALUE_FROM_PERCENT(-0.07f, persent) + y_pos);
            }
            glEnd();

            glBegin(GL_QUADS); // part 4
            {
                glColor3f(0.5f, 0.2f, 0.0f);
                glVertex2f(VALUE_FROM_PERCENT(0.10f, persent) + x_pos, VALUE_FROM_PERCENT(-0.12f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.095f, persent) + x_pos,VALUE_FROM_PERCENT( -0.17f, persent) + y_pos);
                glColor3f(0.8f, 0.5f, 0.3f);
                glVertex2f(VALUE_FROM_PERCENT(0.15f, persent) + x_pos, VALUE_FROM_PERCENT(-0.17f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.135f, persent) + x_pos,VALUE_FROM_PERCENT( -0.12f, persent) + y_pos);
            }
            glEnd();

            glBegin(GL_QUADS); // part 5
            {
                glColor3f(0.5f, 0.2f, 0.0f);
                glVertex2f(VALUE_FROM_PERCENT(0.095f, persent) + x_pos,VALUE_FROM_PERCENT( -0.17f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.103f, persent) + x_pos,VALUE_FROM_PERCENT( -0.235f, persent) + y_pos);
                glColor3f(0.8f, 0.5f, 0.3f);
                glVertex2f(VALUE_FROM_PERCENT(0.143f, persent) + x_pos,VALUE_FROM_PERCENT( -0.235f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.15f, persent) + x_pos, VALUE_FROM_PERCENT(-0.17f, persent) + y_pos);
            }
            glEnd();

            glBegin(GL_QUADS); // part 6
            {
                glColor3f(0.5f, 0.2f, 0.0f);
                glVertex2f(VALUE_FROM_PERCENT(0.103f, persent) + x_pos,VALUE_FROM_PERCENT( -0.235f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.095f, persent) + x_pos,VALUE_FROM_PERCENT( -0.315f, persent) + y_pos);
                glColor3f(0.8f, 0.5f, 0.3f);
                glVertex2f(VALUE_FROM_PERCENT(0.143f, persent) + x_pos,VALUE_FROM_PERCENT( -0.315f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.143f, persent) + x_pos,VALUE_FROM_PERCENT( -0.235f, persent) + y_pos);
            }
            glEnd();

            glBegin(GL_QUADS); // part 7
            {
                glColor3f(0.5f, 0.2f, 0.0f);
                glVertex2f(VALUE_FROM_PERCENT(0.095f, persent) + x_pos,VALUE_FROM_PERCENT( -0.315f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.095f, persent) + x_pos,VALUE_FROM_PERCENT( -0.39f, persent) + y_pos);
                glColor3f(0.8f, 0.5f, 0.3f);
                glVertex2f(VALUE_FROM_PERCENT(0.143f, persent) + x_pos,VALUE_FROM_PERCENT( -0.39f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.143f, persent) + x_pos,VALUE_FROM_PERCENT( -0.315f, persent) + y_pos);
            }
            glEnd();

            glBegin(GL_QUADS); // part 8
            {
                glColor3f(0.5f, 0.2f, 0.0f);
                glVertex2f(VALUE_FROM_PERCENT(0.095f, persent) + x_pos,VALUE_FROM_PERCENT( -0.39f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.09f, persent) + x_pos, VALUE_FROM_PERCENT(-0.465f, persent) + y_pos);
                glColor3f(0.8f, 0.5f, 0.3f);
                glVertex2f(VALUE_FROM_PERCENT(0.15f, persent) + x_pos, VALUE_FROM_PERCENT(-0.465f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.143f, persent) + x_pos,VALUE_FROM_PERCENT( -0.39f, persent) + y_pos);
            }
            glEnd();


            /*
                Lines to display division between parts of stem
            */
            glColor3f(0.5f, 0.2f, 0.0f);
            glLineWidth(3.0f);
            {

                glBegin(GL_LINES); // Division 1
                {
                    glVertex2f(VALUE_FROM_PERCENT(0.10f, persent) + x_pos, VALUE_FROM_PERCENT(-0.03f, persent) + y_pos);
                    glVertex2f(VALUE_FROM_PERCENT(0.13f, persent) + x_pos, VALUE_FROM_PERCENT(-0.03f, persent) + y_pos);
                }
                glEnd();


                glBegin(GL_LINES); // Division 2
                {
                    glVertex2f(VALUE_FROM_PERCENT(0.10f, persent) + x_pos, VALUE_FROM_PERCENT(-0.07f, persent) + y_pos);
                    glVertex2f(VALUE_FROM_PERCENT(0.13f, persent) + x_pos, VALUE_FROM_PERCENT(-0.07f, persent) + y_pos);
                }
                glEnd();


                glBegin(GL_LINES); // Division 3
                {
                    glVertex2f(VALUE_FROM_PERCENT(0.10f, persent) + x_pos, VALUE_FROM_PERCENT(-0.12f, persent) + y_pos);
                    glVertex2f(VALUE_FROM_PERCENT(0.135f, persent) + x_pos,VALUE_FROM_PERCENT(-0.12f, persent) + y_pos);
                }
                glEnd();


                glBegin(GL_LINES); // Division 4
                {
                    glVertex2f(VALUE_FROM_PERCENT(0.095f, persent) + x_pos,VALUE_FROM_PERCENT( -0.17f, persent) + y_pos);
                    glVertex2f(VALUE_FROM_PERCENT(0.15f, persent) + x_pos, VALUE_FROM_PERCENT(-0.17f, persent) + y_pos);
                }
                glEnd();


                glBegin(GL_LINES); // Division 5
                {
                    glVertex2f(VALUE_FROM_PERCENT(0.103f, persent) + x_pos,VALUE_FROM_PERCENT( -0.235f, persent) + y_pos);
                    glVertex2f(VALUE_FROM_PERCENT(0.143f, persent) + x_pos,VALUE_FROM_PERCENT( -0.235f, persent) + y_pos);
                }
                glEnd();

                glBegin(GL_LINES); // Division 6
                {
                    glVertex2f(VALUE_FROM_PERCENT(0.095f, persent) + x_pos,VALUE_FROM_PERCENT( -0.315f, persent) + y_pos);
                    glVertex2f(VALUE_FROM_PERCENT(0.143f, persent) + x_pos,VALUE_FROM_PERCENT( -0.315f, persent) + y_pos);
                }
                glEnd();


                glBegin(GL_LINES); // Division 7
                {
                    glVertex2f(VALUE_FROM_PERCENT(0.095f, persent) + x_pos,VALUE_FROM_PERCENT( -0.39f, persent) + y_pos);
                    glVertex2f(VALUE_FROM_PERCENT(0.143f, persent) + x_pos,VALUE_FROM_PERCENT( -0.39f, persent) + y_pos);
                }
                glEnd();


                glBegin(GL_LINES); // Division 8
                {
                    glVertex2f(VALUE_FROM_PERCENT(0.09f, persent) + x_pos, VALUE_FROM_PERCENT(-0.465f, persent) + y_pos);
                    glVertex2f(VALUE_FROM_PERCENT(0.15f, persent) + x_pos, VALUE_FROM_PERCENT(-0.465f, persent) + y_pos);
                }
                glEnd();
            }


            glLineWidth(1.0f); // Back to Default Value
        }


        /*
            Leaves of a Coconut Tree
        */
        glColor3f(0.0f, 0.4f, 0.1f);
        {
            glBegin(GL_POLYGON); // Leaf 1
            {
                glVertex2f(VALUE_FROM_PERCENT(0.10f, persent) + x_pos, VALUE_FROM_PERCENT(0.01f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.0f , persent)+ x_pos,  VALUE_FROM_PERCENT(0.0f  , persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(-0.07f, persent) + x_pos,VALUE_FROM_PERCENT(-0.06f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(-0.01f, persent) + x_pos,VALUE_FROM_PERCENT(-0.06f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.01f, persent) + x_pos, VALUE_FROM_PERCENT(-0.03f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.02f, persent) + x_pos, VALUE_FROM_PERCENT(-0.06f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.06f, persent) + x_pos, VALUE_FROM_PERCENT(-0.05f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.06f, persent) + x_pos, VALUE_FROM_PERCENT(-0.01f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.08f, persent) + x_pos, VALUE_FROM_PERCENT(-0.03f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.10f, persent) + x_pos, VALUE_FROM_PERCENT(0.0f ,  persent) + y_pos);
            }
            glEnd();

            glBegin(GL_POLYGON); // Leaf 2
            {
                glVertex2f(VALUE_FROM_PERCENT(0.11f, persent) + x_pos, VALUE_FROM_PERCENT(0.01f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.04f, persent) + x_pos, VALUE_FROM_PERCENT(0.07f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.07f, persent) + x_pos, VALUE_FROM_PERCENT(0.08f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.01f, persent) + x_pos, VALUE_FROM_PERCENT(0.06f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.03f, persent) + x_pos, VALUE_FROM_PERCENT(0.09f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.01f, persent) + x_pos, VALUE_FROM_PERCENT(0.14f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.04f, persent) + x_pos, VALUE_FROM_PERCENT(0.15f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.01f, persent) + x_pos, VALUE_FROM_PERCENT(0.16f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.0f , persent) + x_pos,  VALUE_FROM_PERCENT(0.21f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.07f, persent) + x_pos, VALUE_FROM_PERCENT(0.19f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.07f, persent) + x_pos, VALUE_FROM_PERCENT(0.15f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.09f, persent) + x_pos, VALUE_FROM_PERCENT(0.17f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.10f, persent) + x_pos, VALUE_FROM_PERCENT(0.14f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.10f, persent) + x_pos, VALUE_FROM_PERCENT(0.09f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.12f, persent) + x_pos, VALUE_FROM_PERCENT(0.11f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.12f, persent) + x_pos, VALUE_FROM_PERCENT(0.02f , persent)+ y_pos);
            }
            glEnd();

            glBegin(GL_POLYGON); // Leaf 3
            {
                glVertex2f(VALUE_FROM_PERCENT(0.11f, persent) + x_pos, VALUE_FROM_PERCENT(0.04f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.20f, persent) + x_pos, VALUE_FROM_PERCENT(0.13f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.29f, persent) + x_pos, VALUE_FROM_PERCENT(0.12f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.24f, persent) + x_pos, VALUE_FROM_PERCENT(0.09f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.21f, persent) + x_pos, VALUE_FROM_PERCENT(0.11f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.20f, persent) + x_pos, VALUE_FROM_PERCENT(0.08f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.18f, persent) + x_pos, VALUE_FROM_PERCENT(0.06f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.16f, persent) + x_pos, VALUE_FROM_PERCENT(0.06f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.16f, persent) + x_pos, VALUE_FROM_PERCENT(0.04f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.14f, persent) + x_pos, VALUE_FROM_PERCENT(0.03f , persent)+ y_pos);
            }
            glEnd();

        glBegin(GL_POLYGON); // Leaf 4
            {
                glVertex2f(VALUE_FROM_PERCENT(0.13f, persent) + x_pos, VALUE_FROM_PERCENT(0.04f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.25f, persent) + x_pos, VALUE_FROM_PERCENT(0.01f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.29f, persent) + x_pos, VALUE_FROM_PERCENT(-0.09f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.24f, persent) + x_pos, VALUE_FROM_PERCENT(-0.07f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.22f, persent) + x_pos, VALUE_FROM_PERCENT(-0.03f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.18f, persent) + x_pos, VALUE_FROM_PERCENT(-0.04f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.14f, persent) + x_pos, VALUE_FROM_PERCENT(-0.01f, persent) + y_pos);
            }
            glEnd();
        }

        /*
            Coconut on Straight coconut Tree
        */
        glColor3f(0.4f, 0.1f, 0.0f);
        {
            glEnable(GL_POINT_SMOOTH);
            glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
            glPointSize(25.0f);

            glBegin(GL_POINTS); // Coconut 1
            {
                glVertex2f(VALUE_FROM_PERCENT(0.10f, persent) + x_pos, VALUE_FROM_PERCENT(-0.02f , persent)+ y_pos);
            }
            glEnd();


            glBegin(GL_POINTS); // Coconut 2
            {
                glVertex2f(VALUE_FROM_PERCENT(0.13f, persent) + x_pos, VALUE_FROM_PERCENT(-0.02f , persent)+ y_pos);
            }
            glEnd();

            glPointSize(1.0f); // Back to Default Value
            glDisable(GL_POINT_SMOOTH); // Back to Default Style of Point
        }     
}

void DIVA_Omkar(float x_pos, float y_pos, float percent, float percent2)
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
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT(0.0f, percent2) + x_pos, VALUE_FROM_PERCENT(0.0f, percent2) + y_pos, 0.0f);

		glVertex3f(VALUE_FROM_PERCENT(-0.01875f, percent2) + x_pos, VALUE_FROM_PERCENT(0.075f, percent2) + y_pos, 0.0f);

		glVertex3f(VALUE_FROM_PERCENT(0.0f, percent2) + x_pos, VALUE_FROM_PERCENT(0.15f, percent2) + y_pos, 0.0f);

		glVertex3f(VALUE_FROM_PERCENT(0.01875f, percent2) + x_pos, VALUE_FROM_PERCENT(0.075f, percent2) + y_pos, 0.0f);
	}
	glEnd();

}
void zopdi_prashant(float x_pos, float y_pos, float percent)
{
	// Code
	glBegin(GL_QUADS);

	glColor3f(0.6f, 0.3f, 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(-0.8f,percent) + x_pos, VALUE_FROM_PERCENT( -0.3f,percent) + y_pos, 0.0f); // left
	glVertex3f(VALUE_FROM_PERCENT(-0.8f,percent) + x_pos, VALUE_FROM_PERCENT( -0.6f,percent) + y_pos, 0.0f); // bottom
	glVertex3f(VALUE_FROM_PERCENT(-0.4f,percent) + x_pos, VALUE_FROM_PERCENT( -0.6f,percent) + y_pos, 0.0f); // right
	glVertex3f(VALUE_FROM_PERCENT(-0.4f,percent) + x_pos, VALUE_FROM_PERCENT( -0.3f,percent) + y_pos, 0.0f); // top

    glColor3f(0.9f, 0.9f, 0.9f);
	glVertex3f(VALUE_FROM_PERCENT(-0.7f,percent) + x_pos, VALUE_FROM_PERCENT( -0.45f,percent) + y_pos, 0.0f); // left
	glVertex3f(VALUE_FROM_PERCENT(-0.7f,percent) + x_pos, VALUE_FROM_PERCENT( -0.6f,percent) + y_pos, 0.0f); // bottom
	glVertex3f(VALUE_FROM_PERCENT(-0.6f,percent) + x_pos, VALUE_FROM_PERCENT( -0.6f,percent) + y_pos, 0.0f); // right
	glVertex3f(VALUE_FROM_PERCENT(-0.6f,percent) + x_pos, VALUE_FROM_PERCENT( -0.45f,percent) + y_pos, 0.0f); // top

	glVertex3f(VALUE_FROM_PERCENT(-0.55f,percent) + x_pos, VALUE_FROM_PERCENT( -0.4f,percent) + y_pos, 0.0f); // left
	glVertex3f(VALUE_FROM_PERCENT(-0.55f,percent) + x_pos, VALUE_FROM_PERCENT( -0.5f,percent) + y_pos, 0.0f); // bottom
	glVertex3f(VALUE_FROM_PERCENT(-0.45f,percent) + x_pos, VALUE_FROM_PERCENT( -0.5f,percent) + y_pos, 0.0f); // right
	glVertex3f(VALUE_FROM_PERCENT(-0.45f,percent) + x_pos, VALUE_FROM_PERCENT( -0.4f,percent) + y_pos, 0.0f); // top

	glEnd();

    glBegin(GL_LINES);

    glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(-0.5f,percent) + x_pos, VALUE_FROM_PERCENT( -0.4f,percent) + y_pos, 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(-0.5f,percent) + x_pos, VALUE_FROM_PERCENT( -0.5f,percent) + y_pos, 0.0f);
    
	glVertex3f(VALUE_FROM_PERCENT(-0.55f,percent) + x_pos, VALUE_FROM_PERCENT( -0.45f,percent) + y_pos, 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(-0.45f,percent) + x_pos, VALUE_FROM_PERCENT( -0.45f,percent) + y_pos, 0.0f);

    glColor3f(0.8f, 0.7f, 0.5f);
	glVertex3f(VALUE_FROM_PERCENT(-0.65f,percent) + x_pos, VALUE_FROM_PERCENT( -0.05f,percent) + y_pos, 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(-0.6f,percent) + x_pos, VALUE_FROM_PERCENT( -0.1f,percent) + y_pos, 0.0f);

	glVertex3f(VALUE_FROM_PERCENT(-0.6f,percent) + x_pos, VALUE_FROM_PERCENT( -0.05f,percent) + y_pos, 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(-0.6f,percent) + x_pos, VALUE_FROM_PERCENT( -0.1f,percent) + y_pos, 0.0f);

	glVertex3f(VALUE_FROM_PERCENT(-0.55f,percent) + x_pos, VALUE_FROM_PERCENT( -0.05f,percent) + y_pos, 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(-0.6f,percent) + x_pos, VALUE_FROM_PERCENT( -0.1f,percent) + y_pos, 0.0f);

    glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(-0.65f,percent) + x_pos, VALUE_FROM_PERCENT( -0.15f,percent) + y_pos, 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(-0.63f,percent) + x_pos, VALUE_FROM_PERCENT( -0.25f,percent) + y_pos, 0.0f);

    glEnd();

    glBegin(GL_TRIANGLES);
	
    glColor3f(0.8f, 0.7f, 0.5f);
	glVertex3f(VALUE_FROM_PERCENT(-0.75f,percent) + x_pos, VALUE_FROM_PERCENT( -0.3f,percent) + y_pos, 0.0f); //center
	glVertex3f(VALUE_FROM_PERCENT(-0.6f,percent) + x_pos, VALUE_FROM_PERCENT( -0.1f,percent) + y_pos, 0.0f); // right
	glVertex3f(VALUE_FROM_PERCENT(-0.85f,percent) + x_pos, VALUE_FROM_PERCENT( -0.35f,percent) + y_pos, 0.0f); //left

	glVertex3f(VALUE_FROM_PERCENT(-0.75f,percent) + x_pos, VALUE_FROM_PERCENT( -0.35f,percent) + y_pos, 0.0f); //center
	glVertex3f(VALUE_FROM_PERCENT(-0.6f,percent) + x_pos, VALUE_FROM_PERCENT( -0.1f,percent) + y_pos, 0.0f); // right
	glVertex3f(VALUE_FROM_PERCENT(-0.75f,percent) + x_pos, VALUE_FROM_PERCENT( -0.3f,percent) + y_pos, 0.0f); //left

	glVertex3f(VALUE_FROM_PERCENT(-0.7f,percent) + x_pos, VALUE_FROM_PERCENT( -0.35f,percent) + y_pos, 0.0f); //center
	glVertex3f(VALUE_FROM_PERCENT(-0.6f,percent) + x_pos, VALUE_FROM_PERCENT( -0.1f,percent) + y_pos, 0.0f); // right
	glVertex3f(VALUE_FROM_PERCENT(-0.73f,percent) + x_pos, VALUE_FROM_PERCENT( -0.3f,percent) + y_pos, 0.0f); //left

	glVertex3f(VALUE_FROM_PERCENT(-0.6f,percent) + x_pos, VALUE_FROM_PERCENT( -0.35f,percent) + y_pos, 0.0f); //center
	glVertex3f(VALUE_FROM_PERCENT(-0.6f,percent) + x_pos, VALUE_FROM_PERCENT( -0.1f,percent) + y_pos, 0.0f); // right
	glVertex3f(VALUE_FROM_PERCENT(-0.7f,percent) + x_pos, VALUE_FROM_PERCENT( -0.3f,percent) + y_pos, 0.0f); //left

	glVertex3f(VALUE_FROM_PERCENT(-0.55f,percent) + x_pos, VALUE_FROM_PERCENT( -0.35f,percent) + y_pos, 0.0f); //center
	glVertex3f(VALUE_FROM_PERCENT(-0.6f,percent) + x_pos, VALUE_FROM_PERCENT( -0.1f,percent) + y_pos, 0.0f); // right
	glVertex3f(VALUE_FROM_PERCENT(-0.6f,percent) + x_pos, VALUE_FROM_PERCENT( -0.3f,percent) + y_pos, 0.0f); //left

	glVertex3f(VALUE_FROM_PERCENT(-0.45f,percent) + x_pos, VALUE_FROM_PERCENT( -0.35f,percent) + y_pos, 0.0f); //center
	glVertex3f(VALUE_FROM_PERCENT(-0.6f,percent) + x_pos, VALUE_FROM_PERCENT( -0.1f,percent) + y_pos, 0.0f); // right
	glVertex3f(VALUE_FROM_PERCENT(-0.57f,percent) + x_pos, VALUE_FROM_PERCENT( -0.3f,percent) + y_pos, 0.0f); //left

	glVertex3f(VALUE_FROM_PERCENT(-0.45f,percent) + x_pos, VALUE_FROM_PERCENT( -0.3f,percent) + y_pos, 0.0f); //center
	glVertex3f(VALUE_FROM_PERCENT(-0.6f,percent) + x_pos, VALUE_FROM_PERCENT( -0.1f,percent) + y_pos, 0.0f); // right
	glVertex3f(VALUE_FROM_PERCENT(-0.45f,percent) + x_pos, VALUE_FROM_PERCENT( -0.35f,percent) + y_pos, 0.0f); //left

	glVertex3f(VALUE_FROM_PERCENT(-0.35f,percent) + x_pos, VALUE_FROM_PERCENT( -0.35f,percent) + y_pos, 0.0f); //center
	glVertex3f(VALUE_FROM_PERCENT(-0.6f,percent) + x_pos, VALUE_FROM_PERCENT( -0.1f,percent) + y_pos, 0.0f); // right
	glVertex3f(VALUE_FROM_PERCENT(-0.45f,percent) + x_pos, VALUE_FROM_PERCENT( -0.3f,percent) + y_pos, 0.0f); //left

    glEnd();

    glBegin(GL_LINES);

    glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(-0.6f,percent) + x_pos, VALUE_FROM_PERCENT( -0.15f,percent) + y_pos, 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(-0.7f,percent) + x_pos, VALUE_FROM_PERCENT( -0.25f,percent) + y_pos, 0.0f);

	glVertex3f(VALUE_FROM_PERCENT(-0.6f,percent) + x_pos, VALUE_FROM_PERCENT( -0.2f,percent) + y_pos, 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(-0.6f,percent) + x_pos, VALUE_FROM_PERCENT( -0.28f,percent) + y_pos, 0.0f);

	glVertex3f(VALUE_FROM_PERCENT(-0.58f,percent) + x_pos, VALUE_FROM_PERCENT( -0.15f,percent) + y_pos, 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(-0.5f,percent) + x_pos, VALUE_FROM_PERCENT( -0.25f,percent) + y_pos, 0.0f);

    glEnd();
}

void TiltedCoconutTree_Atharv(float x_pos, float y_pos, int persent)
{   
        /*
            Stem of Tilted Coconut Tree
        */
        {
            glBegin(GL_QUADS); // Part 1
            {
                glColor3f(0.5f, 0.2f, 0.0f);
                glVertex2f(VALUE_FROM_PERCENT(0.44f, persent) + x_pos, VALUE_FROM_PERCENT(-0.13f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.41f, persent) + x_pos, VALUE_FROM_PERCENT(-0.19f, persent) + y_pos);
                glColor3f(0.8f, 0.5f, 0.3f);
                glVertex2f(VALUE_FROM_PERCENT(0.45f, persent) + x_pos, VALUE_FROM_PERCENT(-0.20f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.46f, persent) + x_pos, VALUE_FROM_PERCENT(-0.15f, persent) + y_pos);
            }
            glEnd();

             glBegin(GL_QUADS); // Part 2
            {
                glColor3f(0.5f, 0.2f, 0.0f);
                glVertex2f(VALUE_FROM_PERCENT(0.41f, persent) + x_pos, VALUE_FROM_PERCENT(-0.19f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.39f, persent) + x_pos, VALUE_FROM_PERCENT(-0.24f, persent) + y_pos);
                glColor3f(0.8f, 0.5f, 0.3f);
                glVertex2f(VALUE_FROM_PERCENT(0.44f, persent) + x_pos, VALUE_FROM_PERCENT(-0.26f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.45f, persent) + x_pos, VALUE_FROM_PERCENT(-0.20f, persent) + y_pos);
            }
            glEnd();

            glBegin(GL_QUADS); // Part 3
            {
                glColor3f(0.5f, 0.2f, 0.0f);
                glVertex2f(VALUE_FROM_PERCENT(0.39f, persent) + x_pos, VALUE_FROM_PERCENT(-0.24f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.37f, persent) + x_pos, VALUE_FROM_PERCENT(-0.32f, persent) + y_pos);
                glColor3f(0.8f, 0.5f, 0.3f);
                glVertex2f(VALUE_FROM_PERCENT(0.43f, persent) + x_pos, VALUE_FROM_PERCENT(-0.34f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.44f, persent) + x_pos, VALUE_FROM_PERCENT(-0.26f, persent) + y_pos);
            }
            glEnd();

            glBegin(GL_QUADS); // Part 4
            {
                glColor3f(0.5f, 0.2f, 0.0f);
                glVertex2f(VALUE_FROM_PERCENT(0.37f, persent) + x_pos, VALUE_FROM_PERCENT(-0.32f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.33f, persent) + x_pos, VALUE_FROM_PERCENT(-0.39f, persent) + y_pos);
                glColor3f(0.8f, 0.5f, 0.3f);
                glVertex2f(VALUE_FROM_PERCENT(0.43f, persent) + x_pos, VALUE_FROM_PERCENT(-0.41f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.43f, persent) + x_pos, VALUE_FROM_PERCENT(-0.34f, persent) + y_pos);
            }
            glEnd();

            glBegin(GL_QUADS); // Part 5
            {
                glColor3f(0.5f, 0.2f, 0.0f);
                glVertex2f(VALUE_FROM_PERCENT(0.33f, persent) + x_pos, VALUE_FROM_PERCENT(-0.39f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.33f, persent) + x_pos, VALUE_FROM_PERCENT(-0.46f, persent) + y_pos);
                glColor3f(0.8f, 0.5f, 0.3f);
                glVertex2f(VALUE_FROM_PERCENT(0.42f, persent) + x_pos, VALUE_FROM_PERCENT(-0.46f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.43f, persent) + x_pos, VALUE_FROM_PERCENT(-0.41f, persent) + y_pos);
            }
            glEnd();

            glBegin(GL_QUADS); // Part 6
            {
                glColor3f(0.5f, 0.2f, 0.0f);
                glVertex2f(VALUE_FROM_PERCENT(0.33f, persent) + x_pos, VALUE_FROM_PERCENT(-0.46f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.32f, persent) + x_pos, VALUE_FROM_PERCENT(-0.55f, persent) + y_pos);
                glColor3f(0.8f, 0.5f, 0.3f);
                glVertex2f(VALUE_FROM_PERCENT(0.43f, persent) + x_pos, VALUE_FROM_PERCENT(-0.55f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.42f, persent) + x_pos, VALUE_FROM_PERCENT(-0.46f, persent) + y_pos);
            }
            glEnd();


            /*
                Lines to display divsion between parts of stem
            */
            glColor3f(0.5f, 0.2f, 0.0f);
            glLineWidth(3.0f);
            {
                glBegin(GL_LINES); // Division 1
                {
                    glVertex2f(VALUE_FROM_PERCENT(0.41f, persent) + x_pos, VALUE_FROM_PERCENT(-0.19f, persent) + y_pos);
                    glVertex2f(VALUE_FROM_PERCENT(0.45f, persent) + x_pos, VALUE_FROM_PERCENT(-0.20f, persent) + y_pos);
                }
                glEnd();


                glBegin(GL_LINES); // Division 2
                {
                    glVertex2f(VALUE_FROM_PERCENT(0.39f, persent) + x_pos, VALUE_FROM_PERCENT(-0.24f, persent) + y_pos);
                    glVertex2f(VALUE_FROM_PERCENT(0.44f, persent) + x_pos, VALUE_FROM_PERCENT(-0.26f, persent) + y_pos);
                }
                glEnd();


                glBegin(GL_LINES); // Division 3
                {
                    glVertex2f(VALUE_FROM_PERCENT(0.37f, persent) + x_pos, VALUE_FROM_PERCENT(-0.32f, persent) + y_pos);
                    glVertex2f(VALUE_FROM_PERCENT(0.43f, persent) + x_pos, VALUE_FROM_PERCENT(-0.34f, persent) + y_pos);
                }
                glEnd();


                glBegin(GL_LINES); // Division 4
                {
                    glVertex2f(VALUE_FROM_PERCENT(0.33f, persent) + x_pos, VALUE_FROM_PERCENT(-0.39f, persent) + y_pos);
                    glVertex2f(VALUE_FROM_PERCENT(0.43f, persent) + x_pos, VALUE_FROM_PERCENT(-0.41f, persent) + y_pos);
                }
                glEnd();


                glBegin(GL_LINES); // Division 5
                {
                    glVertex2f(VALUE_FROM_PERCENT(0.33f, persent) + x_pos, VALUE_FROM_PERCENT(-0.46f, persent) + y_pos);
                    glVertex2f(VALUE_FROM_PERCENT(0.42f, persent) + x_pos, VALUE_FROM_PERCENT(-0.46f, persent) + y_pos);
                }
                glEnd();


                glBegin(GL_LINES); // Division 6
                {
                    glVertex2f(VALUE_FROM_PERCENT(0.32f, persent) + x_pos, VALUE_FROM_PERCENT(-0.55f, persent) + y_pos);
                    glVertex2f(VALUE_FROM_PERCENT(0.43f, persent) + x_pos, VALUE_FROM_PERCENT(-0.55f, persent) + y_pos);
                }
                glEnd();
            }
        }


        /*
            Leaves of Tilted Coconut Tree
        */
        glColor3f(0.0f, 0.4f, 0.1f);
        {
            glBegin(GL_POLYGON); // Leaf 1
            {
                glVertex2f(VALUE_FROM_PERCENT(0.43f, persent) + x_pos, VALUE_FROM_PERCENT(-0.12f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.33f, persent) + x_pos, VALUE_FROM_PERCENT(-0.13f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.26f, persent) + x_pos, VALUE_FROM_PERCENT(-0.19f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.32f, persent) + x_pos, VALUE_FROM_PERCENT(-0.19f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.31f, persent) + x_pos, VALUE_FROM_PERCENT(-0.16f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.35f, persent) + x_pos, VALUE_FROM_PERCENT(-0.18f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.39f, persent) + x_pos, VALUE_FROM_PERCENT(-0.18f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.39f, persent) + x_pos, VALUE_FROM_PERCENT(-0.15f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.41f, persent) + x_pos, VALUE_FROM_PERCENT(-0.16f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.43f, persent) + x_pos, VALUE_FROM_PERCENT(-0.13f, persent) + y_pos);
            }
            glEnd();


            glBegin(GL_POLYGON); // Leaf 2
            {
                glVertex2f(VALUE_FROM_PERCENT(0.45f, persent) + x_pos, VALUE_FROM_PERCENT(-0.12f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.38f, persent) + x_pos, VALUE_FROM_PERCENT(-0.06f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.41f, persent) + x_pos, VALUE_FROM_PERCENT(-0.05f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.37f, persent) + x_pos, VALUE_FROM_PERCENT(-0.04f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.35f, persent) + x_pos, VALUE_FROM_PERCENT(0.01f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.38f, persent) + x_pos, VALUE_FROM_PERCENT(0.01f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.34f, persent) + x_pos, VALUE_FROM_PERCENT(0.03f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.34f, persent) + x_pos, VALUE_FROM_PERCENT(0.08f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.41f, persent) + x_pos, VALUE_FROM_PERCENT(0.06f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.41f, persent) + x_pos, VALUE_FROM_PERCENT(0.02f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.43f, persent) + x_pos, VALUE_FROM_PERCENT(0.04f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.44f, persent) + x_pos, VALUE_FROM_PERCENT(0.01f , persent)+ y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.44f, persent) + x_pos, VALUE_FROM_PERCENT(-0.04f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.46f, persent) + x_pos, VALUE_FROM_PERCENT(-0.02f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.46f, persent) + x_pos, VALUE_FROM_PERCENT(-0.11f, persent) + y_pos);
            }
            glEnd();


             glBegin(GL_POLYGON); // Leaf 3
            {
                glVertex2f(VALUE_FROM_PERCENT(0.47f, persent) + x_pos, VALUE_FROM_PERCENT(-0.13f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.52f, persent) + x_pos, VALUE_FROM_PERCENT(-0.05f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.53f, persent) + x_pos, VALUE_FROM_PERCENT(-0.08f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.55f, persent) + x_pos, VALUE_FROM_PERCENT(-0.03f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.57f, persent) + x_pos, VALUE_FROM_PERCENT(-0.01f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.59f, persent) + x_pos, VALUE_FROM_PERCENT(-0.04f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.60f, persent) + x_pos, VALUE_FROM_PERCENT(0.0f , persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.67f, persent) + x_pos, VALUE_FROM_PERCENT(-0.02f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.64f, persent) + x_pos, VALUE_FROM_PERCENT(-0.06f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.61f, persent) + x_pos, VALUE_FROM_PERCENT(-0.05f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.62f, persent) + x_pos, VALUE_FROM_PERCENT(-0.08f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.59f, persent) + x_pos, VALUE_FROM_PERCENT(-0.11f , persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.54f, persent) + x_pos, VALUE_FROM_PERCENT(-0.09f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.55f, persent) + x_pos, VALUE_FROM_PERCENT(-0.125, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.48f, persent) + x_pos, VALUE_FROM_PERCENT(-0.14f, persent) + y_pos);
            }
            glEnd();


            glBegin(GL_POLYGON); // Leaf 4
            {
                glVertex2f(VALUE_FROM_PERCENT(0.475f, persent) + x_pos,VALUE_FROM_PERCENT(-0.15f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.56f, persent) + x_pos, VALUE_FROM_PERCENT(-0.21f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.59f, persent) + x_pos, VALUE_FROM_PERCENT(-0.30f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.54f, persent) + x_pos, VALUE_FROM_PERCENT(-0.27f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.54f, persent) + x_pos, VALUE_FROM_PERCENT(-0.23f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.51f, persent) + x_pos, VALUE_FROM_PERCENT(-0.25f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.48f, persent) + x_pos, VALUE_FROM_PERCENT(-0.22f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.50f, persent) + x_pos, VALUE_FROM_PERCENT(-0.19f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.47f, persent) + x_pos, VALUE_FROM_PERCENT(-0.19f, persent) + y_pos);
                glVertex2f(VALUE_FROM_PERCENT(0.47f, persent) + x_pos, VALUE_FROM_PERCENT(-0.16f, persent) + y_pos);
            }
            glEnd();
        }


        /*
            Coconut on Coconut Tree
        */
        glColor3f(0.4f, 0.1f, 0.0f); 
        {
            glEnable(GL_POINT_SMOOTH);
            glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
            glPointSize(25.0f);

            glBegin(GL_POINTS); // Coconut 1
            {
                glVertex2f(VALUE_FROM_PERCENT(0.45f, persent) + x_pos, VALUE_FROM_PERCENT(-0.15f, persent) + y_pos);
            }
            glEnd();


            glBegin(GL_POINTS); // Coconut 2
            {
                glVertex2f(VALUE_FROM_PERCENT(0.42f, persent) + x_pos, VALUE_FROM_PERCENT(-0.15f, persent) + y_pos);
            }
            glEnd();


            glBegin(GL_POINTS); // Coconut 3
            {
                glVertex2f(VALUE_FROM_PERCENT(0.48f, persent) + x_pos, VALUE_FROM_PERCENT(-0.17f, persent) + y_pos);
            }
            glEnd();

            glPointSize(1.0f); // Back to Default Value
            glDisable(GL_POINT_SMOOTH); // Back to Default Style of Point
        }
}




void Birds_Amol(float x_pos, float y_pos)
{
    //******************** Draw Bird *****************************************************

    //Bird Shape 1/2 feather
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);  //
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
    glColor3f(1.0f, 1.0f, 1.0f);  // 
    glVertex2f(0.55f + x_pos, 0.57f + y_pos);  // 
    glVertex2f(0.55f + x_pos, 0.59f + y_pos);
    //glColor3f(-0.36f, 0.58f, 0.0f);
    glVertex2f(0.60f + x_pos, 0.56f + y_pos);
    glVertex2f(0.61f + x_pos, 0.57f + y_pos);

    glEnd();

    //Bird Shape 2 beak
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 1.0f, 1.0f);;  // 
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
    glColor3f(1.0f, 1.0f, 1.0f);  // 
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
    glColor3f(1.0f, 1.0f, 1.0f);  // 
    glVertex2f(0.65f + x_pos, 0.57f + y_pos);  // 
    glVertex2f(0.65f + x_pos, 0.59f + y_pos);
    //glColor3f(-0.36f, 0.58f, 0.0f);
    glVertex2f(0.70f + x_pos, 0.56f + y_pos);
    glVertex2f(0.71f + x_pos, 0.57f + y_pos);

    glEnd();

    //Bird Shape 2 beak
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 1.0f, 1.0f);  // 
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


  // //Bird Shape 1
  //   glBegin(GL_TRIANGLES);
  //   glColor3f(0.6f, 0.4f, 0.6f);  // 
  //   glVertex2f(-0.4f + x_pos, 0.6f + y_pos);  // 
  //   glVertex2f(-0.37f + x_pos, 0.57f + y_pos);
  //   //glColor3f(-0.36f, 0.58f, 0.0f);
  //   glVertex2f(-0.36f + x_pos, 0.58f + y_pos);

  //   glEnd();


  //   glBegin(GL_TRIANGLES);
  //   glColor3f(0.6f, 0.4f, 0.6f);  // 
  //   glVertex2f(-0.3f + x_pos, 0.6f + y_pos);  // 
  //   glVertex2f(-0.37f + x_pos, 0.57f + y_pos);
  //   //glColor3f(-0.36f, 0.58f, 0.0f);
  //   glVertex2f(-0.36f + x_pos, 0.58f + y_pos);

  //   glEnd();


  //   // Bird Shape 2
  //   glBegin(GL_TRIANGLES);
  //   glColor3f(0.6f, 0.4f, 0.6f);  // 
  //   glVertex2f(-0.2f + x_pos, 0.6f + y_pos);  // 
  //   glVertex2f(-0.17f + x_pos, 0.57f + y_pos);
  //   //glColor3f(-0.36f, 0.58f, 0.0f);
  //   glVertex2f(-0.16f + x_pos, 0.58f + y_pos);
  //   glEnd();

  //   glBegin(GL_TRIANGLES);
  //   glColor3f(0.6f, 0.4f, 0.6f);  // 
  //   glVertex2f(-0.1f, 0.6f + y_pos);  // 
  //   glVertex2f(-0.17f, 0.57f + y_pos);
  //   //glColor3f(-0.36f, 0.58f, 0.0f);
  //   glVertex2f(-0.16f, 0.58f + y_pos);
  //   glEnd();

  //   ///****************************

  //  // Bird Shape 3
  //   glBegin(GL_TRIANGLES);
  //   glColor3f(0.6f, 0.4f, 0.6f);  // 
  //   glVertex2f(-0.2f + x_pos, 0.8f + y_pos);  // 
  //   glVertex2f(-0.17f + x_pos, 0.77f + y_pos);
  //   //glColor3f(-0.36f, 0.58f, 0.0f);
  //   glVertex2f(-0.16f + x_pos, 0.78f + y_pos);
  //   glEnd();

  //   glBegin(GL_TRIANGLES);
  //   glColor3f(0.6f, 0.4f, 0.6f);  // 
  //   glVertex2f(-0.1f + x_pos, 0.8f + y_pos);  // 
  //   glVertex2f(-0.17f + x_pos, 0.77f + y_pos);
  //   //glColor3f(-0.36f, 0.58f, 0.0f);
  //   glVertex2f(-0.16f + x_pos, 0.78f + y_pos);
  //   glEnd();



  //   //******************** Draw Bird *****************************************************

  //  //Bird Shape 1
  //   glBegin(GL_TRIANGLES);
  //   glColor3f(0.6f, 0.4f, 0.6f);  // 
  //   glVertex2f(0.4f + x_pos, 0.6f + y_pos);  // 
  //   glVertex2f(0.37f + x_pos, 0.57f + y_pos);
  //   //glColor3f(-0.36f, 0.58f, 0.0f);
  //   glVertex2f(0.36f + x_pos, 0.58f + y_pos);

  //   glEnd();


  //   glBegin(GL_TRIANGLES);
  //   glColor3f(0.6f, 0.4f, 0.6f);  // 
  //   glVertex2f(0.3f + x_pos, 0.6f + y_pos);  // 
  //   glVertex2f(0.37f + x_pos, 0.57f + y_pos);
  //   //glColor3f(-0.36f, 0.58f, 0.0f);
  //   glVertex2f(0.36f + x_pos, 0.58f + y_pos);

  //   glEnd();


  //   // Bird Shape 2
  //   glBegin(GL_TRIANGLES);
  //   glColor3f(0.6f, 0.4f, 0.6f);  // 
  //   glVertex2f(0.2f + x_pos, 0.6f + y_pos);  //
  //   glVertex2f(0.17f + x_pos, 0.57f + y_pos);
  //   //glColor3f(-0.36f, 0.58f, 0.0f);
  //   glVertex2f(0.16f + x_pos, 0.58f + y_pos);
  //   glEnd();

  //   glBegin(GL_TRIANGLES);
  //   glColor3f(0.6f, 0.4f, 0.6f);  // 
  //   glVertex2f(0.1f + x_pos, 0.6f + y_pos);  // 
  //   glVertex2f(0.17f + x_pos, 0.57f + y_pos);
  //   //glColor3f(-0.36f, 0.58f, 0.0f);
  //   glVertex2f(0.16f + x_pos, 0.58f + y_pos);
  //   glEnd();

  //   ///****************************

  //  // Bird Shape 3
  //   glBegin(GL_TRIANGLES);
  //   glColor3f(0.6f, 0.4f, 0.6f);  // 
  //   glVertex2f(0.2f + x_pos, 0.8f + y_pos);  // 
  //   glVertex2f(0.17f + x_pos, 0.77f + y_pos);
  //   //glColor3f(-0.36f, 0.58f, 0.0f);
  //   glVertex2f(0.16f + x_pos, 0.78f + y_pos);
  //   glEnd();

  //   glBegin(GL_TRIANGLES);
  //   glColor3f(0.6f, 0.4f, 0.6f);  // 
  //   glVertex2f(0.1f + x_pos, 0.8f + y_pos);  // 
  //   glVertex2f(0.17f + x_pos, 0.77f + y_pos);
  //   //glColor3f(-0.36f, 0.58f, 0.0f);
  //   glVertex2f(0.16f + x_pos, 0.78f + y_pos);
  //   glEnd();
}



void alphabet_T(float x_pos, float y_pos, float r, float g, float b, float percent)
{
	// Code
	const float width = 1.0f;
	const float height = GOLDEN_RATIO / width;

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

void Texture_Mayur(float x_pos, float y_pos, float r, float g, float b, float percent)
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
    glColor3f(0.8f, 0.9f, 1.0f);
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
    glColor3f(0.8f, 0.9f, 1.0f);
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
    glColor3f(0.8f, 0.9f, 1.0f);
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
    glColor3f(0.8f, 0.9f, 1.0f);
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
    glColor3f(0.8f, 0.9f, 1.0f);
    glVertex3f(0.58f+ x_pos, -0.89f+ y_pos, 0.0f);  // 12 quad
    glVertex3f(0.63f+ x_pos, -0.89f+ y_pos, 0.0f);
    glVertex3f(0.65f+ x_pos, -0.91f+ y_pos, 0.0f);
    glVertex3f(0.6f+ x_pos, -0.91f+ y_pos, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.4f, 0.1f);
    glVertex3f(0.47f+ x_pos, -0.85f+ y_pos, 0.0f);  // middle  quad
    glVertex3f(0.53f+ x_pos, -0.85f+ y_pos, 0.0f);
    glVertex3f(0.53f+ x_pos, -0.89f+ y_pos, 0.0f);
    glVertex3f(0.48f+ x_pos, -0.89f+ y_pos, 0.0f);
    glEnd();

}

void Grass_Mayur(float x_pos, float y_pos, float percent)
{
	// Code

	glBegin(GL_QUADS);
	{
		
		glColor3f(0.564706, 0.780392, 0.235294);
		glVertex2f(VALUE_FROM_PERCENT(-0.8f, percent), VALUE_FROM_PERCENT(0.4f, percent));

		glVertex2f(VALUE_FROM_PERCENT(0.8f, percent), VALUE_FROM_PERCENT(0.4f, percent));
		
		glColor3f(189.0f / 255.0f, 148.0f / 255.0f, 80.0f / 255.0f);
		glVertex2f(VALUE_FROM_PERCENT(0.8f, percent), VALUE_FROM_PERCENT(-0.7f, percent));

		glVertex2f(VALUE_FROM_PERCENT(-0.8f, percent), VALUE_FROM_PERCENT(-0.7f, percent));
	}
	glEnd();
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
	glVertex3f(0.52 + x_pos, -0.57f + y_pos, 0.0f);

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
	glVertex3f(0.2f + x_pos, 0.32f + y_pos, 0.0f);
	glColor3f(0.8f, 0.1f, 0.1f);
	glVertex3f(0.3f + x_pos, 0.32f + y_pos, 0.0f);
	glColor3f(0.8f, 0.1f, 0.1f);
	glVertex3f(0.2f + x_pos, 0.4f + y_pos, 0.0f);
	glColor3f(0.8f, 0.1f, 0.1f);
	glVertex3f(0.3f + x_pos, 0.4f + y_pos, 0.0f);
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

void Morning_Sky_Mayur(float x_pos, float y_pos, float percent)
{
	// Code

	glBegin(GL_QUADS);
	{
		glColor3f(	VALUE_FROM_PERCENT(255.0f / 255.0f, sky_color_factor), 
					VALUE_FROM_PERCENT(172.0f / 255.0f, sky_color_factor), 
					VALUE_FROM_PERCENT(28.0f / 255.0f, sky_color_factor));

		glVertex3f(VALUE_FROM_PERCENT(-1.0f, percent) + x_pos, VALUE_FROM_PERCENT(-0.2f, percent) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT(1.0f, percent) + x_pos, VALUE_FROM_PERCENT(-0.2f, percent) + y_pos, 0.0f);

		glColor3f(	VALUE_FROM_PERCENT(135.0f / 255.0f, sky_color_factor), 
					VALUE_FROM_PERCENT(206.0f / 255.0f, sky_color_factor), 
					VALUE_FROM_PERCENT(255.0f / 255.0f, sky_color_factor));
		
		glVertex3f(VALUE_FROM_PERCENT(1.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT(-1.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);
	}
	glEnd();
}


void Farming_Pankaj(float x_offset, float y_offset, float percent)
{
	void Grass_Pankaj(float x_offset, float y_offset, float percent);
	
	glLineWidth(3.0f);
	
	//Ground
	glBegin(GL_QUADS);
	{
	glColor3f(0.6f, 0.3f, 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(0.3f, percent) + x_offset, VALUE_FROM_PERCENT( 0.0f , percent) + y_offset, 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(0.7f, percent) + x_offset, VALUE_FROM_PERCENT( 0.0f , percent) + y_offset, 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(0.7f, percent) + x_offset, VALUE_FROM_PERCENT( 0.6f , percent) + y_offset, 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(0.3f, percent) + x_offset, VALUE_FROM_PERCENT( 0.6f , percent) + y_offset, 0.0f);

	}
	glEnd();
		
	
//1st Row	
Grass_Pankaj(VALUE_FROM_PERCENT(0.0f, percent) + x_offset, VALUE_FROM_PERCENT( 0.0f , percent) + y_offset, percent);
Grass_Pankaj(VALUE_FROM_PERCENT(0.10f, percent) + x_offset, VALUE_FROM_PERCENT( 0.0f , percent) + y_offset, percent);
Grass_Pankaj(VALUE_FROM_PERCENT(0.20f, percent) + x_offset, VALUE_FROM_PERCENT( 0.0f , percent) + y_offset, percent);
Grass_Pankaj(VALUE_FROM_PERCENT(0.30f, percent) + x_offset, VALUE_FROM_PERCENT( 0.0f , percent) + y_offset, percent);

//2nd Row	
Grass_Pankaj(VALUE_FROM_PERCENT(0.0f, percent) + x_offset, VALUE_FROM_PERCENT( -0.15f , percent) + y_offset, percent);
Grass_Pankaj(VALUE_FROM_PERCENT(0.10f, percent) + x_offset, VALUE_FROM_PERCENT( -0.15f , percent) + y_offset, percent);
Grass_Pankaj(VALUE_FROM_PERCENT(0.20f, percent) + x_offset, VALUE_FROM_PERCENT( -0.15f , percent) + y_offset, percent);
Grass_Pankaj(VALUE_FROM_PERCENT(0.30f, percent) + x_offset, VALUE_FROM_PERCENT( -0.15f , percent) + y_offset, percent);

//3rd Row
Grass_Pankaj(VALUE_FROM_PERCENT(0.0f, percent) + x_offset, VALUE_FROM_PERCENT( -0.30f , percent) + y_offset, percent);
Grass_Pankaj(VALUE_FROM_PERCENT(0.10f, percent) + x_offset, VALUE_FROM_PERCENT( -0.30f , percent) + y_offset, percent);
Grass_Pankaj(VALUE_FROM_PERCENT(0.20f, percent) + x_offset, VALUE_FROM_PERCENT( -0.30f , percent) + y_offset, percent);
Grass_Pankaj(VALUE_FROM_PERCENT(0.30f, percent) + x_offset, VALUE_FROM_PERCENT( -0.30f , percent) + y_offset, percent);


//4th Row
Grass_Pankaj(VALUE_FROM_PERCENT(0.0f, percent) + x_offset, VALUE_FROM_PERCENT( -0.45f , percent) + y_offset, percent);
Grass_Pankaj(VALUE_FROM_PERCENT(0.10f, percent) + x_offset, VALUE_FROM_PERCENT( -0.45f , percent) + y_offset, percent);
Grass_Pankaj(VALUE_FROM_PERCENT(0.20f, percent) + x_offset, VALUE_FROM_PERCENT( -0.45f , percent) + y_offset, percent);
Grass_Pankaj(VALUE_FROM_PERCENT(0.30f, percent) + x_offset, VALUE_FROM_PERCENT( -0.45f , percent) + y_offset, percent);



//First Line
glBegin(GL_LINES);
{
glColor3f(0.5f, 0.1f, 0.1f);
glVertex3f(VALUE_FROM_PERCENT(0.3f, percent) + x_offset, VALUE_FROM_PERCENT( 0.5f , percent) + y_offset, 0.0f);
glVertex3f(VALUE_FROM_PERCENT(0.7f, percent) + x_offset, VALUE_FROM_PERCENT( 0.5f , percent) + y_offset, 0.0f);

}
glEnd();

//Second Line
glBegin(GL_LINES);
{
glColor3f(0.5f, 0.1f, 0.1f);
glVertex3f(VALUE_FROM_PERCENT(0.3f, percent) + x_offset, VALUE_FROM_PERCENT( 0.35f , percent) + y_offset, 0.0f);
glVertex3f(VALUE_FROM_PERCENT(0.7f, percent) + x_offset, VALUE_FROM_PERCENT( 0.35f , percent) + y_offset, 0.0f);

}
glEnd();

//Third Line
glBegin(GL_LINES);
{
glColor3f(0.5f, 0.1f, 0.1f);
glVertex3f(VALUE_FROM_PERCENT(0.3f, percent) + x_offset, VALUE_FROM_PERCENT( 0.2f , percent) + y_offset, 0.0f);
glVertex3f(VALUE_FROM_PERCENT(0.7f, percent) + x_offset, VALUE_FROM_PERCENT( 0.2f , percent) + y_offset, 0.0f);

}
glEnd();


//Forth Line
glBegin(GL_LINES);
{
glColor3f(0.5f, 0.1f, 0.1f);
glVertex3f(VALUE_FROM_PERCENT(0.3f, percent) + x_offset, VALUE_FROM_PERCENT(0.04f , percent) + y_offset, 0.0f);
glVertex3f(VALUE_FROM_PERCENT(0.7f, percent) + x_offset, VALUE_FROM_PERCENT( 0.04f , percent) + y_offset, 0.0f);

}
glEnd();

	glLineWidth(1.0f);
}


void Grass_Pankaj(float x_offset, float y_offset, float percent)
{
	//First Line
	glBegin(GL_LINES);
	{
	glColor3f(0.6f,1.0f, 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(0.35f, percent) + x_offset, VALUE_FROM_PERCENT( 0.5f , percent) + y_offset, 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(0.32f, percent) + x_offset, VALUE_FROM_PERCENT( 0.6f , percent) + y_offset, 0.0f);

	}
	glEnd();
	
	//Second Line
	glBegin(GL_LINES);
	{
	glColor3f(0.6f, 1.0f, 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(0.35f, percent) + x_offset, VALUE_FROM_PERCENT( 0.5f , percent) + y_offset, 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(0.35f, percent) + x_offset, VALUE_FROM_PERCENT( 0.6f , percent) + y_offset, 0.0f);
}
	glEnd();

	//Third Line
	glBegin(GL_LINES);
	{
	glColor3f(0.6f, 1.0f, 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(0.35f, percent) + x_offset, VALUE_FROM_PERCENT( 0.5f , percent) + y_offset, 0.0f);
	glVertex3f(VALUE_FROM_PERCENT(0.38f, percent) + x_offset, VALUE_FROM_PERCENT( 0.6f , percent) + y_offset, 0.0f);

	}
	glEnd();
			
}

void FlowerPot_Shivkumar(float x_pos, float y_pos)
{
	//Perfect Pot with Quads
	glBegin(GL_QUADS);

	glColor3f(0.5f, 0.35f, 0.05f);
	glVertex2f(-0.02+x_pos, -0.08+y_pos);

	glColor3f(0.5f, 0.35f, 0.05f);
	glVertex2f(-0.06+x_pos, 0.09+y_pos);

	glColor3f(0.5f, 0.35f, 0.05f);
	glVertex2f(0.06 + x_pos, 0.09 + y_pos);

	glColor3f(0.5f, 0.35f, 0.05f);
	glVertex2f(0.02 + x_pos, -0.08+ y_pos);

	glEnd();

	glBegin(GL_LINES);

	// Trying Exact Middle Leaves
	glColor3f(0.0f, 0.4f, 0.1f);
	glVertex3f(0.03f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(0.04f + x_pos, 0.15f + y_pos, 0.0f);



	glVertex3f(0.03f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(0.02f + x_pos, 0.15f + y_pos, 0.0f);


	glVertex3f(0.03f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(0.01f + x_pos, 0.15f + y_pos, 0.0f);


	glVertex3f(0.03f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(0.01f + x_pos, 0.15f + y_pos, 0.0f);


	glVertex3f(0.03f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(0.05f + x_pos, 0.15f + y_pos, 0.0f);


	glVertex3f(0.03f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(0.06f + x_pos, 0.15f + y_pos, 0.0f);


	glVertex3f(0.03f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(0.07f + x_pos, 0.15f + y_pos, 0.0f);


	glVertex3f(0.03f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(0.08f + x_pos, 0.15f + y_pos, 0.0f);


	glVertex3f(0.03f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(0.09f + x_pos, 0.15f + y_pos, 0.0f);





	glVertex3f(0.01f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(0.01f + x_pos, 0.15f + y_pos, 0.0f);


	glVertex3f(0.01f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(0.05f + x_pos, 0.15f + y_pos, 0.0f);


	glVertex3f(0.01f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(0.06f + x_pos, 0.15f + y_pos, 0.0f);


	glVertex3f(0.01f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(0.07f + x_pos, 0.15f + y_pos, 0.0f);


	glVertex3f(0.01f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(0.08f + x_pos, 0.15f + y_pos, 0.0f);


	glVertex3f(0.01f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(0.09f + x_pos, 0.15f + y_pos, 0.0f);



	//Trying Middle Right Leaves


	glVertex3f(0.05f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(0.04f + x_pos, 0.15f + y_pos, 0.0f);


	glVertex3f(0.05f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(0.03f + x_pos, 0.15f+ y_pos, 0.0f);


	glVertex3f(0.05f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(0.02f + x_pos, 0.15f + y_pos, 0.0f);


	glVertex3f(0.05f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(0.01f + x_pos, 0.15f + y_pos, 0.0f);


	glVertex3f(0.05f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(0.05f + x_pos, 0.15f + y_pos, 0.0f);


	glVertex3f(0.05f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(0.06f + x_pos, 0.15f + y_pos, 0.0f);


	glVertex3f(0.05f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(0.07f + x_pos, 0.15f + y_pos, 0.0f);


	glVertex3f(0.05f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(0.08f + x_pos, 0.15f + y_pos, 0.0f);


	glVertex3f(0.05f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(0.09f + x_pos, 0.15f + y_pos, 0.0f);

	// Trying Middle Leaves


	glVertex3f(-0.04f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(-0.02f + x_pos, 0.15f + y_pos, 0.0f);


	glVertex3f(-0.04f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(-0.03f + x_pos, 0.15f + y_pos, 0.0f);


	glVertex3f(-0.04f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(-0.04f + x_pos, 0.15f + y_pos, 0.0f);


	glVertex3f(-0.04f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(-0.05f + x_pos, 0.15f + y_pos, 0.0f);


	glVertex3f(-0.04f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(-0.06f + x_pos, 0.15f + y_pos, 0.0f);


	glVertex3f(-0.04f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(-0.07f + x_pos, 0.15f + y_pos, 0.0f);


	glVertex3f(-0.04f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(-0.08f + x_pos, 0.15f + y_pos, 0.0f);


	glVertex3f(-0.04f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(-0.09f + x_pos, 0.15f + y_pos, 0.0f);


	glVertex3f(-0.04f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(-0.001f + x_pos, 0.15f + y_pos, 0.0f);



	glVertex3f(-0.04f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(-0.002f + x_pos, 0.15f + y_pos, 0.0f);



	glVertex3f(-0.04f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(-0.003f + x_pos, 0.15f + y_pos, 0.0f);


	glVertex3f(-0.04f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(-0.004f + x_pos, 0.15f + y_pos, 0.0f);



	glVertex3f(-0.04f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(-0.003f + x_pos, 0.15f + y_pos, 0.0f); // These above are middle right one leaves



	glVertex3f(-0.04f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(-0.005f + x_pos, 0.15f + y_pos, 0.0f);



	glVertex3f(-0.04f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(-0.007f + x_pos, 0.15f + y_pos, 0.0f);



	glVertex3f(-0.04f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(-0.008f + x_pos, 0.15f + y_pos, 0.0f);



	glVertex3f(-0.05f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(-0.01f + x_pos, 0.1f + y_pos, 0.0f);



	glVertex3f(-0.05f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(-0.02f + x_pos, 0.1f + y_pos, 0.0f);


	glVertex3f(-0.05f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(-0.04f + x_pos, 0.03f + y_pos, 0.0f);


	glVertex3f(-0.05f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(-0.04f + x_pos, 0.04f + y_pos, 0.0f);



	glVertex3f(-0.05f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(-0.04f + x_pos, 0.05f + y_pos, 0.0f);




	glVertex3f(-0.05f + x_pos, 0.09f + y_pos, 0.0f);



	glVertex3f(-0.04f + x_pos, 0.06f + y_pos, 0.0f);


	glVertex3f(-0.05f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(-0.04f + x_pos, 0.08f + y_pos, 0.0f);



	glVertex3f(-0.06f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(-0.1f + x_pos, 0.02f + y_pos, 0.0f);



	glVertex3f(-0.06f + x_pos, 0.09f + y_pos, 0.0f);


	glVertex3f(-0.1f + x_pos, 0.02f + y_pos, 0.0f);


	glVertex3f(-0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)

	glVertex3f(-0.1f + x_pos, 0.001f + y_pos, 0.0f);


	glVertex3f(-0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)

	glVertex3f(-0.1f + x_pos, 0.1f + y_pos, 0.0f);


	glVertex3f(-0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)

	glVertex3f(-0.1f + x_pos, 0.01f + y_pos, 0.0f);  ////  Seems Culprit


	glVertex3f(-0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)

	glVertex3f(-0.1f + x_pos, 0.02f + y_pos, 0.0f);


	glVertex3f(-0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)

	glVertex3f(-0.1f + x_pos, 0.03f + y_pos, 0.0f);



	glVertex3f(-0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)

	glVertex3f(-0.1f + x_pos, 0.04f + y_pos, 0.0f);




	glVertex3f(-0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)

	glVertex3f(-0.1f + x_pos, 0.05f + y_pos, 0.0f);


	glVertex3f(-0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)

	glVertex3f(-0.1f + x_pos, 0.06f + y_pos, 0.0f);




	glVertex3f(-0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)

	glVertex3f(-0.1f + x_pos, 0.07f + y_pos, 0.0f);




	glVertex3f(-0.06f + x_pos, 0.08f + y_pos, 0.0f);
	//Left(X,Y)

	glVertex3f(-0.1f + x_pos, 0.09f + y_pos, 0.0f);




	glVertex3f(-0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)

	glVertex3f(-0.1f + x_pos, 0.001f + y_pos, 0.0f);



	glVertex3f(-0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)

	glVertex3f(-0.1f + x_pos, 0.001f + y_pos, 0.0f);


	// RIGHT LEAVES


	glVertex3f(0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)

	glVertex3f(0.1f + x_pos, 0.01f + y_pos, 0.0f);



	glVertex3f(0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)

	glVertex3f(0.1f + x_pos, 0.1f + y_pos, 0.0f);


	glVertex3f(0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)

	glVertex3f(0.1f + x_pos, 0.02f + y_pos, 0.0f);  /// Seems Culprit


	glVertex3f(0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)

	glVertex3f(0.1f + x_pos, 0.02f + y_pos, 0.0f);


	glVertex3f(0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)

	glVertex3f(0.1f + x_pos, 0.03f + y_pos, 0.0f);



	glVertex3f(0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)

	glVertex3f(0.1f + x_pos, 0.04f + y_pos, 0.0f);




	glVertex3f(0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)

	glVertex3f(0.1f + x_pos, 0.05f + y_pos, 0.0f);


	glVertex3f(0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)

	glVertex3f(0.1f + x_pos, 0.06f + y_pos, 0.0f);




	glVertex3f(0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)

	glVertex3f(0.1f + x_pos, 0.07f + y_pos, 0.0f);




	glVertex3f(0.06f + x_pos, 0.08f + y_pos, 0.0f);
	//Left(X,Y)

	glVertex3f(0.1f + x_pos, 0.09f + y_pos, 0.0f);




	glVertex3f(0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)

	glVertex3f(0.1f + x_pos, 0.001f + y_pos, 0.0f);



	glVertex3f(0.06f + x_pos, 0.09f + y_pos, 0.0f);
	//Left(X,Y)

	glVertex3f(0.1f + x_pos, 0.001f + y_pos, 0.0f);


	glEnd();

}
