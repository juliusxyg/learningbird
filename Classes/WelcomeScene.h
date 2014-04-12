//
//  WelcomeScene.h
//  flapunicon
//
//  Created by yingang on 14-4-12.
//
//

#ifndef __flapunicon__WelcomeScene__
#define __flapunicon__WelcomeScene__

#include "cocos2d.h"
#include "WelcomeLayer.h"

using namespace cocos2d;

class WelcomeScene : public cocos2d::CCLayer
{
public:
    virtual bool init();
        
    static CCScene* scene();
    
    CREATE_FUNC(WelcomeScene);
    
private:

};

#endif /* defined(__flapunicon__WelcomeScene__) */
