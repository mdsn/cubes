#pragma once
#include <functional>
#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

struct CubeTex {
  int t[6];
  CubeTex(int front, int right, int left, int back, int bottom, int top);
};

struct Vertex {
  glm::vec3 xyz;
  glm::ivec2 uv;
};

enum class FaceDirection { front, right, left, back, bottom, top };

struct Face {
  FaceDirection direction;
  glm::vec3 vertices[4];
  int indices[6];
  glm::ivec2 texture[4]{{0, 0}, {1, 0}, {1, 1}, {0, 1}};
  std::array<Vertex, 6> points() const;
};

class Cube {
  CubeTex tex;

public:
  const glm::vec3 world_pos;
  const glm::ivec3 chunk_pos;
  Cube(glm::vec3 world_pos, glm::ivec3 chunk_pos, const CubeTex &tex);
  void emit_vertices(std::vector<GLfloat> &vec,
                     const std::vector<FaceDirection> &faces) const;
};
