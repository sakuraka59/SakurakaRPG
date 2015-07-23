#pragma once
#include "../ItemBase.h"

//using namespace std;

class UseItem : public ItemBase {

protected: int _num = 0;
protected: string _use_item_id = "";
public: UseItem();
//public: StateAuto(CharaBase* chara_obj);
public: int getNum();

public: void addNum(int add_num);

public: bool useItem() override;


public: string getUseItemId();
public: void setUseItemId(string use_item_id);
// use item to invocation skill
public: virtual bool useSkill();
};