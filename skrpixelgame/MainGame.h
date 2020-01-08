#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <vector>

#include "GLSLProgram.h"
#include "GLTexture.h"
#include "Sprite.h"

enum class GameState 
{
	PLAY, 
	EXIT
};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

	

private:
	void initSystems();
	void initShaders();
	void gameLoop();
	void processInput();
	void drawGame();
	void calculateFPS();

	SDL_Window* _window;
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;

	std::vector<Sprite*> _sprites;

	GLSLProgram _colorProgram;

	float _maxFPS;
	float _fps;
	float _frameTime;

	float _time;
};
