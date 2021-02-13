file(GLOB_RECURSE DIR_SRC *.cpp)
include_directories(.)
add_library(engine ${DIR_SRC})
