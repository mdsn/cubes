#pragma once

#include <glm/glm.hpp>
#include "chunk.h"

class World {
  glm::dvec2 pos; // player pos
  Chunk chunk;   // current chunk under player pos
  std::vector<GLfloat> chunk_vertices;
public:
  World();
  void render() const;
  std::vector<GLfloat> &vertices();
};