#pragma once
#include "debug.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "world.h"

void clear_screen();

class Renderer {
  Shader world_shader;
  Texture world_texture;
  VAO world_vao;
  VBO world_vbo;
  EBO world_ebo;

  Shader font_shader;
  Texture font_texture;
  VAO font_vao;
  VBO font_vbo;

public:
  explicit Renderer(glm::vec2 window_size);

  void render_world(const Mesh &mesh, const std::vector<ChunkDraw> &draws,
                    const glm::mat4 &view, bool wireframe,
                    bool update_vertices) const;
  void render_ui(const Debug &debug) const;

private:
  glm::mat4 world_proj;
};
