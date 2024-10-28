#pragma once

#include <optional>
#include <glm/glm.hpp>
#include "chunk.h"

class World {
  glm::vec3 player_position;
  std::vector<GLfloat> chunk_vertices;
  std::vector<Chunk> chunks;

public:
  bool chunk_changed = true;
  std::optional<glm::ivec2> prev_chunk;
  glm::ivec2 current_chunk;

  explicit World(glm::vec3 start_position);
  void set_position(glm::vec3 new_pos);
  void finished_rendering();
  const std::vector<GLfloat> &vertices() const;
};