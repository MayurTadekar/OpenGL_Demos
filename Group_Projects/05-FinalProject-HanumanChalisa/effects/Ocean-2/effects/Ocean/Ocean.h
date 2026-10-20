#pragma once

#include "../../../../include/common.h"

class Camera;

struct GerstnerWave
{
    vmath::vec2 direction;
    GLfloat     amplitude;
    GLfloat     wavelength;
    GLfloat     speed;
    GLfloat     steepness;
};

#define OCEAN_MAX_WAVES 6

struct OceanParams
{
    vmath::vec3 translation;
    GLfloat     extent;
    GLint       resolution;

    GerstnerWave waves[OCEAN_MAX_WAVES];
    GLint        numWaves;

    vmath::vec3 shallowColor;
    vmath::vec3 deepColor;
    vmath::vec3 foamColor;
    GLfloat     foamThreshold;
    GLfloat     foamSoftness;
    GLfloat     foamChoppinessGain;

    vmath::vec3 sunDirection;
    vmath::vec3 sunColor;
    GLfloat     sunShininess;
    GLfloat     sunIntensity;

    GLfloat     fresnelStrength;
    GLfloat     reflectionStrength;

    vmath::vec3 horizonFogColor;
    GLfloat     fogDensity;
};

BOOL initializeOcean(GLuint skyboxCubemapID);
void renderOcean(OceanParams &params, Camera *pCamera, const vmath::mat4 &projectionMatrix, float elapsedTime);
void uninitializeOcean(void);

void getDefaultStormPreset(OceanParams &outParams);
