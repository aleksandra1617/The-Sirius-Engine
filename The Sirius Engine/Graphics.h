#pragma once
#include <SDL.h>
#include <vector>

class ShaderHandler;

/// Will be used to create loading bar and keep track of what the graphics system is doing. 
enum class GraphicsStage { NON, LOAD_VERT_DATA, COMPILE_SHADERS, RENDER };

///Handles rendering. 
class Graphics
{
public:

	Graphics();
	~Graphics();
	
	void Start();
	void Update();
	void Render();

private:
	
	int _winWidth, _winHight;

	/*
	*	Defining integer constants to improve readability. Any integers
	*	found in the code should be counting numbers, not ids.
	*/
	const int NULLID{ 0 };

	unsigned int _vbo;

	GraphicsStage _graphicsStage;

	ShaderHandler *_sh;
	SDL_Window * _window;
	SDL_Renderer * _renderer;
	SDL_GLContext _glContext;

	
	void CreateWindow();

	//This buffer is stored in the VRAM
	void CreateBuffer(unsigned int  &bufferID, std::vector<float> data);
};

