// win32 headers
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

//OPENGL RELETED HEADER FILE
#include<gl/GL.h>
#include "OGL.h"
#include<gl/GLU.h>
#include<math.h>
#include "Astromedicomp_Text.h"


//OPENGL RELETED LIBRARYS
#pragma comment(lib,"opengl32.lib")//preprosesor directive
#pragma comment(lib,"GLU32.lib")

//macros
#define WIN_WIDTH 800
#define WIN_HIGTH 600
//#define VALUE_FROM_PERCENT(complete, percent) (complete * percent/100.0f)

// global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//globalvariable declarations
BOOL ouj_gbFullScreen = FALSE;// "SDK" cha BOOL AAHE HA /// he flag variable aahe
HWND ouj_ghwnd = NULL;//handle
DWORD ouj_dwStyle;//ha aapan static
WINDOWPLACEMENT ouj_wpPrev;

//ACTIVE wINDOW RELATED VARIABLE
BOOL ouj_gbActiveWindow = FALSE;


//EXICT KEY PRESS RELATED
BOOL ouj_gbExcapeKeyPressed = FALSE;


//variable releted with file I/O
char ouj_gszLogFileName[] = "Log.txt";
FILE* ouj_gpFile = NULL;


//OPENGL RELETED GLOBAL VARIABLES
HDC ouj_ghdc = NULL;
HGLRC ouj_ghrc = NULL;
/*
//global variable
 //variable declaration
 struct ouj_Curve 
 {
    float ouj_x1, ouj_x2, ouj_x3, ouj_x4;
    float ouj_y1, ouj_y2, ouj_y3, ouj_y4;

    
 };

float Cat1[100] , Cat2[100];
float Cbt1[100] , Cbt2[100];
float Cct1[100] , Cct2[100];
float Cdt1[100] , Cdt2[100];
float Cet1[100] , Cet2[100];
float Cft1[100] , Cft2[100];
float Cgt1[100] , Cgt2[100];
float Cht1[100] , Cht2[100];
float Cit1[100] , Cit2[100];
float Cjt1[100] , Cjt2[100];
float Ckt1[100] , Ckt2[100];
float Clt1[100] , Clt2[100];
float Cmt1[100] , Cmt2[100];
float Cnt1[100] , Cnt2[100];
float Cot1[100] , Cot2[100];
float Cpt1[100] , Cpt2[100];
float Cqt1[100] , Cqt2[100];
float Crt1[100] , Crt2[100];
float Cst1[100] , Cst2[100];
float Ctt1[100] , Ctt2[100];



//object function declaration
void Astromedicomp_Text(void);
void Astro_A(float x_pos, float y_pos, float percent);
void Astro_S(float x_pos, float y_pos, float percent);
void Astro_T(float x_pos, float y_pos, float percent);
void Astro_R(float x_pos, float y_pos, float percent);
void Astro_O(float x_pos, float y_pos, float percent);
void Astro_M(float x_pos, float y_pos, float percent);
void Astro_E(float x_pos, float y_pos, float percent);
void Astro_D(float x_pos, float y_pos, float percent);
void Astro_I(float x_pos, float y_pos, float percent);
void Astro_C(float x_pos, float y_pos, float percent);
void Astro_OO(float x_pos, float y_pos, float percent);
void Astro_MM(float x_pos, float y_pos, float percent);
void Astro_P(float x_pos, float y_pos, float percent);
*/

// Entry point Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
    //function declaration (local)
    int initialize(void);
    void update(void);
    void display(void);
    void uninitilize(void);

    // variable declarations
    WNDCLASSEX ouj_Wndclass;
    HWND ouj_hwnd;
    MSG ouj_msg;
    TCHAR ouj_szAppName[] = TEXT("RTR6");
    BOOL ouj_bDone = FALSE;

    
    // code
    // CREATE LOG FILE 
    ouj_gpFile = fopen(ouj_gszLogFileName, "w");
    if (ouj_gpFile == NULL)
    {
        MessageBox(NULL, TEXT("Log File Creation fail"), TEXT("error"), MB_OK);
        exit(0); // convention aahe he tya mule 0 aahe tithe (logic)
    }
    else
    {
        fprintf(ouj_gpFile, "Program Started Successfully\n");
    }

    // Window class initialization 
    ouj_Wndclass.cbSize = sizeof(WNDCLASSEX);
    ouj_Wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    ouj_Wndclass.cbClsExtra = 0;
    ouj_Wndclass.cbWndExtra = 0;
    ouj_Wndclass.lpfnWndProc = WndProc; // Correctly references the WndProc function
    ouj_Wndclass.hInstance = hInstance;
    ouj_Wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    ouj_Wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
    ouj_Wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    ouj_Wndclass.lpszClassName = ouj_szAppName;
    ouj_Wndclass.lpszMenuName = NULL;
    ouj_Wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

    // Registration of Window class
    RegisterClassEx(&ouj_Wndclass);

    // create Window
    ouj_hwnd = CreateWindowEx(WS_EX_APPWINDOW,
                               ouj_szAppName,
                               TEXT("Omkar U. Jadhav 01-FFP\01-WindowsOS\02-OpenGL\04-Perseptive\02-Color\02-Quad"), 
                               WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE ,
                               CW_USEDEFAULT, 
                               CW_USEDEFAULT, 
                               WIN_WIDTH,
                               WIN_HIGTH,
                               NULL, 
                               NULL, 
                               hInstance, 
                               NULL);

    ouj_ghwnd = ouj_hwnd;

    // Show Window
    ShowWindow(ouj_hwnd, iCmdShow);

    // Paint Background of window
    UpdateWindow(ouj_hwnd);


    //initilize
    int result = initialize();
    if (result != 0)
    {
        fprintf(ouj_gpFile, "initilize()\n");
        DestroyWindow(ouj_hwnd);
        ouj_hwnd = NULL;
    }
    else
    {
        fprintf(ouj_gpFile, "initilize() completlly sucessfully\n");
    }

    //SET THIS WINDOW HAS FORGROUND AND ACTIVE WINDOW
    SetForegroundWindow(ouj_hwnd);
    SetFocus(ouj_hwnd);

    //Game Loop
    while (ouj_bDone == FALSE)
    {
        if (PeekMessage(&ouj_msg, NULL, 0, 0, PM_REMOVE))//PM= peekmessage
        {
            if (ouj_msg.message == WM_QUIT)
            {
                ouj_bDone = TRUE;
            }
            else
            {
                TranslateMessage(&ouj_msg);
                DispatchMessage(&ouj_msg);
            }

        }
        else
        {
            if (ouj_gbActiveWindow == TRUE)
            {
                if (ouj_gbExcapeKeyPressed == TRUE)
                {
                    ouj_bDone = TRUE;
                }

                //render
                display();

                //update
                update();
            }

        }

    }
    // uninitilize
    uninitilize();

    return ((int)ouj_msg.wParam);
}

// callback function
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    //function declarations
    void togglefullscreen(void);
    void resize(int, int);
    void uninitilize(void);

    // CODE
    switch (iMsg)
    {
    case WM_CREATE:
        ZeroMemory((void*)&ouj_wpPrev, sizeof(WINDOWPLACEMENT));//zeromemory = memset
        ouj_wpPrev.length = sizeof(WINDOWPLACEMENT);
        break;
    case WM_SETFOCUS:
        ouj_gbActiveWindow = TRUE;
        break;
    case WM_KILLFOCUS:
        ouj_gbActiveWindow = FALSE;
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
            ouj_gbExcapeKeyPressed = TRUE;
            break;
        default:
            break;
        }
        break;
        
        break;
     case WM_CHAR:
        switch (wParam)
        {
        case 'F':
        case 'f':
           if (ouj_gbFullScreen == FALSE)
           {
                togglefullscreen();
                ouj_gbFullScreen = TRUE;
           }
           else
           {
               togglefullscreen();
               ouj_gbFullScreen = FALSE;
           }
           break;
         default:
           break;
            
        }
        break;
     case WM_CLOSE:
         uninitilize();
         break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        break;
    }

    return DefWindowProc(hwnd, iMsg, wParam, lParam);
}


