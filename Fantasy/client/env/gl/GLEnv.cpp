#ifdef __ANDROID__
#define GLFM_INCLUDE_ES3
#include <glfm.h>
#else

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#endif

#include <glm/glm.hpp>
#include <utils/Utils.h>
#include "GLEnv.h"

static GLEnv *env;
static glm::ivec2 windowSize;
static int drawTypeMap[20],attribTypeMap[20];

#ifdef __ANDROID__
static GLFMDisplay *mDisplay;
#else
static GLFWwindow *window;
#endif

GLEnv::GLEnv() : Environment() {
}

GLEnv::~GLEnv() {
}

bool GLEnv::setup(void *args) {
    env = this;

#ifdef __ANDROID__
    mDisplay= (GLFMDisplay *)(args);

#else
    window = (GLFWwindow *) args;
    //初始化opengl扩展
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        LOG_E("Env", "Failed to initialize opengl ");
        return false;
    }
#endif
    //初始化绘制类型的映射
    drawTypeMap[Env::DrawType::Point]=GL_POINTS;
    drawTypeMap[Env::DrawType::Line]=GL_LINES;
    drawTypeMap[Env::DrawType::LineStrip]=GL_LINE_STRIP;
    drawTypeMap[Env::DrawType::LineLoop]=GL_LINE_LOOP;
    drawTypeMap[Env::DrawType::Triangle]=GL_TRIANGLES;
    drawTypeMap[Env::DrawType::TriangleStrip]=GL_TRIANGLE_STRIP;
    drawTypeMap[Env::DrawType::TriangleFan]=GL_TRIANGLE_FAN;
    //顶点属性类型映射
    attribTypeMap[Env::AttribType::Float]=GL_FLOAT;

    return true;
}

void GLEnv::cleanup() {
#ifdef __ANDROID__

#else
    glfwTerminate();
#endif
}

void GLEnv::windowResize(int width, int height) {
    windowSize = {width, height};
    glViewport(0, 0, width, height);
}

int GLEnv::getWindowWidth() {
    return windowSize.x;
}

int GLEnv::getWindowHeight() {
    return windowSize.y;
}

void GLEnv::renderStart() {
}

void GLEnv::renderEnd() {
#ifdef __ANDROID__
    glfmSwapBuffers(mDisplay);
#else
    glfwPollEvents();
    glfwSwapBuffers(window);
#endif
}

void GLEnv::clearColor(glm::vec4 rgba) {
    glClearColor(rgba.r, rgba.g, rgba.b, rgba.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

unsigned int GLEnv::createShader(std::string vertexShader, std::string fragmentShader) {
#ifdef __ANDROID__
    vertexShader="#version 300 es\n"+vertexShader;
    fragmentShader="#version 300 es\nprecision highp float;\n"+fragmentShader;
#else
    vertexShader="#version 330 core\n"+vertexShader;
    fragmentShader="#version 330 core\n"+fragmentShader;
#endif
    const int logMaxLen = 1024;
    const char *vsc = vertexShader.c_str();
    const char *fsc = fragmentShader.c_str();

    //编译顶点着色器
    unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vsc, NULL);
    glCompileShader(vs);
    int success;
    char infoLog[logMaxLen];
    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vs, logMaxLen, NULL, infoLog);
        LOG_E("Env", "VertexShaderCompileError\n" + std::string(infoLog));
        return 0;
    }

    //编译片段着色器
    unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fsc, NULL);
    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fs, logMaxLen, NULL, infoLog);
        LOG_E("Env", "FragmentShaderCompileError\n" + std::string(infoLog));
        return 0;
    }

    //链接着色器程序
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vs);
    glAttachShader(shaderProgram, fs);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, logMaxLen, NULL, infoLog);
        LOG_E("Env", "ShaderLinkError\n" + std::string(infoLog));
        return 0;
    }
    glDeleteShader(vs);
    glDeleteShader(fs);

    return shaderProgram;
}

void GLEnv::useShader(unsigned int shader) {
    glUseProgram(shader);
}

void GLEnv::delShader(unsigned int shader) {
    glDeleteProgram(shader);
}

void GLEnv::setUniform(unsigned int shader, std::string name, float val) {
    int location = glGetUniformLocation(shader, name.c_str());
    glUniform1f(location,val);
}

void GLEnv::setUniform(unsigned int shader, std::string name, glm::vec2 val) {
    int location = glGetUniformLocation(shader, name.c_str());
    glUniform2fv(location,1,&val[0]);
}

void GLEnv::setUniform(unsigned int shader, std::string name, glm::vec3 val) {
    int location = glGetUniformLocation(shader, name.c_str());
    glUniform3fv(location,1,&val[0]);
}

