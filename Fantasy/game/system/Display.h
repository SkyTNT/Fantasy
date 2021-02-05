#pragma once
#include <glm/glm.hpp>

class Display {
public:
    glm::mat4 projection,view;
public:
    static void init();
    static void free();
    static Display* displays[8];
    static Display* current;
};

