#include "TestSheath.h"

TestSheath::TestSheath() : WeaponSheathBase() {
	this->_item_name = "�e�X�g�p��";
	this->_default_state[mainStateType::atk] = 2;
}

void TestSheath::setStateInit() {
}