/*
 *************************************************
 * @file	: GuruShishya_Adesh.c
 * @brief	: Implementation of Guru Shishya scene 
 * 			  for Prabhu Shriram Navami demo
 * @author	: Adesh Mohanrao Pathare 
 * 			  <adeshpathare8495@gmail.com>
 * @Date    : 31 March 2025
 *************************************************
 */

// Win32 standard header
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES 1
#include <math.h>

// OpenGL Related Header Files
#include <gl/GL.h>
#include <gl/GLU.h>

// Custom Header Files
#include "GuruShishya_Adesh.h"

// OpenGL Related Libraries
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "GLU32.lib")

// Macros
#define AMP_WIN_WIDTH	800
#define AMP_WIN_HEIGHT	600

// Global variable declarations
/* Variable related to Full-Screen */
BOOL amp_gbFullScreen = FALSE;
HWND amp_ghwnd = NULL;
DWORD amp_dwStyle;
WINDOWPLACEMENT amp_wpPrev;
BOOL amp_bDone = FALSE;

/* Variables related to File I/O */
char amp_gszLogFileName[] = "AMP_Log.txt";
FILE* amp_gpFile = NULL;

/* Active window related variables */
BOOL amp_gbActiveWindow = FALSE;

// Exit key press related
BOOL amp_gbEscapeKeyIsPressed = FALSE;

// OpenGL Related Global Variables
HDC amp_ghdc = NULL;
HGLRC amp_ghrc = NULL; /* HGLRC: global handle to Graphics Library rendering content */

// Entry-Point function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdLine, int iCmdShow)
{

	// Variable declarations
	WNDCLASSEX amp_wndclass;
	HWND amp_hwnd; //opeg pointer
	MSG amp_msg;
	TCHAR amp_szAppName[] = TEXT("RTR6-Adesh Pathare");
	BOOL amp_bDone = FALSE;

	/* Code */
	
	// Create LogFile
	amp_gpFile = fopen(amp_gszLogFileName, "w");
	if (amp_gpFile == NULL)
	{
		MessageBox(NULL, TEXT("LogFile creation failed!!!"), TEXT("File I/O Error"), MB_OK | MB_ICONERROR);
		exit(0);
	}
	else
	{
		fprintf(amp_gpFile, "Program Started Successfully.\n");
	}

	// Windows Class Initialization
	amp_wndclass.cbSize		= sizeof(WNDCLASSEX); //cb -> Count of Bytes
	amp_wndclass.style		= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	amp_wndclass.cbClsExtra = 0;
	amp_wndclass.cbWndExtra = 0;
	amp_wndclass.lpfnWndProc= WndProc;
	amp_wndclass.hInstance	= hInstance;
	amp_wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	amp_wndclass.hIcon		= LoadIcon(hInstance, MAKEINTRESOURCE(AMP_MYICON));
	amp_wndclass.hCursor	= LoadCursor(NULL, IDC_ARROW);
	amp_wndclass.lpszClassName = amp_szAppName;
	amp_wndclass.lpszMenuName = NULL;
	amp_wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(AMP_MYICON));
	
	// Registration of Window Class
	RegisterClassEx(&amp_wndclass);

	// Create Window
	amp_hwnd = CreateWindowEx(
						WS_EX_APPWINDOW,
						amp_szAppName,
						TEXT("Adesh: Ram navami group"),
						WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						AMP_WIN_WIDTH,
						AMP_WIN_HEIGHT,
						NULL,
						NULL,
						hInstance,
						NULL);

	// Copy window handle to global window handle
	amp_ghwnd = amp_hwnd;

	// Show window
	ShowWindow(amp_hwnd, iCmdShow);

	// Paint background of the window
	UpdateWindow(amp_hwnd);

	// Initialize
	int amp_result = initialize();

	if (amp_result != 0)
	{
		fprintf(amp_gpFile, "initialize() failed!\n");
		DestroyWindow(amp_hwnd);
		amp_hwnd = NULL;
	}
	else
	{
		fprintf(amp_gpFile, "initialize() completed successfully.\n");
	}

	
	// Set this window as foreground and active window
	SetForegroundWindow(amp_hwnd);
	SetFocus(amp_hwnd);

	// Game Loop
	while(amp_bDone == FALSE)
	{
		if (PeekMessage(&amp_msg, NULL, 0, 0, PM_REMOVE)) // PM_REMOVE: Remove message from pipe once copied to amp_msg.
		{
			if (amp_msg.message == WM_QUIT)
			{
				amp_bDone = TRUE;
			}
			else
			{
				TranslateMessage(&amp_msg);
				DispatchMessage(&amp_msg);
			}
		}
		else
		{
			// if window is active then render and update
			if (amp_gbActiveWindow == TRUE)
			{
				if (amp_gbEscapeKeyIsPressed == TRUE)
					amp_bDone = TRUE;	

				// Render
				display();

				// Update
				update();
			}
		}
	}

	// Unitialize
	uninitialize();

	return (int)amp_msg.wParam;
} //Entry-Point Function

