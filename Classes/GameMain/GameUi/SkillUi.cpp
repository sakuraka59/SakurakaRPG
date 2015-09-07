#include "SkillUi.h"
#include "SkillUi/SkillListUi.h"

#include "../GAME_SETTING.h"

#include "../../Input/Gamepad.h"

SkillUi::SkillUi() {

}
void SkillUi::Init(CharaPlayer* player_obj) {
	
	// ���X�g�\���ʒu�␳�p
	int draw_position_correct = 50;
	this->_player_obj = player_obj;
	this->_skill_list_ui_obj = new SkillListUi(player_obj);
	
	// ���X�g�\���̉������擾
	int search_obj_width = this->_skill_list_ui_obj->getDrawWidth();
	
	this->_skill_list_ui_obj->setPosition(GAME_WIDTH - search_obj_width - draw_position_correct, 0);
}
void SkillUi::openUi() {
	this->_skill_list_ui_obj->openUi();

	this->_draw_flag = true;
	this->addChild(this->_skill_list_ui_obj);
}
void SkillUi::closeUi() {
	this->_skill_list_ui_obj->closeUi();

	Gamepad::GameControll->setControllType(gamePadControllType::chara);

	this->_draw_flag = false;
	this->removeAllChildren();
}
void SkillUi::Update() {
	if (this->_draw_flag != true) {
		return;
	}
	if (Gamepad::GameControll->getControllType() != gamePadControllType::skill_ui) {
		return;
	}

	// ���{�^����UI����
	if (Gamepad::Triangle->isPush() == true) {
		this->closeUi();
		return;
	}

	this->_skill_list_ui_obj->Update();
}