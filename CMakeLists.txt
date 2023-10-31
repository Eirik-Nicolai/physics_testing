cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

set(CMAKE_CXX_FLAGS "-O0")

set(CXX_STANDARD "C++17")

# add_subdirectory(src)
project(physics_practice)

set(SRC_MAIN src/main.cpp src/physics_engine.cpp src/verlet_solver.cpp src/olc_balls.cpp)

# set(SRC_ENGINE
# )

# set(SRC_UTILS
# )

# set(SRC_SYSTEMS
# )

set(SRC_GAME ${SRC_MAIN})

message ("Adding executable...")
add_executable(prog ${SRC_GAME})

message("Linking dirs....")

target_link_libraries(
    prog
    GL
    GLU
    X11
    png
    pthread
    stdc++fs
)

target_include_directories(prog
    PRIVATE
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_SOURCE_DIR}/include"
)
