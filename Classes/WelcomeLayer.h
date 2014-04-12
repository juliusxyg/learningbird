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
    
    CCSize screenSize;
    CCSprite *ground_1;
    CCSprite *ground_2;
    void scrollGround(float dt);
    
};
#endif /* defined(__flapunicon__WelcomeLayer__) */
