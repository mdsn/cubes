#include <glm/glm.hpp>
#include "font.h"

const int tile_width = 8;
const int tile_height = 16;

// XXX assumes y = 0
std::vector<float> make_quads(const std::string &str) {
  std::vector<float> q;
  glm::ivec2 tile;
  int i{0};
  for (char c : str) {
    //
    switch (c) {
    case ' ': tile.x = 0; tile.y = 13; break;
    case '!': tile.x = 1; tile.y = 13; break;
    case '"': tile.x = 2; tile.y = 13; break;
    case '#': tile.x = 3; tile.y = 13; break;
    case '$': tile.x = 4; tile.y = 13; break;
    case '%': tile.x = 5; tile.y = 13; break;
    case '&': tile.x = 6; tile.y = 13; break;
    case '\'': tile.x = 7; tile.y = 13; break;
    case '(': tile.x = 8; tile.y = 13; break;
    case ')': tile.x = 9; tile.y = 13; break;
    case '*': tile.x = 10; tile.y = 13; break;
    case '+': tile.x = 11; tile.y = 13; break;
    case ',': tile.x = 12; tile.y = 13; break;
    case '-': tile.x = 13; tile.y = 13; break;
    case '.': tile.x = 14; tile.y = 13; break;
    case '/': tile.x = 15; tile.y = 13; break;
    case '0': tile.x = 0; tile.y = 12; break;
    case '1': tile.x = 1; tile.y = 12; break;
    case '2': tile.x = 2; tile.y = 12; break;
    case '3': tile.x = 3; tile.y = 12; break;
    case '4': tile.x = 4; tile.y = 12; break;
    case '5': tile.x = 5; tile.y = 12; break;
    case '6': tile.x = 6; tile.y = 12; break;
    case '7': tile.x = 7; tile.y = 12; break;
    case '8': tile.x = 8; tile.y = 12; break;
    case '9': tile.x = 9; tile.y = 12; break;
    case ':': tile.x = 10; tile.y = 12; break;
    case ';': tile.x = 11; tile.y = 12; break;
    case '<': tile.x = 12; tile.y = 12; break;
    case '=': tile.x = 13; tile.y = 12; break;
    case '>': tile.x = 14; tile.y = 12; break;
    case '?': tile.x = 15; tile.y = 12; break;
    case '@': tile.x = 0; tile.y = 11; break;
    case 'A': tile.x = 1; tile.y = 11; break;
    case 'B': tile.x = 2; tile.y = 11; break;
    case 'C': tile.x = 3; tile.y = 11; break;
    case 'D': tile.x = 4; tile.y = 11; break;
    case 'E': tile.x = 5; tile.y = 11; break;
    case 'F': tile.x = 6; tile.y = 11; break;
    case 'G': tile.x = 7; tile.y = 11; break;
    case 'H': tile.x = 8; tile.y = 11; break;
    case 'I': tile.x = 9; tile.y = 11; break;
    case 'J': tile.x = 10; tile.y = 11; break;
    case 'K': tile.x = 11; tile.y = 11; break;
    case 'L': tile.x = 12; tile.y = 11; break;
    case 'M': tile.x = 13; tile.y = 11; break;
    case 'N': tile.x = 14; tile.y = 11; break;
    case 'O': tile.x = 15; tile.y = 11; break;
    case 'P': tile.x = 0; tile.y = 10; break;
    case 'Q': tile.x = 1; tile.y = 10; break;
    case 'R': tile.x = 2; tile.y = 10; break;
    case 'S': tile.x = 3; tile.y = 10; break;
    case 'T': tile.x = 4; tile.y = 10; break;
    case 'U': tile.x = 5; tile.y = 10; break;
    case 'V': tile.x = 6; tile.y = 10; break;
    case 'W': tile.x = 7; tile.y = 10; break;
    case 'X': tile.x = 8; tile.y = 10; break;
    case 'Y': tile.x = 9; tile.y = 10; break;
    case 'Z': tile.x = 10; tile.y = 10; break;
    case '[': tile.x = 11; tile.y = 10; break;
    case '\\': tile.x = 12; tile.y = 10; break;
    case ']': tile.x = 13; tile.y = 10; break;
    case '^': tile.x = 14; tile.y = 10; break;
    case '_': tile.x = 15; tile.y = 10; break;
    case '`': tile.x = 0; tile.y = 9; break;
    case 'a': tile.x = 1; tile.y = 9; break;
    case 'b': tile.x = 2; tile.y = 9; break;
    case 'c': tile.x = 3; tile.y = 9; break;
    case 'd': tile.x = 4; tile.y = 9; break;
    case 'e': tile.x = 5; tile.y = 9; break;
    case 'f': tile.x = 6; tile.y = 9; break;
    case 'g': tile.x = 7; tile.y = 9; break;
    case 'h': tile.x = 8; tile.y = 9; break;
    case 'i': tile.x = 9; tile.y = 9; break;
    case 'j': tile.x = 10; tile.y = 9; break;
    case 'k': tile.x = 11; tile.y = 9; break;
    case 'l': tile.x = 12; tile.y = 9; break;
    case 'm': tile.x = 13; tile.y = 9; break;
    case 'n': tile.x = 14; tile.y = 9; break;
    case 'o': tile.x = 15; tile.y = 9; break;
    case 'p': tile.x = 0; tile.y = 8; break;
    case 'q': tile.x = 1; tile.y = 8; break;
    case 'r': tile.x = 2; tile.y = 8; break;
    case 's': tile.x = 3; tile.y = 8; break;
    case 't': tile.x = 4; tile.y = 8; break;
    case 'u': tile.x = 5; tile.y = 8; break;
    case 'v': tile.x = 6; tile.y = 8; break;
    case 'w': tile.x = 7; tile.y = 8; break;
    case 'x': tile.x = 8; tile.y = 8; break;
    case 'y': tile.x = 9; tile.y = 8; break;
    case 'z': tile.x = 10; tile.y = 8; break;
    case '{': tile.x = 11; tile.y = 8; break;
    case '|': tile.x = 12; tile.y = 8; break;
    case '}': tile.x = 13; tile.y = 8; break;
    case '~': tile.x = 14; tile.y = 8; break;
    default: break;
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
    q.push_back(i * tile_width);  // top left x
    q.push_back(0);               // top left y
    q.push_back(tu);
    q.push_back(tv + factor);

    q.push_back(i * tile_width);  // bottom left x
    q.push_back(tile_height); // bottom left y
    q.push_back(tu);
    q.push_back(tv);

    q.push_back((i+1)*tile_width);  // top right x
    q.push_back(0); // top right y
    q.push_back(tu + factor);
    q.push_back(tv + factor);

    // second triangle
    q.push_back((i+1)*tile_width);  // top right x
    q.push_back(0); // top right y
    q.push_back(tu + factor);
    q.push_back(tv + factor);

    q.push_back(i * tile_width);  // bottom left x
    q.push_back(tile_height); // bottom left y
    q.push_back(tu);
    q.push_back(tv);

    q.push_back((i+1)*tile_width);  // bottom right x
    q.push_back(tile_height); // bottom right y
    q.push_back(tu + factor);
    q.push_back(tv);

    i++;
  }
  return q;
}