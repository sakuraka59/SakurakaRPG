#include "SkillSwordBase.h"
#include "../../../chara/CharaBase.h"

#include "../sword_sheath/sword_sheath_arts/DrawnSword/DrawnSword.h"
SkillSwordBase::SkillSwordBase(CharaBase* use_chara_obj, list<CharaBase*>* all_chara_list) : OneHandBase(use_chara_obj, all_chara_list) {
}
bool SkillSwordBase::checkExtendSkillUse() {

	// �⑕��������
	if (this->_use_chara_obj->getSubWeaponType() == weaponType::sheath) {

		// �⑕�����͕Ў蒼���X�L�����������̃o�[�X�g�Z����

		// �o�[�X�g�Z�͔������ɂ̂ݎg�p�\
		if (this->_use_chara_obj->getWeaponState() == 0) {
			
			// �ѓ����͔������s��
			DrawnSword* set_skill_obj = new DrawnSword(this->_use_chara_obj, this->_use_chara_obj->getAllCharaList());
			this->_use_chara_obj->setSkill(set_skill_obj);


			return false;
		}
	}
	return true;
}