#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL\glew.h>

#include "StbImage.h"
#include <iostream>
class Texture
{
public:
	Texture()
		:_filePath(""), _textureId(0), _width(0), _height(0), _bitDepth(0) {}
	Texture(const char *filePath)
		:_filePath(filePath), _textureId(0), _width(0), _height(0), _bitDepth(0) {
		// TODO test and rmove this and iostream
		std::cout << filePath << std::endl;
	}
	~Texture();

	bool LoadTexturePlain();
	bool LoadTextureAlpha();
	void UseTexture();
	void RemoveTexture();

private:
	enum TextureType
	{
		PLAIN,
		ALPHA
	};

	const char * _filePath;

	GLuint _textureId;
	int _width;
	int _height;
	int _bitDepth;

	bool LoadTexture(TextureType type);
};
#endif // !TEXTURE_H