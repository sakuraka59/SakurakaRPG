#include "ControllSettingDetail.h"

#include "../CharaPlayer.h"

#include "../../item/use_item/UseItem.h"
#include "../../skill/SkillBase.h"


ControllSettingDetail::ControllSettingDetail(CharaPlayer* chara_obj) {
	this->_chara_obj = chara_obj;
}
// スキルをセットする
void ControllSettingDetail::setSkill(SkillBase* skill_obj) {
	this->resetObj();
	this->_skill_obj = skill_obj;
	this->_setting_type = settingDetailType::skill;
}
// アイテムをセットする
void ControllSettingDetail::setItem(UseItem* item_obj) {
	this->resetObj();
	this->_item_obj = item_obj;
	this->_setting_type = settingDetailType::item;
}
// 設定をリセットする
void ControllSettingDetail::resetObj() {
	this->_skill_obj = nullptr;
	this->_item_obj = nullptr;
	this->_setting_type = settingDetailType::no_set;
}
 // セットしたものを使用する
void ControllSettingDetail::useSetObj() {
	switch (this->_setting_type) {
	case settingDetailType::skill:
		this->useSkill();
		break;
	case settingDetailType::item:
		this->useItem();
		break;
	}
}
// セットしたスキルを使用する
void ControllSettingDetail::useSkill() {
	this->_chara_obj->setSkill(this->_skill_obj);
}
// セットしたアイテムを使用する
void ControllSettingDetail::useItem() {
	this->_item_obj->useItem();
}