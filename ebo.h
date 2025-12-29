#pragma once
#include <cstddef>
#include <cstdint>
#include <glad/glad.h>

class EBO {
  GLuint id;

public:
  EBO();
  ~EBO();
  void bind() const;
  void write(size_t size, const uint32_t *data) const;
};
