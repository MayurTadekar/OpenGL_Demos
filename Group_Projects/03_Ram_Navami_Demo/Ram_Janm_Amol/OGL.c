//Win32 headers
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
//OpenGL related header file
#include <gl/GL.h>
#include <gl/GLU.h>

//Custom header files
#include "OGL.h"
#include "Ram_Janm.h"

// OpenGL related libraries
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"GLU32.lib")

// Macros
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

//#define VALUE_FROM_PERCENT(complete_value, percent) (complete_value * percent/100)



// global function declarations/prototype/signature
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Global Variable declarations
//Variable related to Full Screen

BOOL ASN_gbFullScreen = FALSE; // ha Win32 SDK cha bool ahe // TRUE = 1 & FALSE = 0 internally // gbFullScreen madhe "g" stands for global and "b" stands for BOOL // C++ madhe bool asato jyachi value true/false asate.

HWND ASN_ghwnd = NULL;
DWORD ASN_dwStyle;
WINDOWPLACEMENT ASN_wpPrev;

// variable related to File I/O
char ASN_gszLogFileName[] = "Log.txt";
FILE* ASN_gbFile = NULL; // stdio.h madhe FILE asate

// Active window related variable
BOOL ASN_gbActiveWindow = FALSE;

// EXIT Key Press Related 
BOOL ASN_gbEscapeKeyIsPressed = FALSE;

// variable for Window Centering
int ASN_x, ASN_y;
ASN_x = ((SM_CXSCREEN) / 2 - (WIN_WIDTH) / 2);
ASN_y = ((SM_CYSCREEN) / 2 - (WIN_HEIGHT) / 2);

// OpenGL related global variables
HDC ghdc = NULL; // handle to device context
HGLRC ghrc = NULL; // handle to graphics lib rendering context


// Entry-point Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// Function declarations

	int initialize(void);
	void display(void);
	void update(void);
	void uninitialize(void);

	// Variable declarations
	WNDCLASSEX ASN_wndclass;
	HWND ASN_hwnd;
	MSG ASN_msg;
	TCHAR ASN_szAppName[] = TEXT("RTR6");

	BOOL ASN_bDone = FALSE;

	//Code
	// Create Log File
	ASN_gbFile = fopen(ASN_gszLogFileName, "w"); // "w" for writing in the file // "w" overides the file content

	if (ASN_gbFile == NULL)
	{
		MessageBox(NULL, TEXT("LOG FILE CREATION FAILED"), TEXT("FILE I/O ERROR"), MB_OK);
		exit(0);
	}
	else
	{
		fprintf(ASN_gbFile, "Program Started Successfully\n"); // fprintf - it writes in file
	}

	// Window class initialization

	// GLUT INIT
	ASN_wndclass.cbSize = sizeof(WNDCLASSEX);
	ASN_wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	ASN_wndclass.cbClsExtra = 0;
	ASN_wndclass.cbWndExtra = 0;
	ASN_wndclass.lpfnWndProc = WndProc;
	ASN_wndclass.hInstance = hInstance;
	ASN_wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	ASN_wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	ASN_wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	ASN_wndclass.lpszClassName = ASN_szAppName;
	ASN_wndclass.lpszMenuName = NULL;
	ASN_wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	// Registration of Window class
	RegisterClassEx(&ASN_wndclass);

	// Create Window
	ASN_hwnd = CreateWindowEx(WS_EX_APPWINDOW,
		ASN_szAppName,
		TEXT("Amol Suresh Nandkar-FFP-Windows-02-OpenGl-05-2DRotation-03-Two2Dshapes"), // glut Create window parameter
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
		GetSystemMetrics(SM_CXSCREEN) / 2 - (WIN_WIDTH / 2),
		GetSystemMetrics(SM_CYSCREEN) / 2 - (WIN_HEIGHT / 2),
		WIN_WIDTH,
		WIN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ASN_ghwnd = ASN_hwnd; // Assingning hwnd handle to ghwnd which is global variable

	// Show Window
	ShowWindow(ASN_hwnd, iCmdShow);

	//Paint the Background of window
	UpdateWindow(ASN_hwnd);

	//initialize
	int ASN_result = initialize();

	if (ASN_result != 0)
	{
		fprintf(ASN_gbFile, "Initialize() Failed\n");
		DestroyWindow(ASN_hwnd);
		ASN_hwnd = NULL;
	}
	else
	{
		fprintf(ASN_gbFile, "Initialize() Completed Successfully\n");
	}

	// Set This Window as Foreground & Active Window

	SetForegroundWindow(ASN_hwnd);
	SetFocus(ASN_hwnd);

	// Game Loop

	while (ASN_bDone == FALSE)
	{
		if (PeekMessage(&ASN_msg, NULL, 0, 0, PM_REMOVE))
		{
			if (ASN_msg.message == WM_QUIT)
			{
				ASN_bDone = TRUE;
			}
			else
			{
				TranslateMessage(&ASN_msg);
				DispatchMessage(&ASN_msg);
			}
		}
		else
		{
			if (ASN_gbActiveWindow == TRUE)
			{
				if (ASN_gbEscapeKeyIsPressed == TRUE)
				{
					ASN_bDone = TRUE;
				}
				//Render
				display();

				//update
				update();
			}
		}
	}

	// uninitialize
	uninitialize();

	return((int)ASN_msg.wParam);
}

