#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

/**
 * @class Shader
 * @brief Manages the compilation and usage of OpenGL shaders.
 *
 * This class handles the loading, compiling, and management of program created from compiled vertex and fragment shader.
 */
class Shader
{
public:
	/**
	 * @brief Constructs a Shader object from vertex and fragment shader file paths.
	 * @param vertexPath The path to the vertex shader file.
	 * @param fragmentPath The path to the fragment shader file.
	 */
	Shader(const std::string& vertexPath, const std::string& fragmentPath);

	/**
	 * @brief Destructor.
	 */
	~Shader();

	/**
	 * @brief Activates the shader program for use in rendering.
	 */
	void Use();

	/**
	 * @brief Gets the ID of the shader program. Currently unused.
	 * @return The shader program ID.
	 */
	GLuint GetProgramID() const;

public:
	std::map<std::string, GLint> m_uniformLocations;	///< Locations of uniform variables in the shader.

private:
	GLuint m_iProgramId;	///< The shader program ID (after both compile vertex and fragment shader).
	std::vector<std::string> m_uniformNames;		///< Contains all names of uniform variables in every shader.

	/**
	 * @brief Compiles the vertex and fragment shaders from source code.
	 * @param vertexSource The source code of the vertex shader.
	 * @param fragmentSource The source code of the fragment shader.
	 */
	void Compile(const std::string& vertexSource, const std::string& fragmentSource);

	/**
	 * @brief Reads the contents of a shader file.
	 * @param filePath The path to the shader file.
	 * @return The contents of the shader file.
	 */
	std::string ReadShaderFile(const std::string& filePath);

	/**
	 * @brief Checks for compile errors in a shader.
	 * @param shader The shader to check.
	 * @param shaderType The type of the shader (vertex or fragment).
	 */
	void CheckCompileErrors(GLuint shader, GLenum shaderType);
};