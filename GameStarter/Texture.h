#pragma once

#include <glad/glad.h>
#include <string>
#include <iostream>
#include "stb_image.h"

enum class TextureFilterMode 
{
	NEAREST,
	LINEAR,
	MIPMAP
};

class Texture 
{
public:
	Texture(const std::string& filePath);
	~Texture();

	void Bind(GLuint textureUnit = 0);
	void SetFilter(TextureFilterMode mode);
	GLuint GetTextureID() const;

private:
	GLuint m_iTextureID;

	void LoadImage(const std::string& filePath);
};