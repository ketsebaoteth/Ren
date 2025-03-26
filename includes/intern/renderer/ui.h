#pragma once

#include "../ui/define_style.h"
#include "../ui/define_components.h"

void Render_Component(Ui_Component *component)
{
  Render_Component_Type(component);
  for (auto &child : component->children)
  {
    Render_Component_Type(child);
  }
}

void Render_Component_Type(Ui_Component *component);
