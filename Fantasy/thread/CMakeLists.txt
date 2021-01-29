file(GLOB_RECURSE DIR_SRC *.cpp)
add_library(thread ${DIR_SRC})
target_link_libraries(thread)