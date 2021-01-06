cmake_minimum_required(VERSION 3.9)
project(graphic)

set(CMAKE_CXX_STANDARD 11)

find_package(SDL2 REQUIRED)
# Add SDL2 into include directories
include_directories(/usr/include/SDL2)

message("top: CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR}")
message("top: CMAKE_BINARY_DIR=${CMAKE_BINARY_DIR}")
message("top: CMAKE_CURRENT_SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}")
message("top: CMAKE_CURRENT_BINARY_DIR=${CMAKE_CURRENT_BINARY_DIR}")


