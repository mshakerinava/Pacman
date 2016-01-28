#include "PacmanScene.h"

#include "PacmanGame.h"

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
		return false;
    
	auto game = PacmanGame::create();
	if (!game)
		return false;
	
	this->addChild(game);
	Director::getInstance()->getOpenGLView()->setFrameSize(game->getContentSize().width, game->getContentSize().height);
	auto winSize = Director::getInstance()->getWinSize();
	game->setPosition(winSize.width / 2.0f, winSize.height / 2.0f);

	this->schedule(schedule_selector(PacmanScene::update), 1.0f / 60);
	
	return true;
}

void PacmanScene::update(float delta)
{
	for (int i = 0; i < (int)this->getChildren().size(); ++i)
		this->getChildren().at(i)->update(delta);
}
