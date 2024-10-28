#include "chunk.h"

Chunk::Chunk(int x, int z) : x(x), z(z), cubes({}) {
  CubeTex tex{16, 16, 16, 16, 0, 32};

  for (int i = -CHUNK_SIZE / 2; i < CHUNK_SIZE / 2; i++)
    for (int j = -CHUNK_SIZE / 2; j < CHUNK_SIZE / 2; j++) {
      cubes.emplace_back(static_cast<float>(x * CHUNK_SIZE + i), 0,
                         static_cast<float>(z * CHUNK_SIZE + j), tex);
    }
}

void Chunk::emit_cubes(std::vector<GLfloat> &vec) const {
  for (const Cube &q : cubes)
    q.emit_faces(vec);
}
