#ifndef LIGHT_H
#define LIGHT_H

#include <GL\glew.h>
#include <GLM\glm.hpp>
class Light
{
public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue,
		GLfloat aIntensity, GLfloat dIntensity);
	~Light();

protected:
	glm::vec3 _colour;
	GLfloat _ambientIntensity;
	GLfloat _diffuseIntensity;
};

#endif // !LIGHT_H