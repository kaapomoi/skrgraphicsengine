#include "Staff.h"
#include <random>
#include <ctime>
#include <algorithm>
#include <glm/gtx/rotate_vector.hpp>

Staff::Staff(std::string name, int fireRate, int projectilesPerShot, float spread, int projectileDamage, float projectileSpeed):
	_name(name),
	_fireRate(fireRate),
	_projectilesPerShot(projectilesPerShot),
	_spread(spread),
	_projectileDamage(projectileDamage),
	_projectileSpeed(projectileSpeed),
	_frameCounter(0)
{

}

Staff::~Staff()
{

}

void Staff::update(bool isMouseDown, const glm::vec2& position, const glm::vec2& direction, std::vector<Projectile>& projectiles)
{
	_frameCounter++;
	if (_frameCounter >= _fireRate && isMouseDown)
	{
		fire(position, direction, projectiles);
		_frameCounter = 0;
	}
}

void Staff::fire(const glm::vec2& position, const glm::vec2& direction, std::vector<Projectile>& projectiles)
{
	static std::mt19937 randompEngine(time(NULL));

	std::uniform_real_distribution<float> randRotate(-_spread, _spread);

	for (int i = 0; i < _projectilesPerShot; i++)
	{
		projectiles.emplace_back(position, glm::rotate(direction, randRotate(randompEngine)), _projectileDamage, _projectileSpeed);
	}

}
