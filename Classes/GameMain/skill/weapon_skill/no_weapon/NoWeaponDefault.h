#pragma once
#include "../../skill_type/SkillAttack.h"

class NoWeaponDefault : public SkillAttack {

public: NoWeaponDefault(CharaBase* use_chara_obj, std::list<CharaBase*> *all_chara_list);
public: void skillExtendInit() override;
protected: void attackHitEffect(CharaBase* check_chara_obj) override;
};