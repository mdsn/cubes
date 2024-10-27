#pragma once

#include <string>
#include <glm/vec3.hpp>

struct Debug {
  glm::vec3 camera_pos;
  float time_delta;

  std::vector<std::string> lines() const;
};