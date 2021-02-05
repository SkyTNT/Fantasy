#pragma once
#include "Scene.h"

class TestScene: public Scene {
public:
    TestScene();
    ~TestScene() override;

    void init() override;
    void tick() override;
};

