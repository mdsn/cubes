#pragma once
#include <glad/glad.h>

// OpenGL program abstraction.
// Compiles shaders, keeps track of the program id, and provides an interface to
// set uniforms and enable the program.
// Modeled after:
// https://github.com/JoeyDeVries/LearnOpenGL/blob/master/includes/learnopengl/shader.h
class Shader {
public:
  GLuint id;
  Shader(const char *path_vert, const char *path_frag);
};