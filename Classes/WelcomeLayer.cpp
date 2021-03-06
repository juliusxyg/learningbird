//
//  WelcomeLayer.cpp
//  flapunicon
//
//  Created by yingang on 14-4-12.
//
//

#include "WelcomeLayer.h"

USING_NS_CC;

bool WelcomeLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    screenSize = CCDirector::sharedDirector()->getVisibleSize();
    //背景
    addBackground();
    //标题
    addTitle();
    //移动的地板
    addGround();
    //飞翔的小鸟
    addBird();
    //开始按钮
    addStartButton();
    //添加copyright
    addCopyright();
    
    return true;
}

void WelcomeLayer::addCopyright()
{
    CCSprite *copyright = CCSprite::createWithSpriteFrame(AtlasResource::sharedResource()->getSpriteFrameByName("brand_copyright"));
    copyright->setPosition(CCPoint(screenSize.width/2, copyright->getContentSize().height));
    addChild(copyright);
}

void WelcomeLayer::addStartButton()
{
    CCSprite *startButton = CCSprite::createWithSpriteFrame(AtlasResource::sharedResource()->getSpriteFrameByName("button_play"));
    CCSprite *startButtonSelected = CCSprite::createWithSpriteFrame(AtlasResource::sharedResource()->getSpriteFrameByName("button_play"));
    CCMenuItemSprite *startItem = CCMenuItemSprite::create(startButton, startButtonSelected, this, menu_selector(WelcomeLayer::startCallback));
    CCMenu *menu = CCMenu::create(startItem, NULL);
    menu->setPosition(CCPoint(screenSize.width/2, ground_1->getContentSize().height+startButton->getContentSize().height));
    addChild(menu);
}

void WelcomeLayer::addBird()
{
    BirdSprite *bird = BirdSprite::createBird();
    bird->setPosition(CCPoint(screenSize.width/2, (screenSize.height+ground_1->getContentSize().height)/2));
    addChild(bird);
}

void WelcomeLayer::addTitle()
{
    title = CCSprite::createWithSpriteFrame(AtlasResource::sharedResource()->getSpriteFrameByName("title"));
    title->setPosition(CCPoint(screenSize.width/2, screenSize.height-title->getContentSize().height*1.5));
    addChild(title);
}

void WelcomeLayer::addGround()
{
    ground_1 = CCSprite::createWithSpriteFrame(AtlasResource::sharedResource()->getSpriteFrameByName("land"));
    ground_2 = CCSprite::createWithSpriteFrame(AtlasResource::sharedResource()->getSpriteFrameByName("land"));
    //小鸟在飞行时地板是移动的，用两个精灵交替实现移动, 地板的原点是左下角
    ground_1->setAnchorPoint(CCPoint(0, 0));
    ground_2->setAnchorPoint(CCPoint(0, 0));
    
    ground_1->setPosition(CCPoint(0, 0));
    ground_2->setPosition(CCPoint(ground_1->getContentSize().width - 2.0f, 0));//2个像素位置重叠可以避免一条黑缝
    
    addChild(ground_1);
    addChild(ground_2);
    schedule(schedule_selector(WelcomeLayer::scrollGround), 0.01);
}

void WelcomeLayer::scrollGround(float dt)
{
    if(0==ground_2->getPositionX()){
        ground_1->setPosition(CCPoint(0, 0));
        ground_2->setPosition(CCPoint(ground_1->getContentSize().width - 2.0f, 0));
    }
 
    ground_1->setPosition(CCPoint(ground_1->getPositionX()-2.0f, 0));
    ground_2->setPosition(CCPoint(ground_2->getPositionX()-2.0f, 0));
}

void WelcomeLayer::addBackground()
{
    //背景分白天和晚上，读取本地时间
    time_t t = time(NULL);
    tm *localTime = std::localtime(&t);
    int hour = localTime->tm_hour;
    char backgroundName[10];
    if(hour >=6 && hour <=17)
    {
        strcpy(backgroundName, "bg_day");
    }else{
        strcpy(backgroundName, "bg_night");
    }
    CCSprite *background = CCSprite::createWithSpriteFrame(AtlasResource::sharedResource()->getSpriteFrameByName(backgroundName));
    
    background->setPosition(CCPoint(screenSize.width/2, screenSize.height/2));
    background->setScale(320/background->getContentSize().width);
    addChild(background);
}

void WelcomeLayer::startCallback(cocos2d::CCObject *pSender)
{
    CCLog("tap start");
    SimpleAudioEngine::sharedEngine()->playEffect("sfx_swooshing.ogg");
    //切换场景
    CCScene *gameScene = GameScene::scene();
    CCTransitionScene *replaceScene = CCTransitionFade::create(1, gameScene);
    CCDirector::sharedDirector()->replaceScene(replaceScene);
    
}
