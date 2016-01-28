#pragma once

#include "cocos2d.h"

#include "Entity.h"

class Maze;

USING_NS_CC;

class Ghost : public Entity
{
public:
	virtual ~Ghost();

	void update(float delta);

	void die();

protected:
	virtual bool init(Maze *maze);

	virtual void moveAnimation() = 0;
	void flashAnimation();
	void frightAnimation();
	void eyesAnimation();

	void fright();

	void killPacman();
	void setDirection(Direction newDirection);
	float moveTowards(Vec2 dest, float delta);

	virtual Direction ai() = 0;

	bool imprisoned;
};