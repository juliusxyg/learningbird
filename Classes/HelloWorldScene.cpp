#include "HelloWorldScene.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    //获取屏幕大小
    screenSize = CCDirector::sharedDirector()->getVisibleSize();
    //初始化世界
    initWorld();
    //给场景添加小鸟
    addBird();
    //添加容器层, 在地板之前添加就不会覆盖在地板上了
    addPipeContainer();
    //添加地板
    addGround();
    //设置让touch事件生效，开关
    setTouchEnabled(true);
    //开始游戏
    startGame();
    
    return true;
}

void HelloWorld::initWorld()
{
    //box2d的世界需要传入参数去表明这个世界的重力的大小和方向，用b2Vec2表示:参数1和2分别表示x和y方向的重力加速度，本游戏在x方向上没有重力加速所以是0
    world = new b2World(b2Vec2(0, -10.0f));//一个重力加速度是9.8，方便起见用10
    //step1.7 碰撞检测，在初始化世界的时候加入一个碰触监听器, 并且将当前的类作为监听器使用
    world->SetContactListener(this);
}

void HelloWorld::BeginContact(b2Contact* contact)
{
    //获取碰触连接的两个夹具Fixture，记得前面我们定义物理世界body的时候都创建了对应的fixture，它就是用来检测碰撞的
    if(contact->GetFixtureA()->GetBody()->GetUserData()==bird ||
       contact->GetFixtureB()->GetBody()->GetUserData()==bird)//如果是小鸟发生了碰撞，那么游戏就应该结束
    {
        stopGame();
        CCMessageBox("close", "Game Over");
    }
}

void HelloWorld::startGame()
{
    //定时器每一帧不断调用update方法
    scheduleUpdate();
    //定时器每隔一秒调用一次addPipe来画管道
    schedule(schedule_selector(HelloWorld::addPipe), 1);
}

void HelloWorld::stopGame()//关闭定时器
{
    unscheduleUpdate();
    unschedule(schedule_selector(HelloWorld::addPipe));
}

void HelloWorld::addBird()
{
    //引用了cocos2d扩展里的类，创建精灵
    bird = cocos2d::extension::CCPhysicsSprite::create("bird.png");
    //给小鸟绑定一个物理世界的body, 并且指定是动态body，同时指定初始位置为屏幕水平中间，高度9米
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = b2Vec2(screenSize.width/2/PTM_RATIO, 9);
    //box2d世界里面衡量位置的单位是米而不是像素，一般box2d在10米以内的模拟是非常高效的，假定我们应用程序是320x480，因为不同设备尺寸不同，我们可以在AppDelegate.cpp中设置我们app的分辨率.
    bodyDef.userData = bird;//这里传入cocos2d的精灵对象给物理世界的userdata，方便以后不需要的时候删除. 同时注意必须在create body前设置bodyDef
    b2Body* birdBody = world->CreateBody(&bodyDef);
    //为了使小鸟可以和其他精灵发生碰撞或检测碰撞，需要给它设置一个图形边界
    b2FixtureDef birdFixtureDef;
    //fixtureDef有很多参数，这里我们设置图形，其余均默认。图形为
    b2PolygonShape birdShape;
    CCSize birdSize = bird->getContentSize();
    birdShape.SetAsBox(birdSize.width/2/PTM_RATIO, birdSize.height/2/PTM_RATIO);//把小鸟当成一个多边形,参数是小鸟的半宽高，同时别忘了比例
    birdFixtureDef.shape = &birdShape;
    //创建边界
    birdBody->CreateFixture(&birdFixtureDef);
    //绑定body和bird， 注意这两个方法，有个设置需要预先定义CC_ENABLE_BOX2D_INTEGRATION=1才能使用box2d的方法，定义在Build Settings -> Apple LLVM 5.1 Preprocessing
    bird->setPTMRatio(PTM_RATIO);
    bird->setB2Body(birdBody);
    
    addChild(bird);
}

void HelloWorld::addGround()
{
    //创建精灵
    cocos2d::extension::CCPhysicsSprite* ground = cocos2d::extension::CCPhysicsSprite::create("ground.png");
    CCSize groundSize = ground->getContentSize();
    
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

void HelloWorld::addPipe(float dt)
{
    //添加一个随机的位置给小鸟通过(0,-5)
    float offset = -rand()%5;
    //添加上下两个pipe，同时pipe不受物理世界的重力影响
    //下pipe
    cocos2d::extension::CCPhysicsSprite* downPipe = cocos2d::extension::CCPhysicsSprite::create("down_bar.png");
    CCSize downPipeSize = downPipe->getContentSize();
    
    b2BodyDef downBodyDef;
    downBodyDef.type = b2_kinematicBody;//不受重力影响，但是可移动的类型
    downBodyDef.position = b2Vec2(screenSize.width/PTM_RATIO+2, downPipeSize.height/2/PTM_RATIO+offset);//从屏幕右边出来
    downBodyDef.linearVelocity = b2Vec2(-5, 0);//pipe往左移动的速度
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
    cocos2d::extension::CCPhysicsSprite* upPipe = cocos2d::extension::CCPhysicsSprite::create("up_bar.png");
    CCSize upPipeSize = upPipe->getContentSize();
    
    b2BodyDef upBodyDef;
    upBodyDef.type = b2_kinematicBody;//不受重力影响，但是可移动的类型
    upBodyDef.position = b2Vec2(screenSize.width/PTM_RATIO+2, downPipeSize.height/PTM_RATIO+offset+2+upPipeSize.height/2/PTM_RATIO);//从屏幕右边出来, up pipe比down pipe高出2米
    upBodyDef.linearVelocity = b2Vec2(-5, 0);//pipe往左移动的速度
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

void HelloWorld::addPipeContainer()
{
    pipeContainer = CCSprite::create();
    addChild(pipeContainer);
}

void HelloWorld::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    //获取小鸟在物理世界的body，并为其设置线性速度
    bird->getB2Body()->SetLinearVelocity(b2Vec2(0, 5));
}

void HelloWorld::update(float dt)
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
                //CCLog("Remove");
            }
            world->DestroyBody(b);
            //CCLog("Destory");
        }
    }
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
