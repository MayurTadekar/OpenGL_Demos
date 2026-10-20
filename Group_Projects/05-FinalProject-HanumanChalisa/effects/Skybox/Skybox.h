#pragma once

// function declaration
BOOL initializeSkybox(void);
void renderSkybox(Camera *pCamera, vmath::mat4 projectionMatrix, vmath::vec4 clippingPlane);
void uninitializeSkybox(void);
GLuint getSkyboxCubemapID(void);
