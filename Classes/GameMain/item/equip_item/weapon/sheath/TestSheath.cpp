#include "TestSheath.h"

TestSheath::TestSheath() : WeaponSheathBase() {
	this->_item_name = "テスト用鞘";
	this->_default_state[mainStateType::atk] = 2;
}

void TestSheath::setStateInit() {
}