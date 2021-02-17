#pragma once

#include <glm/glm.hpp>
//显示
class Display {
public:
    //投影矩阵,观察矩阵
    glm::mat4 projection, view;
    //清屏色
    glm::vec4 clearColor;
public:
    static void init();

    static void tick();

    static void free();

    //8个显示
    static Display *displays[8];
    static Display *current;
};
