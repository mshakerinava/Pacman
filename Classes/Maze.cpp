#include "Maze.h"

#include <iostream>

Maze* Maze::create(std::string mazeName)
{
	Maze *maze = new (std::nothrow) Maze();
	if (maze && maze->init(mazeName))
	{
		maze->autorelease();
		return maze;
	}
	CC_SAFE_DELETE(maze);
	return nullptr;
}

GameTile * Maze::getTile(Vec2 pos)
{
	/* Tunnel */
	if (pos.x > width)
		pos.x -= width * 8;
	if (pos.x < 0)
		pos.x += width * 8;
	
	int row = pos.y / 8;
	int col = pos.x / 8;
	return getTile(row, col);
}

GameTile * Maze::getTile(int row, int col)
{
	/* Tunnel */
	col %= width;
	if (col < 0)
		col += width;

	if(0 <= row && row < height && 0 <= col && col < width)
		return tiles[row][col];
	
	return nullptr;
}

Vec2 Maze::getPacmanStartPos()
{
	return pacmanStartPos;
}

bool Maze::init(std::string mazeName)
{
	std::string tilemap = FileUtils::getInstance()->getStringFromFile("mazes/" + mazeName + "/tilemap.txt");
	std::stringstream ss(tilemap);
	ss >> this->width >> this->height;
	
	tiles.resize(height);
	/* Origin is Bottom Left in Cocos */
	for (int i = height - 1; i >= 0; --i)
	{
		tiles[i].resize(width);
		for (int j = 0; j < width; ++j)
		{
			char token;
			ss >> token;
			tiles[i][j] = GameTile::create(this, i, j, token);
			this->addChild(tiles[i][j]);
		}
	}
	for (int i = 0; i < 5; ++i)
	{
		std::string label;
		ss >> label;
		int x, y;
		ss >> x >> y;
		y = height * 8 - y;
		if (label == "pacman")
			this->pacmanStartPos = Vec2(x, y);
		else if (label == "blinky")
			this->blinkyStartPos = Vec2(x, y);
		else if (label == "pinky")
			this->pinkyStartPos = Vec2(x, y);
		else if (label == "inky")
			this->inkyStartPos = Vec2(x, y);
		else if (label == "clyde")
			this->clydeStartPos = Vec2(x, y);
		else if (label == "text")
			this->textMidPos = Vec2(x, y);
	}
	return Sprite::initWithFile("mazes/" + mazeName + "/sprite.png");
}

void Maze::update(float delta)
{
	for (int i = 0; i < (int)this->getChildren().size(); ++i)
		this->getChildren().at(i)->update(delta);
}
