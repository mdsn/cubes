#pragma once
#include <glad/glad.h>

struct CubeTex {
  int t[6];
  CubeTex(int front, int right, int left, int back, int bottom, int top);
};

class Cube {
  float x, y, z;
  CubeTex tex;

public:
  Cube(float x, float y, float z, CubeTex tex);
  void emit_faces(std::vector<GLfloat> &vec) const;
};
