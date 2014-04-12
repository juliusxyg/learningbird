//
//  LoadingScene.h
//  flapunicon
//
//  Created by Yingang Xue on 4/11/14.
//
//

#ifndef __flapunicon__LoadingScene__
#define __flapunicon__LoadingScene__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "AtlasResource.h"
#include "WelcomeScene.h"

using namespace cocos2d;
using namespace CocosDenshion;

class LoadingScene : public cocos2d::CCLayer
{
public:
    /*
     1.其被调用的顺序是先init()，后onEnter()。
     
     2.init()在类的初始化时只会调用一次。
     
     3.onEnter在该类被载入场景的时候被调用，可能会发生多次。
     */
    virtual bool init();
    
    virtual void onEnter();
    
    static CCScene* scene();
    
    CREATE_FUNC(LoadingScene);
    
private:
    //当资源载入以后调用这个方法切换场景
    void loadingCallback(CCObject *pSender);
    
    CCSprite *backgroud;
};

#endif /* defined(__flapunicon__LoadingScene__) */


