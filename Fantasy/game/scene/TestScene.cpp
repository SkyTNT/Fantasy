#include "TestScene.h"
#include <game/object/Cube.h>
#include <game/object/CameraObject.h>
#include <game/component/Camera.h>
#include <game/component/Transform.h>
#include <game/component/MoveController.h>
#include "../system/Time.h"
#include <utils/Utils.h>

Cube *cube, *cube2;
CameraObject *cameraObject;
GameObject *head;

TestScene::TestScene() : Scene() {
    cube = nullptr;
    cube2 = nullptr;
    cameraObject = nullptr;
    head = nullptr;
}

TestScene::~TestScene() {
    delete cube;
    delete cube2;
    delete cameraObject;
    delete head;
}

void TestScene::init() {
    Scene::init();
    cube = new Cube();
    cube2 = new Cube();
    cameraObject = new CameraObject();
    cube->name="cube";
    cube2->name="cube2";
    cameraObject->name="cam";
    cube->transform->setLocalPosition({0.5, 0.5, 0});
    cube2->transform->setLocalPosition({-1, 0, 0});
    cube->transform->setLocalEulerAngles({0,0,45});
    cube2->transform->setLocalEulerAngles({0,0,0});

    cameraObject->transform->setLocalPosition({0,0,-3});
    cameraObject->addComponent(new MoveController());
    root->addChild(cameraObject);
    root->addChild(cube);
    cube->addChild(cube2);
}

void TestScene::tick() {
    Scene::tick();
    cube->transform->setLocalEulerAngles(cube->transform->getLocalEulerAngles()+glm::vec3(0,50*Time::deltaTime,0));
}
