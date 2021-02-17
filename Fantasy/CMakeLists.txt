include_directories(.)

if (CMAKE_SYSTEM_NAME MATCHES "Android")
    add_library(fantasy SHARED main_android.cpp)
else()
    set(CMAKE_EXE_LINKER_FLAGS -static)
    add_executable(fantasy main.cpp)
endif()

target_link_libraries(fantasy engine)