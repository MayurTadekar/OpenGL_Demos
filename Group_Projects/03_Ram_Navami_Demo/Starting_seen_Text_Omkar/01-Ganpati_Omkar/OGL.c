// win32 headers
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

//OPENGL RELETED HEADER FILE
#include<gl/GL.h>
#include "OGL.h"
#include<gl/GLU.h>
#include<math.h>
#include"Ganpati_Text.h"


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
//object function declaration
void Ganpati_Text(void);
void Ganpati(float x_pos, float y_pos, float percent);
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

    Ganpati_Text();
   
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
/*
void Ganpati_Text(void)
{
    //set matrix to model view mode
    glMatrixMode(GL_MODELVIEW);
        
    
    //SET TO IDENTITY MATRIX
    glLoadIdentity();

    //translet triangle back word by Z
    glTranslatef(0.0f, 0.0f, -3.0f);


    Ganpati(0.0f, 0.0f, 150);




}

void Ganpati(float x_pos, float y_pos, float percent)
{
    glLineWidth(5.0f);
    glBegin(GL_LINES);//mukut
    {
        glColor4f(VALUE_FROM_PERCENT(1.0f,percent) + x_pos, VALUE_FROM_PERCENT( 0.0f,  percent) + y_pos, 0.0f,0.1f);
        glVertex2f(VALUE_FROM_PERCENT(-0.01f,percent) + x_pos, VALUE_FROM_PERCENT(  0.61f, percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(0.01f,percent) + x_pos, VALUE_FROM_PERCENT(  0.61f, percent) + y_pos);

        glColor4f(VALUE_FROM_PERCENT(1.0f,percent) + x_pos, VALUE_FROM_PERCENT( 0.0f, percent) + y_pos, 0.0f,0.1f);
        glVertex2f(VALUE_FROM_PERCENT(-0.04f,percent) + x_pos, VALUE_FROM_PERCENT(  0.59f, percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(0.04f,percent) + x_pos, VALUE_FROM_PERCENT(  0.59f, percent) + y_pos);

        glColor4f(VALUE_FROM_PERCENT(1.0f,percent) + x_pos, VALUE_FROM_PERCENT( 0.0f, percent) + y_pos, 0.0f,0.1f);
        glVertex2f(VALUE_FROM_PERCENT(-0.07f,percent) + x_pos, VALUE_FROM_PERCENT(  0.57f, percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(0.07f,percent) + x_pos, VALUE_FROM_PERCENT(  0.57f, percent) + y_pos);

        glColor4f(VALUE_FROM_PERCENT(1.0f,percent) + x_pos, VALUE_FROM_PERCENT( 0.0f, percent) + y_pos, 0.0f,0.1f);
        glVertex2f(VALUE_FROM_PERCENT(-0.1f,percent) + x_pos, VALUE_FROM_PERCENT(  0.55f, percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(0.1f,percent) + x_pos, VALUE_FROM_PERCENT(  0.55f, percent) + y_pos);

        glColor4f(VALUE_FROM_PERCENT(1.0f,percent) + x_pos, VALUE_FROM_PERCENT( 0.0f, percent) + y_pos, 0.0f,0.1f);
        glVertex2f(VALUE_FROM_PERCENT(-0.13f,percent) + x_pos, VALUE_FROM_PERCENT(  0.53f, percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(0.13f,percent) + x_pos, VALUE_FROM_PERCENT(  0.53f, percent) + y_pos);

       // glColor3f(VALUE_FROM_PERCENT(0.9f,percent) + x_pos, VALUE_FROM_PERCENT( 1.0f, percent) + y_pos, 1.0f);
        //glVertex2f(-0.02f, 0.46f);
        //glVertex2f(-0.01f, 0.44f);


    }
    glEnd();
   

   glBegin(GL_QUADS); //mukotha(chehara)
    {
        glColor4f(VALUE_FROM_PERCENT(1.0f,percent) + x_pos, VALUE_FROM_PERCENT( 0.0f, percent) + y_pos, 0.0f,0.1f);//chehara
        glVertex3f(VALUE_FROM_PERCENT(-0.1f, percent) + x_pos, VALUE_FROM_PERCENT( 0.51f, percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.08f, percent) + x_pos, VALUE_FROM_PERCENT( 0.51f, percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.08f, percent) + x_pos, VALUE_FROM_PERCENT( 0.2f, percent) + y_pos,.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.1f, percent) + x_pos, VALUE_FROM_PERCENT( 0.2f, percent) + y_pos,.0f);

        glColor4f(VALUE_FROM_PERCENT(1.0f,percent) + x_pos, VALUE_FROM_PERCENT( 0.0f, percent) + y_pos, 0.0f,0.1f);//sond
        glVertex3f(VALUE_FROM_PERCENT(-0.1f, percent) + x_pos, VALUE_FROM_PERCENT( 0.26f, percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.17f, percent) + x_pos, VALUE_FROM_PERCENT( 0.26f, percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.17f, percent) + x_pos, VALUE_FROM_PERCENT( 0.2f, percent) + y_pos,.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.1f, percent) + x_pos, VALUE_FROM_PERCENT( 0.2f, percent) + y_pos,.0f);

        glColor4f(VALUE_FROM_PERCENT(1.0f,percent) + x_pos, VALUE_FROM_PERCENT( 0.0f, percent) + y_pos, 0.0f,0.1f);//sond
        glVertex3f(VALUE_FROM_PERCENT(0.14f, percent) + x_pos, VALUE_FROM_PERCENT( 0.25f, percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.17f, percent) + x_pos, VALUE_FROM_PERCENT( 0.25f, percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.17f, percent) + x_pos, VALUE_FROM_PERCENT( 0.17f, percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.14f, percent) + x_pos, VALUE_FROM_PERCENT( 0.17f, percent) + y_pos,0.0f);

        glColor4f(VALUE_FROM_PERCENT(0.9f,percent) + x_pos, VALUE_FROM_PERCENT( 1.0f, percent) + y_pos, 1.0f,0.1f);// right eye
        glVertex3f(VALUE_FROM_PERCENT(-0.06f, percent) + x_pos, VALUE_FROM_PERCENT( 0.41f,percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.05f ,percent) + x_pos, VALUE_FROM_PERCENT( 0.42f,percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.04f, percent) + x_pos, VALUE_FROM_PERCENT( 0.41f,percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.05f, percent) + x_pos, VALUE_FROM_PERCENT( 0.40f,percent) + y_pos, 0.0f);

        glColor4f(VALUE_FROM_PERCENT(0.9f,percent) + x_pos, VALUE_FROM_PERCENT( 1.0f, percent) + y_pos, 1.0f,0.1f);// left eye
        glVertex3f(VALUE_FROM_PERCENT(0.03f, percent) + x_pos, VALUE_FROM_PERCENT( 0.41f, percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT( 0.42f, percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.05f, percent) + x_pos, VALUE_FROM_PERCENT( 0.41f, percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.04f, percent) + x_pos, VALUE_FROM_PERCENT( 0.40f, percent) + y_pos,0.0f);

        glColor4f(VALUE_FROM_PERCENT(1.0f,percent) + x_pos, VALUE_FROM_PERCENT( 0.0f, percent) + y_pos, 0.0f,0.1f);// right leg
        glVertex3f(VALUE_FROM_PERCENT(-0.055f, percent) + x_pos, VALUE_FROM_PERCENT( -0.15f,percent) + y_pos, 0.0f);//
        glVertex3f(VALUE_FROM_PERCENT(-0.0f, percent) + x_pos, VALUE_FROM_PERCENT( -0.1f, percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.0f, percent) + x_pos, VALUE_FROM_PERCENT( -0.18f,percent) + y_pos, 0.0f);//
        glVertex3f(VALUE_FROM_PERCENT(-0.055f, percent) + x_pos, VALUE_FROM_PERCENT( -0.27f,percent) + y_pos, 0.0f);//


        //glColor4f(VALUE_FROM_PERCENT(0.9f,percent) + x_pos, VALUE_FROM_PERCENT( 1.0f, percent) + y_pos, 1.0f,0.1f);// left leg
        glVertex3f(VALUE_FROM_PERCENT(0.07f, percent) + x_pos, VALUE_FROM_PERCENT( -0.19f,percent) + y_pos, 0.0f);//
        glVertex3f(VALUE_FROM_PERCENT(0.01f, percent) + x_pos, VALUE_FROM_PERCENT( -0.1f, percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.01f, percent) + x_pos, VALUE_FROM_PERCENT( -0.19f,percent) + y_pos, 0.0f);//
        glVertex3f(VALUE_FROM_PERCENT(0.07f, percent) + x_pos, VALUE_FROM_PERCENT( -0.26f,percent) + y_pos, 0.0f);//


    }
    glEnd();

    glBegin(GL_TRIANGLES);// 1 right side 2 left side kan
    {
        glColor4f(VALUE_FROM_PERCENT(1.0f,percent) + x_pos, VALUE_FROM_PERCENT( 0.0f, percent) + y_pos, 0.0f,0.1f);
        glVertex3f(VALUE_FROM_PERCENT(-0.29f, percent) + x_pos, VALUE_FROM_PERCENT( 0.51f,percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.11f, percent) + x_pos, VALUE_FROM_PERCENT( 0.51f,percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.11f, percent) + x_pos, VALUE_FROM_PERCENT( 0.2f, percent) + y_pos,0.0f);

        glColor4f(VALUE_FROM_PERCENT(1.0f,percent) + x_pos, VALUE_FROM_PERCENT( 0.0f, percent) + y_pos, 0.0f,0.1f);
        glVertex3f(VALUE_FROM_PERCENT(0.09f, percent) + x_pos, VALUE_FROM_PERCENT( 0.51f, percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.27f, percent) + x_pos, VALUE_FROM_PERCENT( 0.51f, percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.09f, percent) + x_pos, VALUE_FROM_PERCENT( 0.26f, percent) + y_pos,0.0f);

        glColor4f(VALUE_FROM_PERCENT(1.0f,percent) + x_pos, VALUE_FROM_PERCENT( 0.0f, percent) + y_pos, 0.0f,0.1f);//potacha bhag start(1)
        glVertex3f(VALUE_FROM_PERCENT(-0.19f, percent) + x_pos, VALUE_FROM_PERCENT( 0.19f,percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.165f, percent) + x_pos, VALUE_FROM_PERCENT( 0.26f,percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.115, percent) + x_pos, VALUE_FROM_PERCENT( 0.19f,percent) + y_pos, 0.0f);

        glColor4f(VALUE_FROM_PERCENT(1.0f,percent) + x_pos, VALUE_FROM_PERCENT( 0.0f, percent) + y_pos, 0.0f,0.1f);//2
        glVertex3f(VALUE_FROM_PERCENT(-0.19f, percent) + x_pos, VALUE_FROM_PERCENT( 0.19f,percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.115f, percent) + x_pos, VALUE_FROM_PERCENT( 0.19f,percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.115f, percent) + x_pos, VALUE_FROM_PERCENT( -0.04f,percent) + y_pos, 0.0f);

        glColor4f(VALUE_FROM_PERCENT(1.0f,percent) + x_pos, VALUE_FROM_PERCENT( 0.0f, percent) + y_pos, 0.0f,0.1f);//3
        glVertex3f(VALUE_FROM_PERCENT(-0.19f, percent) + x_pos, VALUE_FROM_PERCENT( 0.19f,percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.19f, percent) + x_pos, VALUE_FROM_PERCENT( -0.0f,percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.115f, percent) + x_pos, VALUE_FROM_PERCENT( -0.04f,percent) + y_pos, 0.0f);

        glColor4f(VALUE_FROM_PERCENT(1.0f,percent) + x_pos, VALUE_FROM_PERCENT( 0.0f, percent) + y_pos, 0.0f,0.1f);//4
        glVertex3f(VALUE_FROM_PERCENT(-0.115, percent) + x_pos, VALUE_FROM_PERCENT( 0.19f,percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.13f, percent) + x_pos, VALUE_FROM_PERCENT( 0.19f, percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(-0.115f, percent) + x_pos, VALUE_FROM_PERCENT( -0.04f,percent) + y_pos, 0.0f);

        glColor4f(VALUE_FROM_PERCENT(1.0f,percent) + x_pos, VALUE_FROM_PERCENT( 0.0f, percent) + y_pos, 0.0f,0.1f);//5
        glVertex3f(VALUE_FROM_PERCENT(-0.109f, percent) + x_pos, VALUE_FROM_PERCENT(-0.04f,percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.13f, percent) + x_pos, VALUE_FROM_PERCENT( 0.18f, percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.13f, percent) + x_pos, VALUE_FROM_PERCENT( -0.0f, percent) + y_pos,0.0f);

        glColor4f(VALUE_FROM_PERCENT(1.0f,percent) + x_pos, VALUE_FROM_PERCENT( 0.0f, percent) + y_pos, 0.0f,0.1f);//6
        glVertex3f(VALUE_FROM_PERCENT(-0.109f, percent) + x_pos, VALUE_FROM_PERCENT( -0.04f,percent) + y_pos, 0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.13f, percent) + x_pos, VALUE_FROM_PERCENT( -0.0f, percent) + y_pos,0.0f);
        glVertex3f(VALUE_FROM_PERCENT(0.0f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.08f, percent) + y_pos,0.0f);

        glColor4f(VALUE_FROM_PERCENT(1.0f,percent) + x_pos, VALUE_FROM_PERCENT( 0.0f, percent) + y_pos, 0.0f,0.1f);//7 right mandi(1)
        glVertex3f(VALUE_FROM_PERCENT(0.0f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.09f, percent) + y_pos,0.0f);//1
        glVertex3f(VALUE_FROM_PERCENT(-0.19f, percent) + x_pos, VALUE_FROM_PERCENT( -0.01f,percent) + y_pos, 0.0f);//2
        glVertex3f(VALUE_FROM_PERCENT(-0.19f, percent) + x_pos, VALUE_FROM_PERCENT( -0.27f,percent) + y_pos, 0.0f);//3

       // glColor3f(VALUE_FROM_PERCENT(0.9f,percent) + x_pos, VALUE_FROM_PERCENT( 0.2f, percent) + y_pos, 0.1f,0.1f);//7 right mandi(2)
        glVertex3f(VALUE_FROM_PERCENT(-0.27f, percent) + x_pos, VALUE_FROM_PERCENT( -0.01f,percent) + y_pos, 0.0f);//1
        glVertex3f(VALUE_FROM_PERCENT(-0.19f, percent) + x_pos, VALUE_FROM_PERCENT( -0.01f,percent) + y_pos, 0.0f);//2
        glVertex3f(VALUE_FROM_PERCENT(-0.19f, percent) + x_pos, VALUE_FROM_PERCENT( -0.27f,percent) + y_pos, 0.0f);//3

       // glColor3f(VALUE_FROM_PERCENT(0.9f,percent) + x_pos, VALUE_FROM_PERCENT( 0.2f, percent) + y_pos, 0.1f,0.1f);//7 right mandi(3)
        glVertex3f(VALUE_FROM_PERCENT(-0.27f, percent) + x_pos, VALUE_FROM_PERCENT( -0.01f,percent) + y_pos, 0.0f);//1
        glVertex3f(VALUE_FROM_PERCENT(-0.27f, percent) + x_pos, VALUE_FROM_PERCENT( -0.3f,percent) + y_pos, 0.0f);//2
        glVertex3f(VALUE_FROM_PERCENT(-0.19f, percent) + x_pos, VALUE_FROM_PERCENT( -0.27f,percent) + y_pos, 0.0f);//3

       // glColor3f(VALUE_FROM_PERCENT(0.9f,percent) + x_pos, VALUE_FROM_PERCENT( 0.2f, percent) + y_pos, 0.1f,0.1f);//7 left mandi(1)
        glVertex3f(VALUE_FROM_PERCENT(0.01f, percent) + x_pos, VALUE_FROM_PERCENT( -0.09f,percent) + y_pos, 0.0f);//1
        glVertex3f(VALUE_FROM_PERCENT(0.13f, percent) + x_pos, VALUE_FROM_PERCENT( -0.01f,percent) + y_pos, 0.0f);//2
        glVertex3f(VALUE_FROM_PERCENT(0.13f, percent) + x_pos, VALUE_FROM_PERCENT( -0.27f,percent) + y_pos, 0.0f);//3

        //glColor3f(VALUE_FROM_PERCENT(0.9f,percent) + x_pos, VALUE_FROM_PERCENT( 0.2f, percent) + y_pos, 0.1f,0.1f);//7 left mandi(2)
        glVertex3f(VALUE_FROM_PERCENT(0.13f, percent) + x_pos, VALUE_FROM_PERCENT( -0.01f,percent) + y_pos, 0.0f);//1
        glVertex3f(VALUE_FROM_PERCENT(0.24f, percent) + x_pos, VALUE_FROM_PERCENT( -0.01f,percent) + y_pos, 0.0f);//2
        glVertex3f(VALUE_FROM_PERCENT(0.13f, percent) + x_pos, VALUE_FROM_PERCENT( -0.27f,percent) + y_pos, 0.0f);//3

        //glColor3f(VALUE_FROM_PERCENT(0.9f,percent) + x_pos, VALUE_FROM_PERCENT( 0.2f, percent) + y_pos, 0.1f,0.1f);//7 left mandi(3)
        glVertex3f(VALUE_FROM_PERCENT(0.24f, percent) + x_pos, VALUE_FROM_PERCENT( -0.01f,percent) + y_pos, 0.0f);//1
        glVertex3f(VALUE_FROM_PERCENT(0.24f, percent) + x_pos, VALUE_FROM_PERCENT( -0.3f, percent) + y_pos,0.0f);//2
        glVertex3f(VALUE_FROM_PERCENT(0.13f, percent) + x_pos, VALUE_FROM_PERCENT( -0.27f,percent) + y_pos, 0.0f);//3



    }
    glEnd();

    glBegin(GL_POLYGON);
    {
        glColor4f(1.0f, 0.0f,0.0f,0.1f);
        glVertex2f(VALUE_FROM_PERCENT(-0.22f,percent) + x_pos, VALUE_FROM_PERCENT( 0.15f,percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(-0.27f,percent) + x_pos, VALUE_FROM_PERCENT( 0.12f,percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(-0.27f,percent) + x_pos, VALUE_FROM_PERCENT( 0.0f,percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(-0.22f,percent) + x_pos, VALUE_FROM_PERCENT( 0.0f,percent) + y_pos);
    }
    
    glEnd();

    glBegin(GL_POLYGON);
    {
        glColor4f(1.0f, 0.0f,0.0f,0.1f);
        glVertex2f(VALUE_FROM_PERCENT(-0.198f,percent) + x_pos, VALUE_FROM_PERCENT( 0.12f,percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(-0.22f,percent) + x_pos, VALUE_FROM_PERCENT( 0.09f,percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(-0.22f,percent) + x_pos, VALUE_FROM_PERCENT( 0.0f,percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(-0.198f,percent) + x_pos, VALUE_FROM_PERCENT( 0.0f,percent) + y_pos);
    }
    
    glEnd();

    
  
    glBegin(GL_POLYGON);
    {
        glColor4f(1.0f, 0.0f,0.0f,0.1f);
        glVertex2f(VALUE_FROM_PERCENT(0.14f,percent) + x_pos, VALUE_FROM_PERCENT( 0.03f,percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(0.16f,percent) + x_pos, VALUE_FROM_PERCENT( 0.0f,percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(0.22f,percent) + x_pos, VALUE_FROM_PERCENT( 0.0f,percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(0.24f,percent) + x_pos, VALUE_FROM_PERCENT( 0.03f,percent) + y_pos);
    }
    
    glEnd();

    glBegin(GL_TRIANGLES);
    {
        glColor4f(1.0f, 0.6f,0.1f,0.1f);
        glVertex2f(VALUE_FROM_PERCENT(0.14f,percent) + x_pos, VALUE_FROM_PERCENT( 0.04f,percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(0.19f,percent) + x_pos, VALUE_FROM_PERCENT( 0.1f,percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(0.24f,percent) + x_pos, VALUE_FROM_PERCENT( 0.04f,percent) + y_pos);
      
    }
    
    glEnd();
}

*/