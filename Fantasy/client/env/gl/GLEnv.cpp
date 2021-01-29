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


//���ÿ���̨
//#pragma comment( linker, "/subsystem:windows /entry:mainCRTStartup" )

static GLEnv* env;
static glm::ivec2 windowSize;

#ifdef __ANDROID__
static GLFMDisplay *mDisplay;

#else
static GLFWwindow* window;

void framebuffer_size_callback(GLFWwindow* window,int width,int height) {
	glViewport(0, 0, width, height);
	windowSize.x = width;
	windowSize.y = height;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	env->getInput()->sendKeyEvent(key, mods, action);
}

void closeCallback(GLFWwindow* window)
{
	env->exit();
}
#endif

GLEnv::GLEnv():Environment()
{
}

GLEnv::~GLEnv()
{
}

bool GLEnv::setup(void *args)
{
	env = this;

#ifdef __ANDROID__
    mDisplay= (GLFMDisplay *)(args);

#else
    glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(1600, 800, "Fantasy", NULL, NULL);
	//glfwSetWindowIcon(window, 1, );
	if (window == NULL)
	{
		LOG_E("Failed to create GLFW window");
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetWindowCloseCallback(window, closeCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LOG_E("Failed to initialize GLAD");
		return false;
	}
#endif
	return true;
}

void GLEnv::cleanup()
{
#ifdef __ANDROID__

#else
    glfwTerminate();
#endif
}

void GLEnv::windowResize(int width, int height) {
	windowSize={width,height};
	glViewport(0, 0, width, height);
}

int GLEnv::getWindowWidth()
{
	return windowSize.x;
}

int GLEnv::getWindowHeight()
{
	return windowSize.y;
}

void GLEnv::renderStart()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void GLEnv::renderEnd()
{
#ifdef __ANDROID__
    glfmSwapBuffers(mDisplay);
#else
    glfwPollEvents();
	glfwSwapBuffers(window);
#endif
}

unsigned int GLEnv::createShader(std::string vertexShader, std::string fragmentShader)
{
	const int logMaxLen = 1024;
	const char *vsc = vertexShader.c_str();
	const char *fsc = fragmentShader.c_str();

	//���붥����ɫ��
	unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vsc, NULL);
	glCompileShader(vs);
	int success;
	char infoLog[logMaxLen];
	glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vs, logMaxLen, NULL, infoLog);
		LOG_E("Env", "VertexShaderCompileError\n" + std::string(infoLog));
		return 0;
	}

	//����Ƭ����ɫ��
	unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fsc, NULL);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fs, logMaxLen, NULL, infoLog);
		LOG_E("Env", "FragmentShaderCompileError\n" + std::string(infoLog));
		return 0;
	}

	//������ɫ������
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

void GLEnv::useShader(unsigned int shader)
{
	glUseProgram(shader);
}

void GLEnv::delShader(unsigned int shader)
{
	glDeleteProgram(shader);
}

unsigned int GLEnv::createObject()
{
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	return VAO;
}

void GLEnv::delObject(unsigned int obj)
{
	glDeleteVertexArrays(1, &obj);
}

void GLEnv::objBindBuffer(unsigned int obj, unsigned int vertexBuffer, unsigned int elementBuffer)
{
	glBindVertexArray(obj);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glBindVertexArray(0);
}

void GLEnv::objSetVertexLayout(unsigned int obj, unsigned int location, unsigned int num, Env::AttribType::Enum type, size_t stride, void* offset, bool normalize)
{
	unsigned int glType = 0;
	switch (type)
	{
	case Env::AttribType::Float:
		glType = GL_FLOAT;
		break;
	default:
		LOG_E("Env", "AttribType Error, location " + i2s(location));
		return;
		break;
	}

	glBindVertexArray(obj);
	glVertexAttribPointer(location, num, glType, normalize, stride, offset);
	glEnableVertexAttribArray(location);
	glBindVertexArray(0);
}

void GLEnv::drawObject(unsigned int obj, unsigned int count, Env::DrawType::Enum type)
{
	unsigned int glType = 0;
	switch (type)
	{
	case Env::DrawType::Point:
		glType = GL_POINTS;
		break;
	case Env::DrawType::Line:
		glType = GL_LINES;
		break;
	case Env::DrawType::LineStrip:
		glType = GL_LINE_STRIP;
		break;
	case Env::DrawType::LineLoop:
		glType = GL_LINE_LOOP;
		break;
	case Env::DrawType::Triangle:
		glType = GL_TRIANGLES;
		break;
	case Env::DrawType::TriangleStrip:
		glType = GL_TRIANGLE_STRIP;
		break;
	case Env::DrawType::TriangleFan:
		glType = GL_TRIANGLE_FAN;
		break;
	default:
		LOG_E("Env", "DrawType Error ");
		return;
		break;
	}
	glBindVertexArray(obj);
	glDrawElements(glType, count, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

unsigned int GLEnv::createVertexBuffer(size_t dataSize, void * data)
{
	unsigned int buffer = 0;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return buffer;
}

void GLEnv::delVertexBuffer(unsigned int buffer)
{
	glDeleteBuffers(1, &buffer);
}

void GLEnv::writeVertexBuffer(unsigned int buffer, size_t dataSize, void* offset, void * data)
{
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferSubData(GL_ARRAY_BUFFER, (GLintptr)offset, dataSize, data);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GLEnv::copyVertexBuffer(unsigned int sourceBuffer, unsigned int targetBuffer, void * sourceOffset, void * targetOffset, size_t size)
{
	glBindBuffer(GL_COPY_WRITE_BUFFER, targetBuffer);
	glBindBuffer(GL_COPY_READ_BUFFER, sourceBuffer);
	glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, (GLintptr)sourceOffset, (GLintptr)targetOffset, size);
	glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
	glBindBuffer(GL_COPY_READ_BUFFER, 0);
}

unsigned int GLEnv::createElementBuffer(size_t dataSize, void * data)
{
	unsigned int buffer = 0;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	return buffer;
}

void GLEnv::delElementBuffer(unsigned int buffer)
{
	glDeleteBuffers(1, &buffer);
}

void GLEnv::writeElementBuffer(unsigned int buffer, size_t dataSize, void* offset, void * data)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, (GLintptr)offset, dataSize, data);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GLEnv::copyElementBuffer(unsigned int sourceBuffer, unsigned int targetBuffer, void * sourceOffset, void * targetOffset, size_t size)
{
	glBindBuffer(GL_COPY_WRITE_BUFFER, targetBuffer);
	glBindBuffer(GL_COPY_READ_BUFFER, sourceBuffer);
	glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, (GLintptr)sourceOffset, (GLintptr)targetOffset, size);
	glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
	glBindBuffer(GL_COPY_READ_BUFFER, 0);
}

