#include "Ghost.h"

#include "Maze.h"

const int Ghost::FRIGHT_TIMES[] = { 6, 5, 4, 3, 2, 5, 2, 2, 1, 5, 2, 1, 1, 3, 1, 1, 0, 1 };

Ghost::~Ghost()
{
}

bool Ghost::init(Maze *maze)
{
	Entity::init(maze);
	this->imprisoned = true;
	this->setState(State::NORMAL);
	this->setMovement(Movement::NORMAL);
	this->setLocalZOrder(2);
	return true;
}

int Ghost::getFrightTime()
{
	int level = maze->getLevel();
	if (level >= sizeof(FRIGHT_TIMES) / sizeof(int))
		return 0;
	else
		return FRIGHT_TIMES[level];
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

float Ghost::moveTowards(Vec2 dest, float delta)
{
	/* TODO: Several dispositions occur! Fix maybe? */
	float dpx = MAX_SPEED * speed * delta;
	float dist = (dest - this->getPosition()).getLength();
	float displacement = MIN(dpx, dist);

	this->setPosition(this->getPosition() + this->movingDirection.getvec2() * displacement);

	return delta - displacement / (MAX_SPEED * speed);
}

void Ghost::setDirection(Direction direction)
{
	this->movingDirection = direction;
	if (this->state == State::NORMAL)
		this->moveAnimation();
	else if (this->state == State::DEAD)
		this->eyesAnimation();
}

void Ghost::setState(State state)
{
	this->state = state;
	
	if (state == State::NORMAL)
	{
		this->moveAnimation();
		if (this->movement == Movement::FRIGHTENED)
			this->setMovement(Movement::NORMAL);
	}
	else if (state == State::FRIGHTENED)
	{
		int delayTime = getFrightTime();
		if (delayTime == 0)
			return this->setState(State::NORMAL);

		this->frightAnimation();
		if (this->movement == Movement::NORMAL && !this->imprisoned)
			this->setMovement(Movement::FRIGHTENED);
		
		this->runAction(Sequence::create(
			DelayTime::create(delayTime),
			CallFunc::create([&]() {this->setState(State::NORMAL); }),
			nullptr));
	}
	else if (state == State::DEAD)
	{
		this->eyesAnimation();
		this->setMovement(Movement::DEAD);
		/* TODO */
	}
}

void Ghost::setMovement(Movement movement)
{
	this->movement = movement;

	if (movement == Movement::NORMAL)
	{
		if (maze->getLevel() <= 1)
			this->speed = 0.75f;
		else if (maze->getLevel() <= 4)
			this->speed = 0.85f;
		else if (maze->getLevel() <= 20)
			this->speed = 0.95f;
		else
			this->speed = 0.95f;
	}
	else if (movement == Movement::FRIGHTENED)
	{
		if (maze->getLevel() <= 1)
			this->speed = 0.5f;
		else if (maze->getLevel() <= 4)
			this->speed = 0.55f;
		else
			this->speed = 0.6f;
	}
	else if (movement == Movement::TUNNEL)
	{
		if (maze->getLevel() <= 1)
			this->speed = 0.4f;
		else if (maze->getLevel() <= 4)
			this->speed = 0.45f;
		else
			this->speed = 0.5f;
	}
	else if (movement == Movement::ESCAPE)
	{
		this->speed = 0.3f;
	}
	else if (movement == Movement::DEAD)
	{
		this->speed = 2.0f;
	}
}

void Ghost::killPacman()
{
	/* Double Check */
	if (maze->getPacmanTile() == maze->getTile(this->getPosition()))
		maze->killPacman();
}

void Ghost::update(float delta)
{
	if (delta <= 0)
		return;

	/* Tunnel teleportation */
	if (this->getPositionX() > maze->getWidth() * 8 + 4)
		this->setPositionX(this->getPositionX() - maze->getWidth() * 8 - 8);
	if(this->getPositionX() < -4)
		this->setPositionX(this->getPositionX() + maze->getWidth() * 8 + 8);

	GameTile *curTile = maze->getTile(this->getPosition());
	GameTile *nextTile = maze->getTile(curTile->getPosition() + movingDirection.getvec2() * 8);;

	/* Check collision with Pacman */
	if (maze->getPacmanTile() == curTile)
	{
		if (this->state == State::NORMAL)
			this->killPacman();
		else if (this->state == State::FRIGHTENED)
			this->die();
		return;
	}

	if (this->imprisoned)
	{
		/* Resurection */
		if (this->state == State::DEAD)
			this->setState(State::NORMAL);

		if (this->movement == Movement::ESCAPE)
		{
			if (this->getPositionX() != maze->getPinkyStartPos().x)
			{
				if (this->getPositionX() < maze->getPinkyStartPos().x)
					this->setDirection(Direction::RIGHT);
				else
					this->setDirection(Direction::LEFT);
				delta = this->moveTowards(maze->getPinkyStartPos(), delta);
			}
			else
			{
				this->setDirection(Direction::UP);
				delta = this->moveTowards(maze->getBlinkyStartPos(), delta);
			}

			if (this->getPosition() == maze->getBlinkyStartPos())
			{
				/* Set Free */
				this->imprisoned = false;
				
				if (this->state == State::NORMAL)
					this->setMovement(Movement::NORMAL);
				else if (this->state == State::FRIGHTENED)
					this->setMovement(Movement::FRIGHTENED);

				this->setDirection(this->ai());
			}
		}
		else /* Going Up & Down trying to Escape */
		{
			if ((this->getPosition().y < maze->getPinkyStartPos().y && this->movingDirection == Direction::UP) ||
				(this->getPosition().y > maze->getPinkyStartPos().y && this->movingDirection == Direction::DOWN))
			{
				delta = this->moveTowards(Vec2(this->getPositionX(), maze->getPinkyStartPos().y), delta);
				/* if Standing on Start Position */
				if (delta > 0)
				{
					/* Try to Escape */
					if (rand() % 100 < 5)
						this->setMovement(Movement::ESCAPE);
				}
			}
			else /* Not Going Towards Starting Position */
			{
				if (this->movingDirection == Direction::UP)
					delta = this->moveTowards(Vec2(this->getPositionX(), maze->getPinkyStartPos().y + 6), delta);
				else /* DOWN */
					delta = this->moveTowards(Vec2(this->getPositionX(), maze->getPinkyStartPos().y - 6), delta);
				if (delta > 0)
					this->setDirection(this->movingDirection.opposite());
			}
		}
	}
	else /* is Free */
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
		}
		else
			delta = this->moveTowards(nextTile->getPosition(), delta);
	}
	this->update(delta);
}

void Ghost::die()
{
	this->setState(State::DEAD);
}

void Ghost::fright()
{
	this->setState(State::FRIGHTENED);
}