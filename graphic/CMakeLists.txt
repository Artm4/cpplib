cmake_minimum_required(VERSION 3.9)
set(projectName graphic)
project(${projectName})

set(CMAKE_CXX_STANDARD 11)

find_package(SDL2 REQUIRED)
# Add SDL2 into include directories
include_directories(/usr/include/SDL2)

message("top: CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR}")
message("top: CMAKE_BINARY_DIR=${CMAKE_BINARY_DIR}")
message("top: CMAKE_CURRENT_SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}")
message("top: CMAKE_CURRENT_BINARY_DIR=${CMAKE_CURRENT_BINARY_DIR}")

include_directories(src)

add_executable(${projectName} src/main.cpp src/util/memory.hpp src/type/traits.hpp src/renderA/render-test01.cpp src/type/constant_eval.cpp src/type/constant.h)

link_libraries(SDL2-2.0 SDL2_image SDL2_ttf SDL2_mixer)

#target_include_directories(${projectName} PUBLIC src)

add_subdirectory(src/renderA)
