//
//  GameBackgroundLayer.cpp
//  flapunicon
//
//  Created by yingang on 14-10-1.
//
//

#include "GameBackgroundLayer.h"

USING_NS_CC;

bool GameBackgroundLayer::init()
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
    
    return true;
}

void GameBackgroundLayer::addBackground()
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