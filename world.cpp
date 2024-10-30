#include <ranges>
#include "world.h"

constexpr int CHUNK_RADIUS = 4;

int map_interval(const double x) {
  const float abs = std::abs(x);
  if (abs < 8.0)
    return 0;
  const int res = 1 + static_cast<int>(abs - 8) / 16;
  return x >= 0 ? res : -res;
}

glm::ivec2 pos_to_chunk(const glm::vec3 pos) {
  return glm::ivec2{map_interval(pos.x), map_interval(pos.z)};
}

std::vector<glm::ivec2> neighbors(const glm::ivec2 position, const int layers) {
  std::vector<glm::ivec2> vec{};
  for (int x = -layers; x < layers; x++)
    for (int y = -layers; y < layers; y++)
      vec.emplace_back(position + glm::ivec2{x, y});
  return vec;
}

void update_chunks(std::vector<Chunk> &chunks, const glm::ivec2 current_chunk) {
  // TODO only remove chunks behind us and create the new ones!!!
  // current_chunk - prev_chunk gives a vector in the direction of the chunk
  // update with a better data structure this replacement can be made cheaper
  chunks.clear();
  for (const auto coord : neighbors(current_chunk, CHUNK_RADIUS))
    chunks.emplace_back(coord.x, coord.y);
}

void emit_vertices(const std::vector<Chunk> &chunks,
                   std::vector<GLfloat> &vertices) {
  vertices.clear();
  for (auto &chunk : chunks)
    chunk.emit_cubes(vertices);
}

World::World(const glm::vec3 start_position) { set_position(start_position); }

void World::set_position(const glm::vec3 new_pos) {
  player_position = new_pos;
  current_chunk = pos_to_chunk(player_position);
  if (prev_chunk != current_chunk) {
    chunk_changed = true; // signals the renderer to upload the data to the gpu
    update_chunks(chunks, current_chunk);
    emit_vertices(chunks, chunk_vertices);
    prev_chunk = current_chunk;
  }
}

void World::finished_rendering() { chunk_changed = false; }

const std::vector<GLfloat> &World::vertices() const { return chunk_vertices; }
