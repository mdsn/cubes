#include <algorithm>
#include <vector>
#include <array>

#include "cube.h"

#include <glm/vec2.hpp>

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

std::array<Vertex, 6> Face::points() const {
  return std::array{
      Vertex{vertices[indices[0]], texture[indices[0]]},
      Vertex{vertices[indices[1]], texture[indices[1]]},
      Vertex{vertices[indices[2]], texture[indices[2]]},
      Vertex{vertices[indices[3]], texture[indices[3]]},
      Vertex{vertices[indices[4]], texture[indices[4]]},
      Vertex{vertices[indices[5]], texture[indices[5]]},
  };
}

// wind triangles counter-clockwise to face front. Each 6 element vector
// indexes into the four vertices that make up a face, defining two triangles
// that share two vertices.
constexpr std::array<Face, 6> positions{
    {// front ACD, ABC (positive z)
     {FaceDirection::front, {A, B, C, D}, {0, 2, 3, 0, 1, 2}},
     // right BGC, BFG (positive x)
     {FaceDirection::right, {F, B, C, G}, {1, 3, 2, 1, 0, 3}},
     // left AHE, ADH (negative x)
     {FaceDirection::left, {E, A, D, H}, {1, 3, 0, 1, 2, 3}},
     // back FHG, FEH (negative z)
     {FaceDirection::back, {E, F, G, H}, {1, 3, 2, 1, 0, 3}},
     // bottom AEF, AFB (negative y)
     {FaceDirection::bottom, {E, A, B, F}, {1, 0, 3, 1, 3, 2}},
     // top DCG, DGH (positive y)
     {FaceDirection::top, {H, D, C, G}, {1, 2, 3, 1, 3, 0}}}};

// the entire texture sample is 1 "logical" unit wide. It is split in 16 by
// 16 tiles, each a square 1/16 = 0.0625 units wide
constexpr float tw{0.0625};

CubeTex::CubeTex(const int front, const int right, const int left,
                 const int back, const int bottom, const int top)
    : t{front, right, left, back, bottom, top} {}

Cube::Cube(const glm::vec3 world_pos, const glm::ivec3 chunk_pos,
           const CubeTex &tex)
    : tex(tex), world_pos(world_pos), chunk_pos(chunk_pos) {}

void Cube::emit_vertices(std::vector<GLfloat> &vec,
                         const std::vector<FaceDirection> &faces) const {
  // 6 components: 3 for position, 2 for texture coord, 1 for color intensity
  // layout defined in specify_cube_vertex_attributes
  int i = 0;
  for (const Face &face : positions) {
    if (std::ranges::find(faces, face.direction) == std::end(faces)) {
      i++;
      continue;
    }

    for (const auto &[xyz, uv] : face.points()) {
      const int tx{tex.t[i] % 16};
      const int ty{tex.t[i] / 16};
      const float du{tw * tx};
      const float dv{tw * ty};
      vec.push_back(world_pos.x + .5 * xyz.x);
      vec.push_back(world_pos.y + .5 * xyz.y);
      vec.push_back(world_pos.z + .5 * xyz.z);
      vec.push_back(du + (uv.x ? tw : 0));
      vec.push_back(dv + (uv.y ? tw : 0));
      vec.push_back(face.direction == FaceDirection::front ? 0.7f :
                    face.direction == FaceDirection::right ? 0.5f :
                    1.0f);
    }

    i++;
  }
}
