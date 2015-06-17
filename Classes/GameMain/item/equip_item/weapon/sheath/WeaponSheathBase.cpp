#include "WeaponSheathBase.h"
#include "../../../../chara/CharaBase.h"

WeaponSheathBase::WeaponSheathBase(CharaBase* chara_obj) : WeaponBase(chara_obj)
{
	this->_weapon_type = weaponType::sheath;
	this->_item_equip_type = equipType::sub_weapon;

}
bool WeaponSheathBase::checkExtendEquipItem() {
	// ���łɏ⑕�����́A�O����K�v������̂ŁA�`�F�b�N��ʂ�
	if (this->_chara_obj->getSubWeaponType() == weaponType::sheath) {
		return true;
	}
	// �Ў蒼���𑕔����̂݁A�����\
	if (this->_chara_obj->getMainWeaponType() == weaponType::sword) {
		return true;
	}
	return false;
}

// ���������ɂ�鑕�������`�F�b�N
bool WeaponSheathBase::checkEquipRelease() {
	if (this->_chara_obj->getMainWeaponType() != weaponType::sword) {
		return true;
	}
	return false;
}