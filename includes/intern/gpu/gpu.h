#pragma once

#include <glad/glad.h>
#include <gl/GL.h>
#include <Windows.h>

struct GPU_Context
{
  HDC device_context;
  HGLRC render_context;
};
