#include <iostream>
#include <GameClient.h>
#include <utils/FileManager.h>
#include <scene/TestScene.h>
#include <Application.h>


//���ÿ���̨
//#pragma comment( linker, "/subsystem:windows /entry:mainCRTStartup" )
static TestScene* testScene;


class Fantasy: public Application{
public:
    void onCreate() override{
        testScene=new TestScene();
        client->loadScene(testScene);
    }

    void onExit() override{
        delete testScene;
    }
};

StartApplication(Fantasy)

