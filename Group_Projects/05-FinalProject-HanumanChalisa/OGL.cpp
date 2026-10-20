// header files
#include "./include/common.h"
#include "./include/helper_timer.h"
#include "OGL.h"

#include "./modules/Audio/Audio.h"
#include "./modules/Texture/Texture.h"
#include "./modules/VideoPlayer/VideoPlayer.h"
#include "./modules/Camera/Camera.h"
#include "./modules/Camera/BSplineCamera.h"
#include "./modules/Model/Model.h"
#include "./modules/Framebuffer/Framebuffer.h"
#include "./modules/Transitions/Transitions.h"

#include "./effects/SceneLighting/SceneLighting.h"
#include "./effects/FadeEffect/FadeEffect.h"
#include "./effects/FogEffect/FogEffect.h"
#include "./effects/WaterLensFlare/WaterLensFlare.h"
#include "./effects/Water/Water.h"
#include "./effects/Grass/Grass.h"
#include "./effects/Skybox/Skybox.h"
#include "./effects/Terrain/Terrain.h"
// #include "./effects/Ocean/Ocean.h"
#include "./effects/Ocean-2/effects/Ocean/Ocean.h"
#include "./effects/Skydome/Skydome.h"
#include "./effects/GodRays/GodRays.h"
#include "./effects/Snowfall/Snowfall.h"
#include "./effects/Waterfall/Waterfall.h"
#include "./effects/Dissolve/Dissolve.h"
#include "./effects/Title/Title.h"
#include "./effects/LightningWithFlash/LightningWithFlash.h"
#include "./effects/Bloom/Bloom.h"

#include "./effects/MayursEffects/Fire/fireonsquare.hpp"
#include "./effects/MayursEffects/VolumetricClouds/VolumetricClouds.hpp"
#include "./effects/MayursEffects/LitSabhamandapProgramWithShadow/LitSabhamandapProgramWithShadow.hpp"
#include "./effects/MayursEffects/Shadow/ShadowProgram.h"
#include "./effects/MayursEffects/SingleLightProgram/SingleLightProgram.h"
#include "./effects/MayursEffects/PBRProgram/PBRProgram.h"
#include "./effects/MayursEffects/PointProgram/PointProgram.h"
#include "./effects/BoidSimulation/BoidSimulation.h"

#define PREVIEW_SCENE 0 // <--- Scene change factor

static const float SCENE_START_TIMES[] = {
	0.0f,							   // 0
	START_TIME_AMC_BANNER,			   // 1
	START_TIME_TITLES,				   // 2
	START_TIME_MOUNTAIN_CAVE_EXTERIOR, // 3
	START_TIME_CAVE_INTERIOR,		   // 4
	START_TIME_MOUNTAIN_PEAK,		   // 5
	START_TIME_FLYING,				   // 6
	START_TIME_OCEAN,				   // 7
	START_TIME_RAM_VACHAN,			   // 8
	START_TIME_YUDDHA_SCENE1,		   // 9
	START_TIME_YUDDHA_SCENE2,		   // 10
	START_TIME_SABHA_MANDAP,		   // 11
	START_TIME_END_CREDITS,			   // 12
	START_TIME_RAM_WORSHIP			   // 13
};

// --------------- Transitions related globals starts here-----------------------------------
struct SceneTransitionData
{
	int fromScene;
	int toScene;
	TransitionType type;
	float triggerTime;
	float duration;
	bool *fired;
};

static bool T0_Fired = false;
// static bool T1_Fired = false;
// static bool T2_Fired = false;
// static bool T3_Fired = false;
// static bool T4_Fired = false;
// static bool T5_Fired = false;
// static bool T6_Fired = false;
// static bool T7_Fired = false;
// static bool T8_Fired = false;
// static bool T9_Fired = false;
// static bool T10_Fired = false;
// static bool T11_Fired = false;

SceneTransitionData gSceneTransitions[] =
	{
		{SCENE_AMC_BANNER,
		 SCENE_TITLES,
		 TRANSITION_BURN,
		 START_TIME_TITLES - 2.0f,
		 2.0f,
		 &T0_Fired},

		// {SCENE_TITLES,
		//  SCENE_MOUNTAIN_CAVE_EXTERIOR,
		//  TRANSITION_FADE,
		//  START_TIME_MOUNTAIN_CAVE_EXTERIOR - 2.0f,
		//  2.0f,
		//  &T1_Fired},

		// {SCENE_MOUNTAIN_CAVE_EXTERIOR,
		//  SCENE_CAVE_INTERIOR,
		//  TRANSITION_FADE,
		//  START_TIME_CAVE_INTERIOR - 2.0f,
		//  2.0f,
		//  &T2_Fired},

		// {SCENE_CAVE_INTERIOR,
		//  SCENE_MOUNTAIN_PEAK,
		//  TRANSITION_FADE,
		//  START_TIME_MOUNTAIN_PEAK - 2.0f,
		//  2.0f,
		//  &T3_Fired},

		// {SCENE_MOUNTAIN_PEAK,
		//  SCENE_FLYING,
		//  TRANSITION_FADE,
		//  START_TIME_FLYING - 2.0f,
		//  2.0f,
		//  &T4_Fired},

		// {SCENE_FLYING,
		//  SCENE_OCEAN,
		//  TRANSITION_FADE,
		//  START_TIME_OCEAN - 2.0f,
		//  2.0f,
		//  &T5_Fired},

		// {SCENE_OCEAN,
		//  SCENE_RAM_VACHAN,
		//  TRANSITION_RIPPLE,
		//  START_TIME_RAM_VACHAN - 2.0f,
		//  2.0f,
		//  &T6_Fired},

		// {SCENE_RAM_VACHAN,
		//  SCENE_YUDDHA,
		//  TRANSITION_FADE,
		//  START_TIME_YUDDHA - 2.0f,
		//  2.0f,
		//  &T7_Fired},

		// {SCENE_YUDDHA,
		//  SCENE_SABHA_MANDAP,
		//  TRANSITION_FADE,
		//  START_TIME_SABHA_MANDAP - 2.0f,
		//  2.0f,
		//  &T8_Fired},

		// {SCENE_SABHA_MANDAP,
		//  SCENE_RAM_WORSHIP,
		//  TRANSITION_DISSOLVE,
		//  START_TIME_RAM_WORSHIP - 2.0f,
		//  2.0f,
		//  &T9_Fired},

		// {SCENE_RAM_WORSHIP,
		//  SCENE_END_CREDITS,
		//  TRANSITION_FADE,
		//  START_TIME_END_CREDITS - 2.0f,
		//  2.0f,
		//  &T10_Fired}
};

const int gTransitionCount = sizeof(gSceneTransitions) / sizeof(gSceneTransitions[0]);
#define FADE_OUT_DURATION 2.0f // Duration of fade-out in seconds
// --------------- Transitions related globals ends here-----------------------------------
static float gTimeOffset = 0.0f;

#define FREE_MODEL(model) \
	if (model)            \
	{                     \
		freeModel(model); \
		model = NULL;     \
	}

// OpenGl Related Global variable
HDC ghdc = NULL;
HGLRC ghrc = NULL;

// Macros
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

// Link With OpenGL Library
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "OpenGL32.lib")

// Global function declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// imgui
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);

// Global variable declaration
DWORD dwStyle = 0;
WINDOWPLACEMENT wpPrev = {sizeof(WINDOWPLACEMENT)}; // initialization of struct => this work on all type (if we want to initialize all value to 0)

BOOL gbFullscreen = FALSE;
BOOL bShowImGui = FALSE;
HWND ghwnd = NULL; // g = global handle of window
BOOL gbActive = FALSE;

FILE *gpFILE = NULL;

// mat4 is datatype means 4 * 4 matrix (present in vmath.h)
mat4 perspectiveProjectionMatrix;

// current window dimensions
INT g_iWinWidth = WIN_WIDTH;
INT g_iWinHeight = WIN_HEIGHT;

// screen dimentions
int screenWidth, screenHeight;

// Camera
Camera *gpCamera = NULL;
BSplineCamera *camera_SnowTerrain = NULL;
BSplineCamera *camera_Ocean = NULL;
BSplineCamera *camera_RamVachanScene = NULL;
BSplineCamera *camera_SabhaMandapScene = NULL;
BSplineCamera *camera_MountainPeakScene = NULL;
BSplineCamera *camera_CaveInterior = NULL;
BSplineCamera *camera_FlyingScene = NULL;
BSplineCamera *camera_YuddhaScene1 = NULL;
BSplineCamera *camera_YuddhaScene2 = NULL;
BSplineCamera *camera_RamWorship = NULL;

BSplineCamera *rotatingCamera = NULL;
BOOL bRotateCamera = FALSE;

// Scene timer
StopWatchInterface *sceneTimer = NULL;
float ELAPSED_TIME; // global timing for scene
int selected_scene; // selected scene
BOOL bAMCVideoUninitialized = FALSE;

// GLOBAL VARIABLE FOR VIDEO
VideoPlayer gAMCBannerVideo;

// global variables for model loading
static GLuint shaderProgramObject = 0;
static GLuint modelMatrixUniform = 0;
static GLuint viewMatrixUniform = 0;
static GLuint projectionMatrixUniform = 0;
static GLuint textureSamplerUniform = 0;

static GLuint clippingPlaneUniform = 0;

// skybox cubemap ID (retrieved from Skybox module for ocean reflections)
static GLuint g_skyboxCubemapForOcean = 0;
SkydomeParams skydomeParams[5];

// Forward declaration for Skydome initialization function
void setupSkydomeDefaults(SkydomeParams skydomeParams[]);

SceneLightParams caveInteriorScene_HanumajiLights;
SceneLightParams mountainExteriorSceneLights;
SceneLightParams generalHanumanJiLights;
SceneLightParams flyingHanumanJiLights;

SceneLightParams sabhamandapScene_ThroneLights;
SceneLightParams sabhamandapScene_HanumajiLights;
SceneLightParams sabhamandapScene_VibhishanLights;
SceneLightParams ramvachanLights;

// for godRays
GodRaysParams godRaysParams;
GodRaysParams godRaysParamsForRamWorship;

// for ocean
OceanParams oceanParams;
OceanParams gOcean;

// for water
WaterParams waterParams[2];
Framebuffer *waterReflectionFramebuffer = NULL;
Framebuffer *waterRefractionFramebuffer = NULL;
WaterfallParams waterfallParams;

// for snowfall
SnowfallParams snowfallParams;
static GLfloat snowLastTime = 0.0f;

// dudv map texture
Texture waterDuDvMapTexture;

Grass *pGrass = NULL;
static float lensFlareAngle = 0.0f;
WaterLensFlareParams ramVachanFlareParams;
WaterLensFlareParams mountainPeakFlareParams;

// Terrain related
Terrain *pHeightmapTerrain = NULL;

// Fire Related
FireOnSquare *pFire = NULL;

// Volumetric Clouds
VolumetricClouds *volumetriccloudsForPeakScene = nullptr;
VolumetricClouds *volumetriccloudsForFlyingScene = nullptr;
VolumetricClouds *volumetriccloudsForYuddhaScene = nullptr;
VolumetricClouds *volumetriccloudsForOcean = nullptr;
float flyingY = 1393.0f;

// Bloom
BloomParams hanumanGlowParams;

// LitSabhamandapProgramWithShadow
LitSabhamandapProgramWithShadow *litSabhamandapProgramWithShadow = nullptr;
FrameBufferObjectWithDepth *firePotShadowFBO = nullptr;
FrameBufferObjectWithDepth *ministerChairShadowFBO = nullptr;
FrameBufferObjectWithDepth *hanumanShadowFBO = nullptr;
FrameBufferObjectWithDepth *vibhishanShadowFBO = nullptr;
FrameBufferObjectWithDepth *pillarShadowFBO = nullptr;
ShadowProgram *shadowProgram = nullptr;
int gwinWidth = 0;
int gwinHeight = 0;

struct ShadowEssentials hanumanShadow = {0.0f, -15.0f, -60.0f, 50, 0.0f, 0.0f, -11.0f};
struct ShadowEssentials vibhishanShadow = {0.0f, 3.0f, -90.0f, 50, 0.0f, 0.0f, -11.0f};
struct ShadowEssentials fireKundShadow = {0.0f, -15.0f, -39.30f, 35, 0.0f, 0.0f, -11.0f};
struct ShadowEssentials ministerChairShadow = {0.0f, 18.0f, 28.0f, 35, 0.0f, 0.0f, -10.0f};
struct ShadowEssentials pillarShadow = {0.0f, 18.0f, 28.0f, 35, 0.0f, 0.0f, -10.0f};

// Ramvachan Shadow
LitSabhamandapProgramWithShadow *ramVachanProgramWithShadow = nullptr;
FrameBufferObjectWithDepth *ramVachanShadowFBO = nullptr;
FrameBufferObjectWithDepth *ramVachanTreeShadowFBO = nullptr;
struct ShadowEssentials ramVachanShadow = {0.0f, -36.0f, 107.0f, 50, 10.0f, 0.0f, -1.4f};
struct ShadowEssentials ramVachanTreeShadow = {0.0f, -38.0f, 160.0f, 50, 10.0f, 0.0f, 1.0f};

// // Ram Worship Shadow
// FrameBufferObjectWithDepth *ramworshipAnimalFBO = nullptr;
// struct ShadowEssentials ramworshipAnimalShadow = {0.0f, -38.0f, 160.0f, 50, 10.0f, 0.0f, 1.0f};

// Yuddha 01 Scene
FrameBufferObjectWithDepth *asurShadowFBO = nullptr;
struct ShadowEssentials asurShadow = {0.0f, -206.0f, 40.0f, 50, -25.0f, -8.5f, -97.0f};
struct ShadowEssentials hanumanYuddha01Shadow = {0.0f, -159.0f, 310.0f, 50, -29.0f, 0.0f, -74.0f};

// Mountain Peak
float mountainPeakLightX = -5000.0;
float mountainPeakLightY = 0.0;
float mountainPeakLightZ = 5000.0;

float hanumanPosX = 54.7;
float hanumanPosY = 177.0;
float hanumanPosZ = 108.0;
float radiance = -1.0f;
float emmissiveStrength = 1;
float YFactor = 5.0f;

// dissolve global variable
extern BOOL g_dissolveStarted = FALSE; // Track if dissolve has started

// Single Light Program
SingleLightProgram *mountainPeakProgram = nullptr;
SingleLightProgram *sideMountainPeakProgram = nullptr;

// PBRProgram
PBRProgram *hanumanOnMountain = nullptr;
vmath::vec3 hanumanOnMountainLightpos = vmath::vec3(0.0f, 0.0f, 1.0f);

// Boid Simulation
BoidSimulation *pBoidSimulation = NULL; // Single BoidSimulation object, its behavior is driven by the passed BoidParams
BoidParams boidParamsVshape;
BoidParams boidParamsFlock;

// Hanuman Flying In Ocean
float hanumanOceanXPos = -2400.0f;
float hanumanOceanYPos = 27.0f;
float hanumanOceanZPos = 0.0f;
float hanumanOceanXFactor = 6.0f;

#pragma region CAMERA

int timer = 0; // use as iterative variable for accessing BezierPoints elements
std::vector<float> BezierPoints;
float controlPoints[4][3] = {
	{20.0f, 12.0f, 105.0f},
	{5.0f, 10.0f, 50.0f},
	{20.0f, 12.0f, 20.0f},
	{15.0f, 10.0f, -40.0f}};

// CAMERA SHOW POINTS
std::vector<float> verts;
PointProgram *pointProgram = nullptr;
std::vector<vmath::vec3> positionsMountainPeakScene;
std::vector<vmath::vec3> positionsYuddhaScene1;

#define CAMERA_SPEED 0.8f

#pragma endregion

// Entry Point Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// Function declaration
	int initialize(void);
	void uninitialize(void);
	void display(void);
	void update(void);

	// local variable declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("SGDWindow");

	int iResult = 0;

	BOOL bDone = FALSE; // For Game Loop

	int SystemWindowWidth, SystemWindowHeight;
	int x_Coordinate, y_Coordinate;

	// get system window width and height
	SystemWindowWidth = GetSystemMetrics(SM_CXSCREEN);
	SystemWindowHeight = GetSystemMetrics(SM_CYSCREEN);
	// get x and y coordinate for show window in center on screen
	x_Coordinate = (SystemWindowWidth / 2) - (WIN_WIDTH / 2);
	y_Coordinate = (SystemWindowHeight / 2) - (WIN_HEIGHT / 2);

	if (fopen_s(&gpFILE, "log.txt", "w") == 0)
	{
		fprintf(gpFILE, "Program Started Successfully\n");
	}
	fclose(gpFILE);
	gpFILE = nullptr;

	// code
	CreateDirectory(TEXT("Log"), NULL);
	if (fopen_s(&gpFILE, "Log/Log.txt", "w") != 0)
	{
		MessageBox(NULL, TEXT("Log file cannot be open"), TEXT("Error"), MB_OK | MB_ICONERROR);
		exit(0);
	}
	fprintf(gpFILE, "Program Started Successfully\n");
	fprintf(gpFILE, "\n==============================================================================\n");

	// WNDCLASSEX Initialization
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndclass.cbWndExtra = 0;
	wndclass.cbClsExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	// screen dimensions
	screenWidth = SystemWindowWidth;
	screenHeight = SystemWindowHeight;

	// Register WNDCLASSEX
	RegisterClassEx(&wndclass);

	// Create Window
	hwnd = CreateWindowEx(WS_EX_APPWINDOW,
						  szAppName,
						  TEXT("Texture Group : Final"),
						  WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
						  x_Coordinate,
						  y_Coordinate,
						  WIN_WIDTH,
						  WIN_HEIGHT,
						  NULL,
						  NULL,
						  hInstance,
						  NULL);

	ghwnd = hwnd;

	LOG_ENTRY("log.txt", "Initialization Started");
	// Initialization
	iResult = initialize();
	if (iResult != 0)
	{
		MessageBox(hwnd, TEXT("initialize() failed."), TEXT("Error"), MB_OK | MB_ICONERROR);
		DestroyWindow(hwnd);
	}
	else
	{
		LOG_ENTRY("log.txt", "Initialization Successful");
	}

	// ImGui initialization
	initializeImGui();

	// show window
	ShowWindow(hwnd, iCmdShow);

	// set window first in z-order (foreground)
	SetForegroundWindow(hwnd);

	// set focus on this window(internally send 'WM_SETFOCUS' message to WndProc())
	SetFocus(hwnd);

	// PlaySound(TEXT("./resources/Audio/track2.wav"), NULL, SND_FILENAME | SND_ASYNC);
	/*
		Instead of Windows API function PlaySound() we are using OpenAL library.
	*/

	// Game Loop
	while (bDone == FALSE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				bDone = TRUE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			// code
			if (gbActive == TRUE) // If Window is in focus then 'WM_SETFOCUS' is send to WndProc() and We Handled this message and set gbActive = true
			{
				// Render
				display();

				// Update
				update();
			}
		}
	}

	// Uninitialization
	uninitialize();

	return ((int)msg.wParam);
}

