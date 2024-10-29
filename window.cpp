#include <iostream>
#include <cstdlib>

#include "window.h"

void _error_callback(int code, const char *err) {
  std::cerr << "GLFW error " << code << ": " << err << std::endl;
}

void _key_callback(GLFWwindow *handle, int key, int scancode, int action,
                   int mods) {
  const auto window = static_cast<Window *>(glfwGetWindowUserPointer(handle));
  if (key < 0)
    return;
  switch (action) {
  case GLFW_PRESS:
    window->keyboard.press(key);
    break;
  case GLFW_RELEASE:
    window->keyboard.release(key);
    break;
  }
}

Window::Window(const float width, const float height, const char *title,
               const UpdateFn &update, const RenderFn &render)
    : size{width, height}, update{update}, render{render} {
  glfwSetErrorCallback(_error_callback);
  if (!glfwInit())
    std::exit(-1);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  handle = glfwCreateWindow(size.x, size.y, title, NULL, NULL);
  if (!handle) {
    glfwTerminate();
    std::exit(-1);
  }

  glfwSetInputMode(handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetInputMode(handle, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
  glfwSetWindowUserPointer(handle, this);
  glfwSetKeyCallback(handle, _key_callback);

  glfwMakeContextCurrent(handle);
  if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
    glfwTerminate();
    std::exit(-1);
  }
}

Window::~Window() { glfwTerminate(); }

glm::vec2 Window::dimensions() const { return size; }

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
