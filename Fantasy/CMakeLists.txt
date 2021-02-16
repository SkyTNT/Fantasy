cmake_minimum_required(VERSION 3.10)
project(Fantasy)

set(CMAKE_CXX_STANDARD 14)

#添加include目录
if (CMAKE_SYSTEM_NAME MATCHES "Android")
    include_directories(3rd/glfm/include)
else()
    include_directories(3rd/glad/include 3rd/glfw/include)
endif()
include_directories(3rd/glm/include 3rd/stb engine)

#添加子目录
if (CMAKE_SYSTEM_NAME MATCHES "Android")
    add_subdirectory(3rd/glfm)
else()
    add_subdirectory(3rd/glfw)
    add_subdirectory(3rd/glad)
endif()
add_subdirectory(3rd/stb)
add_subdirectory(engine)
add_subdirectory(fantasy)