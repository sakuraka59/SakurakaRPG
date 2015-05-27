#include "SkillMyself.h"


SkillMyself::SkillMyself(CharaBase* use_chara_obj, list<CharaBase*>* all_chara_list) : SkillBase(use_chara_obj, all_chara_list)
{

}
bool SkillMyself::updateSkillEffect() {
	this->attackHitEffect(this->_use_chara_obj);
	this->setDeleteFlag();
	return true;
}