cmake_minimum_required(VERSION 3.26)
project(brix)

set(CMAKE_CXX_STANDARD 17)

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
        vao.h)
target_link_libraries(brix PRIVATE glfw)
target_link_libraries(brix PRIVATE glad::glad)
target_link_libraries(brix PRIVATE soil2)
target_link_libraries(brix PRIVATE glm::glm)