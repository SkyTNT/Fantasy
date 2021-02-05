#include "TestScene.h"
#include <game/object/Cube.h>
#include <game/object/CameraObject.h>
#include <game/component/Transform.h>

Cube * cube,*cube2;
CameraObject *cameraObject;

TestScene::TestScene():Scene() {
    cube= nullptr;
    cube2= nullptr;
    cameraObject= nullptr;
}

TestScene::~TestScene() {
    delete cube;
    delete cube2;
    delete cameraObject;
}

void TestScene::init() {
    Scene::init();
    cube=new Cube();
    cube2=new Cube();
    cameraObject=new CameraObject();
    cube->transform->rotation={-45, 0, 0};
    cube->transform->position={0, 0, -10};
    cube2->transform->rotation={-40, 0, 0};
    cube2->transform->position={-1,0,0};
    cameraObject->transform->position={0,0,3};
    root->children.push_back(cube);
    root->children.push_back(cube2);
    root->children.push_back(cameraObject);
}

void TestScene::tick() {
    Scene::tick();
}
