#pragma once
#include <string>

class Shader {
public:
    Shader(const std::string& pathVert, const std::string& pathFrag);
    virtual ~Shader();

    unsigned int getShader();
private:
    unsigned int shader;
};

