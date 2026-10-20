// Customizable OceanParams Fields

// | Field                  | Type    | Default | Description                                              |
// |------------------------|---------|---------|----------------------------------------------------------|
// | `tideSpeed`            | float   | 1.0     | Overall animation rate. 0=frozen, 1=calm, 3=storm surge  |
// | `waveHeight`           | float   | 3.5     | Max crest height in world units                          |
// | `waveChoppiness`       | float   | 0.8     | 0=smooth sine, 1=sharp peaked Gerstner waves             |
// | `waveFrequency`        | float   | 0.4     | Spatial frequency (higher = more crests per unit)         |
// | `waveDirectionAngle`   | float   | 45.0    | Primary swell direction in degrees                       |
// | `waveStrength`         | float   | 0.08    | DuDv surface distortion strength                         |
// | `foamThreshold`        | float   | 2.8     | Height (world units) above which foam appears at crests  |
// | `specularStrength`     | float   | 2.5     | Sun glint intensity on wave peaks                        |

#pragma once

#include "../../include/vmath.h"
#include <GL/glew.h>

// struct declaration
typedef struct OceanParams
{
	// --- Geometry ---
	vmath::vec3 translation;        // World position of ocean plane
	vmath::vec3 scale;              // XYZ scale of ocean plane

	// --- Wave animation ---
	GLfloat tideSpeed;						  // [CUSTOMIZABLE] Overall speed of tide movement (moveFactor increment per frame)
	GLfloat waveHeight;						// [CUSTOMIZABLE] Vertex displacement amplitude (Gerstner wave height)
	GLfloat waveChoppiness;				 // [CUSTOMIZABLE] Lateral displacement (choppiness factor, 0=sine 1=choppy)
	GLfloat waveFrequency;				  // [CUSTOMIZABLE] Spatial frequency of waves (higher = more crests)
	GLfloat waveDirectionAngle; 		// [CUSTOMIZABLE] Primary wave propagation angle (degrees)

	// --- DuDv distortion ---
	GLfloat waveStrength;           // Distortion strength from DuDv map
	GLfloat tiling;                 // DuDv texture tiling factor

	// --- Color & shading ---
	vmath::vec3 shallowColor;       // Near-crest color
	vmath::vec3 deepColor;          // Trough/deep color
	GLfloat colorBlendSharpness;    // Sharpness of shallow/deep transition
	vmath::vec3 foamColor;          // Foam colour at wave crests
	GLfloat foamThreshold;          // Vertex height threshold above which foam appears
	GLfloat specularStrength;       // Specular highlight intensity
	GLfloat shininess;              // Specular shininess exponent
	GLfloat sunElevation;           // Sun elevation in degrees
	GLfloat sunAzimuth;             // Sun azimuth in degrees
	vmath::vec3 sunColor;           // Color of the specular sun reflection

	// --- Internal (do not set manually) ---
	GLfloat moveFactor;             // Accumulated DuDv scroll offset 

} OceanParams;

class Camera;

// function declaration
BOOL    initializeOcean(GLuint dudvMapTexture, GLuint skyboxCubemapTexture);
void    renderOcean(OceanParams &params, Camera *pCamera, vmath::mat4 projectionMatrix);
void    displayOceanImGui(OceanParams &params);   
void    uninitializeOcean(void);
