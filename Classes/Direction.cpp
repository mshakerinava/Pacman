#include "Direction.h"

const Direction Direction::NONE  = Direction(-1);
const Direction Direction::UP    = Direction(0);
const Direction Direction::LEFT  = Direction(1);
const Direction Direction::DOWN  = Direction(2);
const Direction Direction::RIGHT = Direction(3);

Direction::Direction(Vec2 vec)
{
	if (vec.isZero())
		*this = NONE;
	else if (M_PI * -3.0 / 4.0 <= vec.getAngle() && vec.getAngle() <= M_PI * -1.0 / 4.0)
		*this = DOWN;
	else if (M_PI * -1.0 / 4.0 <= vec.getAngle() && vec.getAngle() <= M_PI * 1.0 / 4.0)
		*this = RIGHT;
	else if (M_PI * 1.0 / 4.0 <= vec.getAngle() && vec.getAngle() <= M_PI * 3.0 / 4.0)
		*this = UP;
	else
		*this = LEFT;
}

Direction::Direction(int val/* = -1 */)
{
	if (val < 0)
		val = -1;
	
	val %= 4;

	this->val = val;
	
	switch (val)
	{
	case -1:
		vec2 = Vec2(0, 0);
		break;
	case 0:
		vec2 = Vec2(0, 1);
		break;
	case 1:
		vec2 = Vec2(-1, 0);
		break;
	case 2:
		vec2 = Vec2(0, -1);
		break;
	case 3:
		vec2 = Vec2(1, 0);
		break;
	}
}

Direction::Direction(float dx, float dy)
{
	*this = Direction(Vec2(dx, dy));
}

Vec2 Direction::getvec2() const
{
	return this->vec2;
}

int Direction::getval() const
{
	return this->val;
}

int Direction::getdx() const
{
	return this->vec2.x;
}

int Direction::getdy() const
{
	return this->vec2.y;
}

Direction Direction::opposite()
{
	return Direction(this->getval() == -1 ? -1 : this->getval() + 2);
}

bool operator==(const Direction & lhs, const Direction & rhs)
{
	return lhs.getval() == rhs.getval();
}

bool operator!=(const Direction & lhs, const Direction & rhs)
{
	return !(lhs == rhs);
}
