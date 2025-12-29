#pragma once
#include <vector>
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/hash.hpp" // hash ivec2
#include "cube.h"

#define CHUNK_SIZE 16
#define CHUNK_HEIGHT 256

class Chunk {
  using ChunkMap = std::unordered_map<glm::ivec2, Chunk>;

  const ChunkMap &chunks;
  std::vector<Cube> cubes;

public:
  std::array<std::array<std::array<bool, CHUNK_SIZE>, CHUNK_HEIGHT>, CHUNK_SIZE>
      chunk_map{};

  Chunk(ChunkMap &chunks, int chunk_x, int chunk_z);
  void emit_cubes(std::vector<GLfloat> &vec) const;
};