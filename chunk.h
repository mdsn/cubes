#pragma once
#include <vector>

#include "cube.h"


#define CHUNK_SIZE 16

void make_chunk(std::vector<GLfloat> &vec, int x, int z);

class Chunk {
  std::vector<Cube> cubes;
  std::array<std::array<bool, CHUNK_SIZE>, CHUNK_SIZE> chunk_map{};

public:
  Chunk(int x, int z);
  void emit_cubes(std::vector<GLfloat> &vec) const;
};