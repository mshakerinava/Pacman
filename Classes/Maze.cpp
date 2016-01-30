#include "Maze.h"

#include "PacmanGame.h"

#include <iostream>

#include "EventManager.h"

Maze * Maze::create(std::string mazeName, PacmanGame *game)
{
	Maze *maze = new (std::nothrow) Maze();
	if (maze && maze->init(mazeName, game))
	{
		maze->autorelease();
		return maze;
	}
	CC_SAFE_DELETE(maze);
	return nullptr;
}

int Maze::getWidth()
{
	return width;
}

int Maze::getHeight()
{
	return height;
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

GameTile * Maze::getPacmanTile()
{
	return this->getTile(pacman->getPosition());
}

int Maze::getLevel()
{
	return game->getLevel();
}

Vec2 Maze::getPacmanStartPos()
{
	return pacmanStartPos;
}

Vec2 Maze::getBlinkyStartPos()
{
	return blinkyStartPos;
}

Vec2 Maze::getPinkyStartPos()
{
	return pinkyStartPos;
}

Vec2 Maze::getInkyStartPos()
{
	return inkyStartPos;
}

Vec2 Maze::getClydeStartPos()
{
	return clydeStartPos;
}

Vec2 Maze::getTextMidPos()
{
	return textMidPos;
}

Vec2 Maze::getLifeLeftPos()
{
	return lifeLeftPos;
}

void Maze::killPacman()
{
	pacman->die();
	game->pacmanDied();
}

void Maze::deathAnimation()
{
	pacman->deathAnimation();
}

void Maze::control(Direction dir)
{
	pacman->control(dir);
}

void Maze::stopEntities()
{
	blinky->stopMoving();
	pinky->stopMoving();
	inky->stopMoving();
	clyde->stopMoving();
	pacman->stopMoving();
}

void Maze::resetEntities()
{
	if (blinky)
		this->removeChild(blinky, true);
	blinky = Blinky::create(this);
	
	if (pinky)
		this->removeChild(pinky, true);
	pinky = Pinky::create(this);
	
	if (inky)
		this->removeChild(inky, true);
	inky = Inky::create(this);
	
	if (clyde)
		this->removeChild(clyde, true);
	clyde = Clyde::create(this);
	
	if (pacman)
		this->removeChild(pacman, true);
	pacman = Pacman::create(this);
}

void Maze::hideGhosts()
{
	blinky->setOpacity(0);
	pinky->setOpacity(0);
	inky->setOpacity(0);
	clyde->setOpacity(0);
}

void Maze::frightenGhosts()
{
	blinky->fright();
	pinky->fright();
	inky->fright();
	clyde->fright();
}

void Maze::hidePacman()
{
	this->pacman->setOpacity(0);
}

void Maze::addScore(int score)
{
	game->addScore(score);
}

bool Maze::init(std::string mazeName, PacmanGame *game)
{
	this->game = game;
	game->addChild(this);

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
	
	for (int i = 0; i < 7; ++i)
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
		else if (label == "life")
			this->lifeLeftPos = Vec2(x, y);
	}
	
	this->setPosition(width * 4, height * 4);
	this->resetEntities();

	return Sprite::initWithFile("mazes/" + mazeName + "/sprite.png");
}

void Maze::update(float delta)
{
	for (int i = 0; i < (int)this->getChildren().size(); ++i)
		this->getChildren().at(i)->update(delta);
}

void Maze::pause()
{
	pacman->closeMouth();
	for (int i = 0; i < (int)this->getChildren().size(); ++i)
		this->getChildren().at(i)->pause();
	//tiles[29][1]->resume();
}

void Maze::resume()
{
	for (int i = 0; i < (int)this->getChildren().size(); ++i)
		this->getChildren().at(i)->resume();
}
