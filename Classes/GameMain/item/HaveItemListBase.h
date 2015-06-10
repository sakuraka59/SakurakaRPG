#pragma once
#include "cocos2d.h"

class CharaBase;

class HaveItemListBase : public cocos2d::Ref
{

private: CharaBase* _chara_obj;


public: HaveItemListBase(CharaBase* chara_obj);

};