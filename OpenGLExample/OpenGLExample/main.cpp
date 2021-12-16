#include <windows.h>
#include <tchar.h>
#include <gl\gl.h>
#include <gl\glu.h> 
#define _USE_MATH_DEFINES
#include <math.h>
#pragma comment(lib, "opengl32.lib")

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#undef STB_IMAGE_IMPLEMENTATION

#include "openglprogram.h"
#include "exampleprogram.h"

OpenGLProgram* program = nullptr;

const TCHAR CLSNAME[] = TEXT("OpenGLWindowClass");
LRESULT CALLBACK winproc(HWND hwnd, UINT wm, WPARAM wp, LPARAM lp);
HDC hDC = NULL;
HGLRC hRC = NULL;

void glhFrustumf2(float* matrix, float left, float right, float bottom, float top,
    float znear, float zfar) {
    float temp, temp2, temp3, temp4;
    temp = 2.0 * znear;
    temp2 = right - left;
    temp3 = top - bottom;
    temp4 = zfar - znear;
    matrix[0] = temp / temp2;
    matrix[1] = 0.0;
    matrix[2] = 0.0;
    matrix[3] = 0.0;
    matrix[4] = 0.0;
    matrix[5] = temp / temp3;
    matrix[6] = 0.0;
    matrix[7] = 0.0;
    matrix[8] = (right + left) / temp2;
    matrix[9] = (top + bottom) / temp3;
    matrix[10] = (-zfar - znear) / temp4;
    matrix[11] = -1.0;
    matrix[12] = 0.0;
    matrix[13] = 0.0;
    matrix[14] = (-temp * zfar) / temp4;
    matrix[15] = 0.0;
}

void glhPerspectivef2(float* matrix, float fovyInDegrees, float aspectRatio,
    float znear, float zfar) {
    float ymax, xmax;
    float temp, temp2, temp3, temp4;
    ymax = znear * tanf(fovyInDegrees * M_PI / 360.0);
    // ymin = -ymax;
    // xmin = -ymax * aspectRatio;
    xmax = ymax * aspectRatio;
    glhFrustumf2(matrix, -xmax, xmax, -ymax, ymax, znear, zfar);
}

