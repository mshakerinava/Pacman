#include "Entity.h"

#include "Maze.h"

void Entity::stopMoving()
{
	this->speed = 0;
}

Entity::~Entity()
{
}

bool Entity::init(Maze * maze)
{
	this->maze = maze;
	maze->addChild(this);
	return true;
}