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
}

void MoveController::tick() {
    yaw-=10*Input::cursorVelocity.x*Time::deltaTime;
    pitch-=10*Input::cursorVelocity.y*Time::deltaTime;;
    gameObject->transform->rotation.x=pitch;
    gameObject->transform->rotation.y=yaw;

    center = {0,0,0,1};
    right = {1,0,0,1};
    front = {0,0,-1,1};
    up = {0,1,0,1};

    glm::mat4 model = gameObject->transform->getMatrix();
    right = model*right-model*center;
    front = model*front-model*center;
    up = model*up-model*center;
    move = (right*Input::getAxis().x+front*Input::getAxis().y)*5.0f*Time::deltaTime;
    gameObject->transform->position.x+=move.x;
    gameObject->transform->position.y+=move.y;
    gameObject->transform->position.z+=move.z;

    if (Input::getKey(INPUT_KEY_TAB))
        Input::unlockCursor();
    else
         Input::lockCursor();
}
