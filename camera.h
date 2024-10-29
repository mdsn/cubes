#pragma once

#include <glm/glm.hpp>

// https://songho.ca/opengl/gl_camera.html
struct Camera {
  glm::vec3 pos{0.0f};
  glm::vec3 up{0.0f, 1.0f, 0.0f};
  float yaw{0}, pitch{0};

  explicit Camera(const glm::vec3 pos) : pos(pos) {}

  void update(float dx, float dy);
  glm::vec3 front() const;
  glm::mat4 view() const;
};
