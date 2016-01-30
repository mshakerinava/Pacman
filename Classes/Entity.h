#pragma once

#include "cocos2d.h"

#include "Direction.h"

class Maze;

USING_NS_CC;

class Entity : public Sprite
{	
public:
	virtual void stopMoving();
	
protected:
	static const int MAX_SPEED = 88/* px/sec */;

	virtual ~Entity();

	virtual bool init(Maze *maze);
	
	virtual float moveTowards(Vec2 dest, float delta) = 0;

	virtual void die() = 0;

	Maze *maze;

	Direction movingDirection;
	float speed;
};