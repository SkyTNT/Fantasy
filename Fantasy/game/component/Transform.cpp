#include "Transform.h"
#include "../object/GameObject.h"
#include <glm/gtc/matrix_transform.hpp>

Transform::Transform(GameObject* gameObject) : Component(gameObject) {
    matrix = glm::mat4(1);
    position = rotation = {0,0,0};
    scale = {1,1,1};
}


Transform::~Transform()
{

}

void Transform::tick() {
    //�����ţ�����ת�����λ��
    matrix=glm::mat4(1);
    matrix=glm::scale(matrix,scale);
    matrix=glm::rotate(matrix,rotation.x,{1,0,0});
    matrix=glm::rotate(matrix,rotation.y,{0,1,0});
    matrix=glm::rotate(matrix,rotation.z,{0,0,1});
    matrix=glm::translate(matrix,position);
    if (gameObject->parent)
        matrix=gameObject->parent->transform->matrix*matrix;
}

void Transform::init() {

}


