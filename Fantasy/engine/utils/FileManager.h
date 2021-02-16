#pragma once

#include <string>

class FileManager {
public:
    static std::string  basePath;
    static std::string loadText(const std::string &path);

    static unsigned char *loadImage(const std::string &path, int *width, int *height, int *channel);

    static void freeImage(unsigned char *data);
};
