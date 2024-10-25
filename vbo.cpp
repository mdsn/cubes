#include "vbo.h"

VBO::VBO() {
  glGenBuffers(1, &id);
  glBindBuffer(GL_ARRAY_BUFFER, id);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VBO::~VBO() { glDeleteBuffers(1, &id); }

void VBO::bind() const { glBindBuffer(GL_ARRAY_BUFFER, id); }

void VBO::write(size_t size, GLfloat *data) const {
  bind();
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}