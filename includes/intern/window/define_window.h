#pragma once

#include "./utils/utils.h"
#include "Windows.h"
#include <WinUser.h>
#include "gpu/gpu.h"

struct Window_Handle
{
  HWND handle;
  char *err;
  // TODO(Ketsebaot): linux handle here
};

extern Window_Handle FAULTY_WINDOW_HANDLE;

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
  bool FULLSCREEN = false;
  bool VISIBLE = true;
};

/*
 * creates window
 * returns HWND of the window
 */
Window_Handle Create_Window(Window window);

Window_Handle Win32_Create_Window(Window window);

Window_Handle Linux_Create_Window(Window window);

GPU_Context Setup_Gpu_Context(HWND hwnd);

void Clear_Window(GPU_Context ctx, Color_v4 clear_color);

/* Window Helper Functions */

/*
 * sets window to full screen
 */
void Set_Window_Fullscreen();

void Set_Window_Visible();

void Set_Window_Size(Size_v2 new_size);

void Set_Window_Title(char *new_title);
