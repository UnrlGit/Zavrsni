#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <iostream>
#include <fstream>

#include <GL\glew.h>

#include "DirectionalLight.h"

class Shader
{
public:
	Shader();
	~Shader();

	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);

	std::string ReadFile(const char* fileLocation);

	GLuint GetProjectionLocation();
	GLuint GetModelLocation();
	GLuint GetViewLocation();
	GLuint GetAmbientIntensityLocation();
	GLuint GetAmbientColourLocation();
	GLuint GetDiffuseIntensityLocation();
	GLuint GetDirectionLocation();
	GLuint GetSpecularIntensityLocation();
	GLuint GetSpecularPowerLocation();
	GLuint GetEyePositionLocation();

	void SetDirectionalLight(DirectionalLight * dirLight);

	void UseShader();
	void ClearShader();

private:
	GLuint _shaderID;
	GLuint _uniformProjection;
	GLuint _uniformModel;
	GLuint _uniformView;
	GLuint _uniformEyePosition;
	GLuint _uniformSpecularIntensity;
	GLuint _uniformSpecularPower;

	//this is an instance of struct (I can use uniformDirectionalLight.something)
	struct {
		GLuint uniformColour;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformDirection;
	} _uniformDirectionalLight;

	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};
#endif // !SHADER_H