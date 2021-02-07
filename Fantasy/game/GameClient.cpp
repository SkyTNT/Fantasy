#include "GameClient.h"
#include <utils/Utils.h>
#include <env/Environment.h>
#include <game/system/Time.h>
#include <game/system/Window.h>
#include <game/system/Display.h>
#include <game/system/Input.h>
#include <game/asset/AssetsManager.h>
#include <game/scene/Scene.h>

static GameClient *mClient= nullptr;

GameClient::GameClient() : exiting(false),currentScene(nullptr) {
    mClient = this;
}


GameClient::~GameClient() {
    onExit();
}


void GameClient::exit() {
    exiting = true;
}

void GameClient::init() {
    Window::tick();
    Input::init();
    Display::init();
    AssetsManager::initAssets();
}

void GameClient::onExit() {
    Display::free();
    AssetsManager::freeAssets();
    Env::cleanup();
}


void GameClient::tick() {
    Env::renderStart();
    Time::tick();
    Window::tick();
    Input::tick();
    Display::tick();
    if (currentScene)currentScene->tick();
    Env::renderEnd();
}

void GameClient::loadScene(Scene *scene) {
    this->currentScene = scene;
    scene->init();
}

bool GameClient::needExiting() {
    return exiting;
}

GameClient *GameClient::getGameClient() {
    if (!mClient)
    {
        mClient = new GameClient();
        mClient->init();
    }
    return mClient;
}

