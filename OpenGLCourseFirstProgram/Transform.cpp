#include "Transform.h"
#include <cmath>
#include <iostream>

void Transform::Reset()
{
	model = glm::mat4(1.0f);
}

void Transform::Translate(float speed, float maxOffset, glm::vec3 translation)
{
	if (translateDirection)
		triangleMove += speed;
	else
		triangleMove -= speed;
	if (abs(triangleMove) >= maxOffset)
		translateDirection = !translateDirection;

	translation.x += triangleMove;

	model = glm::translate(model,translation);// apply translation of triangle move to model;
}

void Transform::Rotate(glm::vec3 rotation)
{
	rotationAngle += 0.01f;
	if (rotationAngle >= 360)
		rotationAngle -= 360;

	model = glm::rotate(model, rotationAngle * toRadians, rotation);
}

void Transform::Scale(float minSize, float maxSize, glm::vec3 scale)
{
	if (sizeDirection)
		scaleSize += 0.0001f;
	else
		scaleSize -= 0.0001f;

	if (scaleSize >= maxSize || scaleSize <= minSize)
		sizeDirection = !sizeDirection;

	scale = glm::normalize(scale);

	glm::vec3 curScale = glm::vec3(scaleSize, scaleSize, scaleSize);
	model = glm::scale(model, scale + curScale);
}

glm::mat4 Transform::GetModel()
{
	return model;
}