GLvoid ReSizeGLScene(GLsizei width, GLsizei height) {
    if (height == 0) {
        height = 1;
    }

    glViewport(0, 0, width, height);                    // Reset The Current Viewport

    glMatrixMode(GL_PROJECTION);                        // Select The Projection Matrix
    glLoadIdentity();                           // Reset The Projection Matrix

    // Calculate The Aspect Ratio Of The Window
    float mat[16];
    glhPerspectivef2(mat, 45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
    glLoadMatrixf(mat);

    glMatrixMode(GL_MODELVIEW);                     // Select The Modelview Matrix
    glLoadIdentity();                           // Reset The Modelview Matrix
}

GLvoid KillGLWindow(HWND hWnd, HINSTANCE hInstance, bool withMessages = true)                         // Properly Kill The Window
{
    if (hRC) {
        if (!wglMakeCurrent(NULL, NULL)) {
            if (withMessages) {
                MessageBox(NULL, L"Release Of DC And RC Failed.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
            }
        }
        if (!wglDeleteContext(hRC)) {
            if (withMessages) {
                MessageBox(NULL, L"Release Rendering Context Failed.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
            }
        }
        hRC = NULL;
    }
    if (hDC && !ReleaseDC(hWnd, hDC)) {
        if (withMessages) {
            MessageBox(NULL, L"Release Device Context Failed.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
        }
        hDC = NULL;
    }
    if (hWnd && !DestroyWindow(hWnd)) {
        if (withMessages) {
            MessageBox(NULL, L"Could Not Release hWnd.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
        }
        hWnd = NULL;
    }
    if (!UnregisterClass(CLSNAME, hInstance)) {
        if (withMessages) {
            MessageBox(NULL, L"Could Not Unregister Class.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
        }
        hInstance = NULL;
    }
}

HWND createWindow(HINSTANCE hInst, LPCWSTR title, int width, int height) {

    WNDCLASSEX wc = { };

    wc.cbSize = sizeof(wc);
    wc.style = 0;
    wc.lpfnWndProc = winproc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = CLSNAME;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, TEXT("Could not register window class"), NULL, MB_ICONERROR);
        return 0;
    }

    HWND hwnd = CreateWindowEx(WS_EX_LEFT,
        CLSNAME,
        title,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        width,
        height,
        NULL,
        NULL,
        hInst,
        NULL);


    static  PIXELFORMATDESCRIPTOR pfd =                  // pfd Tells Windows How We Want Things To Be
    {
        sizeof(PIXELFORMATDESCRIPTOR),                  // Size Of This Pixel Format Descriptor
        1,                              // Version Number
        PFD_DRAW_TO_WINDOW |                        // Format Must Support Window
        PFD_SUPPORT_OPENGL |                        // Format Must Support OpenGL
        PFD_DOUBLEBUFFER,                       // Must Support Double Buffering
        PFD_TYPE_RGBA,                          // Request An RGBA Format
        32,                               // Select Our Color Depth
        0, 0, 0, 0, 0, 0,                       // Color Bits Ignored
        0,                              // No Alpha Buffer
        0,                              // Shift Bit Ignored
        0,                              // No Accumulation Buffer
        0, 0, 0, 0,                         // Accumulation Bits Ignored
        16,                             // 16Bit Z-Buffer (Depth Buffer)
        0,                              // No Stencil Buffer
        0,                              // No Auxiliary Buffer
        PFD_MAIN_PLANE,                         // Main Drawing Layer
        0,                              // Reserved
        0, 0, 0                             // Layer Masks Ignored
    };



    GLuint pixelFormat;

    if (!(hDC = GetDC(hwnd))) {
        KillGLWindow(hwnd, hInst);
        MessageBox(NULL, L"Can't Create A GL Device Context.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }

    if (!(pixelFormat = ChoosePixelFormat(hDC, &pfd))) {
        KillGLWindow(hwnd, hInst);
        MessageBox(NULL, L"Can't Find A Suitable PixelFormat.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }

    if (!SetPixelFormat(hDC, pixelFormat, &pfd)) {
        KillGLWindow(hwnd, hInst);
        MessageBox(NULL, L"Can't Set The PixelFormat.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }

    if (!(hRC = wglCreateContext(hDC))) {
        KillGLWindow(hwnd, hInst);
        MessageBox(NULL, L"Can't Create A GL Rendering Context.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }

    if (!wglMakeCurrent(hDC, hRC)) {
        KillGLWindow(hwnd, hInst);
        MessageBox(NULL, L"Can't Activate The GL Rendering Context.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }

    ReSizeGLScene(width, height);

    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    ShowWindow(hwnd, true);
    UpdateWindow(hwnd);

    return hwnd;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR cmdline, int cmdshow)
{
    HWND hwnd = createWindow(hInst, TEXT("OpenGL Program"), 640, 480);

    if (!hwnd) {
        MessageBox(NULL, TEXT("Could not create window"), NULL, MB_ICONERROR);
        return 0;
    }

    program = new ExampleProgram();
    ((ExampleProgram*)program)->setHandle(hwnd);
    if (program) {
        program->init();
    }

    MSG msg;
    bool work = true;
    while (work) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                work = false;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        if (program != nullptr) {
            program->draw();
            SwapBuffers(hDC);
        }
    }
    KillGLWindow(hwnd, hInst, false);
    return msg.wParam;
}

LRESULT CALLBACK winproc(HWND hwnd, UINT wm, WPARAM wp, LPARAM lp)
{
    switch (wm) {
    case WM_CLOSE: {
        PostQuitMessage(0);
        return 0;
    }
    case WM_SIZE: {
        ReSizeGLScene(LOWORD(lp), HIWORD(lp));
        return 0;
    }
    case WM_KEYDOWN: {
        if (program) {
            program->keyDown(wp);
            return 0;
        }
    }
    case WM_KEYUP: {
        if (program) {
            program->keyUp(wp);
            return 0;
        }
    }
    }
    return DefWindowProc(hwnd, wm, wp, lp);
}