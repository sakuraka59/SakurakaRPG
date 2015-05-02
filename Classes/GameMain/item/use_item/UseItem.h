#pragma once
#include "../ItemBase.h"

class UseItem : public ItemBase
{
public: UseItem(CharaBase* chara_obj);
protected: int _num = 0;

//public: StateAuto(CharaBase* chara_obj);
public: int getNum();

public: void addNum(int add_num);

public: bool useItem() override;

// use item to invocation skill
public: virtual bool useSkill();
};