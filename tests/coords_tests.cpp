#define GLM_ENABLE_EXPERIMENTAL
#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <array>
#include <unordered_set>

#include <glm/gtx/hash.hpp>

#include "chunk_constants.h"
#include "coords.h"
#include "mesher.h"

struct FakeWorldQuery {
  std::unordered_set<glm::ivec3> solid;

  void add(const glm::ivec3 pos) { solid.insert(pos); }

  bool is_solid_at_world(const glm::ivec3 pos) const {
    return solid.contains(pos);
  }
};

constexpr std::array<glm::ivec3, 6> kNeighborDirs{
    glm::ivec3{0, 0, 1},  glm::ivec3{1, 0, 0},  glm::ivec3{-1, 0, 0},
    glm::ivec3{0, 0, -1}, glm::ivec3{0, -1, 0}, glm::ivec3{0, 1, 0}};

int count_visible_faces(const FakeWorldQuery &query) {
  int count = 0;
  for (const auto &pos : query.solid) {
    for (const auto &dir : kNeighborDirs) {
      if (!query.is_solid_at_world(pos + dir))
        count++;
    }
  }
  return count;
}

TEST_CASE("floor_div handles boundaries with negatives") {
  using coords::floor_div;
  REQUIRE(floor_div(0, 16) == 0);
  REQUIRE(floor_div(15, 16) == 0);
  REQUIRE(floor_div(16, 16) == 1);
  REQUIRE(floor_div(31, 16) == 1);
  REQUIRE(floor_div(32, 16) == 2);
  REQUIRE(floor_div(-1, 16) == -1);
  REQUIRE(floor_div(-16, 16) == -1);
  REQUIRE(floor_div(-17, 16) == -2);
  REQUIRE(floor_div(-32, 16) == -2);
  REQUIRE(floor_div(-33, 16) == -3);
}

TEST_CASE("world->chunk/local roundtrip") {
  const std::array<glm::ivec3, 8> positions{
      glm::ivec3{0, 0, 0},       glm::ivec3{15, 3, 15},
      glm::ivec3{16, 4, 0},      glm::ivec3{-1, 5, -1},
      glm::ivec3{-16, 6, -16},  glm::ivec3{-17, 7, 17},
      glm::ivec3{31, 8, -33},   glm::ivec3{-48, 9, 48},
  };

  for (const auto &world_pos : positions) {
    const glm::ivec2 chunk = coords::world_to_chunk_pos(world_pos);
    const glm::ivec3 local = coords::world_to_local_pos(world_pos);
    REQUIRE(local.x >= 0);
    REQUIRE(local.x < CHUNK_SIZE);
    REQUIRE(local.z >= 0);
    REQUIRE(local.z < CHUNK_SIZE);

    const glm::ivec3 roundtrip{chunk.x * CHUNK_SIZE + local.x, world_pos.y,
                               chunk.y * CHUNK_SIZE + local.z};
    REQUIRE(roundtrip == world_pos);
  }
}

TEST_CASE("meshing face counts for simple layouts") {
  FakeWorldQuery query;

  query.add({0, 0, 0});
  REQUIRE(count_visible_faces(query) == 6);

  query = FakeWorldQuery{};
  query.add({0, 0, 0});
  query.add({1, 0, 0});
  REQUIRE(count_visible_faces(query) == 10);

  query = FakeWorldQuery{};
  query.add({0, 0, 0});
  query.add({2, 0, 0});
  REQUIRE(count_visible_faces(query) == 12);

  query = FakeWorldQuery{};
  for (int x = 0; x < 2; x++)
    for (int z = 0; z < 2; z++)
      query.add({x, 0, z});
  REQUIRE(count_visible_faces(query) == 16);

  query = FakeWorldQuery{};
  query.add({0, 0, 0});
  query.add({0, 1, 0});
  REQUIRE(count_visible_faces(query) == 10);
}

TEST_CASE("indexed mesh output for a single cube") {
  CubeTex tex{0, 0, 0, 0, 0, 0};
  std::vector<Cube> cubes{
      Cube{glm::ivec3{0, 0, 0}, glm::ivec3{0, 0, 0}, tex}};
  auto is_solid = [&](const glm::ivec3 pos) {
    return pos == glm::ivec3{0, 0, 0};
  };
  Mesh mesh = build_mesh_from_cubes(cubes, is_solid);
  REQUIRE(mesh.vertices.size() == 24);
  REQUIRE(mesh.indices.size() == 36);
  const auto max_it = std::max_element(mesh.indices.begin(),
                                       mesh.indices.end());
  REQUIRE(max_it != mesh.indices.end());
  REQUIRE(*max_it < mesh.vertices.size());
}
