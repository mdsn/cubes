#include <algorithm>
#include <cmath>
#include "world.h"

#include <unordered_set>

constexpr int CHUNK_RADIUS = 1;

int floor_div(const int numerator, const int denominator) {
  const int quotient = numerator / denominator;
  const int remainder = numerator % denominator;
  if (remainder != 0 && numerator < 0)
    return quotient - 1;
  return quotient;
}

glm::ivec2 pos_to_chunk(const glm::vec3 pos) {
  return glm::ivec2{floor_div(static_cast<int>(std::floor(pos.x)), CHUNK_SIZE),
                    floor_div(static_cast<int>(std::floor(pos.z)), CHUNK_SIZE)};
}

// a square disk around a position
std::vector<glm::ivec2> neighbors(const glm::ivec2 position, const int layers) {
  std::vector<glm::ivec2> vec{};
  for (int x = -layers; x <= layers; x++)
    for (int y = -layers; y <= layers; y++)
      vec.emplace_back(position + glm::ivec2{x, y});
  return vec;
}

// abstract this and `neighbors()` from the returned container?
std::unordered_set<glm::ivec2> disk(const glm::ivec2 position,
                                    const int layers) {
  std::unordered_set<glm::ivec2> set{};
  for (int x = -layers; x <= layers; x++)
    for (int y = -layers; y <= layers; y++)
      set.emplace(position + glm::ivec2{x, y});
  return set;
}

// TODO optimization: instead of constantly releasing 2*RADIUS+1 chunks on every
//      change and reallocating the SAME AMOUNT OF SPACE just try and reuse the
//      allocated memory somehow. After all, for a fixed block radius we should
//      be able to allocate all necessary memory at start and never change it
//      again!
//      Chunk Arena, a statically allocated set of pages. The hashmap indexes
//      into it converting from world-coordinates into arena-coordinates.
void update_chunks(std::unordered_map<glm::ivec2, Chunk> &chunks,
                   const std::optional<glm::ivec2> previous_chunk,
                   const glm::ivec2 current_chunk) {
  if (previous_chunk.has_value()) {
    auto direction = current_chunk - previous_chunk.value();
    // moving in x direction
    if (direction.x != 0) {
      const int erase_line = current_chunk.x - direction.x * (CHUNK_RADIUS + 1);
      const int emplace_line = current_chunk.x + direction.x * CHUNK_RADIUS;
      for (int z = -CHUNK_RADIUS; z <= CHUNK_RADIUS; z++) {
        auto pos = glm::ivec2{erase_line, current_chunk.y + z};
        chunks.erase(pos);
        pos.x = emplace_line;
        chunks.emplace(pos, Chunk{chunks, pos.x, pos.y});
      }
    } else { // moving in z direction
      const int erase_line = current_chunk.y - direction.y * (CHUNK_RADIUS + 1);
      const int emplace_line = current_chunk.y + direction.y * CHUNK_RADIUS;
      for (int x = -CHUNK_RADIUS; x <= CHUNK_RADIUS; x++) {
        auto pos = glm::ivec2{current_chunk.x + x, erase_line};
        chunks.erase(pos);
        pos.y = emplace_line;
        chunks.emplace(pos, Chunk{chunks, pos.x, pos.y});
      }
    }
  } else {
    chunks.clear();
    for (const auto &coord : neighbors(current_chunk, CHUNK_RADIUS))
      chunks.emplace(coord, Chunk{chunks, coord.x, coord.y});
  }
}

void emit_vertices(const std::unordered_map<glm::ivec2, Chunk> &chunks,
                   std::vector<GLfloat> &vertices) {
  vertices.clear();
  for (auto &[pos, chunk] : chunks)
    chunk.emit_cubes(vertices);
}

World::World(const glm::vec3 start_position) { set_position(start_position); }

void World::set_position(const glm::vec3 new_pos) {
  player_position = new_pos;
  current_chunk = pos_to_chunk(player_position);
  if (prev_chunk != current_chunk) {
    chunk_changed = true; // signals the renderer to upload the data to the gpu
    update_chunks(chunks, prev_chunk, current_chunk);
    emit_vertices(chunks, chunk_vertices);
    prev_chunk = current_chunk;
  }
}

void World::finished_rendering() { chunk_changed = false; }

const std::vector<GLfloat> &World::vertices() const { return chunk_vertices; }
