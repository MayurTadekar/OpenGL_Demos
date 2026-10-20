#pragma once

// struct declaration
typedef struct WaterfallParams
{
	vmath::vec3 translation;
	vmath::vec3 scale;
	GLfloat rotationAngle[3];
	vmath::vec3 rotationAxis[3];
} WaterfallParams;

int initializeWaterfall();
void renderWaterfall(WaterfallParams params, const vmath::mat4 &viewMatrix, const vmath::mat4 &projectionMatrix);
void uninitializeWaterfall(void);
