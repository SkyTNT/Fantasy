#pragma once

#include <map>
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include "Shader.h"
#include "Texture2D.h"

//材质
class Material : public Asset {
public:
    Material();

    explicit Material(Shader *shader);

    ~Material() override;

    //设置使用的着色器
    void setShader(Shader *shader);
    Shader* getShader();

    //设置材质属性
    void set(const std::string &name, float val);

    void set(const std::string &name, const glm::vec2 &val);

    void set(const std::string &name, const glm::vec3 &val);

    void set(const std::string &name, const glm::vec4 &val);

    void set(const std::string &name, const glm::mat2 &val);

    void set(const std::string &name, const glm::mat2x3 &val);

    void set(const std::string &name, const glm::mat2x4 &val);

    void set(const std::string &name, const glm::mat3 &val);

    void set(const std::string &name, const glm::mat3x2 &val);

    void set(const std::string &name, const glm::mat3x4 &val);

    void set(const std::string &name, const glm::mat4 &val);

    void set(const std::string &name, const glm::mat4x2 &val);

    void set(const std::string &name, const glm::mat4x3 &val);

    void set(const std::string &name, Texture2D *val);

    void use();

private:
    Shader *shader;
    unsigned int shaderID;
    //材质属性
    std::map<std::string, float> floatUniforms;
    std::map<std::string, glm::vec2> vec2Uniforms;
    std::map<std::string, glm::vec3> vec3Uniforms;
    std::map<std::string, glm::vec4> vec4Uniforms;
    std::map<std::string, glm::mat2> mat2Uniforms;
    std::map<std::string, glm::mat2x3> mat2x3Uniforms;
    std::map<std::string, glm::mat2x4> mat2x4Uniforms;
    std::map<std::string, glm::mat3> mat3Uniforms;
    std::map<std::string, glm::mat3x2> mat3x2Uniforms;
    std::map<std::string, glm::mat3x4> mat3x4Uniforms;
    std::map<std::string, glm::mat4> mat4Uniforms;
    std::map<std::string, glm::mat4x2> mat4x2Uniforms;
    std::map<std::string, glm::mat4x3> mat4x3Uniforms;
    std::map<std::string, int> texture2DIndex;
    std::vector<Texture2D *> texture2Ds;
};
