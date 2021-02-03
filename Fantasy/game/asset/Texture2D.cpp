#include "Texture2D.h"
#include <stb_image.h>
#include <env/Environment.h>
#include <utils/Utils.h>

Texture2D::Texture2D(const std::string &path) {
    texture=0;
    this->path=path;
    LOG_I("File","load texture2D "+path);
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    type=channels==3?(Env::ColorType::RGB):(Env::ColorType::RGBA);
    if (data)
        texture=Env::createTexture2D(type,width,height,data);
    else
        LOG_E("File","texture load failed");
    stbi_image_free(data);
}

Texture2D::~Texture2D() {
    LOG_I("File","release texture2D "+path);
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
