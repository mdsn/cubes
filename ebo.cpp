#include "ebo.h"

EBO::EBO() { glGenBuffers(1, &id); }

EBO::~EBO() { glDeleteBuffers(1, &id); }

void EBO::bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id); }

void EBO::write(const size_t size, const uint32_t *data) const {
  bind();
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
