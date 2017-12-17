#include <iostream>

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

const GLint WIDTH = 800, HEIGHT = 600;

int main()
{
	glfwInit();

	//Setting the version of GLFW to 3.3, will fallback if this fails.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//Choosing the profile for open GL, Core uses the current new stuff, Compat_Profile uses a lot of old stuff to keep stuff... well compatible. 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Setting forward compat, more important for mac, but fine to have enabled on windows as well.
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	
	//Not a resizable window. 
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Window", nullptr, nullptr);

	//To make compatible with high resolution screens
	int iScreenWidth, iScreenHeight;
	glfwGetFramebufferSize(window, &iScreenWidth, &iScreenHeight);

	//Ensure the window was successfully created.
	if (!window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;

		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	//Telling GLEW we are using GL Core
	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;

		return EXIT_FAILURE;
	}

	glViewport(0, 0, iScreenWidth, iScreenHeight);

	Shader ourShader("Core.vs", "Core.frag");

	//Triage vertices
	GLfloat vertices[] =
	{
		//position				//Color
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f, 1.0f, //Bottom left
		0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f, 0.5f, //Bottom right
		0.0f, 0.5f, 0.0f,		1.0f, 0.0f, 0.0f, 0.0f //Top center
	};

	//Creating vertex array object and buffer object
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//Binding the buffers
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	//Game loop while window is open.
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Access the shader program and render it to the screen
		ourShader.Use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		//Draw opengl stuff
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();

	return EXIT_SUCCESS;
}