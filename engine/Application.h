#pragma once

class GameClient;
class Scene;

class Application {
public:
    Application();

    virtual ~Application();

    void setup();

    void exit();

    void cleanup();

    virtual void onCreate();

    virtual void loop();

    virtual void onExit();

    void loadScene(Scene *scene);

    static Application *app;
private:
    bool exiting;
    Scene *currentScene;
};

#define StartApplication(AppClass)  \
int main(int argNum,char**args)     \
{                                   \
    auto *app=new AppClass;         \
    Application::app = app;         \
    app->setup();                   \
    app->onCreate();                \
    app->loop();                    \
    app->onExit();                  \
    app->cleanup();                 \
    delete app;                     \
    return 0;                       \
}
