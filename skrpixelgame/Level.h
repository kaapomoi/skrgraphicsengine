#pragma once
#include <string>
#include <vector>

#include <skrengine/SpriteBatch.h>
#include <skrengine/ResourceManager.h>

const int TILE_WIDTH = 16;

class Level
{
public:
	// Load the level
	Level(const std::string& fileName);
	~Level();

	void draw();

	// Getters 
	int getWidth() const { return _levelData[0].size(); }
	int getHeight() const { return _levelData.size(); }
	int getNumHumans() const { return _numHumans; }
	const std::vector<std::string>& getLevelData() const { return _levelData; }
	glm::vec2 getPlayerStartPos() const { return _playerStartPosition; }
	const std::vector<glm::vec2>& getEnemiesStartPos() const { return _enemyStartPositions; }
private:
	std::vector<std::string> _levelData;


	int _numHumans;
	skrengine::SpriteBatch _spriteBatch;

	glm::vec2 _playerStartPosition;
	std::vector<glm::vec2> _enemyStartPositions;
};

