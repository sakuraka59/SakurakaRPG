#pragma once
#include "cocos2d.h"

class CharaBase;

class HaveItemListBase : public cocos2d::Ref
{

protected: CharaBase* _chara_obj;


public: HaveItemListBase(CharaBase* chara_obj);

};