// Callback function
LRESULT CALLBACK WndProc(HWND amp_hwnd, UINT iamp_Msg, WPARAM wParam, LPARAM lParam)
{
	// Local function declarations
	void toggleFullScreen(void);
	void resize(int, int);
	void uninitialize(void);

	// Code
	switch (iamp_Msg)
	{
		case WM_CREATE:
			ZeroMemory((void*)&amp_wpPrev, sizeof(WINDOWPLACEMENT));
			amp_wpPrev.length = sizeof(WINDOWPLACEMENT);
			break;

		case WM_SETFOCUS:
			amp_gbActiveWindow = TRUE;
			break;

		case WM_KILLFOCUS:
			amp_gbActiveWindow = FALSE;
			break;

		case WM_ERASEBKGND:
			return 0;

		case WM_SIZE:
			resize(LOWORD(lParam), HIWORD(lParam));
			break;

		case WM_KEYDOWN:
			switch(wParam)
			{
				case VK_ESCAPE:
					amp_gbEscapeKeyIsPressed = TRUE;
					break;

				default:
					break;
			}
			break;

		case WM_CHAR:
			switch (wParam)
			{
			case 'F':
			case 'f':
				if (amp_gbFullScreen == FALSE)
				{
					toggleFullScreen();
					amp_gbFullScreen = TRUE;
				}
				else
				{
					toggleFullScreen();
					amp_gbFullScreen = FALSE;
				}
				break;

			default:
				break;
			}
			break;

		case WM_CLOSE:
			uninitialize();
			break;
		
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			break;
	}

	return DefWindowProc(amp_hwnd, iamp_Msg, wParam, lParam);
}

