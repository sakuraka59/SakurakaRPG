#include "SkillSwordSheathArtsBase.h"
#include "../../../chara/CharaBase.h"
SkillSwordSheathArtsBase::SkillSwordSheathArtsBase(CharaBase* use_chara_obj, list<CharaBase*>* all_chara_list) : OneHandBase(use_chara_obj, all_chara_list) {
}
bool SkillSwordSheathArtsBase::checkExtendSkillUse() {

	// �A�[�c�Z�͔������ɂ̂ݎg�p�\
	if (this->_use_chara_obj->getWeaponState() != 0) {

		// �ѓ�����
//		SkillBase set_skill_obj = new StowSword(this._use_chara_obj, this._use_chara_obj.getAllCharaList());
//		this._use_chara_obj.setSkill(set_skill_obj);


		return false;
	}
	return true;
}