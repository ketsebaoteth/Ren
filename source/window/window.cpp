#include "window/define_window.h"

Window_Handle FAULTY_WINDOW_HANDLE{
    NULL,
    "[ ERROR ]: Window Creation Failed  | Reason Was Not Specified",
};

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
  {
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  default:
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
  }
  return 0;
}

Window_Handle Create_Window(Window window)
{
#ifdef _WIN32
  return Win32_Create_Window(window);
#elif __linux__
  return Linux_Create_Window(window);
#else
  Window_Handle handle = FAULTY_WINDOW_HANDLE;
  handle.err = "[ ERROR ]: Platform not supported!";
  return handle;
#endif
}

Window_Handle Win32_Create_Window(Window window)
{
  WNDCLASSA wc = {};
  wc.lpfnWndProc = WindowProc;
  wc.hInstance = GetModuleHandle(NULL);
  wc.lpszClassName = "WindowClass";

  if (!RegisterClassA(&wc))
  {
    MessageBoxA(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    Window_Handle handle = FAULTY_WINDOW_HANDLE;
    handle.err = "[ ERROR ]: failed ot register class win32 api";
    return handle;
  }

  // create the window
  HWND hwnd = CreateWindowA(
      "WindowClass",
      window.title,
      WS_OVERLAPPEDWINDOW,
      window.x,
      window.y,
      window.width,
      window.height,
      NULL,
      NULL,
      GetModuleHandle(NULL),
      NULL);

  if (!hwnd)
  {
    MessageBoxA(NULL, "Window Creation Failed!", "Error", MB_ICONERROR | MB_OK);
    Window_Handle handle = FAULTY_WINDOW_HANDLE;
    handle.err = "[ ERROR ]: failed to initalize window handle win32 api !";
    return handle;
  }

  ShowWindow(hwnd, SW_SHOW);
  UpdateWindow(hwnd);

  Window_Handle handle = {
      hwnd,
      NULL,
  };
  return handle;
}

/**
 *  note: This function is not implemented yet.
 *
 */
Window_Handle Linux_Create_Window(Window window)
{

  Window_Handle handle = FAULTY_WINDOW_HANDLE;
  handle.err = "[ ERROR ]: Linux window creation not implemented yet!";
  return handle;
};

GPU_Context Setup_Gpu_Context(HWND hwnd)
{
  HDC hdc = GetDC(hwnd);
  PIXELFORMATDESCRIPTOR pfd = {
      sizeof(PIXELFORMATDESCRIPTOR),
      1,
      PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
      PFD_TYPE_RGBA,
      32,
      0, 0, 0, 0, 0, 0,
      0,
      0,
      0,
      0, 0, 0, 0,
      24, // Depth buffer
      8,  // Stencil buffer
      0,
      PFD_MAIN_PLANE,
      0,
      0, 0, 0};
  int pixelFormat = ChoosePixelFormat(hdc, &pfd);
  SetPixelFormat(hdc, pixelFormat, &pfd);

  HGLRC hglrc = wglCreateContext(hdc);
  if (!hglrc)
  {
    MessageBoxA(hwnd, "Failed to create OpenGL rendering context", "Error", MB_OK | MB_ICONERROR);
    exit(EXIT_FAILURE);
  }
  // make rendering context current
  wglMakeCurrent(hdc, hglrc);
  if (!gladLoadGL())
  {
    MessageBoxA(hwnd, "Failed to initialize GLAD", "Error", MB_OK | MB_ICONERROR);
    exit(EXIT_FAILURE);
  }

  // Set default OpenGL state
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glEnable(GL_DEPTH_TEST);

  GPU_Context ctx;
  ctx.device_context = hdc;
  ctx.render_context = hglrc;
  return ctx;
}

void Clear_Window(GPU_Context ctx, Color_v4 clear_color)
{
  // Set the clear color
  glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Swap buffers
  SwapBuffers(ctx.device_context);
}
