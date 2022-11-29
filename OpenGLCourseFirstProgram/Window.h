#include <GL/glew.h>
#include <GLFW/glfw3.h>

#pragma once
class Window
{
public:
	
	Window();
	Window(GLint windowWidth, GLint windowHeight);

	int Init();

	GLint GetBufferWidht() { return bufferWidth; }
	GLint GetBufferHeight() { return bufferHeight; }

	bool ShouldWindowsClose() { return glfwWindowShouldClose(mainWindow); }
	void SwapBuffers() { glfwSwapBuffers(mainWindow); }

	~Window();

private:
	GLint width, height;
	GLFWwindow* mainWindow;
	int bufferWidth,bufferHeight;

};

