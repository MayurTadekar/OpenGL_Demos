

#include <windows.h>
#include <GL/gl.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include "bow.h"
#include "mayur_common.h"

// Function to  mst_draw a bow with details
void  mst_drawBowHalf(float x_pos, float y_pos, float percentx, float percenty) 
{
	// Code
    
    // Position the bow
    glTranslatef(x_pos, y_pos, 0.0f);
    
    // Draw bow body (curved arc)
    glColor3f(0.55f, 0.27f, 0.07f); // Brown color for wood
    
    // Calculate bow curvature based on pull amount (0.0 to 1.0)
    float bow_curve_x = 0.7f;
    float bow_curve_y = 0.5f;
    float bow_thickness = 0.05f;
    
    glBegin(GL_TRIANGLE_STRIP);
    {
        // Draw the bow with varying thickness
        for (int i = 20; i <= 120; i += 5) {
            float angle = i * M_PI / 180.0f;
            float x1 = bow_curve_x * cosf(angle);
            float y1 = bow_curve_y * sinf(angle);

            float x2 = (bow_curve_x + bow_thickness) * cosf(angle);
            float y2 = (bow_curve_y + bow_thickness) * sinf(angle);
            
            // Outer edge (thicker at middle, thinner at ends)
            VFP_2FXY(x1, y1, percentx, percenty);
            VFP_2FXY(x2, y2, percentx, percenty);
        }
    }
    glEnd();

    float x_curve = VFP(0.8f, percentx);
    float y_curve = VFP(0.2f, percenty);
    float bow_short_curve_x = 0.1f;
    float bow_short_curve_y = 0.05f;
	bow_thickness = 0.04f;

   	glBegin(GL_TRIANGLE_STRIP);
    {
        // Draw the bow with varying thickness
        for (int i = 40; i <= 270; i += 5) {
            float angle = i * M_PI / 180.0f;
            float x1 = bow_short_curve_x * sinf(angle);
            float y1 = bow_short_curve_y * cosf(angle);

            float x2 = (bow_short_curve_x + (bow_thickness + (bow_thickness/(180)) * (i - 180)) ) * sinf(angle);
            float y2 = (bow_short_curve_y + (bow_thickness + (bow_thickness/(180)) * (i - 180)) ) * cosf(angle);
            
            // Outer edge (thicker at middle, thinner at ends)
            VFP_2FXY_TXY(x1, y1, percentx, percenty, x_curve, y_curve);
            VFP_2FXY_TXY(x2, y2, percentx, percenty, x_curve, y_curve);
        }
    }
    glEnd();

    glTranslatef(-x_pos, -y_pos, 0.0f);
}

void  mst_drawBow(float x_pos, float y_pos, float percent, float angle) 
{
	// Code
    glTranslatef(x_pos, y_pos, 0.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
	
	 mst_drawBowHalf(VFP(0.5f, percent), y_pos, percent, percent);

	float bow_curve_x = 0.15f;
    float bow_curve_y = 0.03f;
    float bow_thickness = 0.05f;
    
    // Draw bow grip (handle)
	float x_bow_grip = VFP(0.0f, percent);
	float y_bow_grip = VFP(0.49f, percent);

    glBegin(GL_TRIANGLE_STRIP);
    {
        // Draw the bow with varying thickness
        for (int i = 90; i <= 270; i += 5) {
            float angle = i * M_PI / 180.0f;
            float x1 = bow_curve_x * sinf(angle);
            float y1 = bow_curve_y * cosf(angle);

            float x2 = (bow_curve_x + bow_thickness) * sinf(angle);
            float y2 = (bow_curve_y + bow_thickness) * cosf(angle);
            
            // Outer edge (thicker at middle, thinner at ends)
            glVertex2f(VFP(x1, percent) + x_bow_grip, VFP(y1, percent) + y_bow_grip);
            glVertex2f(VFP(x2, percent) + x_bow_grip, VFP(y2, percent) + y_bow_grip);
        }
    }
    glEnd();

     mst_drawBowHalf(VFP(0.5f, -percent), y_pos, -percent, percent);
    glRotatef(angle, 0.0f, 0.0f, -1.0f);
    glTranslatef(-x_pos, -y_pos, 0.0f);
}

void  mst_drawBowString(float x_pos, float y_pos, float percent, float angle, float pull_amount)
{
	// Code
    glTranslatef(x_pos, y_pos, 0.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
	
	// Draw bowstring
    glColor3f(0.9f, 0.9f, 0.9f); // Off-white for string
    glLineWidth(2.0f);
    
    glBegin(GL_LINE_STRIP);
        VFP_2F(-1.25f, 0.15f, percent); // Left tip
        VFP_2F(0.0f, -pull_amount + 0.15f, percent); // Middle (pulled)
        VFP_2F(1.25f, 0.15f, percent); // Right tip
    glEnd();
    
    glRotatef(angle, 0.0f, 0.0f, -1.0f);
    glTranslatef(-x_pos, -y_pos, 0.0f);
}
