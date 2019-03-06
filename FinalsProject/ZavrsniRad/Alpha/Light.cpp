#include "Light.h"


Light::Light()
{
	_colour = glm::vec3(1.0f, 1.0f, 1.0f);
	_ambientIntensity = 1.0f;
	_diffuseIntensity = 0.0f;
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity)
{
	_colour = glm::vec3(red, green, blue);
	_ambientIntensity = aIntensity;
	_diffuseIntensity = dIntensity;
}


Light::~Light()
{
}

