#pragma once
#include <glm/glm.hpp>
#include <skrengine/SpriteBatch.h>
#include <skrengine/GLTexture.h>
#include <skrengine/ResourceManager.h>

class Projectile
{
public:
	Projectile(glm::vec2 pos, glm::vec2 dir, float speed, int lifeTime);
	~Projectile();

	void draw(skrengine::SpriteBatch& spriteBatch);
	bool update();

private:
	int _lifeTime;
	float _speed;
	glm::vec2 _direction;
	glm::vec2 _position;
};

