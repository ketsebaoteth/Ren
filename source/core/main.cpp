#include "window/define_window.h"

int main()
{
  Window window;
  window.title = "custom title is working";
  window.x = 50;
  window.y = 50;
  Window_Instance instance = Create_Window(window);

  VERIFY_HANDLE(instance);

  GPU_Context ctx = Setup_Gpu_Context(instance);

  RunEventLoop(instance, ctx, [](MSG event)
               {if(event.message == WM_QUIT) return 0; });
};