// Callback function defination
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// variable declaration
	RECT rc;
	// function declarations
	void ToggleFullScreen(void);
	void resize(int, int);

	// code

	// handle messages for imgui
	if (ImGui_ImplWin32_WndProcHandler(hwnd, iMsg, wParam, lParam))
	{
		return (0);
	}

	switch (iMsg)
	{
	case WM_SETFOCUS: // when window is in focus (window is activate)
		gbActive = TRUE;
		break;
	case WM_KILLFOCUS: // when window is not in focus(window is deactivate)
		gbActive = FALSE;
		break;
	case WM_SIZE:
		GetClientRect(ghwnd, &rc);
		g_iWinWidth = rc.right - rc.left;
		g_iWinHeight = rc.bottom - rc.top;
		resize(g_iWinWidth, g_iWinHeight);
		break;

	case WM_ERASEBKGND:
		return (0);

	case WM_KEYDOWN:
	{
		switch (LOWORD(wParam))
		{
		case VK_ESCAPE:
			DestroyWindow(hwnd);
			break;
		case 'W':
		case 'w':
			gpCamera->setMoveForward(true);
			break;
		case 'S':
		case 's':
			gpCamera->setMoveBackward(true);
			break;
		case 'A':
		case 'a':
			gpCamera->setMoveLeft(true);
			break;
		case 'D':
		case 'd':
			gpCamera->setMoveRight(true);
			break;
		case 'Q':
		case 'q':
			gpCamera->setMoveDown(true);
			break;
		case 'E':
		case 'e':
			gpCamera->setMoveUp(true);
			break;
		default:
			break;
		}
	}
	break;
	case WM_KEYUP:
	{
		switch (LOWORD(wParam))
		{
		case 'W':
		case 'w':
			gpCamera->setMoveForward(false);
			break;
		case 'S':
		case 's':
			gpCamera->setMoveBackward(false);
			break;
		case 'A':
		case 'a':
			gpCamera->setMoveLeft(false);
			break;
		case 'D':
		case 'd':
			gpCamera->setMoveRight(false);
			break;
		case 'Q':
		case 'q':
			gpCamera->setMoveDown(false);
			break;
		case 'E':
		case 'e':
			gpCamera->setMoveUp(false);
			break;
		default:
			break;
		}
	}
	break;
	case WM_CHAR:
	{
		switch (LOWORD(wParam))
		{
		case 'F':
		case 'f':
			if (gbFullscreen == FALSE)
			{
				ToggleFullScreen();
				gbFullscreen = TRUE;
			}
			else
			{
				ToggleFullScreen();
				gbFullscreen = FALSE;
			}
			break;
		case 'I':
		case 'i':
			bShowImGui = !bShowImGui;
			break;
		case 'R':
		case 'r':
			bRotateCamera = !bRotateCamera;
			break;
		case 'L':
		case 'l':
			if (gpCamera && !gpCamera->m_bUseBezierCamera)
			{
				fprintf(gpFILE, "Spline Point -> Pos: vmath::vec3(%.2ff, %.2ff, %.2ff), Yaw: %.2ff, Pitch: %.2ff, Roll: %.2ff\n",
						gpCamera->m_position[0], gpCamera->m_position[1], gpCamera->m_position[2],
						gpCamera->m_yaw, gpCamera->m_pitch, gpCamera->m_roll);
				fflush(gpFILE);
			}
			break;
		case 'C':
		case 'c':
			gpCamera->m_bUseBezierCamera = !gpCamera->m_bUseBezierCamera;
			if (gpCamera->m_bUseBezierCamera == false) // Switching to free-look mode
			{
				// Synchronize free-look camera to the current Bezier camera's position and target
				if (gpCamera->m_pBezierPoints && gpCamera->m_pTimer)
				{
					int current_timer = *(gpCamera->m_pTimer);
					// Ensure there are enough points for the current position and a look-at target
					if (current_timer + 5 < gpCamera->m_pBezierPoints->size())
					{
						vmath::vec3 bezier_pos = vmath::vec3(
							(*gpCamera->m_pBezierPoints)[current_timer],
							(*gpCamera->m_pBezierPoints)[current_timer + 1],
							(*gpCamera->m_pBezierPoints)[current_timer + 2]);
						vmath::vec3 bezier_target = vmath::vec3(
							(*gpCamera->m_pBezierPoints)[current_timer + 3],
							(*gpCamera->m_pBezierPoints)[current_timer + 4],
							(*gpCamera->m_pBezierPoints)[current_timer + 5]);
						gpCamera->setCameraState(bezier_pos, bezier_target);
					}
					else
					{
						// Fallback if Bezier points are not sufficient, set a default sensible view for the terrain
						gpCamera->setCameraState(vmath::vec3(0.0f, 10.0f, 50.0f), vmath::vec3(0.0f, -6.0f, 0.0f));
					}
				}
			}
			break;
		default:
			break;
		}
	}
	break;

	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void ToggleFullScreen(void)
{
	// local variable declaration
	MONITORINFO mi = {sizeof(MONITORINFO)};

	// code
	if (gbFullscreen == FALSE)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);
		if (dwStyle & WS_OVERLAPPEDWINDOW)
		{
			if (GetWindowPlacement(ghwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
			{
				SetWindowLong(ghwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
				SetWindowPos(ghwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top, SWP_NOZORDER | SWP_FRAMECHANGED);
			}
		}
		ShowCursor(FALSE);
	}
	else
	{
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);
		ShowCursor(TRUE);
	}
}

int initialize(void)
{
	// function declarations
	void printGLInfo(void);
	void resize(int, int);
	void uninitialize(void);

	// LOG_ENTRY("log.txt", "In Initialize()");

	// variable declarations
	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormatIndex = 0;

	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	// step 1 :- Initialization of PIXELFORMATDESCRIPTOR
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cRedBits = 8;
	pfd.cGreenBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;
	pfd.cDepthBits = 32;

	// step 2 :- Get DC
	ghdc = GetDC(ghwnd);
	if (ghdc == NULL)
	{
		fprintf(gpFILE, "GetDC() Failed.\n");
		return (-1);
	}

	// step 3 :- Os will return pixel format index which is closest match to our pixel format descriptor
	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);
	if (iPixelFormatIndex == 0) // ChoosePixelFormat() return non zero positive on success , on failure return 0
	{
		fprintf(gpFILE, "ChoosePixelFormat() Failed.\n");
		return (-2);
	}

	// step 4 :- Set obtained pixel format
	if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE)
	{
		fprintf(gpFILE, "SetPixelFormat() Failed.\n");
		return (-3);
	}

	// step 5 :- Create OpenGL Context From Device Context(ghdc)
	ghrc = wglCreateContext(ghdc);
	if (ghrc == NULL)
	{
		fprintf(gpFILE, "wglCreateContext() Failed.\n");
		return (-4);
	}

	// step 6 :- Make rendering context current
	if (wglMakeCurrent(ghdc, ghrc) == FALSE)
	{
		fprintf(gpFILE, "wglMakeCurrent() Failed.\n");
		return (-5);
	}

	// Initialize GLEW
	if (glewInit() != GLEW_OK)
	{
		fprintf(gpFILE, "glewInit() Failed to initialize GLEW\n");
		return (-6);
	}

	// print GL Info
	printGLInfo();

	// model loading default code
	// code
	// Vertex Shader
	// step 1 : vertex shader code

	// const GLchar *vertexShaderSourceCode =
	// 	"#version 460 core" \
	// 	"\n" \
	// 	"in vec4 aPosition;" \
	// 	"in vec2 aTexCoord;" \
	// 	"uniform mat4 uModelMatrix;" \
	// 	"uniform mat4 uViewMatrix;" \
	// 	"uniform mat4 uProjectionMatrix;" \
	// 	"uniform vec4 uClippingPlane;" \
	// 	"out vec2 oTexCoord;" \
	// 	"void main(void)" \
	// 	"{" \
	// 	"vec4 worldSpacePosition = uModelMatrix * aPosition;" \
	// 	"gl_Position= uProjectionMatrix * uViewMatrix * worldSpacePosition;" \
	// 	"oTexCoord = aTexCoord;" \
	// 	"gl_ClipDistance[0] = dot(worldSpacePosition,uClippingPlane);" \
	// 	"}";

	// Vertex Shader
	// step 1 : vertex shader code
	const GLchar *vertexShaderSourceCode =
		"#version 460 core"
		"\n"
		"in vec4 aPosition;"
		"in vec2 aTexCoord;"
		"uniform mat4 uModelMatrix;"
		"uniform mat4 uViewMatrix;"
		"uniform mat4 uProjectionMatrix;"
		"out vec2 oTexCoord;"
		"void main(void)"
		"{"
		"gl_Position= uProjectionMatrix * uViewMatrix * uModelMatrix * aPosition;"
		"oTexCoord = aTexCoord;"
		"}";

	// step 2 : create vertex shader object
	GLuint vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	// step 3 : give vertex source code to openGL
	glShaderSource(vertexShaderObject, 1, (const GLchar **)&vertexShaderSourceCode, NULL);

	// step 4 : let OpenGL compile vertex shader
	glCompileShader(vertexShaderObject);

	// step 5 :
	GLint status = 0;
	GLint infoLogLength = 0;
	GLchar *szInfoLog = NULL;

	// step 5 a:
	glGetShaderiv(vertexShaderObject, GL_COMPILE_STATUS, &status);

	// step 5 b:
	if (status == GL_FALSE)
	{
		glGetShaderiv(vertexShaderObject, GL_INFO_LOG_LENGTH, &infoLogLength);

		if (infoLogLength > 0)
		{
			// step 5 c:
			szInfoLog = (GLchar *)malloc(sizeof(GLchar) * (infoLogLength + 1));

			if (szInfoLog != NULL)
			{

				// step 5 d:
				glGetShaderInfoLog(vertexShaderObject, infoLogLength + 1, NULL, szInfoLog);

				// step 5 e:
				fprintf(gpFILE, "Vertex shader compilation error log : %s\n", szInfoLog);

				// step 5 f:
				free(szInfoLog);

				szInfoLog = NULL;
			}
		}

		// step 5 g:
		uninitialize();
	}

	// // Fragment shader
	// // step 6 : write the fragement shader code
	// const GLchar *fragmentShaderCode =
	// 	"#version 460 core" \
	// 	"\n" \
	// 	"in vec2 oTexCoord;" \
	// 	"uniform sampler2D uTextureSampler;" \
	// 	"out vec4 FragColor;" \
	// 	"void main(void)" \
	// 	"{" \
	// 	"FragColor = texture(uTextureSampler,oTexCoord);" \
	// 	"}";

	// Fragment shader
	// step 6 : write the fragement shader code
	const GLchar *fragmentShaderCode =
		"#version 460 core"
		"\n"
		"in vec2 oTexCoord;"
		"uniform sampler2D uTextureSampler;"
		"uniform float alpha;"
		"out vec4 FragColor;"
		"void main(void)"
		"{"
		"	if(texture(uTextureSampler, oTexCoord).a < 0.1) discard;" // Discard fragments with low alpha for better blending
		"FragColor= texture(uTextureSampler, oTexCoord);"
		"}";

	// step 7 : create fragment shader object
	GLuint fragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);

	// step 8 : give fragment shader source code to OpenGL
	glShaderSource(fragmentShaderObject, 1, (const GLchar **)&fragmentShaderCode, NULL);

	// step 9 : let OpenGL compile fragment shader
	glCompileShader(fragmentShaderObject);

	// step 10 :
	status = 0;
	infoLogLength = 0;
	szInfoLog = NULL;

	// step 10 a:
	glGetShaderiv(fragmentShaderObject, GL_COMPILE_STATUS, &status);

	// step 10 b:
	if (status == GL_FALSE)
	{
		glGetShaderiv(fragmentShaderObject, GL_INFO_LOG_LENGTH, &infoLogLength);

		if (infoLogLength > 0)
		{
			// step 10 c:
			szInfoLog = (GLchar *)malloc(sizeof(GLchar) * (infoLogLength + 1));
			if (szInfoLog != NULL)
			{
				// step 10 d:
				glGetShaderInfoLog(fragmentShaderObject, infoLogLength + 1, NULL, szInfoLog);

				// step 10 e:
				fprintf(gpFILE, "fragmenet shader compilation log : %s\n", szInfoLog);

				// step 10 f:
				free(szInfoLog);

				szInfoLog = NULL;
			}
		}

		// step 10 g:
		uninitialize();
	}

	// shader program
	// step 11 : create shader program
	shaderProgramObject = glCreateProgram();

	// step 12 : attach shader to this program
	glAttachShader(shaderProgramObject, vertexShaderObject);
	glAttachShader(shaderProgramObject, fragmentShaderObject);

	// step 13 : bind attribute location with the shader program object
	glBindAttribLocation(shaderProgramObject, AMC_ATTRIBUTE_POSITION, "aPosition");
	glBindAttribLocation(shaderProgramObject, AMC_ATTRIBUTE_TEXCOORD, "aTexCoord");

	// step 14 : link the shader program
	glLinkProgram(shaderProgramObject);

	// step 15 : linking error check
	status = 0;
	infoLogLength = 0;
	szInfoLog = NULL;

	// step 15 a : get linking status
	glGetProgramiv(shaderProgramObject, GL_LINK_STATUS, &status);

	if (status == GL_FALSE)
	{
		// step 15 b :
		glGetProgramiv(shaderProgramObject, GL_INFO_LOG_LENGTH, &infoLogLength);

		if (infoLogLength > 0)
		{
			// step 15 c:
			szInfoLog = (GLchar *)malloc(sizeof(GLchar) * (infoLogLength + 1));

			if (szInfoLog != NULL)
			{
				// step 15 d:
				glGetProgramInfoLog(shaderProgramObject, infoLogLength + 1, NULL, szInfoLog);

				// step 15 e:
				fprintf(gpFILE, "Shader program linking error log : %s \n", szInfoLog);

				// step 15 f:
				free(szInfoLog);

				szInfoLog = NULL;
			}
		}

		// step 15 e:
		uninitialize();
	}

	// get shader uniform location
	modelMatrixUniform = glGetUniformLocation(shaderProgramObject, "uModelMatrix");
	viewMatrixUniform = glGetUniformLocation(shaderProgramObject, "uViewMatrix");
	projectionMatrixUniform = glGetUniformLocation(shaderProgramObject, "uProjectionMatrix");
	textureSamplerUniform = glGetUniformLocation(shaderProgramObject, "uTextureSampler");
	clippingPlaneUniform = glGetUniformLocation(shaderProgramObject, "uClippingPlane");

	// for enable depth
	glClearDepth(1.0f); // compulsory
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL); // Critical for skybox/sun pass passing depth checks

	// step 7 : - set clear color of window to blue (here OpenGL Start)
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Initialize Title
	InitializeTitle();

	initializeLightningWithFlash();

	initializeFogSystem();

	initializeBloom();
	hanumanGlowParams.position = vmath::vec3(0.04f, 6.39f, -47.68f);
	hanumanGlowParams.color = vmath::vec3(1.0f, 0.7f, 0.2f); // Divine golden glow
	hanumanGlowParams.radius = 8.0f;						 // Adjust scale for wider spread
	hanumanGlowParams.intensity = 1.2f;

	// Snowfall
	memset(&snowfallParams, 0, sizeof(snowfallParams));

	snowfallParams.bEnable = TRUE;
	snowfallParams.count = 200;
	snowfallParams.density = 1.0f / 40.0f;
	snowfallParams.depth = 80.0f;
	snowfallParams.gravity = 25.0f;
	snowfallParams.speed = 0.00007f;
	snowfallParams.windForce = 0.05f;
	snowfallParams.windMin = -0.08f;
	snowfallParams.windMax = 0.08f;
	snowfallParams.windEasing = 0.002f;
	snowfallParams.color = vmath::vec3(1.0f, 0.9804f, 0.9804f); // snow white color
	snowfallParams.opacity = 0.45f;
	snowfallParams.sizeMin = 1.f;
	snowfallParams.sizeMax = 4.0f;
	snowfallParams.texturePath = "./resources/Texture/blurSnowDrop.png";
	snowfallParams._time = 0.0f;

	// skybox - texturebased
	initializeSkybox();

	// Skydome - gradient
	initializeSkydome();

	// ---- Scene Lighting ----
	initializeSceneLighting();

	// Helper lambda to fill a LightSource with sane defaults
	auto makeLight = [](BOOL on,
						float px, float py, float pz,
						float ar, float ag, float ab,
						float dr, float dg, float db,
						float sr, float sg, float sb,
						float shin, float inten) -> LightSource
	{
		LightSource L;
		L.bEnable = on;
		L.position = vmath::vec3(px, py, pz);
		L.ambient = vmath::vec3(ar, ag, ab);
		L.diffuse = vmath::vec3(dr, dg, db);
		L.specular = vmath::vec3(sr, sg, sb);
		L.shininess = shin;
		L.intensity = inten;
		L.constant = 1.0f;
		L.linear = 0.0f; // no attenuation for distant studio lights
		L.quadratic = 0.0f;
		return L;
	};

	// ---- SCENE INTERIOR CAVE — Hanumanji ----
	caveInteriorScene_HanumajiLights.bEnableLighting = TRUE;
	//           en    Px     Py    Pz    aR   aG   aB    dR   dG   dB    sR   sG   sB   shin  inten
	caveInteriorScene_HanumajiLights.keyLight = makeLight(TRUE, 0.0f, -460.0f, 62.0f, 0.1294f, 0.0824f, 0.0588f, 0.1020f, 0.0588f, 0.0235f, 0.0f, 0.0f, 0.0f, 32.0f, 2.0f);
	caveInteriorScene_HanumajiLights.fillLight = makeLight(TRUE, 0.0f, 9.450f, 60.0f, 0.0196f, 0.0314f, 0.0510f, 0.2667f, 0.3412f, 0.4549f, 0.0f, 0.0f, 0.0f, 8.0f, 0.4f);
	caveInteriorScene_HanumajiLights.backLight = makeLight(FALSE, 0.0f, -620.0f, 40.0f, 0.0f, 0.0f, 0.0f, 0.60f, 0.30f, 0.05f, 0.80f, 0.50f, 0.10f, 64.0f, 1.2f);

	// ---- SCENE Flying, YuddhaScene 1, 2  General Hanumanji Light----
	generalHanumanJiLights.bEnableLighting = TRUE;
	//           en      Px       Py        Pz      aR      aG      aB      dR      dG      dB      sR      sG      sB     shin   inten
	generalHanumanJiLights.keyLight = makeLight(TRUE, -80.0f, 200.0f, -1000.0f, 0.06f, 0.04f, 0.02f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 24.0f, 2.2f);
	generalHanumanJiLights.fillLight = makeLight(TRUE, 120.0f, 500.0f, 100.0f, 0.03f, 0.04f, 0.07f, 0.18f, 0.24f, 0.38f, 0.0f, 0.0f, 0.0f, 8.0f, 0.55f);
	generalHanumanJiLights.backLight = makeLight(TRUE, 0.0f, -1200.0f, 400.0f, 0.00f, 0.00f, 0.00f, 131.0f / 255.0f, 131.0f / 255.0f, 131.0f / 255.0f, 0.0f, 0.0f, 0.0f, 48.0f, 1.5f);

	// ---- MOUNTAIN CAVE EXTERIOR — Snow Terrain Lights ----
	mountainExteriorSceneLights.bEnableLighting = TRUE;
	// Cold bright sun for snow: En, Px, Py, Pz, aR, aG, aB, dR, dG, dB, sR, sG, sB, shin, inten
	mountainExteriorSceneLights.keyLight = makeLight(TRUE, -500.0f, 1000.0f, 500.0f, 0.1f, 0.1f, 0.15f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 128.0f, 1.5f);
	mountainExteriorSceneLights.fillLight = makeLight(TRUE, 500.0f, 200.0f, -500.0f, 0.0f, 0.0f, 0.05f, 0.4f, 0.5f, 0.7f, 0.0f, 0.0f, 0.0f, 64.0f, 0.6f);
	mountainExteriorSceneLights.backLight = makeLight(FALSE, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

	// ---- SCENE SabhaMandap — Throne (neutral studio) ----
	sabhamandapScene_ThroneLights.bEnableLighting = TRUE;
	//           en    Px     Py    Pz    aR   aG   aB    dR   dG   dB    sR   sG   sB   shin  inten
	sabhamandapScene_ThroneLights.keyLight = makeLight(TRUE, 0.0f, -100.0f, 100.0f, 0.0f, 0.0f, 0.0f, 0.7569, 0.7569, 0.7569, 0.4235, 0.3569, 0.3569, 128.0f, 1.0f);
	sabhamandapScene_ThroneLights.fillLight = makeLight(TRUE, 0.0f, 450.0f, 200.0f, 0.0f, 0.0f, 0.0f, 0.6275, 0.6275, 0.6275, 0.5255, 0.5255, 0.5255, 128.0f, 1.0f);
	sabhamandapScene_ThroneLights.backLight = makeLight(TRUE, 0.0f, 0.0f, -100.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 128.0f, 1.0f);

	// ---- SCENE SabhaMandap — Throne (neutral studio) ----
	flyingHanumanJiLights.bEnableLighting = TRUE;
	//           en    Px     Py    Pz    aR   aG   aB    dR   dG   dB    sR   sG   sB   shin  inten
	flyingHanumanJiLights.keyLight = makeLight(TRUE, 0.0f, 5000.0f, 100.0f, 0.0f, 0.0f, 0.0f, 0.7569, 0.7569, 0.7569, 0.4235, 0.3569, 0.3569, 128.0f, 1.0f);
	flyingHanumanJiLights.fillLight = makeLight(TRUE, 0.0f, 5000.0f, 200.0f, 0.0f, 0.0f, 0.0f, 0.6275, 0.6275, 0.6275, 0.5255, 0.5255, 0.5255, 128.0f, 1.0f);
	flyingHanumanJiLights.backLight = makeLight(TRUE, 0.0f, 1000.0f, -100.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 128.0f, 1.0f);

	// // ---- SCENE SabhaMandap — HanumanJi (warm divine golden light) ----
	sabhamandapScene_HanumajiLights.bEnableLighting = TRUE;
	sabhamandapScene_HanumajiLights.keyLight = makeLight(TRUE, 10.0f, -5.0f, 8.0f, 0.08f, 0.06f, 0.02f, 1.0f, 0.85f, 0.5f, 1.0f, 0.9f, 0.6f, 64.0f, 1.8f);
	sabhamandapScene_HanumajiLights.fillLight = makeLight(FALSE, -8.0f, -8.0f, 5.0f, 0.03f, 0.03f, 0.05f, 0.3f, 0.4f, 0.7f, 0.2f, 0.2f, 0.4f, 32.0f, 0.5f);
	sabhamandapScene_HanumajiLights.backLight = makeLight(TRUE, 0.0f, -5.0f, -12.0f, 0.04f, 0.03f, 0.01f, 1.0f, 0.9f, 0.6f, 1.0f, 0.95f, 0.7f, 128.0f, 1.0f);

	// ---- SCENE SabhaMandap — Vibhishan (cool dramatic, night feel) ----
	sabhamandapScene_VibhishanLights.bEnableLighting = TRUE;
	sabhamandapScene_VibhishanLights.keyLight = makeLight(TRUE, 8.0f, -5.0f, 6.0f, 0.04f, 0.04f, 0.06f, 0.7f, 0.8f, 1.0f, 0.8f, 0.9f, 1.0f, 64.0f, 1.2f);
	sabhamandapScene_VibhishanLights.fillLight = makeLight(FALSE, -6.0f, -8.0f, 4.0f, 0.02f, 0.02f, 0.04f, 0.3f, 0.3f, 0.5f, 0.1f, 0.1f, 0.3f, 16.0f, 0.4f);
	sabhamandapScene_VibhishanLights.backLight = makeLight(TRUE, 0.0f, -5.0f, -10.0f, 0.02f, 0.02f, 0.04f, 0.5f, 0.5f, 0.8f, 0.8f, 0.8f, 1.0f, 128.0f, 0.7f);

	// ---- SCENE RamVachan (cool dramatic, night feel) ----
	ramvachanLights.bEnableLighting = TRUE;
	ramvachanLights.keyLight = makeLight(TRUE, 0.0f, 50.0f, -62.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 128.0f, 1.2f);
	ramvachanLights.fillLight = makeLight(FALSE, -6.0f, -8.0f, 4.0f, 0.02f, 0.02f, 0.04f, 0.3f, 0.3f, 0.5f, 0.1f, 0.1f, 0.3f, 16.0f, 0.4f);
	ramvachanLights.backLight = makeLight(FALSE, 0.0f, -5.0f, -10.0f, 0.02f, 0.02f, 0.04f, 0.5f, 0.5f, 0.8f, 0.8f, 0.8f, 1.0f, 128.0f, 0.7f);

	// ---- Skydome Defaults ----
	setupSkydomeDefaults(skydomeParams);

	// God Rays
	initializeGodRays();

	// Sun world position — align with skydome sun direction
	godRaysParams.sunWorldPos = vmath::vec3(0.0f, 150.0f, -800.0f);

	// Ray appearance
	godRaysParams.rayColor = vmath::vec3(1.00f, 0.88f, 0.60f);
	godRaysParams.exposure = 0.020f;
	godRaysParams.decay = 0.97f;
	godRaysParams.density = 0.96f;
	godRaysParams.weight = 0.45f;
	godRaysParams.numSamples = 80;

	// Occlusion disc
	godRaysParams.bShowOcclusionDisc = TRUE;
	godRaysParams.discRadius = 0.06f;

	// Corona
	godRaysParams.bShowCorona = TRUE;
	godRaysParams.coronaColor = vmath::vec3(1.00f, 0.95f, 0.70f);
	godRaysParams.coronaSize = 0.05f;
	godRaysParams.coronaStrength = 3.0f;

	

	// Sun world position — align with skydome sun direction
	godRaysParams.sunWorldPos = vmath::vec3(0.0f, 150.0f, -800.0f);

	// Ray appearance
	godRaysParams.rayColor = vmath::vec3(1.00f, 0.88f, 0.60f);
	godRaysParams.exposure = 0.020f;
	godRaysParams.decay = 0.97f;
	godRaysParams.density = 0.96f;
	godRaysParams.weight = 0.45f;
	godRaysParams.numSamples = 80;

	// Occlusion disc
	godRaysParams.bShowOcclusionDisc = TRUE;
	godRaysParams.discRadius = 0.06f;

	// Corona
	godRaysParams.bShowCorona = TRUE;
	godRaysParams.coronaColor = vmath::vec3(1.00f, 0.95f, 0.70f);
	godRaysParams.coronaSize = 0.05f;
	godRaysParams.coronaStrength = 3.0f;

	// Sun world position — align with skydome sun direction
	godRaysParamsForRamWorship.sunWorldPos = vmath::vec3(10000.0f, 6300.0f, 3300.0f);

	// Ray appearance
	godRaysParamsForRamWorship.rayColor = vmath::vec3(1.00f, 0.88f, 0.60f);
	godRaysParamsForRamWorship.exposure = 0.020f;
	godRaysParamsForRamWorship.decay = 0.97f;
	godRaysParamsForRamWorship.density = 0.1f;
	godRaysParamsForRamWorship.weight = 0.10f;
	godRaysParamsForRamWorship.numSamples = 16;

	// Occlusion disc
	godRaysParamsForRamWorship.bShowOcclusionDisc = TRUE;
	godRaysParamsForRamWorship.discRadius = 0.06f;

	// Corona
	godRaysParamsForRamWorship.bShowCorona = TRUE;
	godRaysParamsForRamWorship.coronaColor = vmath::vec3(1.00f, 0.95f, 0.70f);
	godRaysParamsForRamWorship.coronaSize = 0.150f;
	godRaysParamsForRamWorship.coronaStrength = 3.0f;

	// ---- Ocean ----
	// Re-use the existing waterDuDvMapTexture loaded above.
	// g_skyboxCubemapForOcean is filled by getSkyboxCubemapID() from Skybox.cpp (see Section 6).
	// #if OCEAN_USE == 1
	// 	g_skyboxCubemapForOcean = getSkyboxCubemapID();
	// 	initializeOcean(waterDuDvMapTexture.id, g_skyboxCubemapForOcean);

	// 	// Ocean default params  (stormy open sea look matching sample image)
	// 	oceanParams.translation = vmath::vec3(0.0f, -40.0f, 0.0f);
	// 	oceanParams.scale = vmath::vec3(2700.0f, 350.0f, 2000.0f);

	// 	// --- CUSTOMIZABLE WAVE / TIDE FACTORS ---
	// 	oceanParams.tideSpeed = 5.94f;			// overall animation speed (0=frozen, 3=stormy fast)
	// 	oceanParams.waveHeight = 7.80f;			// crest-to-trough amplitude in world units
	// 	oceanParams.waveChoppiness = 1.590f;		// 0=smooth sine, 1=sharp Gerstner peaks
	// 	oceanParams.waveFrequency = 0.6f;		// spatial frequency (higher = smaller waves)
	// 	oceanParams.waveDirectionAngle = 75.0f; // degrees – primary swell direction

	// 	// DuDv surface detail
	// 	oceanParams.waveStrength = 0.0f;
	// 	oceanParams.tiling = 9.500f;
	// 	oceanParams.moveFactor = 0.0f;

	// 	// Color (dark stormy ocean matching sample image)
	// 	oceanParams.shallowColor = vmath::vec3(15.0f / 255.0f, 45.0f / 255.0f, 90.0f / 255.0f); // stormy grey-blue crest
	// 	oceanParams.deepColor = vmath::vec3(0.0f, 0.3f, 0.5f);									// deep dark navy
	// 	oceanParams.colorBlendSharpness = 10.0f;
	// 	oceanParams.foamColor = vmath::vec3(207.0f / 255.0f, 214.0f / 255.0f, 234.0f / 255.0f); // white-grey foam
	// 	oceanParams.foamThreshold = 6.0f;														// Y above which foam appears

	// 	// Lighting
	// 	oceanParams.specularStrength = 1.0f; // bright sun glint
	// 	oceanParams.shininess = 51.0f;
	// 	oceanParams.sunElevation = 23.500f;
	// 	oceanParams.sunAzimuth = 180.0f;
	// 	oceanParams.sunColor = vmath::vec3(220.0f / 255.0f, 110.0f / 255.0f, 0.0f);
	// #else
	if (!initializeOcean(getSkyboxCubemapID()))
	{
		LOG("Ocean init failed\n");
		return -11;
	}
	getDefaultStormPreset(gOcean);

	// Example: Globally reduce wave amplitude by half
	for (int i = 0; i < gOcean.numWaves; ++i)
	{
		gOcean.waves[i].amplitude *= 0.4f;
	}
	// #endif

	// Load the models
	extern void initializeModelsConfig(void);
	initializeModelsConfig();

	// ---------------------- pre water initialization ----------------------------
	waterReflectionFramebuffer = createFramebuffer();
	GLuint reflectionTexture = createFramebufferTextureAndAttached(waterReflectionFramebuffer, GL_COLOR_ATTACHMENT0, screenWidth, screenHeight);

	createFramebufferDepthRenderbuffer(waterReflectionFramebuffer, screenWidth, screenHeight);

	waterRefractionFramebuffer = createFramebuffer();

	GLuint refractionTexture = createFramebufferTextureAndAttached(waterRefractionFramebuffer, GL_COLOR_ATTACHMENT0, screenWidth, screenHeight);

	GLuint refractionDepthTexture = createFramebufferDepthRenderbuffer(waterRefractionFramebuffer, screenWidth, screenHeight);

	// Water
	waterDuDvMapTexture = loadTexture("./resources/Texture/waterDUDV.png", FALSE);
	initializeWater(reflectionTexture, refractionTexture, refractionDepthTexture, waterDuDvMapTexture.id);
	waterParams[0].translation = vmath::vec3(0.0f, 8.8f, 38.0f);
	waterParams[0].scale = vmath::vec3(200.0f, 15.0f, 70.0f);
	waterParams[0].titling = 6.0f;
	waterParams[0].waveStrength = 0.01f;
	waterParams[0].moveFactor = 0.0f;
	waterParams[0].tintColor = vmath::vec3(0.0f, 0.5294f, 0.5294f);
	waterParams[0].tintFactor = 0.2f;
	waterParams[0].waterDirection = vmath::vec2(1.0f, 0.0f);
	waterParams[0].movementMode = 0; // original working mode

	waterParams[1].translation = vmath::vec3(0.0f, -35.0f, 0.0f);
	waterParams[1].scale = vmath::vec3(390.0f, 1.0f, 500.0f);
	waterParams[1].titling = 6.0f;
	waterParams[1].waveStrength = 0.2f;
	waterParams[1].moveFactor = 0.0f;
	waterParams[1].tintColor = vmath::vec3(0.0f, 0.3f, 0.7f);
	waterParams[1].tintFactor = 0.2f;
	waterParams[1].waterDirection = vmath::vec2(-1.0f, 0.0f); // -X Direction
	waterParams[1].movementMode = 1;						  // directional mode

	initializeWaterfall();
	waterfallParams.translation = vmath::vec3(-252.26f, -4.55f, 285.00f);
	waterfallParams.scale = vmath::vec3(40.0f, 27.0f, 7.0f);
	waterfallParams.rotationAngle[0] = -43.0f;
	waterfallParams.rotationAxis[0] = vmath::vec3(1.0f, 0.0f, 0.0f);
	waterfallParams.rotationAngle[1] = 90.0f;
	waterfallParams.rotationAxis[1] = vmath::vec3(0.0f, 1.0f, 0.0f);
	waterfallParams.rotationAngle[2] = -10.0f;
	waterfallParams.rotationAxis[2] = vmath::vec3(0.0f, 0.0f, 1.0f);

	// Camera
	for (float t = 0.0f; t <= 1.0f; t = t + 0.0015f)
	{
		float x = pow((1 - t), 3) * controlPoints[0][0] +
				  3 * pow((1 - t), 2) * t * controlPoints[1][0] +
				  3 * (1 - t) * pow(t, 2) * controlPoints[2][0] +
				  pow(t, 3) * controlPoints[3][0];

		float y = pow((1 - t), 3) * controlPoints[0][1] +
				  3 * pow((1 - t), 2) * t * controlPoints[1][1] +
				  3 * (1 - t) * pow(t, 2) * controlPoints[2][1] +
				  pow(t, 3) * controlPoints[3][1];

		float z = pow((1 - t), 3) * controlPoints[0][2] +
				  3 * pow((1 - t), 2) * t * controlPoints[1][2] +
				  3 * (1 - t) * pow(t, 2) * controlPoints[2][2] +
				  pow(t, 3) * controlPoints[3][2];

		BezierPoints.push_back(x);
		BezierPoints.push_back(y);
		BezierPoints.push_back(z);
	}
	gpCamera = new Camera(vmath::vec3(0.0f, 0.0f, -3.0f), 0.0f, 0.0f, CAMERA_SPEED, &BezierPoints, &timer);
	gpCamera->m_bUseBezierCamera = true; // AMP: Make it true when need bazier curve

	// Initialize rotating camera
	camera_Ocean = new BSplineCamera();
	camera_Ocean->setupStableCamera(vmath::vec3(25.57f, 5.30f, 148.95f), 266.48f, 12.10f, 0.0f);

	// std::vector<vmath::vec3> positionsOcean(17, vmath::vec3(18.59f, 5.41f, 99.82f)); // All 17 points are the same position

	// std::vector<float> yawsOcean = {
	// 	276.58f};

	// std::vector<float> pitchesOcean(1, 3.70f);

	// std::vector<float> rollsOcean(1, 0.0f); // All rolls are 0.0f

	// camera_Ocean->setBSplinePoints(positionsOcean, yawsOcean, pitchesOcean, rollsOcean);

	// -----------------------------------------------------------------------------------------------------

	// Initialize Yuddha Scene 1 - Pan camera
	camera_YuddhaScene1 = new BSplineCamera();
	positionsYuddhaScene1 = {
		// vmath::vec3(25.54f, 114.46f, -334.61f),
		// vmath::vec3(25.54f, 114.46f, -334.61f),
		// vmath::vec3(25.54f, 114.46f, -334.61f),
		// vmath::vec3(25.54f, 114.46f, -334.61f),
		// vmath::vec3(25.54f, 114.46f, -334.61f),
		// vmath::vec3(23.08f, 70.34f, -371.16f),
		// vmath::vec3(41.91f, 43.95f, -407.44f),
		// vmath::vec3(93.95f, 40.17f, -389.56f),
		// vmath::vec3(100.50f, 37.30f, -347.43f),
		// vmath::vec3(43.30f, 36.70f, -353.30f),
		// vmath::vec3(-13.89f, 36.09f, -359.17f),
		// vmath::vec3(-71.08f, 35.49f, -365.03f),
		// vmath::vec3(-128.30f, 34.89f, -370.92f),
		// vmath::vec3(-185.46f, 34.30f, -376.78f),
		// vmath::vec3(-241.83f, 34.46f, -367.22f),
		// vmath::vec3(-288.33f, 35.79f, -334.55f),
		// vmath::vec3(-297.39f, 36.82f, -288.66f),
		// vmath::vec3(-244.03f, 36.50f, -268.04f),
		// vmath::vec3(-187.58f, 36.33f, -259.98f),
		// vmath::vec3(-138.43f, 36.33f, -230.28f),
		// vmath::vec3(-85.60f, 43.09f, -208.62f),
		// vmath::vec3(-47.96f, 48.60f, -165.67f),
		// vmath::vec3(1.02f, 64.82f, -140.31f),
		// vmath::vec3(45.43f, 85.42f, -112.09f),
		// vmath::vec3(71.49f, 84.42f, -62.63f),
		// vmath::vec3(61.30f, 86.42f, -6.12f),
		// vmath::vec3(54.11f, 92.35f, 50.34f),
		// vmath::vec3(31.83f, 112.02f, 99.56f),
		// vmath::vec3(31.83f, 112.02f, 99.56f),
		// vmath::vec3(31.83f, 112.02f, 99.56f),
		// vmath::vec3(31.83f, 112.02f, 99.56f)

		vmath::vec3(25.54, 114.46, -334.61),
		vmath::vec3(25.54, 114.46, -334.61),
		vmath::vec3(25.54, 114.46, -334.61),
		vmath::vec3(25.54, 114.46, -334.61),
		vmath::vec3(25.54, 114.46, -334.61),
		vmath::vec3(23.08, 70.34, -371.16),
		vmath::vec3(41.91, 43.95, -407.44),
		vmath::vec3(93.95, 40.17, -389.56),
		vmath::vec3(100.5, 37.3, -347.43),
		vmath::vec3(43.3, 36.7, -353.3),
		vmath::vec3(-13.89, 36.09, -359.17),
		vmath::vec3(-71.08, 35.49, -365.03),
		vmath::vec3(-128.3, 34.89, -370.92),
		vmath::vec3(-185.46, 34.3, -376.78),
		vmath::vec3(-241.83, 34.46, -367.22),
		vmath::vec3(-288.33, 35.79, -334.55),
		vmath::vec3(-297.39, 36.82, -288.66),
		vmath::vec3(-244.03, 36.5, -268.04),
		vmath::vec3(-187.58, 36.33, -259.98),
		vmath::vec3(-138.43, 36.33, -230.28),
		vmath::vec3(-85.6, 43.09, -208.62),
		vmath::vec3(-47.96, 48.6, -165.67),
		vmath::vec3(1.02, 64.82, -140.31),
		vmath::vec3(45.43, 65.32, -112.09),
		vmath::vec3(71.49, 66.72, -62.63),
		vmath::vec3(61.3, 66.72, -6.12),
		vmath::vec3(54.11, 66.72, 50.34),
		vmath::vec3(54.11, 66.72, 50.34),
		vmath::vec3(54.11, 66.72, 50.34),
		vmath::vec3(54.11, 66.72, 50.34),
		vmath::vec3(54.11, 66.72, 50.34),
		vmath::vec3(54.11, 66.72, 50.34),
		vmath::vec3(54.11, 66.72, 50.34),
		vmath::vec3(54.11, 66.72, 50.34),
		vmath::vec3(54.11, 66.72, 50.34),
		vmath::vec3(54.11, 66.72, 50.34),
		vmath::vec3(54.11, 66.72, 50.34),
		// vmath::vec3(31.83, 66.72, 99.56),
		// vmath::vec3(31.83, 66.72, 99.56),
		// vmath::vec3(31.83, 66.72, 99.56),
		// vmath::vec3(31.83, 66.72, 99.56),

	};

	std::vector<float> yawsYuddhaScene1 = {
		264.68f,
		264.68f,
		264.68f,
		265.18f,
		260.69f,
		248.76f,
		263.58f,
		263.58f,
		263.58f,
		263.58f,
		263.58f,
		263.58f,
		263.63f,
		263.76f,
		263.88f,
		263.88f,
		263.88f,
		263.88f,
		263.88f,
		263.89f,
		264.32f,
		263.68f,
		263.68f,
		263.68f,
		263.68f,
		263.68f,
		263.68f,
		263.68f,
		263.68f,
		263.68f,
		263.68f,
		263.68f,
		263.68f,
		263.68f,
		// 263.68f, 263.68f, 263.68f
	};

	std::vector<float> pitchesYuddhaScene1 = {
		30.70f,
		30.70f,
		30.70f,
		15.63f,
		12.05f,
		6.85f,
		-2.80f,
		-2.80f,
		-2.80f,
		-2.80f,
		-2.80f,
		-2.80f,
		-2.09f,
		-0.37f,
		0.70f,
		0.70f,
		0.70f,
		0.70f,
		0.70f,
		0.70f,
		3.18f,
		-4.50f,
		-4.50f,
		-4.50f,
		-4.50f,
		-4.50f,
		-4.50f,
		-4.50f,
		-4.50f,
		-4.50f,
		-4.50f,
		-4.50f,
		-4.50f,
		-4.50f,
		// -4.50f, -4.50f, -4.50f
	};

	std::vector<float> rollsYuddhaScene1(
		positionsYuddhaScene1.size(),
		0.0f);

	camera_YuddhaScene1->setBSplinePoints(
		positionsYuddhaScene1,
		yawsYuddhaScene1,
		pitchesYuddhaScene1,
		rollsYuddhaScene1);

	// -----------------------------------------------------------------------------------------------------

	// Initialize Yuddha Scene 2 - Pan camera
	camera_YuddhaScene2 = new BSplineCamera();
	std::vector<vmath::vec3> positionsYuddhaScene2 = {
		vmath::vec3(4.79f, 33.47f, -13.92f),  // Clamp start
		vmath::vec3(4.79f, 33.47f, -13.92f),  // Clamp start
		vmath::vec3(4.79f, 33.47f, -13.92f),  // 0
		vmath::vec3(3.23f, 29.71f, -18.46f),  // 1
		vmath::vec3(2.56f, 28.11f, -20.40f),  // 2
		vmath::vec3(1.98f, 26.70f, -22.12f),  // 3
		vmath::vec3(1.36f, 25.22f, -23.90f),  // 4
		vmath::vec3(0.93f, 24.17f, -25.17f),  // 5
		vmath::vec3(0.42f, 22.94f, -26.66f),  // 6
		vmath::vec3(-0.12f, 21.65f, -28.23f), // 7
		vmath::vec3(-0.63f, 20.42f, -29.72f), // 8
		vmath::vec3(-0.58f, 18.76f, -29.58f), // 9
		vmath::vec3(-0.99f, 17.78f, -30.77f), // 10
		vmath::vec3(-1.71f, 16.05f, -32.86f), // 11
		vmath::vec3(-2.37f, 14.45f, -34.79f), // 12
		vmath::vec3(-0.51f, 12.38f, -42.00f), // Smooth interpolation
		vmath::vec3(1.35f, 10.31f, -49.21f),  // Smooth interpolation
		vmath::vec3(3.21f, 8.24f, -56.42f),	  // Target
		vmath::vec3(3.21f, 8.24f, -56.42f),	  // Clamp end 1
		vmath::vec3(3.21f, 8.24f, -56.42f),	  // Clamp end 2
		vmath::vec3(3.21f, 8.24f, -56.42f),	  // Clamp end 3
		vmath::vec3(3.21f, 8.24f, -56.42f),	  // Clamp end 4
		vmath::vec3(3.21f, 8.24f, -56.42f)	  // Clamp end 5
	};

	std::vector<float> yawsYuddhaScene2 = {
		71.08f, 71.08f, 71.08f, 71.08f, 71.08f, 71.08f, 71.08f, 71.08f,
		71.08f, 71.08f, 71.08f, 71.08f, 71.08f, 71.08f, 71.08f,
		76.78f, 82.48f, 88.18f,
		88.18f, 88.18f, 88.18f, 88.18f, 88.18f};

	std::vector<float> pitchesYuddhaScene2 = {
		38.00f, 38.00f, 38.00f, 38.00f, 38.00f, 38.00f, 38.00f, 38.00f,
		38.00f, 38.00f, 38.00f, 38.00f, 38.00f, 38.00f, 38.00f,
		32.73f, 27.46f, 22.20f,
		22.20f, 22.20f, 22.20f, 22.20f, 22.20f};

	std::vector<float> rollsYuddhaScene2(23, 0.0f);

	camera_YuddhaScene2->setBSplinePoints(
		positionsYuddhaScene2,
		yawsYuddhaScene2,
		pitchesYuddhaScene2,
		rollsYuddhaScene2);

	// -----------------------------------------------------------------------------------------------------

	// Cave Interior camera
	// New Camera
	camera_CaveInterior = new BSplineCamera();
	camera_CaveInterior->setup360RotationCamera(vmath::vec3(-8.30f, 5.5f, -38.83f), 0.0f, 0.0f, 0.0f, 2);

	std::vector<vmath::vec3> positionsCaveInterior = {
		vmath::vec3(-5.00f, -42.00f, 212.00f),
		vmath::vec3(-3.65f, -35.82f, 190.00f),
		vmath::vec3(-2.30f, -29.65f, 168.00f),
		vmath::vec3(-0.93f, -22.58f, 146.26f),
		vmath::vec3(0.12f, -14.11f, 124.98f),
		vmath::vec3(0.51f, -7.23f, 103.22f),
		vmath::vec3(0.88f, -1.31f, 81.12f),
		vmath::vec3(1.49f, 1.94f, 58.44f),
		vmath::vec3(1.98f, -1.85f, 35.85f),
		vmath::vec3(-15.90f, -5.00f, 22.56f),
		vmath::vec3(-32.39f, -4.78f, 7.54f),
		vmath::vec3(-33.18f, -4.20f, -12.84f),
		vmath::vec3(-30.00f, -3.79f, -35.09f),
		vmath::vec3(-25.30f, -3.76f, -57.29f),
		vmath::vec3(-11.52f, -3.90f, -73.24f),
		vmath::vec3(9.99f, -4.00f, -75.27f),
		vmath::vec3(29.20f, -3.90f, -64.31f),
		vmath::vec3(40.12f, -3.48f, -45.42f),
		vmath::vec3(36.81f, -3.01f, -23.73f),
		vmath::vec3(25.33f, -2.89f, -4.33f),
		vmath::vec3(6.26f, -3.67f, 7.36f), // arrive
		vmath::vec3(6.26f, -3.67f, 7.36f), // hold ~0.33s
		vmath::vec3(6.26f, -3.67f, 7.36f), // hold ~0.33s
		vmath::vec3(6.26f, -3.67f, 7.36f), // hold ~0.33s — 1.0s total
		vmath::vec3(6.26f, -3.67f, 7.36f), // Clamp end
		vmath::vec3(6.26f, -3.67f, 7.36f)  // Clamp end
	};

	std::vector<float> yawsCaveInterior = {
		273.00f,
		272.61f, 272.23f,
		271.81f, 271.29f, 270.65f, 270.03f, 270.98f, 274.85f, 294.88f, 320.98f,
		350.05f, 377.15f, 399.70f, 423.10f, 451.35f, 485.44f, 523.52f, 556.52f,
		588.08f,
		622.48f,				   // arrive
		622.48f, 622.48f, 622.48f, // hold x3
		622.48f, 622.48f		   // clamp
	};

	std::vector<float> pitchesCaveInterior = {
		18.00f,
		19.35f, 20.70f,
		21.92f, 21.53f, 17.23f, 12.25f, 8.08f, 5.11f, 4.88f, 4.28f,
		4.00f, 3.66f, 3.21f, 3.00f, 3.82f, 4.24f, 2.41f, 0.06f,
		-1.22f,
		-0.20f,					// arrive
		-0.20f, -0.20f, -0.20f, // hold x3
		-0.20f, -0.20f			// clamp
	};

	std::vector<float> rollsCaveInterior(26, 0.0f); // All rolls are 0.0f

	camera_CaveInterior->setBSplinePoints(positionsCaveInterior, yawsCaveInterior, pitchesCaveInterior, rollsCaveInterior);
	// -----------------------------------------------------------------------------------------------------
	// Flying camera
	camera_FlyingScene = new BSplineCamera();
	// camera_FlyingScene->setupStableCamera(vmath::vec3(6.69f, 1400.00f, 36.86f), 253.88f, -2.10f, 0.0f);
	camera_FlyingScene->setupStableCamera(vmath::vec3(-261.46f, 1409.20f, 23.85f), 329.78f, -3.80f, 0.00f);

	// -----------------------------------------------------------------------------------------------------
	camera_SnowTerrain = new BSplineCamera();

	std::vector<vmath::vec3> positionsScene2 = {
		vmath::vec3(-328.57f, 235.19f, -536.67f),
		vmath::vec3(-328.57f, 235.19f, -536.67f),
		vmath::vec3(-328.57f, 235.19f, -536.67f),
		vmath::vec3(-213.79f, 192.79f, -458.39f),
		vmath::vec3(-98.93f, 171.00f, -416.98f),
		vmath::vec3(23.80f, 174.30f, -344.92f),
		vmath::vec3(124.95f, 138.10f, -267.09f),
		vmath::vec3(211.52f, 85.00f, -188.75f),
		vmath::vec3(280.30f, 40.27f, -40.68f),
		vmath::vec3(302.94f, 15.53f, 100.90f),
		vmath::vec3(250.14f, 6.25f, 213.71f),
		vmath::vec3(152.46f, 9.09f, 216.74f),
		vmath::vec3(50.23f, 20.65f, 230.17f),
		vmath::vec3(-46.39f, 44.77f, 291.31f),
		vmath::vec3(-110.00f, 52.00f, 240.00f),
		vmath::vec3(-172.72f, 40.04f, 111.35f),
		vmath::vec3(-172.72f, 40.04f, 111.35f),
		vmath::vec3(-172.72f, 40.04f, 111.35f)};

	std::vector<float> yawsScene2 = {
		32.28f, 32.28f, 32.28f, 26.38f, 24.00f, 30.00f, 45.00f, 65.00f,
		95.00f, 130.00f, 160.00f, 185.00f, 205.00f, 225.00f, 235.00f, 238.18f,
		238.18f, 238.18f};

	std::vector<float> pitchesScene2 = {
		-9.00f, -9.00f, -9.00f, -7.70f, -4.50f, -2.00f, -10.00f, -15.00f,
		-12.00f, -8.00f, -3.00f, 0.00f, 0.00f, -2.00f, -5.00f, -7.80f,
		-7.80f, -7.80f};

	std::vector<float> rollsScene2(18, 0.0f); // All rolls are 0.0f

	camera_SnowTerrain->setBSplinePoints(positionsScene2, yawsScene2, pitchesScene2, rollsScene2);

	// -----------------------------------------------------------------------------------------------------
	camera_SabhaMandapScene = new BSplineCamera();

	std::vector<vmath::vec3> positionsScene3 = {
		vmath::vec3(-19.83f, 4.77f, -6.43f),
		vmath::vec3(-19.83f, 4.77f, -6.43f),
		vmath::vec3(-19.83f, 4.77f, -6.43f),
		vmath::vec3(-20.12f, 4.76f, 0.43f),
		vmath::vec3(-16.63f, 4.76f, 5.80f),
		vmath::vec3(-15.59f, 5.67f, 7.90f),
		vmath::vec3(-12.75f, 4.71f, 8.74f),
		vmath::vec3(-11.00f, 4.74f, 9.10f),
		vmath::vec3(-7.56f, 4.81f, 7.06f),
		vmath::vec3(5.20f, 4.95f, 9.14f),
		vmath::vec3(13.24f, 4.95f, 5.61f),
		vmath::vec3(15.85f, 4.95f, 3.76f),
		vmath::vec3(19.96f, 4.95f, -1.14f),
		vmath::vec3(19.74f, 4.84f, -4.02f),
		vmath::vec3(17.72f, 4.61f, -6.96f),
		vmath::vec3(15.85f, 4.49f, -11.73f),
		vmath::vec3(15.85f, 4.49f, -11.73f),
		vmath::vec3(15.85f, 4.49f, -11.73f),
		vmath::vec3(15.85f, 4.49f, -11.73f),
		vmath::vec3(15.85f, 4.49f, -11.73f),
		vmath::vec3(15.85f, 4.49f, -11.73f),
	};

	std::vector<float> yawsScene3 = {
		326.68f, 326.68f, 326.68f, 326.98f, // Smoothed these initial duplicates
		316.58f, 313.58f, 292.58f, 283.28f,
		260.88f, 239.08f, 221.38f, 209.28f,
		208.98f, 209.98f, 199.18f, 199.18f,
		199.18f, 199.18f, 199.18f, 199.18f};

	std::vector<float> pitchesScene3 = {
		0.80f, 0.80f, 0.80f, -2.60f, // Smoothed these initial duplicates
		-4.20f, 1.20f, 1.20f, 1.00f,
		-4.50f, -2.50f, -3.90f, -4.00f,
		-4.20f, -1.70f, 0.60f, 0.60f,
		0.60f, 0.60f, 0.60f, 0.60f};

	std::vector<float> rollsScene3(20, 0.0f); // All rolls are 0.0f

	camera_SabhaMandapScene->setBSplinePoints(positionsScene3, yawsScene3, pitchesScene3, rollsScene3);

	// -----------------------------------------------------------------------------------------------------
	rotatingCamera = new BSplineCamera();
	rotatingCamera->setup360RotationCamera(vmath::vec3(0.0f, 10.0f, 30.0f), 0.0f, -5.0f, 0.0f, 2);

	// NEW camera
	// -----------------------------------------------------------------------------------------------------
	camera_RamVachanScene = new BSplineCamera();
	std::vector<vmath::vec3> positionsScene4 = {
		vmath::vec3(-4.56f, 48.35f, 110.92f),  // Clamp start
		vmath::vec3(-4.56f, 48.35f, 110.92f),  // Clamp start
		vmath::vec3(-4.56f, 48.35f, 110.92f),  // t=0.00s  start
		vmath::vec3(-4.55f, 44.62f, 110.74f),  // t=1.00s
		vmath::vec3(-4.54f, 40.90f, 110.55f),  // t=2.00s
		vmath::vec3(-4.53f, 37.17f, 110.36f),  // t=3.00s
		vmath::vec3(-4.52f, 33.45f, 110.17f),  // t=4.00s
		vmath::vec3(-4.51f, 29.72f, 109.99f),  // t=5.00s
		vmath::vec3(-4.50f, 25.99f, 109.80f),  // t=6.00s
		vmath::vec3(-4.49f, 22.27f, 109.61f),  // t=7.00s
		vmath::vec3(-4.48f, 18.54f, 109.42f),  // t=8.00s
		vmath::vec3(-4.47f, 14.90f, 109.24f),  // t=9.00s
		vmath::vec3(-4.46f, 11.27f, 109.05f),  // t=10.00s corner start
		vmath::vec3(-8.18f, 11.27f, 108.88f),  // t=11.00s
		vmath::vec3(-11.91f, 11.27f, 108.70f), // t=12.00s
		vmath::vec3(-15.35f, 11.31f, 107.58f), // t=13.00s
		vmath::vec3(-18.79f, 11.36f, 106.45f), // t=14.00s
		vmath::vec3(-20.94f, 11.47f, 103.94f), // t=14.67s
		vmath::vec3(-23.08f, 11.59f, 101.42f), // t=15.33s
		vmath::vec3(-21.61f, 11.74f, 98.14f),  // t=15.67s
		vmath::vec3(-20.13f, 11.88f, 94.86f),  // t=16.00s
		vmath::vec3(-19.74f, 12.04f, 91.16f),  // t=16.67s
		vmath::vec3(-19.34f, 12.20f, 87.46f),  // t=17.33s
		vmath::vec3(-17.89f, 12.34f, 84.36f),  // t=18.00s
		vmath::vec3(-16.44f, 12.48f, 81.26f),  // t=18.67s
		vmath::vec3(-13.48f, 12.59f, 79.02f),  // t=19.33s
		vmath::vec3(-10.51f, 12.70f, 76.77f),  // t=20.00s
		vmath::vec3(-9.50f, 13.02f, 73.08f),   // t=21.00s
		vmath::vec3(-8.52f, 13.34f, 61.97f),   // t=22.00s end — arrive here
		vmath::vec3(-8.52f, 13.34f, 61.97f),   // hold ~0.4s — decelerate into hold
		vmath::vec3(-8.52f, 13.34f, 61.97f),   // hold ~0.4s
		vmath::vec3(-8.52f, 13.34f, 61.97f),   // hold ~0.4s — full stop (1.2s total hold)
		vmath::vec3(-8.52f, 13.34f, 61.97f),   // Clamp end
		vmath::vec3(-8.52f, 13.34f, 61.97f)	   // Clamp end
	};

	std::vector<float> yawsScene4 = {
		273.18f, 273.18f,									  // clamp
		273.18f, 273.18f, 273.18f, 273.18f, 273.18f, 273.18f, // t=0..5
		273.18f, 273.08f, 272.98f, 272.83f, 272.68f,		  // t=6..10
		272.68f, 272.68f, 272.68f, 272.68f,					  // t=11..14
		273.43f, 274.18f, 274.93f, 275.18f,					  // t=14.67..16
		276.43f, 277.68f, 277.68f, 277.68f, 277.68f,		  // t=16.67..20
		277.48f, 277.28f,									  // t=21..22
		277.28f, 277.28f, 277.28f,							  // hold x3
		277.28f, 277.28f									  // clamp
	};

	std::vector<float> pitchesScene4 = {
		8.70f, 8.70f,							  // clamp
		8.70f, 8.70f, 8.70f, 8.70f, 8.70f, 8.70f, // t=0..5
		8.70f, 8.50f, 8.30f, 8.10f, 7.90f,		  // t=6..10
		7.87f, 7.83f, 7.82f, 7.80f,				  // t=11..14
		7.80f, 7.80f, 7.70f, 7.60f,				  // t=14.67..16
		7.50f, 7.40f, 7.30f, 7.20f, 7.10f,		  // t=16.67..20
		7.30f, 7.50f,							  // t=21..22
		7.50f, 7.50f, 7.50f,					  // hold x3
		7.50f, 7.50f							  // clamp
	};

	std::vector<float> rollsScene4(35, 0.0f); // All rolls are 0.0f

	camera_RamVachanScene->setBSplinePoints(positionsScene4, yawsScene4, pitchesScene4, rollsScene4);

	// -----------------------------------------------------------------------------------------------------

	camera_MountainPeakScene = new BSplineCamera();

	positionsMountainPeakScene = {
		// vmath::vec3(49.58f, 178.60f, 106.75f),
		// vmath::vec3(49.58f, 178.60f, 106.75f),
		// vmath::vec3(30.32f, 175.64f, 99.48f),
		// // vmath::vec3(10.26f, 172.60f, 92.07f),
		// vmath::vec3(-17.97f, 168.31f, 81.64f),
		// vmath::vec3(-31.34f, 166.29f, 76.70f),
		// vmath::vec3(-43.97f, 164.37f, 72.03f),
		// vmath::vec3(-51.78f, 164.37f, 120.61f),
		// vmath::vec3(-61.21f, 163.46f, 153.70f),
		// vmath::vec3(-49.45f, 163.46f, 182.47f),
		// vmath::vec3(-25.01f, 163.46f, 213.83f),
		// vmath::vec3(17.53f, 163.46f, 240.07f),
		// vmath::vec3(39.61f, 164.88f, 258.20f),
		// vmath::vec3(57.94f, 165.65f, 265.66f),
		// vmath::vec3(57.94f, 165.65f, 265.66f),
		// vmath::vec3(57.94f, 165.65f, 265.66f),
		// vmath::vec3(57.94f, 165.65f, 265.66f),
		// vmath::vec3(57.94f, 165.65f, 265.66f),
		// vmath::vec3(57.94f, 165.65f, 265.66f),
		// vmath::vec3(57.94f, 165.65f, 265.66f),
		vmath::vec3(49.58, 178.6, 106.75),
		vmath::vec3(49.58, 178.6, 106.75),
		vmath::vec3(30.32, 175.64, 99.48),
		vmath::vec3(-17.97, 168.31, 81.64),
		vmath::vec3(-31.34, 166.29, 76.7),
		vmath::vec3(-43.97, 164.37, 72.03),
		vmath::vec3(-51.78, 164.37, 120.61),
		vmath::vec3(-61.21, 163.46, 153.7),
		vmath::vec3(-49.45, 163.46, 182.47),
		vmath::vec3(-25.01, 163.46, 213.83),
		vmath::vec3(17.53, 163.46, 240.07),
		vmath::vec3(39.61, 164.88, 258.2),
		vmath::vec3(50.14, 165.65, 265.66),
		vmath::vec3(51.74, 165.65, 265.66),
		vmath::vec3(53.34, 165.65, 265.66),
		vmath::vec3(53.84, 165.65, 265.66),
		vmath::vec3(54.04, 165.65, 265.66),
		vmath::vec3(54.14, 165.65, 265.66),
		vmath::vec3(54.64, 165.65, 265.66)};

	std::vector<float> yawsMountainPeakScene = {
		381.38f, 381.38f, 380.28f, 380.28f, 380.28f, 380.28f, 356.98f, 343.38f, 328.98f, 311.18f, 291.78f, 278.88f, 270.78f, 270.78f, 270.78f, 270.78f, 270.78f, 270.78f, 270.78f};

	std::vector<float> pitchesMountainPeakScene = {
		8.20f,
		8.20f,
		8.10f,
		8.10f,
		8.10f,
		8.10f,
		3.60f,
		0.30f,
		0.90f,
		1.10f,
		-4.40f,
		-6.80f,
		-6.70f,
		-6.70f,
		-6.70f,
		-6.70f,
		-6.70f,
		-6.70f,
		-6.70f,
	};

	std::vector<float> rollsMountainPeakScene(19, 0.0f);

	camera_MountainPeakScene->setBSplinePoints(
		positionsMountainPeakScene,
		yawsMountainPeakScene,
		pitchesMountainPeakScene,
		rollsMountainPeakScene);

	// Initialize Ram Worship Scene Camera
	camera_RamWorship = new BSplineCamera();
	std::vector<vmath::vec3> positionsRamWorship = {
		vmath::vec3(15.30f, -27.21f, 297.31f),
		vmath::vec3(15.30f, -27.21f, 297.31f),
		vmath::vec3(15.30f, -27.21f, 297.31f),
		vmath::vec3(29.27f, -24.18f, 277.48f),
		vmath::vec3(29.27f, -24.18f, 277.48f),
		vmath::vec3(29.27f, -24.18f, 277.48f),
		vmath::vec3(55.39f, -15.87f, 272.46f),
		vmath::vec3(69.69f, -9.41f, 269.57f),
		vmath::vec3(57.13f, -16.50f, 220.80f),
		vmath::vec3(52.22f, -16.50f, 197.60f),
		vmath::vec3(57.36f, -16.50f, 149.97f),
		vmath::vec3(26.66f, -14.01f, 111.90f),
		vmath::vec3(22.20f, -13.39f, 86.51f),
		vmath::vec3(23.15f, -8.37f, 59.76f),
		vmath::vec3(10.88f, -7.20f, 20.78f),
		vmath::vec3(-1.60f, -6.30f, 4.41f),
		vmath::vec3(-10.10f, -6.13f, -6.70f),
		vmath::vec3(-11.46f, -6.13f, -18.62f),
		vmath::vec3(-13.37f, -6.13f, -35.31f),
		vmath::vec3(-16.37f, -6.13f, -61.54f),
		vmath::vec3(-5.58f, 5.06f, -120.12f),
		vmath::vec3(3.87f, 5.89f, -135.55f),
		vmath::vec3(19.56f, 6.51f, -146.46f),
		vmath::vec3(30.25f, 7.06f, -151.65f),
		vmath::vec3(36.64f, 16.88f, -153.65f),
		vmath::vec3(39.22f, 24.01f, -144.39f),
		vmath::vec3(43.15f, 34.05f, -145.64f),
		vmath::vec3(53.34f, 35.84f, -166.41f),
		vmath::vec3(63.53f, 37.64f, -187.19f),
		vmath::vec3(84.00f, 54.24f, -198.47f),
		vmath::vec3(94.44f, 57.95f, -201.68f),
		vmath::vec3(95.06f, 71.78f, -201.85f),
		vmath::vec3(98.33f, 81.92f, -180.40f),
		vmath::vec3(118.63f, 85.26f, -165.41f),
		vmath::vec3(143.16f, 89.00f, -136.28f),
		vmath::vec3(159.81f, 91.86f, -124.50f),
		vmath::vec3(159.41f, 93.92f, -124.43f),
		vmath::vec3(173.62f, 96.37f, -114.67f),
		vmath::vec3(175.79f, 96.37f, -102.87f),
		vmath::vec3(173.10f, 95.04f, -85.40f),
		vmath::vec3(154.03f, 90.55f, -57.22f),
		vmath::vec3(136.20f, 90.55f, -24.17f),
		vmath::vec3(127.75f, 65.40f, -18.97f),
		vmath::vec3(70.72f, 53.31f, -17.49f),
		vmath::vec3(54.87f, 52.84f, -48.67f),
		vmath::vec3(47.16f, 52.84f, -66.16f),
		vmath::vec3(51.39f, 48.06f, -86.97f),
		vmath::vec3(54.45f, 48.06f, -103.45f),
		vmath::vec3(54.45f, 48.06f, -103.45f),
		vmath::vec3(54.45f, 48.06f, -103.45f),
		vmath::vec3(54.45f, 48.06f, -103.45f)};

	std::vector<float> yawsRamWorship = {
		192.08f, 192.08f, 192.08f, 153.78f, 153.78f, 169.58f, 168.58f, 168.58f,
		163.68f, 182.78f, 191.48f, 191.48f, 191.48f, 191.48f, 180.38f, 173.48f,
		173.48f, 173.48f, 173.48f, 178.08f, 144.88f, 145.08f, 145.28f, 159.08f,
		162.58f, 162.58f, 162.68f, 162.68f, 163.08f, 162.98f, 164.78f, 165.68f,
		166.88f, 166.88f, 170.38f, 170.38f, 170.38f, 170.38f, 168.58f, 171.28f,
		194.88f, 208.08f, 221.38f, 302.78f, 325.48f, 341.58f, 366.78f, 388.08f,
		388.08f, 388.08f, 388.08f};

	std::vector<float> pitchesRamWorship = {
		5.00f, 5.00f, 5.00f, 8.90f, 8.90f, 7.70f, 8.00f, 8.00f,
		10.20f, 8.40f, 11.20f, 11.20f, 11.20f, 11.20f, 10.90f, 4.10f,
		4.10f, 4.10f, 4.10f, 0.90f, -9.60f, -5.60f, -5.60f, -7.10f,
		-7.50f, -7.50f, -18.70f, -18.70f, -19.30f, -21.20f, -19.70f, -32.50f,
		-31.50f, -31.50f, -30.70f, -30.70f, -30.70f, -30.70f, -31.30f, -34.50f,
		-36.70f, -41.40f, -23.10f, -9.80f, -6.70f, -1.90f, 8.30f, 12.30f,
		12.30f, 12.30f, 12.30f};

	std::vector<float> rollsRamWorship(51, 0.0f); // Replaced garbage values with 0.0f

	camera_RamWorship->setBSplinePoints(positionsRamWorship, yawsRamWorship, pitchesRamWorship, rollsRamWorship);

	// ToggleFullScreen();

	// Load Grass
	pGrass = new Grass();
	pGrass->generateGrass();

	// Load video AMC Banner video
	gAMCBannerVideo.speedMultiplier = 1;
	VideoPlayerInit(gAMCBannerVideo, L"./resources/Video/AMCBanner.mp4");

	// Credits
	initializeTextures();

	initializeWaterLensFlare();

	ramVachanFlareParams.sunWorldPosition = godRaysParams.sunWorldPos;
	ramVachanFlareParams.tintColor = vmath::vec3(1.0f, 1.0f, 1.0f);
	ramVachanFlareParams.intensity = 0.66f;
	ramVachanFlareParams.alphaScale = 1.0f;
	ramVachanFlareParams.slant = 0.22f;
	ramVachanFlareParams.clipToWater = true;
	ramVachanFlareParams.useOcclusion = true;
	ramVachanFlareParams.externalVisibility = 0.0f;
	ramVachanFlareParams.sizeScale = 1.0f;
	ramVachanFlareParams.chainDirection = vmath::vec2(0.0f, 0.0f);

	mountainPeakFlareParams.sunWorldPosition = vmath::vec3(55.0f, 222.0f, -523.0f);
	mountainPeakFlareParams.tintColor = vmath::vec3(1.0f, 0.92f, 0.78f);
	mountainPeakFlareParams.intensity = 0.95f;
	mountainPeakFlareParams.alphaScale = 1.0f;
	mountainPeakFlareParams.slant = 0.0f;
	mountainPeakFlareParams.clipToWater = false;
	mountainPeakFlareParams.useOcclusion = false;
	mountainPeakFlareParams.externalVisibility = 0.0f;
	mountainPeakFlareParams.sizeScale = 1.6f;
	mountainPeakFlareParams.chainDirection = vmath::vec2(-0.28f, -0.75f);
	initializeFadeSystem();

	// Terrain Initialize
	pHeightmapTerrain = new Terrain();
	if (pHeightmapTerrain->initialize("./resources/Texture/LastSceneTerrain/HeightMap.png",
									  "./resources/Texture/LastSceneTerrain/AlbedoMap.png",
									  "./resources/Texture/LastSceneTerrain/NormalMap.png",
									  "./resources/Texture/LastSceneTerrain/RoughnessMap.png",
									  "./resources/Texture/LastSceneTerrain/AmbientOcclusionMap.png") != 0)
	{
		LOG("Terrain Initialize Failed!!\n");
		return (-1);
	}

	// LOG_ENTRY("log.txt", "Initializing FireOnSquare");
	pFire = new FireOnSquare();
	if (!pFire)
	{
		LOG("Fire Initialization Failed");
		return (-1);
	}
	pFire->Initialize(WIN_WIDTH, WIN_HEIGHT);

	volumetriccloudsForPeakScene = new VolumetricClouds("./effects/MayursEffects/VolumetricClouds/clouds_peak_scene.txt");
	volumetriccloudsForFlyingScene = new VolumetricClouds("./effects/MayursEffects/VolumetricClouds/clouds_flying_scene.txt");
	volumetriccloudsForYuddhaScene = new VolumetricClouds("./effects/MayursEffects/VolumetricClouds/clouds_yuddha_scene.txt");
	volumetriccloudsForOcean = new VolumetricClouds("./effects/MayursEffects/VolumetricClouds/clouds_ocean_scene.txt");

	LOG_ENTRY("log.txt", "MST: Create LitSabhamandapProgramWithShadow");
	litSabhamandapProgramWithShadow = new LitSabhamandapProgramWithShadow("./effects/MayursEffects/LitSabhamandapProgramWithShadow/lsp_vs.glsl", "./effects/MayursEffects/LitSabhamandapProgramWithShadow/lsp_fs.glsl", "log.txt");
	LOG_ENTRY("log.txt", "MST: Created Successfully LitSabhamandapProgramWithShadow");

	LOG_ENTRY("log.txt", "MST: Create Sabhamandap Interior Shadow FBO");
	firePotShadowFBO = new FrameBufferObjectWithDepth(2048, 2048);
	firePotShadowFBO->Initialize();
	LOG_ENTRY("log.txt", "MST: Created Sabha Mandap Interior Successfully Shadow FBO");

	LOG_ENTRY("log.txt", "MST: Create Sabhamandap Interior Shadow FBO");
	ministerChairShadowFBO = new FrameBufferObjectWithDepth(2048, 2048);
	ministerChairShadowFBO->Initialize();
	LOG_ENTRY("log.txt", "MST: Created Sabha Mandap Interior Successfully Shadow FBO");

	LOG_ENTRY("log.txt", "MST: Create Hanuman Shadow FBO");
	hanumanShadowFBO = new FrameBufferObjectWithDepth(2048, 2048);
	hanumanShadowFBO->Initialize();
	LOG_ENTRY("log.txt", "MST: Created Hanuman Successfully Shadow FBO");

	LOG_ENTRY("log.txt", "MST: Create Vibhishan Shadow FBO");
	vibhishanShadowFBO = new FrameBufferObjectWithDepth(2048, 2048);
	vibhishanShadowFBO->Initialize();
	LOG_ENTRY("log.txt", "MST: Created Vibhishan Successfully Shadow FBO");

	LOG_ENTRY("log.txt", "MST: Create Pillar Shadow FBO");
	pillarShadowFBO = new FrameBufferObjectWithDepth(2048, 2048);
	pillarShadowFBO->Initialize();
	LOG_ENTRY("log.txt", "MST: Created Pillar Successfully Shadow FBO");

	LOG_ENTRY("log.txt", "MST: Create LitSabhamandapProgramWithShadow(ramVachanProgramWithShadow)");
	ramVachanProgramWithShadow = new LitSabhamandapProgramWithShadow("./effects/MayursEffects/LitSabhamandapProgramWithShadow/lsp_vs.glsl", "./effects/MayursEffects/LitSabhamandapProgramWithShadow/lsp_fs.glsl", "log.txt");
	LOG_ENTRY("log.txt", "MST: Created Successfully LitSabhamandapProgramWithShadow(ramVachanProgramWithShadow)");

	LOG_ENTRY("log.txt", "MST: Create Ram-Hanuman Shadow FBO");
	ramVachanShadowFBO = new FrameBufferObjectWithDepth(2048, 2048);
	ramVachanShadowFBO->Initialize();
	LOG_ENTRY("log.txt", "MST: Created Ram-Hanuman Successfully Shadow FBO");

	LOG_ENTRY("log.txt", "MST: Create Asur Shadow FBO");
	asurShadowFBO = new FrameBufferObjectWithDepth(2048, 2048);
	asurShadowFBO->Initialize();
	LOG_ENTRY("log.txt", "MST: Created Asur Successfully Shadow FBO");

	LOG_ENTRY("log.txt", "MST: Create Ram-Vachan Trees Shadow FBO");
	ramVachanTreeShadowFBO = new FrameBufferObjectWithDepth(2048, 2048);
	ramVachanTreeShadowFBO->Initialize();
	LOG_ENTRY("log.txt", "MST: Created Ram-Vachan Trees Successfully Shadow FBO");

	// LOG_ENTRY("log.txt", "MST: Create Ram-Vachan Trees Shadow FBO");
	// ramworshipAnimalFBO = new FrameBufferObjectWithDepth(2048, 2048);
	// ramworshipAnimalFBO->Initialize();
	// LOG_ENTRY("log.txt", "MST: Created Ram-Vachan Trees Successfully Shadow FBO");

	shadowProgram = new ShadowProgram("./effects/MayursEffects/Shadow/shadow_vs.glsl", "./effects/MayursEffects/Shadow/shadow_fs.glsl", "log.txt");

	mountainPeakProgram = new SingleLightProgram("./effects/MayursEffects/SingleLightProgram/SingleLight_vs.glsl",
												 "./effects/MayursEffects/SingleLightProgram/SingleLight_fs.glsl",
												 "log.txt",
												 "./resources/Models/06_SnowPeak/NormalMap.jpg");

	sideMountainPeakProgram = new SingleLightProgram("./effects/MayursEffects/SingleLightProgram/SingleLight_vs.glsl",
													 "./effects/MayursEffects/SingleLightProgram/SingleLight_fs.glsl",
													 "log.txt",
													 "./resources/Models/06_SnowPeak/NormalMap0.jpg");

	pointProgram = new PointProgram("./effects/MayursEffects/PointProgram/PointProgram_vs.glsl",
									"./effects/MayursEffects/PointProgram/PointProgram_fs.glsl",
									"log.txt");

	hanumanOnMountain = new PBRProgram("./effects/MayursEffects/PBRProgram/pbr_vs.glsl",
									   "./effects/MayursEffects/PBRProgram/pbr_fs.glsl",
									   "log.txt");

	// initialize orthographic projection matrix
	perspectiveProjectionMatrix = vmath::mat4::identity();

	glPointSize(10.0f);

	// timer initialization
	sdkCreateTimer(&sceneTimer);
	sdkStartTimer(&sceneTimer);

// Audio
#if PREVIEW_SCENE > 0 // Dev Mode
	gTimeOffset = SCENE_START_TIMES[PREVIEW_SCENE];
	selected_scene = PREVIEW_SCENE - 1;
#else // End-to-End mode
	gTimeOffset = 0.0f;
	InitAudio(); // only plays audio in end-to-end mode
	PlayTestSound();
#endif

	resize(WIN_WIDTH, WIN_HEIGHT);

	// ---------------- Snowfall Init FIX ----------------
	snowfallParams.cameraStartPos = gpCamera->m_position;

	snowfallParams.count = 12000;
	snowfallParams.density = 1.0f / 20.0f;
	snowfallParams.depth = 60.0f;

	snowfallParams.gravity = 25.0f;

	snowfallParams.sizeMin = 8.0f;
	snowfallParams.sizeMax = 20.0f;

	snowfallParams.speed = 1.0f / 1500.0f;

	initializeSnowfall(
		snowfallParams,
		g_iWinWidth,
		g_iWinHeight);

	int iretVal = initializeDissolveShader();
	if (iretVal != 0)
	{
		fprintf(gpFILE, "\n\n initializeDissolveShader(); failed \n");
	}
	else
	{
		fprintf(gpFILE, "\n\n initializeDissolveShader(); sucessfull \n");
	}

	initializeTransitions(WIN_WIDTH, WIN_HEIGHT);

	// Boid Simulation Initialize
	pBoidSimulation = new BoidSimulation();
	pBoidSimulation->Initialize();

	// Set initial Boid parameters for V-shape (Ocean Scene)
	boidParamsVshape.bEnable = FALSE;
	boidParamsVshape.type = BOID_V_SHAPE;
	boidParamsVshape.position = vmath::vec3(0.0f, 10.0f, -10.0f);
	boidParamsVshape.position = vmath::vec3(20.0f, 12.0f, -30.0f);
	boidParamsVshape.speed = 0.01f;
	boidParamsVshape.wingSpeed = 0.15f;
	boidParamsVshape.scale = 10.0f;
	boidParamsVshape.scale = 2.0f;

	// Set initial Boid parameters for Flock (Ram Worship Scene)
	boidParamsFlock.bEnable = FALSE;
	boidParamsFlock.type = BOID_FLOCK;
	boidParamsFlock.position = vmath::vec3(0.0f, 10.0f, -10.0f);
	boidParamsFlock.speed = 1.0f;
	boidParamsFlock.wingSpeed = 15.0f;
	boidParamsFlock.scale = 1.5f;
	boidParamsFlock.scale = 2.0f;

	return (0);
}

