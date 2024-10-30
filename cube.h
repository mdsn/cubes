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

struct Triangle {
  Vertex points[3];
};

enum class FaceDirection { front, right, left, back, bottom, top };

struct Face {
  FaceDirection direction;
  glm::vec3 vertices[4];
  int indices[6];
  glm::ivec2 texture[4]{{0, 0}, {1, 0}, {1, 1}, {0, 1}};
  std::array<Triangle, 2> triangles() const;
};

class Cube {
  int ix, iy, iz;
  float x, y, z;
  CubeTex tex;

public:
  Cube(float x, float y, float z, int ix, int iy, int iz, const CubeTex &tex);
  glm::vec3 position() const;
  glm::ivec3 iposition() const;
  // TODO filter cubes altogether that are entirely surrounded by solid cubes
  void emit_vertices(std::vector<GLfloat> &vec,
                     std::vector<FaceDirection> faces) const;
};