// Callback Function
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// function declarations
	void toggleFullScreen(void);
	void resize(int, int);
	void uninitialize(void);

	// code
	switch(iMsg)
	{
		case WM_CREATE:
			ZeroMemory((void*)&ASN_wpPrev, sizeof(WINDOWPLACEMENT));
			ASN_wpPrev.length = sizeof(WINDOWPLACEMENT);
			break;

		case WM_SETFOCUS:
			ASN_gbActiveWindow = TRUE;
			break;
		case WM_KILLFOCUS:
			ASN_gbActiveWindow = FALSE;
			break;
		case WM_ERASEBKGND: // flicker free rendering sathi hi case add keli ahe
			return(0);
		case WM_SIZE:
			resize(LOWORD(lParam), HIWORD(lParam));
			break;
		case WM_KEYDOWN:
			switch (wParam)
			{
			case VK_ESCAPE:
				ASN_gbEscapeKeyIsPressed = TRUE;
				break;
			default:
				break;

			}
			break;

		case WM_CHAR:
			switch(wParam)
			{
			case 'F':
			case 'f':
				if (ASN_gbFullScreen == FALSE)
				{
					toggleFullScreen();
					ASN_gbFullScreen = TRUE;
				}
				else
				{
					toggleFullScreen();
					ASN_gbFullScreen = FALSE;
				}
				break;

			case 'P':
			case 'p':
				SetTimer(ASN_ghwnd, 1111, 0, NULL);
				break;
			default:
				break;
			}
			break;

		case WM_CLOSE:
			uninitialize();
			break;
		case WM_DESTROY: // glut Leave main Loop
			PostQuitMessage(0);
			break;
		case WM_TIMER:
			/*KillTimer(ASN_ghwnd,1111);
			update();
			SetTimer(ASN_ghwnd, 1111, 10, NULL);*/
			break;
		default:
			break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));

}

// Stub Functions : Where no body present for function

