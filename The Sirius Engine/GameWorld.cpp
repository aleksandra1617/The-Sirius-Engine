#include "GameWorld.h"
#include "Graphics.h"
#include "Physics.h"

#include <iostream>

GameWorld::GameWorld()
{
	_graphics = new Graphics;
	_physics = new Physics;

	_gameState = GameState::NON;
}


GameWorld::~GameWorld()
{
	delete _graphics;
	delete _physics;
}


void GameWorld::InitSystems()
{
	_graphics->Start();
	_physics->Start();
}


void GameWorld::Run()
{
	InitSystems();

	//GamePlay
	while (_gameState != GameState::EXIT) 
	{
		_graphics->Update();
		ProcessInput();
	}
}


void GameWorld::ProcessInput() 
{
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
			
			case SDL_MOUSEMOTION:
				std::cout << "DEBUG: Mouse Pos X: ";
				std::cout << e.motion.x << "  Y: ";
				std::cout << e.motion.y << "\n ";
				break;
		}
	}
}