//
//  GameScene.h
//  flapunicon
//
//  Created by yingang on 14-5-11.
//
//

#ifndef __flapunicon__GameScene__
#define __flapunicon__GameScene__

#include "cocos2d.h"
#include "GameBackgroundLayer.h"

using namespace cocos2d;

class GameScene : public cocos2d::CCLayer
{
public:
    virtual bool init();
    
    static CCScene* scene();
    
    CREATE_FUNC(GameScene);
    
private:
    
};

#endif /* defined(__flapunicon__GameScene__) */
