#include "Projectile.h"
#include "Agent.h"
#include "Human.h"
#include "Enemy.h"
#include "Level.h"

Projectile::Projectile(glm::vec2 pos, glm::vec2 dir, int damage, float speed) :
	_speed(speed),
	_direction(dir),
	_position(pos),
	_damage(damage)
{
	
}

Projectile::~Projectile()
{

}

void Projectile::draw(skrengine::SpriteBatch& spriteBatch)
{
	skrengine::Color color;
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(_position.x + PROJECTILE_RADIUS,
		_position.y + PROJECTILE_RADIUS,
		PROJECTILE_RADIUS * 2,
		PROJECTILE_RADIUS * 2);

	static skrengine::GLTexture texture = skrengine::ResourceManager::getTexture("Textures/tilesetsingular/tile023.png");

	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	glm::vec4 posAndSize = glm::vec4(_position.x, _position.y, 16, 16);

	spriteBatch.draw(destRect, uv, texture.id, color, 0.0f);
}

bool Projectile::update(const std::vector<std::string>& levelData)
{
	_position += _direction * _speed;
	
	return collideWithWorld(levelData);
}

bool Projectile::collideWithAgent(Agent* agent)
{
	const float MIN_DISTANCE = AGENT_RADIUS + PROJECTILE_RADIUS;

	glm::vec2 centerPosA = _position;// + glm::vec2(PROJECTILE_RADIUS);
	glm::vec2 centerPosB = agent->getPosition() + glm::vec2(AGENT_RADIUS);

	glm::vec2 distVec = centerPosA - centerPosB;

	float distance = glm::length(distVec);

	float collisionDepth = MIN_DISTANCE - distance;
	// Collide
	if (collisionDepth > 0)
	{
		return true;
	}
	return false;
}

bool Projectile::collideWithWorld(const std::vector<std::string>& levelData)
{
	glm::ivec2 gridPosition;
	gridPosition.x = floor(_position.x / (float)TILE_WIDTH);
	gridPosition.y = floor(_position.y / (float)TILE_WIDTH);

	if (gridPosition.x < 0 || gridPosition.x > levelData[0].length() ||
		gridPosition.y < 0 || gridPosition.y > levelData.size())
	{
		return true;
	}

	return (levelData[gridPosition.y][gridPosition.x] != '.');
}
