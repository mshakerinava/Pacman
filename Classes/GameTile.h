#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Maze;

class GameTile : public Sprite
{
public:
	static GameTile * create(Maze *maze, int row, int col, char token = '-');

	char getToken();
	int getRow();
	int getCol();
	
	bool isEdible();
	bool isDeadSpace();
	bool isLegalSpace();
	bool isIntersection();

	void eat();

private:
	bool init(Maze *maze, int row, int col, char token);

	Maze *maze;
	char token;
	int row, col;
	bool legalSpace;
	int intersection = -1; /* lazy */
};