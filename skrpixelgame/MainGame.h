#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <random>
#include <ctime>

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

#include "Enemy.h"
#include "Player.h"
#include "Level.h"
#include "Projectile.h"
#include "Staff.h"

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

	// Runs the game
	void run();

private:
	// Initializes the core systems
	void initSystems();

	// Initializes level
	void initLevel();

	// Initializes the shaders
	void initShaders();

	// Main game loop
	void gameLoop();

	// Updates all agents
	void updateAgents();

	void updateProjectiles();

	void checkVictory();

	// Handles input processing
	void processInput();

	// Renders the game
	void drawGame();
	
	float degToRad(float deg);

	GameState _gameState;

	// Member variables
	skrengine::Window _window;

	skrengine::GLSLProgram _textureProgram;
	
	skrengine::InputManager _inputManager;
	
	skrengine::Camera2D _camera2D;
	skrengine::SpriteBatch _agentSpriteBatch;

	std::vector<Level*> _levels;
	
	skrengine::FPSLimiter _fpsLimiter;

	std::vector<Projectile> _projectiles;

	int _screenWidth;
	int _screenHeight;

	float _maxFPS;
	float _fps;

	float _time;
	
	int _currentLevel;

	Player* _player;
	std::vector<Human*> _humans;
	std::vector<Enemy*> _enemies;

	int _numHumansKilled;
	int _numEnemiesKilled;

};

