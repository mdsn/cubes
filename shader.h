#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

// OpenGL program abstraction.
// Compiles shaders, keeps track of the program id, and provides an interface to
// set uniforms and enable the program.
// Modeled after:
// https://github.com/JoeyDeVries/LearnOpenGL/blob/master/includes/learnopengl/shader.h
class Shader {
public:
  GLuint id;
  Shader(const char *path_vert, const char *path_frag);
  ~Shader();
  
  void use();

  void set_int(const std::string &name, GLint value) const;
  void set_float(const std::string &name, GLfloat value) const;
  void set_mat4fv(const std::string &name, const glm::mat4 &mat) const;
};