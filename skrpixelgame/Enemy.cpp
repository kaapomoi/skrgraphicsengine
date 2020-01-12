#include "Enemy.h"

#include "Human.h"
#include <random>
#include <ctime>
#include <glm/gtx/rotate_vector.hpp>


Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::init(float speed, glm::vec2 pos, std::string texturePath, int health)
{
	_speed = speed;
	_position = pos;
	_health = health;
	_textureID = skrengine::ResourceManager::getTexture(texturePath).id;
	_color.r = 255;
	_color.g = 255;
	_color.b = 255;
	_color.a = 255;
}

void Enemy::update(const std::vector<std::string>& levelData, 
				std::vector<Human*>& humans, 
				std::vector<Enemy*>& enemies)
{
	Human* closestHuman = getNearestHuman(humans);

	static std::mt19937 randomsEngine(time(NULL));

	static std::uniform_real_distribution<float> randomRotate(-40.0f * 3.14159265359f / 180, 40.0f * 3.14159265359f / 180);

	if (closestHuman != nullptr)
	{
		_direction = glm::normalize(closestHuman->getPosition() - _position);
	}
	if (collideWithLevel(levelData)) {
		_direction = glm::rotate(_direction, randomRotate(randomsEngine));
	}
	_position += _direction * _speed;
}

Human* Enemy::getNearestHuman(std::vector<Human*>& humans)
{
	Human* closestHuman = nullptr;
	float smallestDistance = 999999999.0f;

	for (int i = 0; i < humans.size(); i++)
	{
		glm::vec2 distVec = humans[i]->getPosition() - _position;
		float distance = glm::length(distVec);

		if (distance < smallestDistance)
		{
			smallestDistance = distance;
			closestHuman = humans[i];
		}
	}

	return closestHuman;
}
