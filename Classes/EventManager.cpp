#include "EventManager.h"

#include "PacmanGame.h"

EventManager * EventManager::create(PacmanGame * game)
{
	EventManager *eventManager = new (std::nothrow) EventManager();
	if (eventManager && eventManager->init(game))
	{
		eventManager->autorelease();
		return eventManager;
	}
	CC_SAFE_DELETE(eventManager);
	return nullptr;
}

void EventManager::addEventListeners()
{
	auto listener = EventListenerKeyboard::create();

	listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
	{
		log("Key with keycode %d pressed", keyCode);
		auto dir = KeyCodeToDirection(keyCode);
		game->control(dir);
		return true;
	};

	auto touchListener = EventListenerTouchOneByOne::create();

	//touchListener->on

	game->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, game);
}

bool EventManager::init(PacmanGame *game)
{
	this->game = game;
	game->addChild(this);
	this->addEventListeners();
	return true;
}

Direction EventManager::KeyCodeToDirection(EventKeyboard::KeyCode keyCode)
{
	Direction result;
	
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_A:
		result = Direction::LEFT;
		break;
	
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_D:
		result = Direction::RIGHT;
		break;
	
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	case EventKeyboard::KeyCode::KEY_W:
		result = Direction::UP;
		break;
	
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case EventKeyboard::KeyCode::KEY_S:
		result = Direction::DOWN;
		break;
	}

	return result;
}