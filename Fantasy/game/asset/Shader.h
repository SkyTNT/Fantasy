#pragma once
#include <string>
#include "Asset.h"

class Shader: public Asset {
public:
    Shader(const std::string& pathVert, const std::string& pathFrag);
    ~Shader() override;

    unsigned int getShader();
private:
    unsigned int shader;
    std::string pathVert,pathFrag;
};

