#pragma once
#include <cstddef>
#include <glad/glad.h>

class VBO {
  GLuint id;

public:
  VBO();
  ~VBO();
  void bind() const;
  void write(size_t size, GLfloat *data) const;
};