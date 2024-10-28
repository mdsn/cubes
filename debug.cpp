#include <format>

#include "debug.h"

std::vector<std::string> Debug::lines() const {
  return std::vector{
      std::format("Camera pos: ({:.3f},{:.3f},{:.3f})", camera_pos.x,
                  camera_pos.y, camera_pos.z),
      std::format("Chunk: ({}, {})", chunk.x, chunk.y),
      std::format("Time delta: {}", time_delta),
  };
}