void togglefullscreen(void)
{
    //variable declarations
    MONITORINFO ouj_mi;

    //code
    if (ouj_gbFullScreen == FALSE)
    {
        ouj_dwStyle = GetWindowLong(ouj_ghwnd, GWL_STYLE);
        if (ouj_dwStyle & WS_OVERLAPPEDWINDOW)
        {
            ZeroMemory((void*)&ouj_mi, sizeof(MONITORINFO));
           ouj_mi.cbSize = sizeof(MONITORINFO);
            if (GetWindowPlacement(ouj_ghwnd, &ouj_wpPrev) && GetMonitorInfo(MonitorFromWindow(ouj_ghwnd, MONITORINFOF_PRIMARY), &ouj_mi))
            {
                SetWindowLong(ouj_ghwnd, GWL_STYLE, ouj_dwStyle & ~WS_OVERLAPPEDWINDOW);
                SetWindowPos(ouj_ghwnd, HWND_TOP, ouj_mi.rcMonitor.left, ouj_mi.rcMonitor.top, ouj_mi.rcMonitor.right - ouj_mi.rcMonitor.left, ouj_mi.rcMonitor.bottom - ouj_mi.rcMonitor.top, SWP_NOZORDER | SWP_FRAMECHANGED);

            }



        }
        ShowCursor(FALSE);

    }




    else
    {
        SetWindowPlacement(ouj_ghwnd, &ouj_wpPrev);
        SetWindowLong(ouj_ghwnd, GWL_STYLE, ouj_dwStyle | WS_OVERLAPPEDWINDOW);
        SetWindowPos(ouj_ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);
    }
}


int initialize(void)
{
    //function declaration
    void printGLInfo(void);
    void resize(int, int);

    //variable declarations
    PIXELFORMATDESCRIPTOR ouj_pfd;
    int ouj_iPixelFormatIndex = 0;

    //code
    //pixel for mat discrapted initilize
    ZeroMemory((void*)&ouj_pfd, sizeof(PIXELFORMATDESCRIPTOR));
    ouj_pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    ouj_pfd.nVersion = 1;
    ouj_pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_COMPOSITION | PFD_DOUBLEBUFFER;
    ouj_pfd.iPixelType = PFD_TYPE_RGBA;
    ouj_pfd.cColorBits = 32;
    ouj_pfd.cRedBits = 8;
    ouj_pfd.cGreenBits = 8;
    ouj_pfd.cBlueBits = 8;
    ouj_pfd.cAlphaBits = 8;

    // GET DC
    ouj_ghdc = GetDC(ouj_ghwnd);
    if (ouj_ghdc == NULL)
    {
        fprintf(ouj_gpFile, "getdc function dc function failed ");
        return(-1);
    }

    //matching format index using hdc and pfd
    ouj_iPixelFormatIndex = ChoosePixelFormat(ouj_ghdc, &ouj_pfd);
    if (ouj_iPixelFormatIndex == 0)
    {
        fprintf(ouj_gpFile, "choice Pixel format function failed ");
        return(-2);
    }


    //seclect a pixel format of found index
    if (SetPixelFormat(ouj_ghdc, ouj_iPixelFormatIndex, &ouj_pfd) == FALSE)
    {
        fprintf(ouj_gpFile, "SetPixelFormat format function failed ");
        return(-3);
    }
     
  
    //create rendaring concept using hdc 
    ouj_ghrc = wglCreateContext(ouj_ghdc);
    if (ouj_ghrc == NULL)
    {
        fprintf(ouj_gpFile, "wglCreateContext function failed ");
        return(-4);
    }

    //make this rendaring context that current context
    if (wglMakeCurrent(ouj_ghdc, ouj_ghrc) == FALSE)
    {
        fprintf(ouj_gpFile, "wglMakeCurrent function failed ");
        return(-5);
    }

    //printfGL Info
    printGLInfo();

    //from hear on words open gl code start
    //tell opengl to choice the color to clear the screen
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    //wormup resize
    resize(WIN_WIDTH, WIN_HIGTH);

    return(0);
}


void printGLInfo(void)
{
    //code

    //printf opengl information
    fprintf(ouj_gpFile, "opengl information");
    fprintf(ouj_gpFile, "******************\n");
    fprintf(ouj_gpFile, "openGL Vender %s\n", glGetString(GL_VENDOR));
    fprintf(ouj_gpFile, "openGL Renderer %s\n", glGetString(GL_RENDERER));
    fprintf(ouj_gpFile, "openGL Version %s\n", glGetString(GL_VERSION));
    fprintf(ouj_gpFile, "******************\n");


    
}

void resize(int width, int height)
{
    //code
    if (height <= 0)
    {
        height = 1;
    }

    //set the view port
    glViewport(0, 0 ,(GLsizei)width, (GLsizei)height);
    
    //set matrix Pojection mode
    glMatrixMode(GL_PROJECTION);// MATRIX CHA MODE PROJECTION LA THAEV

    //SET TO IDENTITY MATRIX
    glLoadIdentity();

    //set  orthographi projection
    gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);


}

void display(void)
{
    //clear openGL buffers
    glClear(GL_COLOR_BUFFER_BIT);

   //Astro text call
    Astromedicomp_Text();
   

    //swap the Buffers
    SwapBuffers(ouj_ghdc);
    
}

void update(void)
{
    //code


    

}
void uninitilize(void)
{
    //function declaration
    void togglefullscreen(void);

    //code
    //if full screen user is 
    if (ouj_gbFullScreen == TRUE)
    {
        togglefullscreen();
        ouj_gbFullScreen = FALSE;
    }

        

    // make hdc as current context by relising rendatin context
    if (wglGetCurrentContext() == ouj_ghrc)
    {
        wglMakeCurrent(NULL, NULL);
        
    }

    //DELET THE REDARING CONTEXT
    if (ouj_ghrc)
    {
        wglDeleteContext(ouj_ghrc);
        ouj_ghrc = NULL;
       
    }

    //RELESE THE DC 
    if (ouj_ghdc)
    {
        ReleaseDC(ouj_ghwnd,ouj_ghdc);
       
    }

   



    // close the file
    if (ouj_gpFile)
    {
        fprintf(ouj_gpFile, "program Terminated sucessfully\n");
        fclose(ouj_gpFile);
        ouj_gpFile = NULL;
    }
 
}

// void Astromedicomp_Text(void)
// {
//      //set matrix to model view mode
//      glMatrixMode(GL_MODELVIEW);
    
   
//      //SET TO IDENTITY MATRIX
//      glLoadIdentity();
 
//      //translet triangle back word by Z
//      glTranslatef(0.0f, 0.0f, -3.0f);
 
//      Astro_A(-1.63f,-0.17f,120);
//      Astro_S(-1.35f, 0.01f, 60);
//      Astro_T(-1.1f, -0.17f, 120);
//      Astro_R(-0.9f, 0.02f, 60);
//      Astro_O(-0.59f, -0.195f, 127);
//      Astro_M(-0.26f, -0.16f, 115);
//      Astro_E(-0.05f, -0.16f, 115);
//      Astro_D(0.296f, -0.16f, 115);
//      Astro_I(0.46f, -0.15f, 115);
//      Astro_C(1.072f, -0.16f, 115);
//      Astro_OO(1.25f, -0.17f, 120);
//      Astro_MM(1.56f, -0.16f, 110);
//      Astro_P(1.79f, 0.03f, 60);
// }

// void Astro_A(float x_pos, float y_pos, float percent)
// {
//          //***************************************************A*****************************************
//     glBegin(GL_TRIANGLE_STRIP);
//     {
//         glColor4f(1.0f, 0.4f, 0.0f, 0.1);

//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.096f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.075f,percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.080f,percent) + x_pos, VALUE_FROM_PERCENT(0.05f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.05f, percent) + x_pos, VALUE_FROM_PERCENT(0.1f, percent) + y_pos, 0.0f);
//        glVerteouj_x3f(VALUE_FROM_PERCENT(-0.056f, percent) + x_pos, VALUE_FROM_PERCENT(0.15f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.025f,percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.016f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.33f, percent) + y_pos, 0.0f);
       



//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.12f, percent) + x_pos, VALUE_FROM_PERCENT( 0.0f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.075f, percent) + x_pos, VALUE_FROM_PERCENT( 0.0f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.092f, percent) + x_pos, VALUE_FROM_PERCENT( 0.05f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.05f, percent) + x_pos, VALUE_FROM_PERCENT( 0.1f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.068f, percent) + x_pos, VALUE_FROM_PERCENT( 0.15f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.026f, percent) + x_pos, VALUE_FROM_PERCENT( 0.2f,  percent) + y_pos,0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.026f, percent) + x_pos, VALUE_FROM_PERCENT( 0.3f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.0f,  percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT( 0.33f,  percent) + y_pos,0.0f);


        
       
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.05f,percent) + x_pos, VALUE_FROM_PERCENT( 0.1f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.042f,percent) + x_pos, VALUE_FROM_PERCENT( 0.13f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.025f,percent) + x_pos, VALUE_FROM_PERCENT( 0.1f,  percent) + y_pos,0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.0f,percent) + x_pos, VALUE_FROM_PERCENT( 0.13f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.025f,percent) + x_pos, VALUE_FROM_PERCENT( 0.1f,  percent) + y_pos,0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.042f,percent) + x_pos, VALUE_FROM_PERCENT( 0.13f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.05f,percent) + x_pos, VALUE_FROM_PERCENT( 0.1f,  percent) + y_pos,0.0f);

