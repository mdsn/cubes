#include <iostream>
#include "texture.h"

#include <SOIL2/SOIL2.h>

Texture::Texture(const char *path) {
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
  SOIL_load_OGL_texture(path, SOIL_LOAD_AUTO, id,
                        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y |
                            SOIL_FLAG_NTSC_SAFE_RGB |
                            SOIL_FLAG_COMPRESS_TO_DXT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

Texture::~Texture() {
  glDeleteTextures(1, &id);
  std::cout << "Texture: goodbye" << std::endl;
}

void Texture::bind() const { glBindTexture(GL_TEXTURE_2D, id); }
