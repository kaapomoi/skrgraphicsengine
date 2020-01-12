#pragma once
#include <string>
#include <glm/glm.hpp>
#include "Projectile.h"
#include <vector>

class Staff
{
public:
	Staff(std::string name, int fireRate, int projectilesPerShot, float spread, int projectileDamage, float projectileSpeed);
	~Staff();

	void update(bool isMouseDown, const glm::vec2& position, const glm::vec2& direction, std::vector<Projectile>& projectiles);

private:
	void fire(const glm::vec2& position, const glm::vec2& direction, std::vector<Projectile>& projectiles);

	std::string _name;

	int _fireRate; // Fire rate in terms of frames

	int _projectilesPerShot;

	float _spread; // Accuracy

	float _projectileSpeed;

	int _projectileDamage;

	int _frameCounter;
};

