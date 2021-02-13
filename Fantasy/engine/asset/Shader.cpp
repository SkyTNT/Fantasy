#include "Shader.h"
#include <env/Environment.h>
#include <utils/Utils.h>
#include <utils/FileManager.h>

Shader::Shader(const std::string &pathVert, const std::string &pathFrag) : pathVert(pathVert), pathFrag(pathFrag) {
    LOG_I("Asset", "load shader " + pathVert + " " + pathFrag);
    shader = Env::createShader(FileManager::loadText(pathVert), FileManager::loadText(pathFrag));
    if (!shader)
        LOG_E("Asset", "load shader " + pathVert + " " + pathFrag + " failed");
}

Shader::~Shader() {
    if (shader) {
        LOG_I("Asset", "free shader " + pathVert + " " + pathFrag);
        Env::delShader(shader);

    }
}

unsigned int Shader::getShader() {
    return shader;
}
