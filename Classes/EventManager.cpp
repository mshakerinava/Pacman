#include "EventManager.h"

static EventManager *eventManagerInstance = nullptr;

EventManager * EventManager::getInstance()
{
	if (!eventManagerInstance)
	{
		eventManagerInstance = new EventManager();
		eventManagerInstance->init();
	}
	return eventManagerInstance;
}

void EventManager::addEventListeners(Node *node, Pacman *pacman)
{
	auto listener = EventListenerKeyboard::create();

	listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
	{
		log("Key with keycode %d pressed", keyCode);
		auto dir = KeyCodeToDirection(keyCode);
		pacman->control(dir);
		return true;
	};

	node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, node);
}

EventManager::EventManager()
{
}

EventManager::~EventManager()
{
	eventManagerInstance = nullptr;
}

void EventManager::init()
{
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