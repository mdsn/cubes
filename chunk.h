#ifndef CHUNK_H
#define CHUNK_H
#include <vector>
#include <glad/glad.h>

#include "cube.h"

#define CHUNK_SIZE 16

void make_chunk(std::vector<GLfloat> &vec, int x, int z);

#endif // CHUNK_H