void printGLInfo(void)
{
	// variable declaration
	GLint numExtension;
	GLint i; // for loop counter

	// code
	fprintf(gpFILE, "OpenGL Vender :	%s\n", glGetString(GL_VENDOR));
	fprintf(gpFILE, "OpenGL Renderer :	%s\n", glGetString(GL_RENDERER));
	fprintf(gpFILE, "OpenGL Version :	%s\n", glGetString(GL_VERSION));
	fprintf(gpFILE, "OpenGL GLSL(Graphic Library Shading Language) Version :	%s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	fprintf(gpFILE, "\n==============================================================================\n");

	// Listing of Supported Extension
	glGetIntegerv(GL_NUM_EXTENSIONS, &numExtension);

	// for (i = 0; i < numExtension; i++)
	// {
	// 	fprintf(gpFILE, "\t%s\n", glGetStringi(GL_EXTENSIONS, i));
	// }

	fprintf(gpFILE, "\n==============================================================================\n");
}

void resize(int width, int height)
{
	// code
	if (height <= 0)
	{
		height = 1;
	}

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	gwinWidth = width;
	gwinHeight = height;

	if (pFire)
	{
		pFire->Resize(width, height);
	}

	if (volumetriccloudsForPeakScene)
	{
		volumetriccloudsForPeakScene->Resize(width, height);
	}

	if (volumetriccloudsForFlyingScene)
	{
		volumetriccloudsForFlyingScene->Resize(width, height);
	}

	if (volumetriccloudsForYuddhaScene)
	{
		volumetriccloudsForYuddhaScene->Resize(width, height);
	}

	if (volumetriccloudsForOcean)
	{
		volumetriccloudsForOcean->Resize(width, height);
	}

	// set perspective projection matrix
	perspectiveProjectionMatrix = vmath::perspective(45.0f, (GLfloat)width / (GLfloat)height, 1.0f, 50000.0f);
	resizeTransitions(width, height);
}

void RenderTexturedBasedScene(GLuint textureID, float alpha) // ha patya dakhwayla ani Video cha VBO quad mhnun IMP
{
	glUseProgram(shaderProgramObject);

	vmath::mat4 modelMatrix =
		vmath::translate(0.0f, 0.0f, -3.0f) *
		vmath::scale(1.8f, 1.0f, 1.0f);

	glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, modelMatrix);
	glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, vmath::mat4::identity());
	glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, perspectiveProjectionMatrix);

	glUniform1f(alphaUniformTextures, alpha);

	glBindVertexArray(vaoTextures);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboTextures);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glUniform1i(textureSamplerUniform, 0);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, NULL);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glUseProgram(0);
}

