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
    head = new GameObject();
    cube->transform->position = {0.5, 0.5, 0};
    cube2->transform->position = {-1, 0, 0};
    cube->transform->rotation.z=-45;
    cameraObject->transform->rotation = {0, 0, 0};
    cameraObject->transform->position={0,0,3};
    cameraObject->addComponent(new MoveController());
    //head->addChild(cameraObject);
    root->addChild(cameraObject);
    root->addChild(cube);
    root->addChild(cube2);
}

void TestScene::tick() {
    Scene::tick();
    cube->transform->rotation.y+=50*Time::deltaTime;
    cube2->transform->rotation.x+=50*Time::deltaTime;
}
