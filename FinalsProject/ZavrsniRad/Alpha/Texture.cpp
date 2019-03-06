#include "Texture.h"

Texture::~Texture()
{
	RemoveTexture();
}

bool Texture::LoadTexturePlain()
{
	bool loadSuccess = LoadTexture(PLAIN);
	return loadSuccess;
}

bool Texture::LoadTextureAlpha()
{
	bool loadSuccess = LoadTexture(ALPHA);
	return loadSuccess;
}

void Texture::UseTexture()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _textureId);
}

void Texture::RemoveTexture()
{
	glDeleteTextures(1, &_textureId);
	_textureId = 0;
	_filePath = 0;
	_width = 0;
	_height = 0;
	_bitDepth = 0;
}

// TODO redo design pattern?
bool Texture::LoadTexture(TextureType type)
{
	// stream  for loading data(1 char is 1 byte)
	unsigned char * textures = stbi_load(_filePath, &_width, &_height, &_bitDepth, 0);
	if (!textures)
	{
		std::cerr << "Could not find: " << _filePath << std::endl;
		return false;
	}

	// setting 1 texture
	glGenTextures(1, &_textureId);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	//config
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// loading  
	if (type == PLAIN)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, textures);
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textures);
	}
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(textures);

	return true;
}