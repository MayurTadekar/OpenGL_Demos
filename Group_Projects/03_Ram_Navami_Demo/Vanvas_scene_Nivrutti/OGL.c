// Standart Win32 headers
#include <windows.h>	// Compiler la samajnarya environmental variable madhlya include file PATH  // Around 3.5 lack API's are present in windows.h either directly or indirectly.
#include <stdio.h>
#include <stdlib.h>		// Library for exit() function

// OpenGL Related Header Files
#include <gl/GL.h>
#include <gl/GLU.h>

// Custom Header Files
#include "OGL.h"

// OpenGL Related Libraries
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "GLU32.lib")	// OpenGL utility by Windows for shapes  	// There is no relation of this Header with GLUT.

// Macros
#define WIN_WIDTH 800
#define WIN_HEIGHT 600		// this is 4:3 Ratio which is standard for VGA

// Global Callback Function Declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Global variable declarations related with Full Screen
BOOL NRD_gbFullScreen = FALSE;
HWND NRD_ghwnd = NULL;
DWORD NRD_dwStyle;
WINDOWPLACEMENT NRD_wpPrev;	// This will contains Window placement at the start of window

// Global Variables declaration related to File I/O
char NRD_gszLogFileName[] = { "Log.txt" };
FILE* NRD_gpFile = NULL;

// Active Window Related Variables
BOOL NRD_gbActiveWindow = FALSE;

// Exit Key pressed related
BOOL NRD_gbEscapeKeyIsPressed = FALSE;

// OpenGL Related Global Variables
HDC NRD_ghdc = NULL;		// Global Handle to Device Context
HGLRC NRD_ghrc = NULL;		// Hangle to Graphics Library Rendering Context (i.e Global Handle to Rendering Context)

// Ram lakxman sita object position related variables
extern float NRD_RLS_updatex;
extern float NRD_RLS_updatey;
extern float NRD_RLS_updateTransform;
BOOL NRD_vanvasAnimation = TRUE;
extern float NRD_Birds_x;
extern float NRD_Birds_y;

// Entry Point Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// Function Declaration
	int initilize(void);
	void display(void);
	void NRD_update(void);
	void uninitilize(void);

	// Variable Declarations
	WNDCLASSEX NRD_wndclass;
	HWND NRD_hwnd;
	MSG NRD_msg;
	TCHAR NRD_szAppName[] = TEXT("RTR6");
	BOOL NRD_bDone = FALSE;
	
	// Code
	// Create Log File
	NRD_gpFile = fopen(NRD_gszLogFileName, "w");
	if (NRD_gpFile == NULL)
	{
		MessageBox(NULL, TEXT("Log File Note Created"), "LOG FILE ERROR", MB_OK | MB_ICONERROR);
		exit(0);
	}
	else
	{
		fprintf(NRD_gpFile, "Program Started Succesfully\n");
	}

	// WNDCLASSEX structure members initilization OR Window Class Initilization
	NRD_wndclass.cbSize = sizeof(WNDCLASSEX);
	NRD_wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;		// here CS_OWNDC tells to OS that create such Device Context (DC) which memory will not be reallocated while running the application.
	NRD_wndclass.cbClsExtra = 0;
	NRD_wndclass.cbWndExtra = 0;
	NRD_wndclass.lpfnWndProc = WndProc;
	NRD_wndclass.hInstance = hInstance;
	NRD_wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	NRD_wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	NRD_wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	NRD_wndclass.lpszClassName = NRD_szAppName;
	NRD_wndclass.lpszMenuName = NULL;
	NRD_wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	
	// Registration of Window Class
	// Error checking should be done of RegisterWindowEx () return, fails or success
	RegisterClassEx(&NRD_wndclass);

	// Create window	// Error checking should be done of CreateWindow() return, fails or success
	NRD_hwnd = CreateWindowEx(WS_EX_APPWINDOW,				// 
						NRD_szAppName, 						// Custom class Name
						TEXT("Nivrutti R. Damdhar - FFP - Windows/02-OpenGL-04-Perspective - Colored"), 	// Caption / Title of Window
						WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,  			// DWORD (Type) and it show my window should be on TOP of all window on desktop, it is combination of 6 Macros.
						(GetSystemMetrics(SM_CXSCREEN)/2 - WIN_WIDTH/2),		//  this paramater is X window on Desktop
						(GetSystemMetrics(SM_CYSCREEN)/2 - WIN_HEIGHT/2),		// which Y Cordinate of Window on Desktop and it is Default
						WIN_WIDTH,  					// Width of Window (we will use our macros here)
						WIN_HEIGHT, 					// Height of Window
						NULL, 							// Handle of Parent Window, Here NULL means Handle of Desktop Window, we Can Give (HWND_DESKTOP)
						NULL, 							// Handle of Menu (NOT system menu) it is User defined Menu
						hInstance, 						// Handle of Current Window, It is NULL in Premptive Multitasking
						NULL);							// Window Creation Parameter, if we want to send any to WndProc() function withou declaring it as global pass it here
														// How to send this Paramater to WndProc:
														// Create structue of some members and pass pointer of that structure to this parameter by typecasting it in (LPVOID)
														// How to use in WndProc: use in case WM_CREATE: in WndProc.


	NRD_ghwnd = NRD_hwnd;	// given hwnd to gloabal variable ghwnd from local variable for toggleFullScreen() use

	// Show Window
	ShowWindow(NRD_hwnd, iCmdShow);

	// Paint Background of the Window by Given Brush as given in hbrBackground of wndclass strut
	UpdateWindow(NRD_hwnd);

	// Initilize
	int result = initilize();
	if(result != 0)
	{
		fprintf(NRD_gpFile, "initilize() failed!\n");
		DestroyWindow(NRD_hwnd);
		NRD_hwnd = NULL;
	}
	else
	{
		fprintf(NRD_gpFile, "initilize() completed Succesfully.\n");
	}

	// Set this window as Foreground and Active Window
	SetForegroundWindow(NRD_hwnd);
	SetFocus(NRD_hwnd);

	// Game Loop
	while (NRD_bDone == FALSE)
	{
		if (PeekMessage(&NRD_msg, NULL, 0, 0, PM_REMOVE))	// PeekMessage() is not blocking function, it will continuesly run unlike the GetMessage() function as (GetMessage() will stop if there is no Message).
														// i.e. PeekMessage() will return FALSE if there is No message in Message Queue, so control will go in else block.
														// PM_REMOVE removes message from Message Queue, but GetMessage() will remove message from queue as it's default behaviour.
		{
			if (NRD_msg.message == WM_QUIT)
			{
				NRD_bDone = TRUE;
			}
			else
			{
				TranslateMessage(&NRD_msg);		// Converts Interrupt into Event of Active Window
				DispatchMessage(&NRD_msg);
			}
		}
		else
		{
			if (NRD_gbActiveWindow)
			{
				// Render
				if (NRD_gbEscapeKeyIsPressed == TRUE)
				{
					NRD_bDone = TRUE;
				}
				display();
				NRD_update();
			}
		}
	}

	// Uninitilize
	uninitilize();

	return((int)NRD_msg.wParam);
}

