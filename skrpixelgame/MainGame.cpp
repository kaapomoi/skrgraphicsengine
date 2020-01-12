#include "MainGame.h"

const float HUMAN_SPEED = 0.5f;
const float ENEMY_SPEED = 0.6f;
const float PLAYER_SPEED = 1.0f;

MainGame::MainGame() :
	_screenWidth(1200),
	_screenHeight(900),
	_gameState(GameState::PLAY),
	_fps(0),
	_maxFPS(60),
	_time(0),
	_currentLevel(0),
	_player(nullptr),
	_numHumansKilled(0),
	_numEnemiesKilled(0)
{
	// todo
}

MainGame::~MainGame()
{
	for (int i = 0; i < _levels.size(); i++)
	{
		delete _levels[i];
	}

	for (int i = 0; i < _humans.size(); i++)
	{
		delete _humans[i];
	}

	for (int i = 0; i < _enemies.size(); i++)
	{
		delete _enemies[i];
	}
}

void MainGame::run()
{
	initSystems();

	initLevel();

	gameLoop();
}

void MainGame::initSystems()
{
	skrengine::init();

	_window.create("Pixel Game", _screenWidth, _screenHeight, 0);
	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);

	initShaders();

	_agentSpriteBatch.init();

	_camera2D.init(_screenWidth, _screenHeight);

	SDL_GL_SetSwapInterval(false);
}

void MainGame::initLevel()
{
	_levels.push_back(new Level("Data/Level/Level1.dat", "Data/Level/Level1bg.dat"));

	_currentLevel = 0;
	_player = new Player();
	_player->init(PLAYER_SPEED, _levels[_currentLevel]->getPlayerStartPos(), 150, &_inputManager, "Textures/goodtiles/wizard.png", &_camera2D, &_projectiles);

	_humans.push_back(_player);

	std::mt19937 randomEngine;
	randomEngine.seed(time(NULL));
	std::uniform_int_distribution<int> randX(2, _levels[_currentLevel]->getWidth() - 2);
	std::uniform_int_distribution<int> randY(2, _levels[_currentLevel]->getHeight() - 2);

	
	for (int i = 0; i < _levels[_currentLevel]->getNumHumans(); i++)
	{
		_humans.push_back(new Human());
		glm::vec2 pos(randX(randomEngine) * TILE_WIDTH, randY(randomEngine) * TILE_WIDTH);
		_humans.back()->init(HUMAN_SPEED, pos, "Textures/goodtiles/bandit.png", 20);
	}
	
	//Add enemies
	const std::vector<glm::vec2>& enemyPositons = _levels[_currentLevel]->getEnemiesStartPos();
	for (int i = 0; i < enemyPositons.size(); i++)
	{
		_enemies.push_back(new Enemy());
		_enemies.back()->init(ENEMY_SPEED, enemyPositons[i], "Textures/goodtiles/ogre.png", 100);
	}

	// Fire rate, no of proj, spread, damage, speed 
	_player->addStaff(new Staff("Atlatl", 20, 1, degToRad(3.f), 30, 10.f));

	_player->addStaff(new Staff("Morghoul", 30, 10, degToRad(20.f), 15, 10.f));

	_player->addStaff(new Staff("Staiel", 5, 1, degToRad(5.0f), 40, 15.f));
}

void MainGame::initShaders()
{
	_textureProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	_textureProgram.addAttribute("vertexPosition");
	_textureProgram.addAttribute("vertexColor");
	_textureProgram.addAttribute("vertexUV");
	_textureProgram.linkShaders();
}

void MainGame::gameLoop()
{
	skrengine::FPSLimiter fpsLimiter;
	fpsLimiter.init(60);

	while (_gameState == GameState::PLAY)
	{
		fpsLimiter.begin();

		checkVictory();

		processInput();

		updateAgents();

		updateProjectiles();

		_camera2D.setPosition(_player->getPosition());
		_camera2D.update();
		drawGame();

		_fps = fpsLimiter.end();
		//std::cout << _fps << "\n";
	}
}

