#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "gfx.h"
#include "camera.h"
#include "shader.h"
#include "window.h"
#include "world.h"
#include "renderer.h"

constexpr float WINDOW_WIDTH{1400.0};
constexpr float WINDOW_HEIGHT{900.0};
const char *WINDOW_TITLE{"BRIX"};

constexpr glm::vec3 INITIAL_POSITION{glm::vec3{0, 3, 0}};

// All global state
struct State {
  bool render_wireframe{false};
  Camera camera{INITIAL_POSITION};
  Debug debug{};
  std::unique_ptr<Window> window;
  std::unique_ptr<Renderer> renderer;
  World world{INITIAL_POSITION};
};

State st;

void handle_mouse_input() {
  static double px{0}; // x grows positively towards the right of the screen
  static double py{0}; // y grows positively towards the bottom of the screen
  double cx, cy;
  if (px != 0.0 || py != 0.0) {
    constexpr float sensitivity = 0.1;
    glfwGetCursorPos(st.window->handle, &cx, &cy);
    st.camera.update(static_cast<float>(cx - px) * sensitivity,
                     static_cast<float>(cy - py) * sensitivity);
    px = cx;
    py = cy;
  } else
    glfwGetCursorPos(st.window->handle, &px, &py);
}

void handle_motion_input(const float dt) {
  const float speed = 5.0f * dt;
  if (st.window->keyboard.held(GLFW_KEY_W))
    st.camera.pos -= st.camera.front() * speed;
  if (st.window->keyboard.held(GLFW_KEY_S))
    st.camera.pos += st.camera.front() * speed;
  if (st.window->keyboard.held(GLFW_KEY_A))
    st.camera.pos += normalize(cross(st.camera.front(), st.camera.up)) * speed;
  if (st.window->keyboard.held(GLFW_KEY_D))
    st.camera.pos -= normalize(cross(st.camera.front(), st.camera.up)) * speed;
  if (st.window->keyboard.held(GLFW_KEY_SPACE))
    st.camera.pos += normalize(st.camera.up) * speed;
  if (st.window->keyboard.held(GLFW_KEY_LEFT_CONTROL))
    st.camera.pos -= normalize(st.camera.up) * speed;
}

void update() {
  handle_mouse_input();
  handle_motion_input(st.window->time_delta);

  st.world.set_position(st.camera.pos);

  if (st.window->keyboard.pressed_once(GLFW_KEY_R))
    st.render_wireframe = !st.render_wireframe;
  if (st.window->keyboard.pressed_once(GLFW_KEY_ESCAPE))
    glfwSetWindowShouldClose(st.window->handle, GL_TRUE);

  st.debug.camera_pos = st.camera.pos;
  st.debug.chunk = st.world.current_chunk;
  st.debug.time_delta = st.window->time_delta;
}

void render() {
  clear_screen();
  st.renderer->render_world(st.world.vertices(), st.camera.view(),
                            st.render_wireframe, st.world.chunk_changed);
  st.world.finished_rendering();
  st.renderer->render_ui(st.debug);
}

int main() {
  st.window = std::make_unique<Window>(WINDOW_WIDTH, WINDOW_HEIGHT,
                                       WINDOW_TITLE, update, render);
  st.renderer = std::make_unique<Renderer>(st.window->dimensions());
  st.window->loop();
  return 0;
}
