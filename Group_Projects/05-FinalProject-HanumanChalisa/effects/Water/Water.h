#pragma once
#include "../include/common.h"
#include "../modules/Camera/Camera.h"

// struct declaration
typedef struct WaterParams
{
    vmath::vec3 translation;
    vmath::vec3 scale;

    GLfloat titling;
    GLfloat waveStrength;
    GLfloat moveFactor;

    vmath::vec3 tintColor;
    GLfloat tintFactor;

    // New directional controls
    vmath::vec2 waterDirection;   // Example: (1,0), (0,1), (1,0.3)
    GLint movementMode;           // 0 = original mode, 1 = directional mode

} WaterParams;

// function declaration
BOOL initializeWater(GLuint reflectionTexture, GLuint refractionTexture, GLuint refractionDepthTexture, GLuint dudvMapTexture);
void renderWater(WaterParams params, Camera *pCamera, vmath::mat4 projectionMatrix);
void uninitializeWater(void);
void updateWater();
