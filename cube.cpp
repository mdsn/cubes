#include <vector>
#include <array>

#include "cube.h"

void make_cube(std::vector<GLfloat> &vec, float x, float y, float z) {
  // 6 faces, 4 vertices per face, 3 components per vertex
  //      H--------G
  //  D--------C   |
  //  |   |    |   |
  //  |   |    |   |
  //  |   E----|-- F
  //  A--------B
  constexpr std::array<float, 3> A{-1, -1, +1};
  constexpr std::array<float, 3> B{+1, -1, +1};
  constexpr std::array<float, 3> C{+1, +1, +1};
  constexpr std::array<float, 3> D{-1, +1, +1};
  constexpr std::array<float, 3> E{-1, -1, -1};
  constexpr std::array<float, 3> F{+1, -1, -1};
  constexpr std::array<float, 3> G{+1, +1, -1};
  constexpr std::array<float, 3> H{-1, +1, -1};
  constexpr std::array<std::array<std::array<float, 3>, 4>, 6> positions{{
      {A, B, C, D}, // ABCD front (positive z)
      {F, B, C, G}, // FBCG right (positive x)
      {E, A, D, H}, // EADH left (negative x)
      {E, F, G, H}, // EFGH back (negative z)
      {E, A, B, F}, // EABF bottom (negative y)
      {H, D, C, G}, // HDCG top (positive y)
  }};

  // wind triangles counter-clockwise to face front. Each 6 element vector
  // indexes into the four vertices that make up a face, defining two triangles
  // that share two vertices.
  constexpr int indices[6][6]{
      {0, 2, 3, 0, 1, 2}, // front ACD, ABC
      {1, 3, 2, 1, 0, 3}, // right BGC, BFG
      {1, 3, 0, 1, 2, 3}, // left AHE, ADH
      {1, 3, 2, 1, 0, 3}, // back FHG, FEH
      {1, 0, 3, 1, 3, 2}, // bottom AEF, AFB
      {1, 2, 3, 1, 3, 0}  // top DCG, DGH
  };

  // texture coordinates--6 faces, four total vertices (2 are shared between
  // the two adjacent triangles making up once face), 2 texture coordinates
  // on each corner (2D coordinate).
  constexpr float uv[6][4][2]{
      {{0, 0}, {1, 0}, {1, 1}, {0, 1}}, {{0, 0}, {1, 0}, {1, 1}, {0, 1}},
      {{0, 0}, {1, 0}, {1, 1}, {0, 1}}, {{0, 0}, {1, 0}, {1, 1}, {0, 1}},
      {{0, 0}, {1, 0}, {1, 1}, {0, 1}}, {{0, 0}, {1, 0}, {1, 1}, {0, 1}},
  };

  // the entire texture sample is 1 "logical" unit wide. It is split in 16 by
  // 16 tiles, each a square 1/16 = 0.0625 units wide
  float tw{0.0625};
  // tile coords in texture--(0,1) is the dirt with a bit of grass
  int tx{0};
  int ty{1};
  // transformed texture coords in texture-space. Each texture coordinate can
  // be either 0 or 1 of some tile
  //  +--------+   top left: (0,1)    top right: (1,1)
  //  |        |
  //  |        |
  //  |        |
  //  +--------+  low left: (0,0)     low right: (1,0)

  // the left coords share the component x = 1/16 tx
  // right coords share component x = 1/16 tx + 1/16

  // low coords share component y = 1/16 ty
  // top coords share component y = 1/16 ty + 1/16

  float du{tw * tx};
  float dv{tw * ty};
  float n{0.5};
  
  // 5 components: 3 for position, 2 for texture coord
  // layout defined in specify_cube_vertex_attributes
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      int ix = indices[i][j];
      vec.push_back(x + n * positions[i][ix][0]);
      vec.push_back(y + n * positions[i][ix][1]);
      vec.push_back(z + n * positions[i][ix][2]);
      vec.push_back(du + (uv[i][ix][0] ? tw : 0.0f));
      vec.push_back(dv + (uv[i][ix][1] ? tw : 0.0f));
    }
  }
}