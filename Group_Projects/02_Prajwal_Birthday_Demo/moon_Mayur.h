
/**************************************************
 * S.G.M.P
 * @file: moon.h
 * @brief: Implementation of moon object for Prajwal Birthday Demo
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @Copyright ©2020-2025 MarshallingVoid
 * @date: 11 February 2025 (Tuesday) 09:30:45 PM
 **************************************************/



#include <GL/freeglut.h>

#ifndef _USE_MATH_DEFINES
#define	_USE_MATH_DEFINES
#include <math.h>
#endif /* _USE_MATH_DEFINES */

#ifndef	VALUE_FROM_PERCENT
#define VALUE_FROM_PERCENT(complete, percent)	(complete * percent / 100.0)
#endif

//	Moon Related Function Declarations
extern void DrawCircle_Mayur_Tadekar(float x_radius, float y_radius, float x_pos, float y_pos, float r, float g, float b, float alpha, float percent_x, float percent_y);
extern void DrawLight_Mayur_Tadekar(float x_radius, float y_radius, float x_pos, float y_pos, float r, float g, float b, float alpha, float percent_x, float percent_y, float border);
extern void DrawMoon_Mayur_Tadekar(float x_pos, float y_pos, float alpha, float percent_x, float percent_y);
extern void DrawMoonReflection_Mayur_Tadekar(float x_pos, float y_pos, float alpha, float percent_x, float percent_y);

//	Moon Related Function Definitions
extern void DrawCircle_Mayur_Tadekar(float x_radius, float y_radius, float x_pos, float y_pos, float r, float g, float b, float alpha, float percent_x, float percent_y)
{
	// Code
	glBegin(GL_TRIANGLE_STRIP);
	{
		for(int le = 0; le <= 36; ++le)
		{
			float angle = M_PI * 2.0f * le / 36;

			glColor4f(r/255.0f, g/255.0f, b/255.0f, alpha);
			glVertex3f( x_pos, 
						y_pos, 
						0.0f);
			glVertex3f(	VALUE_FROM_PERCENT(x_radius * sinf(angle), percent_x) + x_pos, 
						VALUE_FROM_PERCENT(y_radius * cosf(angle), percent_y) + y_pos, 
						0.0f);
		}
	}
	glEnd();
}

extern void DrawLight_Mayur_Tadekar(float x_radius, float y_radius, float x_pos, float y_pos, float r, float g, float b, float alpha, float percent_x, float percent_y, float border)
{
	// Code
	glBegin(GL_TRIANGLE_STRIP);
	{
		for(int le = 0; le <= 36; ++le)
		{
			float angle = M_PI * 2.0f * le / 36;

			glColor4f(r/255.0f, g/255.0f, b/255.0f, alpha);
			glVertex3f(	VALUE_FROM_PERCENT(x_radius * sinf(angle), percent_x) + x_pos, 
						VALUE_FROM_PERCENT(y_radius * cosf(angle), percent_y) + y_pos, 
						0.0f);

			glColor4f(border, border, border, alpha);
			glVertex3f(	VALUE_FROM_PERCENT((x_radius+0.06f) * sinf(angle), percent_x) + x_pos, 
						VALUE_FROM_PERCENT((y_radius+0.06f) * cosf(angle), percent_y) + y_pos, 
						0.0f);
		}
	}
	glEnd();
}	

