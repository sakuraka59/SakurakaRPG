#include "CraftUi.h"
#include "CraftUi/CraftUiBase.h"

#include "../GAME_SETTING.h"

#include "../../Input/Gamepad.h"

CraftUi::CraftUi() {

}
void CraftUi::Init(CharaPlayer* player_obj) {

	// リスト表示位置補正用
	int draw_position_correct = 50;
	this->_player_obj = player_obj;
	this->_list_ui_obj = new CraftUiBase(player_obj);

	// リスト表示の横幅を取得
//	int search_obj_width = this->_skill_list_ui_obj->getDrawWidth();

	this->_list_ui_obj->setPosition(0 + draw_position_correct, 0);
}
void CraftUi::openUi() {
	this->_list_ui_obj->openUi();

	this->_draw_flag = true;
	this->addChild(this->_list_ui_obj);
}
void CraftUi::closeUi() {
	this->_list_ui_obj->closeUi();

	Gamepad::GameControll->setControllType(gamePadControllType::chara);

	this->_draw_flag = false;
	this->removeAllChildren();
}
void CraftUi::Update() {
	if (this->_draw_flag != true) {
		return;
	}
	if (Gamepad::GameControll->getControllType() != gamePadControllType::craft_ui) {
		return;
	}

	// △ボタンでUI閉じる
	if (Gamepad::Triangle->isPush() == true) {
		this->closeUi();
		return;
	}

	this->_list_ui_obj->Update();
}