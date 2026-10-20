


#include <windows.h>
#include <GL/gl.h>

#include "animation.h"
#include "hand.h"
#include "bow.h"
#include "arrow.h"
#include "ravan.h"
#include "fire_effect.h"
#include "mayur_common.h"

static GLfloat hand_x_delta = 0.0f;
static GLfloat string_x_pull = 0.0f;
static GLfloat arrow_x_pull = 0.0f;
static GLfloat arrow_scale_percent = 500.0f;
static GLfloat hand_var_yenyacha_angle = -70.0f;
static GLfloat fire_timer = 0.0f;
static GLfloat fire_xpos = -2.0f;
static GLfloat fire_ypos = -4.6f;
static GLfloat show_arrow = TRUE;
static BOOL drawFireFlag = FALSE;
static BOOL isAnimationComplete = FALSE;
static GLfloat ravanScaleFactor = 1.0f;
static GLfloat ravanYPosFactor = 0.0f;
static GLfloat camera_zpos = 20.0f;
static GLfloat camera_ypos = -5.0f;

void 	drawRamHands(float x_pos, float y_pos, float percent, float arrow_percent)
{
	// Code
	
	glTranslatef(x_pos, y_pos, 0.0f);

	drawBow(0.0f, 0.0f, percent, -90.0f);
	left_hand(0.4f, 0.0f, percent, -90, 0.08f, 0.39f, 0.94f);

	drawBowString(0.0f, 0.0f, percent, -90.0f, -string_x_pull);
	
	if(show_arrow)
	{
		drawArrow(VFP(0.99f, arrow_percent) + arrow_x_pull, 0.0f, arrow_percent, 0.0f, 1.5f);
	}
	
	right_hand(0.5 + hand_x_delta, -0.3f, percent, -90);

	glTranslatef(-x_pos, -y_pos, 0.0f);
}

void 	drawScene()
{
	// Code
	glLoadIdentity();

	gluLookAt(	0.0f, camera_ypos, camera_zpos,
				0.0f, camera_ypos, 0.0f,
				0.0f, 1.0f, 0.0f);



	drawRavana(0.0f, ravanYPosFactor, ravanScaleFactor);	

	// VFP(2.0f, -500.0f) + x_pos
	glRotatef(70.0f, 0.0f, 1.0f, 0.0f);

	glTranslatef(VFP(2.0f, -1000.0f), VFP(2.0f, -230.0f), 0.0f);
	glRotatef(hand_var_yenyacha_angle, 0.0f, 0.0f, 1.0f);

	glTranslatef(VFP(2.0f, 500.0f), 0.0f, 0.0f);
	drawRamHands(0.0f, 0.0f, 500.0f, arrow_scale_percent);
	glTranslatef(-VFP(2.0f, 500.0f), 0.0f, 0.0f);

	glRotatef(hand_var_yenyacha_angle, 0.0f, 0.0f, -1.0f);
	glTranslatef(VFP(2.0f, 1000.0f), VFP(2.0f, 230.0f), 0.0f);

	glRotatef(70.0f, 0.0f, -1.0f, 0.0f);

	if(drawFireFlag)
	{
		drawFire(fire_xpos, fire_ypos, 100.0f);
	}
}

void 	initializeScene()
{
	// Code
	initParticles();
}

void 	animateScene(void)
{
	// Code
	static int animate_flag = 1;

	switch(animate_flag)
	{
	case 1:
		if(eka_tondache_10_kar < 1.4f)
		{
			eka_tondache_10_kar += 0.005f;
		}
		else
		{
			animate_flag++;
		}
		break;

	case 2:
		if(hand_var_yenyacha_angle < 0.0f)
		{
			hand_var_yenyacha_angle += 0.25f;
		}
		else
		{
			animate_flag++;
		}
		break;

	case 3:
		if(hand_x_delta > -3.4f)
		{
			hand_x_delta -= 0.025f;
			string_x_pull -= 0.025f;
			arrow_x_pull -= 0.025f;
		}
		else
		{
			animate_flag++;
		}
		break;

	case 4:
		if(fire_timer < 2.0f)
		{
			drawFireFlag = TRUE;
			fire_timer += 0.01f;
		}
		else
		{
			animate_flag++;
		}
		break;

	case 5:
		ravan_ghabarla = TRUE;
		if(!(string_x_pull >= -0.05f))
			string_x_pull += 0.05f;

		if(fire_xpos < 0.0f)
			fire_xpos += VFP(0.01f, 85);

		if(arrow_x_pull < 8.6f)
		{
			arrow_x_pull += VFP(0.05f, 100.0);
			arrow_scale_percent -= VFP(1.0f, VFP(180, 100));
		}
		else
		{
			animate_flag++;
		}
		break;

	case 6:
		show_arrow = FALSE;
		if(hand_var_yenyacha_angle > -90.0f)
		{
			hand_var_yenyacha_angle -= 0.5f;
		}

		if(arrow_scale_percent > 0.1f)
		{
			arrow_x_pull += VFP(0.05f, 100.0);
			arrow_scale_percent -= VFP(1.0f, VFP(180, 100));
		}

		if( fire_bottomXRadius < 2.6f )
		{
			fire_bottomXRadius += 0.002f;
			fire_bottomYRadius += 0.0008f;
			fire_topXRadius += 0.0009f;
			fire_topYRadius += 0.002f;
			fire_ypos -= 0.0005f;			
		}
		else
		{
			animate_flag++;
		}
		break;

	case 7:
		if( fire_ypos > -11.0f )
		{
			fire_ypos -= 0.01f;	
			fire_topXRadius += 0.0005f;
			fire_topYRadius += 0.005f;		
		}
		else
			animate_flag++;
		break;

	case 8:
		if(ravanScaleFactor > 0.0f)
		{
			ravanScaleFactor -= 0.0025f;
			ravanYPosFactor -= 0.02f;
		}
		else
		{
			animate_flag++;
		}
		break;

	case 9:
		if( camera_ypos > -5.0f)
		{
			camera_ypos -= 0.010f;
		}

		if( camera_zpos > 1.0f )
		{
			camera_zpos -= 0.025f;
		}
		else
		{
			animate_flag++;
		}

		break;

	default:
		isAnimationComplete = TRUE;
		break;
	}

	if(drawFireFlag)
	{
		incrementParticleCount();
		updateParticles();
	}
}

BOOL updateScene(HWND hwnd)
{
	// Code
	KillTimer(hwnd, 2610);
	animateScene();
	SetTimer(hwnd, 2610, 10, NULL);
	return(isAnimationComplete);
}
