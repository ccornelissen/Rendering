#include <iostream>

#define GLEW_STATIC

//Glew
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>

//SOIL
#include "SOIL2/SOIL2.h"

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Local
#include "Shader.h"

const GLint WIDTH = 1280, HEIGHT = 720;

int main()
{
	glfwInit();

	//Setting the version of GLFW to 3.3, will fall back if this fails.
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

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Shader ourShader("Core.vs", "Core.frag");

	//Triage vertices
	/*GLfloat vertices[] =
	{
		//position				//Color						//Texture Coords
		0.5f, 0.5f, 0.0f,		0.0f, 0.0f, 0.0f, 1.0f,		1.0f, 1.0f,				//Top right
		0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 0.0f, 1.0f,		1.0f, 0.0f,				//Bottom right
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 0.0f, 1.0f,		0.0f, 0.0f,				//Bottom left
		-0.5f, 0.5f, 0.0f,		0.0f, 0.0f, 0.0f, 1.0f,		0.0f, 1.0f				//Top left
	};

	GLuint indices[] =
	{
		0, 1, 3,	//First triangle
		1, 2, 3		//Second Triangle
	};*/

	// Set up vertex data and attribute pointers
	// use with Orthographic Projection
// 	GLfloat vertices[] = {
// 	-0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 0.0f,
// 	0.5f * 500, -0.5f * 500, -0.5f * 500,  1.0f, 0.0f,
// 	0.5f * 500,  0.5f * 500, -0.5f * 500,  1.0f, 1.0f,
// 	0.5f * 500,  0.5f * 500, -0.5f * 500,  1.0f, 1.0f,
// 	-0.5f * 500,  0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
// 	-0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 0.0f,
// 
// 	-0.5f * 500, -0.5f * 500,  0.5f * 500,  0.0f, 0.0f,
// 	0.5f * 500, -0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
// 	0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 1.0f,
// 	0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 1.0f,
// 	-0.5f * 500,  0.5f * 500,  0.5f * 500,  0.0f, 1.0f,
// 	-0.5f * 500, -0.5f * 500,  0.5f * 500,  0.0f, 0.0f,
// 
// 	-0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
// 	-0.5f * 500,  0.5f * 500, -0.5f * 500,  1.0f, 1.0f,
// 	-0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
// 	-0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
// 	-0.5f * 500, -0.5f * 500,  0.5f * 500,  0.0f, 0.0f,
// 	-0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
// 
// 	0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
// 	0.5f * 500,  0.5f * 500, -0.5f * 500,  1.0f, 1.0f,
// 	0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
// 	0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
// 	0.5f * 500, -0.5f * 500,  0.5f * 500,  0.0f, 0.0f,
// 	0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
// 
// 	-0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
// 	0.5f * 500, -0.5f * 500, -0.5f * 500,  1.0f, 1.0f,
// 	0.5f * 500, -0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
// 	0.5f * 500, -0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
// 	-0.5f * 500, -0.5f * 500,  0.5f * 500,  0.0f, 0.0f,
// 	-0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
// 
// 	-0.5f * 500,  0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
// 	0.5f * 500,  0.5f * 500, -0.5f * 500,  1.0f, 1.0f,
// 	0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
// 	0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
// 	-0.5f * 500,  0.5f * 500,  0.5f * 500,  0.0f, 0.0f,
// 	-0.5f * 500,  0.5f * 500, -0.5f * 500,  0.0f, 1.0f
// 	};
	
	// use with Perspective Projection (Works like a camera)
	GLfloat vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	}; 

	//Creating vertex array object and buffer object
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//Binding the buffers
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(1);

	//Texture coordinates
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	GLuint texture;

	int iWidth, iHeight;

	//Bind texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	//Setup texture params
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Set image and unbind the texture
	unsigned char *image = SOIL_load_image("Images/banner.jpg", &iWidth, &iHeight, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iWidth, iHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	//Projection setup
	glm::mat4 projection;
	//View frustum angle, camera aspect ration, minimum render distance, max render distance
	projection = glm::perspective(45.0f, (GLfloat)(iScreenWidth / iScreenHeight), 0.1f, 1000.0f);
	/*projection = glm::ortho(0.0f, (GLfloat)iScreenWidth, 0.0f, (GLfloat)iScreenHeight, 0.1f, 1000.f);*/

	//Game loop while window is open.
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		//Clear color buffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Bind/set Texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture"), 0);

		//Access the shader program and render it to the screen
		ourShader.Use();
		
		glm::mat4 model;
		glm::mat4 view;
		
		//Perspective
		model = glm::rotate(model, (GLfloat)glfwGetTime() * 1.5f, glm::vec3(0.5f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		
		//Orthoginal
// 		model = glm::rotate(model, 0.5f, glm::vec3(1.0f, 0.0f, 0.0f));
// 		view = glm::translate(view, glm::vec3(iScreenWidth / 2, iScreenHeight / 2, -700.0f));

		//Pass info to the shader
		GLint modellocation = glGetUniformLocation(ourShader.Program, "model");
		GLint viewlocation = glGetUniformLocation(ourShader.Program, "view");
		GLint projectionlocation = glGetUniformLocation(ourShader.Program, "projection");

		glUniformMatrix4fv(modellocation, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewlocation, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projectionlocation, 1, GL_FALSE, glm::value_ptr(projection));

		//Draw the model
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		/*
		//Create transform
		glm::mat4 transform;
		transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, 0.0f));
		transform = glm::rotate(transform, (GLfloat)glfwGetTime() * 2.0f, glm::vec3(0.0f, 0.0f, 1.0f));

		//Apply transform
		GLint transformlocation = glGetUniformLocation(ourShader.Program, "transform");
		glUniformMatrix4fv(transformlocation, 1, GL_FALSE, glm::value_ptr(transform));
		*/

		//Draw openGL stuff
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);

	glfwTerminate();

	return EXIT_SUCCESS;
}