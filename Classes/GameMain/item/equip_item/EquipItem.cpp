#include "EquipItem.h"

EquipItem::EquipItem(CharaBase* chara_obj) : ItemBase (chara_obj) {
	for (int state_type = static_cast<int>(mainStateType::hp); state_type < static_cast<int>(mainStateType::main_state_end); state_type++) {
		this->_default_state[static_cast<mainStateType>(state_type)] = 0;
	}
	/*
	for (mainStateType state_type : mainStateType) {

	}
	/*
	foreach(mainStateType state_type in Enum.GetValues(typeof(mainStateType))) {
		this._default_state[state_type] = 0;
	}
	foreach(abnormalStateType state_type in Enum.GetValues(typeof(abnormalStateType))) {
		this._state_default_list[state_type] = 0;
	}

	this.setStateInit();
	*/
}