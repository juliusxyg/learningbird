//
//  AtlasResource.h
//  flapunicon
//
//  Created by Yingang Xue on 4/11/14.
//
//

#ifndef __flapunicon__AtlasResource__
#define __flapunicon__AtlasResource__

#include "cocos2d.h"

class AtlasResource
{
public:
    //单例，静态方法获取实例对象
    static AtlasResource* sharedResource();
    //销毁实例对象
    static void destoryResource();
    //载入atlas图片，并生成texture2d对象
    void loadImage(const char* filename);
    //解析atlas texture2d 对象，裁剪出各个精灵需要的资源，并存入字典中
    void parseImage(const char* filename);
    //getter 获取字典中的精灵帧
    cocos2d::CCSpriteFrame* getSpriteFrameByName(const char* name);
    
protected:
    AtlasResource();
    
private:
    std::map<char*, cocos2d::CCSpriteFrame*> _spriteFrames;
    
    static AtlasResource *instance;
    
    cocos2d::CCTexture2D *atlasTexture;
    
};

#endif /* defined(__flapunicon__AtlasResource__) */
