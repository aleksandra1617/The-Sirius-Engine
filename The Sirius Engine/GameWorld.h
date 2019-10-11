#pragma once

class Graphics;
class Physics;

enum class GameState { NON, PLAY, SAVE, LOAD, EXIT }; //TODO: Maybe rename 'Non' to IN_MENU

class GameWorld
{
public:
	GameWorld();
	~GameWorld();

	void Run();

private: 
	GameState _gameState;

	Graphics *_graphics;
	Physics *_physics;

	void InitSystems();
	void ProcessInput();
};

