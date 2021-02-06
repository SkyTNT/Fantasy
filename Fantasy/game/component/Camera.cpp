#include "Camera.h"
#include "Transform.h"
#include "../system/Window.h"
#include "../system/Display.h"
#include "../object/GameObject.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(GameObject *gameObject) : Component(gameObject) {
    clearColor = {0, 0, 0,1};
    viewField = 45;
    near = 0.1f;
    far = 1000;
    display = 0;
    projection = view = glm::mat4(1);
}


void Camera::init() {

}

void Camera::tick() {
    projection = glm::perspective(glm::radians(viewField), (float) Window::width / (float) Window::height, near, far);
    Transform *transform = gameObject->transform;
    //相机的操作顺序和transform相反
    view = glm::mat4(1);
    view = glm::rotate(view, glm::radians(-transform->rotation.x), {1, 0, 0});
    view = glm::rotate(view, glm::radians(-transform->rotation.y), {0, 1, 0});
    view = glm::rotate(view, glm::radians(-transform->rotation.z), {0, 0, 1});
    view = glm::translate(view, -transform->position);

    if (display < 8) {
        Display::displays[display]->projection = projection;
        Display::displays[display]->view = view;
        Display::displays[display]->clearColor = clearColor;
    }
}


