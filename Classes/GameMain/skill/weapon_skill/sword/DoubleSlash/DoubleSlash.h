#pragma once
#include "../SkillSwordBase.h"

class DoubleSlash : public SkillSwordBase {


public: DoubleSlash(CharaBase* use_chara_obj, list<CharaBase*>* all_chara_list);
protected: void attackUpdateEffect() override;
protected: void attackHitEffect(CharaBase* check_chara_obj) override;
};