#pragma once

#define CHECK_HANDLE(handle) \
  do                         \
  {                          \
    if (!(handle))           \
    {                        \
      return -1;             \
    }                        \
  } while (0)

struct Color_v4
{
  float r;
  float g;
  float b;
  float a;
};

struct Size_v2
{
  int x;
  int y;
};
