#include "Material.h"

void Material::UseMaterial(GLuint specularIntensityLocation, GLuint specularPowerLocation)
{
	// setting shader uniforms
	glUniform1f(specularIntensityLocation, _specularIntensity);
	glUniform1f(specularPowerLocation, _specularPower);
}
