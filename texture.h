#pragma once
#include <glad/glad.h>

class Texture {
  GLuint id;

public:
  Texture(const char *path);
  ~Texture();
  void bind() const;
};