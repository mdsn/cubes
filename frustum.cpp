#include "frustum.h"

#include <cmath>

namespace {
glm::vec4 row(const glm::mat4 &m, int r) {
  return glm::vec4{m[0][r], m[1][r], m[2][r], m[3][r]};
}

Plane normalize_plane(const glm::vec4 p) {
  const glm::vec3 n{p.x, p.y, p.z};
  const float len = std::sqrt(glm::dot(n, n));
  if (len == 0.0f)
    return Plane{n, p.w};
  return Plane{n / len, p.w / len};
}
} // namespace

Frustum extract_frustum(const glm::mat4 &view_proj) {
  const glm::vec4 r0 = row(view_proj, 0);
  const glm::vec4 r1 = row(view_proj, 1);
  const glm::vec4 r2 = row(view_proj, 2);
  const glm::vec4 r3 = row(view_proj, 3);

  Frustum frustum{};
  frustum.planes[0] = normalize_plane(r3 + r0); // left
  frustum.planes[1] = normalize_plane(r3 - r0); // right
  frustum.planes[2] = normalize_plane(r3 + r1); // bottom
  frustum.planes[3] = normalize_plane(r3 - r1); // top
  frustum.planes[4] = normalize_plane(r3 + r2); // near
  frustum.planes[5] = normalize_plane(r3 - r2); // far
  return frustum;
}

bool intersects(const Frustum &frustum, const AABB &aabb) {
  for (const Plane &plane : frustum.planes) {
    const glm::vec3 p{
        plane.normal.x >= 0.0f ? aabb.max.x : aabb.min.x,
        plane.normal.y >= 0.0f ? aabb.max.y : aabb.min.y,
        plane.normal.z >= 0.0f ? aabb.max.z : aabb.min.z,
    };
    if (glm::dot(plane.normal, p) + plane.d < 0.0f)
      return false;
  }
  return true;
}
