//
//  GameMainLayer.h
//  flapunicon
//
//  Created by yingang on 14-10-1.
//
//

#ifndef __flapunicon__GameMainLayer__
#define __flapunicon__GameMainLayer__

#include "cocos2d.h"
#include "AtlasResource.h"
#include "Box2D.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

//定义app的高度是480像素，而box2d世界高度10米，如此有一个比例即48,这里定义成float型, ptm即pixel to meter
#define PTM_RATIO 48.0f

class GameMainLayer : public cocos2d::CCLayer, public b2ContactListener
{
public:
    virtual bool init();
    
    CREATE_FUNC(GameMainLayer);
    
    b2World *world;
    
    //定义update, scheduleUpdate每一帧都会调用这个方法
    virtual void update(float dt);
    
private:
    void initWorld();
    void addGround();
    void addPipeContainer();
    void addPipe(float dt);
    
    CCSize screenSize;
    CCSprite* ground_1;
    CCSprite* ground_2;
    CCSprite* pipeContainer;
    CCPhysicsSprite* ground;
    char pipeName[6];
    
    void scrollGround(float dt);
    void startGame();
    
};

#endif /* defined(__flapunicon__GameMainLayer__) */
