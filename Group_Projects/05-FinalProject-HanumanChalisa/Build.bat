@echo off

cls

REM Create bin folder if not exists
if not exist bin (
    mkdir bin
)

REM ==========================================
REM Set compiler flags for
REM End-to-End run => 0, else give scene numbers as below
@REM #define START_TIME_AMC_BANNER             // 1
@REM #define START_TIME_TITLES                 // 2
@REM #define START_TIME_MOUNTAIN_CAVE_EXTERIOR // 3
@REM #define START_TIME_CAVE_INTERIOR          // 4
@REM #define START_TIME_MOUNTAIN_PEAK          // 5          
@REM #define START_TIME_FLYING                 // 6
@REM #define START_TIME_OCEAN                  // 7
@REM #define START_TIME_RAM_VACHA              // 8    
@REM #define START_TIME_YUDDHA                 // 9
@REM #define START_TIME_SABHA_MANDAP           // 10
@REM #define START_TIME_RAM_WORSHIP            // 11
@REM #define START_TIME_END_CREDITS 80.0f
REM ==========================================
set CPP_FLAGS=-D

REM ==========================================
REM Source Files
REM ==========================================
set SRC_CORE=OGL.cpp

set SRC_MODULES= ^
modules\Audio\Audio.cpp ^
modules\Texture\Texture.cpp ^
modules\Camera\Camera.cpp ^
modules\Camera\BSplineCamera.cpp ^
modules\Model\Model.cpp ^
modules\Mesh\Mesh.cpp ^
modules\Framebuffer\Framebuffer.cpp ^
modules\Transitions\Transitions.cpp ^
modules\VideoPlayer\VideoPlayer.cpp

set SRC_IMGUI= ^
modules\imgui\imgui.cpp ^
modules\imgui\imgui_draw.cpp ^
modules\imgui\imgui_demo.cpp ^
modules\imgui\imgui_widgets.cpp ^
modules\imgui\imgui_tables.cpp ^
modules\imgui\imgui_impl_opengl3.cpp ^
modules\imgui\imgui_impl_win32.cpp

set SRC_EFFECTS= ^
effects\SceneLighting\SceneLighting.cpp ^
effects\LightningWithFlash\LightningWithFlash.cpp ^
effects\FadeEffect\FadeEffect.cpp ^
effects\FogEffect\FogEffect.cpp ^
effects\WaterLensFlare\WaterLensFlare.cpp ^
effects\Water\Water.cpp ^
effects\Ocean-2\effects\Ocean\Ocean.cpp ^
effects\Skybox\Skybox.cpp ^
effects\Grass\Grass.cpp ^
effects\Terrain\Terrain.cpp ^
effects\Skydome\Skydome.cpp ^
effects\GodRays\GodRays.cpp ^
effects\Snowfall\Snowfall.cpp ^
effects\Waterfall\Waterfall.cpp ^
effects\Dissolve\Dissolve.cpp ^
effects\Title\Title.cpp ^
effects\BoidSimulation\BoidSimulation.cpp ^
effects\MayursEffects\VolumetricClouds\VolumetricClouds.cpp ^
effects\MayursEffects\VolumetricClouds\ComputeShader.cpp ^
effects\MayursEffects\VolumetricClouds\triangle.cpp ^
effects\Bloom\Bloom.cpp 

set SRC_CONFIGS= ^
modelsConfig.cpp ^
imguiConfigs.cpp 

set ALL_SOURCE_FILES=%SRC_CORE% %SRC_MODULES% %SRC_IMGUI% %SRC_EFFECTS% %SRC_CONFIGS%

REM ==========================================
REM Include Paths
REM ==========================================
set INCLUDE_FLAGS= ^
/I ".\include" ^
/I ".\modules" ^
/I "C:\glew-2.1.0\include" ^
/I "C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v12.8\include" ^
/I ".\include\stb"

REM ======================
REM Compile
REM ======================
cl.exe %CPP_FLAGS% /std:c++17 /MP4 /EHsc /c ^
/Fo.\bin\ ^
%INCLUDE_FLAGS% ^
%ALL_SOURCE_FILES%

echo.
echo ===== OBJECT FILES =====
dir bin
echo ========================
@REM pause

REM ======================
REM Compile Resource File for Icon
REM ======================
rc.exe /fo OGL.res OGL.rc

REM ==========================================
REM Linker Flags and Libraries
REM ==========================================
set LINK_FLAGS= ^
/LIBPATH:".\lib" ^
/LIBPATH:"C:\glew-2.1.0\lib\Release\x64"

set LIBS= ^
glew32.lib ^
opengl32.lib ^
user32.lib ^
ole32.lib ^
gdi32.lib ^
shell32.lib ^
OpenAL32.lib ^
ole32.lib ^
mf.lib ^
mfplat.lib ^
mfreadwrite.lib ^
mfuuid.lib ^
windowscodecs.lib

REM ======================
REM Link
REM ======================
cl.exe /Fe:Demo.exe bin\*.obj OGL.res ^
/link ^
/MACHINE:x64 ^
%LINK_FLAGS% ^
%LIBS%

REM ======================
REM Post-Build Steps
REM ======================
if exist Demo.exe (
    echo Cleaning bin folder...
    del /Q bin\*.obj
)

echo.
echo Build complete!
pause
