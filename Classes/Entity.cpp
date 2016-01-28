#include "Entity.h"

#include "Maze.h"

Entity::~Entity()
{
}

bool Entity::init(Maze * maze)
{
	this->maze = maze;
	maze->addChild(this);
	return true;
}