void GLEnv::setUniform(unsigned int shader, std::string name, glm::vec4 val) {
    int location = glGetUniformLocation(shader, name.c_str());
    glUniform4fv(location,1,&val[0]);
}

#define __setMatrix(size)   int location = glGetUniformLocation(shader, name.c_str());\
                            glUniformMatrix##size##fv(location,1,transpose,&val[0][0]);

void GLEnv::setUniform(unsigned int shader, std::string name, glm::mat2 val,bool transpose) {
    __setMatrix(2)
}

void GLEnv::setUniform(unsigned int shader, std::string name, glm::mat2x3 val,bool transpose) {
    __setMatrix(2x3)
}

void GLEnv::setUniform(unsigned int shader, std::string name, glm::mat2x4 val,bool transpose) {
    __setMatrix(2x4)
}

void GLEnv::setUniform(unsigned int shader, std::string name, glm::mat3 val,bool transpose) {
    __setMatrix(3)
}

void GLEnv::setUniform(unsigned int shader, std::string name, glm::mat3x2 val,bool transpose) {
    __setMatrix(3x2)
}

void GLEnv::setUniform(unsigned int shader, std::string name, glm::mat3x4 val,bool transpose) {
    __setMatrix(3x4)
}

void GLEnv::setUniform(unsigned int shader, std::string name, glm::mat4 val,bool transpose) {
    __setMatrix(4)
}

void GLEnv::setUniform(unsigned int shader, std::string name, glm::mat4x2 val,bool transpose) {
    __setMatrix(4x2)
}

void GLEnv::setUniform(unsigned int shader, std::string name, glm::mat4x3 val,bool transpose) {
    __setMatrix(4x3)
}

#undef __setMatrix

unsigned int GLEnv::createObject() {
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    return VAO;
}

void GLEnv::delObject(unsigned int obj) {
    glDeleteVertexArrays(1, &obj);
}

void GLEnv::objBindBuffer(unsigned int obj, unsigned int vertexBuffer, unsigned int elementBuffer) {
    glBindVertexArray(obj);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glBindVertexArray(0);
}

void GLEnv::objSetVertexLayout(unsigned int obj, unsigned int location, unsigned int num, Env::AttribType::Enum type,
                               size_t stride, void *offset, bool normalize) {

    glBindVertexArray(obj);
    glVertexAttribPointer(location, num, attribTypeMap[type], normalize, stride, offset);
    glEnableVertexAttribArray(location);
    glBindVertexArray(0);
}

void GLEnv::drawObject(unsigned int obj, unsigned int count, Env::DrawType::Enum type) {
    glBindVertexArray(obj);
    glDrawElements(drawTypeMap[type], count, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

unsigned int GLEnv::createVertexBuffer(size_t dataSize, void *data) {
    unsigned int buffer = 0;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return buffer;
}

void GLEnv::delVertexBuffer(unsigned int buffer) {
    glDeleteBuffers(1, &buffer);
}

void GLEnv::writeVertexBuffer(unsigned int buffer, size_t dataSize, void *offset, void *data) {
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferSubData(GL_ARRAY_BUFFER, (GLintptr) offset, dataSize, data);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void
GLEnv::copyVertexBuffer(unsigned int sourceBuffer, unsigned int targetBuffer, void *sourceOffset, void *targetOffset,
                        size_t size) {
    glBindBuffer(GL_COPY_WRITE_BUFFER, targetBuffer);
    glBindBuffer(GL_COPY_READ_BUFFER, sourceBuffer);
    glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, (GLintptr) sourceOffset, (GLintptr) targetOffset,
                        size);
    glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
    glBindBuffer(GL_COPY_READ_BUFFER, 0);
}

unsigned int GLEnv::createElementBuffer(size_t dataSize, void *data) {
    unsigned int buffer = 0;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    return buffer;
}

void GLEnv::delElementBuffer(unsigned int buffer) {
    glDeleteBuffers(1, &buffer);
}

void GLEnv::writeElementBuffer(unsigned int buffer, size_t dataSize, void *offset, void *data) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, (GLintptr) offset, dataSize, data);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void
GLEnv::copyElementBuffer(unsigned int sourceBuffer, unsigned int targetBuffer, void *sourceOffset, void *targetOffset,
                         size_t size) {
    glBindBuffer(GL_COPY_WRITE_BUFFER, targetBuffer);
    glBindBuffer(GL_COPY_READ_BUFFER, sourceBuffer);
    glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, (GLintptr) sourceOffset, (GLintptr) targetOffset,
                        size);
    glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
    glBindBuffer(GL_COPY_READ_BUFFER, 0);
}


