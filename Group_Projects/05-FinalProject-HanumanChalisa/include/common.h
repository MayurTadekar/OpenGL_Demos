#pragma once

// Header files
// Win32 sdk
#include <Windows.h>
#include <windowsx.h>

// C standard library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

// C++ standard library
#include <vector>

// VMath
#include "./vmath.h"
using namespace vmath;

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES 1
#endif

#include <math.h>

// GLEW
#include <gl/glew.h>
#include <gl/gl.h>

// Assimp
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// imgui
#include "../modules/imgui/imgui.h"
#include "../modules/imgui/imgui_impl_opengl3.h"
#include "../modules/imgui/imgui_impl_win32.h"

// user define attributes
#include "VertexAttributesEnum.h"

// link import libraries
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, ".\\lib\\assimp.lib")
#pragma comment(lib, "winmm.lib")

// MACROS
#define LOG(...)                      \
    {                                 \
        fprintf(gpFILE, __VA_ARGS__); \
        fflush(gpFILE);               \
    } // print in log file and immediatly write in file

#define MSGBOX(message) MessageBox(NULL, TEXT(message), TEXT("Error"), MB_OK | MB_ICONERROR)

#define LOG_ERROR(fileName, error)                \
    {                                             \
        FILE *gpLogFile = fopen(fileName, "a");   \
        fprintf(gpLogFile, "ERROR: %s\n", error); \
        fclose(gpLogFile);                        \
        gpLogFile = NULL;                         \
        exit(1);                                  \
    }

#define LOG_ENTRY(fileName, message)               \
    {                                              \
        FILE *gpLogFile = fopen(fileName, "a");    \
        fprintf(gpLogFile, "INFO: %s\n", message); \
        fclose(gpLogFile);                         \
        gpLogFile = NULL;                          \
    }

#define LOG_ENTRY_WITH_PARAM(fileName, message, ...)            \
    {                                                           \
        FILE *gpLogFile = fopen(fileName, "a");                 \
        fprintf(gpLogFile, "INFO: " message "\n", __VA_ARGS__); \
        fclose(gpLogFile);                                      \
        gpLogFile = NULL;                                       \
    }

// Degree to Radian Conversion and vice versa
#define ToRad(x) ((x) * (M_PI / 180.0f))
#define ToDeg(x) ((x) * (180.0f / M_PI))

// structs
typedef struct Transformation
{
    vmath::vec3 translation;
    vmath::vec3 rotation;
    vmath::vec3 scale;
} Transformation;

enum SCENE
{
    SCENE_AMC_BANNER = 0,
    SCENE_TITLES,
    SCENE_MOUNTAIN_CAVE_EXTERIOR,
    SCENE_CAVE_INTERIOR,
    SCENE_MOUNTAIN_PEAK,
    SCENE_FLYING,
    SCENE_OCEAN,
    SCENE_RAM_VACHAN,
    SCENE_YUDDHA_SCENE1,
    SCENE_YUDDHA_SCENE2,
    SCENE_SABHA_MANDAP,
    SCENE_END_CREDITS,
    SCENE_RAM_WORSHIP
};

enum
{
    ATTR_POSITION = 0,
    ATTR_COLOR,
    ATTR_TEXCOORD,
    ATTR_NORMAL,
    ATTR_TANGENT,
    ATTR_BINORMAL
};

// #define START_TIME_AMC_BANNER 0.0f
// #define START_TIME_TITLES (START_TIME_AMC_BANNER + 21.0f)
// #define START_TIME_MOUNTAIN_CAVE_EXTERIOR (START_TIME_TITLES + 4.0f)
// #define START_TIME_CAVE_INTERIOR (START_TIME_MOUNTAIN_CAVE_EXTERIOR + 17.0f)
// #define START_TIME_MOUNTAIN_PEAK (START_TIME_CAVE_INTERIOR + 9.0f)
// #define START_TIME_FLYING (START_TIME_MOUNTAIN_PEAK + 15.0f)
// #define START_TIME_OCEAN (START_TIME_FLYING + 12.0f)
// #define START_TIME_RAM_VACHAN (START_TIME_OCEAN + 10.0f)
// #define START_TIME_YUDDHA_SCENE1 (START_TIME_RAM_VACHAN + 13.0f)
// #define START_TIME_YUDDHA_SCENE2 (START_TIME_YUDDHA_SCENE1 + 9.0f)
// #define START_TIME_SABHA_MANDAP (START_TIME_YUDDHA_SCENE2 + 6.0f) // 1.48 sec
// #define START_TIME_RAM_WORSHIP (START_TIME_SABHA_MANDAP + 10.0f)  // 1.58 sec
// #define START_TIME_END_CREDITS (START_TIME_RAM_WORSHIP + 30.0f)   // 2.28 sec - 3.40 END credits 20Secs for Post credits
// #define END_TIME_TOTAL (START_TIME_END_CREDITS + 92.0f)


// version-8
// #define START_TIME_AMC_BANNER 0.0f
// #define START_TIME_TITLES 21.0f
// #define START_TIME_MOUNTAIN_CAVE_EXTERIOR 25.0f
// #define START_TIME_CAVE_INTERIOR 42.0f
// #define START_TIME_MOUNTAIN_PEAK 51.0f
// #define START_TIME_FLYING 58.0f
// #define START_TIME_OCEAN 70.0f
// #define START_TIME_RAM_VACHAN 80.0f
// #define START_TIME_YUDDHA_SCENE1 93.0f
// #define START_TIME_YUDDHA_SCENE2 102.0f
// #define START_TIME_SABHA_MANDAP 108.0f // 1.48 sec
// #define START_TIME_RAM_WORSHIP 118.0f  // 1.58 sec
// #define START_TIME_END_CREDITS 148.0f  // 2.28 sec - 3.40 END credits 20Secs for Post credits
// #define END_TIME_TOTAL 240.0f



#define START_TIME_AMC_BANNER 0.0f
#define START_TIME_TITLES 21.0f
#define START_TIME_MOUNTAIN_CAVE_EXTERIOR 25.0f
#define START_TIME_CAVE_INTERIOR 42.0f
#define START_TIME_MOUNTAIN_PEAK 51.0f
#define START_TIME_FLYING 59.0f
#define START_TIME_OCEAN 73.0f
#define START_TIME_RAM_VACHAN 87.0f
#define START_TIME_YUDDHA_SCENE1 109.0f
#define START_TIME_YUDDHA_SCENE2 118.0f
#define START_TIME_SABHA_MANDAP 127.0f
#define START_TIME_END_CREDITS  136.0f
#define START_TIME_RAM_WORSHIP 201.0f  // END credits
#define END_TIME_TOTAL 240.0f   // post credits


// Commonly used global variable
extern FILE *gpFILE;
extern INT g_iWinWidth;
extern INT g_iWinHeight;
extern float ELAPSED_TIME; // global timing for scene

// Commonly used function
void uninitialize(void);
