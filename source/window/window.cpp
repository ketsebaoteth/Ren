#include "window/define_window.h"

Window_Instance FAULTY_WINDOW_INSTANCE{
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

  case WM_PAINT:
  {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);
    // Perform any custom painting here (if needed)
    EndPaint(hwnd, &ps);
    break;
  }

  default:
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
  }
  return 0;
}

Window_Instance Create_Window(Window window)
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

Window_Instance Win32_Create_Window(Window window)
{
  WNDCLASSA wc = {};
  wc.lpfnWndProc = WindowProc;
  wc.hInstance = GetModuleHandle(NULL);
  wc.lpszClassName = "WindowClass";

  if (!RegisterClassA(&wc))
  {
    MessageBoxA(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    Window_Instance handle = FAULTY_WINDOW_INSTANCE;
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
    Window_Instance handle = FAULTY_WINDOW_INSTANCE;
    handle.err = "[ ERROR ]: failed to initalize window handle win32 api !";
    return handle;
  }
  if (window.FULLSCREEN)
  {
    int screen_width = GetSystemMetrics(SM_CXSCREEN);
    int screen_height = GetSystemMetrics(SM_CYSCREEN);
    SetWindowLongPtr(hwnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
    SetWindowPos(hwnd, HWND_TOP, 0, 0, screen_width, screen_height, SWP_FRAMECHANGED | SWP_NOOWNERZORDER | SWP_SHOWWINDOW);
    InvalidateRect(hwnd, nullptr, TRUE);
  }
  if (!window.Can_Resize)
  {
    SetWindowLongPtr(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_SIZEBOX);
    InvalidateRect(hwnd, nullptr, TRUE);
  }
  if (!window.Has_Titlebar)
  {
    SetWindowLongPtr(hwnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
    InvalidateRect(hwnd, nullptr, TRUE);
  }
  if (!window.VISIBLE)
  {
    ShowWindow(hwnd, SW_HIDE);
  }
  if (!window.Has_Minimize)
  {
    SetWindowLongPtr(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_MINIMIZEBOX);
    InvalidateRect(hwnd, nullptr, TRUE);
  }
  if (!window.Has_Maximize)
  {
    SetWindowLongPtr(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_MAXIMIZEBOX);
    InvalidateRect(hwnd, nullptr, TRUE);
  }

  ShowWindow(hwnd, SW_SHOW);
  UpdateWindow(hwnd);

  Window_Instance handle = {
      hwnd,
      NULL,
  };
  return handle;
}

/**
 *  note: This function is not implemented yet.
 *
 */
Window_Instance Linux_Create_Window(Window window)
{

  Window_Instance handle = FAULTY_WINDOW_INSTANCE;
  handle.err = "[ ERROR ]: Linux window creation not implemented yet!";
  return handle;
};

GPU_Context Setup_Gpu_Context(Window_Instance window)
{
  HDC hdc = GetDC(window.handle);
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
    MessageBoxA(window.handle, "Failed to create OpenGL rendering context", "Error", MB_OK | MB_ICONERROR);
    exit(EXIT_FAILURE);
  }
  // make rendering context current
  wglMakeCurrent(hdc, hglrc);
  if (!gladLoadGL())
  {
    MessageBoxA(window.handle, "Failed to initialize GLAD", "Error", MB_OK | MB_ICONERROR);
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

void Set_Window_Fullscreen(HWND hwnd)
{
  int screen_width = GetSystemMetrics(SM_CXSCREEN);
  int screen_height = GetSystemMetrics(SM_CYSCREEN);
  SetWindowLongPtr(hwnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
  SetWindowPos(hwnd, HWND_TOP, 0, 0, screen_width, screen_height, SWP_FRAMECHANGED | SWP_NOOWNERZORDER | SWP_SHOWWINDOW);
  InvalidateRect(hwnd, nullptr, TRUE);
}

void Set_Window_Visible(HWND hwnd)
{
  ShowWindow(hwnd, SW_SHOW);
}

void Set_Window_Invisible(HWND hwnd)
{
  ShowWindow(hwnd, SW_HIDE);
}

void Set_Window_Size(HWND hwnd, int width, int height)
{
  if (width < 0 || height < 0)
  {
    return;
  }
  SetWindowPos(hwnd, HWND_TOP, 0, 0, width, height, SWP_FRAMECHANGED | SWP_NOOWNERZORDER | SWP_SHOWWINDOW);
  InvalidateRect(hwnd, nullptr, TRUE);
}

void Set_Window_Position(HWND hwnd, int x, int y)
{
  SetWindowPos(hwnd, HWND_TOP, x, y, 0, 0, SWP_FRAMECHANGED | SWP_NOOWNERZORDER | SWP_SHOWWINDOW);
  InvalidateRect(hwnd, nullptr, TRUE);
}

void Set_Window_Title(HWND hwnd, LPCSTR title)
{
  SetWindowTextA(hwnd, title);
}

void Set_Window_Maximized(HWND hwnd)
{
  ShowWindow(hwnd, SW_MAXIMIZE);
}

void Set_Window_Minimized(HWND hwnd)
{
  ShowWindow(hwnd, SW_MINIMIZE);
}

void Set_Window_Icon(HWND hwnd, LPCSTR icon_path)
{
  HICON icon = (HICON)LoadImageA(NULL, icon_path, IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
  if (icon)
  {
    SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)icon);
  }
  else
  {
    MessageBoxA(hwnd, "Failed to load Window icon", "Error", MB_OK | MB_ICONERROR);
  }
}

MSG Get_Events(Window_Instance window_instance)
{
  MSG msg = {};
  PeekMessage(&msg, window_instance.handle, 0, 0, PM_REMOVE);
  return msg;
}

void Dispatch_Event(MSG msg)
{
  TranslateMessage(&msg);
  DispatchMessage(&msg);
}

void RunEventLoop(Window_Instance window_instance, GPU_Context ctx, std::function<int(MSG)> callback)
{
  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0))
  {
    Dispatch_Event(msg);
    if (msg.message == WM_QUIT)
    {
      break;
    }
    // Call the user-defined event callback
    callback(msg);
  }
}
