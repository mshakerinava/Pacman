#pragma once

#include "cocos2d.h"

#include "Maze.h"

USING_NS_CC;

class PacmanGame : public Sprite
{
public:
	static PacmanGame * create();

	void update(float delta);

private:
	bool init();

	Maze *maze;
};