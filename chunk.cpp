#include "chunk.h"

Chunk::Chunk(const int x, const int z) : x(x), z(z), cubes({}) {
  CubeTex tex{16, 16, 16, 16, 0, 32};

  for (int i = 0; i < CHUNK_SIZE; i++)
    for (int j = 0; j < CHUNK_SIZE; j++) {
      int ti = i - CHUNK_SIZE / 2;
      int tj = j - CHUNK_SIZE / 2;
      cubes.emplace_back(static_cast<float>(x * CHUNK_SIZE + ti), 0,
                         static_cast<float>(z * CHUNK_SIZE + tj), i, 0, j, tex);
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
  return pos.x >= 0 and pos.x < CHUNK_SIZE and pos.y == 0 // XXX
         and pos.z >= 0 and pos.z < CHUNK_SIZE;
}

void Chunk::emit_cubes(std::vector<GLfloat> &vec) const {
  // TODO: also check neighbor chunk--will be necessary for terrain
  for (const Cube &cube : cubes) {
    std::vector<FaceDirection> faces{};
    for (auto &[face, neighbor] : cube_neighbors(cube.iposition())) {
      if (!within_chunk_bounds(neighbor) or !chunk_map[neighbor.x][neighbor.z])
        faces.push_back(face);
    }
    cube.emit_vertices(vec, faces);
  }
}
