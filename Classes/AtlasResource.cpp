//
//  AtlasResource.cpp
//  flapunicon
//
//  Created by Yingang Xue on 4/11/14.
//
//

#include "AtlasResource.h"

USING_NS_CC;

//构造函数，什么都不干
AtlasResource::AtlasResource(){}

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

void AtlasResource::parseImage(const char *filename, CCTexture2D *atlasTexture)
{    
    CCString *fileData = CCString::createWithContentsOfFile(filename);
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
        CCSpriteFrame* spriteFrame = CCSpriteFrame::createWithTexture(atlasTexture, CCRect(1024*startX, 1024*startY, width, height));
        
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(spriteFrame, name);
        CCLog("%s",name);
        
        pos = fileData->m_sString.find_first_of("\n");
        line = fileData->m_sString.substr(0, pos);
        fileData->m_sString = fileData->m_sString.substr(pos+1);
    }
}

CCSpriteFrame* AtlasResource::getSpriteFrameByName(const char *name)
{
    CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name);
    return frame;
}