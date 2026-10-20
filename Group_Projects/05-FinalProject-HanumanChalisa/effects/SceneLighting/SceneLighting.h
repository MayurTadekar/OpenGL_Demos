#pragma once
#include "../../include/common.h"

typedef struct LightSource
{
    BOOL bEnable; // on / off per light

    vmath::vec3 position; // world-space light position
    vmath::vec3 ambient;  // ambient  contribution (keep low, 0.05-0.1)
    vmath::vec3 diffuse;  // diffuse  color
    vmath::vec3 specular; // specular color
    GLfloat shininess;    // specular exponent  (8-128)
    GLfloat intensity;    // overall multiplier (0.0-3.0)
    GLfloat constant;     // attenuation constant   (default 1.0)
    GLfloat linear;       // attenuation linear     (default 0.09)
    GLfloat quadratic;    // attenuation quadratic  (default 0.032)

} LightSource;

typedef struct SceneLightParams
{
    BOOL bEnableLighting;
    vmath::vec3 cameraPos;

    // 3-points
    LightSource keyLight;  // primary directional — strongest, warm
    LightSource fillLight; // secondary opposite  — soft, cool
    LightSource backLight; // rim / hair light    — behind subject

} SceneLightParams;

BOOL initializeSceneLighting(void);
void applySceneLighting(SceneLightParams &params);
void displaySceneLightingImGui(SceneLightParams &params);
void uninitializeSceneLighting(void);

extern GLuint gLitShaderProgram;

// unifforms
extern GLuint gLitModelMatrixUniform;
extern GLuint gLitViewMatrixUniform;
extern GLuint gLitProjectionMatrixUniform;
extern GLuint gLitTextureSamplerUniform;
extern GLuint gLitClippingPlaneUniform;
extern GLuint gLitCameraPosUniform;
extern GLuint gLitEnableLightingUniform;
