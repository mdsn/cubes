#pragma once
#include <glad/glad.h>

class VAO {
  GLuint id;

public:
  VAO();
  ~VAO();
  void bind() const;
  static void unbind();
};