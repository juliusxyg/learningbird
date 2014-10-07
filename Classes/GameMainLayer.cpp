//
//  GameMainLayer.cpp
//  flapunicon
//
//  Created by yingang on 14-10-1.
//
//

#include "GameMainLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

bool GameMainLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    screenSize = CCDirector::sharedDirector()->getVisibleSize();
    
    //背景分白天和晚上，读取本地时间
    time_t t = time(NULL);
    tm *localTime = std::localtime(&t);
    int hour = localTime->tm_hour;
    if(hour >=6 && hour <=17)
    {
        strcpy(pipeName, "pipe");
    }else{
        strcpy(pipeName, "pipe2");
    }

    
    //初始化世界
    initWorld();
    //添加容器层, 在地板之前添加就不会覆盖在地板上了
    addPipeContainer();
    //背景
    addGround();
    //开始游戏
    startGame();
    
    return true;
}

void GameMainLayer::startGame()
{
    //定时器每一帧不断调用update方法
    scheduleUpdate();
    //定时器每隔一秒调用一次addPipe来画管道
    schedule(schedule_selector(GameMainLayer::addPipe), 1);
}

void GameMainLayer::initWorld()
{
    //box2d的世界需要传入参数去表明这个世界的重力的大小和方向，用b2Vec2表示:参数1和2分别表示x和y方向的重力加速度，本游戏在x方向上没有重力加速所以是0
    world = new b2World(b2Vec2(0, -9.8f));//一个重力加速度是9.8
    //step1.7 碰撞检测，在初始化世界的时候加入一个碰触监听器, 并且将当前的类作为监听器使用
    world->SetContactListener(this);
}

void GameMainLayer::addGround()
{
    //运动的地板
    ground_1 = CCSprite::createWithSpriteFrame(AtlasResource::sharedResource()->getSpriteFrameByName("land"));
    ground_2 = CCSprite::createWithSpriteFrame(AtlasResource::sharedResource()->getSpriteFrameByName("land"));
    //小鸟在飞行时地板是移动的，用两个精灵交替实现移动, 地板的原点是左下角
    ground_1->setAnchorPoint(CCPoint(0, 0));
    ground_2->setAnchorPoint(CCPoint(0, 0));
    
    ground_1->setPosition(CCPoint(0, 0));
    ground_2->setPosition(CCPoint(ground_1->getContentSize().width - 2.0f, 0));//2个像素位置重叠可以避免一条黑缝
    
    addChild(ground_1);
    addChild(ground_2);
    schedule(schedule_selector(GameMainLayer::scrollGround), 0.01);
    
    //物理世界地板
    //创建精灵
    ground = CCPhysicsSprite::create();
    CCSize groundSize = ground_1->getContentSize();
    
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;//地板是一个静态body，不受物理世界影响
    //定义地板位置, 屏幕中间，位置靠下，因为默认anchor在中心，所以高度这边设置要图片高度的一半
    bodyDef.position = b2Vec2(screenSize.width/2/PTM_RATIO, groundSize.height/2/PTM_RATIO);
    bodyDef.userData = ground;
    b2Body* groundBody = world->CreateBody(&bodyDef);
    //设置fixture
    b2FixtureDef groundFixtureDef;
    b2PolygonShape groundShape;
    groundShape.SetAsBox(groundSize.width/2/PTM_RATIO, groundSize.height/2/PTM_RATIO);
    groundFixtureDef.shape = &groundShape;
    groundBody->CreateFixture(&groundFixtureDef);
    
    ground->setPTMRatio(PTM_RATIO);
    ground->setB2Body(groundBody);
    addChild(ground);

}

void GameMainLayer::scrollGround(float dt)
{
    if(0==ground_2->getPositionX()){
        ground_1->setPosition(CCPoint(0, 0));
        ground_2->setPosition(CCPoint(ground_1->getContentSize().width - 2.0f, 0));
    }
    
    ground_1->setPosition(CCPoint(ground_1->getPositionX()-2.0f, 0));
    ground_2->setPosition(CCPoint(ground_2->getPositionX()-2.0f, 0));
}

