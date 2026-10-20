#pragma once

#include "../../modules/Camera/Camera.h"

typedef struct SnowfallParams
{
	BOOL        bEnable;	// master snowfall switch
	int         count;// --- Particle count ---

	// --- World volume ---
	GLfloat     density;            // 1/density = half-height of snow volume
	GLfloat     depth;              // Z spread of the volume

	// --- Physics ---
	GLfloat     gravity;            // fall speed multiplier
	GLfloat     speed;              // overall time scale

	// --- Wind ---
	GLfloat     windForce;          // current wind strength
	GLfloat     windMin;            // min random wind target
	GLfloat     windMax;            // max random wind target
	GLfloat     windEasing;         // how fast wind changes

	// --- Appearance ---
	vmath::vec3 color;              // snowflake tint
	GLfloat     opacity;            // max alpha
	GLfloat     sizeMin;            // min point size scale
	GLfloat     sizeMax;            // max point size scale

	// --- Snowflake texture ---
	const char *texturePath;        // path to blurSnowDrop.png

	// --- Camera start position ---
	vmath::vec3 cameraStartPos;

	GLfloat     _windCurrent;
	GLfloat     _windTarget;
	GLfloat     _time;
	GLfloat     _lastDelta;

} SnowfallParams;

BOOL initializeSnowfall(SnowfallParams &params, int screenW, int screenH);
void renderSnowfall(SnowfallParams &params, Camera *pCamera, vmath::mat4 projectionMatrix, int screenW, int screenH);
void updateSnowfall(SnowfallParams &params, GLfloat deltaTime);
void displaySnowfallImGui(SnowfallParams &params);
void uninitializeSnowfall(void);
