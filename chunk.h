#pragma once
#include <vector>
#include <glad/glad.h>

#include "cube.h"

#define CHUNK_SIZE 16

void make_chunk(std::vector<GLfloat> &vec, int x, int z);

class Chunk {
  int x, z;
  std::vector<Cube> cubes;

public:
  Chunk(int x, int z);
  void emit_cubes(std::vector<GLfloat> &vec);
};