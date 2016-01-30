#include "Clyde.h"

#include "Maze.h"

USING_NS_CC;

Clyde * Clyde::create(Maze *maze)
{
	Clyde *clyde = new (std::nothrow) Clyde();
	if (clyde && clyde->init(maze))
	{
		clyde->autorelease();
		return clyde;
	}
	CC_SAFE_DELETE(clyde);
	return nullptr;
}

bool Clyde::init(Maze *maze)
{
	Ghost::init(maze);
	this->setDirection(Direction::UP);
	this->setPosition(maze->getClydeStartPos());
	return Sprite::initWithFile("images/spritesheet.png", Rect(103, 143, 14, 14));
}

void Clyde::moveAnimation()
{
	this->stopAllActions();
	if (this->movingDirection == Direction::UP)
	{
		/* Create SpriteFrames */
		Vector<SpriteFrame*> animFrames;
		animFrames.reserve(2);
		animFrames.pushBack(SpriteFrame::create("images/spritesheet.png", Rect(3 , 143, 14, 14)));
		animFrames.pushBack(SpriteFrame::create("images/spritesheet.png", Rect(23, 143, 14, 14)));
		/* Create Animation */
		Animation* animation = Animation::createWithSpriteFrames(animFrames, 1.0f / 6);
		/* Create Action */
		Animate* animate = Animate::create(animation);
		/* Run and repeat Action forever */
		this->runAction(RepeatForever::create(animate));
	}
	else if (this->movingDirection == Direction::DOWN)
	{
		/* Create SpriteFrames */
		Vector<SpriteFrame*> animFrames;
		animFrames.reserve(2);
		animFrames.pushBack(SpriteFrame::create("images/spritesheet.png", Rect(43, 143, 14, 14)));
		animFrames.pushBack(SpriteFrame::create("images/spritesheet.png", Rect(63, 143, 14, 14)));
		/* Create Animation */
		Animation* animation = Animation::createWithSpriteFrames(animFrames, 1.0f / 6);
		/* Create Action */
		Animate* animate = Animate::create(animation);
		/* Run and repeat Action forever */
		this->runAction(RepeatForever::create(animate));
	}
	else if (this->movingDirection == Direction::LEFT)
	{
		/* Create SpriteFrames */
		Vector<SpriteFrame*> animFrames;
		animFrames.reserve(2);
		animFrames.pushBack(SpriteFrame::create("images/spritesheet.png", Rect(83 , 143, 14, 14)));
		animFrames.pushBack(SpriteFrame::create("images/spritesheet.png", Rect(103, 143, 14, 14)));
		/* Create Animation */
		Animation* animation = Animation::createWithSpriteFrames(animFrames, 1.0f / 6);
		/* Create Action */
		Animate* animate = Animate::create(animation);
		/* Run and repeat Action forever */
		this->runAction(RepeatForever::create(animate));
	}
	else if (this->movingDirection == Direction::RIGHT)
	{
		/* Create SpriteFrames */
		Vector<SpriteFrame*> animFrames;
		animFrames.reserve(2);
		animFrames.pushBack(SpriteFrame::create("images/spritesheet.png", Rect(123, 143, 14, 14)));
		animFrames.pushBack(SpriteFrame::create("images/spritesheet.png", Rect(143, 143, 14, 14)));
		/* Create Animation */
		Animation* animation = Animation::createWithSpriteFrames(animFrames, 1.0f / 6);
		/* Create Action */
		Animate* animate = Animate::create(animation);
		/* Run and repeat Action forever */
		this->runAction(RepeatForever::create(animate));
	}
}

Direction Clyde::ai()
{
	std::vector<Direction> possibleDirections;
	for (int i = 0; i < 4; ++i)
	{
		if (Direction(i) == movingDirection.opposite())
			continue;
		GameTile *nextTile = maze->getTile(this->getPosition() + Direction(i).getvec2() * 8);
		if (nextTile && nextTile->isLegalSpace())
			possibleDirections.push_back(Direction(i));
	}
	if (possibleDirections.empty())
		return this->movingDirection.opposite();
	int i = rand() % (int)possibleDirections.size();
	return possibleDirections[i];
}