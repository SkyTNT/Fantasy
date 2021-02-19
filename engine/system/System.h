#pragma once
#include "Display.h"
#include "Input.h"
#include "Time.h"
#include "Window.h"
#include "FileManager.h"

class System {
public:
    static void init();
    static void tick();
    static void shutDown();
};

