#include "Ghost.h"

#include "Maze.h"

Ghost::~Ghost()
{
}

bool Ghost::init(Maze *maze)
{
	Entity::init(maze);
	this->speed = 0.75f;
	this->imprisoned = false;
	return true;
}

void Ghost::flashAnimation()
{
	/* Create SpriteFrames */
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(4);
	animFrames.pushBack(SpriteFrame::create("images/spritesheet.png", Rect(3 , 163, 14, 14)));
	animFrames.pushBack(SpriteFrame::create("images/spritesheet.png", Rect(23, 163, 14, 14)));
	animFrames.pushBack(SpriteFrame::create("images/spritesheet.png", Rect(43, 163, 14, 14)));
	animFrames.pushBack(SpriteFrame::create("images/spritesheet.png", Rect(63, 163, 14, 14)));
	/* Create Animation */
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 1.0f / 6);
	/* Create Action */
	Animate* animate = Animate::create(animation);
	/* Run and repeat Action forever */
	this->runAction(RepeatForever::create(animate));
}

void Ghost::frightAnimation()
{
	this->stopAllActions();
	/* Create SpriteFrames */
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(2);
	animFrames.pushBack(SpriteFrame::create("images/spritesheet.png", Rect(3 , 163, 14, 14)));
	animFrames.pushBack(SpriteFrame::create("images/spritesheet.png", Rect(23, 163, 14, 14)));
	/* Create Animation */
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 1.0f / 6);
	/* Create Action */
	Animate* animate = Animate::create(animation);
	/* Run and repeat Action forever */
	this->runAction(RepeatForever::create(animate));
}

void Ghost::eyesAnimation()
{
	if (this->movingDirection == Direction::UP)
	{
		/* Create SpriteFrames */
		Vector<SpriteFrame*> animFrames;
		animFrames.reserve(1);
		animFrames.pushBack(SpriteFrame::create("images/spritesheet.png", Rect(3, 203, 14, 14)));
		/* Create Animation */
		Animation* animation = Animation::createWithSpriteFrames(animFrames, 100.0f);
		/* Create Action */
		Animate* animate = Animate::create(animation);
		/* Run and repeat Action forever */
		this->runAction(RepeatForever::create(animate));
	}
	else if (this->movingDirection == Direction::DOWN)
	{
		/* Create SpriteFrames */
		Vector<SpriteFrame*> animFrames;
		animFrames.reserve(1);
		animFrames.pushBack(SpriteFrame::create("images/spritesheet.png", Rect(23, 203, 14, 14)));
		/* Create Animation */
		Animation* animation = Animation::createWithSpriteFrames(animFrames, 100.0f);
		/* Create Action */
		Animate* animate = Animate::create(animation);
		/* Run and repeat Action forever */
		this->runAction(RepeatForever::create(animate));
	}
	else if (this->movingDirection == Direction::LEFT)
	{
		/* Create SpriteFrames */
		Vector<SpriteFrame*> animFrames;
		animFrames.reserve(1);
		animFrames.pushBack(SpriteFrame::create("images/spritesheet.png", Rect(43, 203, 14, 14)));
		/* Create Animation */
		Animation* animation = Animation::createWithSpriteFrames(animFrames, 100.0f);
		/* Create Action */
		Animate* animate = Animate::create(animation);
		/* Run and repeat Action forever */
		this->runAction(RepeatForever::create(animate));
	}
	else if (this->movingDirection == Direction::RIGHT)
	{
		/* Create SpriteFrames */
		Vector<SpriteFrame*> animFrames;
		animFrames.reserve(1);
		animFrames.pushBack(SpriteFrame::create("images/spritesheet.png", Rect(63, 203, 14, 14)));
		/* Create Animation */
		Animation* animation = Animation::createWithSpriteFrames(animFrames, 100.0f);
		/* Create Action */
		Animate* animate = Animate::create(animation);
		/* Run and repeat Action forever */
		this->runAction(RepeatForever::create(animate));
	}
}

void Ghost::die()
{
	this->eyesAnimation();
}

void Ghost::fright()
{
	this->frightAnimation();
}

float Ghost::moveTowards(Vec2 dest, float delta)
{
	/* TODO: Several dispositions occur! Fix maybe? */
	float dpx = MAX_SPEED * speed * delta;
	float dist = (dest - this->getPosition()).getLength();
	float displacement = MIN(dpx, dist);

	this->setPosition(this->getPosition() + this->movingDirection.getvec2() * displacement);

	return delta - displacement / (MAX_SPEED * speed);
}

void Ghost::setDirection(Direction newDirection)
{
	this->movingDirection = newDirection;
	this->moveAnimation();
}

void Ghost::killPacman()
{
	if (maze->getPacmanTile() == maze->getTile(this->getPosition()))
		maze->killPacman();
}

void Ghost::update(float delta)
{
	if (this->getPositionX() > maze->getWidth() * 8 + 4)
		this->setPositionX(this->getPositionX() - maze->getWidth() * 8 - 8);
	if(this->getPositionX() < -4)
		this->setPositionX(this->getPositionX() + maze->getWidth() * 8 + 8);

	GameTile *curTile = maze->getTile(this->getPosition());
	GameTile *nextTile = maze->getTile(curTile->getPosition() + movingDirection.getvec2() * 8);;

	/*
	if (maze->getPacmanTile() == curTile)
	{
	kill(maze->getPacman());
	}
	*/

	if (this->imprisoned)
	{

	}
	else
	{
		if ((curTile->isIntersection() && Direction(curTile->getPosition() - this->getPosition()) == movingDirection) ||
			!nextTile || nextTile->isDeadSpace())
		{
			delta = this->moveTowards(curTile->getPosition(), delta);
			if (this->getPosition() == curTile->getPosition())
			{
				/* Center of intersection. Time for AI. */
				this->setDirection(this->ai());
			}
			if (delta <= 0)
				return;
		}
		delta = this->moveTowards(nextTile->getPosition(), delta);
		if (delta > 0)
			this->update(delta);
	}
}
