#include "Level.h"
#include <skrengine/Errors.h>
#include <fstream>

Level::Level(const std::string& fileName):
	_playerStartPosition(0.f)
{

	std::ifstream file;

	file.open(fileName);
	// Error checking
	if (file.fail())
	{
		skrengine::fatalError("Failed to open " + fileName);
	}

	//Throw away the first string in tmp
	std::string tmp;
	file >> tmp >> _numHumans;
	std::getline(file, tmp);

	while (std::getline(file, tmp))
	{
		_levelData.push_back(tmp);
	}

	_spriteBatch.init();

	_spriteBatch.begin();

	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	skrengine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	for (int y = 0; y < _levelData.size(); y++)
	{
		for (int x = 0; x < _levelData[y].size(); x++)
		{
			char tile = _levelData[y][x];

			// Get dest rect
			glm::vec4 destRect(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);
					
			switch (tile)
			{
			case 'W':
				_spriteBatch.draw(destRect, 
					uvRect,
					skrengine::ResourceManager::getTexture("Textures/tilesetSMS/tile077.png").id, 
					color, 
					0.0f);
				break;
			case '@':
				_levelData[y][x] = '.';
				_playerStartPosition.x = x * TILE_WIDTH;
				_playerStartPosition.y = y * TILE_WIDTH;
				x--;
				break;
			case 'E':
				_levelData[y][x] = '.';
				_enemyStartPositions.emplace_back(x * TILE_WIDTH, y * TILE_WIDTH);
				x--;
				break;
			case '.':
				_spriteBatch.draw(destRect,
					uvRect,
					skrengine::ResourceManager::getTexture("Textures/tileset8by8/tile060.png").id,
					color,
					0.0f);
				break;
			default:
				std::printf("Unexpected symbol %c at (%d, %d)", tile, x, y);
				break;
			}
		}
	}

	_spriteBatch.end();
}

Level::~Level()
{
}

void Level::draw()
{
	_spriteBatch.renderBatch();
}
