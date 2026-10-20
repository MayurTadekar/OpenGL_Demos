//win32 headers
#include<Windows.h>
#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#define _USE_MATH_DEFINES 1


//open GL related header files
#include<gl/GL.h>
#include<gl/GLU.h>

//custom header files
#include "Integration.h"
//#include "SitaApaharan.h"


//open GL related libraries
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"GLU32.lib")

//Macrows
#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define TIMER_ID_SCENE 999 
//#define FADE_EFECT_SCENE 700


//global variable decalartons
int Scene = 0;
// float fadeAlpha = 1.0f;     // Start fully opaque for fade-in
// float fadeSpeed = 0.01f;


//global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


//variables related to screen resolution
RECT desktop;
int width, height, x_desktop, y_desktop;

// Ram lakxman sita object position related variables
extern float NRD_RLS_updatex;
extern float NRD_RLS_updatey;
extern float NRD_RLS_updateTransform;
BOOL NRD_vanvasAnimation = TRUE;
BOOL isFadingIn = TRUE;
BOOL isFadingOut = FALSE;

//global variable decalartons
BOOL gbFullScreen = FALSE;
HWND ghwnd = NULL;
DWORD dwStyle;
WINDOWPLACEMENT wpPrev;

//variables related to file I/O
char gszLogFileName[] = "log.txt";
FILE* gpFile = NULL;

//Active window related variables
BOOL gbActiveWindow = FALSE;

//exit key press related
BOOL gbEscapeKeyPressed = FALSE;

//open gl related global variables
HDC ghdc = NULL;
HGLRC ghrc = NULL;

//entry point function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//local fuction declarations
	int initialize(void);
	void display(void);
	void update(void);
	void uninitialize(void);

	//variable declaration
		 
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("RTR6");

	BOOL bDone = FALSE;

	//code
   //create log file
	gpFile = fopen(gszLogFileName, "w");
	if (gpFile == NULL)
	{
		MessageBox(NULL, TEXT("Log file creation failed "), TEXT("ERROR"), MB_OK);
		exit(0);
	}
	else
	{
		fprintf(gpFile, "\nProgramme started sucesfully");
	}

	//code
	//window class intialization
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; 
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;//
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	//Registration of window class
	RegisterClassEx(&wndclass);

	//get desktop window size 
	GetWindowRect(GetDesktopWindow(), &desktop);
	width = (desktop.right - desktop.left);
	height = (desktop.bottom - desktop.top);

	x_desktop = (width / 2) - (WIN_WIDTH / 2);
	y_desktop = (height / 2) - (WIN_HEIGHT / 2);

	//create window
	hwnd = CreateWindowEx(WS_EX_APPWINDOW,
		szAppName,
		TEXT("Texture Group-FFP-OpenGL-Ramnavami Project"),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
		x_desktop,
		y_desktop,
		WIN_WIDTH, 
		WIN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	//assign handel to local variable
	ghwnd = hwnd;

	//Show the window
	ShowWindow(hwnd, iCmdShow);

	//paint backgroung of the window
	UpdateWindow(hwnd);

	//inailze
	int result = initialize();

	if (result != 0)
	{
		fprintf(gpFile, "\ninitialize fuction failed");
		DestroyWindow(hwnd);
		hwnd = NULL;

	}
	else
	{
		fprintf(gpFile, "\ninitialize fuction completed sucessfully");
	}

	//set this window as foreground and active window
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);


	//game loop
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
			if (gbActiveWindow == TRUE)
			{
				if (gbEscapeKeyPressed == TRUE)
				{
					bDone = TRUE;
				}
				//render
				display();
				//update
				update();
			}


		}
	}//while loop game cha

	//uninitialize
	uninitialize();


	return((int)msg.wParam);


}// win main

