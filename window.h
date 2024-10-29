#pragma once
#include <chrono>
#include <functional>
#include <glm/vec2.hpp>
#include "gfx.h"

using UpdateFn = std::function<void()>;
using RenderFn = std::function<void()>;
using Clock = std::chrono::steady_clock;
using TimePoint = std::chrono::time_point<Clock>;

struct Key {
  bool down;   // is the key pressed now
  bool before; // was the key pressed last time we checked
};

class Keyboard {
  Key keys[GLFW_KEY_LAST]{};

public:
  bool pressed_once(const int key) {
    const bool pressed = keys[key].down && !keys[key].before;
    keys[key].before = keys[key].down;
    return pressed;
  }
  [[nodiscard]] bool held(const int key) const { return keys[key].down; }
  void press(const int key) { keys[key].down = true; }
  void release(const int key) { keys[key].down = false; }
};

class Window {
  glm::vec2 size;
  UpdateFn update;
  RenderFn render;

  TimePoint time_prev;
  TimePoint time_now;

public:
  Keyboard keyboard;
  float time_delta;
  GLFWwindow *handle;

  Window(float width, float height, const char *title, UpdateFn update,
         RenderFn render);
  ~Window();
  [[nodiscard]] glm::vec2 dimensions() const;
  void loop();
};