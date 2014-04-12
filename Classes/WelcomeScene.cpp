//
//  WelcomeScene.cpp
//  flapunicon
//
//  Created by yingang on 14-4-12.
//
//

#include "WelcomeScene.h"


USING_NS_CC;

CCScene* WelcomeScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    WelcomeScene *layer = WelcomeScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
    
}

bool WelcomeScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    //载入欢迎层
    WelcomeLayer *layer = WelcomeLayer::create();
    addChild(layer);
    
    return true;
}

