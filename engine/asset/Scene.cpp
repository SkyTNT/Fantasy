#include "Scene.h"
#include <component/Component.h>

Scene::Scene() {
    root = new GameObject();
}

Scene::~Scene() {
    delete root;
}

void Scene::init() {

}

static void gameObjectsDFS(GameObject *gameObject) {
    for (auto component:gameObject->components) {
        if (!component->initialized) {
            component->init();
            component->initialized = true;
        }
        component->tick();
    }

    for (auto child:gameObject->children)
        gameObjectsDFS(child);
}

void Scene::tick() {
    gameObjectsDFS(root);
}
