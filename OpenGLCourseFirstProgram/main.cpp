#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/vec4.hpp>
#include <vector>

#include "Shader.h"
#include "Window.h"
#include "Camera.h"
#include "Pyramid.h"

struct MainContext{
	
	Window* window;
	Camera* camera;
	Shader* shader;
	std::vector<Object_3D*> objects;

	MainContext(Window *window, Camera *camera,Shader *shader):window(window),camera(camera),shader(shader){};
	~MainContext() { 
		delete window; 
		delete camera; 
		delete shader;

		for (auto object : objects)
			delete object;
	}
};

//Windows dimensions
const GLint WIDTH = 800, HEIGHT = 600;
const char* vertexCodePath = "./Shaders/VertexShader.hlsl";
const char* fragmentCodePath = "./Shaders/FragmentShader.hlsl";

void MainLoop(MainContext *context);
Shader* CreateShader();
MainContext *CreateContext();
std::vector<Object_3D*> CreateObjects();

int main()
{
	MainLoop(CreateContext());
	return 0;
}

Shader* CreateShader()
{
	Shader* shader = new Shader();
	//shader->CreateFromString(OpenGLManager::GetVertexShader(), OpenGLManager::GetFragmentShader());
	shader->CreateFromFiles(vertexCodePath, fragmentCodePath);
	return shader;
}

void MainLoop(MainContext *context)
{
	if (context == nullptr) return;

	while (!context->window->ShouldWindowsClose())
	{
		//get + handle user input events
		glfwPollEvents();

		//clear Window with a color
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		//clear de buffer of color bits, there are a lot of information of each pixel, and we need
		//to specify what we want to clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		context->shader->UseShader();

		for (auto object : context->objects) {
			glUniformMatrix4fv(context->shader->GetModelLocation(), 1, GL_FALSE, glm::value_ptr(object->GetModel()));
			object->Update();
		}

		context->camera->Update();

		glUseProgram(0);
		//swap the buffer where we were paiting to the main window
		context->window->SwapBuffers();
	}

	delete context;
}

MainContext* CreateContext()
{
	Window *window = new Window(WIDTH, HEIGHT);
	if (window->Init() != 1)
		return nullptr;

	ProjectionArgs projArgs(
		45.0f,
		(GLfloat)window->GetBufferWidht() / (GLfloat)window->GetBufferHeight(),
		0.1f,
		100.0f
	);

	Camera *camera = new Camera();
	Shader* shader = CreateShader();

	GLuint shaderID = shader->GetShaderID();
	camera->SetProjection(shaderID,projArgs);

	MainContext *context = new MainContext(window, camera, shader);
	context->objects = CreateObjects();

	return context;
}

std::vector<Object_3D*> CreateObjects()
{
	std::vector<Object_3D*> objects;
	Pyramid* pyramid = new Pyramid();
	Pyramid* pyramid2 = new Pyramid();

	pyramid->Translate(0.0005f, 0.7f, glm::vec3(0, -0.5,-2.5));
	pyramid2->Translate(-0.0005f, 0.7f, glm::vec3(0, 0.5, -2.5));

	pyramid->Rotate(glm::vec3(0, 1, 0));
	pyramid2->Rotate(glm::vec3(0, 1, 0));

	objects.emplace_back(pyramid);
	objects.emplace_back(pyramid2);


	return objects;
}