void renderSabhaMandapSceneHanuman(Camera *pCamera, vmath::vec4 clippingPlane, Model *model)
{
	SceneLightParams *pLights = nullptr;
	pLights = &sabhamandapScene_ThroneLights;

	// BOOL bLit = (pLights && pLights->bEnableLighting && gLitShaderProgram != 0);
	glUseProgram(gLitShaderProgram);

	vmath::mat4 modelMatrix = vmath::mat4::identity();
	vmath::mat4 viewMatrix;

	modelMatrix = vmath::translate(0.0f, 0.0f, -10.0f);

	if (pLights)
		pLights->cameraPos = vmath::vec3(0.0f, -10.0f, 8.0f);

	// if (bLit)
	// {
	glUniformMatrix4fv(gLitModelMatrixUniform, 1, GL_FALSE, modelMatrix);
	glUniformMatrix4fv(gLitViewMatrixUniform, 1, GL_FALSE, gpCamera->getLookAtMatrix());
	glUniformMatrix4fv(gLitProjectionMatrixUniform, 1, GL_FALSE, perspectiveProjectionMatrix);
	glUniform4fv(gLitClippingPlaneUniform, 1, clippingPlane);
	glUniform1i(gLitTextureSamplerUniform, 0);

	// Upload all light uniforms
	applySceneLighting(*pLights);
	// }
	// else
	// {
	// 	glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, modelMatrix);
	// 	glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, gpCamera->getLookAtMatrix());
	// 	glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, perspectiveProjectionMatrix);
	// 	glUniform4fv(clippingPlaneUniform, 1, clippingPlane);
	// 	glUniform1i(textureSamplerUniform, 0);
	// }

	renderModelPBR(model);

	glUseProgram(0);
}

void renderUsingLitProgram(Camera *pCamera, vmath::vec4 clippingPlane, Model *model, vmath::mat4 modelMatrix, SceneLightParams *pLights)
{
	// SceneLightParams *pLights = nullptr;
	// pLights = &sabhamandapScene_ThroneLights;

	// BOOL bLit = (pLights && pLights->bEnableLighting && gLitShaderProgram != 0);
	glUseProgram(gLitShaderProgram);

	// vmath::mat4 modelMatrix = vmath::mat4::identity();
	vmath::mat4 viewMatrix;

	if (pLights)
		pLights->cameraPos = vmath::vec3(0.0f, -10.0f, 8.0f);

	// if (bLit)
	// {
	glUniformMatrix4fv(gLitModelMatrixUniform, 1, GL_FALSE, modelMatrix);
	glUniformMatrix4fv(gLitViewMatrixUniform, 1, GL_FALSE, gpCamera->getLookAtMatrix());
	glUniformMatrix4fv(gLitProjectionMatrixUniform, 1, GL_FALSE, perspectiveProjectionMatrix);
	glUniform4fv(gLitClippingPlaneUniform, 1, clippingPlane);
	glUniform1i(gLitTextureSamplerUniform, 0);

	// Upload all light uniforms
	applySceneLighting(*pLights);

	renderModel(model);

	glUseProgram(0);
}

void renderSabhaMandapScene(Camera *pCamera, vmath::vec4 clippingPlane, Model *model)
{
	SceneLightParams *pLights = nullptr;
	pLights = &sabhamandapScene_ThroneLights;

	// BOOL bLit = (pLights && pLights->bEnableLighting && gLitShaderProgram != 0);
	glUseProgram(gLitShaderProgram);

	vmath::mat4 modelMatrix = vmath::mat4::identity();
	vmath::mat4 viewMatrix;

	modelMatrix = vmath::translate(0.0f, 0.0f, -10.0f);

	if (pLights)
		pLights->cameraPos = vmath::vec3(0.0f, -10.0f, 8.0f);

	// if (bLit)
	// {
	glUniformMatrix4fv(gLitModelMatrixUniform, 1, GL_FALSE, modelMatrix);
	glUniformMatrix4fv(gLitViewMatrixUniform, 1, GL_FALSE, gpCamera->getLookAtMatrix());
	glUniformMatrix4fv(gLitProjectionMatrixUniform, 1, GL_FALSE, perspectiveProjectionMatrix);
	glUniform4fv(gLitClippingPlaneUniform, 1, clippingPlane);
	glUniform1i(gLitTextureSamplerUniform, 0);

	// Upload all light uniforms
	applySceneLighting(*pLights);
	// }
	// else
	// {
	// 	glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, modelMatrix);
	// 	glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, gpCamera->getLookAtMatrix());
	// 	glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, perspectiveProjectionMatrix);
	// 	glUniform4fv(clippingPlaneUniform, 1, clippingPlane);
	// 	glUniform1i(textureSamplerUniform, 0);
	// }

	renderModel(model);

	glUseProgram(0);
}

