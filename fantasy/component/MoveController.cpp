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
    transform->setLocalEulerAngles(glm::vec3(pitch,yaw,0));

    move = (-transform->getLeft()*Input::getAxis().x+transform->getForward()*Input::getAxis().y)*5.0f*Time::deltaTime;
    transform->setLocalPosition(transform->getLocalPosition()+move);

}
