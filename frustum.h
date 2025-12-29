#pragma once

#include <array>
#include <glm/glm.hpp>

struct Plane {
  glm::vec3 normal;
  float d;
};

struct Frustum {
  std::array<Plane, 6> planes;
};

struct AABB {
  glm::vec3 min;
  glm::vec3 max;
};

Frustum extract_frustum(const glm::mat4 &view_proj);
bool intersects(const Frustum &frustum, const AABB &aabb);
