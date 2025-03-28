#pragma once

#include "./utils/utils.h"
#include "Windows.h"
#include "gpu/gpu.h"

#include <functional>
#include <iostream>
#include <WinUser.h>

struct Window_Instance
{
  HWND handle;
  char *err;
  // TODO(Ketsebaot): linux handle here
};

extern Window_Instance FAULTY_WINDOW_HANDLE;

/*
 * Parameters:
 * - title: The title of the window.
 * - width: The width of the window in pixels.
 * - height: The height of the window in pixels.
 * - x: The x-coordinate of the window's position on the screen.
 * - y: The y-coordinate of the window's position on the screen.
 */
struct Window
{
  LPCSTR title = "Hello World From Cosmos Window!";
  int width = 800;
  int height = 500;
  int Min_Width = 200;
  int Min_Height = 200;
  int Max_Width = 1920;
  int Max_Height = 1080;
  int x = 0;
  int y = 0;
  bool Has_Titlebar = true;
  bool Can_Resize = true;
  bool Has_Minimize = true;
  bool Has_Maximize = true;
  bool FULLSCREEN = false;
  bool VISIBLE = true;
};

/*
 * creates window
 * returns HWND of the window
 */
Window_Instance Create_Window(Window window);

Window_Instance Win32_Create_Window(Window window);

Window_Instance Linux_Create_Window(Window window);

GPU_Context Setup_Gpu_Context(Window_Instance window);

/* Window Helper Functions */

/*
 * sets window to full screen
 */
void Set_Window_Fullscreen(HWND hwnd);

void Set_Window_Visible(HWND hwnd);

void Set_Window_Size(HWND hwnd, Size_v2 new_size);

void Set_Window_Title(HWND hwnd, LPCSTR new_title);

void Set_Window_Invisible(HWND hwnd);

void Set_Window_Maximized(HWND hwnd);

void Set_Window_Minimized(HWND hwnd);

void Set_Window_Icon(HWND hwnd, LPCSTR icon_path);

MSG Get_Events(Window_Instance window_instance);

void Dispatch_Event(MSG msg);

void RunEventLoop(Window_Instance instance, GPU_Context ctx, std::function<int(MSG)> callback);
