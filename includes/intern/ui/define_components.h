#pragma once
#include "./define_style.h"
#include <vector>

struct Ui_Component
{
  stylesheet style;
  std::vector<Ui_Component *> children;
};

struct Text_Button
{
  stylesheet style;
  char *text;
  std::vector<Ui_Component *> children;
};
