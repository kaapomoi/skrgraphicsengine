#include "Projectile.h"

Projectile::Projectile(glm::vec2 pos, glm::vec2 dir, float speed, int lifeTime) :
	_speed(0.0f),
	_direction(0.0f),
	_position(0.0f),
	_lifeTime(0)
{
	_position = pos;
	_direction = dir;
	_speed = speed;
	_lifeTime = lifeTime;
}

Projectile::~Projectile()
{

}

void Projectile::draw(skrengine::SpriteBatch& spriteBatch)
{
	skrengine::Color color;
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static skrengine::GLTexture texture = skrengine::ResourceManager::getTexture("Textures/tilesetsingular/tile023.png");

	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	glm::vec4 posAndSize = glm::vec4(_position.x, _position.y, 16, 16);

	spriteBatch.draw(posAndSize, uv, texture.id, color, 0.0f);
}

bool Projectile::update()
{
	_position += _direction * _speed;
	_lifeTime--;
	if (_lifeTime <= 0)
	{
		return true;
	}
	return false;
}
