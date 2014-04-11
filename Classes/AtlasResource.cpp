//
//  AtlasResource.cpp
//  flapunicon
//
//  Created by Yingang Xue on 4/11/14.
//
//

#include "AtlasResource.h"

//构造函数，什么都不干
AtlasResource::AtlasResource(){
    spriteFramesDictionary = cocos2d::CCDictionary::create();
}

AtlasResource* AtlasResource::instance = NULL;

AtlasResource* AtlasResource::sharedResource()
{
    if(instance == NULL)
    {
        instance = new AtlasResource();
    }
    return instance;
}

void AtlasResource::destoryResource()
{
    CC_SAFE_DELETE(instance);
}

void AtlasResource::loadImage(const char *fileImage, const char* filename)
{
    cocos2d::CCTexture2D *atlasTexture = cocos2d::CCTextureCache::sharedTextureCache()->addImage(fileImage);
    
    cocos2d::CCString *fileData = cocos2d::CCString::createWithContentsOfFile(filename);
    int pos = 0;
    pos = fileData->m_sString.find_first_of("\n");
    std::string line = fileData->m_sString.substr(0, pos);
    fileData->m_sString = fileData->m_sString.substr(pos+1);
    while (line != "")
    {
        char name[20];
        int width, height;
        float startX, startY, endX, endY;
        sscanf(line.c_str(), "%s %d %d %f %f %f %f",
                   name, &width, &height, &startX, &startY, &endX, &endY);
        cocos2d::CCSpriteFrame* spriteFrame = cocos2d::CCSpriteFrame::createWithTexture(atlasTexture, cocos2d::CCRect(1024*startX, 1024*startY, width, height));
        
        spriteFramesDictionary->setObject(spriteFrame, name);
        
        pos = fileData->m_sString.find_first_of("\n");
        line = fileData->m_sString.substr(0, pos);
        fileData->m_sString = fileData->m_sString.substr(pos+1);
    }
}

cocos2d::CCSpriteFrame* AtlasResource::getSpriteFrameByName(const char *name)
{
    return (cocos2d::CCSpriteFrame*)spriteFramesDictionary->objectForKey(name);
}