//     }
//     glEnd();

//     glBegin(GL_TRIANGLE_STRIP);
//     {
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.116f,percent) + x_pos, VALUE_FROM_PERCENT( 0.0f,percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.08f,percent) + x_pos, VALUE_FROM_PERCENT( -0.01f,percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.08f,percent) + x_pos, VALUE_FROM_PERCENT( 0.0f, percent) + y_pos,0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.06f,percent) + x_pos, VALUE_FROM_PERCENT( 0.0f, percent) + y_pos,0.0f);

//     }
//     glEnd();

//     glBegin(GL_TRIANGLE_STRIP);
//     {

//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.06f,percent) + x_pos, VALUE_FROM_PERCENT( 0.0f, percent) + y_pos,0.0f);

//        glVerteouj_x3f(VALUE_FROM_PERCENT(0.1f, percent) + x_pos, VALUE_FROM_PERCENT(-0.015f,percent) + y_pos, 0.0f);

//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.1f,percent) + x_pos, VALUE_FROM_PERCENT( 0.0f, percent) + y_pos,0.0f);

//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.14f,percent) + x_pos, VALUE_FROM_PERCENT( 0.0f,percent) + y_pos, 0.0f);
        
//     }
//     glEnd();
    
// }


// void Astro_S(float x_pos, float y_pos, float percent)
// {


//     float t = 0.0f;
//     int i = 0;

//     struct ouj_Curve ouj_curve1;
//     struct ouj_Curve ouj_curve2;

//     //co-ordinate x,y
//     ouj_curve1.ouj_x1 = 0.08f;
//     ouj_curve1.ouj_x2 = -0.32f;
//     ouj_curve1.ouj_x3 = -0.29f;
//     ouj_curve1.ouj_x4 = 0.0f;

//     ouj_curve1.ouj_y1 = 0.35f;
//     ouj_curve1.ouj_y2 = 0.3f;
//     ouj_curve1.ouj_y3 = 0.08f;
//     ouj_curve1.ouj_y4 = 0.0f;

//     ouj_curve2.ouj_x1 = 0.05f;
//     ouj_curve2.ouj_x2 = -0.24f;
//     ouj_curve2.ouj_x3 = -0.22f;
//     ouj_curve2.ouj_x4 = 0.0f;

//     ouj_curve2.ouj_y1 = 0.3f;
//     ouj_curve2.ouj_y2 = 0.3f;
//     ouj_curve2.ouj_y3 = 0.08f;
//     ouj_curve2.ouj_y4 = 0.05f;


//     for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
//     {
//         Cat1[i] = (((pow(1 - t, 3)) *  ouj_curve1.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve1.ouj_x2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve1.ouj_x3)) + ((pow(t, 3)) *  ouj_curve1.ouj_x4));
//         Cbt1[i] = (((pow(1 - t, 3)) *  ouj_curve1.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve1.ouj_y2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve1.ouj_y3)) + ((pow(t, 3)) *  ouj_curve1.ouj_y4));
//     }

//     for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
//     {
//         Cat2[i] = (((pow(1 - t, 3)) *  ouj_curve2.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve2.ouj_x2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve2.ouj_x3)) + ((pow(t, 3)) *  ouj_curve2.ouj_x4));
//         Cbt2[i] = (((pow(1 - t, 3)) *  ouj_curve2.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve2.ouj_y2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve2.ouj_y3)) + ((pow(t, 3)) *  ouj_curve2.ouj_y4));
//     }



//     glColor4f(1.0f, 0.4f, 0.0f, 0.1);
//     glBegin(GL_TRIANGLE_STRIP);
//     {
//         for (i = 0; i < 100; i++)
//         {
//             glVerteouj_x3f(VALUE_FROM_PERCENT(Cat1[i], percent) + x_pos, VALUE_FROM_PERCENT(Cbt1[i], percent) + y_pos, 0.0f);
//             glVerteouj_x3f(VALUE_FROM_PERCENT(Cat2[i], percent) + x_pos, VALUE_FROM_PERCENT(Cbt2[i], percent) + y_pos, 0.0f);

//         }
//     }
//     glEnd();

//     struct ouj_Curve ouj_curve3;
//     struct ouj_Curve ouj_curve4;
 
//     //Co-ordinate x,y 
//     ouj_curve3.ouj_x1 = -0.01f;
//     ouj_curve3.ouj_x2 = 0.32f;
//     ouj_curve3.ouj_x3 = 0.29f;
//     ouj_curve3.ouj_x4 = -0.07f;


//     ouj_curve3.ouj_y1 = 0.05f;
//     ouj_curve3.ouj_y2 = -0.03f;
//     ouj_curve3.ouj_y3 = -0.3f;
//     ouj_curve3.ouj_y4 = -0.35f;

//     ouj_curve4.ouj_x1 = -0.01f;
//     ouj_curve4.ouj_x2 = 0.24f;
//     ouj_curve4.ouj_x3 = 0.22f;
//     ouj_curve4.ouj_x4 = -0.05f;

//     ouj_curve4.ouj_y1 = -0.0f;
//     ouj_curve4.ouj_y2 = -0.08f;
//     ouj_curve4.ouj_y3 = -0.3f;
//     ouj_curve4.ouj_y4= -0.3f;

//     for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
//     {
//         Cct1[i] = (((pow(1 - t, 3)) *  ouj_curve3.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve3.ouj_x2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve3.ouj_x3)) + ((pow(t, 3)) *  ouj_curve3.ouj_x4));
//         Cdt1[i] = (((pow(1 - t, 3)) *  ouj_curve3.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve3.ouj_y2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve3.ouj_y3)) + ((pow(t, 3)) *  ouj_curve3.ouj_y4));
//     }

//     for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
//     {
//         Cct2[i] = (((pow(1 - t, 3)) * ouj_curve4.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve4.ouj_x2)) + ((3 * (pow(t, 2) * (1 - t)) * ouj_curve4.ouj_x3)) + ((pow(t, 3)) * ouj_curve4.ouj_x4));
//         Cdt2[i] = (((pow(1 - t, 3)) * ouj_curve4.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve4.ouj_y2)) + ((3 * (pow(t, 2) * (1 - t)) * ouj_curve4.ouj_y3)) + ((pow(t, 3)) * ouj_curve4.ouj_y4));
//     }


//     glColor4f(1.0f, 0.4f, 0.0f, 0.1);
//     glBegin(GL_TRIANGLE_STRIP);
//     {
//         for (i = 0; i < 100; i++)
//         {
//             glVerteouj_x3f(VALUE_FROM_PERCENT(Cct1[i], percent) + x_pos, VALUE_FROM_PERCENT(Cdt1[i], percent) + y_pos, 0.0f);
//             glVerteouj_x3f(VALUE_FROM_PERCENT(Cct2[i], percent) + x_pos, VALUE_FROM_PERCENT(Cdt2[i], percent) + y_pos, 0.0f);
//         }
//     }
//     glEnd();


//     glBegin(GL_TRIANGLE_STRIP);
//     {
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.04f, percent) + x_pos, VALUE_FROM_PERCENT(-0.3f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.06f, percent) + x_pos, VALUE_FROM_PERCENT(-0.35f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.12f, percent) + x_pos, VALUE_FROM_PERCENT(-0.28f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.18f, percent) + x_pos, VALUE_FROM_PERCENT(-0.25f, percent) + y_pos, 0.0f);



//     }
//     glEnd();

//     glBegin(GL_TRIANGLE_STRIP);
//     {
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.05f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.12f, percent) + x_pos, VALUE_FROM_PERCENT(0.295f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.16f, percent) + x_pos, VALUE_FROM_PERCENT(0.26f, percent) + y_pos, 0.0f);




//     }
//     glEnd(); 
// }
    
// void Astro_T(float x_pos, float y_pos, float percent)
// {


//     glColor4f(1.0f, 0.4f, 0.0f, 0.1);
//     //***************************************************T*****************************************
//     glBegin(GL_TRIANGLE_STRIP);
//     {
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.02f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.02f, percent) + x_pos, VALUE_FROM_PERCENT(0.05f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos, VALUE_FROM_PERCENT(0.1f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.02f, percent) + x_pos, VALUE_FROM_PERCENT(0.15f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.02f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
//     }
//     glEnd();

   

   

//     //T chi top side
//     glBegin(GL_TRIANGLE_STRIP);
//     {
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.09f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.09f, percent) + x_pos, VALUE_FROM_PERCENT(0.33f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.015f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.015f, percent) + x_pos, VALUE_FROM_PERCENT(0.33f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.09f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.09f, percent) + x_pos, VALUE_FROM_PERCENT(0.33f, percent) + y_pos, 0.0f);

       

//     }
//     glEnd();

