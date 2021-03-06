#include <iostream>
#include <scene/TestScene.h>
#include <Application.h>


//½ûÓÃ¿ØÖÆÌ¨
//#pragma comment( linker, "/subsystem:windows /entry:mainCRTStartup" )

class Fantasy: public Application{
public:
    TestScene* testScene = nullptr;

    void onCreate() override{
        testScene=new TestScene();
        loadScene(testScene);
    }

    void onExit() override{
        delete testScene;
    }
};

StartApplication(Fantasy,1600,800);


