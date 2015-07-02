#include "SkillSwordBase.h"
#include "../../../chara/CharaBase.h"
SkillSwordBase::SkillSwordBase(CharaBase* use_chara_obj, list<CharaBase*>* all_chara_list) : OneHandBase(use_chara_obj, all_chara_list) {
}
bool SkillSwordBase::checkExtendSkillUse() {

	// 鞘装備時限定
	if (this->_use_chara_obj->getSubWeaponType() == weaponType::sheath) {

		// 鞘装備時は片手直剣スキルも抜刀剣のバースト技扱い

		// バースト技は抜刀時にのみ使用可能
		if (this->_use_chara_obj->getWeaponState() == 0) {
			
			// 帯刀時は抜刀を行う
//			SkillBase set_skill_obj = new DrawnSword(this._use_chara_obj, this._use_chara_obj.getAllCharaList());
//			this->_use_chara_obj->setSkill(set_skill_obj);


			return false;
		}
	}
	return true;
}