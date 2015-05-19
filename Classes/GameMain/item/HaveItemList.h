#pragma once
#include "cocos2d.h"

class CharaBase;

class HaveItemList : public cocos2d::Ref
{

private: CharaBase* _chara_obj;


public: HaveItemList(CharaBase* chara_obj);

};