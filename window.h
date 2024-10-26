#pragma once
#include <chrono>
#include <functional>
#include <glm/vec2.hpp>
#include "gfx.h"

using UpdateFn = std::function<void()>;
using RenderFn = std::function<void()>;
using Clock = std::chrono::steady_clock;
using TimePoint = std::chrono::time_point<Clock>;

class Window {
  glm::ivec2 size;
  UpdateFn update;
  RenderFn render;

  TimePoint time_prev;
  TimePoint time_now;

public:
  float time_delta;
  GLFWwindow *handle;

  Window(int width, int height, GLFWkeyfun on_key, UpdateFn update,
         RenderFn render);
  ~Window();

  void loop();
};