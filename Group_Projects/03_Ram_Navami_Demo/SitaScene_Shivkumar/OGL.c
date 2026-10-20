// Win32 headers
#include<windows.h> 
#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES 1
#include <math.h>

// OpenGL Related Header Files
#include <gl/GL.h>
#include <gl/GLU.h>

// Custom Header Files
#include "OGL.h"
#include "hanumansita_bhet.h"


// OpenGL related libraries
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "GLU32.lib")

//Macros
#define WIN_WIDTH  800 // 4:3 Ratio of Width to height, it's standard for VGA
#define WIN_HEIGHT 600	

// #define strict macro defined in windows.h 

// Global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Global Variable declarations
BOOL sao_gbFullScreen = FALSE; // gb = Global and Boolean | CAPITAL BOOL has CAPITAL TRUE AND FALSE Values
HWND sao_ghwnd = NULL;
DWORD sao_dwStyle;
WINDOWPLACEMENT sao_wpPrev;

// variables related with File I/O
char sao_gszFileName[] = "Log.txt";
FILE *sao_gpFile = NULL;

// Active Window related variable
BOOL sao_gbActiveWindow = FALSE;

// Exit keypress related
BOOL sao_gbEscapeIsPressed = FALSE;


// C++ bool = Is literally having value true and false (small)
// Win32 SDK BOOL = TRUE (1)  and FALSE (0)


//long  _far _pascal func_name(handle to window usigned_int, message number usigned_int, word type param usigned_int, long type param)

// OpenGL related Global Variables
HDC ghdc = NULL;
HGLRC ghrc = NULL;

// Entry point function

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR LpszCmdLine, int iCmdShow)

//internally WinMain is __winMainCRTStartup-> __mainCRTStartup -> main (CRT -> C Run time)
//LpszCmdLine same as argv (long pointer to string which is zero terminated \0)
//WPARAM word parameter, LPARAM long parameter
//iCmdShow how to show window

{
	//code

	// Variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("RTR2024-181"); // TCHAR -> Unicode char, is a multibyte string
	BOOL bDone = FALSE;

	// Create Log File
	sao_gpFile = fopen(sao_gszFileName, "w");
	if(sao_gpFile == NULL)
	{
		MessageBox(NULL, TEXT("Log File Creation Failed"), TEXT("File I/O Error"), MB_OK);
		exit(0);
	}
	else
	{
	    fprintf(sao_gpFile, "Program Started Successfully\n");
	}
	
	// Function Declaration
	int initialize(void);
	void display(void);
	void update(void);
	void uninitialize(void);

	// Window class initialization
	wndclass.cbSize = sizeof(WNDCLASSEX);   //cb -> count of bytes
	wndclass.style = (CS_HREDRAW | CS_VREDRAW | CS_OWNDC); //CS -> Class style, HREDRAW -> Horizontal redraw, VREDRAW-> Vertical redraw, OWNDC -> Device Context
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //handlebrushBackground,  Win32API -> GetStockObject ; getstockobject can return hbrush, hfont, hpen; getstockobject return type is HGDIOBJ
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON)); //ID of Application Icon
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW); //ID of Cursor 
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));//smallIcon
	
	// Registration of Window class
	RegisterClassEx(&wndclass);

	// Create Window
	hwnd = CreateWindowEx(WS_EX_APPWINDOW,
						szAppName, 
						TEXT("Shivkumar Anil Ople-OpenGL-Triangle"), 
						WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE, // WS -> Window Style (there are 6 styles under overlapped, check learn.microsoft documentation)
						CW_USEDEFAULT,// CW-> Create Window , x cordniate
						CW_USEDEFAULT, // y cordniate
						WIN_WIDTH, // width
						WIN_HEIGHT, // height
						NULL, // same as HWND_DESKTOP(default), parent window
						NULL,
						hInstance,
						NULL
						);

	sao_ghwnd = hwnd;
	// Show Window
	ShowWindow(hwnd, iCmdShow);

	// Paint background of window
	UpdateWindow(hwnd);

	// Initialize
	int result = initialize();

	if(result != 0)
	{
		fprintf(sao_gpFile, "initialize() failed\n");
		DestroyWindow(hwnd);
		hwnd = NULL;
	}
	else{
		fprintf(sao_gpFile, "initialize() completed successfully.");
	}

	// Set This Window As Foreground And Active Window
	SetForegroundWindow(sao_ghwnd);
	SetFocus(sao_ghwnd);

	//Game Loop
	while (bDone == FALSE)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{
				bDone = TRUE;
			}
			else{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

		}
		else{
			
			if(sao_gbActiveWindow == TRUE)
			{
				if(sao_gbEscapeIsPressed == TRUE)
				{
					bDone = TRUE;
				}
				// render
				display();
				// update
				update();
			}
		}
	}
	
	uninitialize();
 
	return((int)msg.wParam);
}

