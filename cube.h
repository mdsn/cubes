#pragma once
#include <glm/vec3.hpp>

struct CubeTex {
  int t[6];
  CubeTex(int front, int right, int left, int back, int bottom, int top);
};

class Cube {
  CubeTex tex;

public:
  const glm::ivec3 world_pos;
  const glm::ivec3 chunk_pos;
  Cube(glm::ivec3 world_pos, glm::ivec3 chunk_pos, const CubeTex &tex);
  const CubeTex &texture() const;
};
