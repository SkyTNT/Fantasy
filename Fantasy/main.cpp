#include <iostream>
#include <client/input/Input.h>
#include <client/GameClient.h>
#include <client/env/gl/GLEnv.h>



int main(int argNum,char**args)
{
    GLEnv *env = new GLEnv();
    GameClient *mClient = new GameClient();
	env->setup(0);
	mClient->init(env);
    while (!mClient->needExiting())
    {
        mClient->tick();
        mClient->render();
    }
	mClient->exit();
	delete mClient;
	delete env;
	return 0;
}
