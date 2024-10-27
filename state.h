#pragma once
#include "camera.h"
#include "debug.h"
#include "renderer.h"
#include "window.h"
#include "world.h"

struct State {
  bool render_wireframe{false};
  Camera camera{glm::vec3{0, 0, 5.0}};
  Debug debug;
  Window *window;
  Renderer *renderer;
  World world;
};

extern State state;