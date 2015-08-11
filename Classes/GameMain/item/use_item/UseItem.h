#pragma once
#include "../ItemBase.h"
#include "../../chara/abnormal_state/abnormalStateType.h"

//using namespace std;

class UseItem : public ItemBase {

protected: int _num = 0;
protected: string _use_item_id = "";
protected: bool _use_flag = false;
public: UseItem();
//public: StateAuto(CharaBase* chara_obj);
protected: std::unordered_map<mainStateType, int> _default_state;
protected: std::unordered_map<mainStateType, int> _correct_state;
protected: std::unordered_map<abnormalStateType, int> _state_default_list;
protected: int _effect_frame;

public: int getNum();

public: void addNum(int add_num);

public: bool useItem() override;


public: string getUseItemId();
public: void setUseItemId(string use_item_id);

public: void setStateData(unordered_map<mainStateType, int> default_state);
public: void setCorrectStateData(unordered_map<mainStateType, int> correct_state);
public: void setEffectFrame(int effect_frame);
public: unordered_map<mainStateType, int> getStateData();
public: unordered_map<mainStateType, int> getCorrectData();
public: int getEffectFrame();


// use item to invocation skill
public: virtual bool useSkill();

public: bool removeUseItem(int num);
};