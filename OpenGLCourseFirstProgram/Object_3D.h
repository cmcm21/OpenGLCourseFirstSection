#include "Mesh.h"
#include "Transform.h"
#include "Shader.h"

#pragma once
class Object_3D
{
public:
	Object_3D();
	virtual ~Object_3D();

	void Update();
	glm::mat4 GetModel() { return transform->GetModel(); }

protected:
	Transform *transform;
	Mesh *mesh;

	virtual void FixedUpdate(){};
	virtual void LateUpdate(){};
	virtual void SetVertices(GLfloat *vertices, unsigned int numOfVertices, unsigned int *indices, unsigned int numOfIndices);
};

