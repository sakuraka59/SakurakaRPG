#pragma once
#include "../OneHandBase.h"


class SkillSwordBase : public OneHandBase {
public: SkillSwordBase(CharaBase* use_chara_obj, list<CharaBase*>* all_chara_list);
public: bool checkExtendSkillUse() override;
};