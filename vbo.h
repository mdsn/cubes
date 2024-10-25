#pragma once
#include <cstddef>
#include <glad/glad.h>

class VBO {
  GLuint id;

public:
  VBO(size_t size, GLfloat *data);
  ~VBO();
  void bind() const;
};