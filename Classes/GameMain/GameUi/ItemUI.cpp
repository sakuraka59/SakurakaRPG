#include "ItemUi.h"
#include "../../Input/Gamepad.h"

#include "ItemUi/ObjItemList.h"
#include "../chara/CharaPlayer.h"


#include <unordered_map>

using namespace std;
ItemUi::ItemUi() {

}
void ItemUi::Init(CharaPlayer* player_obj) {
	
	this->_player_obj = player_obj;
	
	this->_player_item_list_obj = new ObjItemList(this->_player_obj->getHaveUseItemList(), this->_player_obj->getHaveEquipItemList());
	this->_player_item_list_obj->setPosition(50, 0);
	
	// test image draw ----------------------------------------------
	this->_draw_flag = true;

	/*
	string image_pass = "img/map/ground/test_grass2.png";
	cocos2d::Sprite* sprite_data = cocos2d::Sprite::create(image_pass);

	this->addChild(sprite_data);
	*/
}
// ����
void ItemUi::closeItemUi() {
//	Gamepad::GameControll->setControllType(gamePadControllType::chara);
//	this->removeAllChildren();
}
// ���g�̃A�C�e��UI�̂݊J��
void ItemUi::openItemUi() {
	this->addChild(this->_player_item_list_obj);
}
// �I�u�W�F�N�g����̃A�C�e���擾���Ɏg��
void ItemUi::openItemUiToObj(){

}

// �X�V����
void ItemUi::Update() {
	if (this->_draw_flag != true) {
		return;
	}

	if (Gamepad::GameControll->getControllType() != gamePadControllType::item_ui) {
		return;
	}

	this->_player_item_list_obj->Update();

	if (Gamepad::Triangle->isPush() == true) {
		this->closeItemUi();
	}
}