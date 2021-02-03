#pragma once
#include <string>

namespace FileManager {
    std::string loadText(const std::string &path);
    unsigned char *loadImage(const std::string &path,int *width,int *height,int *channel);
    void freeImage(unsigned char *data);
};

