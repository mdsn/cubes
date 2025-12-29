#pragma once

#include <cstdint>
#include <vector>

#include <glm/glm.hpp>

struct Vertex {
  glm::vec3 position;
  glm::vec2 uv;
  float intensity;
};

struct Mesh {
  std::vector<Vertex> vertices;
  std::vector<uint32_t> indices;
};
