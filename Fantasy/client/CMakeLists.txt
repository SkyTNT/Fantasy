file(GLOB_RECURSE DIR_SRC *.cpp)
add_library(client ${DIR_SRC})
if (CMAKE_SYSTEM_NAME MATCHES "Android")
    target_link_libraries(client GLESv3)
else()
    target_link_libraries(client glfw3)
endif()


