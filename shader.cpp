#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"

std::string read_file(const char *path) {
  std::ifstream ifs(path);
  std::string str((std::istreambuf_iterator<char>(ifs)),
                  (std::istreambuf_iterator<char>()));
  return str;
}

GLuint load_shader(GLenum type, const char *path) {
  std::string src{read_file(path)};
  const char *csrc{src.c_str()};
  GLuint id{glCreateShader(type)};
  glShaderSource(id, 1, &csrc, NULL);
  glCompileShader(id);
  GLint success{0};
  glGetShaderiv(id, GL_COMPILE_STATUS, &success);
  // TODO factor out all this error log boilerplate
  if (success == GL_FALSE) {
    GLint log_size{0};
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &log_size);
    std::vector<GLchar> log(log_size);
    glGetShaderInfoLog(id, log_size, &log_size, log.data());
    std::string err = std::string(log.begin(), log.end());
    std::cerr << "shader compilation failed: " << err << std::endl;
  }
  return id;
}

Shader::Shader(const char *path_vert, const char *path_frag) {
  id = glCreateProgram();
  GLuint vsh = load_shader(GL_VERTEX_SHADER, path_vert);
  GLuint fsh = load_shader(GL_FRAGMENT_SHADER, path_frag);
  glAttachShader(id, vsh);
  glAttachShader(id, fsh);
  glBindFragDataLocation(id, 0, "outColor");
  glLinkProgram(id);
  GLint success{0};
  glGetProgramiv(id, GL_LINK_STATUS, &success);
  if (success == GL_FALSE) {
    GLint log_size{0};
    glGetProgramiv(id, GL_INFO_LOG_LENGTH, &log_size);
    std::vector<GLchar> log(log_size);
    glGetProgramInfoLog(id, log_size, &log_size, log.data());
    std::string err = std::string(log.begin(), log.end());
    std::cerr << "program linkage failed: " << err << std::endl;
  }
  glDetachShader(id, vsh);
  glDetachShader(id, fsh);
  glDeleteShader(vsh);
  glDeleteShader(fsh);
}

void Shader::use() { glUseProgram(id); }

void Shader::set_int(const std::string &name, GLint value) const {
  glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::set_float(const std::string &name, GLfloat value) const {
  glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::set_mat4fv(const std::string &name, const glm::mat4 &mat) const {
  glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE,
                     glm::value_ptr(mat));
}
