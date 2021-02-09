#include "MoveController.h"
#include "Transform.h"
#include "../object/GameObject.h"
#include "../system/Input.h"
#include "../system/Time.h"
#include "../system/Window.h"

MoveController::MoveController() : Component() {
}

MoveController::~MoveController() {

}

void MoveController::init() {
    Input::setCursor(Window::width/2,Window::height/2);
    transform= gameObject->transform;
}

void MoveController::tick() {
    pitch += Input::cursorVelocity.y*5.0f*Time::deltaTime;
    yaw += -Input::cursorVelocity.x*5.0f*Time::deltaTime;
    transform->setLocalEulerAngles(glm::vec3(pitch,yaw,0));

    move = (-transform->getLeft()*Input::getAxis().x+transform->getForward()*Input::getAxis().y)*5.0f*Time::deltaTime;
    transform->setLocalPosition(transform->getLocalPosition()+move);


    if (Input::getKey(INPUT_KEY_TAB))
        Input::unlockCursor();
    else
         Input::lockCursor();
}
