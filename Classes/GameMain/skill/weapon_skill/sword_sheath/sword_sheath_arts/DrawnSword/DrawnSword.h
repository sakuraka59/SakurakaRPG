#pragma once
#include "../../SkillSwordSheathArtsBase.h"

class DrawnSword : public SkillSwordSheathArtsBase {


public: DrawnSword(CharaBase* use_chara_obj, list<CharaBase*>* all_chara_list);
protected: void skillInit() override;
protected: void attackUpdateEffect() override;
protected: void attackHitEffect(CharaBase* check_chara_obj) override;
};