#include "Level.h"
#include <skrengine/Errors.h>
#include <fstream>

#include <vector>
#include <random>
#include <ctime>

Level::Level(const std::string& fileName, const std::string & bgFileName) :
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

	file.close();

	std::string bg;
	file.open(bgFileName);

	if (file.fail())
	{
		skrengine::fatalError("Failed to open " + bgFileName);
	}

	while (std::getline(file, bg))
	{
		_bgLevelData.push_back(bg);
	}

	file.close();

	_spriteBatch.init();

	_spriteBatch.begin();


	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	skrengine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	GLuint texture;

	std::mt19937 randomEngine2;
	randomEngine2.seed(time(NULL));

	std::uniform_int_distribution<int> randGrass(1, 50);

	// Background no collision tile setup
	for (int y = _bgLevelData.size() - 1; y >= 0; y--)
	{
		for (int x = 0; x < _bgLevelData[y].size(); x++)
		{
			char tile = _bgLevelData[y][x];

			// Get dest rect
			glm::vec4 destRect(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);

			switch (tile)
			{
			case '1':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Interior1.png").id;
				break;
			case '2':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Interior2.png").id;
				break;
			case '3':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Interior3.png").id;
				break;
			case '4':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Interior4.png").id;
				break;
			case '5':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Interior5.png").id;
				break;
			case '6':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Interior6.png").id;
				break;
			case '7':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Interior7.png").id;
				break;
			case '8':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Interior8.png").id;
				break;
			case '9':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Interior9.png").id;
				break;
			case 'A':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/InteriorA.png").id;
				break;
			case 'B':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/InteriorB.png").id;
				break;
			case 'C':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/InteriorC.png").id;
				break;
				// wall
			case 'D':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Wall.png").id;
				break;
			case 'E':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/WallLeft.png").id;
				break;
			case 'F':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/WallEnd.png").id;
				break;
			case 'G':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Floor.png").id;
				break;
			case 'H':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Table.png").id;
				break;
			case 'I':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/InteriorI.png").id;
				break;


				// dungeon textures
			case ',':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Dungeon/Black.png").id;
				break;
			case 'a':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Dungeon/Wall1.png").id;
				break;
			case 'b':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Dungeon/WallSideMid.png").id;
				break;
			case 'c':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Dungeon/WallSideLeft.png").id;
				break;
			case 'd':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Dungeon/WallSideRight.png").id;
				break;
			case 'w':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Dungeon/Cobweb.png").id;
				break;

			case 'i':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Dungeon/PlankUp.png").id;
				break;
			case 'o':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Dungeon/PlankLeft.png").id;
				break;
			case 'p':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Dungeon/PlankDownLeft.png").id;
				break;

			case 'e':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Dungeon/Wright.png").id;
				break;
			case 'q':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Dungeon/Wleft.png").id;
				break;
			case 's':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Dungeon/Wup.png").id;
				break;
			case 'f':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Dungeon/Wdown.png").id;
				break;
			case 'h':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Dungeon/Chest.png").id;
				break;

			case 'r':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Dungeon/Vine.png").id;
				break;

			case 'v':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Dungeon/WallDownLeft.png").id;
				break;
			case 'n':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Dungeon/WallUpLeft.png").id;
				break;
			case 'm':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Dungeon/WallDownRight.png").id;
				break;
			case 'x':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Dungeon/WallUpRight.png").id;
				break;


			case 'u':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Dungeon/WallUp.png").id;
				break;
			case 'g':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Dungeon/Gray.png").id;
				break;

			case '.':
				if (randGrass(randomEngine2) < 2)
				{
					texture = skrengine::ResourceManager::getTexture("Textures/tileset8by8/tile060.png").id;
				}
				else
				{
					texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/tile137.png").id;
				}
				break;

			default:
				std::printf("Unexpected symbol %c at (%d, %d)", tile, x, y);
				break;
			}

			_spriteBatch.draw(destRect,
				uvRect,
				texture,
				color,
				0.0f);
		}
	}

	bool skipTexture = false;

	// Actual level with collision setup
	for (int y = _levelData.size() - 1; y >= 0; y--)
	{
		for (int x = 0; x < _levelData[y].size(); x++)
		{
			skipTexture = false;
			char tile = _levelData[y][x];

			// Get dest rect
			glm::vec4 destRect(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);
					
			switch (tile)
			{
			case 'W':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/tile137.png").id;
				break;
			case '@':
				_levelData[y][x] = '.';
				_playerStartPosition.x = x * TILE_WIDTH;
				_playerStartPosition.y = y * TILE_WIDTH;
				x--;
				skipTexture = true;
				break;
			case '#':
				_levelData[y][x] = '.';
				skipTexture = true;
				_enemyStartPositions.emplace_back(x * TILE_WIDTH, y * TILE_WIDTH);
				x--;
				break;
			case '1':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Interior1.png").id;
				break;
			case '2':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Interior2.png").id;
				break;
			case '3':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Interior3.png").id;
				break;
			case '4':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Interior4.png").id;
				break;
			case '5':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Interior5.png").id;
				break;
			case '6':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Interior6.png").id;
				break;
			case '7':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Interior7.png").id;
				break;
			case '8':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Interior8.png").id;
				break;
			case '9':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Interior9.png").id;
				break;
			case 'A':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/InteriorA.png").id;
				break;
			case 'B':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/InteriorB.png").id;
				break;
			case 'C':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/InteriorC.png").id;
				break;
				// wall
			case 'D':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Wall.png").id;
				break;
			case 'E':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/WallLeft.png").id;
				break;
			case 'F':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/WallEnd.png").id;
				break;
			case 'G':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Floor.png").id;
				break;
			case 'H':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Table.png").id;
				break;
			case 'I':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/InteriorI.png").id;
				break;


			// dungeon textures
			case ',':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Dungeon/Black.png").id;
				break;
			case 'a':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Dungeon/Wall1.png").id;
				break;
			case 'b':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Dungeon/WallSideMid.png").id;
				break;
			case 'c':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Dungeon/WallSideLeft.png").id;
				break;
			case 'd':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Dungeon/WallSideRight.png").id;
				break;
			case 'w':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Dungeon/Cobweb.png").id;
				break;

			case 'i':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Dungeon/PlankUp.png").id;
				break;
			case 'o':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Dungeon/PlankLeft.png").id;
				break;
			case 'p':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Dungeon/PlankDownLeft.png").id;
				break;
			
			case 'e':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Dungeon/Wright.png").id;
				break;
			case 'q':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Dungeon/Wleft.png").id;
				break;
			case 's':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Dungeon/Wup.png").id;
				break;
			case 'f':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Dungeon/Wdown.png").id;
				break;
			case 'h':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Dungeon/Chest.png").id;
				break;

			case 'r':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Dungeon/Vine.png").id;
				break;

			case 'v':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Dungeon/WallDownLeft.png").id;
				break;
			case 'n':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Dungeon/WallUpLeft.png").id;
				break;
			case 'm':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Dungeon/WallDownRight.png").id;
				break;
			case 'x':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Dungeon/WallUpRight.png").id;
				break;


			case 'u':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Dungeon/WallUp.png").id;
				break;
			case 'g':
				texture = skrengine::ResourceManager::getTexture("Textures/goodtiles/Dungeon/Gray.png").id;
				break;
			case '.':
				skipTexture = true;
				break;
			default:
				std::printf("Unexpected symbol %c at (%d, %d)", tile, x, y);
				break;
			}

			if (!skipTexture)
			{
				_spriteBatch.draw(destRect,
					uvRect,
					texture,
					color,
					0.0f);
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
