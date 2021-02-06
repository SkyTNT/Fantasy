#include "Input.h"
#include <cstring>
#include <utils/Utils.h>

bool Input::keyState[1000];
bool Input::cursorLocked;
std::function<void(float,float)> Input::setCursorReal;
glm::vec2 Input::axis;
glm::vec2 Input::cursor;
glm::vec2 Input::cursorVelocity;
glm::vec2 Input::cursorLockPos;

static glm::vec2 lastCursor;

void Input::init() {
    memset(keyState,0,sizeof keyState);
    axis = cursor = lastCursor = cursorVelocity = cursorLockPos = glm::vec2(0);
    cursorLocked = false;
}

void Input::tick() {
    cursorVelocity=cursor-lastCursor;
    lastCursor=cursor;

    if (cursorLocked)
        setCursor(cursorLockPos.x,cursorLockPos.y);
}

bool Input::getKey(int code) {

    return keyState[code];
}

void Input::pressKey(int code) {
    keyState[code] = true;
    switch (code) {
        case INPUT_KEY_W:
            axis.y = 1;
            break;
        case INPUT_KEY_S:
            axis.y = -1;
            break;
        case INPUT_KEY_D:
            axis.x = 1;
            break;
        case INPUT_KEY_A:
            axis.x = -1;
            break;
        default:
            break;
    }
}

void Input::releaseKey(int code) {
    keyState[code] = false;
    switch (code) {
        case INPUT_KEY_W:
            axis.y = 0;
            break;
        case INPUT_KEY_S:
            axis.y = 0;
            break;
        case INPUT_KEY_D:
            axis.x = 0;
            break;
        case INPUT_KEY_A:
            axis.x = 0;
            break;
        default:
            break;
    }
}

glm::vec2 Input::getCursor() {
    return cursor;
}

void Input::setCursor(float x, float  y) {
    cursor.x=x;
    cursor.y=y;
    setCursorReal(x,y);
}

void Input::lockCursor() {
    cursorLockPos=cursor;
    cursorLocked = true;
}

void Input::unlockCursor() {
    cursorLocked = false;
}

glm::vec2 Input::getAxis() {
    return axis;
}



