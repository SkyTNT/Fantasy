#include <utils/Utils.h>
#include "GameObject.h"
#include "../component/Transform.h"


GameObject::GameObject() {
    parent = nullptr;
    transform = new Transform();
    addComponent(transform);
}


GameObject::~GameObject() {
    for (auto component:components) {
        delete component;
    }
}

Component *GameObject::getComponent(const std::type_info &info) {
    for (auto component:components) {
        if (typeid(*component) == info)
            return component;
    }
    return nullptr;
}

void GameObject::addComponent(Component *component) {
    component->gameObject= this;
    components.push_back(component);
}

void GameObject::addChild(GameObject *child) {
    child->parent= this;
    children.push_back(child);
}

