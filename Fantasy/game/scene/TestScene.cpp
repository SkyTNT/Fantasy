#include "TestScene.h"
#include <game/object/Cube.h>
#include <game/object/CameraObject.h>
#include <game/component/Camera.h>
#include <game/component/Transform.h>
#include "../system/Time.h"
#include <utils/Utils.h>

Cube *cube, *cube2;
CameraObject *cameraObject;

TestScene::TestScene() : Scene() {
    cube = nullptr;
    cube2 = nullptr;
    cameraObject = nullptr;
}

TestScene::~TestScene() {
    delete cube;
    delete cube2;
    delete cameraObject;
}

void TestScene::init() {
    Scene::init();
    cube = new Cube();
    cube2 = new Cube();
    cameraObject = new CameraObject();
    cube->transform->position = {0.5, 0.5, 0};
    cube2->transform->position = {-1, 0, 0};
    cube->transform->rotation.z=-45;
    cameraObject->transform->position = {3, 3, 3};
    cameraObject->transform->rotation = {-45, 45, 0};
    root->children.push_back(cube);
    root->children.push_back(cube2);
    root->children.push_back(cameraObject);
}

void TestScene::tick() {
    Scene::tick();
    cube->transform->rotation.y+=50*Time::deltaTime;
    cube2->transform->rotation.x+=50*Time::deltaTime;
}
