#pragma once

#include "../Environment.h"

//openGL»·¾³
class GLEnv : public Environment {
public:
    GLEnv();

    ~GLEnv() override;

    bool setup(void *args) override;

    void cleanup() override;

    void windowResize(int width, int height) override;

    int getWindowWidth() override;

    int getWindowHeight() override;

    void renderStart() override;

    void renderEnd() override;

    void clearColor(glm::vec4 rgba) override;

    unsigned int createShader(std::string vertexShader, std::string fragmentShader) override;

    void useShader(unsigned int shader) override;

    void delShader(unsigned int shader) override;

    void setUniform(unsigned int shader, const std::string &name, float val) override;

    void setUniform(unsigned int shader, const std::string &name, const glm::vec2 &val) override;

    void setUniform(unsigned int shader, const std::string &name, const glm::vec3 &val) override;

    void setUniform(unsigned int shader, const std::string &name, const glm::vec4 &val) override;

    void setUniform(unsigned int shader, const std::string &name, const glm::mat2 &val, bool transpose) override;

    void setUniform(unsigned int shader, const std::string &name, const glm::mat2x3 &val, bool transpose) override;

    void setUniform(unsigned int shader, const std::string &name, const glm::mat2x4 &val, bool transpose) override;

    void setUniform(unsigned int shader, const std::string &name, const glm::mat3 &val, bool transpose) override;

    void setUniform(unsigned int shader, const std::string &name, const glm::mat3x2 &val, bool transpose) override;

    void setUniform(unsigned int shader, const std::string &name, const glm::mat3x4 &val, bool transpose) override;

    void setUniform(unsigned int shader, const std::string &name, const glm::mat4 &val, bool transpose) override;

    void setUniform(unsigned int shader, const std::string &name, const glm::mat4x2 &val, bool transpose) override;

    void setUniform(unsigned int shader, const std::string &name, const glm::mat4x3 &val, bool transpose) override;

    void setTexture(unsigned int shader, const std::string &name, unsigned int index) override;

    void bindTexture2D(unsigned int index, unsigned int texture) override;

    unsigned int createTexture2D(Env::ColorType::Enum colorType, int width, int height, unsigned char *data) override;

    void setTexture2DWrap(unsigned int texture, Env::WrapType::Enum wrapType) override;

    void setTexture2DFilter(unsigned int texture, Env::FilterType::Enum filterType) override;

    unsigned int createObject() override;

    void delObject(unsigned int obj) override;

    void objBindBuffer(unsigned int obj, unsigned int vertexBuffer, unsigned int elementBuffer) override;

    void objSetVertexLayout(unsigned int obj, unsigned int location, unsigned int num, Env::AttribType::Enum type,
                            size_t stride, void *offset, bool normalize) override;

    void drawObject(unsigned int obj, unsigned int count, Env::DrawType::Enum type) override;

    unsigned int createVertexBuffer(size_t dataSize, void *data) override;

    void delVertexBuffer(unsigned int buffer) override;

    void writeVertexBuffer(unsigned int buffer, size_t dataSize, void *offset, void *data) override;

    void copyVertexBuffer(unsigned int sourceBuffer, unsigned int targetBuffer, void *sourceOffset, void *targetOffset,
                          size_t size) override;

    unsigned int createElementBuffer(size_t dataSize, void *data) override;

    void delElementBuffer(unsigned int buffer) override;

    void writeElementBuffer(unsigned int buffer, size_t dataSize, void *offset, void *data) override;

    void copyElementBuffer(unsigned int sourceBuffer, unsigned int targetBuffer, void *sourceOffset, void *targetOffset,
                           size_t size) override;

private:

};