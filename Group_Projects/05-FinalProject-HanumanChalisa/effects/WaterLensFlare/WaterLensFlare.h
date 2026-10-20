#pragma once

#include "../../include/common.h"
#include "../../modules/Camera/Camera.h"
#include "../Water/Water.h"

// with this struct we can calculate the water lens flare, can be used as a param also.
typedef struct WaterLensFlareParams
{
    vmath::vec3 sunWorldPosition;
    vmath::vec3 tintColor;
    float       intensity;
    float       alphaScale;
    float       slant;
    bool        clipToWater;
    bool        useOcclusion;
    float       externalVisibility;
    float       sizeScale;
    vmath::vec2 chainDirection;
} WaterLensFlareParams;

BOOL initializeWaterLensFlare(void);
void renderWaterLensFlare(const WaterLensFlareParams &params, Camera *pCamera, vmath::mat4 projectionMatrix, WaterParams water, int screenWidth, int screenHeight);
void uninitializeWaterLensFlare(void);
