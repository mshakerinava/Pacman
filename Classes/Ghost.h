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
	void fright();
	
protected:
	static const int FRIGHT_TIMES[];

	virtual bool init(Maze *maze);

	int getFrightTime();

	virtual void moveAnimation() = 0;
	void flashAnimation();
	void frightAnimation();
	void eyesAnimation();
	
	enum class State
	{
		NORMAL,
		FRIGHTENED,
		DEAD
	};

	void setState(State state);
	
	enum class Movement
	{
		NORMAL,
		FRIGHTENED,
		TUNNEL,
		ESCAPE,
		DEAD
	};

	void setMovement(Movement movement);

	void killPacman();
	void setDirection(Direction direction);
	float moveTowards(Vec2 dest, float delta);

	virtual Direction ai() = 0;

	bool imprisoned;
	Movement movement;
	State state;
};