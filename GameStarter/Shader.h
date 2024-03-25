#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	~Shader();

	void Compile(const std::string& vertexSource, const std::string& fragmentSource);
	void Use();
	GLuint GetProgramID() const;

private:
	GLuint m_iProgramId;

	std::string ReadShaderFile(const std::string& filePath);
	void CheckCompileErrors(GLuint shader, GLenum shaderType);
};