void MainGame::updateAgents()
{
	// Update Humans
	for (int i = 0; i < _humans.size(); i++)
	{
		_humans[i]->update(_levels[_currentLevel]->getLevelData(), _humans, _enemies);
	}

	// Update Enemies
	for (int i = 0; i < _enemies.size(); i++)
	{
		_enemies[i]->update(_levels[_currentLevel]->getLevelData(), _humans, _enemies);
	}

	// Update enemy collisions
	for (int i = 0; i < _enemies.size(); i++)
	{
		// Collide with enemies
		for (int j = i + 1; j < _enemies.size(); j++)
		{
			_enemies[i]->collideWithAgent(_enemies[j]);
		}
		// Collide with humans
		for (int j = 1; j < _humans.size(); j++)
		{
			// If we collided with a human
			if (_enemies[i]->collideWithAgent(_humans[j])) 
			{
				_enemies.push_back(new Enemy());
				_enemies.back()->init(ENEMY_SPEED, _humans[j]->getPosition(), "Textures/goodtiles/ogre.png", 50);
				delete _humans[j];
				_humans[j] = _humans.back();
				_humans.pop_back();
			}	
		}

		// Collide with player
		if (_enemies[i]->collideWithAgent(_player))
		{
			// Deal damage to player
			//skrengine::fatalError("you lose");
		}
	}

	// Update human collisions
	for (int i = 0; i < _humans.size(); i++)
	{
		// Collide with other humans
		for (int j = i+1; j < _humans.size(); j++)
		{
			_humans[i]->collideWithAgent(_humans[j]);
		}
	}
}

void MainGame::updateProjectiles()
{
	// Collide with level
	for (int i = 0; i < _projectiles.size();)
	{
		if (_projectiles[i].update(_levels[_currentLevel]->getLevelData())) {
			_projectiles[i] = _projectiles.back();
			_projectiles.pop_back();
		}
		else
		{
			i++;
		}
	}

	bool wasProjectileRemoved;

	// Collide with humans and enemies
	for (int i = 0; i < _projectiles.size(); i++)
	{
		wasProjectileRemoved = false;
		for (int j = 0; j < _enemies.size();)
		{
			if (_projectiles[i].collideWithAgent(_enemies[j]))
			{
				// Damage enemy and kill it if its out of health
				if (_enemies[j]->applyDamage(_projectiles[i].getDamage()))
				{
					delete _enemies[j];
					_enemies[j] = _enemies.back();
					_enemies.pop_back();
					_numEnemiesKilled++;
				}
				else
				{
					j++;
				}

				// Remove projectile
				_projectiles[i] = _projectiles.back();
				_projectiles.pop_back();
				wasProjectileRemoved = true; // Make sure we dont skip a projectile
				break;
			}
			else
			{
				j++;
			}
		}

		// Loop through humans
		if (!wasProjectileRemoved)
		{
			for (int j = 1; j < _humans.size();)
			{
				if (_projectiles[i].collideWithAgent(_humans[j]))
				{
					// Damage enemy and kill it if its out of health
					if (_humans[j]->applyDamage(_projectiles[i].getDamage()))
					{
						delete _humans[j];
						_humans[j] = _humans.back();
						_humans.pop_back();
						_numHumansKilled++;
					}
					else
					{
						j++;
					}

					// Remove projectile
					_projectiles[i] = _projectiles.back();
					_projectiles.pop_back();
					wasProjectileRemoved = true; // Make sure we dont skip a projectile
					break;
				}
				else
				{
					j++;
				}
			}
		}

	}
}

void MainGame::checkVictory()
{
	if (_enemies.empty())
	{
		std::printf("***  You win! *** \n Youkilled %d humans and %d enemies. There are %d/%d civilians remaining",
			_numHumansKilled, _numEnemiesKilled, _humans.size() - 1, _levels[_currentLevel]->getNumHumans());


		skrengine::fatalError("");
	}
}

void MainGame::processInput()
{
	SDL_Event evnt;
	
	// Loops until no events to process
	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type) 
		{
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			_inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
			break;
		case SDL_KEYDOWN:
			_inputManager.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_inputManager.releaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.pressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.releaseKey(evnt.button.button);
			break;
		}
	}

}

void MainGame::drawGame()
{
	// Set the base depth to 1.0
	glClearDepth(1.0);
	// Clear the Color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Bind shaders
	_textureProgram.use();

	//Drawing
	glActiveTexture(GL_TEXTURE0);

	// Shader uses texture 0
	GLint textureUniform = _textureProgram.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);

	// Get camera matrix
	glm::mat4 projectionMatrix = _camera2D.getCameraMatrix();
	GLint pUniform = _textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	_levels[_currentLevel]->draw();

	// Draw the agents
	_agentSpriteBatch.begin();

	for (int i = 0; i < _humans.size(); i++)
	{
		_humans[i]->draw(_agentSpriteBatch);
	}
	for (int i = 0; i < _enemies.size(); i++)
	{
		_enemies[i]->draw(_agentSpriteBatch);
	}
	for (int i = 0; i < _projectiles.size(); i++)
	{
		_projectiles[i].draw(_agentSpriteBatch);
	}

	_agentSpriteBatch.end();
	_agentSpriteBatch.renderBatch();

	//static skrengine::GLTexture texture = skrengine::ResourceManager::getTexture("Textures/tilesetsingular/tile023.png");

	_textureProgram.unuse();

	_window.swapBuffer();
}

float MainGame::degToRad(float deg)
{
	float rad = (deg * 3.1415926535) / 180;
	return rad;
}
