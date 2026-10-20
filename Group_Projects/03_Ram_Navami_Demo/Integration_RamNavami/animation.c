


#include <windows.h>
#include <GL/gl.h>

#include "animation.h"
#include "hand.h"
#include "bow.h"
#include "arrow.h"
#include "ravan.h"
#include "fire_effect.h"
#include "mayur_common.h"

static GLfloat mst_hand_x_delta = 0.0f;
static GLfloat mst_string_x_pull = 0.0f;
static GLfloat mst_arrow_x_pull = 0.0f;
static GLfloat mst_arrow_scale_percent = 500.0f;
static GLfloat mst_hand_var_yenyacha_angle = -70.0f;
static GLfloat mst_fire_timer = 0.0f;
static GLfloat mst_fire_xpos = -2.0f;
static GLfloat mst_fire_ypos = -4.6f;
static GLfloat mst_show_arrow = TRUE;
static BOOL  mst_drawFireFlag = FALSE;
static BOOL mst_isAnimationComplete = FALSE;
static GLfloat mst_ravanScaleFactor = 1.0f;
static GLfloat mst_ravanYPosFactor = 0.0f;
static GLfloat mst_camera_zpos = 20.0f;
static GLfloat mst_camera_ypos = -5.0f;


void 	 mst_drawRamHands(float x_pos, float y_pos, float percent, float arrow_percent)
{
	// Code
	
	glTranslatef(x_pos, y_pos, 0.0f);

	 mst_drawBow(0.0f, 0.0f, percent, -90.0f);
	left_hand(0.4f, 0.0f, percent, -90, 0.08f, 0.39f, 0.94f);

	 mst_drawBowString(0.0f, 0.0f, percent, -90.0f, -mst_string_x_pull);
	
	if(mst_show_arrow)
	{
		 mst_drawArrow(VFP(0.99f, arrow_percent) + mst_arrow_x_pull, 0.0f, arrow_percent, 0.0f, 1.5f);
	}
	
	right_hand(0.5 + mst_hand_x_delta, -0.3f, percent, -90);

	glTranslatef(-x_pos, -y_pos, 0.0f);
}

void 	 mst_drawScene()
{
	// Code
	glLoadIdentity();

	gluLookAt(	0.0f, mst_camera_ypos, mst_camera_zpos,
				0.0f, mst_camera_ypos, 0.0f,
				0.0f, 1.0f, 0.0f);



	 mst_drawRavana(0.0f, mst_ravanYPosFactor, mst_ravanScaleFactor);	

	// VFP(2.0f, -500.0f) + x_pos
	glRotatef(70.0f, 0.0f, 1.0f, 0.0f);

	glTranslatef(VFP(2.0f, -1000.0f), VFP(2.0f, -230.0f), 0.0f);
	glRotatef(mst_hand_var_yenyacha_angle, 0.0f, 0.0f, 1.0f);

	glTranslatef(VFP(2.0f, 500.0f), 0.0f, 0.0f);
	 mst_drawRamHands(0.0f, 0.0f, 500.0f, mst_arrow_scale_percent);
	glTranslatef(-VFP(2.0f, 500.0f), 0.0f, 0.0f);

	glRotatef(mst_hand_var_yenyacha_angle, 0.0f, 0.0f, -1.0f);
	glTranslatef(VFP(2.0f, 1000.0f), VFP(2.0f, 230.0f), 0.0f);

	glRotatef(70.0f, 0.0f, -1.0f, 0.0f);

	if( mst_drawFireFlag)
	{
		 mst_drawFire(mst_fire_xpos, mst_fire_ypos, 100.0f);
	}
}

void 	mst_initializeScene()
{
	// Code
	mst_initParticles();
}

void 	mst_animateScene(void)
{
	// Code
	static int animate_flag = 1;

	switch(animate_flag)
	{
	case 1:
		if(mst_eka_tondache_10_kar < 1.4f)
		{
			mst_eka_tondache_10_kar += 0.002f;
		}
		else
		{
			animate_flag++;
		}
		break;

	case 2:
		if(mst_hand_var_yenyacha_angle < 0.0f)
		{
			mst_hand_var_yenyacha_angle += 0.125f;
		}
		else
		{
			animate_flag++;
		}
		break;

	case 3:
		if(mst_hand_x_delta > -3.4f)
		{
			mst_hand_x_delta -= 0.025f;
			mst_string_x_pull -= 0.025f;
			mst_arrow_x_pull -= 0.025f;
		}
		else
		{
			animate_flag++;
		}
		break;

	case 4:
		if(mst_fire_timer < 2.0f)
		{
			 mst_drawFireFlag = TRUE;
			mst_fire_timer += 0.01f;
		}
		else
		{
			animate_flag++;
		}
		break;

	case 5:
		mst_ravan_ghabarla = TRUE;
		if(!(mst_string_x_pull >= -0.05f))
			mst_string_x_pull += 0.05f;

		if(mst_fire_xpos < 0.0f)
			mst_fire_xpos += VFP(0.01f, 85);

		if(mst_arrow_x_pull < 8.6f)
		{
			mst_arrow_x_pull += VFP(0.05f, 100.0);
			mst_arrow_scale_percent -= VFP(1.0f, VFP(180, 100));
		}
		else
		{
			animate_flag++;
		}
		break;

	case 6:
		mst_show_arrow = FALSE;
		if(mst_hand_var_yenyacha_angle > -90.0f)
		{
			mst_hand_var_yenyacha_angle -= 0.5f;
		}

		if(mst_arrow_scale_percent > 0.1f)
		{
			mst_arrow_x_pull += VFP(0.05f, 100.0);
			mst_arrow_scale_percent -= VFP(1.0f, VFP(180, 100));
		}

		if( mst_fire_bottomXRadius < 2.6f )
		{
			mst_fire_bottomXRadius += 0.002f;
			mst_fire_bottomYRadius += 0.0008f;
			mst_fire_topXRadius += 0.0009f;
			mst_fire_topYRadius += 0.002f;
			mst_fire_ypos -= 0.0005f;			
		}
		else
		{
			animate_flag++;
		}
		break;

	case 7:
		if( mst_fire_ypos > -11.0f )
		{
			mst_fire_ypos -= 0.01f;	
			mst_fire_topXRadius += 0.0005f;
			mst_fire_topYRadius += 0.005f;		
		}
		else
			animate_flag++;
		break;

	case 8:
		if(mst_ravanScaleFactor > 0.0f)
		{
			mst_ravanScaleFactor -= 0.0025f;
			mst_ravanYPosFactor -= 0.02f;
		}
		else
		{
			animate_flag++;
		}
		break;

	case 9:
		if( mst_camera_ypos > -5.0f)
		{
			mst_camera_ypos -= 0.010f;
		}

		if( mst_camera_zpos > 1.0f )
		{
			mst_camera_zpos -= 0.025f;
		}
		else
		{
			animate_flag++;
		}

		break;

	default:
		mst_isAnimationComplete = TRUE;
		break;
	}

	if( mst_drawFireFlag)
	{
		mst_incrementParticleCount();
		mst_updateParticles();
	}
}

BOOL mst_updateScene(HWND hwnd)
{
	// Code
	KillTimer(hwnd, 2610);
	mst_animateScene();
	SetTimer(hwnd, 2610, 10, NULL);
	return(mst_isAnimationComplete);
}
