//
//  LoadingScene.h
//  flapunicon
//
//  Created by Yingang Xue on 4/11/14.
//
//

#ifndef __flapunicon__LoadingScene__
#define __flapunicon__LoadingScene__

#include "cocos2d.h"
#include "AtlasResource.h"

class LoadingScene : public cocos2d::CCLayer
{
public:
    virtual bool init();
    
    static cocos2d::CCScene* scene();
    
    CREATE_FUNC(LoadingScene);
    
private:
    //当资源载入以后调用这个方法切换场景
    void loadingCallback(CCObject *pSender);
};

#endif /* defined(__flapunicon__LoadingScene__) */


