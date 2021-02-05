#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Env {
    //绘制类型
    struct DrawType {
        enum Enum {
            Point = 0,//点绘制
            Line,//单独线条绘制
            LineStrip,//折线绘制
            LineLoop,//闭合折线绘制
            Triangle,//单独三角形绘制
            TriangleStrip,//三角条带绘制
            TriangleFan,//扇面绘制
        };
    };

    struct MemoryType {
        enum Enum {
            Static = 0,
            Dynamic,
            Stream
        };
    };
    //顶点属性类型
    struct AttribType {
        enum Enum {
            Float = 0,//float
        };
    };
    //纹理环绕方式
    struct WrapType {
        enum Enum {
            Repeat = 0,//重复
            MirroredRepeat,//镜像重复
            ClampToEdge,//边缘拉伸
        };
    };

    //颜色格式
    struct ColorType {
        enum Enum {
            RGB = 0,
            RGBA,
        };
    };

    //纹理过滤方式
    struct FilterType {
        enum Enum {
            Nearest = 0,//邻近过滤
            Linear//邻近过滤
        };
    };

    //建立环境
    bool setup(void *args);

    //清理环境
    void cleanup();

    void windowResize(int width, int height);

    //获取窗口宽度
    int getWindowWidth();

    //获取窗口高度
    int getWindowHeight();

    //每次渲染开始函数
    void renderStart();

    //每次渲染结尾函数
    void renderEnd();

    //清屏色
    void clearColor(glm::vec4 rgba);

    //创建着色器程序（顶点着色器代码，片段着色器代码）
    unsigned int createShader(std::string vertexShader, std::string fragmentShader);

    //使用着色器
    void useShader(unsigned int shader);

    //删除着色器
    void delShader(unsigned int shader);

    //设置着色器中的uniform变量
    void setUniform(unsigned int shader, const std::string &name, float val);

    void setUniform(unsigned int shader, const std::string &name, const glm::vec2 &val);

    void setUniform(unsigned int shader, const std::string &name, const glm::vec3 &val);

    void setUniform(unsigned int shader, const std::string &name, const glm::vec4 &val);

    void setUniform(unsigned int shader, const std::string &name, const glm::mat2 &val, bool transpose);

    void setUniform(unsigned int shader, const std::string &name, const glm::mat2x3 &val, bool transpose);

    void setUniform(unsigned int shader, const std::string &name, const glm::mat2x4 &val, bool transpose);

    void setUniform(unsigned int shader, const std::string &name, const glm::mat3 &val, bool transpose);

    void setUniform(unsigned int shader, const std::string &name, const glm::mat3x2 &val, bool transpose);

    void setUniform(unsigned int shader, const std::string &name, const glm::mat3x4 &val, bool transpose);

    void setUniform(unsigned int shader, const std::string &name, const glm::mat4 &val, bool transpose);

    void setUniform(unsigned int shader, const std::string &name, const glm::mat4x2 &val, bool transpose);

    void setUniform(unsigned int shader, const std::string &name, const glm::mat4x3 &val, bool transpose);

    //设置着色器中纹理为指定index
    void setTexture(unsigned int shader, const std::string &name, unsigned int index);

    //绑定纹理到指定index
    void bindTexture2D(unsigned int index, unsigned int texture);

    //创建纹理，colorType:纹理色彩格式，data:纹理的数据
    unsigned int
    createTexture2D(ColorType::Enum colorType, int width, int height, unsigned char *data);

    //删除纹理
    void delTexture2D(unsigned int texture);

    //纹理环绕方式
    void
    setTexture2DWrap(unsigned int texture, WrapType::Enum wrapType);

    //纹理过滤
    void setTexture2DFilter(unsigned int texture, FilterType::Enum filterType);

    //创建物体
    unsigned int createObject();

    //删除物体
    void delObject(unsigned int obj);

    //将物体与vertexBuffer，elementBuffer绑定
    void objBindBuffer(unsigned int obj, unsigned int vertexBuffer, unsigned int elementBuffer);

    //设置顶点属性的布局，location:顶点属性在shader中的位置，num:顶点属性包含的数据个数，type:顶点属性数据类型,siride:步长即到下一个相同顶点属性间隔，offset：顶点属性与开头的偏移，normalize：是否标准化
    //必须在objBindBuffer后调用
    void
    objSetVertexLayout(unsigned int obj, unsigned int location, unsigned int num, AttribType::Enum type,
                       size_t stride, void *offset, bool normalize);

    //绘制物体
    void drawObject(unsigned int obj, unsigned int count, DrawType::Enum type, bool useIndices);

    //创建顶点缓冲对象
    unsigned int createVertexBuffer(size_t dataSize, void *data, MemoryType::Enum memType);

    //删除顶点缓冲对象
    void delVertexBuffer(unsigned int buffer);

    //写入顶点缓冲对象新的数据
    void writeVertexBuffer(unsigned int buffer, size_t dataSize, void *offset, void *data);

    //复制一个顶点缓冲对象到另一个顶点缓冲对象
    void
    copyVertexBuffer(unsigned int sourceBuffer, unsigned int targetBuffer, void *sourceOffset, void *targetOffset,
                     size_t size);

    //创建索引缓冲对象
    unsigned int createElementBuffer(size_t dataSize, void *data, MemoryType::Enum memType);

    //删除索引缓冲对象
    void delElementBuffer(unsigned int buffer);

    //写入索引缓冲对象新的数据
    void writeElementBuffer(unsigned int buffer, size_t dataSize, void *offset, void *data);

    //复制一个索引缓冲对象到了另一个索引缓冲对象
    void
    copyElementBuffer(unsigned int sourceBuffer, unsigned int targetBuffer, void *sourceOffset, void *targetOffset,
                      size_t size);
}
