#pragma once
#include "../skill_type/SkillMyself.h"
#include "../../chara/mainStateType.h"
using namespace std;
class ItemEffect : public SkillMyself {

private: unordered_map<mainStateType, int> _default_state;
private: unordered_map<mainStateType, int> _correct_state;
private: int _effect_frame_num = 0;

public: ItemEffect(CharaBase* use_chara_obj, list<CharaBase*>* all_chara_list,
	unordered_map<mainStateType, int> default_state, unordered_map<mainStateType, int> correct_state, int effect_frame_num);
public: void skillInit() override;
protected: void attackHitEffect(CharaBase* check_chara_obj) override;
};