file(GLOB_RECURSE DIR_SRC *.cpp)
add_library(engine STATIC ${DIR_SRC})

if (CMAKE_SYSTEM_NAME MATCHES "Android")
    target_link_libraries(engine stb glfm GLESv3)
else()
    target_link_libraries(engine stb glad glfw)
endif()
