

#include <windows.h>
#include <GL/gl.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include "hand.h"
#include "mayur_common.h"

// Function to  mst_draw a finger with joints using GL_TRIANGLE_STRIP
void  mst_drawFingerWithJoints(float baseX, float baseY, float width, float length, float angle, float percent) {
    float rad = angle * M_PI / 180.0;
    float cosA = cos(rad);
    float sinA = sin(rad);

    width = VFP(width, percent);
    length = VFP(length, percent);
    
    // Calculate segment lengths
    float segment1 = length * 0.4;
    float segment2 = length * 0.3;
    float segment3 = length * 0.3;
    
    // First segment (base of finger)
    float curX = baseX;
    float curY = baseY;
    
    // Store vertices for border  mst_drawing
    float vertices[16][2];
    int vertexCount = 0;
    
    // Base of finger
    vertices[vertexCount][0] = curX - width/2 * cosA + 0.01 * sinA;
    vertices[vertexCount][1] = curY - width/2 * sinA - 0.01 * cosA;
    vertexCount++;
    
    vertices[vertexCount][0] = curX + width/2 * cosA + 0.01 * sinA;
    vertices[vertexCount][1] = curY + width/2 * sinA - 0.01 * cosA;
    vertexCount++;
    
    // First joint
    curX -= segment1 * sinA;
    curY += segment1 * cosA;
    
    vertices[vertexCount][0] = curX - width/2 * cosA;
    vertices[vertexCount][1] = curY - width/2 * sinA;
    vertexCount++;
    
    vertices[vertexCount][0] = curX + width/2 * cosA;
    vertices[vertexCount][1] = curY + width/2 * sinA;
    vertexCount++;
    
    // Second joint (slightly narrower)
    float width2 = width * 0.9;
    curX -= segment2 * sinA;
    curY += segment2 * cosA;
    
    vertices[vertexCount][0] = curX - width2/2 * cosA;
    vertices[vertexCount][1] = curY - width2/2 * sinA;
    vertexCount++;
    
    vertices[vertexCount][0] = curX + width2/2 * cosA;
    vertices[vertexCount][1] = curY + width2/2 * sinA;
    vertexCount++;
    
    // Fingertip (tapered)
    float width3 = width * 0.7;
    curX -= segment3 * sinA;
    curY += segment3 * cosA;
    
    vertices[vertexCount][0] = curX - width3/2 * cosA;
    vertices[vertexCount][1] = curY - width3/2 * sinA;
    vertexCount++;
    
    vertices[vertexCount][0] = curX + width3/2 * cosA;
    vertices[vertexCount][1] = curY + width3/2 * sinA;
    vertexCount++;
    
    // Fingertip point
    curX -= 0.02 * sinA;
    curY += 0.02 * cosA;
    
    vertices[vertexCount][0] = curX;
    vertices[vertexCount][1] = curY;
    vertexCount++;
    
    // Draw the finger fill
    glBegin(GL_TRIANGLE_STRIP);
        for(int i = 0; i < vertexCount; i++) {
            V2F(vertices[i][0], vertices[i][1]);
        }
    glEnd();
    
    // Draw the finger border
    glColor3f(0.0f, 0.0f, 0.0f);  // Black color for border
    glLineWidth(1.5f);
    
    // Draw left side
    glBegin(GL_LINE_STRIP);
        for(int i = 0; i < vertexCount-1; i += 2) {
            V2F(vertices[i][0], vertices[i][1]);
        }
        V2F(vertices[vertexCount-1][0], vertices[vertexCount-1][1]);
    glEnd();
    
    // Draw right side
    glBegin(GL_LINE_STRIP);
        for(int i = 1; i < vertexCount-1; i += 2) {
            V2F(vertices[i][0], vertices[i][1]);
        }
        V2F(vertices[vertexCount-1][0], vertices[vertexCount-1][1]);
    glEnd();
    
    // Connect base
    // glBegin(GL_LINES);
    //     V2F(vertices[0][0], vertices[0][1]);
    //     V2F(vertices[1][0], vertices[1][1]);
    // glEnd();
}

