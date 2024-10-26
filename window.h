#pragma once
#include <glm/vec2.hpp>
#include "gfx.h"

class Window {
  glm::ivec2 size;

public:
  GLFWwindow *handle;

  Window(int width, int height, GLFWkeyfun on_key);
  ~Window();
};