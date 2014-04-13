//
//  BirdSprite.h
//  flapunicon
//
//  Created by yingang on 14-4-13.
//
//

#ifndef __flapunicon__BirdSprite__
#define __flapunicon__BirdSprite__

#include "cocos2d.h"
#include "AtlasResource.h"

using namespace cocos2d;

class BirdSprite : public CCSprite
{
public:
    BirdSprite();
    ~BirdSprite();
    
    //创建一个会动的小鸟
    static BirdSprite* createBird();
    
protected:
    void getRandomBird();

private:
    char birdName[10];
    char birdNameFrameFormat[10];
    CCSpriteFrame* getFrame(int n);
};

#endif /* defined(__flapunicon__BirdSprite__) */