void renderSabhaMandapSceneWithShadow(Camera *pCamera,
									  vmath::vec4 clippingPlane,
									  Model *model,
									  int showHanumanShadow,
									  int showVibhishanShadow,
									  int showFirePotShadow,
									  int showMinisterChairShadow,
									  int pillarChairShadow)
{
	SceneLightParams *pLights = nullptr;
	pLights = &sabhamandapScene_ThroneLights;

	// BOOL bLit = (pLights && pLights->bEnableLighting && gLitShaderProgram != 0);
	// glUseProgram(gLitShaderProgram);

	vmath::mat4 modelMatrix = vmath::mat4::identity();
	vmath::mat4 viewMatrix;

	modelMatrix = vmath::translate(0.0f, 0.0f, -10.0f);

	if (pLights)
		pLights->cameraPos = vmath::vec3(0.0f, -10.0f, 8.0f);

	// if (bLit)
	// {
	// glUniformMatrix4fv(gLitModelMatrixUniform, 1, GL_FALSE, modelMatrix);
	// glUniformMatrix4fv(gLitViewMatrixUniform, 1, GL_FALSE, gpCamera->getLookAtMatrix());
	// glUniformMatrix4fv(gLitProjectionMatrixUniform, 1, GL_FALSE, perspectiveProjectionMatrix);
	// glUniform4fv(gLitClippingPlaneUniform, 1, clippingPlane);
	// glUniform1i(gLitTextureSamplerUniform, 0);

	// Upload all light uniforms
	// applySceneLighting(*pLights);
	// }
	// else
	// {
	// 	glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, modelMatrix);
	// 	glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, gpCamera->getLookAtMatrix());
	// 	glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, perspectiveProjectionMatrix);
	// 	glUniform4fv(clippingPlaneUniform, 1, clippingPlane);
	// 	glUniform1i(textureSamplerUniform, 0);
	// }

	if (litSabhamandapProgramWithShadow)
	{
		litSabhamandapProgramWithShadow->StartProgram();

		vmath::vec3 lpos = sabhamandapScene_ThroneLights.keyLight.position;

		// vmath::mat4 lightViewMat = vmath::lookat(vmath::vec3(-3.0f, 0.0f, -100.0f),
		// 										 vmath::vec3(0.0f, 0.0f, -10.0f),
		// 										 vmath::vec3(0.0f, 1.0f, 0.0f));

		vmath::mat4 hanumanLightViewMat = vmath::lookat(vmath::vec3(hanumanShadow.lightX, hanumanShadow.lightY, hanumanShadow.lightZ),
														vmath::vec3(0.0f, 0.0f, -10.0f),
														vmath::vec3(0.0f, 1.0f, 0.0f));

		vmath::mat4 hanumanplvmMatrix = perspectiveProjectionMatrix * hanumanLightViewMat * modelMatrix;

		vmath::mat4 vibhishanLightViewMat = vmath::lookat(vmath::vec3(vibhishanShadow.lightX, vibhishanShadow.lightY, vibhishanShadow.lightZ),
														  vmath::vec3(0.0f, 0.0f, -10.0f),
														  vmath::vec3(0.0f, 1.0f, 0.0f));

		vmath::mat4 vibhishanplvmMatrix = perspectiveProjectionMatrix * vibhishanLightViewMat * modelMatrix;

		vmath::mat4 firePotLightViewMat = vmath::lookat(vmath::vec3(fireKundShadow.lightX, fireKundShadow.lightY, fireKundShadow.lightZ),
														vmath::vec3(0.0f, 0.0f, -10.0f),
														vmath::vec3(0.0f, 1.0f, 0.0f));

		vmath::mat4 firePotplvmMatrix = perspectiveProjectionMatrix * firePotLightViewMat * modelMatrix;

		vmath::mat4 ministerChairLightViewMat = vmath::lookat(vmath::vec3(ministerChairShadow.lightX, ministerChairShadow.lightY, ministerChairShadow.lightZ),
															  vmath::vec3(0.0f, 0.0f, -10.0f),
															  vmath::vec3(0.0f, 1.0f, 0.0f));

		vmath::mat4 ministerChairplvmMatrix = perspectiveProjectionMatrix * ministerChairLightViewMat * modelMatrix;

		vmath::mat4 pillarLightViewMat = vmath::lookat(vmath::vec3(pillarShadow.lightX, pillarShadow.lightY, pillarShadow.lightZ),
													   vmath::vec3(0.0f, 0.0f, -10.0f),
													   vmath::vec3(0.0f, 1.0f, 0.0f));

		vmath::mat4 pillarplvmMatrix = perspectiveProjectionMatrix * pillarLightViewMat * modelMatrix;

		litSabhamandapProgramWithShadow->SetUniforms(
			perspectiveProjectionMatrix,
			gpCamera->getLookAtMatrix(),
			modelMatrix,
			hanumanplvmMatrix,
			vibhishanplvmMatrix,
			firePotplvmMatrix,
			ministerChairplvmMatrix,
			pillarplvmMatrix,
			clippingPlane,
			*pLights,
			1, hanumanShadow.shadowPower, showHanumanShadow,
			2, vibhishanShadow.shadowPower, showVibhishanShadow,
			3, fireKundShadow.shadowPower, showFirePotShadow,
			4, ministerChairShadow.shadowPower, showMinisterChairShadow,
			5, pillarShadow.shadowPower, pillarChairShadow);

		hanumanShadowFBO->BindDepthTexture(1);
		vibhishanShadowFBO->BindDepthTexture(2);
		firePotShadowFBO->BindDepthTexture(3);
		ministerChairShadowFBO->BindDepthTexture(4);
		pillarShadowFBO->BindDepthTexture(5);

		renderModel(model);

		litSabhamandapProgramWithShadow->StopProgram();
	}
}

void renderTerrainScene(vmath::vec4 clippingPlane, Model *model)
{
	// code
	glUseProgram(shaderProgramObject);

	glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, vmath::translate(10.0f, 0.0f, -1.0f));

	glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, gpCamera->getLookAtMatrix());
	glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, perspectiveProjectionMatrix);
	glUniform4fv(clippingPlaneUniform, 1, clippingPlane);

	glUniform1i(textureSamplerUniform, 0);
	renderModel(model); // render ramvacahn model

	glUseProgram(0);
}

void renderTerrainSceneWithShadow(vmath::vec4 clippingPlane, Model *model)
{
	// Code

	if (litSabhamandapProgramWithShadow)
	{
		litSabhamandapProgramWithShadow->StartProgram();

		vmath::mat4 modelMatrix = vmath::mat4::identity();
		vmath::mat4 identityMat = vmath::mat4::identity();
		vmath::mat4 ramVachanLightMatrix = vmath::lookat(vmath::vec3(ramVachanShadow.lightX, ramVachanShadow.lightY, ramVachanShadow.lightZ),
														 vmath::vec3(0.0f, 0.0f, -10.0f),
														 vmath::vec3(0.0f, 1.0f, 0.0f));

		vmath::mat4 ramVachanplvmMatrix = perspectiveProjectionMatrix * ramVachanLightMatrix * modelMatrix;

		vmath::mat4 ramVachanTreeLightMatrix = vmath::lookat(vmath::vec3(ramVachanTreeShadow.lightX, ramVachanTreeShadow.lightY, ramVachanTreeShadow.lightZ),
															 vmath::vec3(0.0f, 0.0f, -10.0f),
															 vmath::vec3(0.0f, 1.0f, 0.0f));

		vmath::mat4 ramVachanTreeplvmMatrix = perspectiveProjectionMatrix * ramVachanTreeLightMatrix * modelMatrix;

		litSabhamandapProgramWithShadow->SetUniforms(
			perspectiveProjectionMatrix,
			gpCamera->getLookAtMatrix(),
			modelMatrix,
			ramVachanplvmMatrix,
			ramVachanTreeplvmMatrix,
			identityMat,
			identityMat,
			identityMat,
			clippingPlane,
			ramvachanLights,
			1, ramVachanShadow.shadowPower, 1,
			2, ramVachanTreeShadow.shadowPower, 1,
			3, 0, 0,
			4, 0, 0,
			5, 0, 0);

		ramVachanShadowFBO->BindDepthTexture(1);
		ramVachanTreeShadowFBO->BindDepthTexture(2);

		renderModel(model);

		litSabhamandapProgramWithShadow->StopProgram();
	}
}

void renderYuddhaTerrainSceneWithShadow(vmath::vec4 clippingPlane, Model *model)
{
	// Code

	if (litSabhamandapProgramWithShadow)
	{
		litSabhamandapProgramWithShadow->StartProgram();

		vmath::mat4 modelMatrix = vmath::mat4::identity();
		vmath::mat4 identityMat = vmath::mat4::identity();
		vmath::mat4 asurLightMatrix = vmath::lookat(vmath::vec3(asurShadow.lightX, asurShadow.lightY, asurShadow.lightZ),
													vmath::vec3(0.0f, 0.0f, -10.0f),
													vmath::vec3(0.0f, 1.0f, 0.0f));

		vmath::mat4 asurplvmMatrix = perspectiveProjectionMatrix * asurLightMatrix * modelMatrix;

		vmath::mat4 hanumanShadowTreeLightMatrix = vmath::lookat(vmath::vec3(hanumanYuddha01Shadow.lightX, hanumanYuddha01Shadow.lightY, hanumanYuddha01Shadow.lightZ),
																 vmath::vec3(0.0f, 0.0f, -10.0f),
																 vmath::vec3(0.0f, 1.0f, 0.0f));

		vmath::mat4 hanumanYuddhaplvmMatrix = perspectiveProjectionMatrix * hanumanShadowTreeLightMatrix * modelMatrix;

		litSabhamandapProgramWithShadow->SetUniforms(
			perspectiveProjectionMatrix,
			gpCamera->getLookAtMatrix(),
			modelMatrix,
			asurplvmMatrix,
			hanumanYuddhaplvmMatrix,
			// identityMat,
			identityMat,
			identityMat,
			identityMat,
			clippingPlane,
			ramvachanLights,
			1, asurShadow.shadowPower, 1,
			2, hanumanYuddha01Shadow.shadowPower, 1,
			3, 0, 0,
			4, 0, 0,
			5, 0, 0);

		asurShadowFBO->BindDepthTexture(1);
		hanumanShadowFBO->BindDepthTexture(2);

		renderModel(model);

		litSabhamandapProgramWithShadow->StopProgram();
	}
}

void renderPBRModel(Model *model, vmath::vec3 pos, vmath::vec3 scale)
{
	// Code

	vmath::mat4 modelMatrix = vmath::mat4::identity();
	modelMatrix = vmath::translate(pos[0], pos[1], pos[2]) * vmath::scale(scale[0], scale[1], scale[2]);

	vmath::mat4 viewMatrix = gpCamera->getLookAtMatrix();

	// vmath::mat4 viewMatrix = vmath::lookat(vec3(0.0f, 1000.0f, 1000.0f),
	// 									   vec3(0.0f, 0.0f, 0.0f),
	// 									   vec3(0.0f, 1.0f, 0.0f));

	hanumanOnMountain->SetLightPosition(hanumanOnMountainLightpos);

	hanumanOnMountain->StartProgram();
	{
		hanumanOnMountain->SetUniforms(perspectiveProjectionMatrix,
									   modelMatrix,
									   viewMatrix,
									   radiance,
									   emmissiveStrength);
		// renderModelPBR(model);
		for (int i = 0; i < model->numMeshes; i++)
		{

			// if (model->meshArray[i].textureCount > 1)
			renderMeshPBR(&(model->meshArray[i]));
			// else
			// 	renderMesh(&(model->meshArray[i]));
		}
	}
	hanumanOnMountain->StopProgram();
}

void renderMontainPeakHanumanScene(vmath::vec4 clippingPlane, Model *model)
{
	void renderModelWithDissolve(Model * model, vmath::mat4 modelMatrix, vmath::mat4 viewMatrix, vmath::mat4 projectionMatrix, float progress, float time, BOOL bReverse);

	vmath::mat4 modelMatrix = vmath::mat4::identity();
	modelMatrix = vmath::translate(hanumanPosX, hanumanPosY, hanumanPosZ); // *
																		   //   vmath::rotate(180.0f, 0.0f, 1.0f, 0.0f);

	vmath::mat4 viewMatrix = gpCamera->getLookAtMatrix();

	glUseProgram(shaderProgramObject);
	glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, modelMatrix);
	glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, perspectiveProjectionMatrix);
	glUniform4fv(clippingPlaneUniform, 1, clippingPlane);
	glUniform1i(textureSamplerUniform, 0);
	renderModel(model);
	glUseProgram(0);
}

void renderFlyingScene(vmath::vec4 clippingPlane, Model *model)
{
	static float flyingX = -230.00f;
	static float flyingZ = 0.00f;

	// Incrementally move the model
	if (ELAPSED_TIME < START_TIME_FLYING + (START_TIME_OCEAN - START_TIME_FLYING) / 2.0f)
		flyingX += 0.05f;
	else
		flyingX += 0.9f;

	// flyingZ -= 0.05f;

	vmath::mat4 modelMatrix = vmath::mat4::identity();
	modelMatrix = vmath::translate(flyingX, flyingY, flyingZ); // * vmath::rotate(70.0f, 0.0f, 1.0f, 0.0f);

	vmath::mat4 viewMatrix = gpCamera->getLookAtMatrix();

	glUseProgram(shaderProgramObject);
	glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, modelMatrix);
	glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, perspectiveProjectionMatrix);
	glUniform4fv(clippingPlaneUniform, 1, clippingPlane);
	glUniform1i(textureSamplerUniform, 0);
	renderModel(model);
	glUseProgram(0);
}

void renderFlyingSceneForOcean(vmath::vec4 clippingPlane, Model *model)
{
	hanumanOceanXPos += hanumanOceanXFactor;

	vmath::mat4 modelMatrix = vmath::mat4::identity();
	modelMatrix = vmath::translate(hanumanOceanXPos, hanumanOceanYPos, hanumanOceanZPos); // * vmath::rotate(70.0f, 0.0f, 1.0f, 0.0f);

	vmath::mat4 viewMatrix = gpCamera->getLookAtMatrix();

	glUseProgram(shaderProgramObject);
	glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, modelMatrix);
	glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, perspectiveProjectionMatrix);
	glUniform4fv(clippingPlaneUniform, 1, clippingPlane);
	glUniform1i(textureSamplerUniform, 0);
	renderModel(model);
	glUseProgram(0);
}

void renderTerrainWithCave(vmath::vec4 clippingPlane, Model *model)
{
	// code
	glUseProgram(gLitShaderProgram);

	vmath::mat4 modelMatrix = vmath::mat4::identity();

	// Create transformation matrix
	modelMatrix = vmath::translate(0.0f, -50.0f, 0.0f);
	// modelMatrix *= vmath::scale(20.0f, 20.0f, 20.0f);
	glUniformMatrix4fv(gLitModelMatrixUniform, 1, GL_FALSE, modelMatrix);
	glUniformMatrix4fv(gLitViewMatrixUniform, 1, GL_FALSE, gpCamera->getLookAtMatrix());
	glUniformMatrix4fv(gLitProjectionMatrixUniform, 1, GL_FALSE, perspectiveProjectionMatrix);
	glUniform4fv(gLitClippingPlaneUniform, 1, clippingPlane);
	glUniform1i(gLitTextureSamplerUniform, 0);

	mountainExteriorSceneLights.cameraPos = gpCamera->m_position;
	applySceneLighting(mountainExteriorSceneLights);

	renderModel(model);

	glUseProgram(0);
}

void renderCaveInterior(vmath::vec4 clippingPlane, Model *model[CAVE_INTERIOR_MODELS_SIZE])
{
	// code
	SceneLightParams *pLights = nullptr;
	pLights = &caveInteriorScene_HanumajiLights;

	// BOOL bLit = (pLights && pLights->bEnableLighting && gLitShaderProgram != 0);
	glUseProgram(gLitShaderProgram);

	vmath::mat4 modelMatrix = vmath::mat4::identity();
	for (int i = 0; i < CAVE_INTERIOR_MODELS_SIZE; i++)
	{
		// Create transformation matrix
		modelMatrix = vmath::translate(gpCaveInteriorParams[i].translation[0], gpCaveInteriorParams[i].translation[1], gpCaveInteriorParams[i].translation[2]);
		modelMatrix *= vmath::scale(gpCaveInteriorParams[i].scale[0], gpCaveInteriorParams[i].scale[1], gpCaveInteriorParams[i].scale[2]);

		if (pLights)
			pLights->cameraPos = vmath::vec3(0.0f, -10.0f, 8.0f);

		glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, modelMatrix);

		glUniformMatrix4fv(gLitModelMatrixUniform, 1, GL_FALSE, modelMatrix);
		glUniformMatrix4fv(gLitViewMatrixUniform, 1, GL_FALSE, gpCamera->getLookAtMatrix());
		glUniformMatrix4fv(gLitProjectionMatrixUniform, 1, GL_FALSE, perspectiveProjectionMatrix);
		glUniform4fv(gLitClippingPlaneUniform, 1, clippingPlane);
		glUniform1i(gLitTextureSamplerUniform, 0);

		applySceneLighting(*pLights);

		renderModel(model[i]);
	}

	glUseProgram(0);
}

void renderRamWorshipModels(vmath::vec4 clippingPlane, Model *model[RAM_WORSHIP_MODELS_SIZE])
{
	// void renderRamWorshipTerrainWithShadow(vmath::vec4 clippingPlane, Model * model);

	// code
	glUseProgram(shaderProgramObject);
	vmath::mat4 modelMatrix = vmath::mat4::identity();
	for (int i = 0; i < RAM_WORSHIP_MODELS_SIZE - 1; i++)
	{

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		// Create transformation matrix
		modelMatrix = vmath::translate(gpWorshipModelParams[i].translation[0], gpWorshipModelParams[i].translation[1], gpWorshipModelParams[i].translation[2]);
		modelMatrix *= vmath::scale(gpWorshipModelParams[i].scale[0], gpWorshipModelParams[i].scale[1], gpWorshipModelParams[i].scale[2]);

		glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, modelMatrix);

		glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, gpCamera->getLookAtMatrix());
		glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, perspectiveProjectionMatrix);
		glUniform4fv(clippingPlaneUniform, 1, clippingPlane);
		glUniform1i(textureSamplerUniform, 0);

		renderModel(model[i]);

		glDisable(GL_BLEND);
	}

	glUseProgram(0);

	// renderRamWorshipTerrainWithShadow(clippingPlane, model[0]);
}

// void renderRamWorshipTerrainWithShadow(vmath::vec4 clippingPlane, Model *model)
// {
// 	// Code

// 	if (litSabhamandapProgramWithShadow)
// 	{
// 		litSabhamandapProgramWithShadow->StartProgram();

// 		vmath::mat4 modelMatrix = vmath::mat4::identity();
// 		vmath::mat4 identityMat = vmath::mat4::identity();
// 		vmath::mat4 animalsLightMatrix = vmath::lookat(vmath::vec3(ramworshipAnimalShadow.lightX, ramworshipAnimalShadow.lightY, ramworshipAnimalShadow.lightZ),
// 													   vmath::vec3(0.0f, 0.0f, -10.0f),
// 													   vmath::vec3(0.0f, 1.0f, 0.0f));

// 		vmath::mat4 animalplvmMatrix = perspectiveProjectionMatrix * animalsLightMatrix * modelMatrix;

// 		// vmath::mat4 hanumanShadowTreeLightMatrix = vmath::lookat(vmath::vec3(hanumanYuddha01Shadow.lightX, hanumanYuddha01Shadow.lightY, hanumanYuddha01Shadow.lightZ),
// 		// 														 vmath::vec3(0.0f, 0.0f, -10.0f),
// 		// 														 vmath::vec3(0.0f, 1.0f, 0.0f));

// 		// vmath::mat4 hanumanYuddhaplvmMatrix = perspectiveProjectionMatrix * hanumanShadowTreeLightMatrix * modelMatrix;

// 		litSabhamandapProgramWithShadow->SetUniforms(
// 			perspectiveProjectionMatrix,
// 			gpCamera->getLookAtMatrix(),
// 			modelMatrix,
// 			animalplvmMatrix,
// 			// hanumanYuddhaplvmMatrix,
// 			identityMat,
// 			identityMat,
// 			identityMat,
// 			identityMat,
// 			clippingPlane,
// 			ramvachanLights,
// 			1, asurShadow.shadowPower, 1,
// 			2, 0, 0,
// 			3, 0, 0,
// 			4, 0, 0,
// 			5, 0, 0);

// 		ramworshipAnimalFBO->BindDepthTexture(1);
// 		// hanumanShadowFBO->BindDepthTexture(2);

// 		renderModel(model);

// 		litSabhamandapProgramWithShadow->StopProgram();
// 	}
// }

void renderYudhaScene2Models(vmath::vec4 clippingPlane, Model *model[YUDDHA_SCENE2_MODELS_SIZE])
{
	glUseProgram(shaderProgramObject);
	vmath::mat4 modelMatrix = vmath::mat4::identity();
	for (int i = 0; i < YUDDHA_SCENE2_MODELS_SIZE - 1; i++)
	{
		// Create transformation matrix
		modelMatrix = vmath::translate(gpYudhaScene2Params[i].translation[0], gpYudhaScene2Params[i].translation[1], gpYudhaScene2Params[i].translation[2]);
		modelMatrix *= vmath::scale(gpYudhaScene2Params[i].scale[0], gpYudhaScene2Params[i].scale[1], gpYudhaScene2Params[i].scale[2]);

		glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, modelMatrix);
		glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, gpCamera->getLookAtMatrix());
		glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, perspectiveProjectionMatrix);
		glUniform4fv(clippingPlaneUniform, 1, clippingPlane);
		glUniform1i(textureSamplerUniform, 0);

		renderModel(model[i]);
	}
	glUseProgram(0);
}

void display(void)
{
	char titleText[255];

	// function prototypes
	void renderSceneSelection(int sceneID);

	ELAPSED_TIME = sdkGetTimerValue(&sceneTimer);
	ELAPSED_TIME = ELAPSED_TIME / 1000.0f + gTimeOffset;

	for (int i = 0; i < gTransitionCount; i++)
	{
		SceneTransitionData &t = gSceneTransitions[i];

		if (selected_scene == t.fromScene && ELAPSED_TIME >= t.triggerTime && !gTransition.isTransitioning && !(*t.fired))
		{
			startSceneTransition(
				t.type,
				t.fromScene,
				t.toScene,
				t.duration);

			*t.fired = true;
			break;
		}
	}

	static bool bFBOPhaseComplete = false;

	// Mark FBO phase done the first time we leave SCENE_TITLES
	if (!bFBOPhaseComplete &&
		selected_scene != SCENE_AMC_BANNER &&
		selected_scene != SCENE_TITLES &&
		!gTransition.isTransitioning)
	{
		bFBOPhaseComplete = true;
	}

	if (!bFBOPhaseComplete && gTransition.isTransitioning)
	{
		// ---- FBO : AMC_BANNER → TITLES burn
		updateTransitionProgress(ELAPSED_TIME);

		// Render outgoing scene (AMC video) into texture A
		bindTransitionFramebuffer();
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
							   GL_TEXTURE_2D, textureSceneA, 0);
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		renderSceneSelection(gTransition.fromSceneID);

		// Render incoming scene (TITLES) into texture B
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
							   GL_TEXTURE_2D, textureSceneB, 0);
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		renderSceneSelection(gTransition.toSceneID);

		unbindTransitionFramebuffer();
		renderTransitionOutput();
	}
	else
	{
		// ---- Direct load : no FBO, no transition
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, g_iWinWidth, g_iWinHeight);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		renderSceneSelection(selected_scene);
	}

	// ---- FADE LOGIC ----
	if (!gTransition.isTransitioning)
	{
		float currentSceneStart = 0.0f;
		float nextSceneStart = 0.0f;

		switch (selected_scene)
		{
		case SCENE_AMC_BANNER:
			currentSceneStart = START_TIME_AMC_BANNER;
			nextSceneStart = START_TIME_TITLES;
			break;

		case SCENE_TITLES:
			currentSceneStart = START_TIME_TITLES;
			nextSceneStart = START_TIME_MOUNTAIN_CAVE_EXTERIOR;
			break;

		case SCENE_MOUNTAIN_CAVE_EXTERIOR:
			currentSceneStart = START_TIME_MOUNTAIN_CAVE_EXTERIOR;
			nextSceneStart = START_TIME_CAVE_INTERIOR;
			break;

		case SCENE_CAVE_INTERIOR:
			currentSceneStart = START_TIME_CAVE_INTERIOR;
			nextSceneStart = START_TIME_MOUNTAIN_PEAK;
			break;

		case SCENE_MOUNTAIN_PEAK:
			currentSceneStart = START_TIME_MOUNTAIN_PEAK;
			nextSceneStart = START_TIME_FLYING;
			break;

		case SCENE_FLYING:
			currentSceneStart = START_TIME_FLYING;
			nextSceneStart = START_TIME_OCEAN;
			break;

		case SCENE_OCEAN:
			currentSceneStart = START_TIME_OCEAN;
			nextSceneStart = START_TIME_RAM_VACHAN;
			break;

		case SCENE_RAM_VACHAN:
			currentSceneStart = START_TIME_RAM_VACHAN;
			nextSceneStart = START_TIME_YUDDHA_SCENE1;
			break;

		case SCENE_YUDDHA_SCENE1:
			currentSceneStart = START_TIME_YUDDHA_SCENE1;
			nextSceneStart = START_TIME_YUDDHA_SCENE2;
			break;

		case SCENE_YUDDHA_SCENE2:
			currentSceneStart = START_TIME_YUDDHA_SCENE2;
			nextSceneStart = START_TIME_SABHA_MANDAP;
			break;

		case SCENE_SABHA_MANDAP:
			currentSceneStart = START_TIME_SABHA_MANDAP;
			nextSceneStart = START_TIME_END_CREDITS;
			break;

		case SCENE_END_CREDITS:
			currentSceneStart = START_TIME_END_CREDITS;
			nextSceneStart = START_TIME_RAM_WORSHIP;
			break;

		case SCENE_RAM_WORSHIP:
			currentSceneStart = START_TIME_RAM_WORSHIP;
			nextSceneStart = END_TIME_TOTAL; // TOTAL_DURATION OF SONG
			break;
		default:
			currentSceneStart = 0.0f;
			nextSceneStart = ELAPSED_TIME + 10.0f;
			break;
		}

		float fadeDuration = FADE_OUT_DURATION;
		float manualAlpha = 0.0f;
		float timeRemaining = nextSceneStart - ELAPSED_TIME;

		// Trigger Fade Out near the end of the scene
		if (timeRemaining <= fadeDuration && timeRemaining > 0.0f)
		{
			manualAlpha = (fadeDuration - timeRemaining) / fadeDuration;
		}

		if (manualAlpha < 0.0f)
			manualAlpha = 0.0f;
		if (manualAlpha > 1.0f)
			manualAlpha = 1.0f;

		setFadeAlphaManual(manualAlpha);
		drawFadeOverlay();
	}

	if (bShowImGui)
		displayImGui();

	sprintf(titleText, "ELAPSED_TIME = %.2f", ELAPSED_TIME);
	SetWindowTextA(ghwnd, titleText);
	SwapBuffers(ghdc);
}

