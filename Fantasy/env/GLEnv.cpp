#ifdef __ANDROID__
#define GLFM_INCLUDE_ES3
#include <glfm.h>
#else

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#endif

#include <glm/glm.hpp>
#include <utils/Utils.h>
#include "Environment.h"

static glm::ivec2 windowSize;
static glm::mat4 projection, view, model;
static int drawTypeMap[20], attribTypeMap[20], memTypeMap[20], colorTypeMap[20], wrapTypeMap[20], filterTypeMap[20];

#ifdef __ANDROID__
static GLFMDisplay *mDisplay;
#else
static GLFWwindow *window;
#endif

namespace Env {


    bool setup(void *args) {

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
        projection = view = model = glm::mat4(1);

        glEnable(GL_DEPTH_TEST);

        //初始化绘制类型的映射
        drawTypeMap[DrawType::Point] = GL_POINTS;
        drawTypeMap[DrawType::Line] = GL_LINES;
        drawTypeMap[DrawType::LineStrip] = GL_LINE_STRIP;
        drawTypeMap[DrawType::LineLoop] = GL_LINE_LOOP;
        drawTypeMap[DrawType::Triangle] = GL_TRIANGLES;
        drawTypeMap[DrawType::TriangleStrip] = GL_TRIANGLE_STRIP;
        drawTypeMap[DrawType::TriangleFan] = GL_TRIANGLE_FAN;
        //顶点属性类型映射
        attribTypeMap[AttribType::Float] = GL_FLOAT;

        memTypeMap[MemoryType::Static] = GL_STATIC_DRAW;
        memTypeMap[MemoryType::Dynamic] = GL_DYNAMIC_DRAW;
        memTypeMap[MemoryType::Stream] = GL_STREAM_DRAW;

        colorTypeMap[ColorType::RGB] = GL_RGB;
        colorTypeMap[ColorType::RGBA] = GL_RGBA;

        wrapTypeMap[WrapType::Repeat] = GL_REPEAT;
        wrapTypeMap[WrapType::MirroredRepeat] = GL_MIRRORED_REPEAT;
        wrapTypeMap[WrapType::ClampToEdge] = GL_CLAMP_TO_EDGE;

        filterTypeMap[FilterType::Linear] = GL_LINEAR;
        filterTypeMap[FilterType::Nearest] = GL_NEAREST;


        return true;
    }

    void cleanup() {
#ifdef __ANDROID__

#else
        glfwTerminate();
#endif
    }

    void windowResize(int width, int height) {
        windowSize = {width, height};
        glViewport(0, 0, width, height);
    }

    int getWindowWidth() {
        return windowSize.x;
    }

    int getWindowHeight() {
        return windowSize.y;
    }

    void renderStart() {
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    }

    void renderEnd() {
#ifdef __ANDROID__
        glfmSwapBuffers(mDisplay);
#else
        glfwPollEvents();
        glfwSwapBuffers(window);
#endif
    }

    void setClearColor(const glm::vec4 &rgba){
        glClearColor(rgba.r, rgba.g, rgba.b, rgba.a);
    }

