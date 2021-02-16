file(GLOB_RECURSE DIR_SRC asset/*.cpp component/*.cpp env/*.cpp object/*.cpp scene/*.cpp system/*.cpp thread/*.cpp utils/*.cpp)
add_library(engine STATIC ${DIR_SRC} GameClient.cpp Application.cpp)

if (CMAKE_SYSTEM_NAME MATCHES "Android")
    target_link_libraries(engine stb glfm GLESv3)
else()
    target_link_libraries(engine stb glad glfw)
endif()

