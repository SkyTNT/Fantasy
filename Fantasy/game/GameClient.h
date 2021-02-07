#pragma once
class Scene;

class GameClient {
public:
    GameClient();

    ~GameClient();

    //��ʼ��
    void init();

    //�˳��ͻ���
    void exit();

    //֡�¼�
    void tick();

    //���س���
    void loadScene(Scene *scene);

    bool needExiting();//�Ƿ���Ҫ�˳�

    static GameClient *getGameClient();


private:
    //�¼�����
    void onExit();
private:
    bool exiting;
    Scene *currentScene;
};
