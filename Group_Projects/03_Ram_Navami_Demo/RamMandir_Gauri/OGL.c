//win32 headers
#include<Windows.h>
#include<stdio.h>//file input outut sathi 
#include<stdlib.h>//file madhe exit karayche asel tar
#include<math.h>

//open GL related header files
#include<gl/GL.h>

//custom header files
#include "RamMandir.h"

//open GL related libraries
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"GLU32.lib")

//Macrows
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

//global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//global variable decalartons

//variables related to screen resolution
RECT GRN_desktop;
int GRN_desktop_width, GRN_desktop_height,GRN_x_desktop,GRN_y_desktop;


//global variable decalartons
BOOL GRN_gbFullScreen = FALSE;
DWORD GRN_dwStyle;
WINDOWPLACEMENT GRN_wpPrev;

//variables related to file I/O
char GRN_gszLogFileName[] = "log.txt";
FILE* GRN_gpFile = NULL;

//Active window related variables
BOOL GRN_gbActiveWindow = FALSE;

//exit key press related
BOOL GRN_gbEscapeKeyPressed = FALSE; 

//open gl related global variables
HDC GRN_ghdc = NULL;
HGLRC GRN_ghrc = NULL;

HWND GRN_ghwnd = NULL; 

//entry point function
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszCmdLine,int iCmdShow)
{
	//local fuction declarations
	int initialize(void);
	void display(void);
	void uninitialize(void);
	

	//variable declaration
		  //GRN := Gauri Ramesh Nidan
	WNDCLASSEX GRN_wndclass;//structure declartion of GRN_wndclassEX
	HWND GRN_hwnd;
	MSG GRN_msg;//STRUCT  GRN_msg
	TCHAR GRN_szAppName[] = TEXT("RTR6");//double code problem

	BOOL GRN_bDone = FALSE;

	//code
   //create log file
	GRN_gpFile = fopen(GRN_gszLogFileName, "w");
	if (GRN_gpFile == NULL)
	{
		MessageBox(NULL, TEXT("Log file creation failed "), TEXT("ERROR"), MB_OK);
		exit(0);
	}
	else
	{
		fprintf(GRN_gpFile, "\nProgramme started sucesfully");
	}

	//code
	//window class intialization
	GRN_wndclass.cbSize = sizeof(WNDCLASSEX);
	GRN_wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; //CS_OWNDC os la sagte asa dc tayar kar inbetween move karnar nahi ti fixed/relable jagi thev;
	GRN_wndclass.cbClsExtra = 0;
	GRN_wndclass.cbWndExtra = 0;
	GRN_wndclass.lpfnWndProc = WndProc;//
	GRN_wndclass.hInstance = hInstance;
	GRN_wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	GRN_wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(GRN_Icon));
	GRN_wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	GRN_wndclass.lpszClassName = GRN_szAppName;
	GRN_wndclass.lpszMenuName = NULL;
	GRN_wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(GRN_Icon));//added GRN_wndclassex after 10 member

	//Registration of window class
	RegisterClassEx(&GRN_wndclass);//atom string write 

	//get desktop window size 
	GetWindowRect(GetDesktopWindow(), &GRN_desktop);
	GRN_desktop_width = (GRN_desktop.right - GRN_desktop.left) ;
	GRN_desktop_height = (GRN_desktop.bottom - GRN_desktop.top);

	GRN_x_desktop = (GRN_desktop_width/2) - (WIN_WIDTH / 2);
	GRN_y_desktop = (GRN_desktop_height/2) - (WIN_HEIGHT / 2);

	//create window
	GRN_hwnd = CreateWindowEx(WS_EX_APPWINDOW,
		GRN_szAppName,
		TEXT("GAURI NIDAN-RamMandir"),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
		GRN_x_desktop,//x
		GRN_y_desktop,//y
		WIN_WIDTH,//win width 
		WIN_HEIGHT,//win height 
		NULL,
		NULL,
		hInstance,
		NULL);

	//assign handel to local variable
	GRN_ghwnd = GRN_hwnd;

	//Show the window
	ShowWindow(GRN_hwnd,iCmdShow);

	//paint backgroung of the window
	UpdateWindow(GRN_hwnd);

	//inailze
	int GRN_result = initialize();

	if (GRN_result != 0)
	{
		fprintf(GRN_gpFile, "\ninitialize fuction failed");
		DestroyWindow(GRN_hwnd);
		GRN_hwnd = NULL;

	}
	else
	{
		fprintf(GRN_gpFile, "\ninitialize fuction completed sucessfully");
	}

	//set this window as foreground and active window
	SetForegroundWindow(GRN_hwnd);//z order madhe saglyat var pahije apli window mhanun
	SetFocus(GRN_hwnd);//aplya window la focus madhe ananya sathi


	//game loop
	while (GRN_bDone == FALSE)
	{
		if (PeekMessage(&GRN_msg, NULL, 0, 0, PM_REMOVE))
		{
			if (GRN_msg.message == WM_QUIT)
			{
				GRN_bDone = TRUE;
			}
			else
			{
				TranslateMessage(&GRN_msg);
				DispatchMessage(&GRN_msg);

			}
		}
		else
		{
			if (GRN_gbActiveWindow == TRUE)
			{
				if (GRN_gbEscapeKeyPressed == TRUE)
				{
					GRN_bDone = TRUE;
				}
				//render
				display();
				
			}


		}
	}//while loop game cha

	//uninitialize
	uninitialize();


	return((int)GRN_msg.wParam);
	
	
}// win main

