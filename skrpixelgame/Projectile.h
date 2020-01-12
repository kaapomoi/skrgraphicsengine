#pragma once
#include <glm/glm.hpp>
#include <skrengine/SpriteBatch.h>
#include <skrengine/GLTexture.h>
#include <skrengine/ResourceManager.h>
#include <vector>

static const int PROJECTILE_RADIUS = 4;

class Human;
class Enemy;
class Agent;

class Projectile
{
public:
	Projectile(glm::vec2 pos, glm::vec2 dir, int _damage, float speed);
	~Projectile();

	void draw(skrengine::SpriteBatch& spriteBatch);

	// When update returns true, delete bullet
	bool update(const std::vector<std::string>& levelData);

	bool collideWithAgent(Agent* agent);

	int getDamage() const { return _damage; }

private:

	bool collideWithWorld(const std::vector<std::string>& levelData);

	glm::vec2 _position;
	glm::vec2 _direction;
	int _damage;
	float _speed;
	//int _lifeTime;
};

