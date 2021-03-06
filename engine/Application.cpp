#include "Application.h"
#include <iostream>
#include <env/Environment.h>
#include <system/System.h>
#include <asset/Scene.h>
#include <asset/AssetsManager.h>
#include <utils/Utils.h>

#ifdef __ANDROID__

GLFMDisplay *display = nullptr;

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

void onSurfaceCreated(GLFMDisplay *display_, int width, int height) {
    display = display_;
    Application::app->setup({width,height});
    Application::app->onCreate();
}

void onSurfaceResize(GLFMDisplay *display_, int width, int height) {
    Env::windowResize(width,height);
}

void onSurfaceDestroyed(GLFMDisplay *display_) {
    Application::app->onExit();
    Application::app->cleanup();
    delete Application::app;
}

void onFrame(GLFMDisplay *display_) {
    Env::renderStart();
    System::tick();
    if(Application::app->currentScene)Application::app->currentScene->tick();
    Env::renderEnd();
}

glm::vec2 startPos,deltaPos,realPos;
bool onTouch(GLFMDisplay *display_, int touch, GLFMTouchPhase phase, double x, double y){
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

#else

#include <GLFW/glfw3.h>
static GLFWwindow* window = nullptr;
//实现鼠标接口
class DesktopCursor: public Input::Cursor{
public:
    void setPos(float x, float y) override{
        pos.x=x;
        pos.y=y;
        glfwSetCursorPos(window,x,y);
    }
    const glm::vec2 & getPos() override{
        double x,y;
        glfwGetCursorPos(window,&x,&y);
        pos.x=x;
        pos.y=y;
        return pos;
    }
};

static DesktopCursor* cursor;

//GLFW的回调
static void framebuffer_size_callback(GLFWwindow* window,int width,int height) {
    Env::windowResize(width,height);
}

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action==GLFW_PRESS)
        Input::pressKey(key);
    else if (action==GLFW_RELEASE)
        Input::releaseKey(key);
}

static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods){
    if (action==GLFW_PRESS)
        Input::pressKey(button);
    else if (action==GLFW_RELEASE)
        Input::releaseKey(button);
}

static void closeCallback(GLFWwindow* window)
{
    Application::app->exit();
}
#endif

Application* Application::app = nullptr;

Application::Application() {
    exiting = false;
    currentScene = nullptr;
}

Application::~Application() {

}

void Application::onCreate() {

}

void Application::onExit() {

}

void Application::setup(const Config &config) {
#ifdef __ANDROID__
    Env::setup(display);
    Env::windowResize(config.width,config.height);
    cursor = new MobileCursor;
#else
    //初始化窗口
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(config.width, config.height, "Fantasy", nullptr, nullptr);
    //glfwSetWindowIcon(window, 1, );
    if (window == nullptr)
    {
        LOG_E("Main","Failed to create GLFW window");
        glfwTerminate();
        exiting = true;
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window,mouseButtonCallback);
    glfwSetWindowCloseCallback(window, closeCallback);

    Env::setup(window);
    Env::windowResize(config.width,config.height);
    cursor = new DesktopCursor;
    FileManager::basePath="../../fantasy/assets/";
#endif

    Input::setCursor(cursor);
    System::init();
    AssetsManager::initAssets();
}

void Application::loop() {
    //主循环
    while (!exiting)
    {
        Env::renderStart();
        System::tick();
        if(currentScene)currentScene->tick();
        Env::renderEnd();
    }
}

void Application::cleanup() {
    //结束引擎
    System::shutDown();
    AssetsManager::freeAssets();
    Env::cleanup();
    delete cursor;
}

void Application::exit() {
    exiting = true;
}

void Application::loadScene(Scene *scene){
    currentScene = scene;
    scene->init();
}

