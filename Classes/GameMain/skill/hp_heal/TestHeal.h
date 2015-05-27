#pragma once
#include "../skill_type/SkillMyself.h"
using namespace std;
class TestHeal : public SkillMyself {
public: TestHeal(CharaBase* use_chara_obj, list<CharaBase*>* all_chara_list);
public: void skillInit() override;
protected: void attackHitEffect(CharaBase* check_chara_obj) override;
};