#pragma once
#include <map>
#include <string>
#include <glm/glm.hpp>
#include <env/Environment.h>

class Material {
public:
    Material();

private:
    unsigned int shader;
    std::map<std::string, float>floatUniforms;
    std::map<std::string, glm::vec2>vec2Uniforms;
    std::map<std::string, glm::vec3>vec3Uniforms;
    std::map<std::string, glm::vec4>vec4Uniforms;
    std::map<std::string, glm::mat2>mat2Uniforms;
    std::map<std::string, glm::mat2x3>mat2x3Uniforms;
    std::map<std::string, glm::mat2x4>mat2x4Uniforms;
    std::map<std::string, glm::mat3>mat3Uniforms;
    std::map<std::string, glm::mat3x2>mat3x2Uniforms;
    std::map<std::string, glm::mat3x4>mat3x4Uniforms;
    std::map<std::string, glm::mat4>mat4Uniforms;
    std::map<std::string, glm::mat4x2>mat4x2Uniforms;
    std::map<std::string, glm::mat4x3>mat4x3Uniforms;
};

