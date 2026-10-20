// header files
#include<windows.h>
#include<GL/freeglut.h>
#include <string.h>
#include <time.h>


#include "moon_Mayur.h"
#include "Prasad_stars.h"
#include "Swati_AstroMediComp.h"
#include "Swati_Texture.h"
#include "Amol_Boat.h"
#include "Pankaj_Mountains.h"
#include "Prashant_Fish.h"
#include "Gauri_Land_Starfish.h"
#include "TreasureBox_Adesh.h"
#include "Shivkumar_Happy.h"
#include "Nivrutti_Bubble.h"

#pragma comment(lib,"winmm.lib")

// global variable declarations
int Scene = 0;
BOOL bFullScreen = FALSE;
BOOL MoonMov = TRUE;
BOOL StarsShine = TRUE;
BOOL ScreenFade = TRUE;
BOOL AstroFade = TRUE;
BOOL MediFade = TRUE;
BOOL CompFade = TRUE;
BOOL TextFade = TRUE;
BOOL UresFade = TRUE;
BOOL MountainShine = TRUE;
BOOL RopeFade = TRUE;
BOOL BoatMove = TRUE;
BOOL FishMov = TRUE;
BOOL BubbleXMov = TRUE;
BOOL BubbleYMov = TRUE;
BOOL BubbleSize = TRUE;
BOOL BubbleTwoXMov = TRUE;
BOOL BubbleTwoYMov = TRUE;
BOOL BubbleTwoSize = TRUE;
BOOL TailMove = TRUE;
BOOL SceneUp = TRUE;
BOOL AgainBubbleXMov = TRUE;
BOOL AgainBubbleYMov = TRUE;
BOOL AgainBubbleSize = TRUE;
BOOL AgainBubbleTwoXMov = TRUE;
BOOL AgainBubbleTwoYMov = TRUE;
BOOL AgainBubbleTwoSize = TRUE;
BOOL TurtleFins = FALSE;
BOOL TurtlePos = TRUE;
BOOL ScreenFadeTwo = TRUE;
BOOL bNameBubble = TRUE;

// Group Member Name
float GroupMemberNameBubblexPos[13] = {0.0f};
char *GroupMembersName[13] = {"Mayur ", "Atharv", "Adesh ", "Omkar ", "Pankaj", "Swati ", "Prashant", "Nivrutti", "Shiv", "Amol ", "Prasad", "Gauri ", "Shradhha"};

