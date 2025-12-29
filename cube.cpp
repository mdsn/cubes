#include "cube.h"

CubeTex::CubeTex(const int front, const int right, const int left,
                 const int back, const int bottom, const int top)
    : t{front, right, left, back, bottom, top} {}

Cube::Cube(const glm::ivec3 world_pos, const glm::ivec3 chunk_pos,
           const CubeTex &tex)
    : tex(tex), world_pos(world_pos), chunk_pos(chunk_pos) {}

const CubeTex &Cube::texture() const { return tex; }
