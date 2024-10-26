#pragma once
#include "camera.h"
#include "window.h"

struct State {
  bool render_wireframe{false};
  Window *window;
  Camera camera{glm::vec3{0, 0, 5.0}};
};

extern State state;