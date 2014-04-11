//
//  LoadingScene.cpp
//  flapunicon
//
//  Created by Yingang Xue on 4/11/14.
//
//

#include "LoadingScene.h"

USING_NS_CC;

CCScene* LoadingScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    LoadingScene *layer = LoadingScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;

}

bool LoadingScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    //test
    AtlasResource::sharedResource()->loadImage("atlas.png", "atlas.txt");

    cocos2d::CCSpriteFrame *birdFrame = AtlasResource::sharedResource()->getSpriteFrameByName("bird1_0");
    CCLOG("get bird");
    cocos2d::CCSprite *bird = cocos2d::CCSprite::createWithSpriteFrame(birdFrame);
    bird->cocos2d::CCNode::setPosition(100, 100);
    addChild(bird);
    return true;
}

void LoadingScene::loadingCallback(cocos2d::CCObject *pSender)
{
    
}