float MoonPosUpdate = 0.0f;
float StarsShineFactor = 0.0f;
float ScreenFadeFactor = 0.0f;
float AstroFadeFactor = 0.0f;
float MediFadeFactor = 0.0f;
float CompFadeFactor = 0.0f;
float TextFadeFactor = 0.0f;
float UresFadeFactor = 0.0f;
float MountainShineUpdate = 0.0f;
float RopeFadeFactor = 1.0f;
float BoatRightUpdate = 1.0f;
float FishPosUpdate = 0.0f;
float BubbleXPosUpdate = 0.0f;
float BubbleYPosUpdate = 0.0f;
float BubbleSizeUpdate = 0.0f;
float BubbleTwoXPosUpdate = 0.0f;
float BubbleTwoYPosUpdate = 0.0f;
float BubbleTwoSizeUpdate = 0.0f;
float TailMoveUpdate = 0.0f;
float SceneUpUpdate = 0.0f;
float AgainBubbleXPosUpdate = 0.0f;
float AgainBubbleYPosUpdate = 0.0f;
float AgainBubbleSizeUpdate = 0.0f;
float AgainBubbleTwoXPosUpdate = 0.0f;
float AgainBubbleTwoYPosUpdate = 0.0f;
float AgainBubbleTwoSizeUpdate = 0.0f;
float TurtleFinsUpdate = 0.0f;
float TurtlePosUpdate = 0.0f;
float ScreenFadeFactorTwo = 0.0f;
float NameBubbleUpdate = 0.0f;
float WaveFactor = 0.0f;


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

	// Object Function declarations
	void DrawMoon_Mayur_Tadekar(float x_pos, float y_pos, float alpha, float percent_x, float percent_y);
	void DrawMoonReflection_Mayur_Tadekar(float x_pos, float y_pos, float alpha, float percent_x, float percent_y);
	void Prasad_Stars(float x_pos, float y_pos, float Shining_Factor);
	void Swati_astro(float x_pos, float y_pos, float percent, float FadeFactor);
	void Swati_medi(float x_pos, float y_pos, float percent, float FadeFactor);
	void Swati_comp(float x_pos, float y_pos, float percent, float FadeFactor);
	void Swati_text(float x_pos, float y_pos, float percent, float FadeFactor);
	void Swati_ure(float x_pos, float y_pos, float percent, float FadeFactor);
	void ScreenQuad(void);
	void Boat_Amol(float x_pos, float y_pos, float percent);
	void Bridge_Amol(float x_pos, float y_pos, float percent);
	void Rope_Amol(float x_pos, float y_pos, float percent, float FadeFactor);
	void WaterQuadOne(void);
	void WaterQuadTwo(void);
	void pankaj_mountainS(float x_pos, float y_pos, float percent, float Fadefactor);
	void fish_one(float x_pos, float y_pos, float percent, float TailMoveUpdate);
	void fish_two(float x_pos, float y_pos, float percent, float TailMoveUpdate);
	void fish_three(float x_pos, float y_pos, float percent , float TailMoveUpdate);
	void fish_four(float x_pos, float y_pos, float percent, float TailMoveUpdate);
	void fish_bubble_two(float x_pos, float y_pos, float percent);
	void bubble_two(float x_pos, float y_pos, float percent);
	void Gauri_water(float x_pos,float y_pos,float persent);
	void Gauri_land(float x_pos, float y_pos, float persent);
	void Gauri_Shankh(float x_pos, float y_pos, float percent);
	void Gauri_Grass_one(float x_pos, float y_pos, float persent, float delta_wave_factor,float wave_factor);
	void Gauri_Grass_two(float x_pos, float y_pos, float persent, float delta_wave_factor, float wave_factor);
	void Gauri_Grass_four(float x_pos, float y_pos, float persent, float delta_wave_factor, float wave_factor);
	void Gauri_Grass_three(float x_pos, float y_pos, float persent, float delta_wave_factor, float wave_factor);
	void Gauri_Kasav(float x_pos,float y_pos, float persent, float Ypercent);
	void Gauri_Starfish( float x_pos, float y_pos, float percent);
	void Treasure_Adesh(float x_pos, float y_pos, float percent);
	void Prajwal_Happy(float x_pos, float y_pos, float percent, float FadeFactor);
	void Prajwal_Birthday(float x_pos, float y_pos, float percent, float FadeFactor);
	void Prajwal_Name(float x_pos, float y_pos, float percent, float FadeFactor);
	void ScreenQuadTwo(void);
	void Bulbble_Nivrutti(const char* name, float x_pos, float y_pos, float radiusx, float radiusy, float percent, float text_x, float text_y);



	// Animation Function declarations
	void TwoSecondDelay(int value);
	void MoonPosUpdater(int value);
	void StarsShineFunc(int value);
	void ScreenFadeIn(int);
	void ScreenFadeOut(int);
	void AstroFadeIn(int);
	void MediFadeIn(int);
	void CompFadeIn(int);
	void AstroMediCompFadeOut(int);
	void TextFadeIn(int);
	void UresFadeIn(int);
	void MountainShineUpdater(int);
	void RopeDissapper(int);
	void BoatUpdate(int);
	void SceneUpdater(void);
	void FishPosUpdater(int);
	void BubbleXPosUpdater(int);
	void BubbleYPosUpdater(int);
	void BubbleSizeUpdater(int);
	void BubbleTwoXPosUpdater(int);
	void BubbleTwoYPosUpdater(int);
	void BubbleTwoSizeUpdater(int);
	void TailMoveUpdater(int);
	void SceneUpUpdater(int);
	void ScreenFadeInTwo(int);
	void ScreenFadeOutTwo(int);
	void NameBubbleUpdater(int);
	void GrassAnimation(int);
	void TurtleFinsUpdater(int);
	void TurtlePosUpdater(int);
	
	


	// code
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Happy Birthday Prajwal");

	initialize();

	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutTimerFunc(0, MoonPosUpdater, 0);
	glutTimerFunc(0, StarsShineFunc, 0);
	glutTimerFunc(2000, TwoSecondDelay, 0);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutCloseFunc(uninitialize);

	glutMainLoop();

	return(0);
}

int initialize(void)
{
	// code
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f);

	srand(time(0));
	for (int Name_i = 0; Name_i < 13; Name_i++)
	{
		int xPos_rand = rand() % 1600 - 800;
		float xPos = (float)xPos_rand / 1000.0f;

		if (xPos > 0.0f)
		{
			xPos = xPos * (-1.0f);
		}

		GroupMemberNameBubblexPos[Name_i] = xPos;
	}

	PlaySound(TEXT("FinalTrack1.wav"), NULL, SND_FILENAME | SND_ASYNC);
	return(0);
}

void resize(int width, int height)
{
	// code
	glViewport( 0, 0, width, height);
}

