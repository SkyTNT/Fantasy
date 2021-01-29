//
// Created by iiiiiii on 2021/1/29.
//

#define GLFM_INCLUDE_ES3
#include "glfm.h"
#include <cstring>
#include <client/env/gl/GLEnv.h>
#include <client/GameClient.h>


static GLEnv *glEnv;
static GameClient*client;

static void onSurfaceCreated(GLFMDisplay *display, int width, int height) {
    glEnv = new GLEnv();
    client=new GameClient();
    glEnv->setup(display);
    client->init(glEnv);
    glEnv->windowResize(width,height);
}

static void onSurfaceResize(GLFMDisplay *display, int width, int height) {
    glEnv->windowResize(width,height);
}

static void onSurfaceDestroyed(GLFMDisplay *display) {
    client->exit();
    delete client;
    delete glEnv;
}

static void onFrame(GLFMDisplay *display) {
    client->tick();
    client->render();
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

