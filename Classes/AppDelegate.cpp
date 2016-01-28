#include "AppDelegate.h"
#include "PacmanScene.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview)
	{
        glview = GLViewImpl::create("Pacman");
		glview->setFrameSize(1024, 576);
		director->setOpenGLView(glview);
    }
	
	// Director::getInstance()->getOpenGLView()->setFrameSize(1920, 1080);
	// Director::getInstance()->getOpenGLView()->setDesignResolutionSize(1920, 1080, ResolutionPolicy::EXACT_FIT);
	// Director::getInstance()->setDisplayStats(true);

	auto scene = PacmanScene::createScene();
	director->runWithScene(scene);

    return true;
}

void AppDelegate::applicationDidEnterBackground()
{
}

void AppDelegate::applicationWillEnterForeground()
{
}
