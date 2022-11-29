#include "Window.h"
#include <iostream>

Window::Window()
{
	width = 600;
	height = 800;
	mainWindow = nullptr;
	bufferHeight = 0;
	bufferWidth = 0;
	std::cout << "!!!!!!!!!!CREATING WINDOW!!!!!!!!!!!!!!" << std::endl;
}

Window::Window(GLint windowWidth, GLint windowHeight): 
	width(windowWidth),height(windowHeight),mainWindow(nullptr),bufferHeight(0),bufferWidth(0)
{
	std::cout << "!!!!!!!!!!CREATING WINDOW!!!!!!!!!!!!!!" << std::endl;
}

int Window::Init()
{
	if (!glfwInit())
	{
		std::cout << "GLFW initialization failed!";
		glfwTerminate();
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //core profile = no backwards compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //allow forward compatibility

	mainWindow = glfwCreateWindow(width, height, "Test Window", NULL, NULL);

	if (!mainWindow)
	{
		std::cout << "GLFW window creation failed!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
	glfwMakeContextCurrent(mainWindow);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW initialization failed!" << std::endl;
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return false;
	}

	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, bufferWidth, bufferHeight);
	return 1;
}

Window::~Window()
{
	std::cout << "!!!!!!!!!!DESTROYING WINDOW!!!!!!!!!!!!!!" << std::endl;
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}
