#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <vector>

#include <skrengine/skrengine.h>
#include <skrengine/Errors.h>
#include <skrengine/ResourceManager.h>
#include <skrengine/GLSLProgram.h>
#include <skrengine/GLTexture.h>
#include <skrengine/Sprite.h>
#include <skrengine/Window.h>
#include <skrengine/Camera2D.h>
#include <skrengine/SpriteBatch.h>
#include <skrengine/InputManager.h>
#include <skrengine/Timing.h>


#include "Projectile.h"

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

	skrengine::Window _window;
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;

	skrengine::GLSLProgram _colorProgram;
	skrengine::Camera2D _camera2D;
	skrengine::SpriteBatch _spriteBatch;
	skrengine::InputManager _inputManager;
	skrengine::FPSLimiter _fpsLimiter;

	std::vector<Projectile> _projectiles;

	float _maxFPS;
	float _fps;

	float _time;
};

