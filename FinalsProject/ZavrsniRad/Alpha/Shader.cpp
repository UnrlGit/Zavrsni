#include "Shader.h"


// TODO better name ShaderHandler?
Shader::Shader()
{
	_shaderID = 0;
	_uniformModel = 0;
	_uniformProjection = 0;
}


Shader::~Shader()
{
	ClearShader();
}

void Shader::CreateFromString(const char* vertexCode, const char* fragmentCode) {
	CompileShader(vertexCode, fragmentCode);
}

void Shader::CreateFromFiles(const char * vertexLocation, const char * fragmentLocation)
{
	std::string vertexString = ReadFile(vertexLocation);
	std::string fragmentString = ReadFile(fragmentLocation);
	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();

	CompileShader(vertexCode, fragmentCode);

}

std::string Shader::ReadFile(const char * fileLocation)
{
	std::string content;
	std::ifstream fileStream(fileLocation, std::ios::in);

	if (!fileStream.is_open())
	{
		std::cerr << "Failed to read " << fileLocation <<  std::endl;
	}

	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();
	return content;

}

GLuint Shader::GetProjectionLocation()
{
	return _uniformProjection;
}

GLuint Shader::GetModelLocation()
{
	return _uniformModel;
}

GLuint Shader::GetViewLocation()
{
	return _uniformView;;
}

GLuint Shader::GetAmbientIntensityLocation()
{
	return _uniformDirectionalLight.uniformAmbientIntensity;
}

GLuint Shader::GetAmbientColourLocation()
{
	return _uniformDirectionalLight.uniformColour;
}

GLuint Shader::GetDiffuseIntensityLocation()
{
	return _uniformDirectionalLight.uniformDiffuseIntensity;
}

GLuint Shader::GetDirectionLocation()
{
	return _uniformDirectionalLight.uniformDirection;
}

GLuint Shader::GetSpecularIntensityLocation()
{
	return _uniformSpecularIntensity;
}

GLuint Shader::GetSpecularPowerLocation()
{
	return _uniformSpecularPower;
}

GLuint Shader::GetEyePositionLocation()
{
	return _uniformEyePosition;
}

void Shader::SetDirectionalLight(DirectionalLight * dirLight)
{
	dirLight->UseLight(_uniformDirectionalLight.uniformAmbientIntensity, _uniformDirectionalLight.uniformColour,
		_uniformDirectionalLight.uniformDiffuseIntensity, _uniformDirectionalLight.uniformDirection);
}


void Shader::UseShader()
{
	if (_shaderID != 0)
	{
		glUseProgram(_shaderID);
	}
	else
	{
		printf("Error, no shader");
	}

}

void Shader::ClearShader()
{
	if (_shaderID != 0)
	{
		glDeleteProgram(_shaderID);
		_shaderID = 0;
	}

	_uniformModel = 0;
	_uniformProjection = 0;
}

void Shader::CompileShader(const char * vertexCode, const char * fragmentCode)
{
	_shaderID = glCreateProgram();

	if (!_shaderID)
	{
		std::cerr <<"Error creating shader program!" << std::endl;
		return;
	}

	AddShader(_shaderID, vertexCode, GL_VERTEX_SHADER);
	AddShader(_shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	//getting error codes
	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(_shaderID);
	glGetProgramiv(_shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(_shaderID, sizeof(eLog), NULL, eLog);
		std::cerr << "Error linking program:" << eLog << std::endl;
		return;
	}

	glValidateProgram(_shaderID);
	glGetProgramiv(_shaderID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(_shaderID, sizeof(eLog), NULL, eLog);
		std::cerr << "Error validating program:" << eLog << std::endl;
		return;
	}


	// CODING UNIFORM VARIABLES
	_uniformProjection = glGetUniformLocation(_shaderID, "projection");
	_uniformModel = glGetUniformLocation(_shaderID, "model");
	_uniformView = glGetUniformLocation(_shaderID, "view");
	_uniformDirectionalLight.uniformColour = glGetUniformLocation(_shaderID, "directionalLight.base.colour");
	_uniformDirectionalLight.uniformAmbientIntensity = glGetUniformLocation(_shaderID, "directionalLight.base.ambientIntensity");
	_uniformDirectionalLight.uniformDirection = glGetUniformLocation(_shaderID, "directionalLight.direction");
	_uniformDirectionalLight.uniformDiffuseIntensity = glGetUniformLocation(_shaderID, "directionalLight.base.diffuseIntensity");
	_uniformSpecularIntensity = glGetUniformLocation(_shaderID, "material.specularIntensity");
	_uniformSpecularPower = glGetUniformLocation(_shaderID, "material.shininess");
	_uniformEyePosition = glGetUniformLocation(_shaderID, "eyePosition");

}

void Shader::AddShader(GLuint theProgram, const char * shaderCode, GLenum shaderType)
{
	//empty shader
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);
	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);


	GLint result = 0;
	GLchar eLog[1024] = { 0 };


	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		std::cerr << "Error compiling " << shaderType << ": " << eLog << std::endl;
		return;
	}

	glAttachShader(theProgram, theShader);
	return;
}
