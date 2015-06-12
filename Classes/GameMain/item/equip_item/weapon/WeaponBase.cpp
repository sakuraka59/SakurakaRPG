#include "WeaponBase.h"

WeaponBase::WeaponBase(CharaBase* chara_obj) : EquipItem(chara_obj)
{
	this->_item_equip_type = equipType::weapon;
	this->_have_item_type = haveItemType::weapon;
}

weaponType WeaponBase::getWeaponType() {
	return this->_weapon_type;
}