#include <GL/glew.h>
#pragma once
class Mesh
{
public:
	Mesh();

	void CreateMesh(GLfloat* verices, unsigned int vertecesSize, unsigned int* indices, unsigned int numOfIndices);
	void Render();
	void ClearMesh();

	~Mesh();

private:
	GLuint VAO_ID,VBO_ID,IBO_ID;
	// VAO_ID, id of an array of vertex objects (contains all the data of each vertex object)
	// VBO_ID, id of an array of buffer vertex objects (contains the vertex data itself)
	// IBO_ID, id of an array of indices buffer objects (contains the indices references of each vertex) 

	GLsizei indexCount;
};

