#pragma once
#include <chrono>
#include <functional>
#include <glm/vec2.hpp>
#include "gfx.h"

using UpdateFn = std::function<void()>;
using RenderFn = std::function<void()>;
using Clock = std::chrono::steady_clock;
using TimePoint = std::chrono::time_point<Clock>;

class Keyboard {
  bool keys[GLFW_KEY_LAST];

public:
  bool pressed(int key) const { return (key >= 0) && keys[key]; }
  void press(int key) { keys[key] = true; }
  void release(int key) { keys[key] = false; }
};

class Window {
  glm::ivec2 size;
  UpdateFn update;
  RenderFn render;

  TimePoint time_prev;
  TimePoint time_now;

public:
  Keyboard keyboard;
  float time_delta;
  GLFWwindow *handle;

  static void Init(int width, int height, UpdateFn update, RenderFn render);
  ~Window();

  void loop();
};

extern Window window;