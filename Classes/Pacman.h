#pragma once

#include "cocos2d.h"

#include "Entity.h"

#include "Direction.h"
#include "GameTile.h"

class Maze;

USING_NS_CC;

class Pacman : public Entity
{
public:
	static Pacman * create(Maze *maze);
	
	void update(float delta);

	void closeMouth();
	void control(Direction dir);
	void die();

	void deathAnimation();

protected:
	static const int ENERGIZER_SCORE = 50;
	static const int DOT_SCORE = 10;
	
	bool init(Maze *maze);

	enum class State
	{
		NORMAL,
		ENERGIZED,
		DEAD
	};

	State state;

	void setState(State state);

	void eat(GameTile *tile);

	void applyIntension();
	float moveTowards(Vec2 dest, float delta);
	
	void eatingAnimation();
	
	Direction intensionDirection;
	float facingAngle;
};