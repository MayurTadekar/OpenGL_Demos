

// HEADERS
#include <Windows.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/vmath/vmath.h>

#include "common.h"

#include "macros.h"

#include "Shader.h"
#include "Program.h"

using namespace vmath;

#include "square.h"
#include "triangle.h"
#include "sphere.h"
#include "cube.h"
#include "pyramid.h"

#include "multilight.h"

#include "AtmosphericScatteringProgram.h"

#include "FrameBufferObject.h"

#include "camera.hpp"

#include "imgui.h"
#include "backends/imgui_impl_win32.h"
#include "backends/imgui_impl_opengl3.h"

// MACROS
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

#define LoadIdentity(matrix)       \
    {                              \
        matrix = mat4::identity(); \
    }

enum DrawShape
{
    DRAW_NONE = 0,
    DRAW_TRIANGLE,
    DRAW_SQUARE,
    DRAW_SPHERE,
    DRAW_CUBE,
    DRAW_PYRAMID,
};

DrawShape drawShape = DRAW_SQUARE;

// VARIABLES
HWND ghwnd;
HDC ghdc;
HGLRC ghrc;
DWORD dwStyle;
bool bFullscreen = false;
bool bActivate = true;
FILE *gpLogFile = NULL;
WINDOWPLACEMENT wpPrev;

GLuint vao;
GLuint vbo_position;
GLuint vbo_color;

GLuint mMatrixUniform;
GLuint vMatrixUniform;
GLuint pMatrixUniform;

mat4 perspectiveProjectionMatrix;

float x_pos = 0.0f;
float y_pos = 0.0f;

Triangle *triangle = NULL;
Square *square = NULL;
Sphere *sphere = NULL;
Cube *cube = NULL;
Pyramid *pyramid = NULL;

float rotateAngle = 0.0f;

MultiLight *mprogram = nullptr;
AtmosphericScatteringProgram *cprogram = nullptr;

// Camera camera(vmath::vec3(90000.0f, 0.0f, 90000.0f),
// Camera camera(vmath::vec3(0.0f, 0.0f, 200000.0f),
Camera camera(vmath::vec3(0.0f, 51000.0f, 500.0f),
              vmath::vec3(0.0f, 1.0f, 0.0f));

FrameBufferObject *basicFbo;

float xpos = 1000.0f;
float ypos = 0.0f;
float zpos = 0.0f;

float boundsScale = 0.5f;

