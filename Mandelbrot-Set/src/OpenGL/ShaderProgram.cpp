#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
{
	m_ID = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_ID);
}

void ShaderProgram::Attach(const Shader& shader) const
{
	glAttachShader(m_ID, shader.GetID());
}

void ShaderProgram::Link() const
{
	glLinkProgram(m_ID);

	GLint success;
	GLchar log[512];

	glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_ID, 512, nullptr, log);
		std::cout << "SHADER PROGRAM LINKING FAILED:\n" << log << std::endl;
	}
}