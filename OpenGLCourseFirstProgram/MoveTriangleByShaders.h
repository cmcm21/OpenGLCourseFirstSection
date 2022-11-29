#pragma once
#include <GL/glew.h>
#include <string>

class MoveTriangleByShaders
{
public:
	float triangleOffset;
	float triangleOffsetMax;
	float triangleIncrement;
	bool direction;
	GLint uniformVarLocation;

	MoveTriangleByShaders(float maxOffset, float increment, GLuint shader, std::string variableName) :
		triangleOffset(0), triangleOffsetMax(maxOffset), triangleIncrement(increment), direction(true) 
	{
		uniformVarLocation = glGetUniformLocation(shader, variableName.c_str());
	};
	void Update();
};

