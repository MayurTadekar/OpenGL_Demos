#define STB_IMAGE_IMPLEMENTATION
#include "./include/stb/stb_image.h"

#include "./include/common.h"

#include "./modules/Camera/Camera.h"
#include "./effects/Skybox/Skybox.h"
#include "./effects/Ocean/Ocean.h"

#define WIN_WIDTH  1280
#define WIN_HEIGHT 720
#define MYICON     101

HDC   ghdc  = NULL;
HGLRC ghrc  = NULL;
HWND  ghwnd = NULL;

BOOL  gbActive     = FALSE;
BOOL  gbFullscreen = FALSE;
BOOL  gbRotating   = FALSE;

DWORD             dwStyle  = 0;
WINDOWPLACEMENT   wpPrev   = { sizeof(WINDOWPLACEMENT) };

FILE *gpFILE        = NULL;
INT   g_iWinWidth   = WIN_WIDTH;
INT   g_iWinHeight  = WIN_HEIGHT;
float g_elapsedTime = 0.0f;

vmath::mat4 perspectiveProjectionMatrix;
Camera     *gpCamera  = NULL;
OceanParams gOcean;

LARGE_INTEGER gQPCFreq, gQPCStart;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void   ToggleFullScreen(void);
int    initialize(void);
void   resize(int, int);
void   display(void);
void   updateScene(void);
void   uninitialize(void);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
    CreateDirectoryA("Log", NULL);
    if (fopen_s(&gpFILE, "Log/Log.txt", "w") != 0)
    {
        MessageBox(NULL, TEXT("Cannot open Log/Log.txt"), TEXT("Error"), MB_OK | MB_ICONERROR);
        return 0;
    }
    LOG("Ocean Showcase: program start\n");

    WNDCLASSEX wc;
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInstance;
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = TEXT("OceanShowcase");
    wc.lpszMenuName  = NULL;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
    RegisterClassEx(&wc);

    int sw = GetSystemMetrics(SM_CXSCREEN);
    int sh = GetSystemMetrics(SM_CYSCREEN);
    int x  = (sw - WIN_WIDTH)  / 2;
    int y  = (sh - WIN_HEIGHT) / 2;

    HWND hwnd = CreateWindowEx(
        WS_EX_APPWINDOW,
        TEXT("OceanShowcase"),
        TEXT("Ocean trial for the final demo"),
        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
        x, y, WIN_WIDTH, WIN_HEIGHT,
        NULL, NULL, hInstance, NULL);
    ghwnd = hwnd;

    if (initialize() != 0)
    {
        MessageBox(hwnd, TEXT("initialize() failed"), TEXT("Error"), MB_OK | MB_ICONERROR);
        DestroyWindow(hwnd);
        return 0;
    }

    ShowWindow(hwnd, iCmdShow);
    SetForegroundWindow(hwnd);
    SetFocus(hwnd);

    QueryPerformanceFrequency(&gQPCFreq);
    QueryPerformanceCounter(&gQPCStart);

    MSG msg = { 0 };
    BOOL bDone = FALSE;
    while (!bDone)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT) bDone = TRUE;
            else { TranslateMessage(&msg); DispatchMessage(&msg); }
        }
        else if (gbActive)
        {
            LARGE_INTEGER now;
            QueryPerformanceCounter(&now);
            g_elapsedTime = (float)((now.QuadPart - gQPCStart.QuadPart) / (double)gQPCFreq.QuadPart);

            display();
            updateScene();
        }
    }

    uninitialize();
    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    RECT rc;

    switch (iMsg)
    {
        case WM_SETFOCUS:    gbActive = TRUE;  break;
        case WM_KILLFOCUS:   gbActive = FALSE; break;

        case WM_SIZE:
            GetClientRect(ghwnd, &rc);
            g_iWinWidth  = rc.right  - rc.left;
            g_iWinHeight = rc.bottom - rc.top;
            resize(g_iWinWidth, g_iWinHeight);
            break;

        case WM_ERASEBKGND: return 0;

        case WM_RBUTTONDOWN:
            gbRotating = TRUE;
            SetCapture(hwnd);
            ShowCursor(FALSE);
            break;
        case WM_RBUTTONUP:
            gbRotating = FALSE;
            ReleaseCapture();
            ShowCursor(TRUE);
            break;

        case WM_KEYDOWN:
        {
            switch (LOWORD(wParam))
            {
                case VK_ESCAPE: DestroyWindow(hwnd); break;
                case 'W': case 'w': if (gpCamera) gpCamera->setMoveForward (true); break;
                case 'S': case 's': if (gpCamera) gpCamera->setMoveBackward(true); break;
                case 'A': case 'a': if (gpCamera) gpCamera->setMoveLeft    (true); break;
                case 'D': case 'd': if (gpCamera) gpCamera->setMoveRight   (true); break;
                case 'Q': case 'q': if (gpCamera) gpCamera->setMoveDown    (true); break;
                case 'E': case 'e': if (gpCamera) gpCamera->setMoveUp      (true); break;
            }
        } break;

        case WM_KEYUP:
        {
            switch (LOWORD(wParam))
            {
                case 'W': case 'w': if (gpCamera) gpCamera->setMoveForward (false); break;
                case 'S': case 's': if (gpCamera) gpCamera->setMoveBackward(false); break;
                case 'A': case 'a': if (gpCamera) gpCamera->setMoveLeft    (false); break;
                case 'D': case 'd': if (gpCamera) gpCamera->setMoveRight   (false); break;
                case 'Q': case 'q': if (gpCamera) gpCamera->setMoveDown    (false); break;
                case 'E': case 'e': if (gpCamera) gpCamera->setMoveUp      (false); break;
            }
        } break;

        case WM_CHAR:
        {
            switch (LOWORD(wParam))
            {
                case 'F': case 'f':
                    ToggleFullScreen();
                    gbFullscreen = !gbFullscreen;
                    break;

                case '1':
                    gOcean.waves[0].amplitude = 0.6f;
                    gOcean.waves[1].amplitude = 0.4f;
                    gOcean.foamThreshold = 0.35f;
                    LOG("Preset: calm\n");
                    break;
                case '2':
                    getDefaultStormPreset(gOcean);
                    LOG("Preset: storm (default)\n");
                    break;
                case '3':
                    getDefaultStormPreset(gOcean);
                    for (int i = 0; i < gOcean.numWaves; ++i)
                        gOcean.waves[i].amplitude *= 1.6f;
                    gOcean.foamThreshold = 1.1f;
                    LOG("Preset: extreme\n");
                    break;
                 case '+': case '=':
                    for (int i = 0; i < gOcean.numWaves; ++i)
                        gOcean.waves[i].amplitude *= 1.1f;
                    LOG("Amplitude increased\n");
                    break;
                case '-': case '_':
                    for (int i = 0; i < gOcean.numWaves; ++i)
                        gOcean.waves[i].amplitude *= 0.9f;
                    LOG("Amplitude decreased\n");
                    break;
            }
        } break;

        case WM_CLOSE:   DestroyWindow(hwnd);   break;
        case WM_DESTROY: PostQuitMessage(0);    break;
    }
    return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

