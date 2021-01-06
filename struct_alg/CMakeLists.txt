cmake_minimum_required(VERSION 3.9)
project(struct_alg)

set(CMAKE_CXX_STANDARD 11)

include_directories(src)
#add_subdirectory(src/sort/insert)
#add_subdirectory(src/sort/select)
#add_subdirectory(src/sort/bubble)
#add_subdirectory(src/sort/shell)
#add_subdirectory(src/sort/merge)
add_subdirectory(src/sort/quick)
