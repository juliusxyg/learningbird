//
//  GameScene.cpp
//  flapunicon
//
//  Created by yingang on 14-5-11.
//
//

#include "GameScene.h"


USING_NS_CC;

CCScene* GameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameScene *layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
    
}

bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    //载入背景层，核心层，状态层
    GameBackgroundLayer *background = GameBackgroundLayer::create();
    addChild(background);
    //GameMainLayer *mainlayer = GameMainLayer::create();
    //addChild(mainlayer);
    //GameStatusLayer *statuslayer = GameStatusLayer::create();
    //addChild(statuslayer);
    
    return true;
}
