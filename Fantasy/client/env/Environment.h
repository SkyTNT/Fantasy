#pragma once
#include <string>

namespace Env {
	//��������
	struct DrawType
	{
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
	struct AttribType
	{
		enum Enum {
			Float,//float
		};
	};
}

class Environment
{
public:
	Environment();
	virtual ~Environment();

	//��������
	virtual bool setup(void *args) = 0;
	//������
	virtual void cleanup() = 0;

	virtual void windowResize(int width, int height) =0 ;
	//��ȡ���ڿ��
	virtual int getWindowWidth() = 0;
	//��ȡ���ڸ߶�
	virtual int getWindowHeight() = 0;

	//ÿ����Ⱦ��ʼ����
	virtual void renderStart() = 0;
	//ÿ����Ⱦ��β����
	virtual void renderEnd() = 0;

	//������ɫ�����򣨶�����ɫ�����룬Ƭ����ɫ�����룩
	virtual unsigned int createShader(std::string vertexShader, std::string fragmentShader) = 0;
	//ʹ����ɫ��
	virtual void useShader(unsigned int shader) = 0;
	//ɾ����ɫ��
	virtual void delShader(unsigned int shader) = 0;


	//��������
	virtual unsigned int createObject() = 0;
	//ɾ������
	virtual void delObject(unsigned int obj) = 0;
	//��������vertexBuffer��elementBuffer��
	virtual void objBindBuffer(unsigned int obj, unsigned int vertexBuffer, unsigned int elementBuffer) = 0;
	//���ö������ԵĲ��֣�location:����������shader�е�λ�ã�num:�������԰��������ݸ�����type:����������������,siride:����������һ����ͬ�������Լ����offset�����������뿪ͷ��ƫ�ƣ�normalize���Ƿ��׼��
	virtual void objSetVertexLayout(unsigned int obj, unsigned int location, unsigned int num, Env::AttribType::Enum type, size_t stride, void* offset, bool normalize) = 0;
	//��type�Ļ��Ʒ�ʽ����obj
	virtual void drawObject(unsigned int obj, unsigned int count, Env::DrawType::Enum type) = 0;

	//�������㻺�����
	virtual unsigned int createVertexBuffer(size_t dataSize, void* data) = 0;
	//ɾ�����㻺�����
	virtual void delVertexBuffer(unsigned int buffer) = 0;
	//д�붥�㻺������µ�����
	virtual void writeVertexBuffer(unsigned int buffer, size_t dataSize, void* offset, void* data) = 0;
	//����һ�����㻺�������һ�����㻺�����
	virtual void copyVertexBuffer(unsigned int sourceBuffer, unsigned int targetBuffer, void* sourceOffset, void* targetOffset, size_t size) = 0;

	//���������������
	virtual unsigned int createElementBuffer(size_t dataSize, void* data) = 0;
	//ɾ�������������
	virtual void delElementBuffer(unsigned int buffer) = 0;
	//д��������������µ�����
	virtual void writeElementBuffer(unsigned int buffer, size_t dataSize, void* offset, void* data) = 0;
	//����һ�����������������һ�������������
	virtual void copyElementBuffer(unsigned int sourceBuffer, unsigned int targetBuffer, void* sourceOffset, void* targetOffset, size_t size) = 0;
};
