#include <iostream>
#include <cstdlib>

#include "window.h"

const char *WINDOW_TITLE = "BRIX";

// Global window--thanks jdh
Window window;

void _error_callback(int code, const char *err) {
  std::cerr << "GLFW error " << code << ": " << err << std::endl;
}

void _key_callback(GLFWwindow *handle, int key, int scancode, int action,
                   int mods) {
  switch (action) {
  case GLFW_PRESS:
    window.keyboard.press(key);
    break;
  case GLFW_RELEASE:
    window.keyboard.release(key);
    break;
  }
}

void Window::Init(int width, int height, UpdateFn update, RenderFn render) {
  window.size = glm::ivec2{width, height};
  window.update = update;
  window.render = render;

  glfwSetErrorCallback(_error_callback);
  if (!glfwInit()) {
    std::exit(-1);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  window.handle =
      glfwCreateWindow(window.size.x, window.size.y, WINDOW_TITLE, NULL, NULL);
  if (!window.handle) {
    glfwTerminate();
    std::exit(-1);
  }

  glfwSetInputMode(window.handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetInputMode(window.handle, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
  glfwSetKeyCallback(window.handle, _key_callback);

  glfwMakeContextCurrent(window.handle);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    glfwTerminate();
    std::exit(-1);
  }
}

Window::~Window() { glfwTerminate(); }

void Window::loop() {
  time_now = Clock::now();
  time_prev = time_now;

  while (!glfwWindowShouldClose(handle)) {
    time_delta = std::chrono::duration_cast<std::chrono::duration<float>>(
                     time_now - time_prev)
                     .count();
    time_prev = time_now;
    time_now = Clock::now();

    update();
    render();

    glfwSwapBuffers(handle);
    glfwPollEvents();
  }
}
