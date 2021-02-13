#include "Camera.h"
#include "Transform.h"
#include "../system/Window.h"
#include "../system/Display.h"
#include "../object/GameObject.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() : Component() {

}


void Camera::init() {

}

void Camera::tick() {
    if (display < 8) {
        Display::displays[display]->projection = glm::perspective(glm::radians(viewField), (float) Window::width / (float) Window::height, near, far);
        Display::displays[display]->view = glm::inverse(glm::rotate(gameObject->transform->getLocalToWorld(),glm::radians(180.0f),{0,1,0}));//相机的变换是与物体的变换相反的
        Display::displays[display]->clearColor = clearColor;
    }
}


