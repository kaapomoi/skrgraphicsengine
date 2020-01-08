#include "MainGame.h"

MainGame::MainGame() :
	_screenWidth(800),
	_screenHeight(800),
	_gameState(GameState::PLAY),
	_time(0.0f),
	_maxFPS(144.0f),
	_fps(0.0f)
{
	_camera2D.init(_screenWidth, _screenHeight);
}

MainGame::~MainGame()
{

}

void MainGame::run()
{
	initSystems();
	//_playerTexture = ImageLoader::loadPNG("Textures/tilesetsingular/tile023.png");

	gameLoop();
}

void MainGame::initSystems()
{
	skrengine::init();
	
	_window.create("Pixel game", _screenWidth, _screenHeight, 0);

	initShaders();

	_spriteBatch.init();
	_fpsLimiter.init(_maxFPS);
}

void MainGame::initShaders()
{
	_colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		_fpsLimiter.begin();

		processInput();
		_time += 0.01f;

		_camera2D.update();

		for (int i = 0; i < _projectiles.size();)
		{
			if (_projectiles[i].update())
			{
				_projectiles[i] = _projectiles.back();
				_projectiles.pop_back();
			}
			else
			{
				i++;
			}
		}

		drawGame();

		_fps = _fpsLimiter.end();

		static int frameCount = 0;
		frameCount++;
		if (frameCount >= 1000)
		{
			std::cout << _fps << "fps\n";
			frameCount = 0;
		}
	}
}

void MainGame::processInput()
{
	SDL_Event evnt;

	const float CAMERA_SPEED = _screenWidth/32;
	const float SCALE_SPEED = 0.025f;

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

	if (_inputManager.isKeyPressed(SDLK_w))
	{
		_camera2D.setPosition(_camera2D.getPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
	}
	if (_inputManager.isKeyPressed(SDLK_s))
	{
		_camera2D.setPosition(_camera2D.getPosition() + glm::vec2(0.0f, CAMERA_SPEED));
	}
	if (_inputManager.isKeyPressed(SDLK_a))
	{
		_camera2D.setPosition(_camera2D.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
	}
	if (_inputManager.isKeyPressed(SDLK_d))
	{
		_camera2D.setPosition(_camera2D.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
	}
	if (_inputManager.isKeyPressed(SDLK_q))
	{
		_camera2D.setScale(_camera2D.getScale() + -SCALE_SPEED);
	}
	if (_inputManager.isKeyPressed(SDLK_e))
	{
		_camera2D.setScale(_camera2D.getScale() + SCALE_SPEED);
	}

	if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT))
	{
		glm::vec2 mousecoords = _inputManager.getMouseCoords();
		mousecoords = _camera2D.convertScreenToWorld(mousecoords);
		std::cout << mousecoords.x << ", " << mousecoords.y << "\n";

		glm::vec2 playerPosition(0.0f);
		glm::vec2 direction = mousecoords - playerPosition;
		direction = glm::normalize(direction);

		_projectiles.emplace_back(playerPosition, direction, 1.f, 1000);

	}

}

void MainGame::drawGame()
{
	// Set the base depth to 1.0
	glClearDepth(1.0);
	// Clear the Color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colorProgram.use();
	glActiveTexture(GL_TEXTURE0);
	GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	//GLuint timeLocation = _colorProgram.getUniformLocation("time");
	//glUniform1f(timeLocation, _time);

	GLuint pLocation = _colorProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera2D.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	_spriteBatch.begin();

	
	glm::vec4 pos(0.0f, 0.0f, 16.0f, 16.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	static skrengine::GLTexture texture = skrengine::ResourceManager::getTexture("Textures/tilesetsingular/tile023.png");
	skrengine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	_spriteBatch.draw(pos, uv, texture.id, color, 0.0f);

	for (int i = 0; i < _projectiles.size(); i++)
	{
		_projectiles[i].draw(_spriteBatch);
	}

	_spriteBatch.end();

	_spriteBatch.renderBatch();


	glBindTexture(GL_TEXTURE_2D, 0);
	_colorProgram.unuse();
	
	_window.swapBuffer();
}

/*
void MainGame::calculateFPS()
{
	static Uint32 fpsFrames = 0;   // Frames passed since the last recorded fps.
	static Uint32 fpsLastTime = SDL_GetTicks();

	fpsFrames++;
	if (SDL_GetTicks() >= 1000U && fpsLastTime <= SDL_GetTicks() - 1000U) {  // Update once per second = 1000
		fpsLastTime = SDL_GetTicks();
		_fps = fpsFrames;
		std::cout << _fps << "   \r";  // a couple spaces followed by a \r makes it stay on the same line nicely
		fpsFrames = 0;
	}
}
*/