#pragma once
#include <vector>

#include "cube.h"

#define CHUNK_SIZE 16
#define CHUNK_HEIGHT 256

void make_chunk(std::vector<GLfloat> &vec, int x, int z);

class Chunk {
  std::vector<Cube> cubes;
  std::array<std::array<std::array<bool, CHUNK_SIZE>, CHUNK_HEIGHT>, CHUNK_SIZE>
      chunk_map{};

public:
  Chunk(int chunk_x, int chunk_z);
  void emit_cubes(std::vector<GLfloat> &vec) const;
};