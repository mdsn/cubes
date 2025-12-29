#pragma once

#include <functional>
#include <vector>

#include <glm/glm.hpp>

#include "chunk.h"
#include "mesh.h"

Mesh build_chunk_mesh(const Chunk &chunk, glm::ivec2 chunk_pos,
                      const std::function<bool(glm::ivec3)> &is_solid_at_world);

Mesh build_mesh_from_cubes(
    const std::vector<Cube> &cubes,
    const std::function<bool(glm::ivec3)> &is_solid_at_world);
