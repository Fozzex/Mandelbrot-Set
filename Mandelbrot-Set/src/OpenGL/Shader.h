#pragma once
#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:

	Shader(const std::string& path, GLenum shaderType);
	virtual ~Shader();

	virtual void Compile() const = 0;

	inline GLuint GetID() const { return m_ID; }

protected:

	GLuint m_ID;
	std::string m_Source;

};