// Callback Function
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// Local Toggle function declaration
	void toggleFullScreen(void);
	void resize(int, int);
	void uninitilize(void);

	// Code
	switch (iMsg)
	{
	case WM_CREATE:
		ZeroMemory((void*)&NRD_wpPrev, sizeof(WINDOWPLACEMENT));
		NRD_wpPrev.length = sizeof(WINDOWPLACEMENT);
		break;

	case WM_SETFOCUS:
		NRD_gbActiveWindow = TRUE;
		break;

	case WM_KILLFOCUS:
		NRD_gbActiveWindow = FALSE;
		break;

	case WM_ERASEBKGND:
		return(0);

	case WM_SIZE:
		// Resize window
		resize(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:			// Here VK is Virtual Key Code ( it is used in case if there is no any char to represent a key such as 'A', 'Z')
			NRD_gbEscapeKeyIsPressed = TRUE;
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
			if (NRD_gbFullScreen == FALSE)
			{
				toggleFullScreen();
				NRD_gbFullScreen = TRUE;
			}
			else
			{
				toggleFullScreen();
				NRD_gbFullScreen = FALSE;
			}
			break;

		default:
			break;
		}
		break;
	case WM_CLOSE:
		// Uninitilize if the X button is pressed from right top of window.
		uninitilize();
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}


