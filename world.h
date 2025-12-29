#pragma once

#include <unordered_map>
#include <optional>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/hash.hpp" // hash ivec2
#include "chunk.h"
#include "mesh.h"

class World {
  glm::vec3 player_position;
  Mesh chunk_mesh;
  std::unordered_map<glm::ivec2, Chunk> chunks;

public:
  bool chunk_changed = true;
  std::optional<glm::ivec2> prev_chunk;
  glm::ivec2 current_chunk;

  explicit World(glm::vec3 start_position);
  void set_position(glm::vec3 new_pos);
  void finished_rendering();
  const Mesh &mesh() const;
};
