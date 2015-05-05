#include "WeaponBase.h"

WeaponBase::WeaponBase(CharaBase* chara_obj) : EquipItem(chara_obj)
{
	this->_item_type = equipType::weapon;
}

weaponType WeaponBase::getWeaponType() {
	return this->_weapon_type;
}