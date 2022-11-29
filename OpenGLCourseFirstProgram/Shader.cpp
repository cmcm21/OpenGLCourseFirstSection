#include "Shader.h"
#include <iostream>
#include <string>

Shader::Shader(): shader_ID(0),uniformModelLocation(0)
{
}

void Shader::CreateFromString(const char* vertexCode, const char* fragmentCode)
{
	CompileShader(vertexCode, fragmentCode);
}

void Shader::CreateFromFiles(const char* vertexCodePath, const char* fragmentCodePath)
{
	std::string vertexCode = ReadFile(vertexCodePath);
	std:: string fragmentCode = ReadFile(fragmentCodePath);

	CompileShader(vertexCode.c_str(), fragmentCode.c_str());
}

GLuint Shader::GetModelLocation()
{
	return uniformModelLocation;
}

void Shader::UseShader()
{
	glUseProgram(shader_ID);
}

void Shader::ClearShader()
{
	if (shader_ID != 0)
	{
		glDeleteProgram(shader_ID);
		shader_ID = 0;
	}
}

void Shader::CompileShader(const char* vertexCode, const char* fragmentCode)
{
	shader_ID = glCreateProgram();
	if (!shader_ID)
	{
		std::cout << "Error creating program" << std::endl;
		return;
	}

	AddShader(shader_ID, vertexCode, GL_VERTEX_SHADER);
	AddShader(shader_ID, fragmentCode, GL_FRAGMENT_SHADER);
	
	DebugShaderProgram(shader_ID, false);
	DebugShaderProgram(shader_ID, true);

	glDetachShader(shader_ID, GL_VERTEX_SHADER);
	glDetachShader(shader_ID, GL_FRAGMENT_SHADER);

	uniformModelLocation = glGetUniformLocation(shader_ID, "model");
}

void Shader::AddShader(GLuint program, const char* shaderCode, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	const GLchar* code[1];
	code[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(
		shader,
		1, // the number of code sources
		code,
		codeLength
	);

	glCompileShader(shader);
	DebugShaderCompile(shader, shaderType);

	glAttachShader(program, shader);
}

void Shader::DebugShaderCompile(GLuint shader, GLenum shaderType)
{
	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(shader, sizeof(eLog), nullptr, eLog);
		std::cout << "Shader Compile " << shaderType << " Error: " << eLog << std::endl;
		delete[] eLog;
		return;
	}

	glValidateProgram(shader);
}

void Shader::DebugShaderProgram(GLuint shader, bool validation)
{
	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	GLenum typeOfDebug = validation ? GL_VALIDATE_STATUS : GL_LINK_STATUS;
	const char* errorMsg = validation ? " validation error:  " : " link error: ";

	glLinkProgram(shader);
	glGetProgramiv(shader, typeOfDebug, &result);

	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), nullptr, eLog);
		std::cout << errorMsg << eLog << std::endl;
		delete[] eLog;
		return;
	}

	glValidateProgram(shader);
}

std::string Shader::ReadFile(const char* filePath)
{
	std::string content,line = "";
	std::ifstream file(filePath);

	if (!file.is_open())
	{
		std::cout << "[Shader]::File : " << filePath << " couldn't be opened" << std::endl;
		return "";
	}

	while (!file.eof())
	{
		std::getline(file, line);
		content.append(line + "\n");
	}

	file.close();
	return content;
}

Shader::~Shader()
{
	std::cout << "================DESTROYING SHADER=============" << std::endl;
	ClearShader();
}
