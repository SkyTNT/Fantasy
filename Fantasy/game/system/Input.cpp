#include "Input.h"
#include <cstring>
#include <utils/Utils.h>

bool Input::keyState[1000];
bool Input::cursorLocked;
glm::vec2 Input::axis;
Input::Cursor* Input::cursor;
glm::vec2 Input::cursorLockPos;
glm::vec2 Input::cursorVelocity;
static glm::vec2 lastCursor;

void Input::init() {
    memset(keyState,0,sizeof keyState);
    axis  = cursorVelocity = lastCursor  = cursorLockPos = glm::vec2(0);
    cursorLocked = false;
}

void Input::tick() {

    if (cursorLocked)
    {
        cursorVelocity=cursor->getPos()-cursorLockPos;
        cursor->setPos(cursorLockPos.x,cursorLockPos.y);
    } else
    {
        cursorVelocity=cursor->getPos()-lastCursor;
    }

    lastCursor=cursor->getPos();
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

void Input::setCursor(Input::Cursor *cursor_) {
    cursor=cursor_;
}

void Input::setCursorPos(float x, float y) {
    if (!cursor)
        return;
    cursor->setPos(x,y);

    //清除副作用
    lastCursor.x=x;
    lastCursor.y=y;
    cursorVelocity={0,0};
}

const glm::vec2 &Input::getCursorPos() {
    return cursor->getPos();
}

const glm::vec2 &Input::getCursorVelocity() {
    return cursorVelocity;
}


void Input::lockCursor() {
    cursorLockPos = cursor->getPos();
    cursorLocked = true;
}

void Input::unlockCursor() {
    cursorLocked = false;
}

glm::vec2 Input::getAxis() {
    return axis;
}


Input::Cursor::Cursor() = default;

Input::Cursor::~Cursor() = default;
