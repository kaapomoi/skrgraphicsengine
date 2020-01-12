#pragma once
#include <algorithm>

#include <glm/glm.hpp>
#include <skrengine/GLTexture.h>
#include <skrengine/SpriteBatch.h>
#include <skrengine/ResourceManager.h>

#include "Level.h"

const float AGENT_WIDTH = 16.0f;
const float AGENT_SCALE = 2.0f;
const float AGENT_RADIUS = AGENT_WIDTH / 2.0f;

class Enemy;
class Human;

class Agent
{
public:
	Agent();
	virtual ~Agent();

	virtual void update(const std::vector<std::string>& levelData,
						std::vector<Human*>& humans,
						std::vector<Enemy*>& enemies) = 0;


	bool collideWithLevel(const std::vector<std::string>& levelData);

	bool collideWithAgent(Agent *agent);

	void draw(skrengine::SpriteBatch& spriteBatch);

	// return true if we died
	bool applyDamage(int damage);

	glm::vec2 getPosition() const { return _position; }

protected:
	void checkTilePosition(const std::vector<std::string>& levelData,
							std::vector<glm::vec2>& collideTilePositions,
							float x,
							float y);

	void collideWithTile(glm::vec2 tilePos);

	unsigned int _textureID;
	float _health;
	glm::vec2 _position;
	float _speed;
	skrengine::Color _color;
};

