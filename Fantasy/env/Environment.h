#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Env {
    //��������
    struct DrawType {
        enum Enum {
            Point = 0,//�����
            Line,//������������
            LineStrip,//���߻���
            LineLoop,//�պ����߻���
            Triangle,//���������λ���
            TriangleStrip,//������������
            TriangleFan,//�������
        };
    };

    struct MemoryType {
        enum Enum {
            Static = 0,
            Dynamic,
            Stream
        };
    };
    //������������
    struct AttribType {
        enum Enum {
            Float = 0,//float
        };
    };
    //�����Ʒ�ʽ
    struct WrapType {
        enum Enum {
            Repeat = 0,//�ظ�
            MirroredRepeat,//�����ظ�
            ClampToEdge,//��Ե����
        };
    };

    //��ɫ��ʽ
    struct ColorType {
        enum Enum {
            RGB = 0,
            RGBA,
        };
    };

    //������˷�ʽ
    struct FilterType {
        enum Enum {
            Nearest = 0,//�ڽ�����
            Linear//�ڽ�����
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

    //������ɫ��������Ϊָ��index
    void setTexture(unsigned int shader, const std::string &name, unsigned int index);

    //������ָ��index
    void bindTexture2D(unsigned int index, unsigned int texture);

    //��������colorType:����ɫ�ʸ�ʽ��data:���������
    unsigned int
    createTexture2D(ColorType::Enum colorType, int width, int height, unsigned char *data);

    //ɾ������
    void delTexture2D(unsigned int texture);

    //�����Ʒ�ʽ
    void
    setTexture2DWrap(unsigned int texture, WrapType::Enum wrapType);

    //�������
    void setTexture2DFilter(unsigned int texture, FilterType::Enum filterType);

    //��������
    unsigned int createObject();

    //ɾ������
    void delObject(unsigned int obj);

    //��������vertexBuffer��elementBuffer��
    void objBindBuffer(unsigned int obj, unsigned int vertexBuffer, unsigned int elementBuffer);

    //���ö������ԵĲ��֣�location:����������shader�е�λ�ã�num:�������԰��������ݸ�����type:����������������,siride:����������һ����ͬ�������Լ����offset�����������뿪ͷ��ƫ�ƣ�normalize���Ƿ��׼��
    //������objBindBuffer�����
    void
    objSetVertexLayout(unsigned int obj, unsigned int location, unsigned int num, AttribType::Enum type,
                       size_t stride, void *offset, bool normalize);

    //��������
    void drawObject(unsigned int obj, unsigned int count, DrawType::Enum type, bool useIndices);

    //�������㻺�����
    unsigned int createVertexBuffer(size_t dataSize, void *data, MemoryType::Enum memType);

    //ɾ�����㻺�����
    void delVertexBuffer(unsigned int buffer);

    //д�붥�㻺������µ�����
    void writeVertexBuffer(unsigned int buffer, size_t dataSize, void *offset, void *data);

    //����һ�����㻺�������һ�����㻺�����
    void
    copyVertexBuffer(unsigned int sourceBuffer, unsigned int targetBuffer, void *sourceOffset, void *targetOffset,
                     size_t size);

    //���������������
    unsigned int createElementBuffer(size_t dataSize, void *data, MemoryType::Enum memType);

    //ɾ�������������
    void delElementBuffer(unsigned int buffer);

    //д��������������µ�����
    void writeElementBuffer(unsigned int buffer, size_t dataSize, void *offset, void *data);

    //����һ�����������������һ�������������
    void
    copyElementBuffer(unsigned int sourceBuffer, unsigned int targetBuffer, void *sourceOffset, void *targetOffset,
                      size_t size);
}
