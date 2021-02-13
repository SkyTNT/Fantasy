//
// Created by iiiiiii on 2021/1/29.
//

#define GLFM_INCLUDE_ES3
#include <glfm.h>
#include <cstring>
#include <env/Environment.h>
#include <game/GameClient.h>
#include <game/scene/TestScene.h>
#include <game/system/Input.h>
#include <utils/Utils.h>

static GameClient*client;
static TestScene* testScene;

//虚拟鼠标
class MobileCursor: public Input::Cursor{
public:
    void setPos(float x, float y) override{
        pos.x=x;
        pos.y=y;
    }
    const glm::vec2 & getPos() override{
        return pos;
    }
};

static MobileCursor* cursor;

static void onSurfaceCreated(GLFMDisplay *display, int width, int height) {
    Env::setup(display);
    Env::windowResize(width,height);

    cursor = new MobileCursor;
    client=GameClient::getGameClient();
    testScene=new TestScene();

    Input::setCursor(cursor);
    client->loadScene(testScene);
}

static void onSurfaceResize(GLFMDisplay *display, int width, int height) {
    Env::windowResize(width,height);
}

static void onSurfaceDestroyed(GLFMDisplay *display) {
    client->exit();
    delete cursor;
    delete testScene;
    delete client;
}

static void onFrame(GLFMDisplay *display) {
    client->tick();
}
glm::vec2 startPos,deltaPos,realPos;
static bool onTouch(GLFMDisplay *display, int touch, GLFMTouchPhase phase, double x, double y){
    switch (phase) {
        case GLFMTouchPhaseBegan:
            startPos={x,y};
            break;
        case GLFMTouchPhaseMoved:
            deltaPos=glm::vec2{x,y}-startPos;
            realPos=cursor->getPos()+deltaPos;
            cursor->setPos(realPos.x,realPos.y);
            startPos={x,y};
            break;
        case GLFMTouchPhaseEnded:
            break;
    }
    return true;
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
    glfmSetTouchFunc(display, onTouch);

}