// FUNCTION SIGNATURE
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// FUNCTIONS
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{

    // FUNCTION SIGNATURE
    void Display(void);
    void Update(void);
    void Initialize(void);
    void Uninitialize(void);

    // VARIABLES
    HWND hwnd;
    MSG msg;
    TCHAR szAppName[] = TEXT("CWindow");
    WNDCLASSEX wndcls;
    RECT rcDesktop;
    bool bDone = false;

    // CODE
    if (0 != fopen_s(&gpLogFile, "log.txt", "w"))
    {
        MessageBox(NULL, TEXT("Log File Cannot be opened"), TEXT("ERROR"), MB_ICONERROR);
        exit(1);
    }
    else
    {
        fprintf(gpLogFile, "Log File Opened Successfully\n");
        fflush(gpLogFile);
        fclose(gpLogFile);
        gpLogFile = NULL;
    }

    wndcls.cbSize = sizeof(WNDCLASSEX);
    wndcls.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wndcls.cbClsExtra = 0;
    wndcls.cbWndExtra = 0;
    wndcls.lpfnWndProc = WndProc;
    wndcls.lpszClassName = szAppName;
    wndcls.lpszMenuName = NULL;
    wndcls.hInstance = hInstance;
    wndcls.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wndcls.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
    wndcls.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndcls.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClassEx(&wndcls);

    SystemParametersInfo(SPI_GETWORKAREA, 0, &rcDesktop, 0);

    hwnd = CreateWindowEx(WS_EX_APPWINDOW,
                          szAppName,
                          TEXT("Window"),
                          WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
                          rcDesktop.right / 2 - WIN_WIDTH / 2,
                          rcDesktop.bottom / 2 - WIN_HEIGHT / 2,
                          WIN_WIDTH,
                          WIN_HEIGHT,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    ghwnd = hwnd;

    Initialize();

    ShowWindow(hwnd, iCmdShow);
    SetForegroundWindow(hwnd);
    SetFocus(hwnd);

    while (!bDone)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message)
            {
                bDone = true;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            if (bActivate)
            {
                Display();
                Update();
            }
        }
    }
    Uninitialize();

    return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{

    // FUNCTION SIGNATURE
    void Resize(int, int);
    void Uninitialize(void);
    void ToggleFullscreen(void);

    // CODE
    switch (iMsg)
    {
    case WM_DESTROY:
        Uninitialize();
        PostQuitMessage(0);
        break;

    case WM_SETFOCUS:
        bActivate = true;
        break;

    case WM_KILLFOCUS:
        bActivate = false;
        break;

    case WM_SIZE:
        Resize(LOWORD(lParam), HIWORD(lParam));
        break;

    case WM_ERASEBKGND:
        return (0);

    case WM_CREATE:
        SetTimer(hwnd, 1234, 0, NULL);
        break;

    case WM_KEYDOWN:
        switch (LOWORD(wParam))
        {
        case 0x1B:
            DestroyWindow(hwnd);
            break;

        case 0x46:
        case 0x66:
            ToggleFullscreen();
            break;
        }
        break;

    case WM_CHAR:
        switch (LOWORD(wParam))
        {
        case '1':
            xpos += 0.1f;
            break;

        case '2':
            xpos -= 0.1f;
            break;

        case '3':
            ypos += 0.1f;
            break;

        case '4':
            ypos -= 0.1f;
            break;

        case '5':
            zpos += 0.1f;
            break;

        case '6':
            zpos -= 0.1f;
            break;

        case '7':
            boundsScale += 0.1f;
            break;

        case '8':
            boundsScale -= 0.1f;
            break;
        }
        break;
    }

    camera.HandleKeyboardMessages(iMsg, wParam, lParam);
    camera.HandleMouseMessages(iMsg, wParam, lParam);

    if (ImGui_ImplWin32_WndProcHandler(hwnd, iMsg, wParam, lParam))
        return true;

    return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void ToggleFullscreen(void)
{

    // VARIABLES
    MONITORINFO mi = {sizeof(MONITORINFO)};

    // CODE
    if (!bFullscreen)
    {
        dwStyle = GetWindowLong(ghwnd, GWL_STYLE);
        if (dwStyle & WS_OVERLAPPEDWINDOW)
        {
            if (GetWindowPlacement(ghwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
            {
                SetWindowLong(ghwnd, GWL_STYLE, dwStyle & (~WS_OVERLAPPEDWINDOW));
                SetWindowPos(ghwnd,
                             HWND_TOP,
                             mi.rcMonitor.left,
                             mi.rcMonitor.top,
                             mi.rcMonitor.right - mi.rcMonitor.left,
                             mi.rcMonitor.bottom - mi.rcMonitor.top,
                             SWP_FRAMECHANGED | SWP_NOZORDER);
            }
        }
        // ShowCursor(FALSE);
        bFullscreen = true;
    }
    else
    {
        SetWindowLong(ghwnd, GWL_STYLE, dwStyle & WS_OVERLAPPEDWINDOW);
        SetWindowPlacement(ghwnd, &wpPrev);
        SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER);
        ShowCursor(TRUE);
        bFullscreen = false;
    }
}

void Initialize(void)
{
    // FUNCTIONS
    void Resize(int, int);
    void Uninitialize(void);

    // VARIABLE
    PIXELFORMATDESCRIPTOR pfd;
    int iPixelIndex = 0;

    // CODE
    ghdc = GetDC(ghwnd);
    ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
    pfd.cRedBits = 8;
    pfd.cGreenBits = 8;
    pfd.cBlueBits = 8;
    pfd.cAlphaBits = 8;
    pfd.cDepthBits = 32;
    pfd.cColorBits = 32;

    iPixelIndex = ChoosePixelFormat(ghdc, &pfd);
    if (0 == iPixelIndex)
    {
        // ERROR_EXIT(gpLogFile, "ChoosePixelFormat() Failed", ghwnd);
        LOG_ENTRY("log.txt", "ChoosePixelFormat() Failed with error code: %d", GetLastError());
        Uninitialize();
    }

    if (FALSE == SetPixelFormat(ghdc, iPixelIndex, &pfd))
    {
        // ERROR_EXIT(gpLogFile, "SetPixelFormat() Failed", ghwnd);
        LOG_ENTRY("log.txt", "SetPixelFormat() Failed with error code: %d", GetLastError());
        Uninitialize();
    }

    ghrc = wglCreateContext(ghdc);
    if (NULL == ghrc)
    {
        // ERROR_EXIT(gpLogFile, "wglCreateContext() Failed", ghwnd);
        LOG_ENTRY("log.txt", "wglCreateContext() Failed with error code: %d", GetLastError());
        Uninitialize();
    }

    if (FALSE == wglMakeCurrent(ghdc, ghrc))
    {
        // ERROR_EXIT(gpLogFile, "wglMakeCurrent() Failed", ghwnd);
        LOG_ENTRY("log.txt", "wglMakeCurrent() Failed with error code: %d", GetLastError());
        Uninitialize();
    }

    GLenum glew_error = glewInit();
    if (GLEW_OK != glew_error)
    {
        Uninitialize();
        DestroyWindow(ghwnd);
    }

    // fprintf(gpLogFile, "GL_VENDOR: %s\n", glGetString(GL_VENDOR));
    LOG_ENTRY("log.txt", "GLEW Version: %s", glewGetString(GLEW_VERSION));

    // fprintf(gpLogFile, "GL_RENDERER: %s\n", glGetString(GL_RENDERER));
    LOG_ENTRY("log.txt", "OpenGL Renderer: %s", glGetString(GL_RENDERER));

    // fprintf(gpLogFile, "OpenGL Version: %s\n", glGetString(GL_VERSION));
    LOG_ENTRY("log.txt", "OpenGL Version: %s", glGetString(GL_VERSION));

    // fprintf(gpLogFile, "GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    LOG_ENTRY("log.txt", "GLSL Version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));

    GLint numExt;

    // glGetIntegerv(GL_NUM_EXTENSIONS, &numExt);
    // for (int i = 0; i < numExt; i++)
    // {
    //     fprintf(gpLogFile, "%s\n", glGetStringi(GL_EXTENSIONS, i));
    // }

    glEnable(GL_POINT_SIZE);
    glPointSize(5.0f);

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    glClearDepth(1.0f);

    glDepthFunc(GL_LEQUAL);

    glEnable(GL_DEPTH_TEST);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glShadeModel(GL_SMOOTH);

    perspectiveProjectionMatrix = mat4::identity();

    triangle = new Triangle();
    if (NULL == triangle)
    {
        fprintf(gpLogFile, "Triangle Object Creation Failed\n");
        Uninitialize();
        DestroyWindow(ghwnd);
    }
    triangle->Initialize();

    square = new Square();
    if (NULL == square)
    {
        fprintf(gpLogFile, "Square Object Creation Failed\n");
        Uninitialize();
        DestroyWindow(ghwnd);
    }
    square->Initialize();

    sphere = new Sphere();
    if (NULL == sphere)
    {
        fprintf(gpLogFile, "Sphere Object Creation Failed\n");
        Uninitialize();
        DestroyWindow(ghwnd);
    }
    sphere->Initialize();

    cube = new Cube();
    if (NULL == cube)
    {
        fprintf(gpLogFile, "Cube Object Creation Failed\n");
        Uninitialize();
        DestroyWindow(ghwnd);
    }
    cube->Initialize();

    pyramid = new Pyramid();
    if (NULL == pyramid)
    {
        fprintf(gpLogFile, "Pyramid Object Creation Failed\n");
        Uninitialize();
        DestroyWindow(ghwnd);
    }
    pyramid->Initialize();

    mprogram = new MultiLight();
    mprogram->Initialize();

    cprogram = new AtmosphericScatteringProgram();
    cprogram->Initialize();

    basicFbo = new FrameBufferObject(WIN_WIDTH / 2, WIN_HEIGHT / 2, GL_RGBA16F, GL_DEPTH_COMPONENT32F);
    basicFbo->Initialize();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    // Initialize ImGui for Win32 and OpenGL
    ImGui_ImplWin32_Init(ghwnd);
    ImGui_ImplOpenGL3_Init("#version 130"); // OpenGL version

    // Setup Dear ImGui style
    ImGui::StyleColorsDark(); // You can use other styles like ImGui::StyleColorsClassic();

    Resize(WIN_WIDTH, WIN_HEIGHT);
}

void Resize(int width, int height)
{

    // CODE
    if (height < 1)
        height = 1;

    glViewport(0, 0, (GLsizei)width, (GLsizei)height);

    if (basicFbo)
        basicFbo->Resize(width, height);

    perspectiveProjectionMatrix = perspective(45.0f, (float)width / (float)height, 1.0f, 10000.0f);
}

void Display(void)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    // VARIABLES
    mat4 modelMatrix;
    mat4 viewMatrix;

    // CODE

    LoadIdentity(viewMatrix);
    LoadIdentity(modelMatrix);

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ImGui::Begin("Values");
    {
        cprogram->DisplayIMGUI();
    }
    ImGui::End();

    if (cprogram)
    {
        // glEnable(GL_BLEND);
        glDisable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDepthMask(GL_FALSE);
        cprogram->StartProgram();

        viewMatrix = camera.GetViewMatrix();

        vmath::mat4 _viewMatrix = vmath::lookat(vmath::vec3(0.0f, 0.0f, 10.0f),
                                                vmath::vec3(0.0f, 0.0f, 0.0f),
                                                vmath::vec3(0.0f, 1.0f, 0.0f));

        // basicFbo->BindColorTexture(0);

        // basicFbo->BindDepthTexture(1);

        modelMatrix = vmath::translate(0.0f, 0.0f, 0.0f);

        cprogram->SetUniforms(perspectiveProjectionMatrix,
                              modelMatrix,
                              viewMatrix,
                              _viewMatrix,
                              camera.GetCameraPosition(),
                              //   vmath::vec3(0, 0, 10),
                              //   vmath::vec3(xpos, ypos, zpos),
                              0,
                              1,
                              vmath::vec3(xpos, ypos, zpos),
                              boundsScale);

        square->Display();

        cprogram->StopProgram();
        glDisable(GL_BLEND);
        glDepthMask(GL_TRUE);
    }

    // Render ImGui into OpenGL
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    SwapBuffers(ghdc);
}

void Update(void)
{
    // Code
    cprogram->Update();

    rotateAngle += 0.15f;
    if (rotateAngle >= 360.0f)
        rotateAngle = 0.0f;
}

void Uninitialize(void)
{

    // CODE

    if (vao)
    {
        glDeleteVertexArrays(1, &vao);
        vao = 0;
    }

    glUseProgram(0);

    if (bFullscreen)
    {
        SetWindowLong(ghwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
        SetWindowPlacement(ghwnd, &wpPrev);
        SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER);
        ShowCursor(TRUE);
        bFullscreen = false;
    }

    if (wglGetCurrentContext() == ghrc)
    {
        wglMakeCurrent(NULL, NULL);
    }

    if (ghrc)
    {
        wglDeleteContext(ghrc);
        ghrc = NULL;
    }

    if (ghdc)
    {
        ReleaseDC(ghwnd, ghdc);
        ghdc = NULL;
    }

    if (triangle)
    {
        triangle->Uninitialize();
        delete triangle;
        triangle = NULL;
    }

    if (square)
    {
        square->Uninitialize();
        delete square;
        square = NULL;
    }

    if (cube)
    {
        cube->Uninitialize();
        delete cube;
        cube = NULL;
    }

    if (sphere)
    {
        sphere->Uninitialize();
        delete sphere;
        sphere = NULL;
    }

    if (pyramid)
    {
        pyramid->Uninitialize();
        delete pyramid;
        pyramid = NULL;
    }

    if (basicFbo)
    {
        basicFbo->Uninitialize();
        delete basicFbo;
        basicFbo = NULL;
    }

    if (gpLogFile)
    {
        fclose(gpLogFile);
        gpLogFile = NULL;
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}
