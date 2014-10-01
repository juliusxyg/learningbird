//
//  WelcomeLayer.h
//  flapunicon
//
//  Created by yingang on 14-4-12.
//
//

#ifndef __flapunicon__WelcomeLayer__
#define __flapunicon__WelcomeLayer__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "AtlasResource.h"
#include "BirdSprite.h"
#include "GameScene.h"

using namespace cocos2d;
using namespace CocosDenshion;

class WelcomeLayer : public cocos2d::CCLayer
{
public:
    virtual bool init();
        
    CREATE_FUNC(WelcomeLayer);
    
private:
    void addBackground();
    void addTitle();
    void addGround();
    void addBird();
    void addStartButton();
    void addCopyright();
    
    CCSize screenSize;
    CCSprite *ground_1;
    CCSprite *ground_2;
    CCSprite *title;
    void scrollGround(float dt);
    void startCallback(CCObject *pSender);
    
};
#endif /* defined(__flapunicon__WelcomeLayer__) */
