#include "Mesh.h"
#include <iostream>

Mesh::Mesh()
{
	VAO_ID = 0;
	VBO_ID = 0;
	IBO_ID = 0;

	indexCount = 0;
}

void Mesh::CreateMesh(GLfloat* vertices, unsigned int verticesSize, unsigned int* indices, unsigned int numOfIndices)
{
	indexCount = numOfIndices;
	glGenVertexArrays(1, &VAO_ID); // create 1 vertex array in the graphic card with the id VAO_ID
	glBindVertexArray(VAO_ID);

	glGenBuffers(1, &IBO_ID); // create 1 indices buffer array in the graphic car iwht the id IBO_ID
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices, indices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO_ID); //create 1 vertex buffer array in the graphic car with the id VBO_ID
	glBindBuffer(GL_ARRAY_BUFFER, VBO_ID);
	//Static draw: We don't change theese values, the trinagle won't move on screen (per frame)
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * verticesSize, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(
		0, // index of the pointer
		3, // who many values has the data
		GL_FLOAT,// data type
		GL_FALSE, // normilize?
		0, // how many skips? you could have vertices with color, in this case you should skip the color values
		0 // offset, where this data start in the array. it helps with larger objects.
	);

	glEnableVertexAttribArray(0);//enable the index where the vertex atribute are, basicaly, the same index from glVertexAttribPointer we acces to this atributes in the vetex shader, where we put layout(loaction = 0) in vec3 position

	//unbind VAO and VBO, bind an object to id 0 is equal to set a variable equal to null(Array=nullptr)
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::Render()
{
	glBindVertexArray(VAO_ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IBO_ID);
	//glDrawArrays(GL_TRIANGLES,
	//	0, // where in the array should starts?
	//	3 // amount of points to draw
	//);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0); // restart Vertex array in graphic card
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::ClearMesh()
{
	if (IBO_ID != 0)
	{
		glDeleteBuffers(1, &IBO_ID);
		IBO_ID = 0;
	}

	if (VBO_ID != 0)
	{
		glDeleteBuffers(1, &VBO_ID);
		VBO_ID = 0;
	}

	if (VAO_ID != 0)
	{
		glDeleteVertexArrays(1, &VAO_ID);
		VAO_ID = 0;
	}

	indexCount = 0;
}

Mesh::~Mesh()
{
	std::cout << "+++++++++DESTROYING MESH+++++++++" << std::endl;
	ClearMesh();
}
