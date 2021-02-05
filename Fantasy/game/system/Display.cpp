#include "Display.h"

Display* Display::displays[8];
Display* Display::current;
void Display::init() {
    for (auto & display : displays) {
        display=new Display();
        display->projection=glm::mat4(1);
        display->view=glm::mat4(1);
    }
    current=displays[0];
}

void Display::free() {
    for (auto & display : displays) {
        delete display;
    }
}