//     glBegin(GL_TRIANGLE_STRIP);
//     {
       
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.09f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.07f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.09f, percent) + x_pos, VALUE_FROM_PERCENT(0.27f, percent) + y_pos, 0.0f);

       

//     }
//     glEnd();

//     glBegin(GL_TRIANGLE_STRIP);
//     {
       
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.09f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.07f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.09f, percent) + x_pos, VALUE_FROM_PERCENT(0.27f, percent) + y_pos, 0.0f);

       

//     }
//     glEnd();

//     glBegin(GL_TRIANGLE_STRIP);
//     {
       
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.035f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.0f, percent) + x_pos, VALUE_FROM_PERCENT(-0.015f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.035f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);

       

//     }
//     glEnd();

// }
   
// void Astro_R(float x_pos, float y_pos, float percent)
// {
   

//     float t = 0.0f;
//     int i = 0;
    
//     struct ouj_Curve ouj_curve5;

//     struct ouj_Curve ouj_curve6;

//     //co-ordinate x,y
//     ouj_curve5.ouj_x1 = 0.0f;
//     ouj_curve5.ouj_y1 = 0.35f;
//     ouj_curve5.ouj_x2 = 0.5f;
//     ouj_curve5.ouj_y2 = 0.32f;
//     ouj_curve5.ouj_x3 = 0.04f;
//     ouj_curve5.ouj_y3 = 0.01f;
//     ouj_curve5.ouj_x4 = 0.0f;
//     ouj_curve5.ouj_y4 = 0.0f;

//     ouj_curve6.ouj_x1 = 0.0f;
//     ouj_curve6.ouj_y1 = 0.3f;
//     ouj_curve6.ouj_x2 = 0.25f;
//     ouj_curve6.ouj_y2 = 0.32f;
//     ouj_curve6.ouj_x3 = 0.02f;
//     ouj_curve6.ouj_y3 = 0.03f;
//     ouj_curve6.ouj_x4 = 0.0f;
//     ouj_curve6.ouj_y4 = 0.05f;

//     for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
//     {
//         Cet1[i] = (((pow(1 - t, 3)) * ouj_curve5.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve5.ouj_x2)) + ((3 * (pow(t, 2) * (1-t)) * ouj_curve5.ouj_x3)) + ((pow(t, 3)) * ouj_curve5.ouj_x4));
//         Cft1[i] = (((pow(1 - t, 3)) * ouj_curve5.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve5.ouj_y2)) + ((3 * (pow(t, 2) * (1-t)) * ouj_curve5.ouj_y3)) + ((pow(t, 3)) * ouj_curve5.ouj_y4));
//     }

//     for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
//     {
//          Cet2[i] = (((pow(1 - t, 3)) * ouj_curve6.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve6.ouj_x2)) + ((3 * (pow(t, 2) * (1-t)) * ouj_curve6.ouj_x3)) + ((pow(t, 3)) * ouj_curve6.ouj_x4));
//          Cft2[i] = (((pow(1 - t, 3)) * ouj_curve6.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve6.ouj_y2)) + ((3 * (pow(t, 2) * (1-t)) * ouj_curve6.ouj_y3)) + ((pow(t, 3)) * ouj_curve6.ouj_y4));
//      }

//      glColor4f(1.0f, 0.4f, 0.0f, 0.1);
//     glBegin(GL_TRIANGLE_STRIP);
//     {
//         for (i = 0; i < 100; i++)
//         {
//             glVerteouj_x3f(VALUE_FROM_PERCENT(Cet1[i], percent) + x_pos, VALUE_FROM_PERCENT(Cft1[i], percent) + y_pos, 0.0f);
//             glVerteouj_x3f(VALUE_FROM_PERCENT(Cet2[i], percent) + x_pos, VALUE_FROM_PERCENT(Cft2[i], percent) + y_pos, 0.0f);
//         }
//     }
//     glEnd();

//     glBegin(GL_TRIANGLE_STRIP);
//     {
//         glColor4f(1.0f, 0.4f, 0.0f, 0.1);
//         glVerteouj_x3f( VALUE_FROM_PERCENT(-0.06f,percent)+ x_pos, VALUE_FROM_PERCENT( -0.35f,percent)+ y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.0f,percent) + x_pos, VALUE_FROM_PERCENT(-0.35f,percent)+ y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.06f,percent)+ x_pos ,VALUE_FROM_PERCENT(0.1f,percent) + y_pos,0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.0f,percent)+ x_pos, VALUE_FROM_PERCENT( 0.2f,percent) + y_pos,0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.06f,percent)+x_pos , VALUE_FROM_PERCENT( 0.35f,percent)+ y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.0f,percent)+x_pos,   VALUE_FROM_PERCENT(0.35f,percent)+ y_pos, 0.0f);

      
        
//     }
//     glEnd();
//     glBegin(GL_TRIANGLE_STRIP);
//     {
//         glVerteouj_x3f( VALUE_FROM_PERCENT(-0.079f,percent)+ x_pos, VALUE_FROM_PERCENT( -0.35f,percent)+ y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.023f,percent) + x_pos, VALUE_FROM_PERCENT(-0.37f,percent)+ y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.023f,percent)+ x_pos ,VALUE_FROM_PERCENT(-0.35f,percent) + y_pos,0.0f); 
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.024f,percent) + x_pos, VALUE_FROM_PERCENT(-0.35f,percent)+ y_pos, 0.0f);

      
        
//     }
//     glEnd();

//     glBegin(GL_TRIANGLE_STRIP);
//     {
//         glVerteouj_x3f( VALUE_FROM_PERCENT(-0.07f,percent)+ x_pos, VALUE_FROM_PERCENT(0.35f,percent)+ y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.1f,percent) + x_pos, VALUE_FROM_PERCENT(0.35f,percent)+ y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.06f,percent)+ x_pos ,VALUE_FROM_PERCENT(0.31f,percent) + y_pos,0.0f); 
    

      
        
//     }
//     glEnd();

//     glBegin(GL_TRIANGLE_STRIP);
//     {
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.0001f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.05f, percent) + x_pos, VALUE_FROM_PERCENT(0.025f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.2f, percent) + x_pos, VALUE_FROM_PERCENT(-0.25f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(-0.35f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.4f, percent) + x_pos, VALUE_FROM_PERCENT(-0.45f, percent) + y_pos, 0.0f);
//         //glVerteouj_x3f(VALUE_FROM_PERCENT(0.5f, percent) + x_pos, VALUE_FROM_PERCENT(-0.5f, percent) + y_pos, 0.0f);
       
            



//     }
//     glEnd();
// }

// void Astro_O(float x_pos, float y_pos, float percent)
// {


//     float t = 0.0f;
//     int i = 0;

//     struct ouj_Curve ouj_curve7;
//     struct ouj_Curve ouj_curve8;
   
    
//     //co-ordinate x,y
//     ouj_curve7.ouj_x1 = 0.0f;
//     ouj_curve7.ouj_x2 = -0.15f;
//     ouj_curve7.ouj_x3 = -0.15f;
//     ouj_curve7.ouj_x4 = 0.02f;

//     ouj_curve7.ouj_y1 = 0.34f;
//     ouj_curve7.ouj_y2 = 0.32f;
//     ouj_curve7.ouj_y3 = 0.03f;
//     ouj_curve7.ouj_y4= 0.0f;

//     ouj_curve8.ouj_x1 = 0.0f;
//     ouj_curve8.ouj_x2 = -0.1f;
//     ouj_curve8.ouj_x3 = -0.1f;
//     ouj_curve8.ouj_x4 = 0.02f;

//     ouj_curve8.ouj_y1 = 0.3f;
//     ouj_curve8.ouj_y2 = 0.32f;
//     ouj_curve8.ouj_y3 = 0.05f;
//     ouj_curve8.ouj_y4 = 0.03f;


//     for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
//     {
//         Cgt1[i] = (((pow(1 - t, 3)) * ouj_curve7.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve7.ouj_x2)) + ((3 * (pow(t, 2) * (1 - t)) * ouj_curve7.ouj_x3)) + ((pow(t, 3)) * ouj_curve7.ouj_x4));
//         Cht1[i] = (((pow(1 - t, 3)) * ouj_curve7.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve7.ouj_y2)) + ((3 * (pow(t, 2) * (1 - t)) * ouj_curve7.ouj_y3)) + ((pow(t, 3)) * ouj_curve7.ouj_y4));
//     }

//     for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
//     {
//         Cgt2[i] = (((pow(1 - t, 3)) * ouj_curve8.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve8.ouj_x2)) + ((3 * (pow(t, 2) * (1 - t)) * ouj_curve8.ouj_x3)) + ((pow(t, 3)) * ouj_curve8.ouj_x4));
//         Cht2[i] = (((pow(1 - t, 3)) * ouj_curve8.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve8.ouj_y2)) + ((3 * (pow(t, 2) * (1 - t)) * ouj_curve8.ouj_y3)) + ((pow(t, 3)) * ouj_curve8.ouj_y4));
//     }



