//
//  BirdSprite.cpp
//  flapunicon
//
//  Created by yingang on 14-4-13.
//
//

#include "BirdSprite.h"

USING_NS_CC;

BirdSprite::BirdSprite(){}

BirdSprite::~BirdSprite(){}

BirdSprite* BirdSprite::createBird()
{
    BirdSprite *pRet = new BirdSprite();
    if(pRet)
    {
        pRet->autorelease();
    }else{
        CC_SAFE_DELETE(pRet);
    }
    
    pRet->getRandomBird();
    if(pRet->initWithSpriteFrame(AtlasResource::sharedResource()->getSpriteFrameByName(pRet->birdName)))
    {
        CCArray *frames = CCArray::createWithCapacity(3);
        frames->addObject(pRet->getFrame(0));
        frames->addObject(pRet->getFrame(1));
        frames->addObject(pRet->getFrame(2));
        
        CCAnimate *fly = CCAnimate::create(CCAnimation::createWithSpriteFrames(frames, 0.2f));
        pRet->runAction(CCRepeatForever::create(CCSequence::create(fly, NULL)));
    }
    
    return pRet;
}

void BirdSprite::getRandomBird()
{
    srand((unsigned)time(NULL));
    int type = ((int)rand())% 3;
    sprintf(birdName, "bird%d_0", type);
    sprintf(birdNameFrameFormat, "bird%d_%s", type, "%d");
}

CCSpriteFrame* BirdSprite::getFrame(int n)
{
    char frameName[10];
    sprintf(frameName, birdNameFrameFormat, n);
    return AtlasResource::sharedResource()->getSpriteFrameByName(frameName);
}