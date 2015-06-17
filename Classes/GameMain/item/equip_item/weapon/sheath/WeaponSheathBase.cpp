#include "WeaponSheathBase.h"
#include "../../../../chara/CharaBase.h"

WeaponSheathBase::WeaponSheathBase(CharaBase* chara_obj) : WeaponBase(chara_obj)
{
	this->_weapon_type = weaponType::sheath;
	this->_item_equip_type = equipType::sub_weapon;

}
bool WeaponSheathBase::checkExtendEquipItem() {
	// すでに鞘装備中は、外せる必要があるので、チェックを通す
	if (this->_chara_obj->getSubWeaponType() == weaponType::sheath) {
		return true;
	}
	// 片手直剣を装備中のみ、装備可能
	if (this->_chara_obj->getMainWeaponType() == weaponType::sword) {
		return true;
	}
	return false;
}

// 他装備時による装備解除チェック
bool WeaponSheathBase::checkEquipRelease() {
	if (this->_chara_obj->getMainWeaponType() != weaponType::sword) {
		return true;
	}
	return false;
}