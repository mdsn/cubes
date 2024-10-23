#include "chunk.h"

void make_chunk(std::vector<GLfloat> &vec, int x, int z) {
  for (int i = 0; i < CHUNK_SIZE; i++)
    for (int j = 0; j < CHUNK_SIZE; j++)
      make_cube(vec, x * CHUNK_SIZE + i, 0, z * CHUNK_SIZE + j);
}
