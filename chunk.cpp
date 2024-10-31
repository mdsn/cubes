#include "chunk.h"

#include "FastNoiseLite.h"

float get_noise(FastNoiseLite noise, float x, float y) {
  return noise.GetNoise(x, y) / 2.0 + 0.5;
}

float column_height(FastNoiseLite &noise, float x, float z) {
  float _y = get_noise(noise, x, z) + 0.5f * get_noise(noise, 2 * x, 2 * z) +
             0.25f * get_noise(noise, 4 * x, 4 * z);
  _y = _y / (1 + 0.5 + 0.25);
  _y = std::round(_y * 14) / 14;
  return std::round(13.0f * _y);
}

Chunk::Chunk(const int chunk_x, const int chunk_z) : cubes({}) {
  CubeTex tex{16, 16, 16, 16, 0, 32};
  CubeTex water{202, 202, 202, 202, 202, 202};
  FastNoiseLite noise;

  for (int block_x = 0; block_x < CHUNK_SIZE; block_x++) {
    for (int block_z = 0; block_z < CHUNK_SIZE; block_z++) {
      const int tx = block_x - CHUNK_SIZE / 2;
      const int tz = block_z - CHUNK_SIZE / 2;
      const float _x = chunk_x * CHUNK_SIZE + tx;
      const float _z = chunk_z * CHUNK_SIZE + tz;
      const float _y = column_height(noise, _x, _z);

      for (int block_y = 0;
           block_y < CHUNK_SIZE && block_y <= static_cast<int>(_y); block_y++) {
        if (block_y < 4)
          cubes.emplace_back(glm::vec3(_x, block_y, _z),
                             glm::ivec3(block_x, block_y, block_z), water);
        else
          cubes.emplace_back(glm::vec3(_x, block_y, _z),
                             glm::ivec3(block_x, block_y, block_z), tex);
        chunk_map[block_x][block_y][block_z] = true;
      }
    }
  }
}

constexpr std::array neighbor_directions{
    std::make_pair(FaceDirection::front, glm::ivec3{0, 0, 1}),
    std::make_pair(FaceDirection::right, glm::ivec3{1, 0, 0}),   // right
    std::make_pair(FaceDirection::left, glm::ivec3{-1, 0, 0}),   // left
    std::make_pair(FaceDirection::back, glm::ivec3{0, 0, -1}),   // back
    std::make_pair(FaceDirection::bottom, glm::ivec3{0, -1, 0}), // bottom
    std::make_pair(FaceDirection::top, glm::ivec3{0, 1, 0}),     // top
};

std::vector<std::pair<FaceDirection, glm::ivec3>>
cube_neighbors(glm::ivec3 pos) {
  std::vector<std::pair<FaceDirection, glm::ivec3>> neighbors{};
  for (auto &[face, v] : neighbor_directions) {
    neighbors.emplace_back(std::make_pair(face, pos + v));
  }
  return neighbors;
}

bool within_chunk_bounds(glm::ivec3 pos) {
  return pos.x >= 0 and pos.x < CHUNK_SIZE and pos.y >= 0 and
         pos.y < CHUNK_SIZE and pos.z >= 0 and pos.z < CHUNK_SIZE;
}

void Chunk::emit_cubes(std::vector<GLfloat> &vec) const {
  // TODO: also check neighbor chunk--will be necessary for terrain
  for (const Cube &cube : cubes) {
    std::vector<FaceDirection> faces{};
    for (auto &[face, neighbor] : cube_neighbors(cube.chunk_pos)) {
      if (!within_chunk_bounds(neighbor) or
          !chunk_map[neighbor.x][neighbor.y][neighbor.z])
        faces.push_back(face);
    }
    cube.emit_vertices(vec, faces);
  }
}
