#pragma once

#include <glm/glm.hpp>
#include "chunk.h"

class World {
  glm::dvec2 pos; // player pos
  std::vector<GLfloat> chunk_vertices;
  std::vector<Chunk> chunks;

public:
  bool chunk_changed = true;
  // Chunk chunk; // current chunk under player pos--bring back to private

  World();
  std::vector<GLfloat> &vertices();
};