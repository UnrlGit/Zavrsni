#ifndef SKYBOX_H
#define SKYBOX_H

#include <vector>
#include <string>

#include <GL\glew.h>

#include <GLM\glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>
#include <GLM\gtc\type_ptr.hpp>

#include "StbImage.h"

#include "Mesh.h"
#include "Shader.h"

class Skybox
{
public:
	Skybox();

	Skybox(std::vector<std::string> faceLocations);
	void RenderSkybox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

	~Skybox();


private:
	Mesh * _skyboxMesh;
	Shader * _skyboxShader;

	GLuint _textureId;
	GLuint _uniformProjection;
	GLuint _uniformView;
};
#endif // !SKYBOX_H