// Function to  mst_draw a long arm using GL_TRIANGLE_STRIP
void  mst_drawArm(float wristX, float wristY, float width, float length, float angle, float percent) {
    float rad = angle * M_PI / 180.0;
    float cosA = cos(rad);
    float sinA = sin(rad);
    
    // Calculate forearm and upper arm lengths
    float forearmLength = length * 0.45;
    float upperArmLength = length * 0.55;
    
    // Wrist position
    float curX = wristX;
    float curY = wristY;
    
    // Store vertices for border  mst_drawing
    float forearmVertices[6][2];
    
    // Wrist
    forearmVertices[0][0] = curX - width/2 * cosA;
    forearmVertices[0][1] = curY - width/2 * sinA;
    
    forearmVertices[1][0] = curX + width/2 * cosA;
    forearmVertices[1][1] = curY + width/2 * sinA;
    
    // Slightly wider in the middle of forearm
    float midX = curX - forearmLength * 0.5 * sinA;
    float midY = curY + forearmLength * 0.5 * cosA;
    float midWidth = width * 1.2;
    
    forearmVertices[2][0] = midX - midWidth/2 * cosA;
    forearmVertices[2][1] = midY - midWidth/2 * sinA;
    
    forearmVertices[3][0] = midX + midWidth/2 * cosA;
    forearmVertices[3][1] = midY + midWidth/2 * sinA;
    
    // Elbow (wider)
    float elbowWidth = width * 1.3;
    curX -= forearmLength * sinA;
    curY += forearmLength * cosA;
    
    forearmVertices[4][0] = curX - elbowWidth/2 * cosA;
    forearmVertices[4][1] = curY - elbowWidth/2 * sinA;
    
    forearmVertices[5][0] = curX + elbowWidth/2 * cosA;
    forearmVertices[5][1] = curY + elbowWidth/2 * sinA;
    
    // Draw forearm
    glBegin(GL_TRIANGLE_STRIP);
        for(int i = 0; i < 6; i++) {
            V2F(forearmVertices[i][0], forearmVertices[i][1]);
        }
    glEnd();
    
    // Store upper arm vertices
    float upperArmVertices[6][2];
    
    // Elbow
    upperArmVertices[0][0] = curX - elbowWidth/2 * cosA;
    upperArmVertices[0][1] = curY - elbowWidth/2 * sinA;
    
    upperArmVertices[1][0] = curX + elbowWidth/2 * cosA;
    upperArmVertices[1][1] = curY + elbowWidth/2 * sinA;
    
    // Middle of upper arm (widest part)
    float upperMidX = curX - upperArmLength * 0.5 * sinA;
    float upperMidY = curY + upperArmLength * 0.5 * cosA;
    float upperMidWidth = width * 1.5;
    
    upperArmVertices[2][0] = upperMidX - upperMidWidth/2 * cosA;
    upperArmVertices[2][1] = upperMidY - upperMidWidth/2 * sinA;
    
    upperArmVertices[3][0] = upperMidX + upperMidWidth/2 * cosA;
    upperArmVertices[3][1] = upperMidY + upperMidWidth/2 * sinA;
    
    // Shoulder (slightly narrower than middle)
    float shoulderWidth = width * 1.4;
    float shoulderX = curX - upperArmLength * sinA;
    float shoulderY = curY + upperArmLength * cosA;
    
    upperArmVertices[4][0] = shoulderX - shoulderWidth/2 * cosA;
    upperArmVertices[4][1] = shoulderY - shoulderWidth/2 * sinA;
    
    upperArmVertices[5][0] = shoulderX + shoulderWidth/2 * cosA;
    upperArmVertices[5][1] = shoulderY + shoulderWidth/2 * sinA;
    
    // Draw upper arm
    glBegin(GL_TRIANGLE_STRIP);
        for(int i = 0; i < 6; i++) {
            V2F(upperArmVertices[i][0], upperArmVertices[i][1]);
        }
    glEnd();
    
    // Draw borders
    glColor3f(0.0f, 0.0f, 0.0f);  // Black color for border
    glLineWidth(1.5f);
    
    // Draw forearm borders
    glBegin(GL_LINE_STRIP);
        for(int i = 0; i < 6; i += 2) {
            V2F(forearmVertices[i][0], forearmVertices[i][1]);
        }
    glEnd();
    
    glBegin(GL_LINE_STRIP);
        for(int i = 1; i < 6; i += 2) {
            V2F(forearmVertices[i][0], forearmVertices[i][1]);
        }
    glEnd();
    
    // Connect wrist
    // glBegin(GL_LINES);
    //     V2F(forearmVertices[0][0], forearmVertices[0][1]);
    //     V2F(forearmVertices[1][0], forearmVertices[1][1]);
    // glEnd();
    
    // Draw upper arm borders
    glBegin(GL_LINE_STRIP);
        for(int i = 0; i < 6; i += 2) {
            V2F(upperArmVertices[i][0], upperArmVertices[i][1]);
        }
    glEnd();
    
    glBegin(GL_LINE_STRIP);
        for(int i = 1; i < 6; i += 2) {
            V2F(upperArmVertices[i][0], upperArmVertices[i][1]);
        }
    glEnd();
    
    // Connect shoulder
    glBegin(GL_LINES);
        V2F(upperArmVertices[4][0], upperArmVertices[4][1]);
        V2F(upperArmVertices[5][0], upperArmVertices[5][1]);
    glEnd();
}

