#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <vector>
#include "gfx.h"
#include "camera.h"
#include "shader.h"
#include "vao.h"
#include "window.h"
#include "state.h"
#include "renderer.h"

const float width = 800.0f;
const float height = 600.0f;

// All global state
State g;

void handle_mouse_input() {
  const float sensitivity = 0.1;
  static double px{0};
  static double py{0};
  double cx, cy;
  if (px || py) {
    glfwGetCursorPos(g.window->handle, &cx, &cy);
    // std::cout << "cursor pos x " << cx << " y " << cy << std::endl;
    // x grows positively towards the right of the screen
    // y grows positively towards the bottom of the screen
    float dx = (cx - px) * sensitivity;
    float dy = (cy - py) * sensitivity;
    px = cx;
    py = cy;
    g.camera.update(dx, dy);
  } else {
    glfwGetCursorPos(g.window->handle, &px, &py);
  }
}

void handle_motion_input(double dt) {
  float speed = 5.0 * dt;
  if (g.window->keyboard.held(GLFW_KEY_W)) {
    g.camera.pos -= g.camera.front() * speed;
  }
  if (g.window->keyboard.held(GLFW_KEY_S)) {
    g.camera.pos += g.camera.front() * speed;
  }
  if (g.window->keyboard.held(GLFW_KEY_A)) {
    g.camera.pos +=
        glm::normalize(glm::cross(g.camera.front(), g.camera.up)) * speed;
  }
  if (g.window->keyboard.held(GLFW_KEY_D)) {
    g.camera.pos -=
        glm::normalize(glm::cross(g.camera.front(), g.camera.up)) * speed;
  }
  if (g.window->keyboard.held(GLFW_KEY_SPACE)) {
    g.camera.pos += glm::normalize(g.camera.up) * speed;
  }
  if (g.window->keyboard.held(GLFW_KEY_LEFT_CONTROL)) {
    g.camera.pos -= glm::normalize(g.camera.up) * speed;
  }
}

int map_interval(float x) {
  float abs = std::abs(x);
  if (abs < 8.0)
    return 0;
  int res = 1 + static_cast<int>(abs - 8) / 16;
  return x >= 0 ? res : -res;
}

glm::ivec2 pos_to_chunk(const glm::vec3 pos) {
  return glm::ivec2{map_interval(pos.x), map_interval(pos.z)};
}

void update() {
  handle_mouse_input();
  handle_motion_input(g.window->time_delta);

  // calculate position to chunk (fvec3 -> ivec2)
  g.current_chunk = pos_to_chunk(g.camera.pos);
  if (g.prev_chunk != g.current_chunk) {
    // g.world.chunk = Chunk{g.current_chunk.x, g.current_chunk.y};
    g.world.chunk_changed = true;
  }
  g.prev_chunk = g.current_chunk;

  if (g.window->keyboard.pressed_once(GLFW_KEY_R)) {
    g.render_wireframe = !g.render_wireframe;
  }

  if (g.window->keyboard.pressed_once(GLFW_KEY_ESCAPE)) {
    glfwSetWindowShouldClose(g.window->handle, GL_TRUE);
  }

  g.debug.camera_pos = g.camera.pos;
  g.debug.chunk = g.current_chunk;
  g.debug.time_delta = g.window->time_delta;
}

void render() {
  g.renderer->prepare_world(g.world, g.render_wireframe, g.camera);
  g.renderer->render_world(g.world);
  g.renderer->prepare_ui();
  g.renderer->render_ui(g.debug);
}

int main() {
  Window::Init(800, 600, update, render);
  g.window = &window;
  Renderer renderer{g.world};
  g.renderer = &renderer;

  window.loop();

  return 0;
}
