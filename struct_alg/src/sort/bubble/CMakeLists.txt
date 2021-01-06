cmake_minimum_required(VERSION 3.9)
project(gldemo)

set(CMAKE_CXX_STANDARD 11)

FILE(GLOB_RECURSE COMMON_SRC *.cpp | *.c)
FILE(GLOB_RECURSE COMMON_H *.h)
FILE(GLOB_RECURSE COMMON_LIB_SRC ../../lib/*.cpp | ../../lib/*.c)

add_executable(sort_bubble ${COMMON_SRC} ${COMMON_H} ${COMMON_LIB_SRC} header.h ../../lib/common.h)
