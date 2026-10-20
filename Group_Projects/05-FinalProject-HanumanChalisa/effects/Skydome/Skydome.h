#pragma once

#include "../../modules/Camera/Camera.h"

// -----------------------------------------------------------------------
// SkydomeParams
// All gradient and shape controls — fully tweakable from ImGui at runtime
// -----------------------------------------------------------------------
typedef struct SkydomeParams
{
	// --- Gradient colors (4-stop vertical gradient) ---
	vmath::vec3 colorZenith;        // top of dome    (default: deep blue)
	vmath::vec3 colorMidUpper;      // upper middle   (default: sky blue)
	vmath::vec3 colorMidLower;      // lower middle   (default: horizon haze)
	vmath::vec3 colorHorizon;       // horizon edge   (default: warm orange/white)

	// --- Gradient blend positions [0,1] along Y ---
	GLfloat     stopMidUpper;       // where colorMidUpper peaks  (default 0.6)
	GLfloat     stopMidLower;       // where colorMidLower peaks  (default 0.25)
	GLfloat     stopHorizon;        // where horizon color starts (default 0.05)

	// --- Sun disc ---
	BOOL        bShowSun;           // show procedural sun disc (default TRUE)
	vmath::vec3 sunColor;           // sun color    (default: bright white-yellow)
	vmath::vec3 sunDirection;       // normalised world-space direction toward sun
	GLfloat     sunSize;            // angular size (default 0.998 cosine threshold)
	GLfloat     sunGlowSize;        // glow falloff (default 0.985)
	GLfloat     sunGlowStrength;    // glow brightness multiplier (default 0.4)

	// --- Dome geometry ---
	GLfloat     domeRadius;         // world-space radius (default 900.0)
	GLfloat     domeYOffset;        // lower the dome so horizon is at eye level (default -100.0)
	int         domeStacks;         // latitude subdivisions  (default 32)
	int         domeSectors;        // longitude subdivisions (default 64)

	// --- Exposure / tone ---
	GLfloat     exposure;           // brightness multiplier (default 1.0)

} SkydomeParams;

// -----------------------------------------------------------------------
// Function declarations  (matching project step-numbered style)
// -----------------------------------------------------------------------
BOOL initializeSkydome(void);
void renderSkydome(SkydomeParams &params, Camera *pCamera, vmath::mat4 projectionMatrix);
void displaySkydomeImGui(SkydomeParams &params);
void uninitializeSkydome(void);
void setupSkydomeDefaults(SkydomeParams skydomeParams[], int count);
