


#include <windows.h>
#include <GL/gl.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include "hand.h"
#include "ravan.h"
#include "mayur_common.h"

GLfloat mst_eka_tondache_10_kar = 0.0f;
BOOL mst_ravan_ghabarla = FALSE;

// Function to  mst_draw a circle using triangle fan
void  mst_drawCircle(float cx, float cy, float rx, float ry, int start, int end, int segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy); // Center point
    for (int i = start; i <= end; i++) {
        float theta = 2.0f * M_PI * i / segments;
        float x = cx + rx * cosf(theta);
        float y = cy + ry * sinf(theta);
        glVertex2f(x, y);
    }
    glEnd();
}


// Function to  mst_draw a circle using triangle fan
void  mst_drawCircleWithLine(float cx, float cy, float rx, float ry, int start, int end, int segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy); // Center point
    for (int i = start; i <= end; i++) {
        float theta = 2.0f * M_PI * i / segments;
        float x = cx + rx * cosf(theta);
        float y = cy + ry * sinf(theta);
        glVertex2f(x, y);
    }
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
    for (int i = start; i <= end; i++) {
        float theta = 2.0f * M_PI * i / segments;
        float x = cx + rx * cosf(theta);
        float y = cy + ry * sinf(theta);
        glVertex2f(x, y);
    }
    glEnd();
}


// Function to  mst_draw a circle using triangle fan
void  mst_drawCurve(float cx, float cy, float rx, float ry, float thickness, int start, int end, int segments) 
{
    glBegin(GL_TRIANGLE_STRIP);

    for (int i = start; i < end; i++) {
        float theta = 2.0f * M_PI * i / segments;
        float x = cx + rx * cosf(theta);
        float y = cy + ry * sinf(theta);
        glVertex2f(x, y);

        x = cx + (rx + thickness) * cosf(theta);
        y = cy + (ry + thickness) * sinf(theta);
        glVertex2f(x, y);
    }
    glEnd();
}


// Function to  mst_draw a circle using triangle fan
void  mst_drawCurveReduceThickness(float cx, float cy, float rx, float ry, float thickness, int start, int end, int segments) 
{
    glBegin(GL_TRIANGLE_STRIP);

    for (int i = start; i < end; i++) {
        float theta = 2.0f * M_PI * i / segments;
        float x = cx + rx * cosf(theta);
        float y = cy + ry * sinf(theta);
        glVertex2f(x, y);

        float thickness_delta = (thickness / (end-start) ) * (end - i );

        x = cx + (rx + thickness_delta) * cosf(theta);
        y = cy + (ry + thickness_delta) * sinf(theta);
        glVertex2f(x, y);
    }
    glEnd();
}

// Function to  mst_draw face outline
void  mst_drawFaceOutline(float centerX, float centerY, float radiusX, float radiusY) {
    glColor3f(0.94f, 0.75f, 0.55f); // Skin color
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX, centerY);
    for (int i = 0; i <= 360; i++) {
        float angle = i * M_PI / 180;
        glVertex2f(centerX + cos(angle) * radiusX, centerY + sin(angle) * radiusY);
    }
    glEnd();
}

// Function to  mst_draw an eye with details
void  mst_drawEye(float x, float y, float size) {
    // White of the eye
    glColor3f(1.0f, 1.0f, 1.0f);
     mst_drawCircleWithLine(x, y, size, VFP(size, 40), 0, 360, 360);

    // Iris
    // glColor3f(0.2f, 0.2f, 0.8f);
    //  mst_drawCircle(x, y, size * 0.5f, VFP(size, 40), 360);

    // Pupil
    glColor3f(0.0f, 0.0f, 0.0f);
     mst_drawCircle(x, y, VFP(size, 30), VFP(size, 30), 0, 360,  360);
}

