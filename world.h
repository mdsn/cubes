#pragma once

#include <glm/glm.hpp>
#include "chunk.h"

class World {
  glm::dvec2 pos; // player pos
  std::vector<GLfloat> chunk_vertices;

public:
  bool chunk_changed = true;
  Chunk chunk; // current chunk under player pos
  World();
  std::vector<GLfloat> &vertices();
};