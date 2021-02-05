#pragma once

#include <string>
#include "Asset.h"

//着色器
class Shader : public Asset {
public:
    Shader(const std::string &pathVert, const std::string &pathFrag);

    ~Shader() override;

    //获取着色器
    unsigned int getShader();

private:
    unsigned int shader;
    std::string pathVert, pathFrag;
};
