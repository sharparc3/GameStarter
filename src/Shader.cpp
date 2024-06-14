#include "Shader.h"
#include <vector>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
	m_uniformNames.push_back("u_mvpMatrix");
	m_uniformNames.push_back("currentFrame");
	m_uniformNames.push_back("frameCount");

	std::string vertexSource = ReadShaderFile(vertexPath);
	std::string fragmentSource = ReadShaderFile(fragmentPath);
	Compile(vertexSource, fragmentSource);
}

Shader::~Shader()
{
	glDeleteProgram(m_iProgramId);
}

void Shader::Compile(const std::string& vertexSource, const std::string& fragmentSource)
{
	// Create vertex and fragment shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Set vertex shader source code
	const GLchar* vertexSourceCode = vertexSource.c_str();
	glShaderSource(vertexShader, 1, &vertexSourceCode, NULL);
	// Compile vertex shader
	glCompileShader(vertexShader);
	// Check for vertex shader compilation errors
	CheckCompileErrors(vertexShader, GL_VERTEX_SHADER);

	// Set fragment shader source code
	const GLchar* fragmentSourceCode = fragmentSource.c_str();
	glShaderSource(fragmentShader, 1, &fragmentSourceCode, NULL);
	// Compile fragment shader
	glCompileShader(fragmentShader);
	// Check for fragment shader compilation errors
	CheckCompileErrors(fragmentShader, GL_FRAGMENT_SHADER);

	// Create shader program
	m_iProgramId = glCreateProgram();
	// Attach compiled shaders to the program
	glAttachShader(m_iProgramId, vertexShader);
	glAttachShader(m_iProgramId, fragmentShader);

	// Link the shader program
	glLinkProgram(m_iProgramId);

	// Check for shader linking errors 
	GLint isLinked = 0;
	glGetProgramiv(m_iProgramId, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(m_iProgramId, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(m_iProgramId, maxLength, &maxLength, &infoLog[0]);

		// Print or log the shader linker errors 
		std::cerr << "Shader linking failed: " << &infoLog[0] << std::endl;

		glDeleteProgram(m_iProgramId);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		return;
	}
	else
	{
		glUseProgram(m_iProgramId);

		// get uniforms location
		for (const auto& it : m_uniformNames)
		{
			m_uniformLocations[it.c_str()] = glGetUniformLocation(m_iProgramId, it.c_str());
		}

		glUseProgram(0);
		// Delete the vertex and fragment shaders after linking (if successful)
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}


}

void Shader::Use()
{
	glUseProgram(m_iProgramId);
}

GLuint Shader::GetProgramID() const
{
	return m_iProgramId;
}

std::string Shader::ReadShaderFile(const std::string& filePath)
{
	std::string content;
	std::ifstream fileStream(filePath);

	if (!fileStream.is_open()) 
	{
		std::cerr << "ERROR: Failed to read shader file: " << filePath << std::endl;
		return "";
	}

	std::stringstream shaderStream;
	shaderStream << fileStream.rdbuf();
	content = shaderStream.str();

	fileStream.close();
	return content;
}

void Shader::CheckCompileErrors(GLuint shader, GLenum shaderType)
{
	GLint compileStatus;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
	if (!compileStatus) 
	{
		GLchar infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cerr << "ERROR: shader compilation failed: " << shaderType << "\n" << infoLog << std::endl;
	}
}
