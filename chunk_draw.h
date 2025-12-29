#pragma once

#include "frustum.h"

struct ChunkDraw {
  glm::ivec2 chunk_pos;
  size_t index_offset;
  size_t index_count;
  AABB bounds;
};
