#pragma once
#include "camera.h"
#include "debug.h"
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
  explicit Renderer(const glm::vec2 window_size);

  void render_world(const World &world, const Camera &camera,
                             const bool wireframe,
                             const bool update_vertices) const;
  void render_ui(const Debug &debug) const;
};