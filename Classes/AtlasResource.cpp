//
//  AtlasResource.cpp
//  flapunicon
//
//  Created by Yingang Xue on 4/11/14.
//
//

#include "AtlasResource.h"
//初始化实例指针为空指针
AtlasResource* instance = nullptr;
//构造函数，什么都不干
AtlasResource::AtlasResource(){}

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

void AtlasResource::loadImage(const char *filename)
{
    atlasTexture = cocos2d::CCTextureCache::sharedTextureCache()->addImage(filename);
}

void AtlasResource::parseImage(const char *filename)
{
    char* data = NULL;
    unsigned long fileSize = 0;
    data = cocos2d::CCFileUtils::sharedFileUtils()->getFileData(filename, "r", fileSize);
    
    int lineStart = 0, lineEnd = 0;
    for(lineEnd=0; lineEnd<fileSize; lineEnd++)
    {
        if(strcmp("\n", data[lineEnd]))
        {
            char* line = data.substr(lineStart, lineEnd);
            char* name;
            int width, height;
            float startX, startY, endX, endY;
            sscanf(line.c_str(), "%s %d %d %f %f %f %f %f",
                   name, &width, &height, &startX, &startY, &endX, &endY);
            
            cocos2d::CCrect rect = CCRectMake(1024*startY, 1024*startY, width, height);
            cocos2d::CCSpriteFrame* spriteFrame = cocos2d::CCSpriteFrame::createWithTexture(atlasTexture, rect);
            this->_spriteFrames.insert(name, spriteFrame);
            
            lineStart = lineEnd+1;
        }
    }
}

cocos2d::CCSpriteFrame* AtlasResource::getSpriteFrameByName(const char *name)
{
    return this->_spriteFrames.at(name);
}