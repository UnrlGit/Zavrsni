#ifndef MATERIAL_H
#define MATERIAL_H

#include <GL\glew.h>

class Material
{
public:
	Material()
		: _specularIntensity(0.0f), _specularPower(0.0f) {}
	Material(GLfloat specularIntensity, GLfloat specularPower)
		:_specularIntensity(specularIntensity), _specularPower(_specularPower) {}
	~Material() {}

	void UseMaterial(GLuint specularIntensityLocation, GLuint specularPowerLocation);

private:
	// light absorption
	GLfloat _specularIntensity;
	// how smooth
	GLfloat _specularPower;
};

#endif // !MATERIAL_H