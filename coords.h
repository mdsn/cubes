#pragma once

#include <cmath>
#include <glm/glm.hpp>

#include "chunk_constants.h"

namespace coords {
inline int floor_div(const int numerator, const int denominator) {
  const int quotient = numerator / denominator;
  const int remainder = numerator % denominator;
  if (remainder != 0 && numerator < 0)
    return quotient - 1;
  return quotient;
}

inline glm::ivec2 world_to_chunk_pos(const glm::ivec3 world_pos) {
  return glm::ivec2{floor_div(world_pos.x, CHUNK_SIZE),
                    floor_div(world_pos.z, CHUNK_SIZE)};
}

inline glm::ivec3 world_to_local_pos(const glm::ivec3 world_pos) {
  const glm::ivec2 chunk_pos = world_to_chunk_pos(world_pos);
  return glm::ivec3{world_pos.x - chunk_pos.x * CHUNK_SIZE, world_pos.y,
                    world_pos.z - chunk_pos.y * CHUNK_SIZE};
}

inline glm::ivec2 pos_to_chunk(const glm::vec3 pos) {
  return glm::ivec2{floor_div(static_cast<int>(std::floor(pos.x)), CHUNK_SIZE),
                    floor_div(static_cast<int>(std::floor(pos.z)), CHUNK_SIZE)};
}
} // namespace coords
