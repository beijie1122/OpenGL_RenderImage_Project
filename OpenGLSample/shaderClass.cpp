#include"shaderClass.h"

std::string get_file_contents(const char* filename)
{

	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);

}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	//ALL OpenGL objects are referrences, need to have values!!
	//Create Vertex Shader Object and get reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	//Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);
	compileErrors(vertexShader, "VERTEX");

	//Create gragment shader object and get reference 
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//Attach fragment shader source to the fragment shader object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	//Compile the fragment shader into machine code 
	glCompileShader(fragmentShader);
	compileErrors(fragmentShader, "FRAGMENT");

	//Create shader program object and get its reference
	ID = glCreateProgram();

	//Attach the vertex and fragment shaders to the program object
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	//Link all the shaders together into the shader program
	glLinkProgram(ID);
	compileErrors(ID, "PROGRAM");

	//Delete the shaders once we are done with them
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}

void Shader::compileErrors(unsigned int shader, const char* type)
{
	GLint hasCompiled;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << std::endl;
		}
	}
}
