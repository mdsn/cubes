#include "vbo.h"

VBO::VBO(size_t size, GLfloat *data) {
  glGenBuffers(1, &id);
  glBindBuffer(GL_ARRAY_BUFFER, id);
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VBO::~VBO() { glDeleteBuffers(1, &id); }

void VBO::bind() const { glBindBuffer(GL_ARRAY_BUFFER, id); }
