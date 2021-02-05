#include "GameClient.h"
#include <utils/Utils.h>
#include <game/system/Time.h>
#include <game/system/Window.h>
#include <game/system/Display.h>
#include <game/asset/AssetsManager.h>

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

void GameClient::init() {
    Window::tick();
    Display::init();
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


}

void GameClient::onExit() {
    Display::free();
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

void GameClient::tick() {
    Time::tick();
    Window::tick();
    Env::renderStart();
    Env::clearColor(glm::vec4(1, 1, 1, 1));
    if (currentScene)currentScene->tick();
    Env::renderEnd();
}

void GameClient::loadScene(Scene *scene) {
    this->currentScene = scene;
    scene->init();
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

