#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "OpenGL/VertexShader.h"
#include "OpenGL/FragmentShader.h"
#include "OpenGL/ShaderProgram.h"

float g_ScrollOffset = 0.0f;
void ScrollCallback(GLFWwindow* window, double xoff, double yoff);

int main()
{
	// Context creation
	GLFWwindow* window;
	if (!glfwInit())
		return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(1280, 720, "Mandelbrot Set", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		return -1;
	}

	glfwSetScrollCallback(window, ScrollCallback);

	// Shader creation
	VertexShader vertexShader("src/Shaders/MandelbrotVS.shader");
	vertexShader.Compile();

	FragmentShader fragmentShader("src/Shaders/MandelbrotFS.shader");
	fragmentShader.Compile();

	ShaderProgram shaderProgram;

	shaderProgram.Attach(vertexShader);
	shaderProgram.Attach(fragmentShader);
	shaderProgram.Link();

	// GL quad creation
	float quadVertices[18]
	{
		-1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f
	};

	GLuint VAO, VBO;
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	// Update loop
	while (!glfwWindowShouldClose(window))
	{
		float scale = g_ScrollOffset >= 0 ? g_ScrollOffset + 1 : 1 / std::abs(g_ScrollOffset);
		std::cout << scale << std::endl;
		int location = glGetUniformLocation(shaderProgram.GetID(), "zoomScale");
		glUniform1f(location, scale / 5.0f);

		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram.GetID());
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void ScrollCallback(GLFWwindow* window, double xoff, double yoff)
{
	g_ScrollOffset -= yoff;
}