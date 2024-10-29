#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <vector>
#include "gfx.h"
#include "camera.h"
#include "shader.h"
#include "window.h"
#include "state.h"
#include "renderer.h"

constexpr float WINDOW_WIDTH = 800.0f;
constexpr float WINDOW_HEIGHT = 600.0f;

// All global state
State g;

void handle_mouse_input() {
  static double px{0}; // x grows positively towards the right of the screen
  static double py{0}; // y grows positively towards the bottom of the screen
  double cx, cy;
  if (px || py) {
    constexpr float sensitivity = 0.1;
    glfwGetCursorPos(g.window->handle, &cx, &cy);
    g.camera.update((cx - px) * sensitivity, (cy - py) * sensitivity);
    px = cx;
    py = cy;
  } else
    glfwGetCursorPos(g.window->handle, &px, &py);
}

void handle_motion_input(const double dt) {
  const float speed = 5.0 * dt;
  if (g.window->keyboard.held(GLFW_KEY_W))
    g.camera.pos -= g.camera.front() * speed;
  if (g.window->keyboard.held(GLFW_KEY_S))
    g.camera.pos += g.camera.front() * speed;
  if (g.window->keyboard.held(GLFW_KEY_A))
    g.camera.pos += normalize(cross(g.camera.front(), g.camera.up)) * speed;
  if (g.window->keyboard.held(GLFW_KEY_D))
    g.camera.pos -= normalize(cross(g.camera.front(), g.camera.up)) * speed;
  if (g.window->keyboard.held(GLFW_KEY_SPACE))
    g.camera.pos += normalize(g.camera.up) * speed;
  if (g.window->keyboard.held(GLFW_KEY_LEFT_CONTROL))
    g.camera.pos -= normalize(g.camera.up) * speed;
}

void update() {
  handle_mouse_input();
  handle_motion_input(g.window->time_delta);

  g.world.set_position(g.camera.pos);

  if (g.window->keyboard.pressed_once(GLFW_KEY_R))
    g.render_wireframe = !g.render_wireframe;
  if (g.window->keyboard.pressed_once(GLFW_KEY_ESCAPE))
    glfwSetWindowShouldClose(g.window->handle, GL_TRUE);

  g.debug.camera_pos = g.camera.pos;
  g.debug.chunk = g.world.current_chunk;
  g.debug.time_delta = g.window->time_delta;
}

void render() {
  g.renderer->prepare_world(g.render_wireframe, g.camera);
  g.renderer->render_world(g.world, g.world.chunk_changed);
  g.world.finished_rendering();

  g.renderer->prepare_ui();
  g.renderer->render_ui(g.debug);
}

int main() {
  Window::Init(WINDOW_WIDTH, WINDOW_HEIGHT, update, render);
  g.window = &window;
  Renderer renderer{window.dimensions()};
  g.renderer = &renderer;

  window.loop();

  return 0;
}
