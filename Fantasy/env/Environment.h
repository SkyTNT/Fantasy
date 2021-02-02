#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Env {
    //��������
    struct DrawType {
        enum Enum {
            Point,//�����
            Line,//������������
            LineStrip,//���߻���
            LineLoop,//�պ����߻���
            Triangle,//���������λ���
            TriangleStrip,//������������
            TriangleFan,//�������
        };
    };
    //������������
    struct AttribType {
        enum Enum {
            Float,//float
        };
    };
    struct WrapType {
        enum Enum {
            Repeat,
            MirroredRepeat,
            ClampToEdge,
        };
    };

    struct ColorType {
        enum Enum {
            RGB,
            RGBA,
        };
    };

    struct FilterType {
        enum Enum {
            Nearest,
            Linear
        };
    };

    //��������
    bool setup(void *args);

    //������
    void cleanup();

    void windowResize(int width, int height);

    //��ȡ���ڿ��
    int getWindowWidth();

    //��ȡ���ڸ߶�
    int getWindowHeight();

    //ÿ����Ⱦ��ʼ����
    void renderStart();

    //ÿ����Ⱦ��β����
    void renderEnd();

    //����ɫ
    void clearColor(glm::vec4 rgba);

    //������ɫ�����򣨶�����ɫ�����룬Ƭ����ɫ�����룩
    unsigned int createShader(std::string vertexShader, std::string fragmentShader);

    //ʹ����ɫ��
    void useShader(unsigned int shader);

    //ɾ����ɫ��
    void delShader(unsigned int shader);

    //������ɫ���е�uniform����
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

    void setTexture(unsigned int shader, const std::string &name, unsigned int index);

    void bindTexture2D(unsigned int index, unsigned int texture);

    unsigned int
    createTexture2D(Env::ColorType::Enum colorType, int width, int height, unsigned char *data);

    void
    setTexture2DWrap(unsigned int texture, Env::WrapType::Enum wrapType);

    void setTexture2DFilter(unsigned int texture, Env::FilterType::Enum filterType);

    //��������
    unsigned int createObject();

    //ɾ������
    void delObject(unsigned int obj);

    //��������vertexBuffer��elementBuffer��
    void objBindBuffer(unsigned int obj, unsigned int vertexBuffer, unsigned int elementBuffer);

    //���ö������ԵĲ��֣�location:����������shader�е�λ�ã�num:�������԰��������ݸ�����type:����������������,siride:����������һ����ͬ�������Լ����offset�����������뿪ͷ��ƫ�ƣ�normalize���Ƿ��׼��
    void
    objSetVertexLayout(unsigned int obj, unsigned int location, unsigned int num, Env::AttribType::Enum type,
                       size_t stride, void *offset, bool normalize);

    //����obj
    void drawObject(unsigned int obj, unsigned int count, Env::DrawType::Enum type);

    //�������㻺�����
    unsigned int createVertexBuffer(size_t dataSize, void *data);

    //ɾ�����㻺�����
    void delVertexBuffer(unsigned int buffer);

    //д�붥�㻺������µ�����
    void writeVertexBuffer(unsigned int buffer, size_t dataSize, void *offset, void *data);

    //����һ�����㻺�������һ�����㻺�����
    void
    copyVertexBuffer(unsigned int sourceBuffer, unsigned int targetBuffer, void *sourceOffset, void *targetOffset,
                     size_t size);

    //���������������
    unsigned int createElementBuffer(size_t dataSize, void *data);

    //ɾ�������������
    void delElementBuffer(unsigned int buffer);

    //д��������������µ�����
    void writeElementBuffer(unsigned int buffer, size_t dataSize, void *offset, void *data);

    //����һ�����������������һ�������������
    void
    copyElementBuffer(unsigned int sourceBuffer, unsigned int targetBuffer, void *sourceOffset, void *targetOffset,
                      size_t size);
}
