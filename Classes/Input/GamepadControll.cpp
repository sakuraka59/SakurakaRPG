#include "GamepadControll.h"
#include "Gamepad.h"

#include "../GameMain/GameMain.h"
#include "../GameMain/GameUi/ItemUi.h"
#include "../GameMain/GameUi/SkillUi.h"
#include "../GameMain/GameUi/CraftUi.h"
//#include "../GameMain/GameUi/PlayUi.h"
//#include "../GameMain/GameUi/PlayerCommentUI.h"
//#include "../GameMain/GameUi/DefaultStateUI.h"



GamepadControll::GamepadControll() {
	this->_controll_type = gamePadControllType::chara;
}
gamePadControllType GamepadControll::getControllType() {
	return this->_controll_type;
}
void GamepadControll::setControllType(gamePadControllType controll_type, int controll_detail) {
	this->_before_controll_type = this->_controll_type;
	this->_controll_type = controll_type;

	
	switch (controll_type) {
	case gamePadControllType::item_ui:
		switch (controll_detail){
		case 1:
			GameMain::_item_ui_obj->openItemUiToObj();
			break;
		default:
			GameMain::_item_ui_obj->openItemUi();
			break;
		}
		
		break;
	case gamePadControllType::skill_ui:
		GameMain::_skill_ui_obj->openUi();
		break;
	case gamePadControllType::craft_ui:
		GameMain::_craft_ui_obj->openUi();
		break;

	}
	
}