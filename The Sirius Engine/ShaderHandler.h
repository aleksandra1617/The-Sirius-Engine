#pragma once

#include <iostream>
#include <fstream> 
#include <vector>
#include <map>
#include <string> 
#include <GL\glew.h>

class ShaderHandler
{
public:
	ShaderHandler();
	~ShaderHandler();

	/*
	*	Creates a program object to host the shaders and their settings.
	*   The program object attempts to bind the shaders
	*   together when it is linked. If the shaders aren't compatible
	*   the link process will fail. Once the program gets the shader
	*   stage information, the shaders can be detatched and deleted.
	*/
	void LinkProgram();

private:
	GLuint _program;

	///Quearies program link errors via the OpenGL's info log.
	void CheckLink();

	/**
	*   Shaders are loaded from a text file into a string which is
	*	passed to OpenGL for compiling. 
	*/
	std::string ReadShaderString(const std::string &path);

	/** 
	*	Reads the shader string therough the 'ReadShaderString' function,
	*	creates a shader object and attempts to compile it. 
	*/
	GLuint CreateShader(GLenum shaderType, const std::string &path);

	///Quearies shader compile errors via the OpenGL's info log.
	bool CheckShaderCompilation(GLuint shader);
};

