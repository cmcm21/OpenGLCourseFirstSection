#include "Object_3D.h"
#include <iostream>

Object_3D::Object_3D()
{
	mesh = nullptr;
	transform = new Transform();
}


Object_3D::~Object_3D()
{
	delete transform;
	delete mesh;
	std::cout << "Destroying object 3D" << std::endl;
}

void Object_3D::SetVertices(GLfloat* vertices, unsigned int numOfVertices, unsigned int* indices, unsigned int numOfIndices)
{
	mesh = new Mesh();
	mesh->CreateMesh(vertices, numOfVertices, indices, numOfIndices);

	transform = new Transform();
}

void Object_3D::Update()
{
	transform->Reset();

	FixedUpdate();
	LateUpdate();
	mesh->Render();
}
