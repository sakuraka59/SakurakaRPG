#include "EquipItem.h"

using namespace std;
EquipItem::EquipItem(CharaBase* chara_obj) : ItemBase (chara_obj) {
	for (int state_type = static_cast<int>(mainStateType::hp); state_type < static_cast<int>(mainStateType::main_state_end); state_type++) {
		this->_default_state[static_cast<mainStateType>(state_type)] = 0;
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

	if (this->_item_type == equipType::no_type) {
		return false;
	}
	if (this->checkExtendEquipItem() != true) {
		return false;
	}
//	this->_chara_obj.setEquipItem(this._item_type, this, this._state_default_list);


//	this.releaseEquipChain();
	return true;
}
unordered_map<mainStateType, int> EquipItem::getItemState() {
	return this->_default_state;
}
//-------------------------------------------------------------------
// ���������g���p
//-------------------------------------------------------------------
bool EquipItem::checkExtendEquipItem() {
	return true;
}
// �������ɂ�鑼��������
void EquipItem::releaseEquipChain() {
	return;
}
// ���������̑��������`�F�b�N
bool EquipItem::checkEquipRelease() {
	return false;
}

unordered_map<abnormalStateType, int> EquipItem::getStateDefaultList() {
	return this->_state_default_list;
}
