#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Character
{
public:
	Character();
	virtual ~Character();
	
	virtual void update(float delta) = 0;

protected:
	Vec2 tile;
};

