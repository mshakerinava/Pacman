#pragma once

#include "cocos2d.h"

#include "Ghost.h"

#include "Direction.h"

class Maze;

USING_NS_CC;

class Pinky : public Ghost
{
public:
	static Pinky * create(Maze *maze);

protected:
	bool init(Maze *maze);

	Direction ai();

	void moveAnimation();
};