void toggleFullScreen(void)
{
	// Variable Declarations
	MONITORINFO NRD_mi;

	//TCHAR str[255];

	// Code
	if (NRD_gbFullScreen == FALSE)
	{
		// Get Window Style
		NRD_dwStyle = GetWindowLong(NRD_ghwnd, GWL_STYLE);
		
		// Check whether current window style contains WS_OVERLAPPEDWINDOW
		if (NRD_dwStyle & WS_OVERLAPPEDWINDOW)
		{
			ZeroMemory((void*)&NRD_mi, sizeof(MONITORINFO));
			NRD_mi.cbSize = sizeof(MONITORINFO);

			if (GetWindowPlacement(NRD_ghwnd, &NRD_wpPrev) && GetMonitorInfo(MonitorFromWindow(NRD_ghwnd, MONITORINFOF_PRIMARY), &NRD_mi))
			{
				SetWindowLong(NRD_ghwnd, GWL_STYLE, NRD_dwStyle & ~WS_OVERLAPPEDWINDOW);//Here we Setting current style of window as GWL_STYLE and removing WS_OVERLAPPEDWINDOW from current style using the negation (~)

				// /*********************************************************************/
				SetWindowPos(NRD_ghwnd, HWND_TOP, NRD_mi.rcMonitor.left, NRD_mi.rcMonitor.top, (NRD_mi.rcMonitor.right - NRD_mi.rcMonitor.left), (NRD_mi.rcMonitor.bottom - NRD_mi.rcMonitor.top), SWP_NOZORDER | SWP_FRAMECHANGED);	
				// wsprintf(str, "left : %ld , top = %ld, right:%ld, bottom:%ld",mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right, mi.rcMonitor.bottom);
				// MessageBox(ghwnd, str, TEXT("Full Screen Size"), MB_OK);
				// here HWND_TOP is for Window on Top of Z Order 

				// 7th paramater is for if we want to give messages to that window by SetWindowPos()
				// SWP_NOZORDER  ---------> It states that do not change order of this window as it is already set as HWND_TOP
				// SWP_FRAMECHANGED ------> Recalibrate boarder or repaint the window it is told by this macro 
				//				    ------> SWP_FRAMECHANGED this macro sends a Message to OS and i.e. WM_NCCALCSIZE (to calculate client area size)

				// /*********************************************************************/

				// Do not show Cursor after Full Screen Window
				ShowCursor(FALSE);
			}
		}
	}
	else
	{
		SetWindowPlacement(NRD_ghwnd, &NRD_wpPrev);
		SetWindowLong(NRD_ghwnd, GWL_STYLE, NRD_dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(NRD_ghwnd, HWND_TOP, 0,0,0,0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);		// Here the x,y, top, bottom variable will be 0 as We have set window size from SetWindowPlacement() function from wpPrev struct values.

		ShowCursor(TRUE);
	}
}

int initilize(void)
{
	// Local Variable Declarations
	PIXELFORMATDESCRIPTOR NRD_pfd;
	int NRD_iPixelFormatIndex = 0;

	// Function Declaration
	void printGlInfo(void);
	void resize(int, int);
	
	// Code
	// PIXELFORMATDESCRIPTOR Members Initilization
	ZeroMemory((void*)&NRD_pfd, sizeof(PIXELFORMATDESCRIPTOR));
	NRD_pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	NRD_pfd.nVersion = 1;
	NRD_pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	NRD_pfd.iPixelType = PFD_TYPE_RGBA;
	NRD_pfd.cColorBits = 32;
	NRD_pfd.cRedBits = 8;
	NRD_pfd.cGreenBits = 8;
	NRD_pfd.cBlueBits = 8;
	NRD_pfd.cAlphaBits = 8;

	// Get DC
	NRD_ghdc = GetDC(NRD_ghwnd);
	if (NRD_ghdc == NULL)
	{
		fprintf(NRD_gpFile, "GetDC() Failed.\n");
		return(-1);
	}

	// Get Matching Pixel Format index using HDC and PFD
	NRD_iPixelFormatIndex = ChoosePixelFormat(NRD_ghdc, &NRD_pfd);				// Win32 Function Call
	if (NRD_iPixelFormatIndex == 0)
	{
		fprintf(NRD_gpFile, "ChoosePixelFormat() Failed.\n");
		return(-2);
	}

	// Select the pixel Format of Found Index
	if (SetPixelFormat(NRD_ghdc, NRD_iPixelFormatIndex, &NRD_pfd) == FALSE)		// Win32 Function call
	{
		fprintf(NRD_gpFile, "SetPixelFormat() Failed.\n");
		return(-3);
	}

	// Create Rendering Context using HDC, PFD, and PixelFormatIndex and Chosen Pixel Format Index
	NRD_ghrc = wglCreateContext(NRD_ghdc);										// Bridging API Function
	if (NRD_ghrc == NULL)
	{
		fprintf(NRD_gpFile, "wglCreateContext() Failed.\n");
		return(-4);
	}

	// Make This Rendering Context as Current Context
	if (wglMakeCurrent(NRD_ghdc, NRD_ghrc) == FALSE)
	{
		fprintf(NRD_gpFile, "wglMakeCurrent() Failed.\n");
		return(-5);
	}

	// Print GL Info
	printGlInfo();

	// ************************************** FROM HERE ONWARDS OPENGL Code Starts ************************************** //

	// For tree leaves smothneess
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	// Tell OpenGL to choose the color to clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Warmup Resize
	resize(WIN_WIDTH, WIN_HEIGHT);

	// Initilize this variables before just starting the scene
	NRD_RLS_updatey = -0.9;
	NRD_RLS_updateTransform = -3.0f;
	NRD_Birds_x = 1.5f;
	NRD_Birds_y = 1.1f;

	return(0);
}

void printGlInfo(void)
{
	// Code
	// Print OpenGL Information
	fprintf(NRD_gpFile, "******************************** OpenGL Information ************************************\n");
	fprintf(NRD_gpFile, "1) OpenGL Vendor : %s \n\n", glGetString(GL_VENDOR));
	fprintf(NRD_gpFile, "1) OpenGL Renderer : %s \n\n", glGetString(GL_RENDERER));
	fprintf(NRD_gpFile, "1) OpenGL Version : %s \n", glGetString(GL_VERSION));
	fprintf(NRD_gpFile, "****************************************************************************************\n");
}

void resize(int width, int height)
{
	// Code
	// If Height byaccident becomes 0 or less than 0 then make height 1.
	if (height < 0)
	{
		height = 1;
	}
	// Set the Viewport
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	// Set Matrix to Projection Mode
	glMatrixMode(GL_PROJECTION);

	// Set to Identity Matrix
	glLoadIdentity();

	// Do Perspective Projection
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.f);	// 1st param : FOV-Y (Field of View - Y)
																			// 2nd Param : Aspect Ration  (Float Divison so differently typecast it)
																			// 3rd Param : Near
																			// 4th Param : Far
}

