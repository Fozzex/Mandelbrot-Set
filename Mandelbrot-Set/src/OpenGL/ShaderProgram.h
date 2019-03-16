#pragma once
#include "Shader.h"

class ShaderProgram
{
public:

	ShaderProgram();
	~ShaderProgram();

	void Attach(const Shader& shader) const;
	void Link() const;

	inline GLuint GetID() const { return m_ID; }

private:

	GLuint m_ID;

};