#pragma once

#include "../../include/common.h"
#include "../../modules/Camera/Camera.h"

BOOL   initializeSkybox(const char *faces[6]);
void   renderSkybox(const Camera *pCamera, const vmath::mat4 &projectionMatrix);
GLuint getSkyboxCubemapID(void);
void   uninitializeSkybox(void);