void display(void)
{
	// code
	// Clear OpenGL Buffers
	glClear(GL_COLOR_BUFFER_BIT);

	// Set Matrix to Modelview mode
	glMatrixMode(GL_MODELVIEW);

	// Call to the scene function
	NRD_vanvas();
	
	// Swap the buffers
	SwapBuffers(NRD_ghdc);					// Win32 Function Call
}

void NRD_update(void)
{
	if(NRD_RLS_updatey >= 1.15)
	{
		// add code here for next scene change

		NRD_vanvasAnimation = FALSE;
	}

	if(NRD_vanvasAnimation)
	{
		// code
		// Update Ram Lakxman Sita on Y axis 
		if(NRD_RLS_updatey < 1.15)
		{
			NRD_RLS_updatey+= 0.0008;
		}

		if(NRD_RLS_updatey > -0.1 && NRD_RLS_updatey < 1.15)    // Movement of objects over x-axis upper part
		{
			NRD_RLS_updatex += 0.00033;		// Decrease this factor if speed on y axis changed (minimized)
		}
		if(NRD_RLS_updatey < -0.1 && NRD_RLS_updatey >= -0.9) 	// Movement of objects over x-axis
		{
			NRD_RLS_updatex -= 0.0002;
		}

		if(NRD_RLS_updatey > 0.07)					// Transformation matrix related variable update
		{
			NRD_RLS_updateTransform -= 0.002;
		}
		else if(NRD_RLS_updateTransform > -8.0f)	// Transformation matrix related variable update
		{
			NRD_RLS_updateTransform -= 0.003;
		}

		if(NRD_Birds_x > -4.0f)					// Birds positon changes on x axis
		{
			NRD_Birds_x -= 0.008;
		}

		if(NRD_Birds_y >= 1.1f)					// Birds positon slightly change on Y axis
		{
			NRD_Birds_y += 0.00015;
		}
	}

}

void uninitilize(void)
{
	// Function Declaration
	void toggleFullScreen(void);

	glDisable(GL_BLEND);
	glDisable(GL_POINT_SMOOTH);

	// code
	// If user is exiting in full screen then restore full screen back to Normal
	if (NRD_gbFullScreen = TRUE)
	{
		toggleFullScreen();
		NRD_gbFullScreen = FALSE;
	}

	// Make HDC as current context by releasing Rendering context as current context
	if (wglGetCurrentContext() == NRD_ghrc)
	{
		wglMakeCurrent(NULL, NULL);
	}

	// Delete the rendering context
	if (NRD_ghrc)
	{
		wglDeleteContext(NRD_ghrc);
		NRD_ghrc = NULL;
	}

	// Release the DC
	if (NRD_ghdc)
	{
		ReleaseDC(NRD_ghwnd, NRD_ghdc);
		NRD_ghdc = NULL;
	}
	
	// Destroy Window
	if (NRD_ghwnd)
	{
		DestroyWindow(NRD_ghwnd);
		NRD_ghwnd = NULL;
	}

	// Close the File
	if (NRD_gpFile)
	{
		fprintf(NRD_gpFile, "Program Terminated Succesfully.\n");
		fclose(NRD_gpFile);
		NRD_gpFile = NULL;
	}
}
