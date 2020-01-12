#include "Human.h"
#include <glm/gtx/rotate_vector.hpp>
#include <random>
#include <ctime>

Human::Human():
	_frames(0)
{

}

Human::~Human()
{

}

void Human::init(float speed, glm::vec2 pos, std::string texturePath, int health)
{
	static std::mt19937 randomEngine(time(NULL));

	static std::uniform_real_distribution<float> randDir(-1.0f, 1.0f);

	_color.r = 255;
	_color.g = 0;
	_color.b = 255;
	_color.a = 255;

	_health = health;
	_speed = speed;
	_position = pos;
	_direction = glm::vec2(randDir(randomEngine), randDir(randomEngine));
	_textureID = skrengine::ResourceManager::getTexture(texturePath).id;
	if (_direction.length() == 0)
	{
		_direction = glm::vec2(1.0f, 0.0f);
	}

	_direction = glm::normalize(_direction);
}

void Human::update(const std::vector<std::string>& levelData,
					std::vector<Human*>& humans,
					std::vector<Enemy*>& enemies)
{
	static std::mt19937 randomEngine(time(NULL));

	static std::uniform_real_distribution<float> randRotate(-40.0f * 3.14159265359f / 180, 40.0f * 3.14159265359f / 180);

	_position += _direction * _speed;
	if (_frames >= 20)
	{
		_direction = glm::rotate(_direction, randRotate(randomEngine));
		_frames = 0;
	}
	else
	{
		_frames++;
	}
		

	if (collideWithLevel(levelData)) {
		_direction = glm::rotate(_direction, randRotate(randomEngine));
	}
}
