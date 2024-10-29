#include "camera.h"

void Camera::update(float dx, float dy) {
  yaw += dx;   // yaw rotates camera left
  pitch += dy; // pitch rotates camera down
  pitch = glm::clamp(pitch, -89.0f, 89.0f);
  // std::cout << "pitch " << pitch << " yaw " << yaw << std::endl;
}

glm::vec3 Camera::front() const {
  glm::mat4 rotation =
      rotate(glm::mat4(1.0f), glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));
  rotation = rotate(rotation, glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
  return normalize(make_vec3(glm::vec4{0.0f, 0.0f, 1.0f, 0.0f} * rotation));
}

glm::mat4 Camera::view() const {
  // For the view matrix's coordinate system we want its z-axis to be
  // positive and because by convention (in OpenGL) the camera points
  // towards the negative z-axis we want to negate the direction vector.
  // If we switch the subtraction order around we now get a vector
  // pointing towards the camera's positive z-axis
  // https://learnopengl.com/Getting-started/Camera
  return lookAt(pos, pos - front(), up);
}