// Callback function
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// Code

	//Local Function Declarations
	void toggleFullScreen(void); 
	void resize(int, int);
	void uninitialize(void);

	switch (iMsg)
	{

	case WM_CREATE:
		ZeroMemory((void*)&sao_wpPrev, sizeof(WINDOWPLACEMENT));
		sao_wpPrev.length = sizeof(WINDOWPLACEMENT);
		break;
	
	case WM_SETFOCUS:
			sao_gbActiveWindow = TRUE;
			break;
	
	case WM_KILLFOCUS:
			sao_gbActiveWindow = FALSE;
			break;

	case WM_ERASEBKGND:
			return(0);

	case WM_SIZE:
			resize(LOWORD(lParam), HIWORD(lParam));
			break;

	case WM_KEYDOWN:
			switch (wParam)
			{
			case VK_ESCAPE:
				sao_gbEscapeIsPressed = TRUE;
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
			if(sao_gbFullScreen == FALSE)
			{
				toggleFullScreen();
				sao_gbFullScreen = TRUE;
			}
			else
			{
				toggleFullScreen();
				sao_gbFullScreen = FALSE;
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
	
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void toggleFullScreen(void) // When empty body it is called as a stub function.
{
	//variable declarations
	MONITORINFO mi;

	if(sao_gbFullScreen == FALSE)
	{
		sao_dwStyle = GetWindowLong(sao_ghwnd, GWL_STYLE);
		
		if(sao_dwStyle & WS_OVERLAPPEDWINDOW)
		{
			ZeroMemory((void*)&mi, sizeof(MONITORINFO));
			mi.cbSize = sizeof(MONITORINFO);

			if(GetWindowPlacement(sao_ghwnd, &sao_wpPrev) && GetMonitorInfo(MonitorFromWindow(sao_ghwnd, MONITORINFOF_PRIMARY), &mi))
			{
				SetWindowLong(sao_ghwnd, GWL_STYLE,sao_dwStyle & ~WS_OVERLAPPEDWINDOW);
				SetWindowPos(sao_ghwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top, SWP_NOZORDER | SWP_FRAMECHANGED);
				
				
				//SetWindowPos(ghwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top, SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
			}
		}

		ShowCursor(FALSE);
	}

}
 
int initialize(void)
{
	void resize(int, int);

	// variable declarations
	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormatIndex = 0;

	// code

	// PIXEL Format Descriptor initialization
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

	// GetDC
	ghdc = GetDC(sao_ghwnd);
	if(ghdc == NULL)
	{
		fprintf(sao_gpFile, "GetDC() function Failed.");
		return(-1);
	}	

	// Get Matching Pixel Format Index using HDC and pfd
	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);
	if(iPixelFormatIndex == 0)
	{
		fprintf(sao_gpFile, "ChoosePixelFormat() Failed!");
		return(-2);
	}

	// Select the Pixel Format of the found index
	if(SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE)
	{
		fprintf(sao_gpFile, "SetPixelFormat() Failed!");
		return (-3);
	} 

	// Create Rendering Context using HDC, PFD and Chosen PixelFormatIndex
	ghrc = wglCreateContext(ghdc);
	if(ghrc == NULL)
	{
		fprintf(sao_gpFile, "WGLCreateContext() Failed!");
		return(-4);
	}

	// Make this rendering Context as current context
	if(wglMakeCurrent(ghdc, ghrc) == FALSE)
	{
		fprintf(sao_gpFile, "WGLMakeCurrent() Failed!");
		return(-5);
	}

	// From Here onwards OpenGL Code starts

	glEnable(GL_POINT_SMOOTH);
	
	
	Sheput_Calculation();
	SheputTura_Calculate();
	// Tell OpenGL to choose the color to clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Warmup resize
	resize(WIN_WIDTH, WIN_HEIGHT);

	return(0);
}

void resize(int width, int height)
{
	// code
	// If height gets assigned less than 0 the put 1
	if(height <= 0)
	{
		height = 1;
	}

	// Set the Viewport
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	// Set Matrix Projection Mode
	glMatrixMode(GL_PROJECTION);

	// Set To Identity Matrix
	glLoadIdentity();

	// Do Perspective Projection
	gluPerspective(45.0f, (GLfloat) width / (GLfloat)height, 0.1f, 100.0f);

}

void display(void)
{

	// code
	glClear(GL_COLOR_BUFFER_BIT);

	//Translate triangle backwards by z
	glTranslatef(0.0f, 0.0f, -10.0f);

	// Set Matrix Mode to Model View
	glMatrixMode(GL_MODELVIEW);

	SitaHanumanBhet();
	// Swap the buffers
	SwapBuffers(ghdc);	
}

void update(void)
{
	// dc
}

void uninitialize(void)
{
	// Function declarations
	void toggleFullScreen(void);

	// code
	// If User is Exiting in FullScreen then restore FullScreen back to normal.

	if(sao_gbFullScreen == TRUE)
	{
		toggleFullScreen();
		sao_gbFullScreen = FALSE;
	}

	// make hdc as the current context by releasing rendering context as current context 
	if(wglGetCurrentContext() == ghrc)
	{
		wglMakeCurrent(NULL, NULL);
	}

	// Delete the rendering context
	if(ghrc)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL; 
	}

	// Release the DC
	if(ghdc)
	{
		ReleaseDC(sao_ghwnd, ghdc);
		ghdc = NULL;
	}

	// Destroy Window
	if(sao_ghwnd)
	{
		DestroyWindow(sao_ghwnd);
		sao_ghwnd = NULL;
	}
	
	// Close the file
	if(sao_gpFile)
	{
		fprintf(sao_gpFile, "Program Terminated Successfully!");
		fclose(sao_gpFile);
		sao_gpFile = NULL;
	}
}
