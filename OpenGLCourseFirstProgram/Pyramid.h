#pragma once
#include "Object_3D.h"
class Pyramid : public Object_3D
{
public:
	Pyramid();
	virtual ~Pyramid();

	void Translate(float speed, float maxOffset, glm::vec3 move);
	void Rotate(glm::vec3 roation);
	void Scale(float minSize, float maxSize,glm::vec3 scaleAxes);

private:
	bool shouldMove;
	bool shouldRotate;
	bool shouldScaling;

	float speed,maxOffset,minSize,maxSize;
	glm::vec3 move;
	glm::vec3 rotation;
	glm::vec3 scaleAxes;

protected:
	void FixedUpdate();
};