    unsigned int createShader(std::string vertexShader, std::string fragmentShader) {
#ifdef __ANDROID__
        vertexShader="#version 300 es\n"+vertexShader;
        fragmentShader="#version 300 es\nprecision highp float;\n"+fragmentShader;
#else
        vertexShader = "#version 330 core\n" + vertexShader;
        fragmentShader = "#version 330 core\n" + fragmentShader;
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

    void useShader(unsigned int shader) {
        glUseProgram(shader);

        setUniform(shader, "projection", projection);
        setUniform(shader, "view", view);
        setUniform(shader, "model", model);
    }

    void delShader(unsigned int shader) {
        glDeleteProgram(shader);
    }

    void setProjection(const glm::mat4 &val) {
        projection = val;
    }

    void setView(const glm::mat4 &val) {
        view = val;
    }

    void setModel(const glm::mat4 &val) {
        model = val;
    }

    void setUniform(unsigned int shader, const std::string &name, float val) {
        int location = glGetUniformLocation(shader, name.c_str());
        glUniform1f(location, val);
    }

    void setUniform(unsigned int shader, const std::string &name, const glm::vec2 &val) {
        int location = glGetUniformLocation(shader, name.c_str());
        glUniform2fv(location, 1, &val[0]);
    }

    void setUniform(unsigned int shader, const std::string &name, const glm::vec3 &val) {
        int location = glGetUniformLocation(shader, name.c_str());
        glUniform3fv(location, 1, &val[0]);
    }

    void setUniform(unsigned int shader, const std::string &name, const glm::vec4 &val) {
        int location = glGetUniformLocation(shader, name.c_str());
        glUniform4fv(location, 1, &val[0]);
    }

#define __setMatrix(size)   int location = glGetUniformLocation(shader, name.c_str());\
                            glUniformMatrix##size##fv(location,1,GL_FALSE,&val[0][0]);

    void setUniform(unsigned int shader, const std::string &name, const glm::mat2 &val) {
        __setMatrix(2)
    }

    void setUniform(unsigned int shader, const std::string &name, const glm::mat2x3 &val) {
        __setMatrix(2x3)
    }

    void setUniform(unsigned int shader, const std::string &name, const glm::mat2x4 &val) {
        __setMatrix(2x4)
    }

    void setUniform(unsigned int shader, const std::string &name, const glm::mat3 &val) {
        __setMatrix(3)
    }

    void setUniform(unsigned int shader, const std::string &name, const glm::mat3x2 &val) {
        __setMatrix(3x2)
    }

    void setUniform(unsigned int shader, const std::string &name, const glm::mat3x4 &val) {
        __setMatrix(3x4)
    }

    void setUniform(unsigned int shader, const std::string &name, const glm::mat4 &val) {
        __setMatrix(4)
    }

    void setUniform(unsigned int shader, const std::string &name, const glm::mat4x2 &val) {
        __setMatrix(4x2)
    }

    void setUniform(unsigned int shader, const std::string &name, const glm::mat4x3 &val) {
        __setMatrix(4x3)
    }

#undef __setMatrix

    void setTexture(unsigned int shader, const std::string &name, unsigned int index) {
        glUniform1i(glGetUniformLocation(shader, name.c_str()), index);
    }

    void bindTexture2D(unsigned int index, unsigned int texture) {
        glActiveTexture(GL_TEXTURE0 + index);
        glBindTexture(GL_TEXTURE_2D, texture);
    }

    unsigned int createTexture2D(ColorType::Enum colorType, int width, int height, unsigned char *data) {
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, colorTypeMap[colorType], width, height, 0, colorTypeMap[colorType],
                     GL_UNSIGNED_BYTE,
                     data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

        return texture;
    }

    void delTexture2D(unsigned int texture) {
        glDeleteTextures(1, &texture);
    }

    void setTexture2DWrap(unsigned int texture, WrapType::Enum wrapType) {
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapTypeMap[wrapType]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapTypeMap[wrapType]);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void setTexture2DFilter(unsigned int texture, FilterType::Enum filterType) {
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterTypeMap[filterType]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterTypeMap[filterType]);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    unsigned int createObject() {
        unsigned int VAO;
        glGenVertexArrays(1, &VAO);

        return VAO;
    }

    void delObject(unsigned int obj) {
        glDeleteVertexArrays(1, &obj);
    }

    void objBindBuffer(unsigned int obj, unsigned int vertexBuffer, unsigned int elementBuffer) {
        glBindVertexArray(obj);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
        glBindVertexArray(0);
    }

    void objSetVertexLayout(unsigned int obj, unsigned int location, unsigned int num, AttribType::Enum type,
                            size_t stride, void *offset, bool normalize) {

        glBindVertexArray(obj);
        glVertexAttribPointer(location, num, attribTypeMap[type], normalize, stride, offset);
        glEnableVertexAttribArray(location);
        glBindVertexArray(0);
    }

    void drawObject(unsigned int obj, unsigned int count, DrawType::Enum type, bool useIndices) {
        glBindVertexArray(obj);
        if (useIndices)
            glDrawElements(drawTypeMap[type], count, GL_UNSIGNED_INT, 0);
        else
            glDrawArrays(drawTypeMap[type], 0, count);
        glBindVertexArray(0);
    }

    unsigned int createVertexBuffer(size_t dataSize, void *data, MemoryType::Enum memType) {
        unsigned int buffer = 0;
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, dataSize, data, memTypeMap[memType]);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        return buffer;
    }

    void delVertexBuffer(unsigned int buffer) {
        glDeleteBuffers(1, &buffer);
    }

    void writeVertexBuffer(unsigned int buffer, size_t dataSize, void *offset, void *data) {
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferSubData(GL_ARRAY_BUFFER, (GLintptr) offset, dataSize, data);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void
    copyVertexBuffer(unsigned int sourceBuffer, unsigned int targetBuffer, void *sourceOffset, void *targetOffset,
                     size_t size) {
        glBindBuffer(GL_COPY_WRITE_BUFFER, targetBuffer);
        glBindBuffer(GL_COPY_READ_BUFFER, sourceBuffer);
        glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, (GLintptr) sourceOffset, (GLintptr) targetOffset,
                            size);
        glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
        glBindBuffer(GL_COPY_READ_BUFFER, 0);
    }

    unsigned int createElementBuffer(size_t dataSize, void *data, MemoryType::Enum memType) {
        unsigned int buffer = 0;
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize, data, memTypeMap[memType]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        return buffer;
    }

    void delElementBuffer(unsigned int buffer) {
        glDeleteBuffers(1, &buffer);
    }

    void writeElementBuffer(unsigned int buffer, size_t dataSize, void *offset, void *data) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, (GLintptr) offset, dataSize, data);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void
    copyElementBuffer(unsigned int sourceBuffer, unsigned int targetBuffer, void *sourceOffset, void *targetOffset,
                      size_t size) {
        glBindBuffer(GL_COPY_WRITE_BUFFER, targetBuffer);
        glBindBuffer(GL_COPY_READ_BUFFER, sourceBuffer);
        glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, (GLintptr) sourceOffset, (GLintptr) targetOffset,
                            size);
        glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
        glBindBuffer(GL_COPY_READ_BUFFER, 0);
    }

}