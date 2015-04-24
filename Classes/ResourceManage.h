#ifndef __RESOURCE_MANAGE_H__
#define __RESOURCE_MANAGE_H__

#include "cocos2d.h"
#include <unordered_map>       // �n�b�V���e�[�u��


class ResourceManage
{

public: static std::unordered_map<std::string, cocos2d::Sprite*> _sprite_cache;

public: ResourceManage();
public: static cocos2d::Sprite* getSprite(std::string file_name);
};

#endif //__RESOURCE_MANAGE_H__