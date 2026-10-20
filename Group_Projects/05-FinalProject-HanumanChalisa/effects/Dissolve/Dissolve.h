#pragma once
#include "../include/common.h"
#include "../modules/Model/Model.h"

int initializeDissolveShader(void);
void renderModelWithDissolve(Model *model, vmath::mat4 modelMatrix,vmath::mat4 viewMatrix,vmath::mat4 projectionMatrix,float progress,float time,BOOL bReverse);
void uninitializeDisslove(void);

static GLuint shaderProgramObjectDissolve = 0;
static GLuint modelMatrixUniformDissolve = 0;
static GLuint viewMatrixUniformDissolve = 0;
static GLuint projectionMatrixUniformDissolve = 0;
static GLuint textureSamplerUniformDissolve = 0;

//Dissolve related
static float g_dissolveProgress = -20.0f;
static float g_dissolveTime = 0.0f;
static BOOL g_dissolveActive = FALSE;
static BOOL g_bReverseDissolve = FALSE;  // FALSE = appear (invisible→visible), TRUE = disappear (visible→invisible)
static BOOL bDissolve = FALSE;
static GLuint dissolveReverseUniform;
static float g_dissolveLastFrameTime = 0.0f;

static GLuint dissolveShaderProgram = 0;
static GLuint dissolveMVPUniform = 0;
static GLuint dissolveEnabledUniform = 0;
static GLuint dissolveProgressUniform = 0;
static GLuint dissolveEdgeWidthUniform = 0;
static GLuint dissolveFrequencyUniform = 0;
static GLuint dissolveAmplitudeUniform = 0;
static GLuint dissolveMeshColorUniform = 0;
static GLuint dissolveEdgeColorUniform = 0;
static GLuint dissolveTimeUniform = 0;
static GLuint dissolveTextureSamplerUniform = 0;
