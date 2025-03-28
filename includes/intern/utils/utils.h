#pragma once

#define VERIFY_HANDLE(window_instance) \
  do                                   \
  {                                    \
    if (!(window_instance.handle))     \
    {                                  \
      return -1;                       \
    }                                  \
  } while (0)

struct Color_v4
{
  float r;
  float g;
  float b;
  float a;
};

struct Vertex
{
  float x, y, z;    // Position
  float r, g, b, a; // Color
};

struct Size_v2
{
  int x;
  int y;
};