void display(void) 
{
	// code
	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f(3.0f/255.0f, 3.0f/255.0f, 33.0f/255.0f);
	glBegin(GL_QUADS);
	{
		glVertex3f(-1.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
	}
	glEnd();

	switch (Scene)
	{
	case 0:
		DrawMoon_Mayur_Tadekar(-1.2f + VALUE_FROM_PERCENT(0.65f, MoonPosUpdate), 0.0f, 1.0f, 40.0f, 40.0f);
		Prasad_Stars(0.0f, 0.0f, StarsShineFactor);
		Swati_astro(0.3f, 0.0f, 100.0f, AstroFadeFactor);
		Swati_medi(0.2f, 0.07f, 100.0f, MediFadeFactor);
		Swati_comp(0.2f, 0.02f, 100.0f, CompFadeFactor);
		Swati_text(0.3f, -0.8f, 100.0f, TextFadeFactor);
		Swati_ure(0.31f, -0.8f, 100.0f, UresFadeFactor);
		ScreenQuad();
		break;
	
	case 1:
		DrawMoon_Mayur_Tadekar(-1.2f + VALUE_FROM_PERCENT( 0.5f, MoonPosUpdate), 0.7f, 1.0f, 35.0f, 35.0f);
		Prasad_Stars(0.0f, 0.0f, StarsShineFactor);
		WaterQuadOne();
		DrawMoonReflection_Mayur_Tadekar(-1.2f + VALUE_FROM_PERCENT( 0.5f, MoonPosUpdate), -0.85f, 0.4f, 35.0f, 15.0f);
		pankaj_mountainS(0.0f, -0.6f, 100.0f, MountainShineUpdate);
		Boat_Amol((VALUE_FROM_PERCENT(-1.0f, BoatRightUpdate)) , -0.25f, 100.0f);
		Bridge_Amol(0.0f, -0.25f, 100.0f);
		Rope_Amol(0.0f, -0.25f, 100.0f, RopeFadeFactor);
		ScreenQuad();
		break;
	
	case 2:
		WaterQuadTwo();
		fish_one(1.8f + VALUE_FROM_PERCENT( -2.7f, FishPosUpdate) , -0.2f, 100.0f, TailMoveUpdate);
		fish_two(-1.5f + VALUE_FROM_PERCENT( 2.5f, FishPosUpdate) , 0.1f, 100.0f, TailMoveUpdate);
		fish_three(-1.8f + VALUE_FROM_PERCENT( 2.5f, FishPosUpdate) , 0.0f, 100.0f, TailMoveUpdate);
		fish_bubble_two(0.99f + VALUE_FROM_PERCENT( -2.7f, BubbleXPosUpdate), -0.58f + VALUE_FROM_PERCENT( 1.9f, BubbleYPosUpdate), BubbleSizeUpdate);
		fish_bubble_two(-1.17f + VALUE_FROM_PERCENT( 2.5f, BubbleXPosUpdate), -0.125f + VALUE_FROM_PERCENT( 1.95f, BubbleYPosUpdate), BubbleSizeUpdate);
		fish_bubble_two(-0.99f + VALUE_FROM_PERCENT( 2.5f, BubbleXPosUpdate), 0.42f + VALUE_FROM_PERCENT( 2.49f, BubbleYPosUpdate), BubbleSizeUpdate);
		bubble_two(0.99f + VALUE_FROM_PERCENT( -2.7f, BubbleTwoXPosUpdate), -0.58f + VALUE_FROM_PERCENT( 1.9f, BubbleTwoYPosUpdate), BubbleTwoSizeUpdate);
		bubble_two(-1.17f + VALUE_FROM_PERCENT( 2.5f, BubbleTwoXPosUpdate), -0.125f + VALUE_FROM_PERCENT( 1.95f, BubbleTwoYPosUpdate), BubbleTwoSizeUpdate);
		bubble_two(-0.99f + VALUE_FROM_PERCENT( 2.5f, BubbleTwoXPosUpdate), 0.42f + VALUE_FROM_PERCENT( 2.49f, BubbleTwoYPosUpdate), BubbleTwoSizeUpdate);
		ScreenQuad();
		break;
	
	case 3:
		WaterQuadTwo();
		Gauri_water(0.0f, -1.95f + VALUE_FROM_PERCENT(2.0f, SceneUpUpdate), 100.0f);
		Gauri_Shankh(-0.3f, -1.95f + VALUE_FROM_PERCENT(2.0f, SceneUpUpdate), 100.0f);

		Gauri_Grass_one(0.03f, -2.0f + VALUE_FROM_PERCENT(2.0f, SceneUpUpdate), 100.0f, -1.0f, WaveFactor);
		Gauri_Grass_two(0.12f, -2.0f + VALUE_FROM_PERCENT(2.0f, SceneUpUpdate), 100.0f, -0.8f, WaveFactor);
		Gauri_Grass_three(0.06f, -2.0f + VALUE_FROM_PERCENT(2.0f, SceneUpUpdate), 100.0f, -1.0f, WaveFactor);
		Gauri_Grass_four(0.09f, -2.0f + VALUE_FROM_PERCENT(2.0f, SceneUpUpdate), 100.0f, -0.8f, WaveFactor);

		Gauri_land(0.0f, -2.0f + VALUE_FROM_PERCENT(2.0f, SceneUpUpdate), 100.0f);
		Gauri_Starfish(0.5, -2.0f + VALUE_FROM_PERCENT(2.0f, SceneUpUpdate), 100.0f);

		fish_four(1.5f + VALUE_FROM_PERCENT(-2.5, SceneUpUpdate), -1.2f + VALUE_FROM_PERCENT(2.0f, SceneUpUpdate), 100.0f, TailMoveUpdate);
		fish_bubble_two(0.7f - VALUE_FROM_PERCENT(2.5f, AgainBubbleXPosUpdate) , -1.63f + VALUE_FROM_PERCENT(2.2f, AgainBubbleYPosUpdate), AgainBubbleSizeUpdate);
		Treasure_Adesh(0.0f, -1.83f + VALUE_FROM_PERCENT(2.0f, SceneUpUpdate), 100.0f);

		Gauri_Grass_one(0.33f, -2.0f + VALUE_FROM_PERCENT(2.0f, SceneUpUpdate), 100.0f, -1.0f, WaveFactor);
		Gauri_Grass_two(0.30f, -2.0f + VALUE_FROM_PERCENT(2.0f, SceneUpUpdate), 100.0f, -0.8f, WaveFactor);
		Gauri_Grass_three(0.27f, -2.0f + VALUE_FROM_PERCENT(2.0f, SceneUpUpdate), 100.0f, -1.0f, WaveFactor);
		Gauri_Grass_four(0.24f, -2.0f + VALUE_FROM_PERCENT(2.0f, SceneUpUpdate), 100.0f, -0.8f, WaveFactor);

        Gauri_Kasav(1.6f + VALUE_FROM_PERCENT(-2.0f, TurtlePosUpdate), 0.0f, 100.0f, TurtleFinsUpdate);

		Gauri_Grass_one(-0.70f, -2.0f + VALUE_FROM_PERCENT(2.0f, SceneUpUpdate), 100.0f, -1.0f, WaveFactor);
		Gauri_Grass_two(-0.67f, -2.0f + VALUE_FROM_PERCENT(2.0f, SceneUpUpdate), 100.0f, -0.8f, WaveFactor);
		Gauri_Grass_three(-0.73f, -2.0f + VALUE_FROM_PERCENT(2.0f, SceneUpUpdate), 100.0f, -1.0f, WaveFactor);
		Gauri_Grass_four(-0.64f, -2.0f + VALUE_FROM_PERCENT(2.0f, SceneUpUpdate), 100.0f, -0.8f, WaveFactor);

		Prajwal_Happy(0.0f, -2.0f + VALUE_FROM_PERCENT(2.0f, SceneUpUpdate), 20.0f, 1.0f);
		Prajwal_Birthday(0.0f, -2.0f + VALUE_FROM_PERCENT(2.0f, SceneUpUpdate), 20.0f, 1.0f);
		Prajwal_Name(0.0f, -1.7f + VALUE_FROM_PERCENT(2.0f, SceneUpUpdate), 50.0f, 1.0f);
		ScreenQuadTwo();
		break;
		
	case 4:
		Gauri_water(0.0f, -1.95f + VALUE_FROM_PERCENT(2.0f, SceneUpUpdate), 100.0f);
		Gauri_Shankh(-0.3f, -1.95f + VALUE_FROM_PERCENT(2.0f, SceneUpUpdate), 100.0f);
		
		Gauri_Grass_one(0.03f, -2.0f + VALUE_FROM_PERCENT(2.0f, SceneUpUpdate), 100.0f, -1.0f, WaveFactor);
		Gauri_Grass_two(0.12f, -2.0f + VALUE_FROM_PERCENT(2.0f, SceneUpUpdate), 100.0f, -0.8f, WaveFactor);
		Gauri_Grass_three(0.06f, -2.0f + VALUE_FROM_PERCENT(2.0f, SceneUpUpdate), 100.0f, -1.0f, WaveFactor);
		Gauri_Grass_four(0.09f, -2.0f + VALUE_FROM_PERCENT(2.0f, SceneUpUpdate), 100.0f, -0.8f, WaveFactor);

		for (int Name_i = 0; Name_i < 13; Name_i++)
		{
			Bulbble_Nivrutti(GroupMembersName[Name_i],
							 GroupMemberNameBubblexPos[Name_i], 
							 ((-1.0f * Name_i) - 1.5f) + VALUE_FROM_PERCENT(15.0f, NameBubbleUpdate),
							  0.035 * (strlen(GroupMembersName[Name_i])), 
							  0.03 * (strlen(GroupMembersName[Name_i])) * 9/5, 
							  90.0f, 
							  -0.04f * (strlen(GroupMembersName[Name_i]) / 2), 
							  0.0f);
		}

		Gauri_land(0.0f, -2.0f + VALUE_FROM_PERCENT(2.0f, SceneUpUpdate), 100.0f);
		Gauri_Starfish(0.5, -2.0f + VALUE_FROM_PERCENT(2.0f, SceneUpUpdate), 100.0f);

		Gauri_Grass_one(0.33f, -2.0f + VALUE_FROM_PERCENT(2.0f, SceneUpUpdate), 100.0f, -1.0f, WaveFactor);
		Gauri_Grass_two(0.30f, -2.0f + VALUE_FROM_PERCENT(2.0f, SceneUpUpdate), 100.0f, -0.8f, WaveFactor);
		Gauri_Grass_three(0.27f, -2.0f + VALUE_FROM_PERCENT(2.0f, SceneUpUpdate), 100.0f, -1.0f, WaveFactor);
		Gauri_Grass_four(0.24f, -2.0f + VALUE_FROM_PERCENT(2.0f, SceneUpUpdate), 100.0f, -0.8f, WaveFactor);

		Gauri_Grass_one(-0.70f, -2.0f + VALUE_FROM_PERCENT(2.0f, SceneUpUpdate), 100.0f, -1.0f, WaveFactor);
		Gauri_Grass_two(-0.67f, -2.0f + VALUE_FROM_PERCENT(2.0f, SceneUpUpdate), 100.0f, -0.8f, WaveFactor);
		Gauri_Grass_three(-0.73f, -2.0f + VALUE_FROM_PERCENT(2.0f, SceneUpUpdate), 100.0f, -1.0f, WaveFactor);
		Gauri_Grass_four(-0.64f, -2.0f + VALUE_FROM_PERCENT(2.0f, SceneUpUpdate), 100.0f, -0.8f, WaveFactor);

		Gauri_Kasav(0.1f, -2.2f + VALUE_FROM_PERCENT(2.0f, SceneUpUpdate), 100.0f, 0.0f);
		Treasure_Adesh(0.0f, -1.83f + VALUE_FROM_PERCENT(2.0f, SceneUpUpdate), 100.0f);

		ScreenQuadTwo();
	default:
		break;
	}

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
	glDisable(GL_BLEND);
}

// Objects Function definations
void ScreenQuad(void)
{
	glColor4f(0.0f, 0.0f, 0.0f, ScreenFadeFactor);
	glBegin(GL_QUADS);
	{
		glVertex3f(-1.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
	}
	glEnd();
}

void ScreenQuadTwo(void)
{
	glColor4f(0.0f, 0.0f, 0.0f, ScreenFadeFactorTwo);
	glBegin(GL_QUADS);
	{
		glVertex3f(-1.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
	}
	glEnd();
}

void WaterQuadOne(void)
{
	glColor3f(0.474510, 0.788235, 0.941176);
	glBegin(GL_QUADS);
	{
		glVertex3f(-1.0f, -0.55f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, -0.55f, 0.0f);
	}
	glEnd();
}

void WaterQuadTwo(void)
{
	glBegin(GL_QUADS);
	{
		glColor3f(0.474510, 0.788235, 0.941176);
		glVertex3f(-1.0f, 1.0f + VALUE_FROM_PERCENT(2.0f, SceneUpUpdate), 0.0f);
		glColor3f(0.019608, 0.501961, 0.662745);
		glVertex3f(-1.0f, -1.0f + VALUE_FROM_PERCENT(2.0f, SceneUpUpdate), 0.0f);
		glVertex3f(1.0f, -1.0f + VALUE_FROM_PERCENT(2.0f, SceneUpUpdate), 0.0f);
		glColor3f(0.474510, 0.788235, 0.941176);
		glVertex3f(1.0f, 1.0f + VALUE_FROM_PERCENT(2.0f, SceneUpUpdate), 0.0f);
	}
	glEnd();

}


// Animation Function definations
void SceneUpdater(void)
{
	Scene++;

	switch(Scene)
	{
		case 1:
		case 2:
			MoonMov = TRUE;
			MoonPosUpdate = 0.0f;
			glutTimerFunc(200, MoonPosUpdater, 0);

			glutTimerFunc(100, ScreenFadeOut, 0);
			break;

		case 4 :
			glutPostRedisplay();
			glutTimerFunc(0, ScreenFadeOutTwo, 0);
			break;
	}
}

void TwoSecondDelay(int value)
{
	glutTimerFunc(0, AstroFadeIn, 0);

	glutPostRedisplay();
}

// Functions for 0th Scene Animation
void MoonPosUpdater(int value)
{
	if (MoonMov)
	{
		MoonPosUpdate = MoonPosUpdate + 0.5f;
		if ((MoonPosUpdate > 30.0f) && (Scene == 1))
		{
			glutTimerFunc(16, MountainShineUpdater, 0);
		}

		if (MoonPosUpdate >= 100.0f)
		{
			MoonMov = FALSE;
		}
		glutPostRedisplay();
		glutTimerFunc(16, MoonPosUpdater, 0);
	}
}

void StarsShineFunc(int value)
{
	if (StarsShine)
	{
		StarsShineFactor = StarsShineFactor + 0.01f;
		if (StarsShineFactor >= 1.0f)
		{
			StarsShine = FALSE;
		}
	}
	else
	{
		StarsShineFactor = StarsShineFactor - 0.01f;
		if (StarsShineFactor <= 0.0f)
		{
			StarsShine = TRUE;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(5, StarsShineFunc, 0);
}

void ScreenFadeIn(int value)
{
	if (ScreenFade)
	{
		ScreenFadeFactor = ScreenFadeFactor + 0.01f;
		if (ScreenFadeFactor >= 1.0f)
		{
			ScreenFade = FALSE;
			SceneUpdater();
		}
		glutPostRedisplay();
		glutTimerFunc(20, ScreenFadeIn, 0);
	}
}

void ScreenFadeOut(int value)
{
	if (ScreenFade == FALSE)
	{
		ScreenFadeFactor = ScreenFadeFactor - 0.015f;
		if (ScreenFadeFactor <= 0.0f)
		{
			ScreenFade = TRUE;
			if (Scene == 2)
			{
				glutTimerFunc(0, FishPosUpdater, 20);
				glutTimerFunc(0, BubbleXPosUpdater, 20);
				glutTimerFunc(0, BubbleTwoXPosUpdater, 20);
				glutTimerFunc(0, TailMoveUpdater, 0);
			}
			glutTimerFunc(1500, RopeDissapper, 0);
		}

		glutPostRedisplay();
		glutTimerFunc(20, ScreenFadeOut, 0);
	}
}

void AstroFadeIn(int value)
{
	if (AstroFade)
	{
		AstroFadeFactor = AstroFadeFactor + 0.004f;
		if (AstroFadeFactor >= 1.0f)
		{
			AstroFade = FALSE;
			glutTimerFunc(0, MediFadeIn, 0);
		}
		glutPostRedisplay();
		glutTimerFunc(20, AstroFadeIn, 0);
	}
}

void MediFadeIn(int value)
{	
	if (MediFade)
	{
		MediFadeFactor = MediFadeFactor + 0.005f;
		if (MediFadeFactor >= 1.0f)
		{
			MediFade = FALSE;
			glutTimerFunc(0, CompFadeIn, 0);
		}
		glutPostRedisplay();
		glutTimerFunc(20, MediFadeIn, 0);
	}
}

void CompFadeIn(int value)
{
	if (CompFade)
	{
		CompFadeFactor = CompFadeFactor + 0.005f;
		if (CompFadeFactor >= 1.0f)
		{
			CompFade = FALSE;
			glutTimerFunc(0, AstroMediCompFadeOut, 0);
		}
		glutPostRedisplay();
		glutTimerFunc(20, CompFadeIn, 0);
	}
}

void AstroMediCompFadeOut(int value)
{
		AstroFadeFactor = AstroFadeFactor - 0.01f;
		MediFadeFactor = MediFadeFactor - 0.01f;
		CompFadeFactor = CompFadeFactor - 0.015f;

		if((AstroFadeFactor >= 0.0f) && (MediFadeFactor >= 0.0f) && (CompFadeFactor >= 0.0f))
		{
			AstroFade = TRUE;
			MediFade = TRUE;
			CompFade = TRUE;
			glutTimerFunc(4000, TextFadeIn, 0);
			glutTimerFunc(4000, UresFadeIn, 0);
		}
		glutPostRedisplay();
		glutTimerFunc(20, AstroMediCompFadeOut, 0);
}

void TextFadeIn(int value)
{
	if (TextFade)
	{
		TextFadeFactor = TextFadeFactor + 0.0002f;

		if (TextFadeFactor >= 1.0f)
		{
			TextFade = FALSE;
		}
		glutPostRedisplay();
		glutTimerFunc(110, TextFadeIn, 0);
	}
}

void UresFadeIn(int value)
{
	if (UresFade)
	{
		UresFadeFactor = UresFadeFactor + 0.0002f;

		if (UresFadeFactor >= 1.0f)
		{
			UresFade = FALSE;
			glutTimerFunc(1000, ScreenFadeIn, 0);
		}
		glutPostRedisplay();
		glutTimerFunc(110, UresFadeIn, 0);
	}
}

// Function for 1st Scene Animation
void MountainShineUpdater(int value)
{
	if (MountainShine)
	{
		MountainShineUpdate = MountainShineUpdate + 0.005f;
		if (MountainShineUpdate >= 1.0f)
		{
			MountainShine = FALSE;
		}
		glutPostRedisplay();
		glutTimerFunc(450, MountainShineUpdater, 0);
	}
}

void RopeDissapper(int value)
{
	if (RopeFade)
	{
		RopeFadeFactor = RopeFadeFactor - 0.02f;
		if (RopeFadeFactor <= 0.0f)
		{
			RopeFade = FALSE;
			glutTimerFunc(3000, BoatUpdate, 0);
		}

		glutPostRedisplay();
		glutTimerFunc(20, RopeDissapper, 0);
	}

}

void BoatUpdate(int value)
{
	if(BoatMove)
	{
		BoatRightUpdate = BoatRightUpdate + 0.4f;
		if (BoatRightUpdate >= 140.0f)
		{
			BoatMove = FALSE;
			glutTimerFunc(20, ScreenFadeIn, 0);

		}
		glutPostRedisplay();
		glutTimerFunc(20, BoatUpdate, 0);
	}

}

// Function for 2nd Scene Animation
void FishPosUpdater(int value)
{
	if (FishMov)
	{
		FishPosUpdate = FishPosUpdate + (value / 100.0f);
		if (FishPosUpdate >= 100.0f)
		{
			FishMov = FALSE;
			Scene = 3;
			glutTimerFunc(0, SceneUpUpdater, 0);
			glutTimerFunc(0, TailMoveUpdater, 0);
			glutTimerFunc(20, GrassAnimation, 0);
			glutTimerFunc(0, TurtleFinsUpdater, 0);
		}
		glutPostRedisplay();
		glutTimerFunc(16, FishPosUpdater, value);
	}
}

void BubbleXPosUpdater(int value)
{
	if (BubbleXMov)
	{
		BubbleXPosUpdate = BubbleXPosUpdate + 0.2f;
		if (BubbleXPosUpdate >= 10.0f)
		{
			glutTimerFunc(16, BubbleSizeUpdater, 0);
		}
		if (BubbleXPosUpdate >= 30.0f)
		{
			BubbleXMov = FALSE;
			glutTimerFunc(0, BubbleYPosUpdater, 0);
		}
		glutPostRedisplay();
		glutTimerFunc(16, BubbleXPosUpdater, 0);
	}
}

void BubbleYPosUpdater(int value)
{
	if (BubbleYMov)
	{
		BubbleYPosUpdate = BubbleYPosUpdate + 0.5f;
		if (BubbleYPosUpdate >= 100)
		{
			BubbleYMov = FALSE;
		}
		glutPostRedisplay();
		glutTimerFunc(16, BubbleYPosUpdater, 0);
	}
}

void BubbleSizeUpdater(int value)
{
	if (BubbleSize)
	{
		BubbleSizeUpdate = BubbleSizeUpdate + 0.01f;
		if (BubbleSizeUpdate >= 100.0f)
		{
			BubbleSize = FALSE;
		}
		glutPostRedisplay();
		glutTimerFunc(16, BubbleSizeUpdater, 0);
	}
}

void BubbleTwoXPosUpdater(int value)
{
	if (BubbleTwoXMov)
	{
		BubbleTwoXPosUpdate = BubbleTwoXPosUpdate + 0.2f;
		if (BubbleTwoXPosUpdate >= 40.0f)
		{
			glutTimerFunc(16, BubbleTwoSizeUpdater, 0);
		}
		if (BubbleTwoXPosUpdate >= 60.0f)
		{
			BubbleXMov = FALSE;
			glutTimerFunc(0, BubbleTwoYPosUpdater, 0);
		}
		glutPostRedisplay();
		glutTimerFunc(16, BubbleTwoXPosUpdater, 0);
	}
}

void BubbleTwoYPosUpdater(int value)
{
	if (BubbleTwoYMov)
	{
		BubbleTwoYPosUpdate = BubbleTwoYPosUpdate + 0.02f;
		if (BubbleTwoYPosUpdate >= 100)
		{
			BubbleTwoYMov = FALSE;
		}
		glutPostRedisplay();
		glutTimerFunc(16, BubbleTwoYPosUpdater, 0);
	}
}

void BubbleTwoSizeUpdater(int value)
{
	if (BubbleTwoSize)
	{
		BubbleTwoSizeUpdate = BubbleTwoSizeUpdate + 0.01f;
		if (BubbleTwoSizeUpdate >= 100.0f)
		{
			BubbleTwoSize = FALSE;
		}
		glutPostRedisplay();
		glutTimerFunc(16, BubbleTwoSizeUpdater, 0);
	}
}

void TailMoveUpdater(int value)
{
	if (TailMove)
	{
		TailMoveUpdate = TailMoveUpdate + 0.001f;
		if (TailMoveUpdate >= 0.03f)
		{
			TailMove = FALSE;
		}
		glutPostRedisplay();
		glutTimerFunc(2, TailMoveUpdater, 0);
	}
	else
	{
		TailMoveUpdate = TailMoveUpdate - 0.001f;
		if (TailMoveUpdate <= -0.03f)
		{
			TailMove = TRUE;
		}
		glutPostRedisplay();
		glutTimerFunc(2, TailMoveUpdater, 0);
	}
}

// Function for 3rd Scene Animation
void SceneUpUpdater(int value)
{
	if (SceneUp)
	{
		SceneUpUpdate = SceneUpUpdate + 0.2;
		if (AgainBubbleSize == TRUE && AgainBubbleSizeUpdate <= 100.0f)
		{
			AgainBubbleSizeUpdate = AgainBubbleSizeUpdate + 0.35f;
			AgainBubbleXPosUpdate = AgainBubbleXPosUpdate + 0.2;
			AgainBubbleYPosUpdate = AgainBubbleYPosUpdate + 0.2;
		}
		else
		{
			AgainBubbleYPosUpdate = AgainBubbleYPosUpdate + 0.5;
		}
	
		if (SceneUpUpdate >= 50.0f)
		{
			glutTimerFunc(0, TurtlePosUpdater, 0);
		}
	
		if (SceneUpUpdate >= 100.0f)
		{
			SceneUp = FALSE;
			glutTimerFunc(1000, ScreenFadeInTwo, 0);
		}
		glutPostRedisplay();
		glutTimerFunc(16, SceneUpUpdater, 0);
	}

}

void ScreenFadeInTwo(int value)
{
	if (ScreenFadeTwo)
	{
		ScreenFadeFactorTwo = ScreenFadeFactorTwo + 0.01f;
		if (ScreenFadeFactorTwo >= 1.0f)
		{
			ScreenFadeTwo = FALSE;
			SceneUpdater();
		}
		glutPostRedisplay();
		glutTimerFunc(16, ScreenFadeInTwo, 0);
	}
}

void TurtleFinsUpdater(int value)
{
	if (TurtleFins)
	{
		TurtleFinsUpdate = TurtleFinsUpdate + 0.05f;
		if (TurtleFinsUpdate >= 5.0f)
		{
			TurtleFins = FALSE;
		}
		glutPostRedisplay();
		glutTimerFunc(1, TurtleFinsUpdater, 0);
	}
	else
	{
		TurtleFinsUpdate = TurtleFinsUpdate - 0.05f;
		if (TurtleFinsUpdate <= -5.0f)
		{
			TurtleFins = TRUE;
		}
		glutPostRedisplay();
		glutTimerFunc(1, TurtleFinsUpdater, 0);
	}
}

void TurtlePosUpdater(int value)
{
	TurtlePosUpdate = TurtlePosUpdate + 0.001f;
	if (TurtlePosUpdate >= 100.0f)
	{
		TurtlePos = FALSE;
	}
	glutPostRedisplay();
	glutTimerFunc(16, TurtlePosUpdater, 0);
}

void ScreenFadeOutTwo(int value)
{
	if (ScreenFadeTwo == FALSE)
	{
		ScreenFadeFactorTwo = ScreenFadeFactorTwo - 0.01f;
		if (ScreenFadeFactorTwo <= 0.0f)
		{
			ScreenFadeTwo = TRUE;
			glutTimerFunc(0, NameBubbleUpdater, 0);
		}
		glutPostRedisplay();
		glutTimerFunc(16, ScreenFadeOutTwo, 0);
	}
}


// Function for 4th Scene Animation
void NameBubbleUpdater(int value)
{
	if (bNameBubble)
	{
		NameBubbleUpdate = NameBubbleUpdate + 0.25F;
		if (NameBubbleUpdate >= 100.0f)
		{
			bNameBubble = FALSE;
			ScreenFadeTwo = TRUE;
			ScreenFadeFactorTwo = 0.0f;
			glutTimerFunc(0, ScreenFadeInTwo, 0);
		}
		glutPostRedisplay();
		glutTimerFunc(8, NameBubbleUpdater, 0);
	}
}

void GrassAnimation(int value)
{
	WaveFactor = WaveFactor + 0.05;
	glutPostRedisplay();
	glutTimerFunc(20, GrassAnimation, value);
}