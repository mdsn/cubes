#pragma once

#include <functional>

#include <glm/glm.hpp>

#include "chunk.h"
#include "mesh.h"

Mesh build_chunk_mesh(const Chunk &chunk, glm::ivec2 chunk_pos,
                      const std::function<bool(glm::ivec3)> &is_solid_at_world);
