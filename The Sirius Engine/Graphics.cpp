/// The region coments are to separate all the functions that are being called 
/// in the specific core function(Start, Update, Render) to allow for easier 
/// debugging and increase readability. 

#include "Graphics.h"

#include <vector>
#include <iostream>
#include <GL\glew.h> 
#include <SDL.h>

Graphics::Graphics()
{
	_winWidth = 1024;
	_winHight = 720;
}


Graphics::~Graphics()
{
	glDeleteBuffers(1, &_vbo);

	SDL_DestroyRenderer(_renderer);
	SDL_GL_DeleteContext(_glContext);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

#pragma region Start
void Graphics::Start()
{
	CreateWindow();

	//CREATE Context (allows the GPU to draw on the SDL Window)
	_glContext = SDL_GL_CreateContext(_window);

	//INITIALIZE GLEW
	GLenum status = glewInit();

	//CHECK if initialized correctly
	if (status != GLEW_OK)
	{
		SDL_Log("Unable to initialize GLEW");
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	//Gather buffer data (X, Y pos)
	std::vector<float> data = {-0.5f,  0.5f,
								0.5f,  0.5f,
								0.0f, -0.5f};
								

	//Send the data to a vbo
	CreateBuffer(_vbo, data);
}

void Graphics::CreateWindow()
{
	//INITIALIZE SDL. 
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) // 0 is passed when we don't want to use any flags 
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
	else
		SDL_Log("SDL initialized!");

	//SET attributes
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);  //Number of bits used to display red/ Number of shades of red that can be displayed
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32); //The data in bits allocated per pixel, 32 bits of colour data -> 2 to the power of 8
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); //Creates one buffer but allocates space for two


	//CREATE window flags
	Uint32 flags = SDL_WINDOW_OPENGL;

	//CREATE Window and Renderer
	SDL_CreateWindowAndRenderer(_winWidth, _winHight, flags, &_window, &_renderer);
	SDL_SetWindowTitle(_window, "My Engine");
}


void Graphics::CreateBuffer(unsigned int &bufferID, std::vector<float> data) //TODO: Create a template so that I can create any type of buffer not just one made from floats.
{
	//Generates a buffer and assigns an ID to it
	glGenBuffers(1, &bufferID);

	//Specify how to use the buffer and select it
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);

	//Specify buffer size (optional: provide the buffer with data )
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(data), data.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, NULLID);
}
#pragma endregion "All the graphics setup functions, called in 'Start'."

///UPDATE region
void Graphics::Update()
{
	glClearColor(0.02f, 0.3f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Render();

	//Swaps the buffers
	SDL_GL_SwapWindow(_window);
}

///RENDER region
void Graphics::Render()
{
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glEnableVertexAttribArray(0);
	
	//Look for the data: starting at 0, 3 floats per vertex, no normalizing, with no stride and no offset.
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//Draw: triangles, starting at 0, 3 vertices.
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(NULLID);
	glBindBuffer(GL_ARRAY_BUFFER, NULLID);
}
