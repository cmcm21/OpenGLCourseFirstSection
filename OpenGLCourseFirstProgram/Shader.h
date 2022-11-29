#include <GL/glew.h>
#include <fstream>

#pragma once
class Shader
{
public:
	Shader();

	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFiles(const char* vertextCodePath, const char* fragmentCodePath);

	GLuint GetShaderID() { return shader_ID; }
	GLuint GetModelLocation();

	void UseShader();
	void ClearShader();

	~Shader();

private:
	GLuint shader_ID, uniformModelLocation;

	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint program, const char* shaderCode, GLenum shaderType);
	void DebugShaderCompile(GLuint shader, GLenum shaderType);
	void DebugShaderProgram(GLuint shader, bool validation);
	std::string ReadFile(const char* filePath);
};

