#pragma once

#include "cocos2d.h"

#include "Entity.h"
#include "Direction.h"
#include "Maze.h"

USING_NS_CC;

class Pacman : public Entity
{
public:
	static Pacman* create(Maze *maze);

	virtual void update(float delta) override;

	void control(Direction dir);
	
protected:
	static const int ENERGIZER_SCORE = 50;
	static const int DOT_SCORE = 10;
	static const int MAX_SPEED = 88/* px/sec */;

	bool init(Maze *maze);

	void applyIntension();
	void eat(GameTile *tile);
	float moveTowards(Vec2 dest, float delta);
	void energize();

	void eatingAnimation();
	void deathAnimation();
	void closeMouth();

	Maze *maze;
	
	Direction intensionDirection;
	Direction movingDirection;
	
	float speed;
	float facingAngle;

	int score = 0;
};