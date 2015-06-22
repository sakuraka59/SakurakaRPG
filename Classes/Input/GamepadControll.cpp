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
void GamepadControll::setControllType(gamePadControllType controll_type) {
	this->_controll_type = controll_type;

	
	switch (controll_type) {
	case gamePadControllType::item_ui:
		GameMain::_item_ui_obj->openItemUi();
		break;
	}
	

}