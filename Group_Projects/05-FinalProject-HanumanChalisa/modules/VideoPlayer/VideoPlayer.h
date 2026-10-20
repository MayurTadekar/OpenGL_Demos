#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <mfobjects.h>
#include <propvarutil.h>
#include <GL/glew.h>

#pragma comment(lib, "mf.lib")
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mfreadwrite.lib")
#pragma comment(lib, "mfuuid.lib")
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "propsys.lib")

struct VideoPlayer
{
    IMFSourceReader* pReader   = nullptr;
    GLuint           textureID = 0;
    int              width     = 0;
    int              height    = 0;
    bool             bLooping  = false; // video must render once, true if want LOOP
    bool             bEOF      = false;
    float            videoFPS  = 30.0f;
    float            frameDuration = 1.0f / 30.0f;
    LONGLONG         lastFrameTimestamp = -1LL;  // track by MF timestamp, not wall clock
    int speedMultiplier = 1;  // 1=normal, 2=2x, 3=3x
};

bool VideoPlayerInit(VideoPlayer& vp, const wchar_t* fileName);
void VideoPlayerUpdateTexture(VideoPlayer& vp, float currentTimeSec);
void VideoPlayerUninit(VideoPlayer& vp);
