#pragma once
#include <string>

namespace Env {
	//绘制类型
	struct DrawType
	{
		enum Enum {
			Point,//点绘制
			Line,//单独线条绘制
			LineStrip,//折线绘制
			LineLoop,//闭合折线绘制
			Triangle,//单独三角形绘制
			TriangleStrip,//三角条带绘制
			TriangleFan,//扇面绘制
		};
	};
	//顶点属性类型
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

	//建立环境
	virtual bool setup(void *args) = 0;
	//清理环境
	virtual void cleanup() = 0;

	virtual void windowResize(int width, int height) =0 ;
	//获取窗口宽度
	virtual int getWindowWidth() = 0;
	//获取窗口高度
	virtual int getWindowHeight() = 0;

	//每次渲染开始函数
	virtual void renderStart() = 0;
	//每次渲染结尾函数
	virtual void renderEnd() = 0;

	//创建着色器程序（顶点着色器代码，片段着色器代码）
	virtual unsigned int createShader(std::string vertexShader, std::string fragmentShader) = 0;
	//使用着色器
	virtual void useShader(unsigned int shader) = 0;
	//删除着色器
	virtual void delShader(unsigned int shader) = 0;


	//创建物体
	virtual unsigned int createObject() = 0;
	//删除物体
	virtual void delObject(unsigned int obj) = 0;
	//将物体与vertexBuffer，elementBuffer绑定
	virtual void objBindBuffer(unsigned int obj, unsigned int vertexBuffer, unsigned int elementBuffer) = 0;
	//设置顶点属性的布局，location:顶点属性在shader中的位置，num:顶点属性包含的数据个数，type:顶点属性数据类型,siride:步长即到下一个相同顶点属性间隔，offset：顶点属性与开头的偏移，normalize：是否标准化
	virtual void objSetVertexLayout(unsigned int obj, unsigned int location, unsigned int num, Env::AttribType::Enum type, size_t stride, void* offset, bool normalize) = 0;
	//以type的绘制方式绘制obj
	virtual void drawObject(unsigned int obj, unsigned int count, Env::DrawType::Enum type) = 0;

	//创建顶点缓冲对象
	virtual unsigned int createVertexBuffer(size_t dataSize, void* data) = 0;
	//删除顶点缓冲对象
	virtual void delVertexBuffer(unsigned int buffer) = 0;
	//写入顶点缓冲对象新的数据
	virtual void writeVertexBuffer(unsigned int buffer, size_t dataSize, void* offset, void* data) = 0;
	//复制一个顶点缓冲对象到另一个顶点缓冲对象
	virtual void copyVertexBuffer(unsigned int sourceBuffer, unsigned int targetBuffer, void* sourceOffset, void* targetOffset, size_t size) = 0;

	//创建索引缓冲对象
	virtual unsigned int createElementBuffer(size_t dataSize, void* data) = 0;
	//删除索引缓冲对象
	virtual void delElementBuffer(unsigned int buffer) = 0;
	//写入索引缓冲对象新的数据
	virtual void writeElementBuffer(unsigned int buffer, size_t dataSize, void* offset, void* data) = 0;
	//复制一个索引缓冲对象到了另一个索引缓冲对象
	virtual void copyElementBuffer(unsigned int sourceBuffer, unsigned int targetBuffer, void* sourceOffset, void* targetOffset, size_t size) = 0;
};
