#pragma once
#include <string>
#include <env/Environment.h>

class Texture2D {
public:
    explicit Texture2D(const std::string &path);
    ~Texture2D();

    unsigned int getTexture();
    int getWidth();
    int getHeight();
    int getChannel();
    Env::ColorType::Enum getType();

private:
    unsigned int texture;
    int width, height, channels;
    Env::ColorType::Enum type;
    std::string path;
};

