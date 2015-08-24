#include "ControlSetting.h"
#include "ControllSettingDetail.h"

#include "../CharaPlayer.h"
#include "../../skill/SkillBase.h"
#include "../../item/use_item/UseItem.h"


ControllSetting::ControllSetting(CharaPlayer* chara_obj) {
	for (int state_type = static_cast<int>(buttonSettingType::_no_type) + 1; state_type < static_cast<int>(buttonSettingType::_enum_end); state_type++) {
		this->_setting_list[static_cast<buttonSettingType>(state_type)] = new ControllSettingDetail(chara_obj);
	}
	/*
	this->_setting_list[buttonSettingType::circle_l1] = new ControllSettingDetail(chara_obj);
	this->_setting_list[buttonSettingType::cross_l1] = new ControllSettingDetail(chara_obj);
	this->_setting_list[buttonSettingType::square_l1] = new ControllSettingDetail(chara_obj);
	this->_setting_list[buttonSettingType::triangle_l1] = new ControllSettingDetail(chara_obj);

	this->_setting_list[buttonSettingType::circle_l2] = new ControllSettingDetail(chara_obj);
	this->_setting_list[buttonSettingType::cross_l2] = new ControllSettingDetail(chara_obj);
	this->_setting_list[buttonSettingType::square_l2] = new ControllSettingDetail(chara_obj);
	this->_setting_list[buttonSettingType::triangle_l2] = new ControllSettingDetail(chara_obj);
	*/
}
void ControllSetting::setControllSettingSkill(buttonSettingType button_type, SkillBase* skill_obj) {
	this->_setting_list[button_type]->setSkill(skill_obj);
}
void ControllSetting::setControllSettingItem(buttonSettingType button_type, UseItem* item_obj) {
	this->_setting_list[button_type]->setItem(item_obj);
}
void ControllSetting::useControllButton(buttonSettingType button_type) {
	this->_setting_list[button_type]->useSetObj();
}
void ControllSetting::resetControllButton(buttonSettingType button_type) {
//	this->_setting_list[button_type]->();
}