//callback window procedure
LRESULT CALLBACK WndProc(HWND GRN_hwnd, UINT iMsg, WPARAM wParm, LPARAM lParam)
{
	//fuction declartions
	void toggleFullScreen(void);
	void resize(int,int);
	void uninitialize(void);

	//code
	switch (iMsg)
	{
	  
	  case WM_CREATE://mmset he structure madhil members la default variables declarations ne memory set karato.
		             //deafult memory allocation
		             ZeroMemory((void*)&GRN_wpPrev, sizeof(WINDOWPLACEMENT));//type che nav dyache size of sathi
					 GRN_wpPrev.length = sizeof(WINDOWPLACEMENT); //length hi ekdach intialize karaychi asete mhanun 

		              break;

	  case WM_SETFOCUS:
		               GRN_gbActiveWindow = TRUE;
		               break;

	  case WM_KILLFOCUS:
		                 GRN_gbActiveWindow = FALSE;
		                 break;

	  case WM_SIZE:
		            resize(LOWORD(lParam), HIWORD(lParam));//lowword width ani hiword madhe height milte
		            break;


	  case WM_ERASEBKGND:
		                 return(0);//break chya jagi return 0 use kele

	  case WM_KEYDOWN:
		              switch (wParm)
		              {
					    case VK_ESCAPE:
							           GRN_gbEscapeKeyPressed = TRUE;
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
						       if (GRN_gbFullScreen == FALSE)
						       {
								   toggleFullScreen(); 
								   GRN_gbFullScreen = TRUE;
							   }
							   else
							   {
								   toggleFullScreen(); 
								   GRN_gbFullScreen = FALSE;

							   }
						       
						       break;

					  default:break;
		            }
					break;

		case WM_TIMER:
		             
					KillTimer(GRN_hwnd,wParm);
					switch (wParm)
					{
					
						case DAY_CHANGE_TIMER:
						                     dayUpdate();
						                     SetTimer(GRN_ghwnd,DAY_CHANGE_TIMER,10, NULL); 
											 break;
                            /*
						case DAY_CHANGE_TIMER_AFTERNOON:
														dayUpdateAfternoon();
						                                SetTimer(GRN_ghwnd,DAY_CHANGE_TIMER_AFTERNOON,10, NULL); 
						                                break;
														*/
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
	return(DefWindowProc(GRN_hwnd, iMsg, wParm, lParam));//defualt window procedure of operating system
}

void toggleFullScreen(void)
{
	//variable declarations
	MONITORINFO GRN_mi;

	//code
	if (GRN_gbFullScreen == FALSE)
	{
		GRN_dwStyle = GetWindowLong(GRN_ghwnd,GWL_STYLE);
		if (GRN_dwStyle && WS_OVERLAPPEDWINDOW)
		{
			ZeroMemory((void*)&GRN_mi, sizeof(MONITORINFO));
			GRN_mi.cbSize = sizeof(MONITORINFO);//structure use karaychya adhi 

			if (GetWindowPlacement(GRN_ghwnd, &GRN_wpPrev) && GetMonitorInfo(MonitorFromWindow(GRN_ghwnd, MONITORINFOF_PRIMARY),&GRN_mi))//window postion sathi ani moniter chi mahiti milvnyasathi
				//jyala graphics card lavle ahe to primary moniter asto to MONITORINFOF_PRIMARY ne milto
			{
				//remove karayala ws_overlap window
				SetWindowLong(GRN_ghwnd, GWL_STYLE, GRN_dwStyle & ~WS_OVERLAPPEDWINDOW);

				SetWindowPos(GRN_ghwnd, HWND_TOP, GRN_mi.rcMonitor.left, GRN_mi.rcMonitor.top,
					(GRN_mi.rcMonitor.right - GRN_mi.rcMonitor.left), (GRN_mi.rcMonitor.bottom - GRN_mi.rcMonitor.top),
					SWP_NOZORDER | SWP_FRAMECHANGED); //WM_NCCALCSIZE ha msg pathvala jata SWP_FRAMECHANGED
			}

		}
		ShowCursor(FALSE);
		
	}
	else
	{
		SetWindowPlacement(GRN_ghwnd,&GRN_wpPrev);
		SetWindowLong(GRN_ghwnd, GWL_STYLE, GRN_dwStyle |WS_OVERLAPPEDWINDOW);
		SetWindowPos(GRN_ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_NOOWNERZORDER|SWP_NOZORDER | SWP_FRAMECHANGED);
		ShowCursor(TRUE); 
	}
}

int initialize(void)
{
	// fuction declaration
	void printGLInfo(void);
	void resize(int, int);

	//variable declarations
	PIXELFORMATDESCRIPTOR GRN_pfd;
	int GRN_iPixelFormatIndex = 0;

	//pixel format descripetor intialization
	ZeroMemory((void*)&GRN_pfd, sizeof(PIXELFORMATDESCRIPTOR));
	GRN_pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	GRN_pfd.nVersion = 1;
	GRN_pfd.dwFlags= PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	GRN_pfd.iPixelType = LPD_TYPE_RGBA;
	GRN_pfd.cColorBits = 32;
	GRN_pfd.cRedBits = 8;
	GRN_pfd.cGreenBits = 8;
	GRN_pfd.cBlueBits = 8;
	GRN_pfd.cAlphaBits = 8;
	
	//get dc
	GRN_ghdc = GetDC(GRN_ghwnd);/////////////////////////////
	if (GRN_ghdc == NULL)
	{
		fprintf(GRN_gpFile, "Get Dc fuction failed\n");
		exit(-1);
	}

	//get matching pixel format index using hdc and GRN_pfd
	GRN_iPixelFormatIndex = ChoosePixelFormat(GRN_ghdc, &GRN_pfd);
	if (GRN_iPixelFormatIndex == 0) 
	{
		fprintf(GRN_gpFile, "choose pixel format fuction failed\n");
		exit(-2);
	}

	//select the pixel format of found index
	if (SetPixelFormat(GRN_ghdc, GRN_iPixelFormatIndex, &GRN_pfd) == FALSE)
	{
		fprintf(GRN_gpFile, "set pixel format fuction failed\n");
		exit(-3);
	}

	//create rendering context using hdc,GRN_pfd and pixelformatindex and chosen pixel format index

	GRN_ghrc = wglCreateContext(GRN_ghdc);//briging api fuction
	if (GRN_ghrc == NULL)
	{
		fprintf(GRN_gpFile, "wgl create fuction failed\n");
		exit(-4);
	}
	
	//make this rending context as current context
	if (wglMakeCurrent(GRN_ghdc, GRN_ghrc) == FALSE)
	{
		fprintf(GRN_gpFile, "wgl make current fuction failed\n");
		exit(-5);
	}

	//print GL info

	printGLInfo();

	//from here onwards opengl code start
	//tell opengl to choose the color to clear the screen

	colorChageRed=0.0f;
	colorChangeGreen=0.0f;
	colorChangeBlue=0.0f;
	
	colorFlagMorning=FALSE;

	SetTimer(GRN_ghwnd,DAY_CHANGE_TIMER,0, NULL);

	//code
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//warm up resize
	resize(WIN_WIDTH, WIN_HEIGHT);

	return(0);
}

void printGLInfo(void)
{
	//code

	//print open GL information
	fprintf(GRN_gpFile, "\nOPENGL INFORMATION");
	fprintf(GRN_gpFile, "\n*******************");
	fprintf(GRN_gpFile, "\nOpenGL Vender : %s \n", glGetString(GL_VENDOR));
	fprintf(GRN_gpFile, "\nOpenGL Renderer : %s \n", glGetString(GL_RENDERER));
	fprintf(GRN_gpFile, "\nOpenGL Version : %s \n", glGetString(GL_VERSION));
	fprintf(GRN_gpFile, "\n*******************");


}

void resize(int width, int height)
{
	//code
	//if height by accident<=0 then make it 1
	if (height <= 0)
	{
		height = 1;
		//set the view port
		glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	}
	//set the view port
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	//set matrics projection mode
	glMatrixMode(GL_PROJECTION);

	//set to identitity matrics
	glLoadIdentity();

	//do prospective projection 

	gluPerspective(45.0f, 
		((GLfloat)width / (GLfloat)height),
		0.1f,
		100.0f); 

}

void display(void)
{
  //code
	
	//clear open gl buffers
	glClear(GL_COLOR_BUFFER_BIT);

	//set matrics model view mode
	glMatrixMode(GL_MODELVIEW);

	GauriRamMandir();
	
	SwapBuffers(GRN_ghdc);
}

void update(void)
{
	//code
}

void uninitialize(void)
{
	 //fuction declarations
	void toggleFullScreen(void);

	//code
//if user is exting full screen then retore full screen to normal
	if (GRN_gbFullScreen == TRUE)
	{
		toggleFullScreen();
		GRN_gbFullScreen = FALSE;
	}
	
	//make hdc as current context y releasing rendering context as current context
	if (wglGetCurrentContext() == GRN_ghrc)
	{
		wglMakeCurrent(NULL, NULL);
		
	}

	//delete the rendering context
	if (GRN_ghrc)
	{
		    wglDeleteContext(GRN_ghrc);
			GRN_ghrc = NULL;
	}

	//relese the dc
	if (GRN_ghdc)
	{
		ReleaseDC(GRN_ghwnd, GRN_ghdc);
		GRN_ghdc = NULL;

	}
	//destroy window
	if (GRN_ghwnd)
	{
		DestroyWindow(GRN_ghwnd);
		GRN_ghwnd = NULL;
	}

	//close the file
	if (GRN_gpFile)
	{
		fprintf(GRN_gpFile, "\nFile close sucesfully");
		fclose(GRN_gpFile);
		GRN_gpFile = NULL;
	}

}


