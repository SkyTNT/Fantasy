#include "Shader.h"
#include <env/Environment.h>
#include <utils/Utils.h>
Shader::Shader(const std::string &pathVert, const std::string &pathFrag):shader(0) {
    shader = Env::createShader(load_asset(pathVert), load_asset(pathFrag));
}

Shader::~Shader() {
    if (shader)
        Env::delShader(shader);
}

unsigned int Shader::getShader() {
    return shader;
}
