#include "Pacman.h"

#include "Maze.h"

USING_NS_CC;

Pacman * Pacman::create(Maze *maze)
{
	Pacman *pacman = new (std::nothrow) Pacman();
	if (pacman && pacman->init(maze))
	{
		pacman->autorelease();
		return pacman;
	}
	CC_SAFE_DELETE(pacman);
	return nullptr;
}

bool Pacman::init(Maze *maze)
{
	Entity::init(maze);
	this->setState(State::NORMAL);
	this->eatingAnimation();
	this->intensionDirection = Direction::LEFT;
	this->applyIntension();
	this->setPosition(maze->getPacmanStartPos());
	return Sprite::initWithFile("images/spritesheet.png", Rect(43, 3, 13, 13));
}

float Pacman::moveTowards(Vec2 dest, float delta)
{
	/* Several dispositions occur! Fix maybe? */
	float dpx = MAX_SPEED * speed * delta;

	float curx = this->getPositionX();
	this->setPositionX(abs(dest.x - curx) <= dpx ? dest.x : curx + dpx * (dest.x - curx) / abs(dest.x - curx));

	float cury = this->getPositionY();
	this->setPositionY(abs(dest.y - cury) <= dpx ? dest.y : cury + dpx * (dest.y - cury) / abs(dest.y - cury));

	return MAX(0, delta * (1 - MAX(abs(dest.x - curx), abs(dest.y - cury)) / dpx));
}

void Pacman::applyIntension()
{
	/* Consume Intension */
	movingDirection = intensionDirection;
	intensionDirection = Direction::NONE;
	this->setRotation(180.0f - this->movingDirection.getvec2().getAngle() / M_PI * 180);
}

void Pacman::setState(State state)
{
	this->state = state;

	/** The Pacman Dossier @ Gamasutra.com **/
	if (this->state == State::NORMAL)
	{
		if (maze->getLevel() <= 1)
			this->speed = 0.8f;
		else if (maze->getLevel() <= 4)
			this->speed = 0.9f;
		else if (maze->getLevel() <= 20)
			this->speed = 1.0f;
		else
			this->speed = 0.9f;
	}
	else if (this->state == State::ENERGIZED)
	{
		if (maze->getLevel() <= 1)
			this->speed = 0.9f;
		else if (maze->getLevel() <= 4)
			this->speed = 0.95f;
		else
			this->speed = 1.0f;
	}
	else if (this->state == State::DEAD)
	{
		this->stopAllActions();
		this->stopMoving();
	}
}

void Pacman::eat(GameTile * tile)
{
	if (tile->getToken() == '.')
		maze->addScore(DOT_SCORE);
	else if (tile->getToken() == '@')
	{
		maze->addScore(ENERGIZER_SCORE);
		this->setState(State::ENERGIZED);
		maze->frightenGhosts();
	}
	tile->eat();
}

void Pacman::eatingAnimation()
{
	/* Create SpriteFrames */
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(4);
	animFrames.pushBack(SpriteFrame::create("images/spritesheet.png", Rect(43, 3, 13, 13)));
	animFrames.pushBack(SpriteFrame::create("images/spritesheet.png", Rect(3, 3, 13, 13)));
	animFrames.pushBack(SpriteFrame::create("images/spritesheet.png", Rect(23, 3, 13, 13)));
	animFrames.pushBack(SpriteFrame::create("images/spritesheet.png", Rect(3, 3, 13, 13)));
	/* Create Animation */
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 1.0f / 24);
	/* Create Action */
	Animate* animate = Animate::create(animation);
	/* Run and repeat Action forever */
	this->runAction(RepeatForever::create(animate));
}

void Pacman::deathAnimation()
{
	this->setRotation(0);
	/* Create SpriteFrames */
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(10);
	animFrames.pushBack(SpriteFrame::create("images/spritesheet.png", Rect(1  , 241, 17, 17)));
	animFrames.pushBack(SpriteFrame::create("images/spritesheet.png", Rect(21 , 241, 17, 17)));
	animFrames.pushBack(SpriteFrame::create("images/spritesheet.png", Rect(41 , 241, 17, 17)));
	animFrames.pushBack(SpriteFrame::create("images/spritesheet.png", Rect(81 , 241, 17, 17)));
	animFrames.pushBack(SpriteFrame::create("images/spritesheet.png", Rect(101, 241, 17, 17)));
	animFrames.pushBack(SpriteFrame::create("images/spritesheet.png", Rect(121, 241, 17, 17)));
	animFrames.pushBack(SpriteFrame::create("images/spritesheet.png", Rect(141, 241, 17, 17)));
	animFrames.pushBack(SpriteFrame::create("images/spritesheet.png", Rect(161, 241, 17, 17)));
	animFrames.pushBack(SpriteFrame::create("images/spritesheet.png", Rect(181, 241, 17, 17)));
	animFrames.pushBack(SpriteFrame::create("images/spritesheet.png", Rect(201, 241, 17, 17)));
	/* Create Animation */
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.16f);
	/* Create Action */
	Animate* animate = Animate::create(animation);
	/* Run and repeat Action forever */
	this->runAction(animate);
}

void Pacman::closeMouth()
{
	this->setDisplayFrame(SpriteFrame::create("images/spritesheet.png", Rect(43, 3, 13, 13)));
}

void Pacman::update(float delta)
{
	GameTile *curTile = maze->getTile(this->getPosition());
	GameTile *nextIntensionTile = maze->getTile(curTile->getPosition() + intensionDirection.getvec2() * 8);
	GameTile *nextTile = maze->getTile(curTile->getPosition() + movingDirection.getvec2() * 8);;
	
	if (curTile->isEdible())
	{
		this->eat(curTile);
		/* Eating dots slows Pacman down */
		return;
	}

	if (intensionDirection != Direction::NONE && nextIntensionTile && nextIntensionTile->isLegalSpace())
	{
		this->applyIntension();
		nextTile = nextIntensionTile;
	}
	
	if (movingDirection == Direction::NONE)
		return;
	else if (nextTile && nextTile->isLegalSpace())
	{
		this->resume();
		delta = this->moveTowards(curTile->getPosition() + movingDirection.getvec2() * (4.0f + 1E-4f), delta);
		if (delta > 0)
			this->update(delta);
	}
	else
	{
		delta = this->moveTowards(curTile->getPosition(), delta);
		if(delta == 0)
			this->pause();
	}
}

void Pacman::control(Direction dir)
{
	if (this->state == State::DEAD)
		return;
	
	this->intensionDirection = dir;
}

void Pacman::die()
{
	this->setState(State::DEAD);
}
