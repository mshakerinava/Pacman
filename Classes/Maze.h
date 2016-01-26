#pragma once

#include "cocos2d.h"

#include "GameTile.h"

USING_NS_CC;

class Maze : public Sprite
{
public:
	static Maze * create(std::string mazeName);

	GameTile * getTile(Vec2 pos);
	GameTile * getTile(int row, int col);

	Vec2 getPacmanStartPos();

protected:
	bool init(std::string mazeName);
	void update(float) override;

	int width, height;
	std::vector< std::vector<GameTile *> > tiles;

	Vec2 pacmanStartPos;
	Vec2 blinkyStartPos;
	Vec2 pinkyStartPos;
	Vec2 inkyStartPos;
	Vec2 clydeStartPos;
	Vec2 textMidPos;
};