//     glColor4f(1.0f, 0.4f, 0.0f, 0.1);
//     glBegin(GL_TRIANGLE_STRIP);
//     {
//         for (i = 0; i < 100; i++)
//         {
//             glVerteouj_x3f(VALUE_FROM_PERCENT(Cgt1[i], percent) + x_pos, VALUE_FROM_PERCENT(Cht1[i], percent) + y_pos, 0.0f);
//             glVerteouj_x3f(VALUE_FROM_PERCENT(Cgt2[i], percent) + x_pos, VALUE_FROM_PERCENT(Cht2[i], percent) + y_pos, 0.0f);

//         }
//     }
//     glEnd();

//     struct ouj_Curve ouj_curve9;
//     struct ouj_Curve ouj_curve10;

//     //Co-ordinate x,y 
//     ouj_curve9.ouj_x1 = 0.0f;
//     ouj_curve9.ouj_x2 = 0.15f;
//     ouj_curve9.ouj_x3 = 0.15f;
//     ouj_curve9.ouj_x4 = 0.0f;

//     ouj_curve9.ouj_y1 = 0.34f;
//     ouj_curve9.ouj_y2 = 0.3f;
//     ouj_curve9.ouj_y3 = 0.03f;
//     ouj_curve9.ouj_y4 = 0.0f;

//     ouj_curve10.ouj_x1 = 0.0f;
//     ouj_curve10.ouj_x2 = 0.1f;
//     ouj_curve10.ouj_x3 = 0.1f;
//     ouj_curve10.ouj_x4 = 0.0f;

//     ouj_curve10.ouj_y1 = 0.3f;
//     ouj_curve10.ouj_y2 = 0.3f;
//     ouj_curve10.ouj_y3 = 0.05f;
//     ouj_curve10.ouj_y4 = 0.03f;

//     for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
//     {
//         Cit1[i] = (((pow(1 - t, 3)) *  ouj_curve9.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve9.ouj_x2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve9.ouj_x3)) + ((pow(t, 3)) *  ouj_curve9.ouj_x4));
//         Cjt1[i] = (((pow(1 - t, 3)) *  ouj_curve9.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve9.ouj_y2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve9.ouj_y3)) + ((pow(t, 3)) *  ouj_curve9.ouj_y4));
//     }

//     for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
//     {
//         Cit2[i] = (((pow(1 - t, 3)) *  ouj_curve10.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve10.ouj_x2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve10.ouj_x3)) + ((pow(t, 3)) *  ouj_curve10.ouj_x4));
//         Cjt2[i] = (((pow(1 - t, 3)) *  ouj_curve10.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve10.ouj_y2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve10.ouj_y3)) + ((pow(t, 3)) *  ouj_curve10.ouj_y4));
//     }


//     glColor4f(1.0f, 0.4f, 0.0f, 0.1);
//     glBegin(GL_TRIANGLE_STRIP);
//     {
//         for (i = 0; i < 100; i++)
//         {
//             glVerteouj_x3f(VALUE_FROM_PERCENT(Cit1[i], percent) + x_pos, VALUE_FROM_PERCENT(Cjt1[i], percent) + y_pos, 0.0f);
//             glVerteouj_x3f(VALUE_FROM_PERCENT(Cit2[i], percent) + x_pos, VALUE_FROM_PERCENT(Cjt2[i], percent) + y_pos, 0.0f);
//         }
//     }
//     glEnd();
// }
// void Astro_M(float x_pos, float y_pos, float percent)

// {
    
//     glColor4f(1.0f, 0.4f, 0.0f, 0.1);
//         //***************************************************M*****************************************
//     glBegin(GL_TRIANGLE_STRIP);//left
//     {
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.12f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.12f, percent) + x_pos, VALUE_FROM_PERCENT(0.15f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.12f, percent) + x_pos, VALUE_FROM_PERCENT(0.25f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.12f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
//     }
//     glEnd();
//     glBegin(GL_TRIANGLE_STRIP);
//     {
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.29f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.03f, percent) + x_pos, VALUE_FROM_PERCENT(0.29f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.03f, percent) + x_pos, VALUE_FROM_PERCENT(0.24f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.24f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);
        
//     }
//     glEnd();

//     glBegin(GL_TRIANGLE_STRIP);//right
//     {
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.12f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.12f, percent) + x_pos, VALUE_FROM_PERCENT(0.15f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.12f, percent) + x_pos, VALUE_FROM_PERCENT(0.25f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.12f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
//     }
//     glEnd();
//     glBegin(GL_TRIANGLE_STRIP);
//     {
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.29f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.03f, percent) + x_pos, VALUE_FROM_PERCENT(0.29f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.03f, percent) + x_pos, VALUE_FROM_PERCENT(0.24f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.24f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);
        
//     }
//     glEnd();

//     glBegin(GL_TRIANGLE_STRIP);//left
//     {
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.14f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.1f, percent) + x_pos, VALUE_FROM_PERCENT(-0.015f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.1f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.06f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
      
//     }
//     glEnd();
//     glBegin(GL_TRIANGLE_STRIP);
//     {
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.14f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.1f, percent) + x_pos, VALUE_FROM_PERCENT(-0.015f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.1f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.06f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
      
//     }
     
//     glEnd();
   
// }
// void Astro_E(float x_pos, float y_pos, float percent)
// {


//     glColor4f(1.0f, 0.4f, 0.0f, 0.1);
//     //***************************************************E*****************************************
//     glBegin(GL_TRIANGLE_STRIP);
//     {
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.1f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.15f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.25f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
//     }
//     glEnd();
//     glBegin(GL_TRIANGLE_STRIP);
//     {
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.32f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.1f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.15f, percent) + x_pos, VALUE_FROM_PERCENT(0.32f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.2f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.23f, percent) + x_pos, VALUE_FROM_PERCENT(0.32f, percent) + y_pos, 0.0f);
//         //glVerteouj_x3f(VALUE_FROM_PERCENT(0.31f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
//     }
//     glEnd();
//     glBegin(GL_TRIANGLE_STRIP);
//     {
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.16f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.1f, percent) + x_pos, VALUE_FROM_PERCENT(0.16f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.13f, percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.15f, percent) + x_pos, VALUE_FROM_PERCENT(0.16f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.15f, percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);

        
//     }
//     glEnd();
//     glBegin(GL_TRIANGLE_STRIP);
//     {
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT(0.035f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.1f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.15f, percent) + x_pos, VALUE_FROM_PERCENT(0.035f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.2f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.23f, percent) + x_pos, VALUE_FROM_PERCENT(0.035f, percent) + y_pos, 0.0f);
//         //glVerteouj_x3f(VALUE_FROM_PERCENT(0.31f, percent) + x_pos, VALUE_FROM_PERCENT(0.05f, percent) + y_pos, 0.0f);


//     }
//     glEnd();
// }
// void Astro_D(float x_pos, float y_pos, float percent)
// {
   

//     float t = 0.0f;
//     int i = 0;

//     struct ouj_Curve ouj_curve11;
//     struct ouj_Curve ouj_curve12;

//     //co-ordinate x,y
//     //co-ordinate x,y
//     ouj_curve11.ouj_x1 = 0.0f;
//     ouj_curve11.ouj_x2 = 0.25f;
//     ouj_curve11.ouj_x3 = 0.20f;
//     ouj_curve11.ouj_x4 =- 0.01f;


//     ouj_curve11.ouj_y1 = 0.35f;
//     ouj_curve11.ouj_y2 = 0.3f;
//     ouj_curve11.ouj_y3 = 0.08f;
//     ouj_curve11.ouj_y4 = 0.0f;

//     ouj_curve12.ouj_x1 = 0.0f;
//     ouj_curve12.ouj_x2 = 0.19f;
//     ouj_curve12.ouj_x3 = 0.17f;
//     ouj_curve12.ouj_x4 = -0.01f;

//     ouj_curve12.ouj_y1 = 0.3f;
//     ouj_curve12.ouj_y2 = 0.3f;
//     ouj_curve12.ouj_y3 = 0.08f;
//     ouj_curve12.ouj_y4 = 0.04f;


//     for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
//     {
        
//         Ckt1[i] = (((pow(1 - t, 3)) *  ouj_curve11.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve11.ouj_x2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve11.ouj_x3)) + ((pow(t, 3)) *  ouj_curve11.ouj_x4));
//         Clt1[i] = (((pow(1 - t, 3)) *  ouj_curve11.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve11.ouj_y2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve11.ouj_y3)) + ((pow(t, 3)) *  ouj_curve11.ouj_y4));
//     }

