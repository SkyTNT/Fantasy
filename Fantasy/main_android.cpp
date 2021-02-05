//
// Created by iiiiiii on 2021/1/29.
//

#define GLFM_INCLUDE_ES3
#include <glfm.h>
#include <cstring>
#include <env/Environment.h>
#include <client/GameClient.h>
#include <game/scene/TestScene.h>
#include <utils/Utils.h>

static GameClient*client;
static TestScene* testScene;

static void onSurfaceCreated(GLFMDisplay *display, int width, int height) {

    client=new GameClient();
    testScene=new TestScene();
    Env::setup(display);
    Env::windowResize(width,height);
    client->init();
    client->loadScene(testScene);
}

static void onSurfaceResize(GLFMDisplay *display, int width, int height) {
    Env::windowResize(width,height);
}

static void onSurfaceDestroyed(GLFMDisplay *display) {
    client->exit();
    delete testScene;
    delete client;
}

static void onFrame(GLFMDisplay *display) {
    client->tick();
}

void glfmMain(GLFMDisplay *display) {

    glfmSetDisplayConfig(display,
                         GLFMRenderingAPIOpenGLES2,
                         GLFMColorFormatRGBA8888,
                         GLFMDepthFormat16,
                         GLFMStencilFormatNone,
                         GLFMMultisampleNone);
    glfmSetSurfaceCreatedFunc(display, onSurfaceCreated);
    glfmSetSurfaceResizedFunc(display, onSurfaceResize);
    glfmSetSurfaceDestroyedFunc(display, onSurfaceDestroyed);
    glfmSetRenderFunc(display, onFrame);

}