void renderSceneSelection(int sceneID)
{
	vmath::mat4 modelMatrix = vmath::mat4::identity();

	switch (sceneID)
	{
	case SCENE_AMC_BANNER:
	{
		// Use static texture
		// RenderTexturedBasedScene(creditsTexture[creditsTextureNum].id, alpha);

		// Use video texture
		if (gAMCBannerVideo.textureID != 0)
			RenderTexturedBasedScene(gAMCBannerVideo.textureID, 1.0f); // alpha=1.0 for video
	}
	break;

	case SCENE_TITLES:
	{
		// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// RenderTexturedBasedScene(creditsTexture[creditsTextureNum].id, alpha);
		DisplayTitle();
	}
	break;

	case SCENE_MOUNTAIN_CAVE_EXTERIOR:
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		bool bWasBezier = gpCamera->m_bUseBezierCamera;
		if (bWasBezier && camera_SnowTerrain)
		{
			gpCamera->m_bUseBezierCamera = false;
		}

		vmath::vec4 clippingPlane = vmath::vec4(0.0f, 0.0f, 0.0f, 0.0f);
		renderSkybox(gpCamera, perspectiveProjectionMatrix, clippingPlane);

		gpCamera->rotateOnMouse(bRotateCamera);

		renderTerrainWithCave(clippingPlane, gpTerrainWithCave);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		renderTerrainWithCave(clippingPlane, gpTreesOnFirstTerrain);
		glDisable(GL_BLEND);

		static GLuint localDepthTex = 0;
		if (localDepthTex == 0)
		{
			glGenTextures(1, &localDepthTex);
			glBindTexture(GL_TEXTURE_2D, localDepthTex);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}

		glBindTexture(GL_TEXTURE_2D, localDepthTex);
		glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, 0, 0, g_iWinWidth, g_iWinHeight, 0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glDisable(GL_DEPTH_TEST);
		glDepthMask(GL_FALSE);

		drawFogVolumeLayer(gMountainExteriorSceneFogParams, localDepthTex, perspectiveProjectionMatrix);

		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);

		renderSnowfall(
			snowfallParams,
			gpCamera,
			perspectiveProjectionMatrix,
			g_iWinWidth,
			g_iWinHeight);

		if (bWasBezier && camera_SnowTerrain)
		{
			gpCamera->m_bUseBezierCamera = true;
		}

		glDisable(GL_BLEND);
	}
	break;

	case SCENE_CAVE_INTERIOR:
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		bool bWasBezier = gpCamera->m_bUseBezierCamera;
		if (bWasBezier && camera_CaveInterior)
		{
			gpCamera->m_bUseBezierCamera = false;
		}

		vmath::vec4 clippingPlane = vmath::vec4(0.0f, 0.0f, 0.0f, 0.0f);

		gpCamera->rotateOnMouse(bRotateCamera);

		renderCaveInterior(clippingPlane, gpCaveInteriorModels);

		renderBloom(hanumanGlowParams, gpCamera, perspectiveProjectionMatrix);

		static GLuint localDepthTex = 0;
		if (localDepthTex == 0)
		{
			glGenTextures(1, &localDepthTex);
			glBindTexture(GL_TEXTURE_2D, localDepthTex);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}

		glBindTexture(GL_TEXTURE_2D, localDepthTex);
		glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, 0, 0, g_iWinWidth, g_iWinHeight, 0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glDisable(GL_DEPTH_TEST);
		glDepthMask(GL_FALSE);

		drawFogVolumeLayer(gMountainExteriorSceneFogParams, localDepthTex, perspectiveProjectionMatrix);

		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);

		if (bWasBezier && camera_CaveInterior)
		{
			gpCamera->m_bUseBezierCamera = true;
		}

		glDisable(GL_BLEND);
	}
	break;

	case SCENE_MOUNTAIN_PEAK:
	{
		bool bWasBezier = gpCamera->m_bUseBezierCamera;
		if (bWasBezier && camera_MountainPeakScene)
		{
			gpCamera->m_bUseBezierCamera = false;
		}

		// START RENDER TO FBO
		if (volumetriccloudsForPeakScene)
		{
			volumetriccloudsForPeakScene->RenderCloudTextures();
		}

		// START RENDER TO FBO
		if (volumetriccloudsForPeakScene)
		{
			volumetriccloudsForPeakScene->StartRenderingToFBO();
		}

		// Render skybox first (drawn at horizon behind ocean)
		vmath::vec4 clippingPlane = vmath::vec4(0.0f, 0.0f, 0.0f, 0.0f);
		// renderSkybox(gpCamera, perspectiveProjectionMatrix, clippingPlane);

		renderSkydome(skydomeParams[0], gpCamera, perspectiveProjectionMatrix);

		gpCamera->rotateOnMouse(bRotateCamera);

		vmath::mat4 view = vmath::lookat(vec3(0.0f, 1000.0f, 1000.0f),
										 vec3(0.0f, 0.0f, 0.0f),
										 vec3(0.0f, 1.0f, 0.0f));

		mountainPeakProgram->StartProgram();
		{

			mountainPeakProgram->SetUniforms(perspectiveProjectionMatrix,
											 modelMatrix,
											 //  view,
											 gpCamera->getLookAtMatrix(),
											 0);

			renderModel(gpMountain);
			renderModel(gpSideMountain);
		}
		mountainPeakProgram->StopProgram();

		// sideMountainPeakProgram->StartProgram();
		// {

		// 	sideMountainPeakProgram->SetUniforms(perspectiveProjectionMatrix,
		// 										 modelMatrix,
		// 										 view,
		// 										 // gpCamera->getLookAtMatrix(),
		// 										 0);

		// 	renderModel(gpSideMountain);
		// }
		// sideMountainPeakProgram->StopProgram();

		renderPBRModel(gpHanumanOnMountain, vmath::vec3(hanumanPosX, hanumanPosY, hanumanPosZ), vmath::vec3(4.0f, 4.0f, 4.0f));

		// pointProgram->StartProgram();
		// {
		// 	pointProgram->SetUniforms(perspectiveProjectionMatrix,
		// 							  modelMatrix,
		// 							  gpCamera->getLookAtMatrix(),
		// 							  vmath::vec3(1.0f, 0.0f, 0.0f));

		// 	pointProgram->DrawPoints(verts);
		// }
		// pointProgram->StopProgram();

		// STOP RENDER TO FBO
		if (volumetriccloudsForPeakScene)
		{
			volumetriccloudsForPeakScene->StopRenderingToFBO();
		}

		// RENDER WITH CLOUDS
		if (volumetriccloudsForPeakScene)
		{
			volumetriccloudsForPeakScene->Display(perspectiveProjectionMatrix,
												  modelMatrix,
												  gpCamera->getLookAtMatrix(),
												  gpCamera->getPosition(),
												  //   camera.GetCameraPosition(),
												  ELAPSED_TIME);
		}

		float flareWindowStart = START_TIME_MOUNTAIN_PEAK + 3.4f;
		float flareWindowEnd = START_TIME_MOUNTAIN_PEAK + 4.9f;
		if (ELAPSED_TIME >= flareWindowStart && ELAPSED_TIME <= flareWindowEnd)
		{
			float u = (ELAPSED_TIME - flareWindowStart) / (flareWindowEnd - flareWindowStart);

			float rise = u / 0.12f;
			if (rise < 0.0f)
				rise = 0.0f;
			if (rise > 1.0f)
				rise = 1.0f;
			rise = rise * rise * (3.0f - 2.0f * rise);

			float fall = (u - 0.70f) / 0.30f;
			if (fall < 0.0f)
				fall = 0.0f;
			if (fall > 1.0f)
				fall = 1.0f;
			fall = 1.0f - fall * fall * (3.0f - 2.0f * fall);

			mountainPeakFlareParams.externalVisibility = rise * fall;
			renderWaterLensFlare(mountainPeakFlareParams, gpCamera, perspectiveProjectionMatrix, waterParams[0], g_iWinWidth, g_iWinHeight);
		}

		if (bWasBezier && camera_MountainPeakScene)
		{
			gpCamera->m_bUseBezierCamera = true;
		}
	}
	break;

	case SCENE_FLYING:
	{
		bool bWasBezier = gpCamera->m_bUseBezierCamera;
		if (bWasBezier && camera_FlyingScene)
		{
			gpCamera->m_bUseBezierCamera = false;
		}

		// START RENDER TO FBO
		if (volumetriccloudsForFlyingScene)
		{
			volumetriccloudsForFlyingScene->RenderCloudTextures();
		}

		// START RENDER TO FBO
		if (volumetriccloudsForFlyingScene)
		{
			volumetriccloudsForFlyingScene->StartRenderingToFBO();
		}

		// Render skybox first (drawn at horizon behind ocean)
		vmath::vec4 clippingPlane = vmath::vec4(0.0f, 0.0f, 0.0f, 0.0f);
		// renderSkybox(gpCamera, perspectiveProjectionMatrix, clippingPlane);

		renderSkydome(skydomeParams[0], gpCamera, perspectiveProjectionMatrix);

		gpCamera->rotateOnMouse(bRotateCamera);

		// renderFlyingScene(clippingPlane, gpHanumanJi_FlyingModel);

		static float flyingX = -230.00f;
		static float flyingZ = 0.00f;

		// Incrementally move the model
		if (ELAPSED_TIME < START_TIME_FLYING + (START_TIME_OCEAN - START_TIME_FLYING) / 2.0f)
			flyingX += 0.05f;
		else
			flyingX += 0.9f;

		// flyingZ -= 0.05f;

		modelMatrix = vmath::mat4::identity();
		modelMatrix *= vmath::translate(flyingX, flyingY, flyingZ); // * vmath::rotate(70.0f, 0.0f, 1.0f, 0.0f);

		renderUsingLitProgram(gpCamera, clippingPlane, gpHanumanJi_FlyingModel, modelMatrix, &flyingHanumanJiLights);

		// STOP RENDER TO FBO
		if (volumetriccloudsForFlyingScene)
		{
			volumetriccloudsForFlyingScene->StopRenderingToFBO();
		}

		// RENDER WITH CLOUDS
		if (volumetriccloudsForFlyingScene)
		{
			volumetriccloudsForFlyingScene->Display(perspectiveProjectionMatrix,
													modelMatrix,
													gpCamera->getLookAtMatrix(),
													gpCamera->getPosition(),
													//   camera.GetCameraPosition(),
													ELAPSED_TIME);
		}

		if (bWasBezier && camera_FlyingScene)
		{
			gpCamera->m_bUseBezierCamera = true;
		}
	}
	break;

	case SCENE_OCEAN:
	{
		bool bWasBezier = gpCamera->m_bUseBezierCamera;
		if (bWasBezier && camera_Ocean)
		{
			gpCamera->m_bUseBezierCamera = false;
		}

		// START RENDER TO FBO
		if (volumetriccloudsForOcean)
		{
			volumetriccloudsForOcean->RenderCloudTextures();
		}

		// START RENDER TO FBO
		if (volumetriccloudsForOcean)
		{
			volumetriccloudsForOcean->StartRenderingToFBO();
		}

		gpCamera->setCameraState(gpCamera->getPosition(), vmath::vec3(hanumanOceanXPos, hanumanOceanYPos, hanumanOceanZPos));

		// Render skybox first (drawn at horizon behind ocean)
		vmath::vec4 clippingPlane = vmath::vec4(0.0f, 0.0f, 0.0f, 0.0f);
		// renderSkybox(gpCamera, perspectiveProjectionMatrix, clippingPlane);
		renderSkydome(skydomeParams[0], gpCamera, perspectiveProjectionMatrix);

		// renderFlyingSceneForOcean(clippingPlane, gpHanumanJi_FlyingModel);

		hanumanOceanXPos += hanumanOceanXFactor;

		modelMatrix = vmath::mat4::identity();
		modelMatrix *= vmath::translate(hanumanOceanXPos, hanumanOceanYPos, hanumanOceanZPos); // * vmath::rotate(70.0f, 0.0f, 1.0f, 0.0f);
		modelMatrix *= vmath::scale(3.0f, 3.0f, 3.0f);										   // * vmath::rotate(70.0f, 0.0f, 1.0f, 0.0f);

		renderUsingLitProgram(gpCamera, clippingPlane, gpHanumanJi_FlyingModel, modelMatrix, &flyingHanumanJiLights);

		// Render tessellated Gerstner ocean on top
		// #if OCEAN_USE == 1
		// 		renderOcean(oceanParams, gpCamera, perspectiveProjectionMatrix);
		// #else
		renderOcean(gOcean, gpCamera, perspectiveProjectionMatrix, ELAPSED_TIME);
		// #endif

		if (pBoidSimulation && boidParamsVshape.bEnable)
		{
			boidParamsVshape.type = BOID_V_SHAPE; // Ensure correct type is set for rendering
			pBoidSimulation->Render(perspectiveProjectionMatrix, gpCamera->getLookAtMatrix(), boidParamsVshape);
		}

		// STOP RENDER TO FBO
		if (volumetriccloudsForOcean)
		{
			volumetriccloudsForOcean->StopRenderingToFBO();
		}

		if (volumetriccloudsForOcean)
		{
			volumetriccloudsForOcean->Display(perspectiveProjectionMatrix,
											  modelMatrix,
											  gpCamera->getLookAtMatrix(),
											  gpCamera->getPosition(),
											  //   camera.GetCameraPosition(),
											  ELAPSED_TIME);
		}

		if (bWasBezier && camera_Ocean)
		{
			gpCamera->m_bUseBezierCamera = true;
		}
	}
	break;

	case SCENE_RAM_VACHAN:
	{
		bool bWasBezier = gpCamera->m_bUseBezierCamera;
		if (bWasBezier && camera_RamVachanScene)
		{
			gpCamera->m_bUseBezierCamera = false;
		}

		ramVachanShadowFBO->Clear(0.4f, 0.4f, 0.4f, 1.0f);

		ramVachanShadowFBO->Bind();
		{
			glClear(GL_DEPTH_BUFFER_BIT);

			shadowProgram->StartProgram();
			{
				vmath::mat4 lightViewMat = vmath::lookat(
					vmath::vec3(ramVachanShadow.lightX, ramVachanShadow.lightY, ramVachanShadow.lightZ),
					vmath::vec3(0.0f, 0.0f, -10.0f),
					vmath::vec3(0.0f, 1.0f, 0.0f));

				modelMatrix = vmath::mat4::identity();
				modelMatrix *= vmath::translate(ramVachanShadow.shadowX, ramVachanShadow.shadowY, ramVachanShadow.shadowZ);

				shadowProgram->SetUniforms(perspectiveProjectionMatrix, lightViewMat, modelMatrix);

				renderModel(gpRamVachan_RamWithHanuman);
			}
			shadowProgram->StopProgram();
		}
		ramVachanShadowFBO->Unbind();

		ramVachanTreeShadowFBO->Clear(0.4f, 0.4f, 0.4f, 1.0f);

		ramVachanTreeShadowFBO->Bind();
		{
			glClear(GL_DEPTH_BUFFER_BIT);

			shadowProgram->StartProgram();
			{
				vmath::mat4 lightViewMat = vmath::lookat(
					vmath::vec3(ramVachanTreeShadow.lightX, ramVachanTreeShadow.lightY, ramVachanTreeShadow.lightZ),
					vmath::vec3(0.0f, 0.0f, -10.0f),
					vmath::vec3(0.0f, 1.0f, 0.0f));

				modelMatrix = vmath::mat4::identity();
				modelMatrix *= vmath::translate(ramVachanTreeShadow.shadowX, ramVachanTreeShadow.shadowY, ramVachanTreeShadow.shadowZ);

				shadowProgram->SetUniforms(perspectiveProjectionMatrix, lightViewMat, modelMatrix);

				renderModel(gpRamVachan_Trees);
			}
			shadowProgram->StopProgram();
		}
		ramVachanTreeShadowFBO->Unbind();

		glViewport(0, 0, (GLsizei)gwinWidth, (GLsizei)gwinHeight);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// ---------- Ram-Hanuman anmol vachan Scene
		// -------------------------------------------------------------------------
		// render into water reflection framebuffer
		// -------------------------------------------------------------------------

		bindFramebuffer(waterReflectionFramebuffer, screenWidth, screenHeight);
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			float originalCamY = gpCamera->m_position[1];
			gpCamera->m_position[1] = 2.0f * waterParams[0].translation[1] - gpCamera->m_position[1];

			gpCamera->invertPitch();
			gpCamera->update();

			vmath::vec4 clippingPlane = vmath::vec4(0.0f, 1.0f, 0.0f, -waterParams[0].translation[1]);

			renderSkybox(gpCamera, perspectiveProjectionMatrix, vmath::vec4(0.0f, 0.0f, 0.0f, 0.0f));

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			renderTerrainScene(clippingPlane, gpRamVachan_TerrainModel);
			renderTerrainScene(clippingPlane, gpRamVachan_Trees);
			renderTerrainScene(clippingPlane, gpRamVachan_RamWithHanuman);

			glDisable(GL_BLEND);

			gpCamera->m_position[1] = originalCamY;
			gpCamera->invertPitch();
			gpCamera->update();
		}
		unbindFramebuffer();

		// -------------------------------------------------------------------------
		// render into water refraction framebuffer
		// -------------------------------------------------------------------------
		bindFramebuffer(waterRefractionFramebuffer, screenWidth, screenHeight);
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			vmath::vec4 clippingPlane = vmath::vec4(0.0f, -1.0f, 0.0f, +waterParams[0].translation[1]);

			renderSkybox(gpCamera, perspectiveProjectionMatrix, vmath::vec4(0.0f, 0.0f, 0.0f, 0.0f));

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			renderTerrainScene(clippingPlane, gpRamVachan_TerrainModel);
			renderTerrainScene(clippingPlane, gpRamVachan_Trees);
			renderTerrainScene(clippingPlane, gpRamVachan_RamWithHanuman);

			glDisable(GL_BLEND);
		}
		unbindFramebuffer();

		// -------------------------------------------------------------------------
		// render into default framebuffer
		// -------------------------------------------------------------------------
		glViewport(0, 0, g_iWinWidth, g_iWinHeight);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		vmath::vec4 clippingPlane = vmath::vec4(0.0f, -1.0f, 0.0f, 90000.0f);

		pGrass->render(gpCamera->getLookAtMatrix(), perspectiveProjectionMatrix, gpCamera->m_position);

		renderSkydome(skydomeParams[3], gpCamera, perspectiveProjectionMatrix);
		renderGodRays(godRaysParams, gpCamera, perspectiveProjectionMatrix, 0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		renderTerrainSceneWithShadow(clippingPlane, gpRamVachan_TerrainModel);
		renderTerrainScene(clippingPlane, gpRamVachan_Trees);
		// renderTerrainScene(clippingPlane, gpRamVachan_RamWithHanuman);
		renderWater(waterParams[0], gpCamera, perspectiveProjectionMatrix);

		// renderTerrainScene(clippingPlane, gpRamVachan_RamWithHanuman);

		modelMatrix = vmath::mat4::identity();
		modelMatrix *= vmath::translate(10.0f, 0.0f, -1.0f);

		renderUsingLitProgram(gpCamera, clippingPlane, gpRamVachan_RamWithHanuman, modelMatrix, &generalHanumanJiLights);

		glDisable(GL_BLEND);

		renderWaterLensFlare(ramVachanFlareParams, gpCamera, perspectiveProjectionMatrix, waterParams[0], g_iWinWidth, g_iWinHeight);

		glViewport(0, 0, g_iWinWidth, g_iWinHeight);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		// ---------- Ram-Hanuman anmol vachan Scene ends here

		if (bWasBezier && camera_RamVachanScene)
		{
			gpCamera->m_bUseBezierCamera = true;
		}
	}
	break;

	case SCENE_YUDDHA_SCENE1:
	{
		bool bWasBezier = gpCamera->m_bUseBezierCamera;
		if (bWasBezier && camera_YuddhaScene1)
		{
			gpCamera->m_bUseBezierCamera = false;
		}

		if (ELAPSED_TIME >= START_TIME_YUDDHA_SCENE1 + 6.0f)
		{
			YFactor -= 0.5f;
		}

		asurShadowFBO->Clear(0.4f, 0.4f, 0.4f, 1.0f);

		asurShadowFBO->Bind();
		{
			glClear(GL_DEPTH_BUFFER_BIT);

			shadowProgram->StartProgram();
			{
				// vmath::vec3 lpos = sabhamandapScene_ThroneLights.keyLight.position;

				vmath::mat4 lightViewMat = vmath::lookat(vmath::vec3(asurShadow.lightX, asurShadow.lightY, asurShadow.lightZ),
														 vmath::vec3(0.0f, 0.0f, -10.0f),
														 vmath::vec3(0.0f, 1.0f, 0.0f));

				modelMatrix = vmath::mat4::identity();
				modelMatrix *= vmath::translate(asurShadow.shadowX, asurShadow.shadowY, asurShadow.shadowZ);

				shadowProgram->SetUniforms(perspectiveProjectionMatrix, lightViewMat, modelMatrix);

				renderModel(gpAsurSena);
			}
			shadowProgram->StopProgram();
		}
		asurShadowFBO->Unbind();

		hanumanShadowFBO->Clear(0.4f, 0.4f, 0.4f, 1.0f);

		hanumanShadowFBO->Bind();
		{
			glClear(GL_DEPTH_BUFFER_BIT);

			shadowProgram->StartProgram();
			{
				// vmath::vec3 lpos = sabhamandapScene_ThroneLights.keyLight.position;

				vmath::mat4 lightViewMat = vmath::lookat(vmath::vec3(hanumanYuddha01Shadow.lightX, hanumanYuddha01Shadow.lightY, hanumanYuddha01Shadow.lightZ),
														 vmath::vec3(0.0f, 0.0f, -10.0f),
														 vmath::vec3(0.0f, 1.0f, 0.0f));

				modelMatrix = vmath::mat4::identity();
				modelMatrix *= vmath::translate(hanumanYuddha01Shadow.shadowX, hanumanYuddha01Shadow.shadowY + 50.0f + YFactor, hanumanYuddha01Shadow.shadowZ);

				shadowProgram->SetUniforms(perspectiveProjectionMatrix, lightViewMat, modelMatrix);

				renderModel(gpHanumanJiInYuddha_one);
			}
			shadowProgram->StopProgram();
		}
		hanumanShadowFBO->Unbind();

		glViewport(0, 0, (GLsizei)gwinWidth, (GLsizei)gwinHeight);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		vmath::vec4 clippingPlane = vmath::vec4(0.0f, 0.0f, 0.0f, 0.0f);
		gpCamera->rotateOnMouse(bRotateCamera);
		vmath::mat4 viewMatrix = gpCamera->getLookAtMatrix();

		modelMatrix = vmath::mat4::identity();

		// pointProgram->StartProgram();
		// {
		// 	pointProgram->SetUniforms(perspectiveProjectionMatrix,
		// 							  modelMatrix,
		// 							  gpCamera->getLookAtMatrix(),
		// 							  vmath::vec3(1.0f, 0.0f, 0.0f));

		// 	pointProgram->DrawPoints(verts);
		// }
		// pointProgram->StopProgram();

		// Render without dissolve effect - madam's change translate from top
		SceneLightParams *pLights = nullptr;
		pLights = &generalHanumanJiLights;

		// renderModel(gpHanumanJiInYuddha_one);

		modelMatrix = vmath::mat4::identity();
		modelMatrix *= vmath::translate(-30.0f, 130.0f + YFactor, -120.96f);
		renderUsingLitProgram(gpCamera, clippingPlane, gpHanumanJiInYuddha_one, modelMatrix, &generalHanumanJiLights);

		glUseProgram(shaderProgramObject);

		modelMatrix = vmath::mat4::identity();
		modelMatrix *= vmath::translate(-30.0f, -1.0f, -120.96f);
		glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, modelMatrix);
		renderModel(gpAsurSena);

		glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, modelMatrix);
		glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, gpCamera->getLookAtMatrix());
		glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, perspectiveProjectionMatrix);
		glUniform4fv(clippingPlaneUniform, 1, clippingPlane);
		glUniform1i(textureSamplerUniform, 0);

		// renderModel(gpYuddhaScene1Platform);
		renderYuddhaTerrainSceneWithShadow(clippingPlane, gpYuddhaScene1Platform);

		glUseProgram(0);

		static GLuint localDepthTex = 0;
		if (localDepthTex == 0)
		{
			glGenTextures(1, &localDepthTex);
			glBindTexture(GL_TEXTURE_2D, localDepthTex);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}

		glBindTexture(GL_TEXTURE_2D, localDepthTex);
		glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, 0, 0, g_iWinWidth, g_iWinHeight, 0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glDisable(GL_DEPTH_TEST);
		glDepthMask(GL_FALSE);

		drawFogVolumeLayer(gYuddhaScene1FogParams, localDepthTex, perspectiveProjectionMatrix);

		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);

		if (bWasBezier && camera_YuddhaScene1)
		{
			gpCamera->m_bUseBezierCamera = true;
		}
	}
	break;

	case SCENE_YUDDHA_SCENE2:
	{
		void renderYudhaScene2Models(vmath::vec4 clippingPlane, Model * models[]);

		bool bWasBezier = gpCamera->m_bUseBezierCamera;
		if (bWasBezier && camera_YuddhaScene2)
		{
			gpCamera->m_bUseBezierCamera = false;
		}

		// START RENDER TO FBO
		if (volumetriccloudsForYuddhaScene)
		{
			volumetriccloudsForYuddhaScene->RenderCloudTextures();
		}

		// START RENDER TO FBO
		if (volumetriccloudsForYuddhaScene)
		{
			volumetriccloudsForYuddhaScene->StartRenderingToFBO();
		}

		vmath::vec4 clippingPlane = vmath::vec4(0.0f, 0.0f, 0.0f, 0.0f);
		gpCamera->rotateOnMouse(bRotateCamera);

		glViewport(0, 0, g_iWinWidth, g_iWinHeight);
		glClearColor(0.216, 0.278, 0.310, 1.0f); // Lightning sathi konta akash pahije to color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		renderYudhaScene2Models(clippingPlane, gpYudhaScene2Models);

		renderUsingLitProgram(gpCamera, clippingPlane, gpYudhaScene2Models[1], modelMatrix, &generalHanumanJiLights);
		glDisable(GL_BLEND);

		renderLightningWithFlash(ELAPSED_TIME, START_TIME_SABHA_MANDAP - 2.0f);

		// STOP RENDER TO FBO
		if (volumetriccloudsForYuddhaScene)
		{
			volumetriccloudsForYuddhaScene->StopRenderingToFBO();
		}

		// static GLuint localDepthTex = 0;
		// if (localDepthTex == 0)
		// {
		// 	glGenTextures(1, &localDepthTex);
		// 	glBindTexture(GL_TEXTURE_2D, localDepthTex);
		// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		// }

		// glBindTexture(GL_TEXTURE_2D, localDepthTex);
		// glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, 0, 0, g_iWinWidth, g_iWinHeight, 0);

		// glEnable(GL_BLEND);
		// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// glDisable(GL_DEPTH_TEST);
		// glDepthMask(GL_FALSE);

		// drawFogVolumeLayer(gYuddhaScene1FogParams, localDepthTex, perspectiveProjectionMatrix);

		// glEnable(GL_DEPTH_TEST);
		// glDepthMask(GL_TRUE);
		// RENDER WITH CLOUDS
		if (volumetriccloudsForYuddhaScene)
		{
			volumetriccloudsForYuddhaScene->Display(perspectiveProjectionMatrix,
													modelMatrix,
													gpCamera->getLookAtMatrix(),
													gpCamera->getPosition(),
													//   camera.GetCameraPosition(),
													ELAPSED_TIME);
		}

		if (bWasBezier && camera_YuddhaScene2)
		{
			gpCamera->m_bUseBezierCamera = true;
		}
	}
	break;

	case SCENE_SABHA_MANDAP:
	{

		if (pFire)
		{
			pFire->GenerateFireTexture(perspectiveProjectionMatrix);
		}

		pillarShadowFBO->Clear(0.4f, 0.4f, 0.4f, 1.0f);

		pillarShadowFBO->Bind();
		{
			glClear(GL_DEPTH_BUFFER_BIT);

			shadowProgram->StartProgram();
			{
				vmath::vec3 lpos = sabhamandapScene_ThroneLights.keyLight.position;

				vmath::mat4 lightViewMat = vmath::lookat(vmath::vec3(pillarShadow.lightX, pillarShadow.lightY, pillarShadow.lightZ),
														 vmath::vec3(0.0f, 0.0f, -10.0f),
														 vmath::vec3(0.0f, 1.0f, 0.0f));

				modelMatrix = vmath::mat4::identity();
				modelMatrix *= vmath::translate(pillarShadow.shadowX, pillarShadow.shadowY, pillarShadow.shadowZ);

				shadowProgram->SetUniforms(perspectiveProjectionMatrix, lightViewMat, modelMatrix);

				renderModel(gpPillarModel);
			}
			shadowProgram->StopProgram();
		}
		pillarShadowFBO->Unbind();

		ministerChairShadowFBO->Clear(0.4f, 0.4f, 0.4f, 1.0f);

		ministerChairShadowFBO->Bind();
		{
			glClear(GL_DEPTH_BUFFER_BIT);

			shadowProgram->StartProgram();
			{
				vmath::vec3 lpos = sabhamandapScene_ThroneLights.keyLight.position;

				vmath::mat4 lightViewMat = vmath::lookat(vmath::vec3(ministerChairShadow.lightX, ministerChairShadow.lightY, ministerChairShadow.lightZ),
														 vmath::vec3(0.0f, 0.0f, -10.0f),
														 vmath::vec3(0.0f, 1.0f, 0.0f));

				modelMatrix = vmath::mat4::identity();
				modelMatrix *= vmath::translate(ministerChairShadow.shadowX, ministerChairShadow.shadowY, ministerChairShadow.shadowZ);

				shadowProgram->SetUniforms(perspectiveProjectionMatrix, lightViewMat, modelMatrix);

				renderModel(gpMinisterChairModel);
			}
			shadowProgram->StopProgram();
		}
		ministerChairShadowFBO->Unbind();

		firePotShadowFBO->Clear(0.4f, 0.4f, 0.4f, 1.0f);

		firePotShadowFBO->Bind();
		{
			glClear(GL_DEPTH_BUFFER_BIT);

			shadowProgram->StartProgram();
			{
				vmath::vec3 lpos = sabhamandapScene_ThroneLights.keyLight.position;

				vmath::mat4 lightViewMat = vmath::lookat(vmath::vec3(fireKundShadow.lightX, fireKundShadow.lightY, fireKundShadow.lightZ),
														 vmath::vec3(0.0f, 0.0f, -10.0f),
														 vmath::vec3(0.0f, 1.0f, 0.0f));

				modelMatrix = vmath::mat4::identity();
				modelMatrix *= vmath::translate(fireKundShadow.shadowX, fireKundShadow.shadowY, fireKundShadow.shadowZ);

				shadowProgram->SetUniforms(perspectiveProjectionMatrix, lightViewMat, modelMatrix);

				renderModel(gpFirePotModel);
			}
			shadowProgram->StopProgram();
		}
		firePotShadowFBO->Unbind();

		hanumanShadowFBO->Clear(0.4f, 0.4f, 0.4f, 1.0f);

		hanumanShadowFBO->Bind();
		{
			glClear(GL_DEPTH_BUFFER_BIT);

			shadowProgram->StartProgram();
			{
				vmath::vec3 lpos = sabhamandapScene_ThroneLights.keyLight.position;

				vmath::mat4 lightViewMat = vmath::lookat(vmath::vec3(hanumanShadow.lightX, hanumanShadow.lightY, hanumanShadow.lightZ),
														 vmath::vec3(0.0f, 0.0f, -10.0f),
														 vmath::vec3(0.0f, 1.0f, 0.0f));

				modelMatrix = vmath::mat4::identity();
				modelMatrix *= vmath::translate(fireKundShadow.shadowX, fireKundShadow.shadowY, fireKundShadow.shadowZ);

				shadowProgram->SetUniforms(perspectiveProjectionMatrix, lightViewMat, modelMatrix);

				// renderPBRModel(gpHanumanJiModel, vmath::vec3(0.0f, 0.0f, 0.0f));
				renderModel(gpHanumanJiModel);
			}
			shadowProgram->StopProgram();
		}
		hanumanShadowFBO->Unbind();

		vibhishanShadowFBO->Clear(0.4f, 0.4f, 0.4f, 1.0f);

		vibhishanShadowFBO->Bind();
		{
			glClear(GL_DEPTH_BUFFER_BIT);

			shadowProgram->StartProgram();
			{
				vmath::vec3 lpos = sabhamandapScene_ThroneLights.keyLight.position;

				vmath::mat4 lightViewMat = vmath::lookat(vmath::vec3(vibhishanShadow.lightX, vibhishanShadow.lightY, vibhishanShadow.lightZ),
														 vmath::vec3(0.0f, 0.0f, -10.0f),
														 vmath::vec3(0.0f, 1.0f, 0.0f));

				modelMatrix = vmath::mat4::identity();
				modelMatrix *= vmath::translate(vibhishanShadow.shadowX, vibhishanShadow.shadowY, vibhishanShadow.shadowZ);

				shadowProgram->SetUniforms(perspectiveProjectionMatrix, lightViewMat, modelMatrix);

				renderModel(gpVibhishanModel);
				renderModel(gpThroneModel);
			}
			shadowProgram->StopProgram();
		}
		vibhishanShadowFBO->Unbind();

		glViewport(0, 0, (GLsizei)gwinWidth, (GLsizei)gwinHeight);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		bool bWasBezier = gpCamera->m_bUseBezierCamera;
		if (bWasBezier && camera_SabhaMandapScene)
		{
			gpCamera->m_bUseBezierCamera = false;
		}
		vmath::vec4 clippingPlane = vmath::vec4(0.0f, 0.0f, 1.0f, 10.0f);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		renderSabhaMandapSceneWithShadow(gpCamera, clippingPlane, gpSabhaMandapModel, 1, 1, 1, 1, 1);
		renderSabhaMandapSceneWithShadow(gpCamera, clippingPlane, gpThroneModel, 0, 1, 0, 0, 0);
		renderSabhaMandapSceneWithShadow(gpCamera, clippingPlane, gpFirePotModel, 0, 0, 0, 0, 0);
		renderSabhaMandapSceneWithShadow(gpCamera, clippingPlane, gpMinisterChairModel, 0, 0, 0, 0, 0);
		renderSabhaMandapSceneWithShadow(gpCamera, clippingPlane, gpPillarModel, 0, 0, 0, 1, 0);

		if (ELAPSED_TIME > 5.0f)
		{
			// renderPBRModel(gpHanumanJiModel, vmath::vec3(0.0f, 0.0f, -10.0f), vmath::vec3(1.0f, 1.0f, 1.0f));
			renderSabhaMandapSceneHanuman(gpCamera, clippingPlane, gpHanumanJiModel);
		}

		if (ELAPSED_TIME > 8.0f)
		{
			// renderPBRModel(gpVibhishanModel, vmath::vec3(0.0f, 0.0f, -10.0f), vmath::vec3(1.0f, 1.0f, 1.0f));
			renderSabhaMandapScene(gpCamera, clippingPlane, gpVibhishanModel);
		}

		glDisable(GL_BLEND);

		if (pFire)
		{
			modelMatrix = vmath::mat4::identity();
			modelMatrix *= vmath::translate(-4.50f, 3.0f, -10.88f);
			pFire->Draw(perspectiveProjectionMatrix, modelMatrix, gpCamera->getLookAtMatrix());

			modelMatrix = vmath::mat4::identity();
			modelMatrix *= vmath::translate(3.1f, 3.0f, -10.88f);
			pFire->Draw(perspectiveProjectionMatrix, modelMatrix, gpCamera->getLookAtMatrix());
		}

		gpCamera->rotateOnMouse(bRotateCamera);
		if (bWasBezier && camera_SabhaMandapScene)
		{
			gpCamera->m_bUseBezierCamera = true;
		}
	}
	break;

	case SCENE_RAM_WORSHIP:
	{
		// Use static texture
		bool bWasBezier = gpCamera->m_bUseBezierCamera;
		if (bWasBezier && camera_RamWorship)
		{
			gpCamera->m_bUseBezierCamera = false;
		}

		// ramworshipAnimalFBO->Clear(0.4f, 0.4f, 0.4f, 1.0f);

		// ramworshipAnimalFBO->Bind();
		// {
		// 	glClear(GL_DEPTH_BUFFER_BIT);

		// 	shadowProgram->StartProgram();
		// 	{
		// 		vmath::mat4 lightViewMat = vmath::lookat(
		// 			vmath::vec3(ramworshipAnimalShadow.lightX, ramworshipAnimalShadow.lightY, ramworshipAnimalShadow.lightZ),
		// 			vmath::vec3(0.0f, 0.0f, -10.0f),
		// 			vmath::vec3(0.0f, 1.0f, 0.0f));

		// 		modelMatrix = vmath::mat4::identity();
		// 		modelMatrix *= vmath::translate(ramworshipAnimalShadow.shadowX, ramworshipAnimalShadow.shadowY, ramworshipAnimalShadow.shadowZ);

		// 		shadowProgram->SetUniforms(perspectiveProjectionMatrix, lightViewMat, modelMatrix);

		// 		renderModel(gpModelsOnLastTerrain[1]);
		// 	}
		// 	shadowProgram->StopProgram();
		// }
		// ramworshipAnimalFBO->Unbind();

		// vmath::mat4 animalsLightMatrix = vmath::lookat(vmath::vec3(ramworshipAnimalShadow.lightX, ramworshipAnimalShadow.lightY, ramworshipAnimalShadow.lightZ),
		// 											   vmath::vec3(0.0f, 0.0f, -10.0f),
		// 											   vmath::vec3(0.0f, 1.0f, 0.0f));

		// vmath::mat4 animalplvmMatrix = perspectiveProjectionMatrix * animalsLightMatrix * modelMatrix;

		// -------------------------------------------------------------------------
		// render into water reflection framebuffer
		// -------------------------------------------------------------------------
		bindFramebuffer(waterReflectionFramebuffer, screenWidth, screenHeight);
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// take camera below the water
			float distanceToWater = 2.0f * gpCamera->m_position[1] - waterParams[1].translation[1];
			gpCamera->m_position[1] = gpCamera->m_position[1] - distanceToWater;

			gpCamera->invertPitch();
			gpCamera->update();

			vmath::vec4 clippingPlane = vmath::vec4(0.0f, 1.0f, 0.0f, -waterParams[1].translation[1]);

			renderSkybox(gpCamera, perspectiveProjectionMatrix, clippingPlane);

			// Render terrain with clipping plane for reflection
			// pHeightmapTerrain->render(gpCamera, perspectiveProjectionMatrix);
			// ramworshipAnimalFBO->BindDepthTexture(5);
			// pHeightmapTerrain->render(gpCamera, perspectiveProjectionMatrix,
			// 						  animalplvmMatrix, 5, ramworshipAnimalShadow.shadowPower);

			gpCamera->m_position[1] = gpCamera->m_position[1] + distanceToWater;

			gpCamera->invertPitch();
			gpCamera->update();
		}
		unbindFramebuffer();

		// -------------------------------------------------------------------------
		// render into water refraction framebuffer
		// -------------------------------------------------------------------------
		bindFramebuffer(waterRefractionFramebuffer, screenWidth, screenHeight);
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			vmath::vec4 clippingPlane = vmath::vec4(0.0f, -1.0f, 0.0f, +waterParams[1].translation[1]);

			renderSkybox(gpCamera, perspectiveProjectionMatrix, clippingPlane);

			// Render terrain with clipping plane for refraction
			// pHeightmapTerrain->render(gpCamera, perspectiveProjectionMatrix);

			// ramworshipAnimalFBO->BindDepthTexture(5);
			// pHeightmapTerrain->render(gpCamera, perspectiveProjectionMatrix,
			// 						  animalplvmMatrix, 5, ramworshipAnimalShadow.shadowPower);
		}
		unbindFramebuffer();

		// -------------------------------------------------------------------------
		// render into default framebuffer
		// -------------------------------------------------------------------------
		glViewport(0, 0, g_iWinWidth, g_iWinHeight);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render skybox first
		vmath::vec4 clippingPlane = vmath::vec4(0.0f, 0.0f, 0.0f, 0.0f);
		renderSkybox(gpCamera, perspectiveProjectionMatrix, clippingPlane);
		renderGodRays(godRaysParamsForRamWorship, gpCamera, perspectiveProjectionMatrix, 0);

		gpCamera->rotateOnMouse(bRotateCamera);

		pHeightmapTerrain->render(gpCamera, perspectiveProjectionMatrix);
		//  ramworshipAnimalFBO->BindDepthTexture(5);
		//  pHeightmapTerrain->render(gpCamera, perspectiveProjectionMatrix,
		//  						  animalplvmMatrix, 5, ramworshipAnimalShadow.shadowPower);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		renderRamWorshipModels(clippingPlane, gpModelsOnLastTerrain);
		renderWater(waterParams[1], gpCamera, perspectiveProjectionMatrix);
		glDisable(GL_BLEND);

		renderUsingLitProgram(gpCamera, clippingPlane, gpModelsOnLastTerrain[3], modelMatrix, &generalHanumanJiLights);

		if (pBoidSimulation && boidParamsFlock.bEnable)
		{
			boidParamsFlock.type = BOID_FLOCK;
			pBoidSimulation->Render(perspectiveProjectionMatrix, gpCamera->getLookAtMatrix(), boidParamsFlock);
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		mat4 viewMatrix = gpCamera->getLookAtMatrix();
		renderWaterfall(waterfallParams, viewMatrix, perspectiveProjectionMatrix);

		glDisable(GL_BLEND);

		// gRamWorshipSceneFogParams Starts here---------------
		static GLuint localDepthTex = 0;
		if (localDepthTex == 0)
		{
			glGenTextures(1, &localDepthTex);
			glBindTexture(GL_TEXTURE_2D, localDepthTex);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}

		glBindTexture(GL_TEXTURE_2D, localDepthTex);
		glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, 0, 0, g_iWinWidth, g_iWinHeight, 0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glDisable(GL_DEPTH_TEST);
		glDepthMask(GL_FALSE);

		drawFogVolumeLayer(gRamWorshipSceneFogParams, localDepthTex, perspectiveProjectionMatrix);

		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);

		// gRamWorshipSceneFogParams Ends here---------------

		if (bWasBezier && camera_RamWorship)
		{
			gpCamera->m_bUseBezierCamera = true;
		}
	}
	break;

	case SCENE_END_CREDITS:
	{

		// Use static texture
		// RenderTexturedBasedScene(creditsTexture[creditsTextureNum].id, alpha);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, g_iWinWidth, g_iWinHeight);
		glDisable(GL_DEPTH_TEST);
		glDepthMask(GL_FALSE);
		glDisable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(
			GL_SRC_ALPHA,
			GL_ONE_MINUS_SRC_ALPHA);
		glClear(GL_COLOR_BUFFER_BIT);

		float sceneElapsed = ELAPSED_TIME - START_TIME_END_CREDITS;
		displayEndCredits();
	}
	}
}

