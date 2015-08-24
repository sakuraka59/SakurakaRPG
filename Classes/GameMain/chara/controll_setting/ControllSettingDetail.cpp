#include "ControllSettingDetail.h"

#include "../CharaPlayer.h"

#include "../../item/use_item/UseItem.h"
#include "../../skill/SkillBase.h"


ControllSettingDetail::ControllSettingDetail(CharaPlayer* chara_obj) {
	this->_chara_obj = chara_obj;
}
// �X�L�����Z�b�g����
void ControllSettingDetail::setSkill(SkillBase* skill_obj) {
	this->resetObj();
	this->_skill_obj = skill_obj;
	this->_setting_type = settingDetailType::skill;
}
// �A�C�e�����Z�b�g����
void ControllSettingDetail::setItem(UseItem* item_obj) {
	this->resetObj();
	this->_item_obj = item_obj;
	this->_setting_type = settingDetailType::item;
}
// �ݒ�����Z�b�g����
void ControllSettingDetail::resetObj() {
	this->_skill_obj = nullptr;
	this->_item_obj = nullptr;
	this->_setting_type = settingDetailType::no_set;
}
 // �Z�b�g�������̂��g�p����
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
// �Z�b�g�����X�L�����g�p����
void ControllSettingDetail::useSkill() {
	this->_chara_obj->setSkill(this->_skill_obj);
}
// �Z�b�g�����A�C�e�����g�p����
void ControllSettingDetail::useItem() {
	this->_item_obj->useItem();
}