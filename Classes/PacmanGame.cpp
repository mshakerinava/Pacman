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
	if (state == State::READY)
	{
		maze->pause();
	}
	else if (state == State::PLAY)
	{
		maze->update(delta);
	}
}

int PacmanGame::getLevel()
{
	return this->level;
}

void PacmanGame::addScore(int score)
{
	score += score;
}

void PacmanGame::pacmanDied()
{
	this->setState(State::GRIEF);
}

bool PacmanGame::init()
{
	srand(time(NULL));
	
	this->maze = Maze::create("classic", this);
	
	this->eventManager = EventManager::create(this);
	this->ready = Sprite::create("images/spritesheet.png", Rect(202, 1, 48, 8));
	this->gameover = Sprite::create("images/spritesheet.png", Rect(12, 191, 80, 8));
	for (int i = 0; i < 3; ++i)
		this->extraLifes[i] = Sprite::create("images/spritesheet.png", Rect(84, 164, 11, 11));
	
	this->addChild(ready);
	this->addChild(gameover);
	for (int i = 0; i < 3; ++i)
		this->addChild(extraLifes[i]);

	this->ready->setPosition(maze->getTextMidPos());
	this->gameover->setPosition(maze->getTextMidPos());
	for (int i = 0; i < 3; ++i)
		this->extraLifes[i]->setPosition(maze->getLifeLeftPos() + Vec2(i * 16, 0));

	this->hideReady();
	this->hideGameover();
	this->extraLifes[2]->setOpacity(0);

	initWithTexture(nullptr, maze->getTextureRect());
	this->setState(State::READY);
	return true;
}

void PacmanGame::showReady()
{
	this->ready->setOpacity(255);
}

void PacmanGame::hideReady()
{
	this->ready->setOpacity(0);
}

void PacmanGame::showGameover()
{
	this->gameover->setOpacity(255);
}

void PacmanGame::hideGameover()
{
	this->gameover->setOpacity(0);
}

void PacmanGame::loseLife()
{
	numberOfExtraLifes--;
	
	for (int i = 0; i < 3; ++i)
		if (i < numberOfExtraLifes)
			extraLifes[i]->setOpacity(255);
		else
			extraLifes[i]->setOpacity(0);
	
	if (numberOfExtraLifes == -1)
		this->setState(State::GAMEOVER);
	else
		this->resetLevel();
}

void PacmanGame::resetLevel()
{
	maze->resetEntities();
	this->setState(State::READY);
}

void PacmanGame::control(Direction dir)
{
	maze->control(dir);
}

void PacmanGame::setState(State state)
{
	/* Exit Previous State */
	if (this->state == State::READY)
	{
		this->hideReady();
		maze->resume();
	}

	this->state = state;

	/* Enter New State */
	if (this->state == State::READY)
	{
		maze->pause();
		this->showReady();
		this->runAction(Sequence::create(
			DelayTime::create(2.0f),
			CallFunc::create([&]() { this->setState(State::PLAY); }),
			nullptr));
	}
	else if (this->state == State::GRIEF)
	{
		//maze->stopEntities();   TODO: This method is Buggy!!
		this->runAction(Sequence::create(
			DelayTime::create(1.0f),
			CallFunc::create([&]() { this->setState(State::DEATH); }),
			nullptr));
	}
	else if (this->state == State::DEATH)
	{
		maze->hideGhosts();
		maze->deathAnimation();
		this->runAction(Sequence::create(
			DelayTime::create(2.0f),
			CallFunc::create([&]() { this->loseLife(); }),
			nullptr));
	}
	else if (this->state == State::GAMEOVER)
	{
		maze->hidePacman();
		this->showGameover();
	}
}
