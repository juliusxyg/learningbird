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
    
    
    return true;
}

void LoadingScene::onEnter()
{
    //加载背景图
    backgroud = CCSprite::create("splash.png");
    CCSize screentSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint screenOrigin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    backgroud->setPosition(CCPoint(screenOrigin.x + screentSize.width/2, screenOrigin.y + screentSize.height/2));
    addChild(backgroud);
    
    //加载atlas图片资源
    CCTextureCache::sharedTextureCache()->addImageAsync("atlas.png", this, callfuncO_selector(LoadingScene::loadingCallback));
}

void LoadingScene::loadingCallback(cocos2d::CCObject *pSender)
{
    AtlasResource::sharedResource()->parseImage("atlas.txt", (CCTexture2D*)pSender);
    
    //预加载音效
    SimpleAudioEngine::sharedEngine()->preloadEffect("sfx_die.ogg");
    SimpleAudioEngine::sharedEngine()->preloadEffect("sfx_hit.ogg");
    SimpleAudioEngine::sharedEngine()->preloadEffect("sfx_point.ogg");
    SimpleAudioEngine::sharedEngine()->preloadEffect("sfx_swooshing.ogg");
    SimpleAudioEngine::sharedEngine()->preloadEffect("sfx_wing.ogg");
    
    //切换场景
    CCScene *welcomeScene = WelcomeScene::scene();
    CCTransitionScene *replaceScene = CCTransitionFade::create(1, welcomeScene);
    CCDirector::sharedDirector()->replaceScene(replaceScene);
}

