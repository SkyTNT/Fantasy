include_directories(.)

file(GLOB_RECURSE DIR_SRC *.cpp)

if (CMAKE_SYSTEM_NAME MATCHES "Android")
    add_library(fantasy SHARED ${DIR_SRC})
else()
    set(CMAKE_EXE_LINKER_FLAGS -static)
    add_executable(fantasy ${DIR_SRC})
endif()

target_link_libraries(fantasy engine)