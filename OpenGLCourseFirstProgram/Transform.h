#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <string>


class Transform
{
public:

	Transform():
		triangleMove(0),translateDirection(true),
		rotationAngle(0.0f),scaleSize(0.4f),sizeDirection(true)
	{
		model = glm::mat4(1.0f);
	};

	void Reset();
	void Translate(float speed, float maxOffset, glm::vec3 translation);
	void Rotate(glm::vec3 rotation);
	void Scale(float minSize, float maxSize, glm::vec3 scale);
	glm::mat4 GetModel();

private:
	float triangleMove;
	bool translateDirection;

	float rotationAngle;
	float scaleSize;
	bool sizeDirection;

	const float toRadians = 3.1415926535f / 180.0f;
	glm::mat4 model;
};

