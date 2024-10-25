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

const float width = 800.0f;
const float height = 600.0f;

GLuint gen_buffer(GLsizei size, GLfloat *data);
GLuint load_texture(const GLchar *path);
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

  //   --------------- Cube -----------------
  // Create a vertex array object
  GLuint vaoCube;
  glGenVertexArrays(1, &vaoCube);
  glBindVertexArray(vaoCube);

  // Create a vertex buffer object and copy the vertex data to it
  std::vector<GLfloat> vec;
  Chunk chunk{0, 0};
  chunk.emit_cubes(vec);

  GLuint vboCube = gen_buffer(vec.size() * sizeof(GLfloat), vec.data());
  Shader cube_shader{"shaders/cubeVertex.glsl", "shaders/cubeFragment.glsl"};

  cube_shader.use();
  glBindBuffer(GL_ARRAY_BUFFER, vboCube);
  specify_cube_vertex_attributes(cube_shader.id);

  // Load textures
  glActiveTexture(GL_TEXTURE0);
  GLuint textures = load_texture("resources/fogletexture.png");
  cube_shader.set_int("fogletexture", 0); // GL_TEXTURE0

  // glm::perspective : The first parameter is the vertical field-of-view,
  //    the second parameter the aspect ratio of the screen and the last two
  //    parameters are the near and far planes.
  cube_shader.set_mat4fv(
      "proj",
      glm::perspective(glm::radians(45.0f), width / height, 1.0f, 100.0f));

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

    glPolygonMode(GL_FRONT_AND_BACK, g.render_wireframe ? GL_LINE : GL_FILL);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw the cube
    cube_shader.use();
    cube_shader.set_mat4fv("view", g.camera.view());
    cube_shader.set_float("time", (sin(elapsedTime * 4.0f) + 1.0f) / 2.0f);

    glBindVertexArray(vaoCube);
    glDrawArrays(GL_TRIANGLES, 0, vec.size());

    glfwSwapBuffers(g.window);
    glfwPollEvents();
    if (glfwWindowShouldClose(g.window)) {
      break;
    }
  }

  glDeleteTextures(1, &textures);
  glDeleteBuffers(1, &vboCube);
  glDeleteVertexArrays(1, &vaoCube);

  glfwTerminate();
  return 0;
}

// ------------------ gl stuff -------------------
GLuint gen_buffer(GLsizei size, GLfloat *data) {
  GLuint name;
  glGenBuffers(1, &name);
  glBindBuffer(GL_ARRAY_BUFFER, name);
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  return name;
}

GLuint load_texture(const GLchar *path) {
  GLuint texture;
  glGenTextures(1, &texture);

  glBindTexture(GL_TEXTURE_2D, texture);
  SOIL_load_OGL_texture(path, SOIL_LOAD_AUTO, texture,
                        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y |
                            SOIL_FLAG_NTSC_SAFE_RGB |
                            SOIL_FLAG_COMPRESS_TO_DXT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  return texture;
}

void specify_cube_vertex_attributes(GLuint shader_program) {
  GLint posAttrib = glGetAttribLocation(shader_program, "position");
  glEnableVertexAttribArray(posAttrib);
  glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);

  GLint texAttrib = glGetAttribLocation(shader_program, "texcoord");
  glEnableVertexAttribArray(texAttrib);
  glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void *)(3 * sizeof(float)));
}
