#include <iostream>
#include "window/define_window.h"

int main()
{
  Window window;
  Window_Handle window_handle = Create_Window(window);

  CHECK_HANDLE(window_handle.handle);

  GPU_Context ctx = Setup_Gpu_Context(window_handle.handle);
  while (true)
  {
    MSG msg = {};
    if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)
        break;
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }

    // clear window
    Clear_Window(ctx, {0.2f, 0.4f, 0.5f, 1.0f});
  }
  return 0;
}
