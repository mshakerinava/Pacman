#include "GameTile.h"

#include "Maze.h"

GameTile * GameTile::create(Maze *maze, int row, int col, char token)
{
	GameTile *tile = new (std::nothrow) GameTile();
	if (tile && tile->init(maze, row, col, token))
	{
		tile->autorelease();
		return tile;
	}
	CC_SAFE_DELETE(tile);
	return nullptr;
}

bool GameTile::init(Maze *maze, int row, int col, char token)
{
	this->maze = maze;
	this->row = row;
	this->col = col;
	this->token = token;

	this->setPosition(Vec2(col * 8 + 4, row * 8 + 4));

	if (token == '-' || token == '.' || token == '@')
		this->legalSpace = true;
	else
		this->legalSpace = false;

	switch (token)
	{
	case '.':
		return Sprite::initWithFile("images/spritesheet.png", Rect(2, 191, 8, 8));
	case '@':
		return Sprite::initWithFile("images/spritesheet.png", Rect(2, 182, 8, 8));
	default:
		/* Completely transparent */
		return Sprite::initWithFile("images/spritesheet.png", Rect(314, 272, 8, 8));
		/* TODO : Better idea? */
	}
}

char GameTile::getToken()
{
	return this->token;
}

int GameTile::getRow()
{
	return this->row;
}

int GameTile::getCol()
{
	return this->col;
}

bool GameTile::isEdible()
{
	if (this->token == '.' || this->token == '@')
		return true;
	return false;
}

bool GameTile::isDeadSpace()
{
	return !this->isLegalSpace();
}

bool GameTile::isLegalSpace()
{
	return legalSpace;
}

bool GameTile::isIntersection()
{
	int ways = 0;
	if (intersection == -1)
	{
		for (int d = -1; d <= 1; d += 2)
		{
			if (maze->getTile(row + d, col) && maze->getTile(row + d, col)->isLegalSpace())
				++ways;
			if (maze->getTile(row, col + d) && maze->getTile(row, col + d)->isLegalSpace())
				++ways;
		}
		intersection = ways > 2 ? 1 : 0;
	}
	return intersection;
}

void GameTile::eat()
{
	if (this->token == '.' || this->token == '@')
		this->token = '-';
	this->setOpacity(0);
}
