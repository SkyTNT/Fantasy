#pragma once
class GameClient;
class Application {
public:
    Application();
    virtual ~Application();

    void setup();
    void cleanup();
    virtual void onCreate();
    virtual void loop();
    virtual void onExit();
    virtual void tick();

protected:
    GameClient *client;
};

#define StartApplication(AppClass)\
int main(int argNum,char**args)\
{\
    auto *app=new AppClass;\
    app->setup();\
    app->onCreate();\
    app->loop();\
    app->onExit();\
    app->cleanup();\
    delete app;\
    return 0;\
}
