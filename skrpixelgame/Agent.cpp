#include "Agent.h"

Agent::Agent() :
	_speed(0.f),
	_position(0.0f),
	_textureID(0)
{

}

Agent::~Agent()
{
}

bool Agent::collideWithLevel(const std::vector<std::string>& levelData)
{
	std::vector<glm::vec2> collideTilePositions;

	checkTilePosition(levelData, collideTilePositions, _position.x, _position.y);

	checkTilePosition(levelData, collideTilePositions, _position.x + AGENT_WIDTH, _position.y);

	checkTilePosition(levelData, collideTilePositions, _position.x, _position.y + AGENT_WIDTH);

	checkTilePosition(levelData, collideTilePositions, _position.x + AGENT_WIDTH, _position.y + AGENT_WIDTH);

	if (collideTilePositions.size() == 0)
	{
		return false;
	}

	// Do the collision
	for (int i = 0; i < collideTilePositions.size(); i++)
	{
		collideWithTile(collideTilePositions[i]);
	}
	return true;
}

bool Agent::collideWithAgent(Agent* agent)
{
	const float MIN_DISTANCE =  AGENT_RADIUS * 2;

	glm::vec2 centerPosA = _position + glm::vec2(AGENT_RADIUS);
	glm::vec2 centerPosB = agent->getPosition() + glm::vec2(AGENT_RADIUS);

	glm::vec2 distVec = centerPosA - centerPosB;

	float distance = glm::length(distVec);

	float collisionDepth = MIN_DISTANCE - distance;
	// Collide
	if (collisionDepth > 0)
	{
		glm::vec2 collisionDepthVec = glm::normalize(distVec) * collisionDepth;

		_position += collisionDepthVec / 2.0f;
		agent->_position -= collisionDepthVec / 2.0f;
		return true;
	}
	return false;
}

void Agent::draw(skrengine::SpriteBatch& spriteBatch)
{
	//static int textureID = skrengine::ResourceManager::getTexture("Textures/goodtiles/bandit.png").id;
	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	skrengine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	glm::vec4 destRect;
	destRect.x = _position.x;
	destRect.y = _position.y;
	destRect.z = AGENT_WIDTH;
	destRect.w = AGENT_WIDTH;

	spriteBatch.draw(destRect, uvRect, _textureID, color, 1.0f);
}

bool Agent::applyDamage(int damage)
{
	_health -= damage;
	if (_health <= 0)
	{
		return true;
	}
	return false;
}

void Agent::checkTilePosition(const std::vector<std::string>& levelData, 
	std::vector<glm::vec2>& collideTilePositions, float x, float y)
{
	//Check the four corners
	//First corner
	glm::vec2 cornerPos = glm::vec2(floor(x / (float)TILE_WIDTH),
									  floor(y / (float)TILE_WIDTH));
	 
	if (cornerPos.x < 0 || cornerPos.x > levelData[0].length() || 
		cornerPos.y < 0 || cornerPos.y > levelData.size())
	{
		return;
	}
	if (levelData[cornerPos.y][cornerPos.x] != '.')
	{
		collideTilePositions.push_back(cornerPos * (float)TILE_WIDTH + glm::vec2((float)TILE_WIDTH / 2.0f));
	}
}

// AABB collision
void Agent::collideWithTile(glm::vec2 tilePos)
{
	const float TILE_RADIUS = (float)TILE_WIDTH / 2.0f;
	const float MIN_DISTANCE = AGENT_RADIUS + TILE_RADIUS;

	glm::vec2 certerPlayerPos = _position + glm::vec2(AGENT_RADIUS);
	glm::vec2 distVec = certerPlayerPos - tilePos;

	float xdepth = MIN_DISTANCE - abs(distVec.x);
	float ydepth = MIN_DISTANCE - abs(distVec.y);

	// Colliding
	if (xdepth > 0 && ydepth > 0)
	{
		if (std::max(xdepth, 0.0f) < std::max(ydepth, 0.0f))
		{
			if (distVec.x < 0)
			{
				_position.x -= xdepth;
			}
			else
			{
				_position.x += xdepth;
			}
		}
		else
		{
			if (distVec.y < 0)
			{
				_position.y -= ydepth;
			}
			else
			{
				_position.y += ydepth;
			}
		}
	}

}
