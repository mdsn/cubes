cmake_minimum_required(VERSION 3.26)
project(brix)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(soil2 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

add_executable(brix main.cpp
        cube.h
        cube.cpp
        chunk.cpp
        chunk.h
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
