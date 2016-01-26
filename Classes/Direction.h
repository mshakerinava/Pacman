#pragma once

#include "cocos2d.h"

USING_NS_CC;

/*
 * Direction has five possible states.
 * Direction is immutable.
 */

class Direction
{
public:
	static const Direction NONE;
	static const Direction UP;
	static const Direction LEFT;
	static const Direction DOWN;
	static const Direction RIGHT;

	Direction(Vec2 vec);
	Direction(int val = -1);
	Direction(float dx, float dy);
	
	Vec2 getvec2() const;
	int getval() const;
	int getdx() const;
	int getdy() const;

	Direction opposite();
	
	bool friend operator==(const Direction & lhs, const Direction & rhs);
	bool friend operator!=(const Direction & lhs, const Direction & rhs);

protected:
	Vec2 vec2;
	int val;
};