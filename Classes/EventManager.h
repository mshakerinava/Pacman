#pragma once

#include "cocos2d.h"

#include "Pacman.h"
#include "Direction.h"

USING_NS_CC;

class EventManager
{
public:
	static EventManager * getInstance();
	
	void addEventListeners(Node *node, Pacman *pacman);
	
protected:
	EventManager();
	virtual ~EventManager();
	
	void init();

	static Direction KeyCodeToDirection(EventKeyboard::KeyCode keyCode);
};