#include "GameClient.h"
#include <utils/Utils.h>
#include <game/system/Time.h>
#include <game/system/Window.h>
#include <game/asset/AssetsManager.h>
#include <game/object/Cube.h>
#include <game/component/Transform.h>

static GameClient *mClient;

GameClient::GameClient() : exiting(false){
    mClient = this;
    currentScene = nullptr;
    input = new Input();
}


GameClient::~GameClient() {
    onExit();
    delete input;
}


void GameClient::exit() {
    exiting = true;
}

Cube * cube;


void GameClient::init() {
    Window::update();//让初始化时就能获取窗口大小
    AssetsManager::initAssets();


    //设置输入回调
    input->setKeyCallBack([this](int code, int mods, int action) {
        onKeyEvent(code, mods, action);
    });
    input->setMouseKeyCallBack([this](int code, int mods, int action) {
        onMouseKeyEvent(code, mods, action);
    });
    input->setMouseMoveCallBack([this](float x, float y) {
        onMouseMove(x, y);
    });
    loadScene(new Scene());

    cube=new Cube();
    cube->transform->rotation={-45,0,0};
    currentScene->root->children.push_back(cube);
}

void GameClient::onExit() {
    AssetsManager::freeAssets();
    Env::cleanup();
}


void GameClient::onKeyEvent(int code, int mods, int action) {
    switch (code) {
        case INPUT_KEY_ESCAPE:
            exit();
            break;
        default:
            break;
    }
}

void GameClient::onMouseKeyEvent(int code, int mods, int action) {

}

void GameClient::onMouseMove(float x, float y) {

}

void gameObjectsDFS(GameObject *gameObject){
    for(auto component:gameObject->components)
    {
        if(!component->initialized)
        {
            component->init();
            component->initialized= true;
        }
        component->tick();
    }

    for(auto child:gameObject->children)
        gameObjectsDFS(child);
}

void GameClient::tick() {
    Time::update();
    Window::update();
    Env::renderStart();
    Env::clearColor(glm::vec4(1, 1, 1, 1));
    gameObjectsDFS(currentScene->root);
    Env::renderEnd();
}

void GameClient::loadScene(Scene *scene) {
    this->currentScene = scene;
}

Input *GameClient::getInput() {
    return input;
}

bool GameClient::needExiting() {
    return exiting;
}

GameClient *GameClient::getGameClient() {
    return mClient;
}

