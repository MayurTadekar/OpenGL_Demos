

#include <windows.h>
#include <GL/gl.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include "arrow.h"
#include "mayur_common.h"

// Function to  mst_draw an arrow with details
void  mst_drawArrow(float x_pos, float y_pos, float percent, float angle, float length) 
{
    // Save current matrix

    // Position and rotate the arrow
    glTranslatef(x_pos, y_pos, 0.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    
    // Draw arrow shaft
    glColor3f(  150.0f / 255.0f, 
                75.0f / 255.0f, 
                0.0f / 255.0f); // Red wood color
    glBegin(GL_TRIANGLE_STRIP);
        VFP_2F(-length / 2.0f, -0.02f, percent);
        VFP_2F(-length / 2.0f, 0.02f, percent);
        VFP_2F(length / 2.0f, -0.02f, percent);
        VFP_2F(length / 2.0f, 0.02f, percent);
    glEnd();
    
    // Draw arrow head
    glColor3f(0.6f, 0.6f, 0.6f); // Silver/metal color
    glBegin(GL_TRIANGLES);
        VFP_2F(VFP(length / 2.0f, percent) + 0.05f, 0.0f, percent);    // Tip
        VFP_2F(VFP(length / 2.0f, percent) - 0.05f, -0.06f, percent);  // Bottom corner
        VFP_2F(VFP(length / 2.0f, percent) - 0.05f, 0.06f, percent);   // Top corner
    glEnd();
    
    // Draw arrow fletching (feathers)
    
    float feather_x = -length / 2.0f - 0.3f ;
    glColor3f(0.2f, 0.2f, 0.2f); // Red feathers

    // Right feather
    glBegin(GL_TRIANGLE_STRIP);
        for (int i = 10; i <= 20; i++) {
            float t = i / 10.0f;
            float height = 0.08f * sinf(t * 0.5 * M_PI);
            VFP_2F(VFP(0.2f * t, percent) + feather_x, 0.0f, percent);
            VFP_2F(VFP(0.2f * t, percent) + feather_x, height, percent);
        }
    glEnd();
    
    // Left feather
    glBegin(GL_TRIANGLE_STRIP);
        for (int i = 10; i <= 20; i++) {
            float t = i / 10.0f;
            float height = -0.08f * sinf(t * 0.5 * M_PI);
            VFP_2F(VFP(0.2f * t, percent) + feather_x, 0.0f, percent);
            VFP_2F(VFP(0.2f * t, percent) + feather_x, height, percent);
        }
    glEnd();
    
    glRotatef(angle, 0.0f, 0.0f, -1.0f);
    glTranslatef(-x_pos, -y_pos, 0.0f);


}