void update(void)
{
	// code
	static float lastBoidUpdate = 0.0f;
	float currentBoidTime = ELAPSED_TIME;
	float boidDt = currentBoidTime - lastBoidUpdate;
	lastBoidUpdate = currentBoidTime;

#if PREVIEW_SCENE == 0
	// Animation code

	if (!gTransition.isTransitioning)
	{
		if (ELAPSED_TIME >= START_TIME_AMC_BANNER && ELAPSED_TIME < START_TIME_TITLES)
		{
			selected_scene = SCENE_AMC_BANNER;
		}
		else if (ELAPSED_TIME >= START_TIME_TITLES && ELAPSED_TIME < START_TIME_MOUNTAIN_CAVE_EXTERIOR)
		{
			creditsTextureNum = 0;
			selected_scene = SCENE_TITLES;
		}
		else if (ELAPSED_TIME >= START_TIME_MOUNTAIN_CAVE_EXTERIOR && ELAPSED_TIME < START_TIME_CAVE_INTERIOR)
		{
			creditsTextureNum = 0;
			selected_scene = SCENE_MOUNTAIN_CAVE_EXTERIOR;
		}
		else if (ELAPSED_TIME >= START_TIME_CAVE_INTERIOR && ELAPSED_TIME < START_TIME_MOUNTAIN_PEAK)
		{
			creditsTextureNum = 0;

			FREE_MODEL(gpTerrainWithCave);
			FREE_MODEL(gpTreesOnFirstTerrain);

			selected_scene = SCENE_CAVE_INTERIOR;
		}
		else if (ELAPSED_TIME >= START_TIME_MOUNTAIN_PEAK && ELAPSED_TIME < START_TIME_FLYING)
		{
			creditsTextureNum = 0;

			// Free Cave Interior models as the scene is complete
			for (int i = 0; i < CAVE_INTERIOR_MODELS_SIZE; i++)
			{
				FREE_MODEL(gpCaveInteriorModels[i]);
			}

			selected_scene = SCENE_MOUNTAIN_PEAK;
		}
		else if (ELAPSED_TIME >= START_TIME_FLYING && ELAPSED_TIME < START_TIME_OCEAN)
		{
			creditsTextureNum = 0;

			// Free Mountain Peak models as we transition to Flying scene
			FREE_MODEL(gpMountain);
			FREE_MODEL(gpHanumanOnMountain);

			selected_scene = SCENE_FLYING;
		}
		else if (ELAPSED_TIME >= START_TIME_OCEAN && ELAPSED_TIME < START_TIME_RAM_VACHAN)
		{
			creditsTextureNum = 0;
			selected_scene = SCENE_OCEAN;
		}
		else if (ELAPSED_TIME >= START_TIME_RAM_VACHAN && ELAPSED_TIME < START_TIME_YUDDHA_SCENE1)
		{
			creditsTextureNum = 0;
			// Free Flying Hanuman model
			FREE_MODEL(gpHanumanJi_FlyingModel);
			selected_scene = SCENE_RAM_VACHAN;
		}
		else if (ELAPSED_TIME >= START_TIME_YUDDHA_SCENE1 && ELAPSED_TIME < START_TIME_YUDDHA_SCENE2)
		{
			creditsTextureNum = 0;

			FREE_MODEL(gpRamVachan_TerrainModel);
			FREE_MODEL(gpRamVachan_RamWithHanuman);
			FREE_MODEL(gpRamVachan_Trees);

			selected_scene = SCENE_YUDDHA_SCENE1;
		}
		else if (ELAPSED_TIME >= START_TIME_YUDDHA_SCENE2 && ELAPSED_TIME < START_TIME_SABHA_MANDAP)
		{
			creditsTextureNum = 0;

			// Free Yuddha Scene 1 models
			FREE_MODEL(gpYuddhaScene1Platform);
			FREE_MODEL(gpHanumanJiInYuddha_one);

			selected_scene = SCENE_YUDDHA_SCENE2;
		}
		else if (ELAPSED_TIME >= START_TIME_SABHA_MANDAP && ELAPSED_TIME < START_TIME_END_CREDITS)
		{
			creditsTextureNum = 0;

			// Free Yuddha Scene 2 models
			for (int i = 0; i < YUDDHA_SCENE2_MODELS_SIZE; i++)
			{
				FREE_MODEL(gpYudhaScene2Models[i]);
			}

			selected_scene = SCENE_SABHA_MANDAP;
		}
		else if (ELAPSED_TIME >= START_TIME_END_CREDITS && ELAPSED_TIME < START_TIME_RAM_WORSHIP)
		{
			creditsTextureNum = 0;

			FREE_MODEL(gpSabhaMandapModel);
			FREE_MODEL(gpFirePotModel);
			FREE_MODEL(gpPillarModel);
			FREE_MODEL(gpMinisterChairModel);
			FREE_MODEL(gpThroneModel);
			FREE_MODEL(gpHanumanJiModel);
			FREE_MODEL(gpVibhishanModel);

			selected_scene = SCENE_END_CREDITS;
		}
		else if (ELAPSED_TIME >= START_TIME_RAM_WORSHIP)
		{
			creditsTextureNum = 0;

			// // Free final scene models
			// FREE_MODEL(gpModelsOnLastTerrain[0]);
			// FREE_MODEL(gpModelsOnLastTerrain[1]);
			// FREE_MODEL(gpModelsOnLastTerrain[2]);
			// FREE_MODEL(gpModelsOnLastTerrain[3]);

			selected_scene = SCENE_RAM_WORSHIP;
		}
		else
		{
			// ---------------------------------------------------------------
			// CRITICAL FIX: during a transition the timeline guard keeps
			// selected_scene = fromScene.  But the toScene camera MUST run
			// every frame so scene B is already moving when it fades in.
			//
			// We call the toScene's camera/update logic directly here,
			// completely bypassing the switch(selected_scene) which would
			// only run fromScene.
			// ---------------------------------------------------------------
			switch (gTransition.toSceneID)
			{
			case SCENE_MOUNTAIN_CAVE_EXTERIOR:
			{
				// Snow update
				GLfloat dt = ELAPSED_TIME - snowLastTime;
				snowLastTime = ELAPSED_TIME;
				updateSnowfall(snowfallParams, dt);

				// Camera update — effectiveStart = transition trigger time
				// so t>0 immediately when the transition fires
				if (gpCamera->m_bUseBezierCamera && camera_SnowTerrain)
				{
					float effectiveStart = START_TIME_MOUNTAIN_CAVE_EXTERIOR - 3.0f; // must match T1 duration
					float t = (ELAPSED_TIME - effectiveStart) / (START_TIME_CAVE_INTERIOR - effectiveStart);
					t = (t < 0.0f) ? 0.0f : (t > 1.0f) ? 1.0f
													   : t;

					camera_SnowTerrain->update(t);
					gpCamera->m_position = camera_SnowTerrain->getPosition();
					gpCamera->m_yaw = camera_SnowTerrain->getYaw();
					gpCamera->m_pitch = camera_SnowTerrain->getPitch();
					gpCamera->m_roll = camera_SnowTerrain->getRoll();
					gpCamera->update();
				}
				// if (gRamWorshipSceneFogParams.bEnable && gRamWorshipSceneFogParams.fogDensity > 0.0f)
				// {
				// 	// Tweak this factor: Higher value = clears instantly, Lower value = clears slower
				// 	float blizzardClearingSpeed = 0.000005f;

				// 	// Incrementally dissolve fog density based on elapsed frametime
				// 	gRamWorshipSceneFogParams.fogDensity -= blizzardClearingSpeed * ELAPSED_TIME;

				// 	// Hard clamp cleanup
				// 	if (gRamWorshipSceneFogParams.fogDensity <= 0.0f)
				// 	{

				// 		// gRamWorshipSceneFogParams.fogDensity = 1.0f;
				// 		gRamWorshipSceneFogParams.bEnable = FALSE; // Stops drawing entirely when sky turns clean
				// 	}
				// }
				break;
			}
			case SCENE_MOUNTAIN_PEAK:
			{
				if (gpCamera->m_bUseBezierCamera && camera_MountainPeakScene)
				{
					float effectiveStart = START_TIME_MOUNTAIN_PEAK - 2.0f; // match T3 duration
					float t = (ELAPSED_TIME - effectiveStart) / (START_TIME_FLYING - effectiveStart);
					t = (t < 0.0f) ? 0.0f : (t > 1.0f) ? 1.0f
													   : t;

					camera_MountainPeakScene->update(t);
					gpCamera->m_position = camera_MountainPeakScene->getPosition();
					gpCamera->m_yaw = camera_MountainPeakScene->getYaw();
					gpCamera->m_pitch = camera_MountainPeakScene->getPitch();
					gpCamera->m_roll = camera_MountainPeakScene->getRoll();
					gpCamera->update();
				}
				break;
			}
			case SCENE_FLYING:
			{
				if (gpCamera->m_bUseBezierCamera && camera_FlyingScene)
				{
					float effectiveStart = START_TIME_FLYING - 2.0f; // match T4 duration
					float t = (ELAPSED_TIME - effectiveStart) / (START_TIME_OCEAN - effectiveStart);
					t = (t < 0.0f) ? 0.0f : (t > 1.0f) ? 1.0f
													   : t;

					camera_FlyingScene->update(t);
					gpCamera->m_position = camera_FlyingScene->getPosition();
					gpCamera->m_yaw = camera_FlyingScene->getYaw();
					gpCamera->m_pitch = camera_FlyingScene->getPitch();
					gpCamera->m_roll = camera_FlyingScene->getRoll();
					gpCamera->update();
				}
				break;
			}
			case SCENE_YUDDHA_SCENE1:
			{
				if (gpCamera->m_bUseBezierCamera && camera_YuddhaScene1)
				{
					float t = (ELAPSED_TIME - START_TIME_YUDDHA_SCENE1) / (START_TIME_YUDDHA_SCENE2 - START_TIME_YUDDHA_SCENE1);
					t = (t < 0.0f) ? 0.0f : (t > 1.0f) ? 1.0f
													   : t;

					camera_YuddhaScene1->update(t);
					gpCamera->m_position = camera_YuddhaScene1->getPosition();
					gpCamera->m_yaw = camera_YuddhaScene1->getYaw();
					gpCamera->m_pitch = camera_YuddhaScene1->getPitch();
					gpCamera->m_roll = camera_YuddhaScene1->getRoll();
					gpCamera->update();
				}
				break;
			}
			case SCENE_RAM_WORSHIP:
			{
				if (gpCamera->m_bUseBezierCamera && camera_RamWorship)
				{
					float effectiveStart = START_TIME_RAM_WORSHIP - 2.0f; // match transition duration
					float t = (ELAPSED_TIME - effectiveStart) / (START_TIME_END_CREDITS - effectiveStart);
					t = (t < 0.0f) ? 0.0f : (t > 1.0f) ? 1.0f
													   : t;

					camera_RamWorship->update(t);
					gpCamera->m_position = camera_RamWorship->getPosition();
					gpCamera->m_yaw = camera_RamWorship->getYaw();
					gpCamera->m_pitch = camera_RamWorship->getPitch();
					gpCamera->m_roll = camera_RamWorship->getRoll();
					gpCamera->update();
				}
				break;
			}
			// Add a case here for every scene that has a bezier camera
			default:
				break;
			}
		}
	}
#endif

	switch (selected_scene)
	{
	case SCENE_AMC_BANNER:
		VideoPlayerUpdateTexture(gAMCBannerVideo, ELAPSED_TIME);
		break;

	case SCENE_TITLES:
	{
		float titlesEnd = START_TIME_MOUNTAIN_CAVE_EXTERIOR; // next scene start
		float fadeOutStart = titlesEnd - 2.0f;

		if (ELAPSED_TIME < fadeOutStart)
		{
			// Fade in
			if (alpha < 1.0f)
				alpha += 0.002f;
		}
		else
		{
			// Fade out
			float fadeOutT = (ELAPSED_TIME - fadeOutStart) / 2.0f;
			alpha = 1.0f - fadeOutT;
			if (alpha < 0.0f)
				alpha = 0.0f;
		}

		if (bAMCVideoUninitialized == FALSE)
		{
			VideoPlayerUninit(gAMCBannerVideo);
			bAMCVideoUninitialized = TRUE;
		}
		break;
	}

	case SCENE_MOUNTAIN_CAVE_EXTERIOR:
	{
		GLfloat dt = ELAPSED_TIME - snowLastTime;
		snowLastTime = ELAPSED_TIME;
		updateSnowfall(snowfallParams, dt);

		gpCamera->rotateOnMouse(bRotateCamera);

		if (gpCamera->m_bUseBezierCamera && camera_SnowTerrain)
		{
			float effectiveStart = START_TIME_MOUNTAIN_CAVE_EXTERIOR - 2.0f;
			float t = (ELAPSED_TIME - effectiveStart) / (START_TIME_CAVE_INTERIOR - effectiveStart);
			t = (t < 0.0f) ? 0.0f : (t > 1.0f) ? 1.0f
											   : t;

			camera_SnowTerrain->update(t);
			gpCamera->m_position = camera_SnowTerrain->getPosition();
			gpCamera->m_yaw = camera_SnowTerrain->getYaw();
			gpCamera->m_pitch = camera_SnowTerrain->getPitch();
			gpCamera->m_roll = camera_SnowTerrain->getRoll();
			gpCamera->update();
		}
		break;
	}

	case SCENE_CAVE_INTERIOR:
	{
		gpCamera->rotateOnMouse(bRotateCamera);

		if (gpCamera->m_bUseBezierCamera && camera_CaveInterior)
		{
			float t = (ELAPSED_TIME - START_TIME_CAVE_INTERIOR) /
					  (START_TIME_MOUNTAIN_PEAK - START_TIME_CAVE_INTERIOR);
			t = (t < 0.0f) ? 0.0f : (t > 1.0f) ? 1.0f
											   : t;

			camera_CaveInterior->update(t);

			gpCamera->m_position = camera_CaveInterior->getPosition();
			gpCamera->m_yaw = camera_CaveInterior->getYaw();
			gpCamera->m_pitch = camera_CaveInterior->getPitch();
			gpCamera->m_roll = camera_CaveInterior->getRoll();
			gpCamera->update();
		}
		else if (gpCamera->m_bUseBezierCamera)
		{
			if ((timer + 3) + 4 < BezierPoints.size())
			{
				timer = timer + 3;
			}
		}

		// Texture alpha
		if (alpha <= 1.0f)
		{
			alpha += 0.002f;
		}
		break;
	}

	case SCENE_MOUNTAIN_PEAK:
	{

		// camera_MountainPeakScene->setBSplinePoints(positionsMountainPeakScene);

		// verts.clear();
		// for (float t = 0.0f; t <= 1.0f; t += 0.01f)
		// {
		// 	vmath::vec3 p = camera_MountainPeakScene->getSplinePoint(t);
		// 	verts.push_back(p[0]);
		// 	verts.push_back(p[1]);
		// 	verts.push_back(p[2]);
		// }

		if (gpCamera->m_bUseBezierCamera && camera_MountainPeakScene)
		{
			float effectiveStart = START_TIME_MOUNTAIN_PEAK - 2.0f; // match T3 duration
			float t = (ELAPSED_TIME - effectiveStart) / ((START_TIME_FLYING - 2.0f) - effectiveStart);
			t = (t < 0.0f) ? 0.0f : (t > 1.0f) ? 1.0f
											   : t;

			camera_MountainPeakScene->update(t);
			gpCamera->m_position = camera_MountainPeakScene->getPosition();
			gpCamera->m_yaw = camera_MountainPeakScene->getYaw();
			gpCamera->m_pitch = camera_MountainPeakScene->getPitch();
			gpCamera->m_roll = camera_MountainPeakScene->getRoll();
			gpCamera->update();
		}

		break;
	}

	case SCENE_FLYING:
	{
		if (gpCamera->m_bUseBezierCamera && camera_FlyingScene)
		{
			float t = (ELAPSED_TIME - START_TIME_FLYING) / (START_TIME_OCEAN - START_TIME_FLYING);
			t = (t < 0.0f) ? 0.0f : (t > 1.0f) ? 1.0f
											   : t;

			camera_FlyingScene->update(t);
			gpCamera->m_position = camera_FlyingScene->getPosition();
			gpCamera->m_yaw = camera_FlyingScene->getYaw();
			gpCamera->m_pitch = camera_FlyingScene->getPitch();
			gpCamera->m_roll = camera_FlyingScene->getRoll();
			gpCamera->update();
		}
		else if (gpCamera->m_bUseBezierCamera)
		{
			if ((timer + 3) + 4 < BezierPoints.size())
			{
				timer = timer + 3;
			}
		}
		break;
	}

	case SCENE_OCEAN:
	{
		gpCamera->rotateOnMouse(bRotateCamera);

		if (gpCamera->m_bUseBezierCamera && camera_Ocean)
		{
			float t = (ELAPSED_TIME - START_TIME_OCEAN) /
					  (START_TIME_RAM_VACHAN - START_TIME_OCEAN);
			t = (t < 0.0f) ? 0.0f : (t > 1.0f) ? 1.0f
											   : t;

			camera_Ocean->update(t);

			gpCamera->m_position = camera_Ocean->getPosition();
			gpCamera->m_yaw = camera_Ocean->getYaw();
			gpCamera->m_pitch = camera_Ocean->getPitch();
			gpCamera->m_roll = camera_Ocean->getRoll();
			gpCamera->update();
		}
		else if (gpCamera->m_bUseBezierCamera)
		{
			if ((timer + 3) + 4 < BezierPoints.size())
			{
				timer = timer + 3;
			}
		}

		break;
	}

	case SCENE_RAM_VACHAN:
	{
		gpCamera->rotateOnMouse(bRotateCamera);

		if (gpCamera->m_bUseBezierCamera && camera_RamVachanScene)
		{
			float t = (ELAPSED_TIME - START_TIME_RAM_VACHAN) /
					  (START_TIME_YUDDHA_SCENE1 - START_TIME_RAM_VACHAN);
			t = (t < 0.0f) ? 0.0f : (t > 1.0f) ? 1.0f
											   : t;

			camera_RamVachanScene->update(t);

			gpCamera->m_position = camera_RamVachanScene->getPosition();
			gpCamera->m_yaw = camera_RamVachanScene->getYaw();
			gpCamera->m_pitch = camera_RamVachanScene->getPitch();
			gpCamera->m_roll = camera_RamVachanScene->getRoll();
			gpCamera->update();
		}
		else if (gpCamera->m_bUseBezierCamera)
		{
			if ((timer + 3) + 4 < BezierPoints.size())
			{
				timer = timer + 3;
			}
		}

		break;
	}

	case SCENE_YUDDHA_SCENE1:
	{

		// camera_YuddhaScene1->setBSplinePoints(positionsYuddhaScene1);

		// verts.clear();
		// for (float t = 0.0f; t <= 1.0f; t += 0.01f)
		// {
		// 	vmath::vec3 p = camera_YuddhaScene1->getSplinePoint(t);
		// 	verts.push_back(p[0]);
		// 	verts.push_back(p[1]);
		// 	verts.push_back(p[2]);
		// }

		// Render without dissolve effect - madam's change translate from top
		float animationStartTime = START_TIME_YUDDHA_SCENE2 - 2.0f;
		float animationEndTime = START_TIME_YUDDHA_SCENE2;
		float t_anim = (ELAPSED_TIME - animationStartTime) / (animationEndTime - animationStartTime);
		t_anim = (t_anim < 0.0f) ? 0.0f : (t_anim > 1.0f) ? 1.0f
														  : t_anim;
		// YFactor = 25.0f * (0.5f - t_anim);

		// ========== DISSOLVE ANIMATION ==========
		const float ANIMATION_DURATION = 19.5f; // 40.5 seconds for full animation
		const float TOTAL_PROGRESS_RANGE = 20.0f;

		float sceneTime = ELAPSED_TIME - START_TIME_YUDDHA_SCENE1;

		// Initialize dissolve immediately when scene starts
		if (!g_dissolveStarted && sceneTime >= 0.0f)
		{
			g_dissolveStarted = TRUE;
			g_dissolveActive = TRUE;
			g_bReverseDissolve = FALSE; // FALSE = appear effect
			g_dissolveProgress = 0.0f;	// Start fully invisible (20)
			g_dissolveLastFrameTime = ELAPSED_TIME;

			fprintf(gpFILE, "\n========== DISSOLVE START ==========\n");
			fprintf(gpFILE, "Scene time: %.2f, Start Progress: %.2f\n", sceneTime, g_dissolveProgress);
			fprintf(gpFILE, "Animation will take %.1f seconds\n", ANIMATION_DURATION);
			fflush(gpFILE);
		}

		gpCamera->rotateOnMouse(bRotateCamera);

		if (gpCamera->m_bUseBezierCamera && camera_YuddhaScene1)
		{
			float effectiveStart = START_TIME_YUDDHA_SCENE1 - 2.0f; // duration of transition T7
			float t = (ELAPSED_TIME - effectiveStart) / (START_TIME_YUDDHA_SCENE2 - effectiveStart);
			t = (t < 0.0f) ? 0.0f : (t > 1.0f) ? 1.0f
											   : t;

			camera_YuddhaScene1->update(t);

			gpCamera->m_position = camera_YuddhaScene1->getPosition();
			gpCamera->m_yaw = camera_YuddhaScene1->getYaw();
			gpCamera->m_pitch = camera_YuddhaScene1->getPitch();
			gpCamera->m_roll = camera_YuddhaScene1->getRoll();
			gpCamera->update();
		}
		else if (gpCamera->m_bUseBezierCamera)
		{
			if ((timer + 3) + 4 < BezierPoints.size())
			{
				timer = timer + 3;
			}
		}

		// Update dissolve animation
		if (g_dissolveActive)
		{
			float currentTime = ELAPSED_TIME;
			float deltaTime = currentTime - g_dissolveLastFrameTime;
			g_dissolveLastFrameTime = currentTime;

			// Limit delta time
			if (deltaTime > 0.033f)
				deltaTime = 0.033f;
			if (deltaTime < 0.0f)
				deltaTime = 0.0f;

			// Calculate progress change per frame
			float progressPerSecond = TOTAL_PROGRESS_RANGE / ANIMATION_DURATION;
			float progressDelta = progressPerSecond * deltaTime;

			// For appear effect: progress decreases from 20 to 0
			g_dissolveProgress += progressDelta;

			// Log progress at intervals
			static float lastLoggedProgress = -1.0f;
			if (fabs(g_dissolveProgress - lastLoggedProgress) >= 2.0f)
			{
				fprintf(gpFILE, "Dissolve Progress: %.2f at scene time: %.2f\n",
						g_dissolveProgress, sceneTime);
				fflush(gpFILE);
				lastLoggedProgress = g_dissolveProgress;
			}

			// Check if animation is complete
			if (g_dissolveProgress >= TOTAL_PROGRESS_RANGE)
			{
				g_dissolveProgress = TOTAL_PROGRESS_RANGE;
				g_dissolveActive = FALSE;
				fprintf(gpFILE, "Dissolve animation completed at scene time: %.2f\n", sceneTime);
				fflush(gpFILE);
			}

			g_dissolveTime = sceneTime;
		}

		break;
	}

	case SCENE_YUDDHA_SCENE2:
	{
		if (gpCamera->m_bUseBezierCamera && camera_YuddhaScene2)
		{
			float effectiveStart = START_TIME_YUDDHA_SCENE2 - 2.0f;
			float t = (ELAPSED_TIME - effectiveStart) /
					  (START_TIME_SABHA_MANDAP - effectiveStart);
			t = (t < 0.0f) ? 0.0f : (t > 1.0f) ? 1.0f
											   : t;

			camera_YuddhaScene2->update(t);

			gpCamera->m_position = camera_YuddhaScene2->getPosition();
			gpCamera->m_yaw = camera_YuddhaScene2->getYaw();
			gpCamera->m_pitch = camera_YuddhaScene2->getPitch();
			gpCamera->m_roll = camera_YuddhaScene2->getRoll();
			gpCamera->update();
		}
		else if (gpCamera->m_bUseBezierCamera)
		{
			if ((timer + 3) + 4 < BezierPoints.size())
			{
				timer = timer + 3;
			}
		}
		break;
	}

	case SCENE_SABHA_MANDAP:
	{
		if (gpCamera->m_bUseBezierCamera && camera_SabhaMandapScene)
		{
			float effectiveStart = START_TIME_SABHA_MANDAP - 2.0f; // match transition duration
			float t = (ELAPSED_TIME - effectiveStart) /
					  (START_TIME_END_CREDITS - effectiveStart);
			t = (t < 0.0f) ? 0.0f : (t > 1.0f) ? 1.0f
											   : t;

			camera_SabhaMandapScene->update(t);

			gpCamera->m_position = camera_SabhaMandapScene->getPosition();
			gpCamera->m_yaw = camera_SabhaMandapScene->getYaw();
			gpCamera->m_pitch = camera_SabhaMandapScene->getPitch();
			gpCamera->m_roll = camera_SabhaMandapScene->getRoll();
			gpCamera->update();
		}
		else if (gpCamera->m_bUseBezierCamera)
		{
			if ((timer + 3) + 4 < BezierPoints.size())
			{
				timer = timer + 3;
			}
		}

		break;
	}

	case SCENE_RAM_WORSHIP:
	{
		if (gpCamera->m_bUseBezierCamera && camera_RamWorship)
		{
			float effectiveStart = START_TIME_RAM_WORSHIP - 2.0f;
			float t = (ELAPSED_TIME - effectiveStart) /
					  (END_TIME_TOTAL - effectiveStart);
			t = (t < 0.0f) ? 0.0f : (t > 1.0f) ? 1.0f
											   : t;

			camera_RamWorship->update(t);

			gpCamera->m_position = camera_RamWorship->getPosition();
			gpCamera->m_yaw = camera_RamWorship->getYaw();
			gpCamera->m_pitch = camera_RamWorship->getPitch();
			gpCamera->m_roll = camera_RamWorship->getRoll();
			gpCamera->update();
		}
		else if (gpCamera->m_bUseBezierCamera)
		{
			if ((timer + 3) + 4 < BezierPoints.size())
			{
				timer = timer + 3;
			}
		}

		// Texture alpha
		if (alpha <= 1.0f)
		{
			alpha += 0.002f;
		}
		break;
	}

	case SCENE_END_CREDITS:
	{
		// Texture alpha
		if (alpha <= 1.0f)
		{
			alpha += 0.002f;
		}

		break;
	}
	} // end switch(selected_scene)

	// Position birds exactly in front of the camera at a static -10 Z distance
	if (gpCamera)
	{
		vmath::vec3 camPos = gpCamera->m_position;
		float yawRad = gpCamera->m_yaw * (3.14159265f / 180.0f);
		float pitchRad = gpCamera->m_pitch * (3.14159265f / 180.0f);

		vmath::vec3 front = vmath::vec3(
			cosf(pitchRad) * cosf(yawRad),
			sinf(pitchRad),
			cosf(pitchRad) * sinf(yawRad));
		vmath::vec3 boidPos = camPos + vmath::normalize(front) * 10.0f;

		boidParamsVshape.position = boidPos;
		boidParamsFlock.position = boidPos;
	}

	if (pBoidSimulation)
	{
		// Update is uncommented to allow wing flapping and matrix population
		pBoidSimulation->Update(boidDt, boidParamsVshape);
		pBoidSimulation->Update(boidDt, boidParamsFlock);
	}
}

