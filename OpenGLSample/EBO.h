#pragma once
#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>

class EBO
{

public:
	GLuint ID;
	EBO(GLuint* indicies, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();


};






#endif // !VBO_CLASS_H
