#include "TestSword.h"

TestSword::TestSword() : WeaponSwordBase()
{
	this->_item_name = "テスト用片手剣";
	this->_default_state[mainStateType::atk] = 10;
	//			this._state_default_list[abnormalStateType.poison] = 1;
}