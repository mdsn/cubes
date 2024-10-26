#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <string>
#include <vector>
#include "gfx.h"
#include "camera.h"
#include "chunk.h"
#include "shader.h"
#include "vao.h"
#include "vbo.h"
#include "texture.h"
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
  if (g.window->keyboard.pressed(GLFW_KEY_W)) {
    g.camera.pos -= g.camera.front() * speed;
  }
  if (g.window->keyboard.pressed(GLFW_KEY_S)) {
    g.camera.pos += g.camera.front() * speed;
  }
  if (g.window->keyboard.pressed(GLFW_KEY_A)) {
    g.camera.pos +=
        glm::normalize(glm::cross(g.camera.front(), g.camera.up)) * speed;
  }
  if (g.window->keyboard.pressed(GLFW_KEY_D)) {
    g.camera.pos -=
        glm::normalize(glm::cross(g.camera.front(), g.camera.up)) * speed;
  }
  if (g.window->keyboard.pressed(GLFW_KEY_SPACE)) {
    g.camera.pos += glm::normalize(g.camera.up) * speed;
  }
  if (g.window->keyboard.pressed(GLFW_KEY_LEFT_CONTROL)) {
    g.camera.pos -= glm::normalize(g.camera.up) * speed;
  }
}

void update() {
  if (g.window->keyboard.pressed(GLFW_KEY_R)) {
    g.render_wireframe = !g.render_wireframe;
  }
}

void render() { g.world.render(); }

int main() {
  Window::Init(800, 600, update, render);
  g.window = &window;
  Renderer renderer{g.world};
  g.renderer = &renderer;

  // ---------------- Loop ------------------
  auto t_start = std::chrono::high_resolution_clock::now();
  auto t_now = t_start;
  auto t_prev = t_start;

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  while (!glfwWindowShouldClose(g.window->handle)) {
    float t_delta =
        std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_prev)
            .count();
    t_prev = t_now;
    t_now = std::chrono::high_resolution_clock::now();

    if (glfwGetKey(g.window->handle, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(g.window->handle, GL_TRUE);
    }

    handle_mouse_input();
    handle_motion_input(t_delta);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    g.renderer->prepare_world(g.world, g.render_wireframe, g.camera);
    glDrawArrays(GL_TRIANGLES, 0, g.world.vertices().size() / 5);
    VAO::unbind();

    g.renderer->prepare_ui();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    VAO::unbind();

    glfwSwapBuffers(g.window->handle);
    glfwPollEvents();
    if (glfwWindowShouldClose(g.window->handle)) {
      break;
    }
  }

  return 0;
}
