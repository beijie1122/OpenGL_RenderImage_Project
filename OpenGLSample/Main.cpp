#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "stb.h"
#include"shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

int main()
{
	//Initialize glfw
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



	//Tell glfw the name of the window (window) and the dimensions/name 
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGLSample", NULL, NULL);

	//Safety, incase the window does not open
	if (window == NULL)
	{
		printf("Failed too create GLFW window\n");
		glfwTerminate();
		return -1;
	}

	//Make the window current context
	glfwMakeContextCurrent(window);

	//Loads GLAD to configure OpenGL
	gladLoadGL();

	//Specify the viewport for OpenGL
	glViewport(0, 0, 800, 800);

	//Vertices coordinates - Edit this to change the image of a triangle 
	//GLfloat vertices[] =
	//{
	//	-0.5f, -0.5f * float(sqrt(3)) *1/ 3,	0.0f,	0.8f, 0.3f, 0.2f,			//Lower left corner
	//	0.5f, -0.5f * float(sqrt(3)) *1/ 3,		0.0f,	0.8f, 0.3f, 0.2f,			//Lower right corner
	//	0.0f, 0.5f * float(sqrt(3)) * 2 / 3,	0.0f,	1.0f, 0.6f, 0.32f,		//Upper Corner
	//	-0.25f, 0.5f * float(sqrt(3)) *1/ 6,	0.0f,	0.9, 0.45f, 0.17f,		//Inner left
	//	0.25f, 0.5f * float(sqrt(3)) *1/ 6,		0.0f,	0.9, 0.45f, 0.17f,		//Inner right
	//	0.0f, -0.5f * float(sqrt(3)) *1/ 3,		0.0f,	0.8f, 0.3f, 0.02f			//Inner down
	//};

	//GLuint indices[] =
	//{
	//	0, 3, 5,	//Lower left 
	//	3, 2, 4,	//lower right
	//	5, 4, 1		//Upper triangle
	//};

	GLfloat vertices[] =
	{
		-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
		0.5f, 0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 1.0f,	1.0f, 0.0f
	};

	GLuint indices[] =
	{
		0, 2, 1,
		0, 3, 2
	};

	

	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	//VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	//VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	int widthImg, hightImg, numColCh;
	unsigned char* bytes = stbi_load("PopCatTestImageforGL.png", &widthImg, &hightImg, &numColCh, 0);

	GLuint texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Finding the VBO and objects 

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, hightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLuint tex0Uni = glGetUniformLocation(shaderProgram.ID, "tex0");
	shaderProgram.Activate();
	glUniform1i(tex0Uni, 0);

	//Color to render (currently navy blue) - RED, YELLOW, BLUE, OPENSITY (0 - 1)
	//glClearColor(0.07f, 0.03f, 0.17f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT);
	//glfwSwapBuffers(window);

	//Loops are needed to keep the window open, write in the loop to determine what closes the window
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram.Activate();
		glUniform1f(uniID, 0.5f);
		glBindTexture(GL_TEXTURE_2D, texture);
		VAO1.Bind();
		//glDrawArrays(GL_TRIANGLES, 0, 3); -- first example with one triangle
		//glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	glDeleteTextures(1, &texture);
	shaderProgram.Delete();
	//Gets ride of OpenGL (similar to IOstreams)
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}