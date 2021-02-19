#pragma once

class GameClient;
class Scene;

class Application {
public:
    struct Config;

    Application();

    virtual ~Application();

    void setup(const Config &config);

    void exit();

    void cleanup();

    virtual void onCreate();

    virtual void loop();

    virtual void onExit();

    void loadScene(Scene *scene);

    static Application *app;

    Scene *currentScene;
private:
    bool exiting;
public:
    struct Config{
        int width,height;
    };
};
#ifdef __ANDROID__
#include <glfm.h>

void onSurfaceCreated(GLFMDisplay *display_, int width, int height);
void onSurfaceResize(GLFMDisplay *display_, int width, int height);
void onSurfaceDestroyed(GLFMDisplay *display_);
void onFrame(GLFMDisplay *display_);
bool onTouch(GLFMDisplay *display_, int touch, GLFMTouchPhase phase, double x, double y);

#define StartApplication(AppClass,width,height)\
void glfmMain(GLFMDisplay *display) {\
    glfmSetDisplayConfig(display,\
                         GLFMRenderingAPIOpenGLES2,\
                         GLFMColorFormatRGBA8888,\
                         GLFMDepthFormat16,\
                         GLFMStencilFormatNone,\
                         GLFMMultisampleNone);\
    glfmSetSurfaceCreatedFunc(display, onSurfaceCreated);\
    glfmSetSurfaceResizedFunc(display, onSurfaceResize);\
    glfmSetSurfaceDestroyedFunc(display, onSurfaceDestroyed);\
    glfmSetRenderFunc(display, onFrame);\
    glfmSetTouchFunc(display, onTouch);\
    Application::app = new AppClass;\
}

#else

#define StartApplication(AppClass,width,height)  \
int main(int argc,char **argv){\
Application::app = new AppClass;\
Application::app->setup({width,height});\
Application::app->onCreate();\
Application::app->loop();\
Application::app->onExit();\
Application::app->cleanup();\
delete Application::app;\
Application::app = nullptr;\
return 0;\
}
#endif