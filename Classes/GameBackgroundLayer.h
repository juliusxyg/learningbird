//
//  GameBackgroundLayer.h
//  flapunicon
//
//  Created by yingang on 14-10-1.
//
//

#ifndef __flapunicon__GameBackgroundLayer__
#define __flapunicon__GameBackgroundLayer__

#include "cocos2d.h"
#include "AtlasResource.h"

using namespace cocos2d;

class GameBackgroundLayer : public cocos2d::CCLayer
{
public:
    virtual bool init();
    
    CREATE_FUNC(GameBackgroundLayer);
    
private:
    void addBackground();
    
    CCSize screenSize;

    
};


#endif /* defined(__flapunicon__GameBackgroundLayer__) */
