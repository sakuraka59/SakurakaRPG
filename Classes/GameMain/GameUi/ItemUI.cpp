#include "ItemUi.h"
#include "../GAME_SETTING.h"
#include "../../Input/Gamepad.h"

#include "ItemUi/ObjItemList.h"
#include "ItemUi/SearchObjItemList.h"
#include "../chara/CharaPlayer.h"

#include "../item/haveItemType.h"
#include "../item/equip_item/HaveEquipItemList.h"
#include "../item/use_item/HaveUseItemList.h"

#include <unordered_map>

using namespace std;
ItemUi::ItemUi() {

}
void ItemUi::Init(CharaPlayer* player_obj) {
	
	this->_player_obj = player_obj;
	
	int draw_position_correct = 50;
	this->_player_item_list_obj = new ObjItemList();
	this->_player_item_list_obj->setBackGround();
	this->_player_item_list_obj->setItemList(this->_player_obj->getHaveEquipItemList(), this->_player_obj->getHaveUseItemList());
	this->_player_item_list_obj->setPosition(draw_position_correct, 0);

	this->_search_item_list_obj = new SearchObjItemList();
	this->_search_item_list_obj->setBackGround();
	int search_obj_width = this->_search_item_list_obj->getDrawWidth();
	this->_search_item_list_obj->setPosition(GAME_WIDTH - search_obj_width - draw_position_correct, 0);
//	this->_search_item_list_obj->Init(this->_player_obj);


	this->_search_item_list_obj->setObjItemListObj(this->_player_item_list_obj);
	this->_player_item_list_obj->setObjItemListObj(this->_search_item_list_obj);

	// test image draw ----------------------------------------------
	this->_draw_flag = true;

	/*
	string image_pass = "img/map/ground/test_grass2.png";
	cocos2d::Sprite* sprite_data = cocos2d::Sprite::create(image_pass);

	this->addChild(sprite_data);
	*/
}
// 閉じる
void ItemUi::closeItemUi() {
	Gamepad::GameControll->setControllType(gamePadControllType::chara);
	this->removeAllChildren();
	this->_player_item_list_obj->closeItemList();
	this->_search_item_list_obj->closeItemList();
	this->_draw_flag = false;
}
// 自身のアイテムUIのみ開く
void ItemUi::openItemUi() {
	this->_player_item_list_obj->openItemListInit();
	this->_player_item_list_obj->setOnlyFlag(true);
	this->_draw_flag = true;
	this->_search_obj_flag = false;

	this->addChild(this->_player_item_list_obj);

	this->changeControllState(itemUiControllState::player);
}
// オブジェクトからのアイテム取得時に使う
void ItemUi::openItemUiToObj(){
	this->_player_obj->sendComment("何があるかな・・・？");
	this->openItemUi();
	
//	this->_player_item_list_obj->openItemListInit(this->_obj_item_list);
	this->_search_item_list_obj->setItemList(this->_search_obj_equip_item_list, this->_search_obj_use_item_list);
	this->_search_item_list_obj->openItemListInit();



	// openItemUiの後に設定
	this->_player_item_list_obj->setOnlyFlag(false);
	this->_search_obj_flag = true;

	this->addChild(this->_search_item_list_obj);

	this->changeControllState(itemUiControllState::search_obj);

}
// 調べたオブジェクトのアイテム一覧をセット
void ItemUi::setSearchObjItemList(HaveEquipItemList* equip_item_list, HaveUseItemList* use_item_list) {
	this->_search_obj_equip_item_list = equip_item_list;
	this->_search_obj_use_item_list = use_item_list;
	
}
// 更新処理
void ItemUi::Update() {
	if (this->_draw_flag != true) {
		return;
	}

	if (Gamepad::GameControll->getControllType() != gamePadControllType::item_ui) {
		return;
	}

	if (Gamepad::Triangle->isPush() == true) {
		this->closeItemUi();
		return;
	}

	// オブジェクト調べ中の場合、UI操作変更可能にする
	if (this->_search_obj_flag == true) {
		if (Gamepad::L1->isPush() == true) {
			this->changeControllState(itemUiControllState::player);
			return;
		} else if (Gamepad::R1->isPush() == true) {
			this->changeControllState(itemUiControllState::search_obj);
			return;
		}
	}
	switch (this->_controll_state) {
	case itemUiControllState::player:
		this->_player_item_list_obj->Update();
		break;
	case itemUiControllState::search_obj:
		if (this->_search_obj_flag == true) {
			this->_search_item_list_obj->Update();
		} else {
			this->changeControllState(itemUiControllState::player);
			this->_player_item_list_obj->Update();
		}

		break;
	}


}
void ItemUi::changeControllState(itemUiControllState controll_state) {
	this->_controll_state = controll_state;
}
void ItemUi::removeEquipItem(EquipItem* remove_item_obj) {
	this->_player_item_list_obj->removeEquipItem(remove_item_obj);
}