#include "MoveController.h"
#include "Transform.h"
#include "../object/GameObject.h"
#include "../system/Input.h"
#include "../system/Time.h"
#include "../system/Window.h"

MoveController::MoveController(GameObject *gameObject) : Component(gameObject) {

}

MoveController::~MoveController() {

}

void MoveController::init() {
    //Input::setCursor(Window::width/2,Window::height/2);
    //Input::lockCursor();
}

void MoveController::tick() {
    gameObject->transform->position.x+=Input::getAxis().x*Time::deltaTime;
    gameObject->transform->position.z+=Input::getAxis().y*Time::deltaTime;
    gameObject->transform->rotation.x+=10*Input::cursorVelocity.x*Time::deltaTime;
    gameObject->transform->rotation.y+=10*Input::cursorVelocity.y*Time::deltaTime;
}
