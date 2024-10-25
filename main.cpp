#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <SOIL2/SOIL2.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "camera.h"
#include "chunk.h"
#include "shader.h"
#include "vao.h"
#include "vbo.h"
#include "texture.h"

const float width = 800.0f;
const float height = 600.0f;

void specify_cube_vertex_attributes(GLuint shader_program);

struct State {
  bool render_wireframe = false;
  GLFWwindow *window;
  Camera camera{glm::vec3{0, 0, 5.0}};
};

// All global state
State g;

void handle_mouse_input() {
  const float sensitivity = 0.1;
  static double px{0};
  static double py{0};
  double cx, cy;
  if (px || py) {
    glfwGetCursorPos(g.window, &cx, &cy);
    // std::cout << "cursor pos x " << cx << " y " << cy << std::endl;
    // x grows positively towards the right of the screen
    // y grows positively towards the bottom of the screen
    float dx = (cx - px) * sensitivity;
    float dy = (cy - py) * sensitivity;
    px = cx;
    py = cy;
    g.camera.update(dx, dy);
  } else {
    glfwGetCursorPos(g.window, &px, &py);
  }
}

void handle_motion_input(double dt) {
  float speed = 5.0 * dt;
  if (glfwGetKey(g.window, GLFW_KEY_W)) {
    g.camera.pos -= g.camera.front() * speed;
  }
  if (glfwGetKey(g.window, GLFW_KEY_S)) {
    g.camera.pos += g.camera.front() * speed;
  }
  if (glfwGetKey(g.window, GLFW_KEY_A)) {
    g.camera.pos +=
        glm::normalize(glm::cross(g.camera.front(), g.camera.up)) * speed;
  }
  if (glfwGetKey(g.window, GLFW_KEY_D)) {
    g.camera.pos -=
        glm::normalize(glm::cross(g.camera.front(), g.camera.up)) * speed;
  }
  if (glfwGetKey(g.window, GLFW_KEY_SPACE)) {
    g.camera.pos += glm::normalize(g.camera.up) * speed;
  }
  if (glfwGetKey(g.window, GLFW_KEY_LEFT_CONTROL)) {
    g.camera.pos -= glm::normalize(g.camera.up) * speed;
  }
}

void on_key(GLFWwindow *window, int key, int scancode, int action, int mods) {
  if (action != GLFW_PRESS)
    return;
  if (key == GLFW_KEY_R) {
    g.render_wireframe = !g.render_wireframe;
  }
}

int main() {
  if (!glfwInit())
    return -1;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  g.window = glfwCreateWindow(width, height, "brix", NULL, NULL);
  if (!g.window) {
    glfwTerminate();
    return -2;
  }

  glfwSetInputMode(g.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetInputMode(g.window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
  glfwSetKeyCallback(g.window, on_key);

  glfwMakeContextCurrent(g.window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    glfwTerminate();
    return -3;
  }

  glActiveTexture(GL_TEXTURE0);
  // --------------- Text -----------------
  // Load font shaders
  Shader font_shader{"shaders/textVertex.glsl", "shaders/textFragment.glsl"};
  font_shader.use();
  font_shader.set_int("foglefont", 0); // GL_TEXTURE0?
  font_shader.set_mat4fv("proj",
                         glm::ortho(0.0f, width, height, 0.0f, -1.0f, 1.0f));
  // Load font texture
  Texture font_texture{"resources/foglefont.png"};
  // Create a vao for the text
  VAO vaoText;
  vaoText.bind();
  std::vector<GLfloat> quad{0.0f, 20.0f, 0.0f,  1.0f, 20.0f, 0.0f, // x y u v
                            1.0f, 0.0f,  0.0f,  0.0f, 0.0f,  0.0f,
                            0.0f, 20.0f, 0.0f,  1.0f, 20.0f, 20.0f,
                            1.0f, 1.0f,  20.0f, 0.0f, 1.0f,  0.0f};
  VBO vboText{quad.size() * sizeof(GLfloat), quad.data()};
  vboText.bind();
  GLint vertexAttr = glGetAttribLocation(font_shader.id, "vertex");
  glEnableVertexAttribArray(vertexAttr);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

  //   --------------- Cube -----------------
  Shader cube_shader{"shaders/cubeVertex.glsl", "shaders/cubeFragment.glsl"};
  cube_shader.use();
  cube_shader.set_int("fogletexture", 0); // GL_TEXTURE0
  cube_shader.set_mat4fv(
      "proj",
      glm::perspective(glm::radians(45.0f), width / height, 1.0f, 100.0f));
  // Load textures
  Texture cube_texture{"resources/fogletexture.png"};
  // Create a vertex array object
  VAO vaoCube;
  vaoCube.bind();
  // Create a vertex buffer object and copy the vertex data to it
  std::vector<GLfloat> vec;
  Chunk chunk{0, 0};
  chunk.emit_cubes(vec);
  VBO vboCube{vec.size() * sizeof(GLfloat), vec.data()};
  vboCube.bind();
  specify_cube_vertex_attributes(cube_shader.id);
  // ---------------- Loop ------------------
  auto t_start = std::chrono::high_resolution_clock::now();
  auto t_now = t_start;
  auto t_prev = t_start;

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  while (!glfwWindowShouldClose(g.window)) {
    // Update elapsed time
    float t_delta =
        std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_prev)
            .count();
    t_prev = t_now;
    t_now = std::chrono::high_resolution_clock::now();
    float elapsedTime =
        std::chrono::duration_cast<std::chrono::duration<float>>(t_now -
                                                                 t_start)
            .count();

    if (glfwGetKey(g.window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(g.window, GL_TRUE);
    }

    handle_mouse_input();
    handle_motion_input(t_delta);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw the cube
    glPolygonMode(GL_FRONT_AND_BACK, g.render_wireframe ? GL_LINE : GL_FILL);
    cube_shader.use();
    cube_shader.set_mat4fv("view", g.camera.view());
    cube_shader.set_float("time", (sin(elapsedTime * 4.0f) + 1.0f) / 2.0f);
    cube_texture.bind();
    vaoCube.bind();
    // this should be count of vertices, not count of elements in vec
    // also why are there 46080 elements here -> 256 cubes, 36 vertices output
    // per cube, 5 elems per vertex
    glDrawArrays(GL_TRIANGLES, 0, vec.size() / 5);
    VAO::unbind();

    // Draw the text?
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Force GL_FILL for text
    font_shader.use();
    font_texture.bind();
    vaoText.bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    VAO::unbind();

    glfwSwapBuffers(g.window);
    glfwPollEvents();
    if (glfwWindowShouldClose(g.window)) {
      break;
    }
  }

  glfwTerminate();
  return 0;
}

// ------------------ gl stuff -------------------
void specify_cube_vertex_attributes(GLuint shader_program) {
  GLint posAttrib = glGetAttribLocation(shader_program, "position");
  glEnableVertexAttribArray(posAttrib);
  glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);

  GLint texAttrib = glGetAttribLocation(shader_program, "texcoord");
  glEnableVertexAttribArray(texAttrib);
  glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void *)(3 * sizeof(float)));
}
