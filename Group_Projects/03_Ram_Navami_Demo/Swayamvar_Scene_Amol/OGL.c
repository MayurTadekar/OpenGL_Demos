// Win32 headers
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

// OpenGL related Header Files
#include <gl/GL.h>
#include <gl/GLU.h>

// Custom Header File
#include "OGL.h"
#include "Atharv_Ram_Sita_Vivah.h"

// OpenGL related Libraries
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "GLU32.lib")

// Macros
#define WIN_WIDTH 800
#define WIN_HEIGHT 600


// global function declarations
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

// global variable declarations
// Variable Related With FullScreen
BOOL AAA_gbFullScreen = FALSE;
HWND AAA_ghwnd = NULL;
DWORD AAA_dwStyle;
WINDOWPLACEMENT AAA_wpPrev;

// active window related variable
BOOL AAA_gbActiveWindow = FALSE;

// Exit Key Press Related Variables
BOOL AAA_gbEscapeKeyIsPressed = FALSE;

// variable related to file I/O
char AAA_gszLogFileName[] = "Log.txt";
FILE *AAA_gpFile = NULL;

// OpenGL related Global variables
HDC AAA_ghdc = NULL;
HGLRC AAA_ghrc = NULL;

// Entry Point function 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// function declaration
	int initialize(void);
	void display(void);
	void update(void);
	void uninitialize(void);

	// Variable declarations
	WNDCLASSEX AAA_wndclass;
	HWND AAA_hwnd;
	MSG AAA_msg;
	TCHAR AAA_szAppName[] = TEXT("RTR 6");
	BOOL AAA_bDone = FALSE;

	// code
	// Create Log File
	AAA_gpFile = fopen( AAA_gszLogFileName, "w");
	if (AAA_gpFile == NULL)
	{
		MessageBox(NULL, TEXT("Log File Creation Failed"), TEXT("File I/O Error"), MB_OK);
		exit(0);
	}
	else
	{
		fprintf(AAA_gpFile, "Program Started Successfully...\n");
	}

	// Window Class Initialization
	AAA_wndclass.cbSize = sizeof(WNDCLASSEX);
	AAA_wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	AAA_wndclass.cbClsExtra = 0;
	AAA_wndclass.cbWndExtra = 0;
	AAA_wndclass.lpfnWndProc = WndProc;
	AAA_wndclass.hInstance = hInstance;
	AAA_wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	AAA_wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	AAA_wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	AAA_wndclass.lpszClassName = AAA_szAppName;
	AAA_wndclass.lpszMenuName = NULL;
	AAA_wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	// Registration of Window class
	RegisterClassEx(&AAA_wndclass);

	// Create Window
	AAA_hwnd = CreateWindowEx( 	WS_EX_APPWINDOW,
							AAA_szAppName,
							TEXT("Atharv Anil Ambekar - FFP - Windows OS - 05 Perspective Black & White Triangle"),
							WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
							(GetSystemMetrics(SM_CXSCREEN)/2 - (WIN_WIDTH /2)),
							(GetSystemMetrics(SM_CYSCREEN)/2 - (WIN_HEIGHT /2)),
							WIN_WIDTH,
							WIN_HEIGHT,
							NULL,
							NULL,
							hInstance,
							NULL
						);

	AAA_ghwnd = AAA_hwnd;
	 
	// Show window
	ShowWindow(AAA_hwnd, iCmdShow);

	// Paint background of window
	UpdateWindow(AAA_hwnd);

	// Initialize
	int AAA_result = initialize();
	if (AAA_result != 0)
	{
		fprintf( AAA_gpFile, "Initialize() failed \n");
		DestroyWindow(AAA_hwnd);
		AAA_hwnd = NULL;
	}
	else
	{
		fprintf(AAA_gpFile, "Initialize() Completed Successfully\n");
	}

	// Set this Window as foreground and Active Window
	SetForegroundWindow(AAA_hwnd);
	SetFocus(AAA_hwnd);

	// Game Loop
	while (AAA_bDone == FALSE)
	{
		if (PeekMessage(&AAA_msg, NULL, 0, 0, PM_REMOVE))
		{
			if (AAA_msg.message == WM_QUIT)
			{
				AAA_bDone = TRUE;
			}
			else
			{
				TranslateMessage(&AAA_msg);
				DispatchMessage(&AAA_msg);
			}
		}
		else
		{
			if (AAA_gbActiveWindow == TRUE)
			{	
				if (AAA_gbEscapeKeyIsPressed == TRUE)
				{
					AAA_bDone = TRUE;
				}

				// Render
				display();

				// Update
				update();
			}
		}
	}

	// Uninitialize
	uninitialize();

	return((int)AAA_msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// local function declarations
	void toggleFullScreen(void);
	void resize(int, int);

	// code
	switch (iMsg)
	{
	case WM_CREATE :
		ZeroMemory((void*)&AAA_wpPrev, sizeof(WINDOWPLACEMENT));
		AAA_wpPrev.length = sizeof(WINDOWPLACEMENT);
		break;
	
	case WM_SETFOCUS :
		AAA_gbActiveWindow = TRUE;
		break;

	case WM_KILLFOCUS :
		AAA_gbActiveWindow = FALSE;
		break;

	case WM_KEYDOWN :
		switch (wParam)
		{
		case VK_ESCAPE:
			AAA_gbEscapeKeyIsPressed = TRUE;
			break;

		default:
			break;
		}

		break;
	
	case WM_ERASEBKGND :

		return(0);

	case WM_SIZE :
		resize(LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_CHAR :
		switch (wParam)
		{
		case 'F' :
		case 'f' :
			if (AAA_gbFullScreen == FALSE)
			{
				toggleFullScreen();
				AAA_gbFullScreen = TRUE;
			}
			else 
			{
				toggleFullScreen();
				AAA_gbFullScreen = FALSE;
			}	
			break;

		default :
			break;
		}

		break;	
	
	case WM_CLOSE :
		uninitialize();
		break;
	case WM_DESTROY : 
		PostQuitMessage(0);
		break;

	default:
		break;
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void toggleFullScreen(void)
{
	// variable declarations
	MONITORINFO mi;

	// code
	if (AAA_gbFullScreen == FALSE)
	{
		AAA_dwStyle = GetWindowLong( AAA_ghwnd, GWL_STYLE);
		if (AAA_dwStyle & WS_OVERLAPPEDWINDOW)
		{
			ZeroMemory((void *)&mi, sizeof(MONITORINFO));
			mi.cbSize = sizeof(MONITORINFO);

			if (GetWindowPlacement(AAA_ghwnd, &AAA_wpPrev) && (GetMonitorInfo(MonitorFromWindow(AAA_ghwnd, MONITORINFOF_PRIMARY), &mi)))
			{
				SetWindowLong(AAA_ghwnd, GWL_STYLE, AAA_dwStyle & ~WS_OVERLAPPEDWINDOW);
				SetWindowPos(	AAA_ghwnd, 
								HWND_TOP, 
								mi.rcMonitor.left, 
								mi.rcMonitor.top, 
								(mi.rcMonitor.right - mi.rcMonitor.left),
								(mi.rcMonitor.bottom - mi.rcMonitor.top),
								SWP_NOZORDER | SWP_FRAMECHANGED
							);
			}
		}
		
		ShowCursor(FALSE);
	}
	else
	{
		SetWindowPlacement(AAA_ghwnd, &AAA_wpPrev);
		SetWindowLong(AAA_ghwnd, GWL_STYLE, AAA_dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(	AAA_ghwnd,
						HWND_TOP,
						0,
						0, 
						0, 
						0,
						SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_FRAMECHANGED);

		ShowCursor(TRUE);
	}
}

int initialize(void)
{
	// function declaraions
	void printGLInfo(void);
	void resize(int, int);

	// variable declarations
	PIXELFORMATDESCRIPTOR AAA_pfd;
	int AAA_iPixelFormatIndex = 0;

	// code
	// PIXELFORMATDESCRIPTOR initialization
	ZeroMemory((void *)&AAA_pfd, sizeof(PIXELFORMATDESCRIPTOR));

	AAA_pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	AAA_pfd.nVersion = 1;
	AAA_pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	AAA_pfd.iPixelType = PFD_TYPE_RGBA;
	AAA_pfd.cColorBits = 32;
	AAA_pfd.cRedBits = 8;
	AAA_pfd.cGreenBits = 8;
	AAA_pfd.cBlueBits = 8;
	AAA_pfd.cAlphaBits = 8;

	//GetDC
	AAA_ghdc = GetDC(AAA_ghwnd);
	if (AAA_ghdc == NULL)
	{
		fprintf(AAA_gpFile, "GetDC Function Failed");
		return(-1);
	}

	// Get Matching Pixel Format Index using hdc and pfd
	AAA_iPixelFormatIndex = ChoosePixelFormat(AAA_ghdc, &AAA_pfd);
	if (AAA_iPixelFormatIndex == 0)
	{
		fprintf(AAA_gpFile, "ChoosePixelFormat Failed");
		return(-2);
	}

	// Select The Pixel Format of Found Index
	if (SetPixelFormat(AAA_ghdc, AAA_iPixelFormatIndex, &AAA_pfd) == FALSE)
	{
		fprintf(AAA_gpFile, "SetPixelFormat Failed");
		return(-3);
	}

	// Create Rendering context using hdc, pfd and choosen pixel format index
	AAA_ghrc = wglCreateContext(AAA_ghdc);
	if (AAA_ghrc == NULL)
	{
		fprintf(AAA_gpFile, "wglCreateContext Function failed");
		return(-4);
	}

	// Make This Rendering Context as Current Context
	if (wglMakeCurrent(AAA_ghdc, AAA_ghrc) == FALSE)
	{
		fprintf(AAA_gpFile, "wglMakeCurrent Function failed");
		return(-5);
	}

	// Print GLInfo 
	printGLInfo();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Load Similey Texture
	if(loadGLTexture(&texture_Raj_mahal, MAKEINTRESOURCE(IDBITMAP_RAJMAHAL)) == FALSE)
	{
		fprintf(AAA_gpFile, "loadGLTexture() failed for smiley texture in initialize");
		return(-6);
	}

	// Enable texturing
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_POINT_SMOOTH);
	HandCurveCalculation();

	// From here Onward OpenGL Code starts
	// Tell OpenGL to Choose the Color to Clear the Screen
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Warmup resize
	resize(WIN_WIDTH, WIN_HEIGHT);

	return(0);
}


void printGLInfo(void)
{
	// code
	// Print OpenGL Information 
	fprintf(AAA_gpFile, "OpenGL information\n");
	fprintf(AAA_gpFile, "*********************\n");
	fprintf(AAA_gpFile, "OpenGL Vendor : %s \n", glGetString(GL_VENDOR));
	fprintf(AAA_gpFile, "OpenGL Renderer : %s \n", glGetString(GL_RENDERER));
	fprintf(AAA_gpFile, "OpenGL Version : %s \n", glGetString(GL_VERSION));
	fprintf(AAA_gpFile, "*********************\n");
}

void resize(int width, int height)
{
	// code
	// If Height by accident becomes 0, then make it 1
	if (height <= 0)
	{
		height = 1;
	}

	// Set The ViewPort
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	// Set Matrix Projection Mode
	glMatrixMode(GL_PROJECTION);

	// Set to Identity Matrix
	glLoadIdentity();

	// Do Perspective Projection
	gluPerspective(45.0f,
		((GLfloat)width / (GLfloat)height),
		0.1f,
		100.0f);
}

void display(void)
{
	// code
	// Clear OpenGL Buffers
	glClear(GL_COLOR_BUFFER_BIT);

	// Set Matrix to Model View Mode
	glMatrixMode(GL_MODELVIEW);

	RamSitaVivah();

	// Swap the Buffers
	SwapBuffers(AAA_ghdc);
}

void update(void)
{
	// code
}

void uninitialize(void)
{
	// function declarations
	void toggleFullScreen(void);

	// code
	// If User is Exiting in Full Screen ,Then Restore FullScreen Back to Normal
	if (AAA_gbFullScreen == TRUE)
	{
		toggleFullScreen();
		AAA_gbFullScreen = FALSE;
	}

	if(texture_Raj_mahal)
	{
		glDeleteTextures(1, &texture_Raj_mahal);
		texture_Raj_mahal = 0;
	}

	// Make hdc as Current Context by releasing rendering Context as Current Context
	if (wglGetCurrentContext() == AAA_ghrc)
	{
		wglMakeCurrent(NULL, NULL);
	}

	// Delete the Rendering Context
	if (AAA_ghrc)
	{
		wglDeleteContext(AAA_ghrc);
		AAA_ghrc = NULL;
	}

	// Release The DC
	if (AAA_ghdc)
	{
		ReleaseDC(AAA_ghwnd, AAA_ghdc);
		AAA_ghdc = NULL;
	}

	// Destroy Window
	if (AAA_ghwnd)
	{
		DestroyWindow(AAA_ghwnd);
		AAA_ghwnd = NULL;
	}

	// Close File
	if (AAA_gpFile)
	{
		fprintf(AAA_gpFile, "Program Terminated Successfully ...");
		fclose(AAA_gpFile);
		AAA_gpFile = NULL;
	}
}




