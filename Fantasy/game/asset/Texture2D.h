#pragma once
#include <string>
#include <env/Environment.h>
#include "Asset.h"

//2D����
class Texture2D: public Asset {
public:
    explicit Texture2D(const std::string &path);
    ~Texture2D() override;

    //��ȡ����
    unsigned int getTexture();
    //��ȡ���
    int getWidth();
    //��ȡ�߶�
    int getHeight();
    //��ȡ��ɫͨ������
    int getChannel();
    //��ȡ��ɫ��ʽ
    Env::ColorType::Enum getType();

private:
    unsigned int texture;
    int width, height, channels;
    Env::ColorType::Enum type;
    std::string path;
};

