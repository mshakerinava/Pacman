#pragma once

#include "cocos2d.h"

#include "Ghost.h"

#include "Direction.h"

class Maze;

USING_NS_CC;

class Blinky : public Ghost
{
public:
	static Blinky * create(Maze *maze);

protected:
	bool init(Maze *maze);
	
	Direction ai();

	void moveAnimation();	
};