void ToggleFullScreen(void)
{
    MONITORINFO mi = { sizeof(MONITORINFO) };
    if (!gbFullscreen)
    {
        dwStyle = GetWindowLong(ghwnd, GWL_STYLE);
        if (dwStyle & WS_OVERLAPPEDWINDOW)
        {
            if (GetWindowPlacement(ghwnd, &wpPrev) &&
                GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
            {
                SetWindowLong(ghwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
                SetWindowPos(ghwnd, HWND_TOP,
                             mi.rcMonitor.left, mi.rcMonitor.top,
                             mi.rcMonitor.right - mi.rcMonitor.left,
                             mi.rcMonitor.bottom - mi.rcMonitor.top,
                             SWP_NOZORDER | SWP_FRAMECHANGED);
            }
        }
        ShowCursor(FALSE);
    }
    else
    {
        SetWindowPlacement(ghwnd, &wpPrev);
        SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
        SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0,
                     SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);
        ShowCursor(TRUE);
    }
}

typedef HGLRC (WINAPI *PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC, HGLRC, const int *);
#define WGL_CONTEXT_MAJOR_VERSION_ARB             0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB             0x2092
#define WGL_CONTEXT_PROFILE_MASK_ARB              0x9126
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB          0x00000001

int initialize(void)
{
    PIXELFORMATDESCRIPTOR pfd = { 0 };
    pfd.nSize        = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion     = 1;
    pfd.dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType   = PFD_TYPE_RGBA;
    pfd.cColorBits   = 32;
    pfd.cDepthBits   = 24;
    pfd.cStencilBits = 8;
    pfd.iLayerType   = PFD_MAIN_PLANE;

    ghdc = GetDC(ghwnd);
    int iPF = ChoosePixelFormat(ghdc, &pfd);
    if (iPF == 0) { LOG("ChoosePixelFormat failed\n"); return -1; }
    if (!SetPixelFormat(ghdc, iPF, &pfd)) { LOG("SetPixelFormat failed\n"); return -2; }

    HGLRC tempRC = wglCreateContext(ghdc);
    if (!tempRC) { LOG("wglCreateContext (temp) failed\n"); return -3; }
    wglMakeCurrent(ghdc, tempRC);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) { LOG("glewInit failed\n"); return -4; }

    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB =
        (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

    if (wglCreateContextAttribsARB)
    {
        int attribs[] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
            WGL_CONTEXT_MINOR_VERSION_ARB, 6,
            WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
            0
        };
        HGLRC coreRC = wglCreateContextAttribsARB(ghdc, NULL, attribs);
        if (coreRC)
        {
            wglMakeCurrent(NULL, NULL);
            wglDeleteContext(tempRC);
            ghrc = coreRC;
            wglMakeCurrent(ghdc, ghrc);
        }
        else
        {
            LOG("wglCreateContextAttribsARB failed; staying on legacy context\n");
            ghrc = tempRC;
        }
    }
    else
    {
        LOG("wglCreateContextAttribsARB not available; staying on legacy context\n");
        ghrc = tempRC;
    }

    LOG("GL Vendor:   %s\n", glGetString(GL_VENDOR));
    LOG("GL Renderer: %s\n", glGetString(GL_RENDERER));
    LOG("GL Version:  %s\n", glGetString(GL_VERSION));
    LOG("GLSL:        %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glClearColor(0.05f, 0.07f, 0.10f, 1.0f);

    gpCamera = new Camera(vmath::vec3(0.0f, 8.0f, 35.0f), -10.0f, -90.0f, 0.30f);

    const char *faces[6] = {
        "./resources/Texture/skybox/px.png",
        "./resources/Texture/skybox/nx.png",
        "./resources/Texture/skybox/py.png",
        "./resources/Texture/skybox/ny.png",
        "./resources/Texture/skybox/pz.png",
        "./resources/Texture/skybox/nz.png",
    };
    if (!initializeSkybox(faces)) { LOG("Skybox init failed\n"); return -10; }

    if (!initializeOcean(getSkyboxCubemapID())) { LOG("Ocean init failed\n"); return -11; }
    getDefaultStormPreset(gOcean);

    // Example: Globally reduce wave amplitude by half
    for (int i = 0; i < gOcean.numWaves; ++i)
    {
        gOcean.waves[i].amplitude *= 0.5f; 
    }

    perspectiveProjectionMatrix = vmath::mat4::identity();
    resize(WIN_WIDTH, WIN_HEIGHT);
    return 0;
}

void resize(int w, int h)
{
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    perspectiveProjectionMatrix = vmath::perspective(60.0f, (float)w / (float)h, 0.1f, 2000.0f);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderSkybox(gpCamera, perspectiveProjectionMatrix);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, getSkyboxCubemapID());

    renderOcean(gOcean, gpCamera, perspectiveProjectionMatrix, g_elapsedTime);

    SwapBuffers(ghdc);
}

void updateScene(void)
{
    if (gpCamera)
    {
        gpCamera->rotateOnMouse(gbRotating ? TRUE : FALSE);
        gpCamera->update();
    }
}

void uninitialize(void)
{
    uninitializeOcean();
    uninitializeSkybox();

    if (gpCamera) { delete gpCamera; gpCamera = NULL; }

    if (wglGetCurrentContext() == ghrc) wglMakeCurrent(NULL, NULL);
    if (ghrc)  { wglDeleteContext(ghrc); ghrc = NULL; }
    if (ghdc)  { ReleaseDC(ghwnd, ghdc); ghdc = NULL; }

    if (gpFILE) { LOG("Program end\n"); fclose(gpFILE); gpFILE = NULL; }
}
