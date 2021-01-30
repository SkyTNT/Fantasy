#include <iostream>
#include <GLFW/glfw3.h>
#include <client/input/Input.h>
#include <client/GameClient.h>
#include <client/env/gl/GLEnv.h>
#include <utils/Utils.h>

static GLEnv *env;
static GLFWwindow* window;
static GameClient *mClient;

static void framebuffer_size_callback(GLFWwindow* window,int width,int height) {
    env->windowResize(width,height);
}

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    mClient->getInput()->sendKeyEvent(key, mods, action);
}

static void closeCallback(GLFWwindow* window)
{
    mClient->exit();
}


int main(int argNum,char**args)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(1600, 800, "Fantasy", NULL, NULL);
    //glfwSetWindowIcon(window, 1, );
    if (window == NULL)
    {
        LOG_E("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetWindowCloseCallback(window, closeCallback);

    env = new GLEnv();
    mClient = new GameClient();

	env->setup(window);
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