void GameMainLayer::addPipeContainer()
{
    pipeContainer = CCSprite::create();
    addChild(pipeContainer);
}

void GameMainLayer::addPipe(float dt)
{
    //添加一个随机的位置给小鸟通过(0,-5)
    float offset = -rand()%5;
    //添加上下两个pipe，同时pipe不受物理世界的重力影响
    //下pipe
    char pname[15];
    const char *pipe_name;
    sprintf(pname, "%s_up", pipeName);
    pipe_name = pname;
    CCPhysicsSprite* downPipe = CCPhysicsSprite::createWithSpriteFrame(AtlasResource::sharedResource()->getSpriteFrameByName(pipe_name));
    CCSize downPipeSize = downPipe->getContentSize();
    b2BodyDef downBodyDef;
    downBodyDef.type = b2_kinematicBody;//不受重力影响，但是可移动的类型
    downBodyDef.position = b2Vec2(screenSize.width/PTM_RATIO+2, downPipeSize.height/2/PTM_RATIO+offset);//从屏幕右边出来
    downBodyDef.linearVelocity = b2Vec2(-200/PTM_RATIO, 0);//pipe往左移动的速度=地板移动的速度
    downBodyDef.userData = downPipe;
    b2Body* downPipeBody = world->CreateBody(&downBodyDef);
    //夹具
    b2FixtureDef downFixtureDef;
    b2PolygonShape downShape;
    downShape.SetAsBox(downPipeSize.width/2/PTM_RATIO, downPipeSize.height/2/PTM_RATIO);
    downFixtureDef.shape = &downShape;
    downPipeBody->CreateFixture(&downFixtureDef);
    
    downPipe->setPTMRatio(PTM_RATIO);
    downPipe->setB2Body(downPipeBody);
    
    pipeContainer->addChild(downPipe);
    //上pipe
    sprintf(pname, "%s_down", pipeName);
    pipe_name = pname;
    CCPhysicsSprite* upPipe = CCPhysicsSprite::createWithSpriteFrame(AtlasResource::sharedResource()->getSpriteFrameByName(pipe_name));
    CCSize upPipeSize = upPipe->getContentSize();
    
    b2BodyDef upBodyDef;
    upBodyDef.type = b2_kinematicBody;//不受重力影响，但是可移动的类型
    upBodyDef.position = b2Vec2(screenSize.width/PTM_RATIO+2, downPipeSize.height/PTM_RATIO+offset+2+upPipeSize.height/2/PTM_RATIO);//从屏幕右边出来, up pipe比down pipe高出2米
    upBodyDef.linearVelocity = b2Vec2(-200/PTM_RATIO, 0);//pipe往左移动的速度
    upBodyDef.userData = upPipe;
    b2Body* upPipeBody = world->CreateBody(&upBodyDef);
    //夹具
    b2FixtureDef upFixtureDef;
    b2PolygonShape upShape;
    upShape.SetAsBox(upPipeSize.width/2/PTM_RATIO, upPipeSize.height/2/PTM_RATIO);
    upFixtureDef.shape = &upShape;
    upPipeBody->CreateFixture(&upFixtureDef);
    
    upPipe->setPTMRatio(PTM_RATIO);
    upPipe->setB2Body(upPipeBody);
    
    pipeContainer->addChild(upPipe);
    
}

void GameMainLayer::update(float dt)
{
    //执行box2d世界的step方法，dt为时间间隔
    world->Step(dt, 8, 3);//8,3 分别是官方推荐的速度迭代和位置迭代的推荐值
    
    //step1.6.2 清理物理世界里的元素
    CCSprite *s;
    for (b2Body *b = world->GetBodyList(); b!=NULL; b=b->GetNext())
    {
        if(b->GetPosition().x<-3)//位置超过右边3个单位时销毁, 同时销毁物理世界body和cocos2d的sprite对象(图形)
        {
            s = (CCSprite*)b->GetUserData();//获取绑定该body的数据，这里做强制类型转换
            if(s!=NULL)
            {
                s->removeFromParent();//从父容器中移除
                CCLog("Remove");
            }
            world->DestroyBody(b);
            CCLog("Destory");
        }
    }
}



