#include <glm/gtc/matrix_transform.hpp>
#include "renderer.h"

Renderer::Renderer(World &world)
    : world_shader{"shaders/cubeVertex.glsl", "shaders/cubeFragment.glsl"},
      world_texture{"resources/fogletexture.png"} {
  world_shader.use();
  world_shader.set_int("fogletexture", 0);
  world_shader.set_mat4fv( // XXX 800x600 hardcoded
      "proj",
      glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 100.0f));

  world_vao.bind();
  world_vbo.write(world.vertices().size() * sizeof(GLfloat),
                  world.vertices().data());
  world_shader.attr("position", 3, GL_FLOAT, 5 * sizeof(float), 0);
  world_shader.attr("texcoord", 2, GL_FLOAT, 5 * sizeof(float),
                    (void *)(3 * sizeof(float)));
}

void Renderer::prepare_world(World &world, bool wireframe,
                             const Camera &camera) {
  glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
  world_shader.use();
  world_shader.set_mat4fv("view", camera.view());
  world_texture.bind();
  world_vao.bind();
}
