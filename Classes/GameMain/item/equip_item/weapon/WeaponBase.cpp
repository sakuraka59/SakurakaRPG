#include "WeaponBase.h"

WeaponBase::WeaponBase() : EquipItem()
{
	this->_item_equip_type = equipType::weapon;
	this->_have_item_type = haveItemType::weapon;
}

weaponType WeaponBase::getWeaponType() {
	return this->_weapon_type;
}
