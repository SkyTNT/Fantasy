#pragma once
#include "../Environment.h"

//openGL»·¾³
class GLEnv:public Environment
{
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
	unsigned int createShader(std::string vertexShader, std::string fragmentShader) override;
	void useShader(unsigned int shader) override;
	void delShader(unsigned int shader) override;

	unsigned int createObject() override;
	void delObject(unsigned int obj) override;
	void objBindBuffer(unsigned int obj, unsigned int vertexBuffer, unsigned int elementBuffer) override;
	void objSetVertexLayout(unsigned int obj, unsigned int location, unsigned int num, Env::AttribType::Enum type, size_t stride, void* offset, bool normalize) override;
	void drawObject(unsigned int obj, unsigned int count, Env::DrawType::Enum type) override;

	unsigned int createVertexBuffer(size_t dataSize, void* data) override;
	void delVertexBuffer(unsigned int buffer) override;
	void writeVertexBuffer(unsigned int buffer, size_t dataSize, void* offset, void* data) override;
	void copyVertexBuffer(unsigned int sourceBuffer, unsigned int targetBuffer, void* sourceOffset, void* targetOffset, size_t size) override;

	unsigned int createElementBuffer(size_t dataSize, void* data) override;
	void delElementBuffer(unsigned int buffer) override;
	void writeElementBuffer(unsigned int buffer, size_t dataSize, void* offset, void* data) override;
	void copyElementBuffer(unsigned int sourceBuffer, unsigned int targetBuffer, void* sourceOffset, void* targetOffset, size_t size) override;

private:

};