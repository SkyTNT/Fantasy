#include "Texture2D.h"
#include <stb_image.h>
#include <env/Environment.h>
#include <utils/Utils.h>

Texture2D::Texture2D(const std::string &path) {
    unsigned char *data = stbi_load("../assets/wall.jpg", &width, &height, &channels, 0);
    if (data)
        texture=Env::createTexture2D(Env::ColorType::RGB,width,height,data);
    else
        LOG_E("File","texture load failed");
    stbi_image_free(data);
}

Texture2D::~Texture2D() {
    Env::delTexture2D(texture);
}

unsigned int Texture2D::getTexture() {
    return texture;
}
