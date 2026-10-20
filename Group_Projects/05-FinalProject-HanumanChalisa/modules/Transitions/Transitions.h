#pragma once
#include <windows.h>
#include <gl/glew.h>
#include <gl/gl.h>

// TransitionType — cinematic after effects
enum TransitionType
{
    TRANSITION_NONE = 0,

    TRANSITION_FADE = 1,     // black overlay fade — simple, clean, cinematic
    TRANSITION_DISSOLVE = 2, // sand/dust particle dissolve — grains sweep left to right
    TRANSITION_RIPPLE = 3,   // water ripple warp — concentric distortion from center
    TRANSITION_BURN = 4,     // fire burn from bottom
    TRANSITION_SPIN = 5,  // glass shard break
};

struct TransitionState
{
    BOOL isTransitioning;
    float startTime;
    float duration;
    TransitionType type;
    int fromSceneID;
    int toSceneID;
};

extern TransitionState gTransition;
extern GLuint textureSceneA;
extern GLuint textureSceneB;

// Core API
BOOL initializeTransitions(int width, int height);
void resizeTransitions(int width, int height);
void startSceneTransition(TransitionType type, int fromScene, int toScene, float duration = 2.0f);
void updateTransitionProgress(float currentTime);
void bindTransitionFramebuffer();
void unbindTransitionFramebuffer();
void renderTransitionOutput();
void uninitializeTransitions();
