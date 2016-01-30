#pragma once

#include "cocos2d.h"

#include "Direction.h"

class PacmanGame;

USING_NS_CC;

class EventManager : public Node
{
public:
	static EventManager * create(PacmanGame *game);
		
protected:
	static Direction KeyCodeToDirection(EventKeyboard::KeyCode keyCode);
	
	bool init(PacmanGame *game);
	
	void addEventListeners();

	PacmanGame *game;
};