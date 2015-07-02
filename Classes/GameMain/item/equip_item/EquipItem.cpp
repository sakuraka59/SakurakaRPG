#include "EquipItem.h"
#include "../../chara/CharaBase.h"

using namespace std;
EquipItem::EquipItem(CharaBase* chara_obj) : ItemBase (chara_obj) {
	for (int state_type = static_cast<int>(mainStateType::no_type) + 1; state_type < static_cast<int>(mainStateType::enum_end); state_type++) {
		this->_default_state[static_cast<mainStateType>(state_type)] = 0;
	}

	for (int state_type = static_cast<int>(abnormalStateType::no_type) + 1; state_type < static_cast<int>(abnormalStateType::enum_end); state_type++) {
		this->_state_default_list[static_cast<abnormalStateType>(state_type)] = 0;
	}
	this->setStateInit();
	/*
	foreach(mainStateType state_type in Enum.GetValues(typeof(mainStateType))) {
		this._default_state[state_type] = 0;
	}
	foreach(abnormalStateType state_type in Enum.GetValues(typeof(abnormalStateType))) {
		this._state_default_list[state_type] = 0;
	}
	*/
	
	
}
void EquipItem::setStateInit() {

}
bool EquipItem::useItem(){

	if (this->_item_equip_type == equipType::no_type) {
		return false;
	}
	if (this->checkExtendEquipItem() != true) {
		return false;
	}

	if (this->_chara_obj->checkActionFlag() != true) {
		return false;
	}

	this->_chara_obj->setEquipItem(this->_item_equip_type, this, this->_state_default_list);


	this->releaseEquipChain();
	return true;
}
unordered_map<mainStateType, int> EquipItem::getItemState() {
	return this->_default_state;
}
//-------------------------------------------------------------------
// 装備条件拡張用
//-------------------------------------------------------------------
bool EquipItem::checkExtendEquipItem() {
	return true;
}
// 装備時による他装備解除
void EquipItem::releaseEquipChain() {
	return;
}
// 他装備時の装備解除チェック
bool EquipItem::checkEquipRelease() {
	return false;
}

unordered_map<abnormalStateType, int> EquipItem::getStateDefaultList() {
	return this->_state_default_list;
}

void EquipItem::setEquipFlag() {
	this->_equip_flag = true;
}
void EquipItem::unsetEquipFlag() {
	this->_equip_flag = false;
}
bool EquipItem::getEquipFlag() {
	return this->_equip_flag;
}
