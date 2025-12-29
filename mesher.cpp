#include "mesher.h"

#include <array>

namespace {
enum class FaceDirection { front, right, left, back, bottom, top };

// 6 faces, 4 vertices per face, 3 components per vertex
//      H--------G
//  D--------C   |
//  |   |    |   |
//  |   |    |   |
//  |   E----|-- F
//  A--------B
constexpr glm::vec3 A{-1, -1, +1};
constexpr glm::vec3 B{+1, -1, +1};
constexpr glm::vec3 C{+1, +1, +1};
constexpr glm::vec3 D{-1, +1, +1};
constexpr glm::vec3 E{-1, -1, -1};
constexpr glm::vec3 F{+1, -1, -1};
constexpr glm::vec3 G{+1, +1, -1};
constexpr glm::vec3 H{-1, +1, -1};

struct Face {
  FaceDirection direction;
  glm::ivec3 neighbor_offset;
  glm::vec3 vertices[4];
  int indices[6];
  glm::ivec2 texture[4]{{0, 0}, {1, 0}, {1, 1}, {0, 1}};
};

// wind triangles counter-clockwise to face front. Each 6 element vector
// indexes into the four vertices that make up a face, defining two triangles
// that share two vertices.
constexpr std::array<Face, 6> kFaces{
    {// front ACD, ABC (positive z)
     {FaceDirection::front, {0, 0, 1}, {A, B, C, D}, {0, 2, 3, 0, 1, 2}},
     // right BGC, BFG (positive x)
     {FaceDirection::right, {1, 0, 0}, {F, B, C, G}, {1, 3, 2, 1, 0, 3}},
     // left AHE, ADH (negative x)
     {FaceDirection::left, {-1, 0, 0}, {E, A, D, H}, {1, 3, 0, 1, 2, 3}},
     // back FHG, FEH (negative z)
     {FaceDirection::back, {0, 0, -1}, {E, F, G, H}, {1, 3, 2, 1, 0, 3}},
     // bottom AEF, AFB (negative y)
     {FaceDirection::bottom, {0, -1, 0}, {E, A, B, F}, {1, 0, 3, 1, 3, 2}},
     // top DCG, DGH (positive y)
     {FaceDirection::top, {0, 1, 0}, {H, D, C, G}, {1, 2, 3, 1, 3, 0}}}};

float face_intensity(const FaceDirection direction) {
  return direction == FaceDirection::front ? 0.7f
         : direction == FaceDirection::right ? 0.5f
                                             : 1.0f;
}

// the entire texture sample is 1 "logical" unit wide. It is split in 16 by
// 16 tiles, each a square 1/16 = 0.0625 units wide
constexpr float kTileWidth{0.0625f};
} // namespace

Mesh build_chunk_mesh(const Chunk &chunk, const glm::ivec2 chunk_pos,
                      const std::function<bool(glm::ivec3)> &is_solid_at_world) {
  static_cast<void>(chunk_pos);
  Mesh mesh{};
  for (const Cube &cube : chunk.cube_list()) {
    const CubeTex &tex = cube.texture();
    int face_index = 0;
    for (const Face &face : kFaces) {
      const glm::ivec3 neighbor_world = cube.world_pos + face.neighbor_offset;
      if (!is_solid_at_world(neighbor_world)) {
        for (int idx : face.indices) {
          const int tx{tex.t[face_index] % 16};
          const int ty{tex.t[face_index] / 16};
          const float du{kTileWidth * tx};
          const float dv{kTileWidth * ty};
          const glm::vec3 xyz = face.vertices[idx];
          const glm::ivec2 uv = face.texture[idx];
          mesh.vertices.push_back(Vertex{
              glm::vec3{cube.world_pos.x + 0.5f * xyz.x,
                        cube.world_pos.y + 0.5f * xyz.y,
                        cube.world_pos.z + 0.5f * xyz.z},
              glm::vec2{du + (uv.x ? kTileWidth : 0.0f),
                        dv + (uv.y ? kTileWidth : 0.0f)},
              face_intensity(face.direction),
          });
        }
      }
      face_index++;
    }
  }

  return mesh;
}
