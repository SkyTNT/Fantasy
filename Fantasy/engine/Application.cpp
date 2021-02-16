#include "Application.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include <GameClient.h>
#include <utils/Utils.h>
#include <utils/FileManager.h>
#include <env/Environment.h>
#include <scene/TestScene.h>
#include <system/Input.h>
static GLFWwindow* window;
static GameClient *mClient;

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

static void cursorCallback(GLFWwindow* window, double x, double y){

}

static void closeCallback(GLFWwindow* window)
{
    mClient->exit();
}


Application::Application() {

}

Application::~Application() {

}

void Application::onCreate() {

}

void Application::onExit() {

}

void Application::tick() {

}

void Application::setup() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(1600, 800, "Fantasy", nullptr, nullptr);
    //glfwSetWindowIcon(window, 1, );
    if (window == nullptr)
    {
        LOG_E("Main","Failed to create GLFW window");
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window,mouseButtonCallback);
    //glfwSetCursorPosCallback(window,cursorCallback);
    glfwSetWindowCloseCallback(window, closeCallback);
    Env::setup(window);
    Env::windowResize(1600,800);
    FileManager::basePath="../../fantasy/assets/";

    cursor = new DesktopCursor;
    Input::setCursor(cursor);
    client = mClient = GameClient::getGameClient();
}

void Application::loop() {
    while (!mClient->needExiting())
    {
        mClient->tick();
    }
}

void Application::cleanup() {
    delete cursor;
    delete mClient;
}

