#include "PacmanGame.h"

PacmanGame * PacmanGame::create()
{
	PacmanGame *game = new (std::nothrow) PacmanGame();
	if (game && game->init())
	{
		game->autorelease();
		return game;
	}
	CC_SAFE_DELETE(game);
	return nullptr;
}

void PacmanGame::update(float delta)
{
	maze->update(delta);
}

bool PacmanGame::init()
{
	srand(time(NULL));
	this->maze = Maze::create("classic", this);
	if (this->maze == nullptr)
		return false;
	maze->set
	return true;
}