#pragma once
#include <memory>
#include "camera.h"
#include "debug.h"
#include "renderer.h"
#include "window.h"
#include "world.h"

const glm::vec3 INITIAL_POSITION{glm::vec3{0, 3, 0}};

struct State {
  bool render_wireframe{false};
  Camera camera{INITIAL_POSITION};
  Debug debug;
  std::unique_ptr<Window> window;
  std::unique_ptr<Renderer> renderer;
  World world{INITIAL_POSITION};
};

extern State state;