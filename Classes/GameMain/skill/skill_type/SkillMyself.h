#pragma once
#include <unordered_map>
#include "../SkillBase.h"
class CharaBase;

using namespace std;
class SkillMyself : public SkillBase {
public: SkillMyself(CharaBase* use_chara_obj, list<CharaBase*>* all_chara_list);
protected: bool updateSkillEffect() override;
};