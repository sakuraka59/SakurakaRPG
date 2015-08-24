#include "ControlSettingList.h"
#include "ControlSetting.h"

#include "../CharaPlayer.h"

ControllSettingList::ControllSettingList(CharaPlayer* chara_obj) {
	this->_chara_obj = chara_obj;
}
ControllSetting* ControllSettingList::getControllSetting() {
	weaponType main_weapon = this->_chara_obj->getMainWeaponType();
	weaponType sub_weapon = this->_chara_obj->getSubWeaponType();

	if (this->_controll_setting_list[main_weapon][sub_weapon] == nullptr) {
		this->_controll_setting_list[main_weapon][sub_weapon] = new ControllSetting(this->_chara_obj);
	}
	return this->_controll_setting_list[main_weapon][sub_weapon];
}

ControllSetting* ControllSettingList::testControllSetting(weaponType main_weapon, weaponType sub_weapon) {

	if (this->_controll_setting_list[main_weapon][sub_weapon] == nullptr) {
		this->_controll_setting_list[main_weapon][sub_weapon] = new ControllSetting(this->_chara_obj);
	}
	return this->_controll_setting_list[main_weapon][sub_weapon];
}