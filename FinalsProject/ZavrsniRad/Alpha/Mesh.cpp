#include "Mesh.h"


Mesh::~Mesh()
{
	ClearMesh();
}

void Mesh::CreateMesh(GLfloat * vertices, unsigned int * indicies, unsigned int numOfVertices, unsigned int numOfIndicies)
{
	_indexCount = numOfIndicies;

	// creating array (1) on  graphics card, _vao id is for accessingg it, binding it to graphics card
	// basically creates space on graphics card and gets id for accessing
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	// stores indicies on graphics card
	glGenBuffers(1, &_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies[0])* numOfIndicies, indicies, GL_STATIC_DRAW);
	// stores vertices on graphics card
	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(indicies[0])* numOfVertices, vertices, GL_STATIC_DRAW);

	// CONNECTING TO SHADERS AND ENABLING, values in order are:
	// (layout in shader, number of values used, type, normalization, stride (after how many values it reappears), starting offset)
	//shader (layout = 0), xyz values
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, 0);
	glEnableVertexAttribArray(0);
	//shader (layout = 1) uv values
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 3));
	glEnableVertexAttribArray(1);
	//shader (layout = 2) nx, ny, nz values
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 5));
	glEnableVertexAttribArray(2);

	// unbinding, removing from graphics card
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::RenderMesh()
{
	// connecting to data and drawing it
	glBindVertexArray(_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
	// TODO 0 instead of nullptr
	glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_INT, nullptr);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Mesh::ClearMesh()
{
	if (_ibo != 0)
	{
		glDeleteBuffers(1, &_ibo);
		_ibo = 0;
	}

	if (_vbo != 0)
	{
		glDeleteBuffers(1, &_vbo);
		_vbo = 0;
	}
	if (_vao != 0)
	{
		glDeleteVertexArrays(1, &_vao);
		_vao = 0;
	}


	_indexCount = 0;
}
