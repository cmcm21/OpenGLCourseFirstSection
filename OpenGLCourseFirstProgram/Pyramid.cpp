#include "Pyramid.h"
#include <iostream>

Pyramid::Pyramid():
	shouldMove(false),shouldRotate(false),shouldScaling(false),
	speed(0),maxOffset(0),minSize(0),maxSize(0),move(0,0,0),rotation(0,0,0),scaleAxes(0,0,0)
{
	//in which order the vertices will be drawn
	//the order in which each traingle's vertex is placed doesn't matter
	unsigned int indices[] = {
		3,0,1, // right triangle of the pyramid = 1,3,0, 3,1,0, ...etc
		1,3,2, // left trangle of the pyramid = 1,2,3, ...etc	
		0,3,2, // front triangle of the pyramid = 2, 3, 0, ... etc
		2,1,0, // base triangle of the pyramid = 2,0,1,...etc
	};
	//pyramid vertices 
	GLfloat vertices[] = {
		-1.0f, -1.0f,0.0f, // vertex left bottom vertex index = 0
		0.0f, -1.0f, 1.0f, // vertex depth vertex index = 1
		1.0f, -1.0f, 0.0f, // vertex right bottom vertex index = 2
		0.0f, 1.0f, 0.0f  // vertex up  vertex index = 3
	};

	SetVertices(vertices, 12, indices, 12);
}

Pyramid::~Pyramid()
{
}

void Pyramid::Translate(float speed, float maxOffset, glm::vec3 move)
{
	this->shouldMove = true;
	this->speed = speed;
	this->maxOffset = maxOffset;
	this->move = move;
}

void Pyramid::Rotate(glm::vec3 rotation)
{
	shouldRotate = true;
	this->rotation = rotation;
}

void Pyramid::Scale(float minSizeI, float maxSize, glm::vec3 scaleAxes)
{
	shouldScaling = true;

	this->minSize = minSizeI;
	this->maxSize = maxSize;
	this->scaleAxes = scaleAxes;
}

void Pyramid::FixedUpdate()
{
	if (shouldMove)
		transform->Translate(speed, maxOffset, move);

	if (shouldRotate)
		transform->Rotate(rotation);

	if (shouldScaling)
		transform->Scale(minSize, maxSize, scaleAxes);
}
