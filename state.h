#pragma once
#include "camera.h"
#include "debug.h"
#include "renderer.h"
#include "window.h"
#include "world.h"

struct State {
  bool render_wireframe{false};
  glm::ivec2 prev_chunk;
  glm::ivec2 current_chunk;
  Camera camera{glm::vec3{0, 3, 0}};
  Debug debug;
  Window *window;
  Renderer *renderer;
  World world;
};

extern State state;