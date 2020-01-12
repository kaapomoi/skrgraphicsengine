#pragma once
#include "Agent.h"

class Enemy : public Agent
{
public:
	Enemy();
	~Enemy();

	void init(float speed, glm::vec2 pos, std::string texturePath, int health);

	virtual void update(const std::vector<std::string>& levelData,
		std::vector<Human*>& humans,
		std::vector<Enemy*>& enemies);
private:
	glm::vec2 _direction;
	Human* getNearestHuman(std::vector<Human*>& humans);
};

