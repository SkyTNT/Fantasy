#pragma once
class Scene;

class GameClient {
public:
    GameClient();

    ~GameClient();

    //初始化
    void init();

    //退出客户端
    void exit();

    //帧事件
    void tick();

    //加载场景
    void loadScene(Scene *scene);

    bool needExiting();//是否需要退出

    static GameClient *getGameClient();


private:
    //事件处理
    void onExit();
private:
    bool exiting;
    Scene *currentScene;
};
