#include <iostream>
#include <cstdlib>

#include "window.h"

const char *WINDOW_TITLE = "BRIX";

void _error_callback(int code, const char *err) {
  std::cerr << "GLFW error " << code << ": " << err << std::endl;
}

Window::Window(int width, int height, GLFWkeyfun on_key)
    : size({width, height}) {
  glfwSetErrorCallback(_error_callback);
  if (!glfwInit()) {
    std::exit(-1);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  handle = glfwCreateWindow(size.x, size.y, WINDOW_TITLE, NULL, NULL);
  if (!handle) {
    glfwTerminate();
    std::exit(-1);
  }

  glfwSetInputMode(handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetInputMode(handle, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
  glfwSetKeyCallback(handle, on_key);

  glfwMakeContextCurrent(handle);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    glfwTerminate();
    std::exit(-1);
  }
}

Window::~Window() { glfwTerminate(); }
