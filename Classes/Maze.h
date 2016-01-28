#pragma once

#include "cocos2d.h"

#include "GameTile.h"

#include "Pacman.h"
#include "Blinky.h"
#include "Pinky.h"
#include "Inky.h"
#include "Clyde.h"

class PacmanGame;

USING_NS_CC;

class Maze : public Sprite
{
public:
	static Maze * create(std::string mazeName, PacmanGame *game);

	void update(float) override;

	int getWidth();
	int getHeight();

	GameTile * getTile(Vec2 pos);
	GameTile * getTile(int row, int col);

	GameTile * getPacmanTile();

	Vec2 getPacmanStartPos();
	Vec2 getBlinkyStartPos();
	Vec2 getPinkyStartPos();
	Vec2 getInkyStartPos();
	Vec2 getClydeStartPos();
	Vec2 getTextMidPos();

	void killPacman();

protected:
	bool init(std::string mazeName, PacmanGame *game);
	
	PacmanGame *game;

	Pacman *pacman;
	Blinky *blinky;
	Pinky *pinky;
	Inky *inky;
	Clyde *clyde;

	int width, height;
	std::vector< std::vector<GameTile *> > tiles;

	Vec2 pacmanStartPos;
	Vec2 blinkyStartPos;
	Vec2 pinkyStartPos;
	Vec2 inkyStartPos;
	Vec2 clydeStartPos;
	Vec2 textMidPos;
};