#pragma once

#include "../../include/common.h"
#include "../../modules/Camera/Camera.h"

struct BloomParams {
    vmath::vec3 position;
    vmath::vec3 color;
    float radius;
    float intensity;
};

void initializeBloom(void);
void renderBloom(const BloomParams& params, Camera* pCamera, vmath::mat4 projectionMatrix);
void uninitializeBloom(void);