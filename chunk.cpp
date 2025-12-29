#include "chunk.h"

#include "FastNoiseLite.h"

// XXX these two functions copy pasted from world.cpp
int _map_interval(const double x) {
  const float abs = std::abs(x);
  if (abs < 8.0)
    return 0;
  const int res = 1 + static_cast<int>(abs - 8) / 16;
  return x >= 0 ? res : -res;
}

// XXX these two functions copy pasted from world.cpp
glm::ivec2 _pos_to_chunk(const glm::vec3 pos) {
  return glm::ivec2{_map_interval(pos.x), _map_interval(pos.z)};
}

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
      // transform xz to put the middle of the chunk at the center
      const int tx = block_x - CHUNK_SIZE / 2;
      const int tz = block_z - CHUNK_SIZE / 2;
      // world coordinates across all chunks
      const int _x = chunk_x * CHUNK_SIZE + tx;
      const int _z = chunk_z * CHUNK_SIZE + tz;
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
  glm::ivec3 chunk_pos;
  glm::ivec3 world_pos;
};

constexpr std::array neighbor_directions{
    Neighbor{FaceDirection::front, glm::ivec3{0, 0, 1}, glm::ivec3{0, 0, 1}},
    Neighbor{FaceDirection::right, glm::ivec3{1, 0, 0}, glm::ivec3{1, 0, 0}},
    Neighbor{FaceDirection::left, glm::ivec3{-1, 0, 0}, glm::ivec3{-1, 0, 0}},
    Neighbor{FaceDirection::back, glm::ivec3{0, 0, -1}, glm::ivec3{0, 0, -1}},
    Neighbor{FaceDirection::bottom, glm::ivec3{0, -1, 0}, glm::ivec3{0, -1, 0}},
    Neighbor{FaceDirection::top, glm::ivec3{0, 1, 0}, glm::ivec3{0, 1, 0}},
};

std::vector<Neighbor> neighboring_cube_positions(const Cube &cube) {
  std::vector<Neighbor> positions{};
  for (auto &[face, cpos, wpos] : neighbor_directions) {
    positions.emplace_back(
        Neighbor{face, cube.chunk_pos + cpos, cube.world_pos + wpos});
  }
  return positions;
}

bool within_chunk_bounds(glm::ivec3 pos) {
  return pos.x >= 0 and pos.x < CHUNK_SIZE and pos.y >= 0 and
         pos.y < CHUNK_SIZE and pos.z >= 0 and pos.z < CHUNK_SIZE;
}

void Chunk::emit_cubes(std::vector<GLfloat> &vec) const {
  for (const Cube &cube : cubes) {
    std::vector<FaceDirection> faces{};
    for (auto &[face, cpos, wpos] : neighboring_cube_positions(cube)) {
      if (!within_chunk_bounds(cpos)) {
        // this neighbor cube is in the adjacent chunk--it must be on the
        // opposite end of the chunk, but sharing the two other coordinates;
        // which coordinates depends on the direction where the neighbor cube
        // lies.
        // TODO instead of _pos_to_chunk, have the chunk Just Know the chunk in
        // the face direction
        auto npos = _pos_to_chunk(wpos);
        auto it = chunks.find(npos);

        if (it == chunks.end()) {
          // Neighbor chunk missing; treat as air and emit face
          faces.push_back(face);
          continue;
        } else {
          // Neighbor chunk exists, check if the adjacent block exists.
          glm::ivec3 neighbor_chunk_pos = cpos;
          switch (face) {
          case FaceDirection::left:
            neighbor_chunk_pos.x = CHUNK_SIZE - 1;
            break;
          case FaceDirection::right:
            neighbor_chunk_pos.x = 0;
            break;
          case FaceDirection::front:
            neighbor_chunk_pos.z = 0;
            break;
          case FaceDirection::back:
            neighbor_chunk_pos.z = CHUNK_SIZE - 1;
            break;
          case FaceDirection::top: // ???
          case FaceDirection::bottom:
          default:
            break;
          }

          if (!it->second.chunk_map[neighbor_chunk_pos.x][neighbor_chunk_pos.y]
                                   [neighbor_chunk_pos.z]) {
            faces.push_back(face);
          }
        }
      } else if (!chunk_map[cpos.x][cpos.y][cpos.z]) {
        faces.push_back(face);
      }
    }
    cube.emit_vertices(vec, faces);
  }
}
