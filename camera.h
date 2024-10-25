#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// https://songho.ca/opengl/gl_camera.html
struct Camera {
  glm::vec3 pos{0.0f};
  glm::vec3 up{0.0f, 1.0f, 0.0f};
  float yaw{0}, pitch{0};

  Camera(glm::vec3 cPos) : pos(cPos) {}

  void update(float dx, float dy);
  glm::vec3 front() const;
  glm::mat4 view() const;
};
