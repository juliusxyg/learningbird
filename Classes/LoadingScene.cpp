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
    AtlasResource::sharedResource()->loadImage("atlas.png");
    AtlasResource::sharedResource()->parseImage("atlas.txt");
    
    AtlasResource::sharedResource()->getSpriteFrameByName("bird1_0");
    
    return true;
}

void LoadingScene::loadingCallback(cocos2d::CCObject *pSender)
{
    
}

