#include "chunk.h"

#include "FastNoiseLite.h"

float get_noise(FastNoiseLite noise, float x, float y) {
  return noise.GetNoise(x, y) / 2.0 + 0.5;
}

Chunk::Chunk(const int x, const int z) : cubes({}) {
  CubeTex tex{16, 16, 16, 16, 0, 32};
  CubeTex water{202, 202, 202, 202, 202, 202};
  FastNoiseLite noise;

  for (int i = 0; i < CHUNK_SIZE; i++)
    for (int j = 0; j < CHUNK_SIZE; j++) {
      const int ti = i - CHUNK_SIZE / 2;
      const int tj = j - CHUNK_SIZE / 2;
      const float _x = x * CHUNK_SIZE + ti;
      const float _z = z * CHUNK_SIZE + tj;
      float _y = get_noise(noise, _x, _z) +
                 0.5f * get_noise(noise, 2 * _x, 2 * _z) +
                 0.25f * get_noise(noise, 4 * _x, 4 * _z);
      _y = _y / (1 + 0.5 + 0.25);
      _y = std::round(_y * 14) / 14;
      _y = std::round(13.0f * _y);
      if (_y < 4)
        cubes.emplace_back(glm::vec3(_x, _y, _z), glm::ivec3(i, _y, j), water);
      else
        cubes.emplace_back(glm::vec3(_x, _y, _z), glm::ivec3(i, _y, j), tex);
      chunk_map[i][j] = true;
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
  return pos.x >= 0 and pos.x < CHUNK_SIZE and
         pos.y == 0 // XXX y assumed to be 0 in the single-plank chunks
         and pos.z >= 0 and pos.z < CHUNK_SIZE;
}

void Chunk::emit_cubes(std::vector<GLfloat> &vec) const {
  // TODO: also check neighbor chunk--will be necessary for terrain
  for (const Cube &cube : cubes) {
    std::vector<FaceDirection> faces{};
    for (auto &[face, neighbor] : cube_neighbors(cube.chunk_pos)) {
      if (!within_chunk_bounds(neighbor) or !chunk_map[neighbor.x][neighbor.z])
        faces.push_back(face);
    }
    cube.emit_vertices(vec, faces);
  }
}
