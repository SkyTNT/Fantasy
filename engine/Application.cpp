#include "Application.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include <env/Environment.h>
#include <system/System.h>
#include <scene/Scene.h>
#include <asset/AssetsManager.h>
#include <utils/Utils.h>
#include <utils/FileManager.h>

static GLFWwindow* window = nullptr;
Application* Application::app = nullptr;

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

static void closeCallback(GLFWwindow* window)
{
    Application::app->exit();
}


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
        exiting = true;
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window,mouseButtonCallback);
    glfwSetWindowCloseCallback(window, closeCallback);
    Env::setup(window);
    Env::windowResize(1600,800);
    FileManager::basePath="../../fantasy/assets/";

    cursor = new DesktopCursor;
    Input::setCursor(cursor);
    System::init();
    AssetsManager::initAssets();
}

void Application::loop() {
    while (!exiting)
    {
        Env::renderStart();
        System::tick();
        if(currentScene)currentScene->tick();
        Env::renderEnd();
    }
}

void Application::cleanup() {
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