void right_hand(GLfloat x_pos, GLfloat y_pos, GLfloat percent, GLfloat angle)
{
    // Code

    // Transformation
    glTranslatef(x_pos, y_pos, 0.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);

    // Draw the arm first
    glColor3f(0.08f, 0.39f, 0.94f); // Slightly darker than hand for depth
     mst_drawArm(0.0f, VFP(-0.3f, percent), VFP(0.3f, percent), VFP(1.5f, percent), 180.0f, percent);

    // Set skin color
    glColor3f(0.08f, 0.49f, 0.94f);
    
    // Store palm vertices for border  mst_drawing
    float palmVertices[10][2];
    
    // Draw palm using GL_TRIANGLE_STRIP
    glBegin(GL_TRIANGLE_STRIP);
        // Bottom of palm (wrist)
        palmVertices[0][0] = VFP(-0.15f, percent);
        palmVertices[0][1] = VFP(-0.3f, percent);
        VFP_2F(-0.15f, -0.3f, percent);
        
        palmVertices[1][0] = VFP(0.15f, percent);
        palmVertices[1][1] = VFP(-0.3f, percent);
        VFP_2F(0.15f, -0.3f, percent);
        
        // Left side of palm
        palmVertices[2][0] = VFP(-0.18f, percent);
        palmVertices[2][1] = VFP(-0.2f, percent);
        VFP_2F(-0.18f, -0.2f, percent);
        
        palmVertices[3][0] = VFP(0.15f, percent);
        palmVertices[3][1] = VFP(-0.2f, percent);
        VFP_2F(0.15f, -0.2f, percent);
        
        // Middle of palm
        palmVertices[4][0] = VFP(-0.2f, percent);
        palmVertices[4][1] = VFP(-0.1f, percent);
        VFP_2F(-0.2f, -0.1f, percent);
        
        palmVertices[5][0] = VFP(0.155f, percent);
        palmVertices[5][1] = VFP(-0.1f, percent);
        VFP_2F(0.155f, -0.1f, percent);
        
        // Top of palm where fingers connect
        palmVertices[6][0] = VFP(-0.24f, percent);
        palmVertices[6][1] = VFP(0.0f, percent);
        VFP_2F(-0.24f, 0.0f, percent);
        
        palmVertices[7][0] = VFP(0.15f, percent);
        palmVertices[7][1] = VFP(0.0f, percent);
        VFP_2F(0.15f, 0.0f, percent);
        
        // Area where thumb connects
        palmVertices[8][0] = VFP(-0.18f, percent);
        palmVertices[8][1] = VFP(0.1f, percent);
        VFP_2F(-0.18f, 0.1f, percent);
        
        palmVertices[9][0] = VFP(0.15f, percent);
        palmVertices[9][1] = VFP(0.05f, percent);
        VFP_2F(0.15f, 0.05f, percent);
    glEnd();


    // Thumb (different angle)
    glColor3f(0.08f, 0.49f, 0.94f);
     mst_drawFingerWithJoints(VFP(-0.2f, percent), VFP(0.01f, percent), 0.08f, VFP(0.15f, 60), 20.0f, percent);
    
    // Draw palm border
    glColor3f(0.0f, 0.0f, 0.0f);  // Black color for border
    glLineWidth(1.5f);
    
    // Draw left side border
    glBegin(GL_LINE_STRIP);
        for(int i = 0; i < 8; i += 2) 
        {
            V2F(palmVertices[i][0], palmVertices[i][1]);
        }
    glEnd();
    
    // Draw right side border
    glBegin(GL_LINE_STRIP);
        for(int i = 1; i < 10; i += 2) 
        {
            V2F(palmVertices[i][0], palmVertices[i][1]);
        }
    glEnd();
    
    // Reset color for fingers
    glColor3f(0.08f, 0.49f, 0.94f);
    
    // Draw fingers with joints

    const float finger_height_delta = 20.0f;

    // Index finger
    glColor3f(0.08f, 0.49f, 0.94f);
     mst_drawFingerWithJoints(VFP(-0.15f, percent), VFP(0.08f, percent), 0.07f, VFP(0.3f, finger_height_delta), 10.0f, percent);
    
    // Middle finger
    glColor3f(0.08f, 0.49f, 0.94f);
     mst_drawFingerWithJoints(VFP(-0.06f, percent), VFP(0.07f, percent), 0.08f, VFP(0.35f, finger_height_delta), 0.0f, percent);
    
    // Ring finger
    glColor3f(0.08f, 0.49f, 0.94f);
     mst_drawFingerWithJoints(VFP(0.03f, percent), VFP(0.065f, percent), 0.07f, VFP(0.3f, finger_height_delta), -4.0f, percent);
    
    // Pinky finger
    glColor3f(0.08f, 0.49f, 0.94f);
     mst_drawFingerWithJoints(VFP(0.12f, percent), VFP(0.055f, percent), 0.06f, VFP(0.25f, finger_height_delta), -5.0f, percent);

    glRotatef(-angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(-x_pos, -y_pos, 0.0f);
}

void left_hand(GLfloat x_pos, GLfloat y_pos, GLfloat percent, GLfloat angle, float r, float g, float b)
{
    // Code

    // Transformation
    glTranslatef(VFP(x_pos,percent), VFP(y_pos,percent), 0.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);

    // Draw the arm first
    // glColor3f(0.08f, 0.39f, 0.94f); // Slightly darker than hand for depth
    // Slightly darker than hand for depth
    glColor3f(r, g, b);
     mst_drawArm(0.0f, VFP(-0.3f, percent), VFP(0.3f, percent), VFP(1.5f, percent), 180.0f, percent);

    // Set skin color
    // glColor3f(0.94f, 0.75f, 0.64f);
    glColor3f(r, g, b);

    // Store palm vertices for border  mst_drawing
    float palmVertices[10][2];
    
    // Draw palm using GL_TRIANGLE_STRIP
    glBegin(GL_TRIANGLE_STRIP);
        // Bottom of palm (wrist)
        palmVertices[0][0] = VFP(-0.15f, percent);
        palmVertices[0][1] = VFP(-0.3f, percent);
        VFP_2F(-0.15f, -0.3f, percent);
        
        palmVertices[1][0] = VFP(0.15f, percent);
        palmVertices[1][1] = VFP(-0.3f, percent);
        VFP_2F(0.15f, -0.3f, percent);
        
        // Left side of palm
        palmVertices[2][0] = VFP(-0.18f, percent);
        palmVertices[2][1] = VFP(-0.2f, percent);
        VFP_2F(-0.18f, -0.2f, percent);
        
        palmVertices[3][0] = VFP(0.15f, percent);
        palmVertices[3][1] = VFP(-0.2f, percent);
        VFP_2F(0.15f, -0.2f, percent);
        
        // Middle of palm
        palmVertices[4][0] = VFP(-0.2f, percent);
        palmVertices[4][1] = VFP(-0.1f, percent);
        VFP_2F(-0.2f, -0.1f, percent);
        
        palmVertices[5][0] = VFP(0.155f, percent);
        palmVertices[5][1] = VFP(-0.1f, percent);
        VFP_2F(0.155f, -0.1f, percent);
        
        // Top of palm where fingers connect
        palmVertices[6][0] = VFP(-0.2f, percent);
        palmVertices[6][1] = VFP(0.0f, percent);
        VFP_2F(-0.2f, 0.0f, percent);
        
        palmVertices[7][0] = VFP(0.15f, percent);
        palmVertices[7][1] = VFP(0.0f, percent);
        VFP_2F(0.15f, 0.0f, percent);
        
        // Area where thumb connects
        palmVertices[8][0] = VFP(-0.18f, percent);
        palmVertices[8][1] = VFP(0.1f, percent);
        VFP_2F(-0.18f, 0.1f, percent);
        
        palmVertices[9][0] = VFP(0.15f, percent);
        palmVertices[9][1] = VFP(0.05f, percent);
        VFP_2F(0.15f, 0.05f, percent);
    glEnd();
    
    // Draw palm border
    glColor3f(0.0f, 0.0f, 0.0f);  // Black color for border
    glLineWidth(1.5f);
    
    // Draw left side border
    glBegin(GL_LINE_STRIP);
        for(int i = 0; i < 10; i += 2) {
            V2F(palmVertices[i][0], palmVertices[i][1]);
        }
    glEnd();
    
    // Draw right side border
    glBegin(GL_LINE_STRIP);
        for(int i = 1; i < 10; i += 2) {
            V2F(palmVertices[i][0], palmVertices[i][1]);
        }
    glEnd();
    
    // Draw fingers with joints

    const float finger_height_delta = 100.0f;

    // Index finger
    glColor3f(r, g, b);
     mst_drawFingerWithJoints(VFP(-0.15f, percent), VFP(0.04f, percent), 0.07f, VFP(0.3f, 20.0f), 0.0f, percent);
    
    // Middle finger
    glColor3f(r, g, b);
     mst_drawFingerWithJoints(VFP(-0.06f, percent), VFP(0.05f, percent), 0.08f, VFP(0.35f, 20.0f), 0.0f, percent);
    
    // Ring finger
    glColor3f(r, g, b);
     mst_drawFingerWithJoints(VFP(0.03f, percent), VFP(0.03f, percent), 0.07f, VFP(0.3f, 20.0f), -4.0f, percent);
    
    // Pinky finger
    glColor3f(r, g, b);
     mst_drawFingerWithJoints(VFP(0.12f, percent), VFP(0.02f, percent), 0.06f, VFP(0.25f, 20.0f), -5.0f, percent);

    // Thumb (different angle)
    glColor3f(r, g, b);
     mst_drawFingerWithJoints(VFP(-0.18f, percent), VFP(0.01f, percent), 0.08f, VFP(0.15f, 150), -90.0f, percent);

    glRotatef(-angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(VFP(-x_pos,percent), VFP(-y_pos,percent), 0.0f);
}