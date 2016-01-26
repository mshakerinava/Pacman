#pragma once

#include "cocos2d.h"

class PacmanScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
	CREATE_FUNC(PacmanScene);

	void update(float) override;
};