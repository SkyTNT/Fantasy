#include "Transform.h"
#include "../object/GameObject.h"
#include "../system/Time.h"
#include <glm/gtc/matrix_transform.hpp>
#include <utils/Utils.h>

Transform::Transform() : Component() {
    localToWorld = worldToLocal = glm::mat4(1);
    position = eulerAngles =localPosition = localEulerAngles  = {0, 0, 0};
    rotation = localRotation = glm::qua<float>(eulerAngles);
    left = {1,0,0};
    forward = {0,0,1};
    up = {0 ,1 ,1};
    scale = {1, 1, 1};
}

void Transform::tick() {

}

void Transform::init() {

}

const glm::vec3 &Transform::getPosition(){
    return position;
}

const glm::vec3 &Transform::getEulerAngles(){
    return eulerAngles;
}

const glm::vec3 &Transform::getScale(){
    return scale;
}

const glm::vec3 &Transform::getLocalPosition(){
    return localPosition;
}

const glm::vec3 &Transform::getLocalEulerAngles(){
    return localEulerAngles;
}


const glm::vec3 &Transform::getLeft(){
    return left;
}

const glm::vec3 &Transform::getUp(){
    return up;
}

const glm::vec3 &Transform::getForward(){
    return forward;
}

const glm::mat4 &Transform::getLocalToWorld() {
    return localToWorld;
}

const glm::mat4 &Transform::getWorldToLocal() {
    return worldToLocal;
}

void Transform::setPosition(const glm::vec3 &val) {
    position = localPosition = val;
    if (gameObject->parent)
        localPosition = gameObject->parent->transform->worldToLocal * glm::vec4(position,1);
    recalculate();
}

void Transform::setEulerAngles(const glm::vec3 &val) {
    eulerAngles = localEulerAngles = val;
    rotation = localRotation = glm::qua<float>(glm::radians(eulerAngles));
    if (gameObject->parent){
        localRotation = glm::inverse(gameObject->parent->transform->rotation)*rotation;
        localEulerAngles = glm::eulerAngles(localRotation);
    }

    recalculate();
}

void Transform::setScale(const glm::vec3 &val) {
    scale = val;
    recalculate();
}

void Transform::setLocalPosition(const glm::vec3 &val) {
    localPosition =val;
    recalculate();
}

void Transform::setLocalEulerAngles(const glm::vec3 &val) {
    localEulerAngles =  val;
    localRotation = glm::qua<float>(glm::radians(val));
    recalculate();
    eulerAngles = glm::degrees(glm::eulerAngles(rotation));
}

void Transform::recalculate() {

    if (gameObject->parent){
        position = gameObject->parent->transform->localToWorld * glm::vec4(localPosition,1);
        rotation = gameObject->parent->transform->rotation*localRotation;
    } else{
        position = localPosition;
        rotation = localRotation;
    }

    left = rotation*glm::vec3{1,0,0};
    forward = rotation*glm::vec3{0,0,1};
    up = rotation*glm::vec3{0 ,1 ,0};

    //先缩放，后旋转，最后位移
    localToWorld = glm::mat4(1);
    localToWorld = glm::translate(localToWorld, position);
    localToWorld = localToWorld* glm::mat4_cast(rotation);
    localToWorld = glm::scale(localToWorld, scale);

    worldToLocal = glm::inverse(localToWorld);

    for(GameObject * child:gameObject->children){//重新计算子节点
        child->transform->recalculate();
    }

}