void toggleFullScreen(void)
{
	// variable declarations
	MONITORINFO amp_mi;

	//code
	if (amp_gbFullScreen == FALSE)
	{
		amp_dwStyle = GetWindowLong(amp_ghwnd, GWL_STYLE);
		if (amp_dwStyle & WS_OVERLAPPEDWINDOW)
		{
			ZeroMemory((void*)&amp_mi, sizeof(MONITORINFO));
			amp_mi.cbSize = sizeof(MONITORINFO);

			if (GetWindowPlacement(amp_ghwnd, &amp_wpPrev)
				&& GetMonitorInfo(
					MonitorFromWindow(amp_ghwnd, MONITORINFOF_PRIMARY), 
					&amp_mi)) // MONITORINFOF_PRIMARY: Give me info for primary monitor
			{
				SetWindowLong(amp_ghwnd, GWL_STYLE, amp_dwStyle & ~WS_OVERLAPPEDWINDOW);
				SetWindowPos(
					amp_ghwnd,
					HWND_TOP,
					amp_mi.rcMonitor.left,
					amp_mi.rcMonitor.top,
					amp_mi.rcMonitor.right - amp_mi.rcMonitor.left,
					amp_mi.rcMonitor.bottom - amp_mi.rcMonitor.top,
					SWP_NOZORDER | SWP_FRAMECHANGED); //SWP_FRAMECHANGED will send a message to OS as WM_NCCALCSIZE
			}
		}
		ShowCursor(FALSE);
	}
	else
	{
		SetWindowPlacement(amp_ghwnd, &amp_wpPrev);
		SetWindowLong(amp_ghwnd, GWL_STYLE, amp_dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(
			amp_ghwnd,
			HWND_TOP,
			0, // SetWindowPlacement() already set the original position, hence 0
			0, // SetWindowPlacement() already set the original position, hence 0
			0, // SetWindowPlacement() already set the original position, hence 0
			0, // SetWindowPlacement() already set the original position, hence 0
			SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER);
		ShowCursor(TRUE);
	}
	
}

// Stub functions
int initialize(void)
{
	// Function declarations
	void printGLInfo(void);

	// resize the window
	resize(AMP_WIN_WIDTH, AMP_WIN_HEIGHT);

	// variable declarations
	PIXELFORMATDESCRIPTOR amp_pfd;
	int amp_iPixelFormatIndex = 0;

	// code

	// PIXELFORMATDESCRIPTOR Initialization
	ZeroMemory((void*)&amp_pfd, sizeof(PIXELFORMATDESCRIPTOR));
	// Initialization of structre PIXELFORMATDESCRIPTOR
	amp_pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	amp_pfd.nVersion = 1;
	amp_pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	amp_pfd.iPixelType = PFD_TYPE_RGBA;
	amp_pfd.cColorBits = 32;
	amp_pfd.cRedBits = 8;
	amp_pfd.cBlueBits = 8;
	amp_pfd.cGreenBits = 8;
	amp_pfd.cAlphaBits = 8;

	// Get DC
	amp_ghdc = GetDC(amp_ghwnd);
	if (amp_ghdc == NULL)
	{
		fprintf(amp_gpFile, "GetDC() failed.\n");
		return -1;
	}

	// get matching pixel formar index using HDC and PFD
	amp_iPixelFormatIndex = ChoosePixelFormat(amp_ghdc, &amp_pfd);
	if (amp_iPixelFormatIndex == 0)
	{
		fprintf(amp_gpFile, "ChoosePixelFormar() failed.\n");
		return -2;
	}

	// select the pixel format of found index
	if (SetPixelFormat(amp_ghdc, amp_iPixelFormatIndex, &amp_pfd) == FALSE)
	{
		fprintf(amp_gpFile, "SetPixelFormat() failed.\n");
		return -3;
	}

	// create rendering context using HDC, PFD and set pixelformatindex
	amp_ghrc = wglCreateContext(amp_ghdc);
	if (amp_ghrc == NULL)
	{
		fprintf(amp_gpFile, "wglCreateContext() failed.\n");
		return -4;
	}

	// make this rendering context as current context
	if (wglMakeCurrent(amp_ghdc, amp_ghrc) == FALSE)
	{
		fprintf(amp_gpFile, "wglMakeCurrent() failed.\n");
		return -5;
	}

	// Print GL Info
	printGLInfo();

	// From here onwards openGL code starts

	// Tell OpenGL to Choose the color to clear the screen;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// calculation of all the curves
	adesh_curve_calculations();
	
	// warm-up resize
	resize(AMP_WIN_WIDTH, AMP_WIN_HEIGHT);

	return 0;
}

void printGLInfo(void)
{
	// code

	// print OpenGL Info
	fprintf(amp_gpFile, "***** OPENGL INFORMATION *****\n");
	fprintf(amp_gpFile, "*******************************\n");
	fprintf(amp_gpFile, "OpenGL Vendor 	 : %s\n", glGetString(GL_VENDOR));
	fprintf(amp_gpFile, "OpenGL Renderer : %s\n", glGetString(GL_RENDERER));
	fprintf(amp_gpFile, "OpenGL Version  : %s\n", glGetString(GL_VERSION));
	fprintf(amp_gpFile, "*******************************\n");

}

void resize(int amp_width, int amp_height)
{
	//code
	// if height by accident becomes 0 then make it 1
	if (amp_height <= 0)
	{
		amp_height = 1;
	}

	// set the viewport
	glViewport(0, 0, (GLsizei)amp_width, (GLsizei)amp_height);

	// Set matrix projection mode
	glMatrixMode(GL_PROJECTION);
	
	// Set to identity matrix
	glLoadIdentity();

	// set perspective projection
	gluPerspective(45.0f, ((GLfloat)amp_width / (GLfloat)amp_height), 0.1f, 100.0f);
}

void display(void)
{
	// code
	// Clear openGL buffers
	glClear(GL_COLOR_BUFFER_BIT);

	// set matrix to model view mode
	glMatrixMode(GL_MODELVIEW);

	// set to identity matrix
	glLoadIdentity();

	// translate triangle backwards by z-axis
	glTranslatef(0.0f, 0.0f, -2.30f);

	// call to main function
	adesh_guru_shishya();

	// Swap the buffers
	SwapBuffers(amp_ghdc);
}

void update(void)
{
	//code
}

void uninitialize(void)
{
	// function declarations
	void toggleFullScreen(void);

	//code

	// if user is exiting in full screen then restore the full screen to normal
	if (amp_gbFullScreen == TRUE)
	{
		toggleFullScreen();
		amp_gbFullScreen = FALSE;
	}

	/* make HDC as current context by releasing 
	rendering context as current context */
	if (wglGetCurrentContext() == amp_ghrc)
	{
		wglMakeCurrent(NULL, NULL);
	}

	// delete the rendering context
	if (amp_ghrc)
	{
		wglDeleteContext(amp_ghrc);
		amp_ghrc = NULL;
	}

	// release the DC
	if (amp_ghdc)
	{
		ReleaseDC(amp_ghwnd, amp_ghdc);
		amp_ghdc = NULL;
	}

	// Destroy Window
	if (amp_ghwnd)
	{
		DestroyWindow(amp_ghwnd);
		amp_ghwnd = NULL;
	}

	// Close the file
	if (amp_gpFile)
	{
		fprintf(amp_gpFile, "Program Teramp_minated Successfully.\n");
		fclose(amp_gpFile);
		amp_gpFile = NULL;
	}
}


//EOF