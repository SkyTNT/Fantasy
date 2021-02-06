#pragma once

#include <glm/glm.hpp>
//��ʾ
class Display {
public:
    //ͶӰ����,�۲����
    glm::mat4 projection, view;
    //����ɫ
    glm::vec4 clearColor;
public:
    static void init();

    static void tick();

    static void free();

    //8����ʾ
    static Display *displays[8];
    static Display *current;
};
