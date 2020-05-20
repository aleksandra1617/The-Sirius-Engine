#include "ShaderHandler.h"


// Using an initialisation list here because it's faster than _program = 0
// (only works for constructors)
ShaderHandler::ShaderHandler() : _program(0){}
ShaderHandler::~ShaderHandler(){}


void ShaderHandler::LinkProgram()
{
	//CREATES A VERTEX SHADER HANDLER
	GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, "./Default Shaders/shader1.vs");

	//CREATES A FRAGMENT SHADER HANDLER
	GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, "./Default Shaders/shader1.fs");

	_program = glCreateProgram();

	//Handle vertex shader
	glAttachShader(_program, vertexShader);
	glDeleteShader(vertexShader);
	glDetachShader(_program, vertexShader);

	//Handle fragment shader
	glAttachShader(_program, fragmentShader);
	glDeleteShader(fragmentShader);
	glDetachShader(_program, fragmentShader); 
	glLinkProgram(_program);

	CheckLink();
}

void ShaderHandler::CheckLink()
{
	GLint link_status;
	glGetProgramiv(_program, GL_LINK_STATUS, &link_status);

	std::cout << "Link status: " << link_status << std::endl;

	if (link_status != GL_TRUE)
	{
		const int string_length = 1024;
		GLchar errorLog[string_length] = "";
		glGetProgramInfoLog(_program, string_length, NULL, errorLog);
		std::cout << "Error Detected in LinkProgram()" << std::endl; 
		std::cerr << errorLog << std::endl;
	}
	else
	{
		std::cout << "Successful Link Established!" << std::endl;
	}
}


std::string ShaderHandler::ReadShaderString(const std::string &path) 
{
	std::string data;
	std::string line;

	std::ifstream shaderFile;
	shaderFile.open((path).c_str());

	if (shaderFile.is_open())
	{
		//while there's more to read
		while (shaderFile.good())
		{
			getline(shaderFile, line);
			data.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load the (" << path << ") shader file!" << std::endl;
	}

	return data;
}


GLuint ShaderHandler::CreateShader(GLenum shaderType, const std::string &path)
{
	GLuint shader = glCreateShader(shaderType);
	std::string shaderData = ReadShaderString(path);

	const char * shaderCode = shaderData.c_str();
	glShaderSource(shader, 1, (const GLchar **)&shaderCode, NULL);
	glCompileShader(shader);

	CheckShaderCompilation(shader);

	return shader;
}


bool ShaderHandler::CheckShaderCompilation(GLuint shader)
{
	GLint compile_status = GL_FALSE;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);

	if (compile_status != GL_TRUE)
	{
		const int string_length = 1024;
		GLchar log[string_length] = "";
		glGetShaderInfoLog(shader, string_length, NULL, log);
		std::cout << "Error Detected in CreateShader()";
		std::cerr << log << std::endl;

		return false;
	}
	else
	{
		std::cout << "Shader: " << shader << " compiled sucessfully. " << std::endl;
	}

	return true;
}
