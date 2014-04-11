#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#define CC_ENABLE_BOX2D_INTEGRATION 1

#include "cocos2d.h"
//加载物理世界引擎
#include "Box2D.h"
#include "cocos-ext.h"

//定义app的高度是480像素，而box2d世界高度10米，如此有一个比例即48,这里定义成float型, ptm即pixel to meter
#define PTM_RATIO 48.0f

//因为我们将使用本类作为物理世界的碰触监听器，所以依靠c++的多重继承特性，我们继承b2ContactListener
class HelloWorld : public cocos2d::CCLayer, public b2ContactListener
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
    
    //step1.2 创建物理世界实例，b2Word在引入box2d后即可以引用，此实例对象在initWorld中被实例化
    b2World *world;
    //step1.3 创建小鸟实例
    cocos2d::extension::CCPhysicsSprite *bird;
    //step1.3.1 获取的屏幕高宽度, 注意这里类型定义
    cocos2d::CCSize screenSize;
    //定义update, scheduleUpdate每一帧都会调用这个方法
    virtual void update(float dt);
    //step1.5 给小鸟添加触摸事件，点击往上的速度
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    //step1.6.1 添加一个容器，把pipe的层都放在该容器中
    cocos2d::CCSprite *pipeContainer;
    //step1.7 监听碰撞的开始
    virtual void BeginContact(b2Contact* contact);
    
private:
    //step1. 开始添加小鸟
    void addBird();
    //step1.1 初始化物理世界
    void initWorld();
    //step1.4 添加地板
    void addGround();
    //step1.6 添加管道, 管道是每隔一定时间不断添加的并且往左移动，消失的pipe需要被销毁
    void addPipe(float dt);
    //step1.6.1
    void addPipeContainer();
    
    void startGame();
    void stopGame();
};

#endif // __HELLOWORLD_SCENE_H__
