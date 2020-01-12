#pragma once
#include "Human.h"
#include <skrengine/InputManager.h>
#include <skrengine/Camera2D.h>

#include <SDL/SDL.h>

#include "Projectile.h"
#include "Staff.h"

class Player : public Human
{
public:
	Player();
	~Player();

	void init(float speed, glm::vec2 pos, int health, skrengine::InputManager* inputManager,
		std::string texturePath,
		skrengine::Camera2D* camera,
		std::vector<Projectile>* projectiles
	);

	void addStaff(Staff* staff);

	void update(const std::vector<std::string>& levelData,
		std::vector<Human*>& humans,
		std::vector<Enemy*>& enemies) override;

private:
	skrengine::InputManager* _inputManager;
	
	std::vector<Staff*> _staffs;
	int _currentStaffIndex;

	skrengine::Camera2D* _camera;
	std::vector<Projectile>* _projectiles;
};

