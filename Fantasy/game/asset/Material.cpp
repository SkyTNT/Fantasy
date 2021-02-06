#include "Material.h"
#include <env/Environment.h>
#include <utils/Utils.h>

Material::Material() {
    shader = nullptr;
    shaderID = 0;
}

Material::Material(Shader *shader) : shader(shader) {
    shaderID = shader->getShader();
}

Material::~Material() {

}

void Material::setShader(Shader *shader) {
    this->shader = shader;
    shaderID = shader->getShader();
}

Shader *Material::getShader() {
    return shader;
}


//储存着色器Uniform
void Material::set(const std::string &name, float val) {
    floatUniforms[name] = val;
}

void Material::set(const std::string &name, const glm::vec2 &val) {
    vec2Uniforms[name] = val;
}

void Material::set(const std::string &name, const glm::vec3 &val) {
    vec3Uniforms[name] = val;
}

void Material::set(const std::string &name, const glm::vec4 &val) {
    vec4Uniforms[name] = val;
}

void Material::set(const std::string &name, const glm::mat2 &val) {
    mat2Uniforms[name] = val;
}

void Material::set(const std::string &name, const glm::mat2x3 &val) {
    mat2x3Uniforms[name] = val;
}

void Material::set(const std::string &name, const glm::mat2x4 &val) {
    mat2x4Uniforms[name] = val;
}

void Material::set(const std::string &name, const glm::mat3 &val) {
    mat3Uniforms[name] = val;
}

void Material::set(const std::string &name, const glm::mat3x2 &val) {
    mat3x2Uniforms[name] = val;
}

void Material::set(const std::string &name, const glm::mat3x4 &val) {
    mat3x4Uniforms[name] = val;
}

void Material::set(const std::string &name, const glm::mat4 &val) {
    mat4Uniforms[name] = val;
}

void Material::set(const std::string &name, const glm::mat4x2 &val) {
    mat4x2Uniforms[name] = val;
}

void Material::set(const std::string &name, const glm::mat4x3 &val) {
    mat4x3Uniforms[name] = val;
}

void Material::set(const std::string &name, Texture2D *val) {
    auto it = texture2DIndex.find(name);
    if (it == texture2DIndex.end()) {
        texture2DIndex[name] = texture2Ds.size();
        texture2Ds.push_back(val);
    } else {
        texture2Ds[it->second] = val;
    }

}

#define setUniforms(type)   for (const auto &it:type##Uniforms) {\
                                Env::setUniform(shaderID, it.first, it.second);\
                            }

//使用着色器并设置uniform
void Material::use() {
    Env::useShader(shaderID);
    setUniforms(float)
    setUniforms(vec2)
    setUniforms(vec3)
    setUniforms(vec4)
    setUniforms(mat2)
    setUniforms(mat2x3)
    setUniforms(mat2x4)
    setUniforms(mat3)
    setUniforms(mat3x2)
    setUniforms(mat3x4)
    setUniforms(mat4)
    setUniforms(mat4x2)
    setUniforms(mat4x3)

    for (const auto &it:texture2DIndex) {
        Env::setTexture(shaderID, it.first, it.second);
        Env::bindTexture2D(it.second, texture2Ds[it.second]->getTexture());
    }
}

#undef setUniforms