// Function to  mst_draw a mustache with more detail
void  mst_drawMustache(float centerX, float centerY, float width) {
    glColor3f(0.0f, 0.0f, 0.0f); // Black color for mustache
    glBegin(GL_TRIANGLES);
    
    // Left side of mustache
    glVertex2f(centerX - width / 2, centerY);
    glVertex2f(centerX - width / 4, centerY - width / 8);
    glVertex2f(centerX - width / 4 - width / 10, centerY - width / 16);

    // Right side of mustache
    glVertex2f(centerX + width / 4 + width / 10, centerY - width / 16);
    glVertex2f(centerX + width / 4, centerY - width / 8);
    glVertex2f(centerX + width / 2, centerY);

    glEnd();
}

// Function to  mst_draw ears with more detail
void  mst_drawEar(float x, float y, float size) {
    // Outer ear shape
    glColor3f(0.94f, 0.75f, 0.55f); // Skin color
    glBegin(GL_TRIANGLES);
        glVertex2f(x - size / 2, y + size); // Top corner
        glVertex2f(x + size / 2, y + size); // Bottom corner
        glVertex2f(x - size / 4 + size / 10, y); // Inner corner
    glEnd();

    // Inner ear detail (curve)
    glColor3f(1.0f, 1.0f, 1.0f); // Light color inside ear
     mst_drawCircle(x - size / 4 + size / 10, y + size / 5, size / 5, size / 5, 0, 20, 20);
}


// Function to  mst_draw lips (mouth)
void  mst_drawLips(float x, float y, float width, float height) {
    glColor3f(0.8f, 0.2f, 0.2f); // Reddish color for lips
    
    // Upper lip
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= 180; i += 5) {
        float angle = i * M_PI / 180.0f;
        float x1 = x + width * 0.5f * cosf(angle);
        float y1 = y + height * 0.25f * sinf(angle);
        glVertex2f(x1, y1);
        glVertex2f(x1, y1 - height * 0.1f);
    }
    glEnd();

    // Lower lip
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= 180; i += 5) {
        float angle = i * M_PI / 180.0f;
        float x1 = x + width * 0.5f * cosf(angle);
        float y1 = y - height * 0.25f * sinf(angle);
        glVertex2f(x1, y1);
        glVertex2f(x1, y1 + height * 0.1f);
    }
    glEnd();
}

// Function to  mst_draw nose
void  mst_drawNose(float x, float y, float size) {
    glColor3f(0.9f, 0.7f, 0.5f); // Slightly darker than skin color
    
    glBegin(GL_TRIANGLES);
    glVertex2f(x, y);
    glVertex2f(x - size * 0.3f, y - size);
    glVertex2f(x + size * 0.3f, y - size);
    glEnd();

    // Nostrils
    glColor3f(0.6f, 0.4f, 0.3f);
     mst_drawCircle(x - size * 0.15f, y - size * 0.8f, size * 0.1f, size * 0.1f, 0, 20, 20);
     mst_drawCircle(x + size * 0.15f, y - size * 0.8f, size * 0.1f, size * 0.1f, 0, 20, 20);
}

