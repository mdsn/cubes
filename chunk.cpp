#include "chunk.h"

void make_chunk(std::vector<GLfloat> &vec, int x, int z) {
  CubeTex tex{16, 16, 16, 16, 0, 32};

  for (int i = 0; i < CHUNK_SIZE; i++)
    for (int j = 0; j < CHUNK_SIZE; j++) {
      Cube q{static_cast<float>(x * CHUNK_SIZE + i), 0,
             static_cast<float>(z * CHUNK_SIZE + j), tex};
      q.emit_faces(vec);
    }
}
