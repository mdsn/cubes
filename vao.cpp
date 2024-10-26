#include <iostream>
#include "vao.h"

VAO::VAO() { glGenVertexArrays(1, &id); }

VAO::~VAO() { glDeleteVertexArrays(1, &id); }

void VAO::bind() const { glBindVertexArray(id); }

void VAO::unbind() { glBindVertexArray(0); }
