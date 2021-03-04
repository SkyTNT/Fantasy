#include "MoveController.h"
#include <component/Transform.h>
#include <object/GameObject.h>
#include <system/System.h>

MoveController::MoveController() : Component() {
}


void MoveController::init() {
    Input::setCursorPos(Window::width/2,Window::height/2);
    Input::lockCursor();
    transform= gameObject->transform;
}

void MoveController::tick() {
    pitch += Input::getCursorVelocity().y*5.0f*Time::deltaTime;
    yaw += -Input::getCursorVelocity().x*5.0f*Time::deltaTime;

    if (pitch>90)
        pitch=90;
    if (pitch<-90)
        pitch=-90;

    transform->setLocalEulerAngles(glm::vec3(pitch,yaw,0));
    forward = glm::cross(transform->getLeft(),{0,1,0});

    move = (-transform->getLeft()*Input::getAxis().x+forward*Input::getAxis().y)*5.0f*Time::deltaTime;
    if (Input::getKey(INPUT_KEY_SPACE))
        move+=glm::vec3{0,2*Time::deltaTime,0};
    if (Input::getKey(INPUT_KEY_LEFT_SHIFT)||Input::getKey(INPUT_KEY_RIGHT_SHIFT))
        move+=glm::vec3{0,-2*Time::deltaTime,0};
    transform->setLocalPosition(transform->getLocalPosition()+move);

}
