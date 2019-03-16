#pragma once
#include "Shader.h"

class VertexShader : public Shader
{
public:

	VertexShader(const std::string& path) :
		Shader(path, GL_VERTEX_SHADER) {}

	void Compile() const override;

};

void VertexShader::Compile() const
{
	const char* source = m_Source.c_str();
	glShaderSource(m_ID, 1, &source, nullptr);

	glCompileShader(m_ID);

	GLint success;
	GLchar log[512];

	glGetShaderiv(m_ID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(m_ID, 512, nullptr, log);
		std::cout << "VERTEX SHADER COMPILATION FAILED:\n" << log << std::endl;
	}
}