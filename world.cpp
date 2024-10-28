#include "world.h"

World::World() : pos{0, 0}, chunk{0, 0} { chunk.emit_cubes(chunk_vertices); }

std::vector<GLfloat> &World::vertices() {
  if (chunk_changed) {
    chunk_vertices.clear();
    chunk.emit_cubes(chunk_vertices);
  }
  return chunk_vertices;
}
