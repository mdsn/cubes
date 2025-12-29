#pragma once
#include <vector>
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/hash.hpp" // hash ivec2
#include "chunk_constants.h"
#include "cube.h"

class Chunk {
  using ChunkMap = std::unordered_map<glm::ivec2, Chunk>;

  const ChunkMap &chunks;
  std::vector<Cube> cubes;

public:
  std::array<std::array<std::array<bool, CHUNK_SIZE>, CHUNK_HEIGHT>, CHUNK_SIZE>
      chunk_map{};

  Chunk(ChunkMap &chunks, int chunk_x, int chunk_z);
  void emit_cubes(std::vector<GLfloat> &vec) const;

private:
  static bool within_local_bounds(glm::ivec3 pos);
  static bool is_solid_at_world(const ChunkMap &chunks,
                                glm::ivec3 world_pos);
};
