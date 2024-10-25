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

void check_error(const GLuint id, GLenum type) {
  void (*query)(GLuint, GLenum, GLint *);
  void (*get_info)(GLuint, GLsizei, GLsizei *, GLchar *);
  std::string msg;

  switch (type) {
  case GL_COMPILE_STATUS:
    query = glGetShaderiv;
    get_info = glGetShaderInfoLog;
    msg = "shader compilation failed: ";
    break;
  case GL_LINK_STATUS:
    query = glGetProgramiv;
    get_info = glGetProgramInfoLog;
    msg = "program linkage failed: ";
    break;
  }

  GLint success{0};
  query(id, type, &success);

  if (success == GL_FALSE) {
    GLint log_size{0};
    query(id, GL_INFO_LOG_LENGTH, &log_size);
    std::vector<GLchar> log(log_size);
    get_info(id, log_size, &log_size, log.data());
    std::string err = std::string(log.begin(), log.end());
    std::cerr << msg << err << std::endl;
  }
}

GLuint load_shader(GLenum type, const char *path) {
  const std::string src{read_file(path)};
  const char *csrc{src.c_str()};
  const GLuint id{glCreateShader(type)};
  glShaderSource(id, 1, &csrc, NULL);
  glCompileShader(id);
  check_error(id, GL_COMPILE_STATUS);
  return id;
}

Shader::Shader(const char *path_vert, const char *path_frag) {
  id = glCreateProgram();
  const GLuint vsh = load_shader(GL_VERTEX_SHADER, path_vert);
  const GLuint fsh = load_shader(GL_FRAGMENT_SHADER, path_frag);
  glAttachShader(id, vsh);
  glAttachShader(id, fsh);
  glBindFragDataLocation(id, 0, "outColor");
  glLinkProgram(id);
  check_error(id, GL_LINK_STATUS);
  glDetachShader(id, vsh);
  glDetachShader(id, fsh);
  glDeleteShader(vsh);
  glDeleteShader(fsh);
}

void Shader::use() const { glUseProgram(id); }
Shader::~Shader() { glDeleteProgram(id); }

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
