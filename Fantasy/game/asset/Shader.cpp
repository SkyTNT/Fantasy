#include "Shader.h"
#include <env/Environment.h>
#include <utils/Utils.h>
#include <utils/FileManager.h>
Shader::Shader(const std::string &pathVert, const std::string &pathFrag) {
    shader = Env::createShader(FileManager::loadText(pathVert), FileManager::loadText(pathFrag));
}

Shader::~Shader() {
    if (shader)
        Env::delShader(shader);
}

unsigned int Shader::getShader() {
    return shader;
}
