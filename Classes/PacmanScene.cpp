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
	this->addChild(game);
	game->setScale(3);
	game->setAnchorPoint(Vec2(0, 0));
	game->setPosition(0, 0);
	Director::getInstance()->getOpenGLView()->setFrameSize(game->getContentSize().width * 3, game->getContentSize().height * 3);
	
	this->schedule(schedule_selector(PacmanScene::update), 1.0f / 60);
	
	return true;
}

void PacmanScene::update(float delta)
{
	for (int i = 0; i < (int)this->getChildren().size(); ++i)
		this->getChildren().at(i)->update(delta);
}
