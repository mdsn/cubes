#include <glm/gtc/matrix_transform.hpp>
#include "renderer.h"
#include "font.h"

Renderer::Renderer(World &world)
    : world_shader{"shaders/cubeVertex.glsl", "shaders/cubeFragment.glsl"},
      world_texture{"resources/fogletexture.png"},
      font_shader{"shaders/textVertex.glsl", "shaders/textFragment.glsl"},
      font_texture{"resources/fixedsys.png"} {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  world_shader.use();
  world_shader.set_int("fogletexture", 0);
  world_shader.set_mat4fv( // XXX 800x600 hardcoded
      "proj",
      glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 100.0f));

  font_shader.use();
  font_shader.set_int("font", 0);
  font_shader.set_mat4fv("proj",
                         glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f));
}

void Renderer::prepare_world(World &world, bool wireframe,
                             const Camera &camera) {
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
  world_shader.use();
  world_shader.set_mat4fv("view", camera.view());
  world_texture.bind();
  world_vao.bind();
}

void Renderer::render_World(World &world) {
  if (world.chunk_changed) {
    world_vbo.write(world.vertices().size() * sizeof(GLfloat),
                    world.vertices().data());
    world_shader.attr("position", 3, GL_FLOAT, 5 * sizeof(float), 0);
    world_shader.attr("texcoord", 2, GL_FLOAT, 5 * sizeof(float),
                      (void *)(3 * sizeof(float)));
    world.chunk_changed = false; // should do at update()?
  }
  glDrawArrays(GL_TRIANGLES, 0, world.vertices().size() / 5);
  VAO::unbind();
}

void Renderer::prepare_ui() {
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  font_shader.use();
  font_texture.bind();
  font_vao.bind();
}

void Renderer::render_ui(const Debug &debug) {
  auto lines = debug.lines();
  std::vector<GLfloat> quad = make_quads(lines);
  font_vbo.write(quad.size() * sizeof(GLfloat), quad.data());
  font_shader.attr("vertex", 4, GL_FLOAT, 4 * sizeof(GLfloat), 0);
  glDrawArrays(GL_TRIANGLES, 0, quad.size() / 4);
  VAO::unbind();
}
