#pragma once
#include <windows.h>
#include <GL/glew.h>
#include <gl/gl.h>

BOOL initializeFadeSystem(void);
void updateFadeTransitionLogic(float elapsedTime, const float *sceneStartTimes, int totalScenes, float fadeDuration);
void drawFadeOverlay(void);
void uninitializeFadeSystem(void);
void setFadeAlphaManual(float alpha);