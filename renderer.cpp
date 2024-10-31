#include <glm/gtc/matrix_transform.hpp>
#include "renderer.h"
#include "font.h"

void clear_screen() {
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

Renderer::Renderer(const glm::vec2 window_size)
    : world_shader{"shaders/cubeVertex.glsl", "shaders/cubeFragment.glsl"},
      world_texture{"resources/fogletexture.png"},
      font_shader{"shaders/textVertex.glsl", "shaders/textFragment.glsl"},
      font_texture{"resources/fixedsys.png"} {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  world_shader.use();
  world_shader.set_int("fogletexture", 0);
  world_shader.set_mat4fv(
      "proj", glm::perspective(glm::radians(45.0f),
                               window_size.x / window_size.y, 1.0f, 100.0f));

  font_shader.use();
  font_shader.set_int("font", 0);
  font_shader.set_mat4fv("proj", glm::ortho(0.0f, window_size.x, window_size.y,
                                            0.0f, -1.0f, 1.0f));
}

void Renderer::render_world(const std::vector<GLfloat> &vertices,
                            const glm::mat4 &view, const bool wireframe,
                            const bool update_vertices) const {
  constexpr int VERTEX_DATA_SIZE = 6;
  glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
  world_shader.use();
  world_shader.set_mat4fv("view", view);
  world_texture.bind();
  world_vao.bind();
  if (update_vertices) {
    world_vbo.write(vertices.size() * sizeof(GLfloat), vertices.data());
    world_shader.attr("position", 3, GL_FLOAT, VERTEX_DATA_SIZE * sizeof(float),
                      nullptr);
    world_shader.attr("texcoord", 2, GL_FLOAT, VERTEX_DATA_SIZE * sizeof(float),
                      reinterpret_cast<void *>(3 * sizeof(float)));
    world_shader.attr("intensity", 1, GL_FLOAT,
                      VERTEX_DATA_SIZE * sizeof(float),
                      reinterpret_cast<void *>(5 * sizeof(float)));
  }
  glDrawArrays(GL_TRIANGLES, 0, vertices.size() / VERTEX_DATA_SIZE);
  VAO::unbind();
}

void Renderer::render_ui(const Debug &debug) const {
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  font_shader.use();
  font_texture.bind();
  font_vao.bind();
  const auto lines = debug.lines();
  std::vector<GLfloat> quad = make_quads(lines);
  font_vbo.write(quad.size() * sizeof(GLfloat), quad.data());
  font_shader.attr("vertex", 4, GL_FLOAT, 4 * sizeof(GLfloat), nullptr);
  glDrawArrays(GL_TRIANGLES, 0, quad.size() / 4);
  VAO::unbind();
}
