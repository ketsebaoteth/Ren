#pragma once

#include "./utils/utils.h"

enum POSITION_STYLES
{
  ABSOLUTE,
  RELATIVE,
  FIXED,
};

enum BORDER_DIRECTION
{
  INSET,
  OUTSET,
};

enum TEXT_ALIGN
{
  LEFT,
  CENTER,
  RIGHT,
};

struct Tborder
{
  int top;
  int left;
  int right;
  int bottom;
  int all;
  Color_v4 color;
  BORDER_DIRECTION direction;
};

struct Side_v4
{
  int top;
  int left;
  int right;
  int bottom;
};

struct Border_Radius
{
  int top_left;
  int top_right;
  int bottom_left;
  int bottom_right;
};

struct stylesheet
{
  Side_v4 position;
  POSITION_STYLES position_style;
  int width;
  int height;
  Side_v4 margin;
  Side_v4 padding;
  Tborder border;
  Color_v4 background_color;
  Color_v4 color;
  Border_Radius border_radius;
  char *font;
  int font_size;
  int font_weight;
  int line_height;
  TEXT_ALIGN text_align;
  bool visible;
  bool disabled;
};
