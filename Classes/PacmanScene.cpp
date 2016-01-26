#include "PacmanScene.h"

#include "Maze.h"
#include "Pacman.h"
#include "EventManager.h"

USING_NS_CC;

Scene* PacmanScene::createScene()
{
    auto scene = Scene::create();
    auto layer = PacmanScene::create();

    scene->addChild(layer);

    return scene;
}

bool PacmanScene::init()
{
    if (!Layer::init())
    {
		return false;
    }
    
	auto maze = Maze::create("google");
	auto winSize = Director::getInstance()->getWinSize();
	maze->setPosition(winSize.width / 2.0, winSize.height / 2.0);
	this->addChild(maze);
	maze->runAction(ScaleBy::create(0, 2));
	
	auto pacman = Pacman::create(maze);
	maze->addChild(pacman);
	pacman->setPosition(Vec2(112, 76.5));
	
	EventManager::getInstance()->addEventListeners(this, pacman);

	this->schedule(schedule_selector(PacmanScene::update), 1.0f / 60);
	return true;
}

void PacmanScene::update(float delta)
{
	for (int i = 0; i < (int)this->getChildren().size(); ++i)
		this->getChildren().at(i)->update(delta);
}
