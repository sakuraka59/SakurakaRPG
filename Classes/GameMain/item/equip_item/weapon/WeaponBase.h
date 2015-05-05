#pragma once

#include "../EquipItem.h"
#include "weaponType.h"

class CharaBase;

class WeaponBase : EquipItem
{
protected: bool two_hand_flag = false;
protected: bool sub_only_flag = true; // (two_hand_flag = true) to false only

protected: weaponType _weapon_type = weaponType::no_type;
protected: weaponType _main_only_type = weaponType::all_weapon;

public: WeaponBase(CharaBase* chara_obj);

public: weaponType getWeaponType();

};