// Function to  mst_draw a more detailed crown
void  mst_drawCrown(float centerX, float centerY, float width, float height) {
    glColor3f(1.0f, 0.84f, 0.0f); // Gold color

    // Base of the crown
     mst_drawCircleWithLine(centerX, centerY, VFP(width, 60), VFP(height, 20), 180, 360, 360);

    glColor3f(1.0f, 0.84f, 0.0f); // Gold color
     mst_drawCircleWithLine(centerX + VFP(width, -5), centerY + VFP(height, 200), VFP(width, 10), VFP(height, 200), 0, 60, 360);
    glColor3f(1.0f, 0.84f, 0.0f); // Gold color
     mst_drawCircleWithLine(centerX + VFP(width, 5), centerY + VFP(height, 200), VFP(width, 10), VFP(height, 200), 180-60, 180, 360);

    glColor3f(1.0f, 0.84f, 0.0f); // Gold color
     mst_drawCircleWithLine(centerX, centerY, VFP(width, 50), VFP(height, 250), 0, 180, 360);

    glColor3f(1.0f, 0.84f, 0.0f); // Gold color
     mst_drawCircleWithLine(centerX, centerY, VFP(width, 60), VFP(height, 200), 0, 180, 360);

    glColor3f(1.0f, 0.84f, 0.0f); // Gold color
     mst_drawCircleWithLine(centerX, centerY, VFP(width, 60), VFP(height, 50), 0, 180, 360);

	glTranslatef(0.0f, -0.4f, 0.0f);    
    glColor3f(1.0f, 0.84f, 0.0f); // Gold color
     mst_drawCircleWithLine(centerX + VFP(width, -5), centerY + VFP(height, 200), VFP(width, 10), VFP(height, 180), 0, 60, 360);

    glColor3f(1.0f, 0.84f, 0.0f); // Gold color
     mst_drawCircleWithLine(centerX + VFP(width, 5), centerY + VFP(height, 200), VFP(width, 10), VFP(height, 180), 180-60, 180, 360);
	glTranslatef(0.0f, 0.4f, 0.0f);    

    glColor3f(1.0f, 0.0f, 0.0f); // Red jewels
     mst_drawCircleWithLine(centerX, centerY + VFP(height, 70), VFP(0.1f, 80), VFP(0.1f, 100), 0, 20, 20);

    // // Crown spikes
    // for (int i = 0; i < 5; i++) {
    //     float x = centerX - width * 0.4f + i * width * 0.2f;
    //     glBegin(GL_TRIANGLES);
    //     glVertex2f(x, centerY + height * 0.3f);
    //     glVertex2f(x - width * 0.05f, centerY + height);
    //     glVertex2f(x + width * 0.05f, centerY + height);
    //     glEnd();
    // }
}

