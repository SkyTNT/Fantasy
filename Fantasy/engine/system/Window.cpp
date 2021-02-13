#include "Window.h"
#include <env/Environment.h>

int Window::width = 0;
int Window::height = 0;

void Window::tick() {
    width = Env::getWindowWidth();
    height = Env::getWindowHeight();
}
