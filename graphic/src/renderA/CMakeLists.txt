message("top: CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR}")
message("top: CMAKE_BINARY_DIR=${CMAKE_BINARY_DIR}")
message("top: CMAKE_CURRENT_SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}")
message("top: CMAKE_CURRENT_BINARY_DIR=${CMAKE_CURRENT_BINARY_DIR}")


include_directories(.)
include_directories(/usr/include/SDL2)


add_executable(rendera01 render-test01.cpp render/gi.cpp render/gi.h render/impl/SDL/sdl_imp.cpp render/impl/SDL/sdl_imp.h render/impl/giimp.h render/impl/SDL/sdl_init.h render/render_include.h render/render_matrix.hpp render/transform.cpp render/transform.h render/transform_key.h)
add_executable(rendera02 render-test02.cpp render/gi.cpp render/gi.h render/impl/SDL/sdl_imp.cpp render/impl/SDL/sdl_imp.h render/impl/giimp.h render/impl/SDL/sdl_init.h render/render_include.h render/render_matrix.hpp)
add_executable(rendera03 render-test03.cpp render/gi.cpp render/impl/SDL/sdl_imp.cpp)
add_executable(rendera04 render-test04.cpp render/gi.cpp render/impl/SDL/sdl_imp.cpp render/transform.cpp)
add_executable(rendera05 render-test05.cpp render/gi.cpp render/impl/SDL/sdl_imp.cpp render/transform.cpp)
add_executable(rendera06 render-test06.cpp render/gi.cpp render/impl/SDL/sdl_imp.cpp render/transform.cpp)

