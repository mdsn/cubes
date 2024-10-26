#pragma once
#include "camera.h"
#include "shader.h"
#include "texture.h"
#include "vao.h"
#include "vbo.h"
#include "world.h"

class Renderer {
  Shader world_shader;
  Texture world_texture;
  VAO world_vao;
  VBO world_vbo;

  Shader font_shader;
  Texture font_texture;
  VAO font_vao;
  VBO font_vbo;

public:
  Renderer(World &world);

  void prepare_world(World &world, bool wireframe, const Camera &camera);
  void prepare_ui();
};