//callback window procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParm, LPARAM lParam)
{
	//fuction declartions
	void toggleFullScreen(void);
	void resize(int, int);
	void uninitialize(void);

	//code
	switch (iMsg)
	{

	case WM_CREATE:
		//deafult memory allocation
		ZeroMemory((void*)&wpPrev, sizeof(WINDOWPLACEMENT));
		wpPrev.length = sizeof(WINDOWPLACEMENT); 

		break;

	case WM_SETFOCUS:
		gbActiveWindow = TRUE;
		break;

	case WM_KILLFOCUS:
		gbActiveWindow = FALSE;
		break;

	case WM_SIZE:
		resize(LOWORD(lParam), HIWORD(lParam));
		break;


	case WM_ERASEBKGND:
		return(0);

	case WM_KEYDOWN:
		switch (wParm)
		{
		case VK_ESCAPE:
			gbEscapeKeyPressed = TRUE;
			break;
		default:
			break;
		}
		break;

	case WM_CHAR:
		switch (wParm)
		{
		case 'f':
		case 'F':
			if (gbFullScreen == FALSE)
			{
				toggleFullScreen();
				gbFullScreen = TRUE;
			}
			else
			{
				toggleFullScreen();
				gbFullScreen = FALSE;

			}
			break;

		case'P':
		case'p':
			SetTimer(hwnd, TIMER_ID_SCENE, 2000, NULL);
			
			break;

	    // case'A':
        // case'a':
		//     SetTimer(hwnd, TIMER_ID_FOR_PUSHPAK_VIMAN, 0, NULL);
		// 	break;

	    // case'G':
		// case'g':
		//     SetTimer(hwnd, DAY_CHANGE_TIMER, 0, NULL);
		//     break;

		default:
		break;

		}
		break;

	case WM_TIMER:
		KillTimer(hwnd, wParm);
		switch (wParm)
		{
		case TIMER_ID_SCENE:
			Scene++;

			if (Scene > 13) 
				Scene = 0;
			
			SetTimer(hwnd, TIMER_ID_SCENE, 5000, NULL); 
			break;

		case TIMER_ID_FOR_PUSHPAK_VIMAN:
			AAA_update();
			SetTimer(hwnd, TIMER_ID_FOR_PUSHPAK_VIMAN, 10, NULL);
			break;

		case TIMER_ID_FOR_NECKLACE:
			NecklaceMove();
			SetTimer(hwnd, TIMER_ID_FOR_NECKLACE, 10, NULL);
			break;

		case TIMER_ID_FOR_BANGLES:
			BanglesMove();
			SetTimer(hwnd, TIMER_ID_FOR_BANGLES, 10, NULL);
			break;

		case DAY_CHANGE_TIMER:
		    dayUpdate();
			SetTimer(hwnd, DAY_CHANGE_TIMER, 10, NULL);
			break;

		// case FADE_EFECT_SCENE:
		//     updateFade();
		// 	SetTimer(hwnd, FADE_EFECT_SCENE, 10, NULL);
		// 	break;


		default:
			break;
		}

		break;

	case WM_CLOSE:
		uninitialize();
		break;

	case WM_DESTROY: PostQuitMessage(0);
		break;
	default: break;
	}
	return(DefWindowProc(hwnd, iMsg, wParm, lParam));//defualt window procedure of operating system
}

void toggleFullScreen(void)
{
	//variable declarations
	MONITORINFO mi;

	//code
	if (gbFullScreen == FALSE)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);
		if (dwStyle && WS_OVERLAPPEDWINDOW)
		{
			ZeroMemory((void*)&mi, sizeof(MONITORINFO));
			mi.cbSize = sizeof(MONITORINFO);//structure use karaychya adhi 

			if (GetWindowPlacement(ghwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))//window postion sathi ani moniter chi mahiti milvnyasathi
				//jyala graphics card lavle ahe to primary moniter asto to MONITORINFOF_PRIMARY ne milto
			{
				//remove karayala ws_overlap window
				SetWindowLong(ghwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);

				SetWindowPos(ghwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top,
					(mi.rcMonitor.right - mi.rcMonitor.left), (mi.rcMonitor.bottom - mi.rcMonitor.top),
					SWP_NOZORDER | SWP_FRAMECHANGED); //WM_NCCALCSIZE ha msg pathvala jata SWP_FRAMECHANGED
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
	// fuction declaration
	void printGLInfo(void);
	void resize(int, int);

	//variable declarations
	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormatIndex = 0;

	//pixel format descripetor intialization
	ZeroMemory((void*)&pfd, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = LPD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cRedBits = 8;
	pfd.cGreenBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;


	//get dc
	ghdc = GetDC(ghwnd);/////////////////////////////
	if (ghdc == NULL)
	{
		fprintf(gpFile, "Get Dc fuction failed\n");
		exit(-1);
	}

	//get matching pixel format index using hdc and pfd
	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);
	if (iPixelFormatIndex == 0)
	{
		fprintf(gpFile, "choose pixel format fuction failed\n");
		exit(-2);
	}

	//select the pixel format of found index
	if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE)
	{
		fprintf(gpFile, "set pixel format fuction failed\n");
		exit(-3);
	}

	//create rendering context using hdc,pfd and pixelformatindex and chosen pixel format index

	ghrc = wglCreateContext(ghdc);//briging api fuction
	if (ghrc == NULL)
	{
		fprintf(gpFile, "wgl create fuction failed\n");
		exit(-4);
	}

	//make this rending context as current context
	if (wglMakeCurrent(ghdc, ghrc) == FALSE)
	{
		fprintf(gpFile, "wgl make current fuction failed\n");
		exit(-5);
	}

	//print GL info

	printGLInfo();

	//from here onwards opengl code start
	//tell opengl to choose the color to clear the screen

	//code
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	

	// calculation of all the curves
	adesh_curve_calculations();
	
	// Point Smooth
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	SetTimer(ghwnd, DAY_CHANGE_TIMER ,0 , NULL);


	//warm up resize
	resize(WIN_WIDTH, WIN_HEIGHT);

	// Vanvas variable 

	NRD_RLS_updatey = -0.9;
    NRD_RLS_updateTransform = -3.0f;

	colorChageRed=0.0f;
    colorChangeGreen=0.0f;
    colorChangeBlue=0.0f;

    colorFlagMorning=FALSE;

	return(0);
}

