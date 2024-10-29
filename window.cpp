#include <iostream>
#include <cstdlib>
#include <utility>

#include "window.h"

void glfw_error_callback(int code, const char *err) {
  std::cerr << "GLFW error " << code << ": " << err << std::endl;
}

void glfw_key_callback(GLFWwindow *handle, int key, int scancode, int action,
                       int mods) {
  (void)scancode; // Silence unused warnings
  (void)mods;
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
  default:
  }
}

Window::Window(const float width, const float height, const char *title,
               UpdateFn update, RenderFn render)
    : size{width, height}, update{std::move(update)}, render{std::move(render)},
      time_delta{0} {
  glfwSetErrorCallback(glfw_error_callback);
  if (!glfwInit())
    std::exit(-1);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  handle = glfwCreateWindow(static_cast<int>(size.x), static_cast<int>(size.y),
                            title, nullptr, nullptr);
  if (!handle) {
    glfwTerminate();
    std::exit(-1);
  }

  glfwSetInputMode(handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetInputMode(handle, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
  glfwSetWindowUserPointer(handle, this);
  glfwSetKeyCallback(handle, glfw_key_callback);

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
