#pragma once

#include <string>
#include <glm/glm.hpp>

struct Debug {
  glm::vec3 camera_pos;
  glm::ivec2 chunk;
  float time_delta;

  std::vector<std::string> lines() const;
};