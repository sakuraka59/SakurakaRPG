#include "WeaponSwordBase.h"
#include "../../../../chara/CharaBase.h"

WeaponSwordBase::WeaponSwordBase(CharaBase* chara_obj) : WeaponBase(chara_obj){
	this->_weapon_type = weaponType::sword;
}