#include "Inky.h"

#include "Maze.h"

#include "GameTile.h"

USING_NS_CC;

Inky * Inky::create(Maze *maze)
{
	Inky *inky = new (std::nothrow) Inky();
	if (inky && inky->init(maze))
	{
		inky->autorelease();
		return inky;
	}
	CC_SAFE_DELETE(inky);
	return nullptr;
}

bool Inky::init(Maze *maze)
{
	Ghost::init(maze);
	this->setDirection(Direction::UP);
	this->setPosition(maze->getInkyStartPos());
	return Sprite::initWithFile("images/spritesheet.png", Rect(103, 123, 14, 14));
}

void Inky::moveAnimation()
{
	this->stopAllActions();
	if (this->movingDirection == Direction::UP)
	{
		/* Create SpriteFrames */
		Vector<SpriteFrame*> animFrames;
		animFrames.reserve(2);
		animFrames.pushBack(SpriteFrame::create("images/spritesheet.png", Rect(3, 123, 14, 14)));
		animFrames.pushBack(SpriteFrame::create("images/spritesheet.png", Rect(23, 123, 14, 14)));
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
		animFrames.pushBack(SpriteFrame::create("images/spritesheet.png", Rect(43, 123, 14, 14)));
		animFrames.pushBack(SpriteFrame::create("images/spritesheet.png", Rect(63, 123, 14, 14)));
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
		animFrames.pushBack(SpriteFrame::create("images/spritesheet.png", Rect(83, 123, 14, 14)));
		animFrames.pushBack(SpriteFrame::create("images/spritesheet.png", Rect(103, 123, 14, 14)));
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
		animFrames.pushBack(SpriteFrame::create("images/spritesheet.png", Rect(123, 123, 14, 14)));
		animFrames.pushBack(SpriteFrame::create("images/spritesheet.png", Rect(143, 123, 14, 14)));
		/* Create Animation */
		Animation* animation = Animation::createWithSpriteFrames(animFrames, 1.0f / 6);
		/* Create Action */
		Animate* animate = Animate::create(animation);
		/* Run and repeat Action forever */
		this->runAction(RepeatForever::create(animate));
	}
}

Direction Inky::ai()
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