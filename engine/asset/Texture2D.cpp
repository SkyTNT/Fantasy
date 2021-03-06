#include "Texture2D.h"
#include <env/Environment.h>
#include <utils/Utils.h>
#include <system/FileManager.h>

Texture2D::Texture2D(const std::string &path) {
    texture = 0;
    width = 0;
    height = 0;
    channels = 0;
    this->path = path;
    LOG_I("Asset", "load texture2D " + path);
    unsigned char *data = FileManager::loadImage(path.c_str(), &width, &height, &channels);
    type = channels == 3 ? (Env::ColorType::RGB) : (Env::ColorType::RGBA);
    if (data)
        texture = Env::createTexture2D(type, width, height, data);
    else
        LOG_E("Asset", path + " texture load failed");
    FileManager::freeImage(data);
}

Texture2D::~Texture2D() {
    LOG_I("Asset", "free texture2D " + path);
    Env::delTexture2D(texture);
}

unsigned int Texture2D::getTexture() {
    return texture;
}

int Texture2D::getWidth() {
    return width;
}

int Texture2D::getHeight() {
    return height;
}

int Texture2D::getChannel() {
    return channels;
}

Env::ColorType::Enum Texture2D::getType() {
    return type;
}
