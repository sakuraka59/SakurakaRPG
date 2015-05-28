#pragma once
#include "../../skill_type/SkillMagic.h"

using namespace std;
class MagicShot : public SkillMagic {

public: MagicShot(CharaBase* use_chara_obj, list<CharaBase*>* all_chara_list);
public: void skillInit() override;
protected: void skillActiveEffect(CharaBase* check_chara_obj) override;
};