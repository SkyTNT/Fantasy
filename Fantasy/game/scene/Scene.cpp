#include "Scene.h"

Scene::Scene() {
    root=new GameObject();
}

Scene::~Scene() {
    delete root;
}

void Scene::init() {

}
