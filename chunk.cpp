#include "chunk.h"

#include <cassert>
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

struct Neighbor {
  FaceDirection face;
  glm::ivec3 world_pos;
};

constexpr std::array neighbor_directions{
    Neighbor{FaceDirection::front, glm::ivec3{0, 0, 1}},
    Neighbor{FaceDirection::right, glm::ivec3{1, 0, 0}},
    Neighbor{FaceDirection::left, glm::ivec3{-1, 0, 0}},
    Neighbor{FaceDirection::back, glm::ivec3{0, 0, -1}},
    Neighbor{FaceDirection::bottom, glm::ivec3{0, -1, 0}},
    Neighbor{FaceDirection::top, glm::ivec3{0, 1, 0}},
};

std::vector<Neighbor> neighboring_cube_positions(const Cube &cube) {
  std::vector<Neighbor> positions{};
  for (auto &[face, wpos] : neighbor_directions) {
    positions.emplace_back(Neighbor{face, cube.world_pos + wpos});
  }
  return positions;
}

int Chunk::floor_div(const int numerator, const int denominator) {
  const int quotient = numerator / denominator;
  const int remainder = numerator % denominator;
  if (remainder != 0 && numerator < 0)
    return quotient - 1;
  return quotient;
}

glm::ivec2 Chunk::world_to_chunk_pos(const glm::ivec3 world_pos) {
  return glm::ivec2{floor_div(world_pos.x, CHUNK_SIZE),
                    floor_div(world_pos.z, CHUNK_SIZE)};
}

glm::ivec3 Chunk::world_to_local_pos(const glm::ivec3 world_pos) {
  const glm::ivec2 chunk_pos = world_to_chunk_pos(world_pos);
  return glm::ivec3{world_pos.x - chunk_pos.x * CHUNK_SIZE,
                    world_pos.y,
                    world_pos.z - chunk_pos.y * CHUNK_SIZE};
}

bool Chunk::within_local_bounds(const glm::ivec3 pos) {
  return pos.x >= 0 && pos.x < CHUNK_SIZE && pos.y >= 0 &&
         pos.y < CHUNK_HEIGHT && pos.z >= 0 && pos.z < CHUNK_SIZE;
}

bool Chunk::is_solid_at_world(const ChunkMap &chunks,
                              const glm::ivec3 world_pos) {
  const glm::ivec2 chunk_pos = world_to_chunk_pos(world_pos);
  auto it = chunks.find(chunk_pos);
  if (it == chunks.end()) {
    // Treat missing chunks as air so faces render until neighbors load.
    // TODO trigger boundary remesh when new chunks arrive.
    return false;
  }

  const glm::ivec3 local_pos = world_to_local_pos(world_pos);
  const glm::ivec3 roundtrip_world{
      chunk_pos.x * CHUNK_SIZE + local_pos.x, world_pos.y,
      chunk_pos.y * CHUNK_SIZE + local_pos.z};
  assert(roundtrip_world.x == world_pos.x);
  assert(roundtrip_world.z == world_pos.z);
  if (!within_local_bounds(local_pos))
    return false;

  return it->second.chunk_map[local_pos.x][local_pos.y][local_pos.z];
}

void Chunk::emit_cubes(std::vector<GLfloat> &vec) const {
  for (const Cube &cube : cubes) {
    std::vector<FaceDirection> faces{};
    for (auto &[face, wpos] : neighboring_cube_positions(cube)) {
      if (!is_solid_at_world(chunks, wpos)) {
        faces.push_back(face);
      }
    }
    cube.emit_vertices(vec, faces);
  }
}
