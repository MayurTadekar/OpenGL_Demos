#ifndef __FOG_EFFECT_H__
#define __FOG_EFFECT_H__

#include <windows.h>
#include "../../include/vmath.h"
#include <GL/glew.h>
#include <gl/GL.h>

struct FogParameters
{
    BOOL bEnable;
    float fogDensity;
    float fogGradient;
    vmath::vec3 fogColor;
};

extern FogParameters gMountainExteriorSceneFogParams;
extern FogParameters gYuddhaScene1FogParams;
extern FogParameters gRamWorshipSceneFogParams;

BOOL initializeFogSystem(void);
void uninitializeFogSystem(void);
void drawFogVolumeLayer(const FogParameters &params, GLuint sceneDepthTexture, vmath::mat4 projectionMatrix);
void renderFogImGuiControls(void);

#endif
