#include "System.h"


void System::init() {
    Input::init();
    Window::tick();
    Display::init();
}

void System::tick() {
    Time::tick();
    Window::tick();
    Input::tick();
    Display::tick();
}

void System::shutDown() {
    Display::free();
}
