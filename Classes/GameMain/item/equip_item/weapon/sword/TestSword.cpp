#include "TestSword.h"

TestSword::TestSword(CharaBase* chara_obj) : WeaponSwordBase(chara_obj)
{
	this->_item_name = "�e�X�g�p�Ў茕";
	this->_default_state[mainStateType::atk] = 10;
	//			this._state_default_list[abnormalStateType.poison] = 1;
}