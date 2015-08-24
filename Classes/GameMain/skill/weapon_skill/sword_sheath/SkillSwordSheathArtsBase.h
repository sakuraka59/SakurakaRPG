#pragma once
#include "../OneHandBase.h"


class SkillSwordSheathArtsBase : public OneHandBase {
public: SkillSwordSheathArtsBase(CharaBase* use_chara_obj, list<CharaBase*>* all_chara_list);
public: bool checkExtendSkillUse() override;
};