void uninitialize(void)
{
	// function declarations
	void ToggleFullScreen(void);

	// code

	if (pHeightmapTerrain)
	{
		free(pHeightmapTerrain);
		pHeightmapTerrain = NULL;
	}

	if (sceneTimer)
	{
		sdkStopTimer(&sceneTimer);
		sdkDeleteTimer(&sceneTimer);
		sceneTimer = NULL;
	}

	uninitializeImGui();

	// free model // scene change nntr models free kele ahet for OPTIMIZED performance
	// FREE_MODEL(gpSabhaMandapModel);
	// FREE_MODEL(gpSabhaMandapInteriorModel);
	// FREE_MODEL(gpThroneModel);
	// FREE_MODEL(gpHanumanJiModel);
	// FREE_MODEL(gpVibhishanModel);
	// FREE_MODEL(gpRamVachan_TerrainModel);
	// FREE_MODEL(gpRamVachan_RamWithHanuman);
	// FREE_MODEL(gpTerrainWithCave);
	// FREE_MODEL(gpTreesOnFirstTerrain);
	// FREE_MODEL(gpCaveInterriorWithHanumanJi);

	// if (volumetriccloudsForPeakScene)
	// {
	// 	volumetriccloudsForPeakScene->Uninitialize();
	// 	delete (volumetriccloudsForPeakScene);
	// 	volumetriccloudsForPeakScene = nullptr;
	// }

	uninitializeSkydome();
	uninitializeGodRays();
	uninitializeSnowfall();
	uninitializeSceneLighting();
	uninitializeTransitions();
	uninitializeWaterfall();
	UninitializeTitle();
	uninitializeLightningWithFlash();
	uninitializeFogSystem();
	uninitializeBloom();

	if (pBoidSimulation)
	{
		pBoidSimulation->Uninitialize();
		delete pBoidSimulation;
		pBoidSimulation = NULL;
	}

// Audio uninitialize
#if PREVIEW_SCENE == 0
	CleanupAudio();
#endif

	// for shader program object
	if (shaderProgramObject)
	{
		// step 1 : use shader Program object
		glUseProgram(shaderProgramObject);

		// step 2 : get number of attached shader
		GLint numShader = 0;

		glGetProgramiv(shaderProgramObject, GL_ATTACHED_SHADERS, &numShader);

		if (numShader > 0)
		{
			std::vector<GLuint> shaders(numShader);
			glGetAttachedShaders(shaderProgramObject, numShader, NULL, shaders.data());
			for (GLuint s : shaders)
			{
				glDetachShader(shaderProgramObject, s);
				glDeleteShader(s);
			}
		}

		glUseProgram(0);

		glDeleteProgram(shaderProgramObject);

		shaderProgramObject = 0;
	}

	// Delete camera object
	if (gpCamera)
	{
		delete gpCamera;
		gpCamera = NULL;
	}

	if (rotatingCamera)
	{
		delete rotatingCamera;
		rotatingCamera = NULL;
	}

	if (camera_CaveInterior)
	{
		delete camera_CaveInterior;
		camera_CaveInterior = NULL;
	}

	if (camera_MountainPeakScene)
	{
		delete camera_MountainPeakScene;
		camera_MountainPeakScene = NULL;
	}

	if (camera_SabhaMandapScene)
	{
		delete camera_SabhaMandapScene;
		camera_SabhaMandapScene = NULL;
	}

	if (camera_SnowTerrain)
	{
		delete camera_SnowTerrain;
		camera_SnowTerrain = NULL;
	}

	if (camera_Ocean)
	{
		delete camera_Ocean;
		camera_Ocean = NULL;
	}

	if (camera_RamVachanScene)
	{
		delete camera_RamVachanScene;
		camera_RamVachanScene = NULL;
	}
	if (camera_FlyingScene)
	{
		delete camera_FlyingScene;
		camera_FlyingScene = NULL;
	}

	if (camera_YuddhaScene1)
	{
		delete camera_YuddhaScene1;
		camera_YuddhaScene1 = NULL;
	}
	if (camera_YuddhaScene2)
	{
		delete camera_YuddhaScene2;
		camera_YuddhaScene2 = NULL;
	}

	if (camera_RamWorship)
	{
		delete camera_RamWorship;
		camera_RamWorship = NULL;
	}

	uninitializeSkybox();
	uninitializeOcean();
	uninitializeWaterLensFlare();
	uninitializeFadeSystem();

	// If Application is exitting in fullscreen mode
	if (gbFullscreen == TRUE)
	{
		ToggleFullScreen();
		gbFullscreen = FALSE;
	}

	// Make ghdc as current context
	if (wglGetCurrentContext() == ghrc)
	{
		wglMakeCurrent(NULL, NULL);
	}

	// Delete Rendering Context
	if (ghrc)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;
	}

	// Release the ghdc
	if (ghdc)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}
	// Destroy Window
	if (ghwnd)
	{
		DestroyWindow(ghwnd);
		ghwnd = NULL;
	}

	if (mountainPeakProgram)
	{
		delete (mountainPeakProgram);
		mountainPeakProgram = nullptr;
	}

	if (sideMountainPeakProgram)
	{
		delete (sideMountainPeakProgram);
		sideMountainPeakProgram = nullptr;
	}

	if (litSabhamandapProgramWithShadow)
	{
		delete (litSabhamandapProgramWithShadow);
		litSabhamandapProgramWithShadow = nullptr;
	}

	if (shadowProgram)
	{
		delete (shadowProgram);
		shadowProgram = nullptr;
	}

	if (ministerChairShadowFBO)
	{
		delete (ministerChairShadowFBO);
		ministerChairShadowFBO = nullptr;
	}

	if (pillarShadowFBO)
	{
		delete (pillarShadowFBO);
		pillarShadowFBO = nullptr;
	}

	if (firePotShadowFBO)
	{
		delete (firePotShadowFBO);
		firePotShadowFBO = nullptr;
	}

	if (hanumanShadowFBO)
	{
		delete (hanumanShadowFBO);
		hanumanShadowFBO = nullptr;
	}

	if (vibhishanShadowFBO)
	{
		delete (vibhishanShadowFBO);
		vibhishanShadowFBO = nullptr;
	}

	if (ramVachanShadowFBO)
	{
		delete (ramVachanShadowFBO);
		ramVachanShadowFBO = nullptr;
	}

	if (ramVachanTreeShadowFBO)
	{
		delete (ramVachanTreeShadowFBO);
		ramVachanTreeShadowFBO = nullptr;
	}

	// Close log file
	if (gpFILE)
	{
		fprintf(gpFILE, "Program Ended Successfully\n");
		fprintf(gpFILE, "\n==============================================================================\n");
		fclose(gpFILE);
		gpFILE = NULL;
	}
}
