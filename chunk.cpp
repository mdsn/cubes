#include "chunk.h"

#include "FastNoiseLite.h"

float get_noise(const FastNoiseLite &noise, const float x, const float y) {
  return noise.GetNoise(x, y) / 2.0 + 0.5;
}

int column_height(const FastNoiseLite &noise, const float x, const float z) {
  float _y = get_noise(noise, x, z) + 0.5f * get_noise(noise, 2 * x, 2 * z) +
             0.25f * get_noise(noise, 4 * x, 4 * z);
  _y = _y / (1 + 0.5 + 0.25);
  _y = std::round(_y * 14) / 14;
  return static_cast<int>(std::round(13.0f * _y));
}

Chunk::Chunk(ChunkMap &chunks, const int chunk_x, const int chunk_z)
    : chunks(chunks), cubes({}) {
  // TODO more block types
  CubeTex tex{13, 16, 16, 10, 0, 32};
  CubeTex water{202, 202, 202, 202, 202, 202};
  FastNoiseLite noise; // TODO move this into a member of World

  for (int block_x = 0; block_x < CHUNK_SIZE; block_x++) {
    for (int block_z = 0; block_z < CHUNK_SIZE; block_z++) {
      // world coordinates across all chunks
      const int _x = chunk_x * CHUNK_SIZE + block_x;
      const int _z = chunk_z * CHUNK_SIZE + block_z;
      const int _y = column_height(noise, _x, _z);

      for (int block_y = 0; block_y < CHUNK_SIZE && block_y <= _y; block_y++) {
        if (block_y < 4) // hardcoded water level to see some texture variety
          cubes.emplace_back(glm::ivec3(_x, block_y, _z),
                             glm::ivec3(block_x, block_y, block_z), water);
        else
          cubes.emplace_back(glm::ivec3(_x, block_y, _z),
                             glm::ivec3(block_x, block_y, block_z), tex);
        chunk_map[block_x][block_y][block_z] = true;
      }
    }
  }
}

const std::vector<Cube> &Chunk::cube_list() const { return cubes; }
