#pragma once

#include "cocos2d.h"

#include "Ghost.h"

#include "Direction.h"

class Maze;

USING_NS_CC;

class Clyde : public Ghost
{
public:
	static Clyde * create(Maze *maze);

protected:
	bool init(Maze *maze);

	Direction ai();

	void moveAnimation();
};