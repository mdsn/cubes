cmake_minimum_required(VERSION 3.26)
project(brix)

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(soil2 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)

add_executable(brix main.cpp
        cube.h
        cube.cpp
        chunk.cpp
        chunk.h
        chunk_constants.h
        coords.h
        shader.cpp
        shader.h
        camera.cpp
        camera.h
        vbo.cpp
        vbo.h
        vao.cpp
        vao.h
        texture.cpp
        texture.h
        window.cpp
        window.h
        gfx.h
        world.cpp
        world.h
        renderer.cpp
        renderer.h
        font.cpp
        font.h
        debug.cpp
        debug.h
        FastNoiseLite.h
)
target_link_libraries(brix PRIVATE glfw)
target_link_libraries(brix PRIVATE glad::glad)
target_link_libraries(brix PRIVATE soil2)
target_link_libraries(brix PRIVATE glm::glm)

target_compile_features(brix PRIVATE cxx_std_23)
target_compile_options(brix PRIVATE -Wall -Wextra)

include(CTest)
include(Catch)

if (BUILD_TESTING)
  add_executable(brix_tests tests/coords_tests.cpp)
  target_include_directories(brix_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
  target_link_libraries(brix_tests PRIVATE Catch2::Catch2WithMain glm::glm)
  target_compile_features(brix_tests PRIVATE cxx_std_23)
  target_compile_options(brix_tests PRIVATE -Wall -Wextra)
  catch_discover_tests(brix_tests)
endif()
