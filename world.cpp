#include "world.h"

std::vector<glm::ivec2> neighbors(glm::ivec2 pos) {
  return std::vector{
      pos + glm::ivec2{-1, -1}, pos + glm::ivec2{-1, 0}, glm::ivec2{-1, 1},
      pos + glm::ivec2{0, -1},  pos + glm::ivec2{0, 0},  pos + glm::ivec2{0, 1},
      pos + glm::ivec2{1, -1},  pos + glm::ivec2{1, 0},  pos + glm::ivec2{1, 1},
  };
}

World::World() : pos{0, 0} {
  for (auto coord : neighbors(pos)) {
    Chunk c{coord.x, coord.y};
    c.emit_cubes(chunk_vertices);
    chunks.push_back(c);
  }
}

std::vector<GLfloat> &World::vertices() {
  if (chunk_changed) {
    // chunk_vertices.clear();
    // chunk.emit_cubes(chunk_vertices);
  }
  return chunk_vertices;
}
