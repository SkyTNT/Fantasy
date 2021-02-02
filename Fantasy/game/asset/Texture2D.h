#pragma once
#include <string>
class Texture2D {
public:
    explicit Texture2D(const std::string &path);
    ~Texture2D();

    unsigned int getTexture();

private:
    unsigned int texture;
    int width, height, channels;
};