//     for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
//     {
//         Ckt2[i] = (((pow(1 - t, 3)) *  ouj_curve12.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve12.ouj_x2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve12.ouj_x3)) + ((pow(t, 3)) *  ouj_curve12.ouj_x4));
//         Clt2[i] = (((pow(1 - t, 3)) *  ouj_curve12.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve12.ouj_y2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve12.ouj_y3)) + ((pow(t, 3)) *  ouj_curve12.ouj_y4));
//     }

//     glColor4f(1.0f, 0.4f, 0.0f, 0.1);
//     glBegin(GL_TRIANGLE_STRIP);
//     {
//         for (i = 0; i < 100; i++)
//         {
//             glVerteouj_x3f(VALUE_FROM_PERCENT(Ckt1[i], percent) + x_pos, VALUE_FROM_PERCENT(Clt1[i], percent) + y_pos, 0.0f);
//             glVerteouj_x3f(VALUE_FROM_PERCENT(Ckt2[i], percent) + x_pos, VALUE_FROM_PERCENT(Clt2[i], percent) + y_pos, 0.0f);
//         }
//     }
//     glEnd();


//     // ubhi line
//     glBegin(GL_TRIANGLE_STRIP);
//     {
//         glColor4f(1.0f, 0.4f, 0.0f, 0.1);
//         //Verteouj_x3f( VALUE_FROM_PERCENT(-0.055f,percent)+ x_pos, VALUE_FROM_PERCENT( -0.35f,percent)+ y_pos, 0.0f);
//        //glVerteouj_x3f(VALUE_FROM_PERCENT(0.0f,percent) + x_pos, VALUE_FROM_PERCENT(-0.35f,percent)+ y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.03f,percent)+ x_pos ,VALUE_FROM_PERCENT(0.0f,percent) + y_pos,0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.0f,percent)+ x_pos, VALUE_FROM_PERCENT( 0.0f,percent) + y_pos,0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.03f,percent)+x_pos , VALUE_FROM_PERCENT( 0.35f,percent)+ y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.0f,percent)+x_pos,   VALUE_FROM_PERCENT(0.35f,percent)+ y_pos, 0.0f);

      
        
//     }
//     glEnd();

//     //top head
//     glBegin(GL_TRIANGLE_STRIP);
//     {
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.03f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.06f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.03f, percent) + x_pos, VALUE_FROM_PERCENT(0.33f, percent) + y_pos, 0.0f);




//     }
//     glEnd();

//     //top head
//     glBegin(GL_TRIANGLE_STRIP);
//     {
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.03f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.06f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.03f, percent) + x_pos, VALUE_FROM_PERCENT(0.02f, percent) + y_pos, 0.0f);




//     }
//     glEnd();
// }
// void Astro_I(float x_pos, float y_pos, float percent)


// {


//     glColor4f(1.0f, 0.4f, 0.0f, 0.1);
//     //***************************************************I*****************************************
//     glBegin(GL_TRIANGLE_STRIP);
//     {
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.15f, percent) + x_pos, VALUE_FROM_PERCENT(0.032f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.19f, percent) + x_pos, VALUE_FROM_PERCENT(0.032f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.15f, percent) + x_pos, VALUE_FROM_PERCENT(0.1f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.19f, percent) + x_pos, VALUE_FROM_PERCENT(0.15f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.15f, percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.19f, percent) + x_pos, VALUE_FROM_PERCENT(0.25f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.15f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.19f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
//     }
//     glEnd();

//     //E chi varachi side
//     glBegin(GL_TRIANGLE_STRIP);
//     {
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.06f, percent) + x_pos, VALUE_FROM_PERCENT(0.33f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.06f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.1f, percent) + x_pos, VALUE_FROM_PERCENT(0.33f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.15f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.25f, percent) + x_pos, VALUE_FROM_PERCENT(0.33f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(0.33f, percent) + y_pos, 0.0f);
//         //glVerteouj_x3f(VALUE_FROM_PERCENT(0.31f, percent) + x_pos, VALUE_FROM_PERCENT(0.33f, percent) + y_pos, 0.0f);
//     }
//     glEnd();

   

