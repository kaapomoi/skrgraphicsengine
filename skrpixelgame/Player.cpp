#include "Player.h"

Player::Player():
	_currentStaffIndex(-1),
	_inputManager(nullptr)
{

}

Player::~Player()
{
}

void Player::init(float speed, glm::vec2 pos, int health, skrengine::InputManager* inputManager,
	std::string texturePath, skrengine::Camera2D* camera, std::vector<Projectile>* projectiles)
{
	_speed = speed;
	_position = pos;
	_health = health;
	_inputManager = inputManager;
	_textureID = skrengine::ResourceManager::getTexture(texturePath).id;
	_camera = camera;
	_projectiles = projectiles;
	_color.r = 0;
	_color.g = 0;
	_color.b = 124;
	_color.a = 255;
}

void Player::addStaff(Staff* staff)
{
	// Add staff for player
	_staffs.push_back(staff);
	
	// If no staff equipped, equip staff
	if (_currentStaffIndex == -1)
	{
		_currentStaffIndex = 0;
	}
}

void Player::update(const std::vector<std::string>& levelData,
					std::vector<Human*>& humans,
					std::vector<Enemy*>& enemies)
{
	if (_inputManager->isKeyPressed(SDLK_w))
	{
		_position.y += _speed;
	} 
	else if (_inputManager->isKeyPressed(SDLK_s))
	{
		_position.y -= _speed;
	}
	if (_inputManager->isKeyPressed(SDLK_a))
	{
		_position.x -= _speed;
	}
	else if (_inputManager->isKeyPressed(SDLK_d))
	{
		_position.x += _speed;
	}

	if (_inputManager->isKeyPressed(SDLK_1) && _staffs.size() >= 0)
	{
		_currentStaffIndex = 0;
	}
	else if (_inputManager->isKeyPressed(SDLK_2) && _staffs.size() >= 1)
	{
		_currentStaffIndex = 1;
	}
	else if (_inputManager->isKeyPressed(SDLK_3) && _staffs.size() >= 2)
	{
		_currentStaffIndex = 2;
	}


	if (_currentStaffIndex != -1)
	{
		glm::vec2 mouseCoords = _inputManager->getMouseCoords();
		mouseCoords = _camera->convertScreenToWorld(mouseCoords);
		glm::vec2 centerPosition = _position + glm::vec2(AGENT_RADIUS);
		
		glm::vec2 direction = glm::normalize(mouseCoords - centerPosition);


		_staffs[_currentStaffIndex]->update(_inputManager->isKeyPressed(SDL_BUTTON_LEFT),
			centerPosition,
			direction,
			*_projectiles);
	}

	collideWithLevel(levelData);
}