extern void DrawMoon_Mayur_Tadekar(float x_pos, float y_pos, float alpha, float percent_x, float percent_y)
{
	// Code

	DrawCircle_Mayur_Tadekar(VALUE_FROM_PERCENT(0.5f, 60.0f), 0.5f, 0.0f + x_pos, 0.0f + y_pos, 245, 230, 242, alpha, percent_x, percent_y);
	DrawLight_Mayur_Tadekar(VALUE_FROM_PERCENT(0.5f, 60.0f), 0.5f, 0.0f + x_pos, 0.0f + y_pos, 245, 230, 242, alpha, percent_x, percent_y, 0.0f);

	DrawCircle_Mayur_Tadekar(VALUE_FROM_PERCENT(0.13f, 60.0f), 0.13f, VALUE_FROM_PERCENT(-0.15f, percent_x) + x_pos, VALUE_FROM_PERCENT(0.23f, percent_y) + y_pos, 196, 191, 183, alpha, percent_x, percent_y);
	DrawCircle_Mayur_Tadekar(VALUE_FROM_PERCENT(0.11f, 60.0f), 0.11f, VALUE_FROM_PERCENT(-0.18f, percent_x) + x_pos, VALUE_FROM_PERCENT(0.08f, percent_y) + y_pos, 196, 191, 183, alpha, percent_x, percent_y);

	DrawCircle_Mayur_Tadekar(VALUE_FROM_PERCENT(0.05f, 60.0f), 0.05f, VALUE_FROM_PERCENT(0.15f, percent_x) + x_pos, VALUE_FROM_PERCENT(0.3f, percent_y) + y_pos, 196, 191, 183, alpha, percent_x, percent_y);
	DrawCircle_Mayur_Tadekar(VALUE_FROM_PERCENT(0.07f, 60.0f), 0.07f, VALUE_FROM_PERCENT(0.2f, percent_x) + x_pos, VALUE_FROM_PERCENT(0.2f, percent_y) + y_pos, 196, 191, 183, alpha, percent_x, percent_y);
	DrawCircle_Mayur_Tadekar(VALUE_FROM_PERCENT(0.03f, 60.0f), 0.03f, VALUE_FROM_PERCENT(0.11f, percent_x) + x_pos, VALUE_FROM_PERCENT(0.25f, percent_y) + y_pos, 196, 191, 183, alpha, percent_x, percent_y);

	DrawCircle_Mayur_Tadekar(VALUE_FROM_PERCENT(0.16f, 60.0f), 0.16f, VALUE_FROM_PERCENT(0.1f, percent_x) + x_pos, VALUE_FROM_PERCENT(-0.08f, percent_y) + y_pos, 196, 191, 183, alpha, percent_x, percent_y);
	
	DrawCircle_Mayur_Tadekar(VALUE_FROM_PERCENT(0.13f, 60.0f), 0.13f, VALUE_FROM_PERCENT(-0.08f, percent_x) + x_pos, VALUE_FROM_PERCENT(-0.3f, percent_y) + y_pos, 196, 191, 183, alpha, percent_x, percent_y);	
}


extern void DrawMoonReflection_Mayur_Tadekar(float x_pos, float y_pos, float alpha, float percent_x, float percent_y)
{
	// Code

	DrawCircle_Mayur_Tadekar(VALUE_FROM_PERCENT(0.5f, 60.0f), 0.5f, 0.0f + x_pos, 0.0f + y_pos, 255, 255, 255, alpha, percent_x, percent_y);
	DrawLight_Mayur_Tadekar(VALUE_FROM_PERCENT(0.5f, 60.0f), 0.5f, 0.0f + x_pos, 0.0f + y_pos, 255, 255, 255, alpha, percent_x, percent_y, 1.0f);

	DrawCircle_Mayur_Tadekar(VALUE_FROM_PERCENT(0.13f, 60.0f), 0.13f, VALUE_FROM_PERCENT(-0.15f, percent_x) + x_pos, VALUE_FROM_PERCENT(0.23f, percent_y) + y_pos, 255, 255, 255, alpha - 0.2, percent_x, percent_y);
	DrawCircle_Mayur_Tadekar(VALUE_FROM_PERCENT(0.11f, 60.0f), 0.11f, VALUE_FROM_PERCENT(-0.18f, percent_x) + x_pos, VALUE_FROM_PERCENT(0.08f, percent_y) + y_pos, 255, 255, 255, alpha - 0.2, percent_x, percent_y);

	DrawCircle_Mayur_Tadekar(VALUE_FROM_PERCENT(0.05f, 60.0f), 0.05f, VALUE_FROM_PERCENT(0.15f, percent_x) + x_pos, VALUE_FROM_PERCENT(0.3f, percent_y) + y_pos, 255, 255, 255, alpha - 0.2, percent_x, percent_y);
	DrawCircle_Mayur_Tadekar(VALUE_FROM_PERCENT(0.07f, 60.0f), 0.07f, VALUE_FROM_PERCENT(0.2f, percent_x) + x_pos, VALUE_FROM_PERCENT(0.2f, percent_y) + y_pos, 255, 255, 255, alpha - 0.2, percent_x, percent_y);
	DrawCircle_Mayur_Tadekar(VALUE_FROM_PERCENT(0.03f, 60.0f), 0.03f, VALUE_FROM_PERCENT(0.11f, percent_x) + x_pos, VALUE_FROM_PERCENT(0.25f, percent_y) + y_pos, 255, 255, 255, alpha - 0.2, percent_x, percent_y);

	DrawCircle_Mayur_Tadekar(VALUE_FROM_PERCENT(0.16f, 60.0f), 0.16f, VALUE_FROM_PERCENT(0.1f, percent_x) + x_pos, VALUE_FROM_PERCENT(-0.08f, percent_y) + y_pos, 255, 255, 255, alpha - 0.2, percent_x, percent_y);
	
	DrawCircle_Mayur_Tadekar(VALUE_FROM_PERCENT(0.13f, 60.0f), 0.13f, VALUE_FROM_PERCENT(-0.08f, percent_x) + x_pos, VALUE_FROM_PERCENT(-0.3f, percent_y) + y_pos, 255, 255, 255, alpha - 0.2, percent_x, percent_y);	
}
