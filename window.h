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
  Key keys[GLFW_KEY_LAST];

public:
  bool pressed_once(int key) {
    bool pressed = keys[key].down && !keys[key].before;
    keys[key].before = keys[key].down;
    return pressed;
  }
  bool held(int key) { return keys[key].down; }
  void press(int key) { keys[key].down = true; }
  void release(int key) { keys[key].down = false; }
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

  static void Init(float width, float height, UpdateFn update, RenderFn render);
  glm::vec2 dimensions() const;
  ~Window();

  void loop();
};

extern Window window;