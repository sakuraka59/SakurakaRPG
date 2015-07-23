#include "WeaponRapierBase.h"
#include "../../../../chara/CharaBase.h"

WeaponRapierBase::WeaponRapierBase() : WeaponBase(){
	this->_weapon_type = weaponType::rapier;
}