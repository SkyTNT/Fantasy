file(GLOB_RECURSE DIR_SRC *.cpp)
add_library(game ${DIR_SRC})
target_link_libraries(game)