// Updated  mst_drawFace function with more details
void  mst_drawFace() {
    // Face outline
    //  mst_drawFaceOutline(0, 0, 0.8f, 1.0f);

    glColor3f(0.94f, 0.75f, 0.55f); // Skin color
     mst_drawCircleWithLine(0.0f, 0.05f, VFP(1.0f, 70.0f), VFP(1.0f, 70.0f), 0, 360, 360);
    glColor3f(0.94f, 0.75f, 0.55f); // Skin color
     mst_drawCircleWithLine(0.0f, 0.1f, VFP(1.0f, 70.0f), VFP(1.0f, 400.0f), 0, 10, 360);
    glColor3f(0.94f, 0.75f, 0.55f); // Skin color
     mst_drawCircleWithLine(0.0f, 0.1f, VFP(1.0f, 70.0f), VFP(1.0f, 400.0f), 170, 180, 360);
    
    // Eyes
    
    glColor3f(0.0f, 0.0f, 0.0f); // Black

    glTranslatef(-0.45f, 0.3f + VFP(0.15f, 30), 0.0f);
    if(mst_ravan_ghabarla)
        glRotatef(15.0f, 0.0f, 0.0f, 1.0f);
    else
        glRotatef(-15.0f, 0.0f, 0.0f, 1.0f);
     mst_drawCurveReduceThickness(0.0f, 0.0f, VFP(0.15f, 200), VFP(0.15f, 90), 0.05f, 30, 120, 360);
	if(mst_ravan_ghabarla)
        glRotatef(-15.0f, 0.0f, 0.0f, 1.0f);
    else
        glRotatef(15.0f, 0.0f, 0.0f, 1.0f);
    glTranslatef(+0.45f, -(0.3f + VFP(0.15f, 30)), 0.0f);
	 mst_drawEye(-0.35f, 0.3f, 0.15f);
    
    glScalef(-1.0f, 1.0f, 1.0f);
    glTranslatef(-0.45f, 0.3f + VFP(0.15f, 30), 0.0f);
    if(mst_ravan_ghabarla)
        glRotatef(15.0f, 0.0f, 0.0f, 1.0f);
    else
        glRotatef(-15.0f, 0.0f, 0.0f, 1.0f);
     mst_drawCurveReduceThickness(0.0f, 0.0f, VFP(0.15f, 200), VFP(0.15f, 90), 0.05f, 30, 120, 360);
	if(mst_ravan_ghabarla)
        glRotatef(-15.0f, 0.0f, 0.0f, 1.0f);
    else
        glRotatef(15.0f, 0.0f, 0.0f, 1.0f);
    glTranslatef(+0.45f, -(0.3f + VFP(0.15f, 30)), 0.0f);
	glScalef(-1.0f, 1.0f, 1.0f);
     mst_drawEye(0.35f, 0.3f, 0.15f);
    
    // Nose
    //  mst_drawNose(0.0f, 0.0f, 0.2f);
     mst_drawCurve(0.0f, 0.0f, VFP(0.1f, 40), VFP(0.1f, 20), 0.02f, 180, 360, 360);
     mst_drawCurve(0.0f, 0.0f, VFP(0.1f, 40), VFP(0.1f, 400), 0.02f, 100, 182, 360);

    // Mustache
     mst_drawCurve(0.0f, -0.2f, VFP(0.1f, 250), VFP(0.1f, 100), 0.08f, 20, 100, 360);
     mst_drawCurve(0.52f, -0.062f, VFP(0.1f, 250), VFP(0.1f, 140), 0.08f, 205, 264, 360);
     mst_drawCurveReduceThickness(0.52, -0.075f, VFP(0.1f, 200), VFP(0.1f, 130), 0.08f, 260, 360, 360);

    glScalef(-1.0f, 1.0f, 1.0f);
     mst_drawCurve(0.0f, -0.2f, VFP(0.1f, 250), VFP(0.1f, 100), 0.08f, 20, 100, 360);
     mst_drawCurve(0.52f, -0.062f, VFP(0.1f, 250), VFP(0.1f, 140), 0.08f, 205, 264, 360);
     mst_drawCurveReduceThickness(0.52, -0.075f, VFP(0.1f, 200), VFP(0.1f, 130), 0.08f, 260, 360, 360);
    glScalef(-1.0f, 1.0f, 1.0f);
    
    // Lips
    if(mst_ravan_ghabarla)
    {        
        glColor3f(1.0f, 1.0f, 1.0f);
         mst_drawCircleWithLine(0.0f, -0.3f, VFP(0.1f, 150), VFP(0.1f, 150), 0, 360, 360);
    }
    else
    {
         mst_drawCurve(0.0f, -0.3f, VFP(0.1f, 300), VFP(0.1f, 50), 0.03f, 90 - 30, 90 + 30, 360);
    }

    // Crown
     mst_drawCrown(0, 0.6f, 1.2f, 0.3f);
}


void  mst_drawRavana10Face()
{
    // Code

    for(int le = 5; le < 10; ++le)
    {
        float x_pos = mst_eka_tondache_10_kar * (14-le) - (mst_eka_tondache_10_kar * 4);
        glTranslatef(x_pos, -0.1f, 0.0f);
         mst_drawFace();
        glTranslatef(-x_pos, 0.1f, 0.0f);
    }

    for(int le = 0; le < 5; ++le)
    {
        float x_pos = mst_eka_tondache_10_kar * le - (mst_eka_tondache_10_kar * 4) ;
        glTranslatef(x_pos, -0.1f, 0.0f);
         mst_drawFace();
        glTranslatef(-x_pos, 0.1f, 0.0f);
    }
}

// Function to  mst_draw an anatomically accurate neck
void  mst_drawNeck(float centerX, float centerY, float width, float height, float skinToneR, float skinToneG, float skinToneB) {
    // Base skin color
    float baseColorR = skinToneR;
    float baseColorG = skinToneG;
    float baseColorB = skinToneB;
    
    // Slightly darker shading color for muscle definition
    float shadeColorR = baseColorR * 0.9f;
    float shadeColorG = baseColorG * 0.9f;
    float shadeColorB = baseColorB * 0.9f;
    
    // Main neck cylinder
    glColor3f(0.94f, 0.75f, 0.55f); // Skin color
	glBegin(GL_TRIANGLE_STRIP);
        // Front of neck is slightly curved
        for (int i = -90; i <= 90; i += 10) {
            float angle = i * M_PI / 180.0f;
            float x_offset = cosf(angle) * width * 0.5f;
            
            // Top of neck (narrower where it meets the head)
            glVertex2f(centerX + x_offset, centerY + height);
            
            // Bottom of neck (wider where it meets the shoulders)
            glVertex2f(centerX + x_offset, centerY);
        }
    glEnd();


    glColor3f(0.94f, 0.75f, 0.55f); // Skin color
     mst_drawCircleWithLine(0.0f, centerY, VFP(0.1f, 350.0f), VFP(0.1f, 100.0f), 180, 360, 360);

    // Reset line width
    glLineWidth(1.0f);
}

