#include "TestSheath.h"

TestSheath::TestSheath(CharaBase* chara_obj) : WeaponSheathBase(chara_obj) {
	this->_item_name = "�e�X�g�p��";
	this->_default_state[mainStateType::atk] = 2;
}

void TestSheath::setStateInit() {
}