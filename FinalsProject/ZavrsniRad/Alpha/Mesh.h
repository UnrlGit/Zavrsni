#ifndef MESH_H
#define MESH_H

#include <GL\glew.h>
class Mesh
{
public:
	Mesh()
		:_vao(0), _vbo(0), _ibo(0), _indexCount(0) {}
	~Mesh();

	void CreateMesh(GLfloat *vertices, unsigned int *indicies, unsigned int numOfVertices, unsigned int numOfIndicies);
	void RenderMesh();
	void ClearMesh();

private:
	// id(s)
	GLuint _vao;
	GLuint _vbo;
	GLuint _ibo;

	GLsizei _indexCount;
};

#endif ! // MESH_H