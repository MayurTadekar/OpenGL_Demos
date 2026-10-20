#pragma once

#include "../../include/common.h"
#include "../../modules/Camera/Camera.h"

// -----------------------------------------------------------------------
// GodRaysParams
// All god rays controls — fully tweakable from ImGui at runtime
// Follows exact same pattern as SkydomeParams
// -----------------------------------------------------------------------
typedef struct GodRaysParams
{
	// --- Sun screen-space position ---
	// Set this to the projected screen position of your sun (0..1 range)
	// Derived automatically from sunWorldPos each frame
	vmath::vec3 sunWorldPos;       // world-space sun position

	// --- Ray appearance ---
	vmath::vec3 rayColor;          // god ray tint color    (default: warm yellow-white)
	GLfloat     exposure;          // overall brightness    (default: 0.35)
	GLfloat     decay;             // falloff per sample    (default: 0.97)
	GLfloat     density;           // sample spacing        (default: 0.96)
	GLfloat     weight;            // per-sample brightness (default: 0.45)
	int         numSamples;        // ray march samples     (default: 80)

	// --- Occlusion disc (blocks rays behind scene geometry) ---
	BOOL        bShowOcclusionDisc; // draw black sun disc to create shadow (default TRUE)
	GLfloat     discRadius;         // angular radius of occlusion disc     (default 0.08)

	// --- Sun corona / halo on top of rays ---
	BOOL        bShowCorona;        // bright sun disc drawn after rays     (default TRUE)
	vmath::vec3 coronaColor;        // corona color  (default bright white-yellow)
	GLfloat     coronaSize;         // screen-space radius of corona        (default 0.06)
	GLfloat     coronaStrength;     // brightness of corona                 (default 2.5)

} GodRaysParams;

// -----------------------------------------------------------------------
// Function declarations — matching project step-numbered style
// -----------------------------------------------------------------------
BOOL initializeGodRays(void);
void renderGodRays(GodRaysParams &params, Camera *pCamera,
                   vmath::mat4 projectionMatrix,
                   GLuint sceneDepthTexture);   // pass 0 if no depth occlusion
void displayGodRaysImGui(GodRaysParams &params);
void uninitializeGodRays(void);
