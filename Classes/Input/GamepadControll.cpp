#include "GamepadControll.h"
#include "Gamepad.h"

#include "../GameMain/GameMain.h"
#include "../GameMain/GameUi/ItemUi.h"
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
	}
	

}