//     //E chi Khalachi  side
//     glBegin(GL_TRIANGLE_STRIP);
//     {
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.06f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.06f, percent) + x_pos, VALUE_FROM_PERCENT(0.03f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.1f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.15f, percent) + x_pos, VALUE_FROM_PERCENT(0.03f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.25f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(0.03f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);


//     }
//     glEnd();

//      //T chi Corner side
//      glBegin(GL_TRIANGLE_STRIP);
//      {
//          glVerteouj_x3f(VALUE_FROM_PERCENT(0.06f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
//          glVerteouj_x3f(VALUE_FROM_PERCENT(0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
//          glVerteouj_x3f(VALUE_FROM_PERCENT(0.06f, percent) + x_pos, VALUE_FROM_PERCENT(0.27f, percent) + y_pos, 0.0f);
//      }
//      glEnd();

//       //T chi Corner side
//       glBegin(GL_TRIANGLE_STRIP);
//       {
//           glVerteouj_x3f(VALUE_FROM_PERCENT(0.06f, percent) + x_pos, VALUE_FROM_PERCENT(0.03f, percent) + y_pos, 0.0f);
//           glVerteouj_x3f(VALUE_FROM_PERCENT(0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.03f, percent) + y_pos, 0.0f);
//           glVerteouj_x3f(VALUE_FROM_PERCENT(0.06f, percent) + x_pos, VALUE_FROM_PERCENT(0.05f, percent) + y_pos, 0.0f);
 
         
//       glEnd();

//        //T chi Corner side
//      glBegin(GL_TRIANGLE_STRIP);
//      {
//          glVerteouj_x3f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
//          glVerteouj_x3f(VALUE_FROM_PERCENT(0.28f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
//          glVerteouj_x3f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(0.27f, percent) + y_pos, 0.0f);

        
//      }
//      glEnd();

      

//        //T chi Corner side
//      glBegin(GL_TRIANGLE_STRIP);
//      {
//          glVerteouj_x3f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(0.03f, percent) + y_pos, 0.0f);
//          glVerteouj_x3f(VALUE_FROM_PERCENT(0.28f, percent) + x_pos, VALUE_FROM_PERCENT(0.03f, percent) + y_pos, 0.0f);
//          glVerteouj_x3f(VALUE_FROM_PERCENT(0.3f, percent) + x_pos, VALUE_FROM_PERCENT(0.05f, percent) + y_pos, 0.0f);
//      }
//      glEnd();

//     }  
// }
// void Astro_C(float x_pos, float y_pos, float percent)
// {
   

//     float t = 0.0f;
//     int i = 0;

//     struct ouj_Curve ouj_curve13;
//     struct ouj_Curve ouj_curve14;
    
//     //co-ordinate x,y
//     ouj_curve13.ouj_x1 = 0.0f;
//     ouj_curve13.ouj_x2 = -0.3f;
//     ouj_curve13.ouj_x3 = -0.27f;
//     ouj_curve13.ouj_x4 = 0.0f;

   
//     ouj_curve13.ouj_y1 = 0.35f;
//     ouj_curve13.ouj_y2 = 0.3f;
//     ouj_curve13.ouj_y3 = 0.08f;
//     ouj_curve13.ouj_y4 = 0.0f;

//     ouj_curve14.ouj_x1 = 0.0f;
//     ouj_curve14.ouj_x2 = -0.22f;
//     ouj_curve14.ouj_x3 = -0.20f;
//     ouj_curve14.ouj_x4 = 0.0f;

//     ouj_curve14.ouj_y1 = 0.3f;
//     ouj_curve14.ouj_y2 = 0.3f;
//     ouj_curve14.ouj_y3 = 0.08f;
//     ouj_curve14.ouj_y4 = 0.05f;


//     for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
//     {
//         Cmt1[i] = (((pow(1 - t, 3)) *  ouj_curve13.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve13.ouj_x2)) + ((3 * (pow(t, 2) *(1-t)) *  ouj_curve13.ouj_x3)) + ((pow(t, 3)) *  ouj_curve13.ouj_x4));
//         Cnt1[i] = (((pow(1 - t, 3)) *  ouj_curve13.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve13.ouj_y2)) + ((3 * (pow(t, 2)*(1-t)) *  ouj_curve13.ouj_y3)) + ((pow(t, 3)) *  ouj_curve13.ouj_y4));
//     }

//     for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
//     {
//          Cmt2[i] = (((pow(1 - t, 3)) *  ouj_curve14.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve14.ouj_x2)) + ((3 * (pow(t, 2) *(1-t)) *  ouj_curve14.ouj_x3)) + ((pow(t, 3)) *  ouj_curve14.ouj_x4));
//          Cnt2[i] = (((pow(1 - t, 3)) *  ouj_curve14.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve14.ouj_y2)) + ((3 * (pow(t, 2) *(1-t)) *  ouj_curve14.ouj_y3)) + ((pow(t, 3)) *  ouj_curve14.ouj_y4));
//      }

//      glColor4f(1.0f, 0.4f, 0.0f, 0.1);
//     glBegin(GL_TRIANGLE_STRIP);
//     {
//         for (i = 0; i < 100; i++)
//         {
//             glVerteouj_x3f(VALUE_FROM_PERCENT(Cmt1[i], percent) + x_pos, VALUE_FROM_PERCENT(Cnt1[i], percent) + y_pos, 0.0f);
//             glVerteouj_x3f(VALUE_FROM_PERCENT(Cmt2[i], percent) + x_pos, VALUE_FROM_PERCENT(Cnt2[i], percent) + y_pos, 0.0f);
//         }
//     }
//     glEnd();

    

// }
// void Astro_OO(float x_pos, float y_pos, float percent)
// {


//     float t = 0.0f;
//     int i = 0;

//     struct ouj_Curve ouj_curve15;
//     struct ouj_Curve ouj_curve16;
   
//     //co-ordinate x,y
//     ouj_curve15.ouj_x1 = 0.0f;
//     ouj_curve15.ouj_x2 = -0.15f;
//     ouj_curve15.ouj_x3 = -0.15f;
//     ouj_curve15.ouj_x4 = 0.02f;

//     ouj_curve15.ouj_y1 = 0.34f;
//     ouj_curve15.ouj_y2 = 0.32f;
//     ouj_curve15.ouj_y3 = 0.03f;
//     ouj_curve15.ouj_y4 = 0.0f;

//     ouj_curve16.ouj_x1 = 0.0f;
//     ouj_curve16.ouj_x2 = -0.1f;
//     ouj_curve16.ouj_x3 = -0.1f;
//     ouj_curve16.ouj_x4 = 0.02f;

//     ouj_curve16.ouj_y1 = 0.3f;
//     ouj_curve16.ouj_y2 = 0.32f;
//     ouj_curve16.ouj_y3 = 0.05f;
//     ouj_curve16.ouj_y4 = 0.03f;

  


//     for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
//     {
//         Cot1[i] = (((pow(1 - t, 3)) * ouj_curve15.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve15.ouj_x2)) + ((3 * (pow(t, 2) * (1 - t)) * ouj_curve15.ouj_x3)) + ((pow(t, 3)) * ouj_curve15.ouj_x4));
//         Cpt1[i] = (((pow(1 - t, 3)) * ouj_curve15.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve15.ouj_y2)) + ((3 * (pow(t, 2) * (1 - t)) * ouj_curve15.ouj_y3)) + ((pow(t, 3)) * ouj_curve15.ouj_y4));
//     }

//     for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
//     {
//         Cot2[i] = (((pow(1 - t, 3)) * ouj_curve16.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve16.ouj_x2)) + ((3 * (pow(t, 2) * (1 - t)) * ouj_curve16.ouj_x3)) + ((pow(t, 3)) * ouj_curve16.ouj_x4));
//         Cpt2[i] = (((pow(1 - t, 3)) * ouj_curve16.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve16.ouj_y2)) + ((3 * (pow(t, 2) * (1 - t)) * ouj_curve16.ouj_y3)) + ((pow(t, 3)) * ouj_curve16.ouj_y4));
//     }



//     glColor4f(1.0f, 0.4f, 0.0f, 0.1);
//     glBegin(GL_TRIANGLE_STRIP);
//     {
//         for (i = 0; i < 100; i++)
//         {
//             glVerteouj_x3f(VALUE_FROM_PERCENT(Cot1[i], percent) + x_pos, VALUE_FROM_PERCENT(Cpt1[i], percent) + y_pos, 0.0f);
//             glVerteouj_x3f(VALUE_FROM_PERCENT(Cot2[i], percent) + x_pos, VALUE_FROM_PERCENT(Cpt2[i], percent) + y_pos, 0.0f);

//         }
//     }
//     glEnd();

//     struct ouj_Curve ouj_curve17;
//     struct ouj_Curve ouj_curve18;

//  //Co-ordinate x,y 
//  ouj_curve17.ouj_x1 = 0.0f;
//  ouj_curve17.ouj_x2 = 0.15f;
//  ouj_curve17.ouj_x3 = 0.15f;
//  ouj_curve17.ouj_x4 = 0.0f;

//  ouj_curve17.ouj_y1 = 0.34f;
//  ouj_curve17.ouj_y2 = 0.3f;
//  ouj_curve17.ouj_y3 = 0.03f;
//  ouj_curve17.ouj_y4 = 0.0f;

//  ouj_curve18.ouj_x1 = 0.0f;
//  ouj_curve18.ouj_x2 = 0.1f;
//  ouj_curve18.ouj_x3 = 0.1f;
//  ouj_curve18.ouj_x4 = 0.0f;

//  ouj_curve18.ouj_y1 = 0.3f;
//  ouj_curve18.ouj_y2 = 0.3f;
//  ouj_curve18.ouj_y3 = 0.05f;
//  ouj_curve18.ouj_y4 = 0.03f;

   
//     for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
//     {
//         Cqt1[i] = (((pow(1 - t, 3)) *  ouj_curve17.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve17.ouj_x2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve17.ouj_x3)) + ((pow(t, 3)) *  ouj_curve17.ouj_x4));
//         Crt1[i] = (((pow(1 - t, 3)) *  ouj_curve17.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve17.ouj_y2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve17.ouj_y3)) + ((pow(t, 3)) *  ouj_curve17.ouj_y4));
//     }

//     for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
//     {
//         Cqt2[i] = (((pow(1 - t, 3)) *  ouj_curve18.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve18.ouj_x2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve18.ouj_x3)) + ((pow(t, 3)) *  ouj_curve18.ouj_x4));
//         Crt2[i] = (((pow(1 - t, 3)) *  ouj_curve18.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) *  ouj_curve18.ouj_y2)) + ((3 * (pow(t, 2) * (1 - t)) *  ouj_curve18.ouj_y3)) + ((pow(t, 3)) *  ouj_curve18.ouj_y4));
//     }


//     glColor4f(1.0f, 0.4f, 0.0f, 0.1);
//     glBegin(GL_TRIANGLE_STRIP);
//     {
//         for (i = 0; i < 100; i++)
//         {
//             glVerteouj_x3f(VALUE_FROM_PERCENT(Cqt1[i], percent) + x_pos, VALUE_FROM_PERCENT(Crt1[i], percent) + y_pos, 0.0f);
//             glVerteouj_x3f(VALUE_FROM_PERCENT(Cqt2[i], percent) + x_pos, VALUE_FROM_PERCENT(Crt2[i], percent) + y_pos, 0.0f);
//         }
//     }
//     glEnd();

// }
// void Astro_MM(float x_pos, float y_pos, float percent)
// {
//     glColor4f(1.0f, 0.4f, 0.0f, 0.1);
//      //***************************************************M*****************************************
//      glBegin(GL_TRIANGLE_STRIP);//left
//      {
//          glVerteouj_x3f(VALUE_FROM_PERCENT(-0.12f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
//          glVerteouj_x3f(VALUE_FROM_PERCENT(-0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
//          glVerteouj_x3f(VALUE_FROM_PERCENT(-0.12f, percent) + x_pos, VALUE_FROM_PERCENT(0.15f, percent) + y_pos, 0.0f);
//          glVerteouj_x3f(VALUE_FROM_PERCENT(-0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);
//          glVerteouj_x3f(VALUE_FROM_PERCENT(-0.12f, percent) + x_pos, VALUE_FROM_PERCENT(0.25f, percent) + y_pos, 0.0f);
//          glVerteouj_x3f(VALUE_FROM_PERCENT(-0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
//          glVerteouj_x3f(VALUE_FROM_PERCENT(-0.12f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
//          glVerteouj_x3f(VALUE_FROM_PERCENT(-0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
//      }
//      glEnd();
//      glBegin(GL_TRIANGLE_STRIP);
//      {
//          glVerteouj_x3f(VALUE_FROM_PERCENT(-0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
//          glVerteouj_x3f(VALUE_FROM_PERCENT(-0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.29f, percent) + y_pos, 0.0f);
//          glVerteouj_x3f(VALUE_FROM_PERCENT(-0.03f, percent) + x_pos, VALUE_FROM_PERCENT(0.29f, percent) + y_pos, 0.0f);
//          glVerteouj_x3f(VALUE_FROM_PERCENT(-0.03f, percent) + x_pos, VALUE_FROM_PERCENT(0.24f, percent) + y_pos, 0.0f);
//          glVerteouj_x3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.24f, percent) + y_pos, 0.0f);
//          glVerteouj_x3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);
         
//      }
//      glEnd();
 
//      glBegin(GL_TRIANGLE_STRIP);//right
//      {
//          glVerteouj_x3f(VALUE_FROM_PERCENT(0.12f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
//          glVerteouj_x3f(VALUE_FROM_PERCENT(0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
//          glVerteouj_x3f(VALUE_FROM_PERCENT(0.12f, percent) + x_pos, VALUE_FROM_PERCENT(0.15f, percent) + y_pos, 0.0f);
//          glVerteouj_x3f(VALUE_FROM_PERCENT(0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);
//          glVerteouj_x3f(VALUE_FROM_PERCENT(0.12f, percent) + x_pos, VALUE_FROM_PERCENT(0.25f, percent) + y_pos, 0.0f);
//          glVerteouj_x3f(VALUE_FROM_PERCENT(0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.3f, percent) + y_pos, 0.0f);
//          glVerteouj_x3f(VALUE_FROM_PERCENT(0.12f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
//          glVerteouj_x3f(VALUE_FROM_PERCENT(0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
//      }
//      glEnd();
//      glBegin(GL_TRIANGLE_STRIP);
//      {
//          glVerteouj_x3f(VALUE_FROM_PERCENT(0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.35f, percent) + y_pos, 0.0f);
//          glVerteouj_x3f(VALUE_FROM_PERCENT(0.08f, percent) + x_pos, VALUE_FROM_PERCENT(0.29f, percent) + y_pos, 0.0f);
//          glVerteouj_x3f(VALUE_FROM_PERCENT(0.03f, percent) + x_pos, VALUE_FROM_PERCENT(0.29f, percent) + y_pos, 0.0f);
//          glVerteouj_x3f(VALUE_FROM_PERCENT(0.03f, percent) + x_pos, VALUE_FROM_PERCENT(0.24f, percent) + y_pos, 0.0f);
//          glVerteouj_x3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.24f, percent) + y_pos, 0.0f);
//          glVerteouj_x3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(0.2f, percent) + y_pos, 0.0f);
         
//      }
//      glEnd();

//      glBegin(GL_TRIANGLE_STRIP);//left
//      {
//          glVerteouj_x3f(VALUE_FROM_PERCENT(-0.14f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
//          glVerteouj_x3f(VALUE_FROM_PERCENT(-0.1f, percent) + x_pos, VALUE_FROM_PERCENT(-0.015f, percent) + y_pos, 0.0f);
//          glVerteouj_x3f(VALUE_FROM_PERCENT(-0.1f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
//          glVerteouj_x3f(VALUE_FROM_PERCENT(-0.06f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
       
//      }
//      glEnd();
//      glBegin(GL_TRIANGLE_STRIP);
//      {
//          glVerteouj_x3f(VALUE_FROM_PERCENT(0.14f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
//          glVerteouj_x3f(VALUE_FROM_PERCENT(0.1f, percent) + x_pos, VALUE_FROM_PERCENT(-0.015f, percent) + y_pos, 0.0f);
//          glVerteouj_x3f(VALUE_FROM_PERCENT(0.1f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
//          glVerteouj_x3f(VALUE_FROM_PERCENT(0.06f, percent) + x_pos, VALUE_FROM_PERCENT(0.0f, percent) + y_pos, 0.0f);
       
//      }
      
//      glEnd();

     
// }
//  void Astro_P(float x_pos, float y_pos, float percent)
// {
   

//     float t = 0.0f;
//     int i = 0;

//     struct ouj_Curve ouj_curve19;
//     struct ouj_Curve ouj_curve20;
//     //co-ordinate x,y
//     ouj_curve19.ouj_x1 = 0.0f;
//     ouj_curve19.ouj_y1 = 0.35f;
//     ouj_curve19.ouj_x2 = 0.5f;
//     ouj_curve19.ouj_y2 = 0.25f;
//     ouj_curve19.ouj_x3 = 0.04f;
//     ouj_curve19.ouj_y3 = 0.01f;
//     ouj_curve19.ouj_x4 = 0.0f;
//     ouj_curve19.ouj_y4 = 0.0f;

//     ouj_curve20.ouj_x1 = 0.0f;
//     ouj_curve20.ouj_y1 = 0.3f;
//     ouj_curve20.ouj_x2 = 0.25f;
//     ouj_curve20.ouj_y2 = 0.25f;
//     ouj_curve20.ouj_x3 = 0.02f;
//     ouj_curve20.ouj_y3 = 0.03f;
//     ouj_curve20.ouj_x4 = 0.0f;
//     ouj_curve20.ouj_y4 = 0.05f;

//     for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
//     {
//         Cst1[i] = (((pow(1 - t, 3)) * ouj_curve19.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve19.ouj_x2)) + ((3 * (pow(t, 2) * (1-t)) * ouj_curve19.ouj_x3)) + ((pow(t, 3)) * ouj_curve19.ouj_x4));
//         Ctt1[i] = (((pow(1 - t, 3)) * ouj_curve19.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve19.ouj_y2)) + ((3 * (pow(t, 2) * (1-t)) * ouj_curve19.ouj_y3)) + ((pow(t, 3)) * ouj_curve19.ouj_y4));
      
//     }

//     for (t = 0.0f, i = 0; t <= 1.0f; t = t + 0.01f, i++)
//     {
//         Cst2[i] = (((pow(1 - t, 3)) * ouj_curve20.ouj_x1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve20.ouj_x2)) + ((3 * (pow(t, 2) * (1-t)) * ouj_curve20.ouj_x3)) + ((pow(t, 3)) * ouj_curve20.ouj_x4));
//         Ctt2[i] = (((pow(1 - t, 3)) * ouj_curve20.ouj_y1) + ((3 * t) * ((pow(1 - t, 2)) * ouj_curve20.ouj_y2)) + ((3 * (pow(t, 2) * (1-t)) * ouj_curve20.ouj_y3)) + ((pow(t, 3)) * ouj_curve20.ouj_y4));
//      }

//      glColor4f(1.0f, 0.4f, 0.0f, 0.1);
//     glBegin(GL_TRIANGLE_STRIP);
//     {
//         for (i = 0; i < 100; i++)
//         {
//             glVerteouj_x3f(VALUE_FROM_PERCENT(Cst1[i], percent) + x_pos, VALUE_FROM_PERCENT(Ctt1[i], percent) + y_pos, 0.0f);
//             glVerteouj_x3f(VALUE_FROM_PERCENT(Cst2[i], percent) + x_pos, VALUE_FROM_PERCENT(Ctt2[i], percent) + y_pos, 0.0f);
//         }
//     }
//     glEnd();

//     glBegin(GL_TRIANGLE_STRIP);
//     {
//         glColor4f(1.0f, 0.4f, 0.0f, 0.1);
//         glVerteouj_x3f( VALUE_FROM_PERCENT(-0.065f,percent)+ x_pos, VALUE_FROM_PERCENT( -0.35f,percent)+ y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.0f,percent) + x_pos, VALUE_FROM_PERCENT(-0.35f,percent)+ y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.065f,percent)+ x_pos ,VALUE_FROM_PERCENT(0.1f,percent) + y_pos,0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.0f,percent)+ x_pos, VALUE_FROM_PERCENT( 0.2f,percent) + y_pos,0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.065f,percent)+x_pos , VALUE_FROM_PERCENT( 0.35f,percent)+ y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.0f,percent)+x_pos,   VALUE_FROM_PERCENT(0.35f,percent)+ y_pos, 0.0f);

      
        
//     }
//     glEnd();
//     glBegin(GL_TRIANGLE_STRIP);
//     {
//         glVerteouj_x3f( VALUE_FROM_PERCENT(-0.079f,percent)+ x_pos, VALUE_FROM_PERCENT( -0.35f,percent)+ y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.023f,percent) + x_pos, VALUE_FROM_PERCENT(-0.37f,percent)+ y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.023f,percent)+ x_pos ,VALUE_FROM_PERCENT(-0.35f,percent) + y_pos,0.0f); 
//         glVerteouj_x3f(VALUE_FROM_PERCENT(0.024f,percent) + x_pos, VALUE_FROM_PERCENT(-0.35f,percent)+ y_pos, 0.0f);

      
        
//     }
//     glEnd();

//     glBegin(GL_TRIANGLE_STRIP);
//     {
//         glVerteouj_x3f( VALUE_FROM_PERCENT(-0.065f,percent)+ x_pos, VALUE_FROM_PERCENT(0.35f,percent)+ y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.1f,percent) + x_pos, VALUE_FROM_PERCENT(0.35f,percent)+ y_pos, 0.0f);
//         glVerteouj_x3f(VALUE_FROM_PERCENT(-0.065f,percent)+ x_pos ,VALUE_FROM_PERCENT(0.31f,percent) + y_pos,0.0f); 
    

      
        
//     }
//     glEnd();

// }