void printGLInfo(void)
{
	//code

	//print open GL information
	fprintf(gpFile, "\nOPENGL INFORMATION");
	fprintf(gpFile, "\n*******************");
	fprintf(gpFile, "\nOpenGL Vender : %s \n", glGetString(GL_VENDOR));
	fprintf(gpFile, "\nOpenGL Renderer : %s \n", glGetString(GL_RENDERER));
	fprintf(gpFile, "\nOpenGL Version : %s \n", glGetString(GL_VERSION));
	fprintf(gpFile, "\n*******************");


}


void resize(int width, int height)
{
	//code
	//if height by accident<=0 then make it 1
	if (height <= 0)
	{
		height = 1;

	}
	//set the view port
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	//set matrics projection mode
	glMatrixMode(GL_PROJECTION);

	//set to identitity matrics
	glLoadIdentity();

	//do prospective projection
	gluPerspective(45.0f, //fov-y filled of v y
		(GLfloat)width / (GLfloat)height,//aspect ratio
		0.1f,//near
		100.0f);//far

}

void display(void)
{
	//code

	  //clear open gl buffers
	glClear(GL_COLOR_BUFFER_BIT);

	//set matrics model view mode
	glMatrixMode(GL_MODELVIEW);

	//set it to identitity matrics
	glLoadIdentity();

	//translate triangle backwords by z axis
	glTranslatef(0.0f, 0.0f, -2.3f);

	
	glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    {
	glVertex3f(-1.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
    }
    glEnd();


	switch (Scene)
	{
	case 0://ganpati
	    Ganpati_Text();

		break;
	case 1://astromedicomp
	    Astromedicomp_Text();
		break;
	case 2://texture group
	    Omkar_Texture_Text();
		break;
	case 3: //project name
        omkar_main();
		break;
	case 4://ram janm
	    Amoldada_All_Functions();
		break;
	case 5://guru shishya
		adesh_guru_shishya();
		break;
	case 6://seeta Swayamvr
	
		break;
	case 7://vanvas
	    nivrutti_vanvas();
		break;
	case 8://seeta apharan
		Atharv_Sita_Apaharan();
		break;
	case 9://apaharan
		break;
	case 10: //hanuman seeta bhet
		break;
	case 11://ravan dahan
		break;
	case 12://ram mandir
	    GauriRamMandir();
		break;
	case 13://group membr names
	    break;
		
	default:
	    break;

	}


	//swap the buffers
	SwapBuffers(ghdc);

}

void update(void)
{
	//vanvas code
	if(NRD_RLS_updatey >= 0.9)
	{
		// here switch the scene
	
	
		NRD_vanvasAnimation = FALSE;
	}
	
	if(NRD_vanvasAnimation)
	{
		// code
		if(NRD_RLS_updatey < 0.9 )
		{
			NRD_RLS_updatey+= 0.0001;
		}
	
		if(NRD_RLS_updatey < -0.1 && NRD_RLS_updatey >= -0.9)
		{
			NRD_RLS_updatex -= 0.0004;
		}
	
		if(NRD_RLS_updatey > -0.1 && NRD_RLS_updatey < 0.9)
		{
			NRD_RLS_updatex += 0.0008;
		}
	
		if(NRD_RLS_updatey > 0.07)
		{
			NRD_RLS_updateTransform -= 0.009;
		}
		else if(NRD_RLS_updateTransform > -8.0f)
		{
			NRD_RLS_updateTransform -= 0.005;
		}
	}
}

// void updateFade(void)
// {
// 	// Fade In
// if (isFadingIn) {
//     fadeAlpha -= fadeSpeed;
//     if (fadeAlpha <= 0.0f) {
//         fadeAlpha = 0.0f;
//         isFadingIn = FALSE;
//     }
// }

// // Fade Out (if you want to trigger it later)
// if (isFadingOut) {
//     fadeAlpha += fadeSpeed;
//     if (fadeAlpha >= 1.0f) {
//         fadeAlpha = 1.0f;
//         isFadingOut = FALSE;
//         // You can change the scene or do something here
//     }
// }

// }

void uninitialize(void)
{
	//fuction declarations
	void toggleFullScreen(void);

	//code
//if user is exting full screen then retore full screen to normal
	if (gbFullScreen == TRUE)
	{
		toggleFullScreen();
		gbFullScreen = FALSE;
	}

	//make hdc as current context y releasing rendering context as current context
	if (wglGetCurrentContext() == ghrc)
	{
		wglMakeCurrent(NULL, NULL);

	}

	//delete the rendering context
	if (ghrc)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;
	}

	//relese the dc
	if (ghdc)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;

	}
	//destroy window
	if (ghwnd)
	{
		DestroyWindow(ghwnd);
		ghwnd = NULL;
	}

	//close the file
	if (gpFile)
	{
		fprintf(gpFile, "\nFile close sucesfully");
		fclose(gpFile);
		gpFile = NULL;
	}

}
