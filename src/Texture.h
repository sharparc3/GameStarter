#pragma once

#include <glad/glad.h>
#include <string>
#include <iostream>
#include "stb_image.h"

/**
 * @enum TextureFilterMode
 * @brief Specifies the texture filtering mode.
 */
enum class TextureFilterMode 
{
	NEAREST,		///< Nearest-neighbor filtering.
	LINEAR,			///< Linear filtering.
	MIPMAP			///< Mipmap filtering. Currently unused.
};

/**
 * @class Texture
 * @brief Manages an OpenGL texture.
 *
 * This class handles loading, binding, and setting filter modes for textures.
 */
class Texture 
{
public:
	/**
	 * @brief Constructs a Texture object and loads an image from a file.
	 * @param filePath The path to the image file.
	 */
	Texture(const std::string& filePath);

	/**
	 * @brief Default constructor for Texture.
	 */
	Texture();

	/**
	 * @brief Destructor.
	 */
	~Texture();

	/**
	 * @brief Binds the texture to a specified texture unit.
	 * @param textureUnit The texture unit to bind to (default is 0).
	 */
	void Bind(GLuint textureUnit = 0);

	/**
	 * @brief Sets the texture filtering mode.
	 * @param mode The filtering mode to set.
	 */
	void SetFilter(TextureFilterMode mode);

	/**
	 * @brief Sets the texture filtering mode using an integer.
	 * @param mode The filtering mode to set (0 for NEAREST, 1 for LINEAR).
	 */
	void SetFilter(GLint mode);

	/**
	 * @brief Gets the ID of the texture.
	 * @return The texture ID.
	 */
	GLuint GetTextureID() const;
	
	friend class Text;		///< Grants the Text class access to Texture's private members.
private:
	GLuint m_iTextureID;	///< The ID of the texture.

	/**
	 * @brief Loads an image from a file and creates an OpenGL texture.
	 * @param filePath The path to the image file.
	 */
	void LoadImage(const std::string& filePath);
};