// Function to  mst_draw body/torso
void  mst_drawBody(float centerX, float centerY, float width, float height) 
{
    
	glRotatef(180.0f, 0.0f, 0.0f, 1.0f);

    // Upper torso
    glColor3f(0.94f, 0.75f, 0.55f); // Skin color
    glBegin(GL_TRIANGLE_STRIP);
        glVertex2f(centerX - width * 0.5f, VFP(centerY, 100.0f));
        glVertex2f(centerX + width * 0.5f, VFP(centerY, 100.0f));
        glVertex2f(centerX - width * 0.35f, centerY + height * 0.3f);
        glVertex2f(centerX + width * 0.35f, centerY + height * 0.3f);
    glEnd();

    glColor3f(0.94f, 0.75f, 0.55f); // Skin color
     mst_drawCircleWithLine(VFP(width, -34.0f), VFP(centerY, 119.0f), VFP(1.0f, 80.0), VFP(1.0f, 30.0), 195, 270, 360);

    glColor3f(0.94f, 0.75f, 0.55f); // Skin color
     mst_drawCircleWithLine(VFP(width, -34.0f), VFP(centerY, 119.0f), VFP(1.0f, 150.0), VFP(1.0f, 30.0), 270, 330, 360);

    glScalef(-1.0f, 1.0f, 1.0f);
    glColor3f(0.94f, 0.75f, 0.55f); // Skin color
     mst_drawCircleWithLine(VFP(width, -34.0f), VFP(centerY, 119.0f), VFP(1.0f, 150.0), VFP(1.0f, 30.0), 270, 330, 360);
    glColor3f(0.94f, 0.75f, 0.55f); // Skin color
     mst_drawCircleWithLine(VFP(width, -34.0f), VFP(centerY, 119.0f), VFP(1.0f, 80.0), VFP(1.0f, 30.0), 195, 270, 360);
    glScalef(-1.0f, 1.0f, 1.0f);

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
        glVertex2f(centerX - width * 0.35f, centerY + height * 0.3f);
        glVertex2f(centerX - VFP(width, 44.0f), VFP(centerY, 200.0f));
        glVertex2f(centerX + VFP(width, 44.0f), VFP(centerY, 200.0f));
        glVertex2f(centerX + width * 0.35f, centerY + height * 0.3f);
    glEnd();
    
    // Lower torso
    glColor3f(0.94f, 0.75f, 0.55f); // Skin color
    glBegin(GL_TRIANGLE_STRIP);
        glVertex2f(centerX - width * 0.35f, centerY + height * 0.3f);
        glVertex2f(centerX + width * 0.35f, centerY + height * 0.3f);
        glVertex2f(centerX - width * 0.3f, centerY + height * 0.5f);
        glVertex2f(centerX + width * 0.3f, centerY + height * 0.5f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
        glVertex2f(centerX + width * 0.35f, centerY + height * 0.3f);
        glVertex2f(centerX + width * 0.3f, centerY + height * 0.5f);
        glVertex2f(centerX - width * 0.3f, centerY + height * 0.5f);
        glVertex2f(centerX - width * 0.35f, centerY + height * 0.3f);
    glEnd();
    
    // Armor (chest plate)
    glColor3f(0.8f, 0.65f, 0.1f); // Gold color
    glBegin(GL_TRIANGLE_STRIP);
        glVertex2f(centerX - width * 0.45f, centerY + height * 0.05f);
        glVertex2f(centerX + width * 0.45f, centerY + height * 0.05f);
        glVertex2f(centerX - width * 0.35f, centerY + height * 0.25f);
        glVertex2f(centerX + width * 0.35f, centerY + height * 0.25f);
    glEnd();
  
    // Central chest jewel
    glColor3f(0.9f, 0.1f, 0.1f); // Red
     mst_drawCircle(centerX, centerY + height * 0.15f, width * 0.08f, width * 0.08f, 0, 20, 20);

    glColor3f(0.2f, 0.1f, 0.1f); // Red
     mst_drawCircle(centerX, centerY + height * 0.45f, width * 0.01f, width * 0.01f, 0, 20, 20);
    
	glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
}

void  mst_drawLowerBody(float centerX, float centerY, float width, float height)
{
	// Belt/waistband
	glRotatef(180.0f, 0.0f, 0.0f, 1.0f);

    glColor3f(0.70f, 0.065f, 0.095f);
     mst_drawCircleWithLine(VFP(width, 28.5f), centerY + height * 0.36f, VFP(width, 40.0f), VFP(height, 60.0f), 75, 180, 360);

    glRotatef(7.0f, 0.0f, 0.0f, -1.0f);
    glColor3f(0.70f, 0.065f, 0.095f);
     mst_drawCircleWithLine(VFP(width, 12.0f), centerY + VFP(height, 105.0f) * 0.36f, VFP(width, 4.0f), VFP(height, 60.0f), 0, 80, 360);
    glRotatef(7.0f, 0.0f, 0.0f, 1.0f);

    glColor3f(0.70f, 0.065f, 0.095f);
     mst_drawCircleWithLine(VFP(-width, 30.0f), centerY + height * 0.36f, VFP(width, 45.0f), VFP(height, 60.0f), 0, 100, 360);

    glRotatef(7.0f, 0.0f, 0.0f, 1.0f);
    glColor3f(0.70f, 0.065f, 0.095f);
     mst_drawCircleWithLine(VFP(-width, 12.0f), centerY + VFP(height, 105.0f) * 0.36f, VFP(width, 4.0f), VFP(height, 60.0f), 80, 180, 360);
    glRotatef(7.0f, 0.0f, 0.0f, -1.0f);

    glColor3f(0.07f, 0.0f, 0.0f); // Red color
     mst_drawCircleWithLine(0.0f, centerY + height * 0.36f, VFP(width, 32.0f), VFP(0.1f, 100.0f), 0, 180, 360);

	glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
}

// Function to  mst_draw a sword
void  mst_drawSword(float handX, float handY, float length, float width, float angle) 
{

    glTranslatef(handX, handY, 0.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);

    // Handle and blade proportions
    float handleLength = length * 0.3f;
    float bladeLength = length * 0.7f;
    
    // Handle end position
    float handleEndX = handX + handleLength;
    float handleEndY = handY + handleLength;
    
    // Blade tip position
    float tipX = handleEndX + bladeLength;
    float tipY = handleEndY + bladeLength;
    
    // Draw handle
    glColor3f(0.5f, 0.3f, 0.0f); // Brown handle
    glBegin(GL_TRIANGLE_STRIP);
        glVertex2f(length/3.0f, width/5.0f);
        glVertex2f(length/3.0f, -width/5.0f);
        glVertex2f(-length/10.0f, width/5.0f);
        glVertex2f(-length/10.0f, -width/5.0f);
    glEnd();
    
    // Draw blade
    glColor3f(0.8f, 0.8f, 0.9f); // Silver blade
    glTranslatef(1.5f, -1.5f, 0.0f);
    glBegin(GL_TRIANGLE_STRIP);
    {
        for(int le = 0; le <= 90; ++le)
        {
            float angle = 2.0f * M_PI * le / 360.0f;

            glVertex2f(VFP(length, 80) * sinf(angle), VFP(width, 200) * cosf(angle));
            glVertex2f(VFP(length, 80) * sinf(angle), VFP(width, 400) * cosf(angle));
        }
    }
    glEnd();
    glTranslatef(-1.5f, 1.5f, 0.0f);
    
    // Draw guard (cross-piece)
    glColor3f(0.8f, 0.65f, 0.1f); // Gold
    glBegin(GL_TRIANGLE_STRIP);
        glVertex2f(length/3.0f, width * 1.3f);
        glVertex2f(length/3.0f, -width * 1.3f);
        glVertex2f(length/4.0f, width * 1.3f);
        glVertex2f(length/4.0f, -width * 1.3f);
    glEnd();
    
    glRotatef(-angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(-handX, -handY, 0.0f);

}

// Function to  mst_draw a round shield
void  mst_drawShield(float handX, float handY, float radius, float angle) {
    float rad = angle * M_PI / 180.0f;
    float cosA = cosf(rad);
    float sinA = sinf(rad);
    
    // Shield center position (offset from hand)
    float shieldX = handX + radius * 0.3f * cosA;
    float shieldY = handY + radius * 0.3f * sinA;
    
    // Draw main shield body
    glColor3f(0.2f, 0.2f, 0.2f); // Red shield
     mst_drawCircle(shieldX, shieldY, radius, radius, 0, 30, 30);
    
    // Draw inner shield circle
    glColor3f(0.8f, 0.65f, 0.1f); // Gold
     mst_drawCircle(shieldX, shieldY, radius * 0.8f, radius * 0.2f, 0, 30, 30);
    
    // Draw central shield boss
    glColor3f(0.8f, 0.8f, 0.9f); // Silver
     mst_drawCircle(shieldX, shieldY, radius * 0.2f, radius * 0.2f, 0, 20, 20);
    
    // Draw decorative patterns
    glLineWidth(2.0f);
    glColor3f(0.7f, 0.7f, 0.7f); // Red
    glBegin(GL_LINES);
        for (int i = 0; i < 8; i++) {
            float a = i * M_PI / 4.0f;
            glVertex2f(shieldX + radius * 0.3f * cosf(a), 
                      shieldY + radius * 0.3f * sinf(a));
            glVertex2f(shieldX + radius * 0.7f * cosf(a), 
                      shieldY + radius * 0.7f * sinf(a));
        }
    glEnd();
    glLineWidth(1.0f);
}

// Function to  mst_draw a single leg
void  mst_drawSingleLeg(float offsetX, float centerX, float centerY, BOOL isLeft, float skinToneR, float skinToneG, float skinToneB, float width, float height) 
{
    // Base skin color
    float baseColorR = skinToneR;
    float baseColorG = skinToneG;
    float baseColorB = skinToneB;
    
    // Slightly darker shading color for muscle definition
    float shadeColorR = baseColorR * 0.9f;
    float shadeColorG = baseColorG * 0.9f;
    float shadeColorB = baseColorB * 0.9f;

    float kneeY = centerY - VFP(height, -20);
    float ankleY = centerY - VFP(height, 50);

    // // Knee
    // glColor3f(baseColorR, baseColorG, baseColorB);
    //  mst_drawCircle(centerX + offsetX, kneeY, width * 0.2f, width * 0.2f, 0, 20, 20);
    
    // Calf
    glBegin(GL_TRIANGLE_STRIP);
        for (int i = 0; i <= 180; i += 10) {
            float angle = i * M_PI / 180.0f;
            float x = centerX + offsetX + cosf(angle) * width * 0.2f;
            
            glColor3f(baseColorR, baseColorG, baseColorB);
            glVertex2f(x, kneeY);
            
            glColor3f(shadeColorR, shadeColorG, shadeColorB);
            glVertex2f(x * 0.95f + (centerX + offsetX) * 0.05f, ankleY);
        }
    glEnd();
    
    // // Ankle
    // glColor3f(baseColorR, baseColorG, baseColorB);
    //  mst_drawCircle(centerX + offsetX, ankleY, width * 0.15f, 20);
    
    // Foot
    
    glColor3f(150.0f / 255.0f, 75.0f / 255.0f, 0);
     mst_drawCircleWithLine(VFP(width, 1), VFP(height, -155.0f), VFP(width, 8.0f), VFP(height, 5.0f), 90, 180, 360);
    glColor3f(150.0f / 255.0f, 75.0f / 255.0f, 0);
     mst_drawCircleWithLine(VFP(width, 1), VFP(height, -155.0f), VFP(width, 50.0f), VFP(height, 5.0f), 0, 90, 360);
    glColor3f(150.0f / 255.0f, 75.0f / 255.0f, 0);
     mst_drawCircleWithLine(VFP(width, 1), VFP(height, -155.0f), VFP(width, 8.0f), VFP(height, 1.0f), 180, 270, 360);
    glColor3f(150.0f / 255.0f, 75.0f / 255.0f, 0);
     mst_drawCircleWithLine(VFP(width, 1), VFP(height, -155.0f), VFP(width, 50.0f), VFP(height, 1.0f), 270, 360, 360);
}


void  mst_drawLegs(float centerX, float centerY, float width, float height, float skinToneR, float skinToneG, float skinToneB) 
{
    glRotatef(4.0f, 0.0f, 0.0f, 1.0f);
     mst_drawSingleLeg(VFP(width, 10.0f), centerX, centerY, FALSE, skinToneR, skinToneG, skinToneB, width, height);
    glRotatef(4.0f, 0.0f, 0.0f, -1.0f);
    glRotatef(4.0f, 0.0f, 0.0f, -1.0f);
    glScalef(-1.0f, 1.0f, 1.0f);
     mst_drawSingleLeg(VFP(width, 10.0f), centerX, centerY, TRUE, skinToneR, skinToneG, skinToneB, width, height);
    glScalef(-1.0f, 1.0f, 1.0f);
    glRotatef(4.0f, 0.0f, 0.0f, 1.0f);
}

// Function to  mst_draw complete Ravana
void  mst_drawRavana(float x, float y, float scale) 
{
    
    glTranslatef(x, y, 0.0f);
    
    glPushMatrix();
    glScalef(scale, scale, 1.0f);

    float headRadius = 0.4f;
    float neckWidth = headRadius * 0.6f;
    float neckHeight = headRadius * 0.3f;
    float bodyWidth = headRadius * 10.0f;
    float bodyHeight = headRadius * 20.0f;
    
    // Draw legs
     mst_drawLegs(0.0f, VFP(bodyHeight, -90), VFP(VFP(bodyWidth, 60.0f), 100.0f), VFP(bodyHeight * 0.9f, 100.0f), 0.94f, 0.75f, 0.55f);

    left_hand(2.08f, -2.0f, 200.0f, -138.0f, 0.94f, 0.75f, 0.55f);    
    glScalef(-1.0f, 1.0f, 1.0f);
    left_hand(2.08f, -2.0f, 200.0f, -138.0f, 0.94f, 0.75f, 0.55f);    
    glScalef(-1.0f, 1.0f, 1.0f);

    // glScalef(0.4f, 0.4f, 1.0f);
     mst_drawSword(-3.5f, -4.5f, 5.0f, 0.5f, 140.0f); 
    //  mst_drawSword(0.0f, 0.0f, 5.0f, 0.5f, 0.0f); 
    // glScalef(2.0f, 2.0f, 1.0f);

     mst_drawShield(3.5f, -3.6f, 1.4f, 0.0f);

    // Draw body
     mst_drawBody(0.0f, 1.0f, bodyWidth, bodyHeight);
     mst_drawLowerBody(0.0f, 2.5f, bodyWidth, bodyHeight * 0.8f);

     mst_drawNeck(-0.35f, -0.97f, 1.4f, 0.35f, 0.94f, 0.75f, 0.55f);

     mst_drawRavana10Face();

    glPopMatrix();
    glTranslatef(-x, -y, 0.0f);
}
