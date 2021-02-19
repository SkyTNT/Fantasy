#pragma once

#include <asset/Scene.h>

class TestScene : public Scene {
public:
    TestScene();

    ~TestScene() override;

    void init() override;

    void tick() override;
};
