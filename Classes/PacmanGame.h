#pragma once

#include "cocos2d.h"

#include <string>

#include "Maze.h"
#include "EventManager.h"

USING_NS_CC;

class PacmanGame : public Sprite
{
public:
	static PacmanGame * create();

	void update(float delta);

	int getLevel();

	void addScore(int score);
	
	void control(Direction dir);
	void pacmanDied();

private:
	bool init();

	void showReady();
	void hideReady();
	void showGameover();
	void hideGameover();
	void loseLife();
	void resetLevel();
	
	Maze *maze;
	Sprite *ready;
	Sprite *gameover;
	Sprite *extraLifes[3];
	EventManager *eventManager;

	enum class State
	{
		READY,
		PLAY,
		GRIEF,
		DEATH,
		GAMEOVER
	};

	void setState(State state);

	State state;
	int level = 1;
	int score = 0;
	int numberOfExtraLifes = 2;
};