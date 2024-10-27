#include <glm/glm.hpp>
#include "font.h"

const int tile_width = 8;
const int tile_height = 16;

#define CHAR(C, X, Y)                                                          \
  case C:                                                                      \
    tile.x = X;                                                                \
    tile.y = Y;                                                                \
    break;

void emit_one(char c, int x, int y, std::vector<float> &vec) {
  glm::ivec2 tile;
  switch (c) {
    CHAR(' ', 0, 13)
    CHAR('!', 1, 13)
    CHAR('"', 2, 13)
    CHAR('#', 3, 13)
    CHAR('$', 4, 13)
    CHAR('%', 5, 13)
    CHAR('&', 6, 13)
    CHAR('\'', 7, 13)
    CHAR('(', 8, 13)
    CHAR(')', 9, 13)
    CHAR('*', 10, 13)
    CHAR('+', 11, 13)
    CHAR(',', 12, 13)
    CHAR('-', 13, 13)
    CHAR('.', 14, 13)
    CHAR('/', 15, 13)
    CHAR('0', 0, 12)
    CHAR('1', 1, 12)
    CHAR('2', 2, 12)
    CHAR('3', 3, 12)
    CHAR('4', 4, 12)
    CHAR('5', 5, 12)
    CHAR('6', 6, 12)
    CHAR('7', 7, 12)
    CHAR('8', 8, 12)
    CHAR('9', 9, 12)
    CHAR(':', 10, 12)
    CHAR(';', 11, 12)
    CHAR('<', 12, 12)
    CHAR('=', 13, 12)
    CHAR('>', 14, 12)
    CHAR('?', 15, 12)
    CHAR('@', 0, 11)
    CHAR('A', 1, 11)
    CHAR('B', 2, 11)
    CHAR('C', 3, 11)
    CHAR('D', 4, 11)
    CHAR('E', 5, 11)
    CHAR('F', 6, 11)
    CHAR('G', 7, 11)
    CHAR('H', 8, 11)
    CHAR('I', 9, 11)
    CHAR('J', 10, 11)
    CHAR('K', 11, 11)
    CHAR('L', 12, 11)
    CHAR('M', 13, 11)
    CHAR('N', 14, 11)
    CHAR('O', 15, 11)
    CHAR('P', 0, 10)
    CHAR('Q', 1, 10)
    CHAR('R', 2, 10)
    CHAR('S', 3, 10)
    CHAR('T', 4, 10)
    CHAR('U', 5, 10)
    CHAR('V', 6, 10)
    CHAR('W', 7, 10)
    CHAR('X', 8, 10)
    CHAR('Y', 9, 10)
    CHAR('Z', 10, 10)
    CHAR('[', 11, 10)
    CHAR('\\', 12, 10)
    CHAR(']', 13, 10)
    CHAR('^', 14, 10)
    CHAR('_', 15, 10)
    CHAR('`', 0, 9)
    CHAR('a', 1, 9)
    CHAR('b', 2, 9)
    CHAR('c', 3, 9)
    CHAR('d', 4, 9)
    CHAR('e', 5, 9)
    CHAR('f', 6, 9)
    CHAR('g', 7, 9)
    CHAR('h', 8, 9)
    CHAR('i', 9, 9)
    CHAR('j', 10, 9)
    CHAR('k', 11, 9)
    CHAR('l', 12, 9)
    CHAR('m', 13, 9)
    CHAR('n', 14, 9)
    CHAR('o', 15, 9)
    CHAR('p', 0, 8)
    CHAR('q', 1, 8)
    CHAR('r', 2, 8)
    CHAR('s', 3, 8)
    CHAR('t', 4, 8)
    CHAR('u', 5, 8)
    CHAR('v', 6, 8)
    CHAR('w', 7, 8)
    CHAR('x', 8, 8)
    CHAR('y', 9, 8)
    CHAR('z', 10, 8)
    CHAR('{', 11, 8)
    CHAR('|', 12, 8)
    CHAR('}', 13, 8)
    CHAR('~', 14, 8)
  default:
    break;
  }
  // +----+  Texture coords grow like the usual cartesian axis (axes?)
  // |   /|    ^
  // | /  |    |
  // +----+  (0,0) --->
  float factor{0.0625};
  float tu = tile.x * factor;
  float tv = tile.y * factor;

  // for each vertex, xy are pixel coordinates in screen space because of the
  // orthographic projection, but texture coordinates are in uv--the texture
  // coordinates go from 0 to 1 in both directions and grow to the right and
  // upwards, whereas the xy coordinates grow to the right and downwards
  vec.push_back(x * tile_width);  // top left x
  vec.push_back(y * tile_height); // top left y
  vec.push_back(tu);
  vec.push_back(tv + factor);

  vec.push_back(x * tile_width);        // bottom left x
  vec.push_back((y + 1) * tile_height); // bottom left y
  vec.push_back(tu);
  vec.push_back(tv);

  vec.push_back((x + 1) * tile_width); // top right x
  vec.push_back(y * tile_height);      // top right y
  vec.push_back(tu + factor);
  vec.push_back(tv + factor);

  // second triangle
  vec.push_back((x + 1) * tile_width); // top right x
  vec.push_back(y * tile_height);      // top right y
  vec.push_back(tu + factor);
  vec.push_back(tv + factor);

  vec.push_back(x * tile_width);        // bottom left x
  vec.push_back((y + 1) * tile_height); // bottom left y
  vec.push_back(tu);
  vec.push_back(tv);

  vec.push_back((x + 1) * tile_width);  // bottom right x
  vec.push_back((y + 1) * tile_height); // bottom right y
  vec.push_back(tu + factor);
  vec.push_back(tv);
}

std::vector<float> make_quads(const std::vector<std::string> &lines) {
  std::vector<float> q;
  int x{0}, y{0};
  for (auto str : lines) {
    for (char c : str) {
      emit_one(c, x, y, q);
      x++;
    }
    y++;
    x = 0;
  }
  return q;
}