#pragma once
#include <string>
#include <env/Environment.h>
#include "Asset.h"

//2D纹理
class Texture2D: public Asset {
public:
    explicit Texture2D(const std::string &path);
    ~Texture2D() override;

    //获取纹理
    unsigned int getTexture();
    //获取宽度
    int getWidth();
    //获取高度
    int getHeight();
    //获取颜色通道数量
    int getChannel();
    //获取颜色格式
    Env::ColorType::Enum getType();

private:
    unsigned int texture;
    int width, height, channels;
    Env::ColorType::Enum type;
    std::string path;
};

