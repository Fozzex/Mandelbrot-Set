#include "Shader.h"

Shader::Shader(const std::string& path, GLenum shaderType)
{
	try
	{
		std::ifstream file(path);
		file.exceptions(std::ios::badbit | std::ios::failbit);

		std::stringstream ssSource;
		ssSource << file.rdbuf();

		m_Source = ssSource.str();
	}
	catch(std::fstream::failure e)
	{
		std::cout << e.what() << std::endl;
	}

	m_ID = glCreateShader(shaderType);
}

Shader::~Shader()
{
	glDeleteShader(m_ID);
}