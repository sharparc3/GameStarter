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
	Texture();
	~Texture();

	void Bind(GLuint textureUnit = 0);
	void SetFilter(TextureFilterMode mode);

	// 0 - NEAREST
	// 1 - LINEAR
	void SetFilter(GLint mode);
	GLuint GetTextureID() const;
	
	friend class Text;
private:
	GLuint m_iTextureID;

	void LoadImage(const std::string& filePath);
};