void toggleFullScreen(void)
{
	//variable declarations
	MONITORINFO ASN_mi;

	//code
	if (ASN_gbFullScreen == FALSE)
	{
		ASN_dwStyle = GetWindowLong(ASN_ghwnd, GWL_STYLE);

		if (ASN_dwStyle & WS_OVERLAPPEDWINDOW)
		{
			ZeroMemory((void*)&ASN_mi, sizeof(MONITORINFO));
			ASN_mi.cbSize = sizeof(MONITORINFO);

			if (GetWindowPlacement(ASN_ghwnd, &ASN_wpPrev) && GetMonitorInfo(MonitorFromWindow(ASN_ghwnd, MONITORINFOF_PRIMARY), &ASN_mi))
			{
				SetWindowLong(ASN_ghwnd, GWL_STYLE, ASN_dwStyle & ~WS_OVERLAPPEDWINDOW);
				SetWindowPos(ASN_ghwnd, HWND_TOP, ASN_mi.rcMonitor.left, ASN_mi.rcMonitor.top, ASN_mi.rcMonitor.right - ASN_mi.rcMonitor.left, ASN_mi.rcMonitor.bottom - ASN_mi.rcMonitor.top, SWP_NOZORDER | SWP_FRAMECHANGED);

			}
		}
		ShowCursor(FALSE);
	}
	else 
	{
		SetWindowPlacement(ASN_ghwnd, &ASN_wpPrev);
		SetWindowLong(ASN_ghwnd, GWL_STYLE, ASN_dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(ASN_ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);
		ShowCursor(TRUE);
	}
}


int initialize(void)
{
	//Function declarations
	void printGLInfo(void);
	void resize(int, int);

	// variable declarations
	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormatIndex = 0;

	//code
	// PixelFormat descriptor initialization
	ZeroMemory((void*)&pfd, sizeof(PIXELFORMATDESCRIPTOR));
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

	

	// GetDC
	ghdc = GetDC(ASN_ghwnd);
	if (ghdc == NULL)
	{
		fprintf(ASN_gbFile, "getDC() failed\n");
		return(-1);
	}

	//Get matching format index using HDC & pfd
	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);
	if (iPixelFormatIndex == 0)
	{
		fprintf(ASN_gbFile, "choosepixelformat() failed\n");
		return(-2);
	}

	// select the pixel format of found index
	if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE)
	{
		fprintf(ASN_gbFile, "SetPixelformat() failed\n");
		return(-3);
	}

	// Create rendering context using hdc, pfd & pixel format index & chosen pixel format index
	ghrc = wglCreateContext(ghdc);
	if (ghrc == NULL)
	{
		fprintf(ASN_gbFile, "wglcreatecontext() failed\n");
		return(-4);
	}
	

	// Make this rendering context as current context
	if (wglMakeCurrent(ghdc, ghrc) == FALSE)
	{
		fprintf(ASN_gbFile, "wglMakeCurrent() failed\n");
		return(-5);
	}

	//print Gl Info
	printGLInfo();

	//< Depth Related code (Pyramid)
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f); // Depth 1 ne clear kar
	glEnable(GL_DEPTH_TEST); // Depth test enable kar
	glDepthFunc(GL_LEQUAL); // L equal means -> less than or equal asalele fragment pass kar


	//  from here onwards Open Gl code starts
	// Tell openGL to choose the color to clear the screen

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Warm-up Resize
	resize(WIN_WIDTH, WIN_HEIGHT);

	toggleFullScreen();

	return(0);
}

void printGLInfo(void)
{
	// code
	// print OpenGL Information
	fprintf(ASN_gbFile, "OPENGL INFORMATION\n");
	fprintf(ASN_gbFile, "*******************\n");
	fprintf(ASN_gbFile, "OpenGl Vendor : %s\n",glGetString(GL_VENDOR));
	fprintf(ASN_gbFile, "OpenGl Renderer : %s\n", glGetString(GL_RENDERER));
	fprintf(ASN_gbFile, "OpenGl Version : %s\n", glGetString(GL_VERSION));
	fprintf(ASN_gbFile, "*******************\n");
	
}

void resize(int width, int height)
{
	//code
	// if height is 0 / less than 0 then make height 1
	if (height <= 0)
	{
		height = 1;
	}
	// set the view port
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	// set matrix projection mode
	glMatrixMode(GL_PROJECTION);

	// Set to Identity Matrix
	glLoadIdentity();

	// Do Perspective projection // 
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f); // FOV-Y, Aspect ratio, javalchi bhint, Lambchi bhint
	
}

void display(void)
{
	//code
	// clear opengl buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//TRIANGLE
	// Set Matrix to Model view mode
	glMatrixMode(GL_MODELVIEW);

	Ram_Janm_Display_call_Amol();
	// swap the buffers
	SwapBuffers(ghdc);
}

void update(void)
{
	// code
	

}

void uninitialize(void)
{
	// function declaration
	void toggleFullScreen(void);

	// code
	
	// if user is exitting in full screen then restore to normal

	if (ASN_gbFullScreen == TRUE)
	{
		toggleFullScreen();
		ASN_gbFullScreen = FALSE;
	}
	
	//make hdc as current context by releasing rendering context as current context

	if (wglGetCurrentContext() == ghrc)
	{
		wglMakeCurrent(NULL, NULL);

	}

	// deleting the rendering context
	if (ghrc)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;
	}

	// release the DC
	if (ghdc)
	{
		ReleaseDC(ASN_ghwnd, ghdc);
		ghdc = NULL;
	}

	// Destroy Window
	if (ASN_ghwnd)
	{
		DestroyWindow(ASN_ghwnd);
		ASN_ghwnd = NULL;
	}
	
	// close the file
	if (ASN_gbFile)
	{
		fprintf(ASN_gbFile, "Program terminated Successfully\n");
		fclose(ASN_gbFile);
		ASN_gbFile = NULL;
	}

}

