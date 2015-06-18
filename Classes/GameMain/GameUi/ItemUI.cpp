#include "ItemUi.h"


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
	this->addChild(this->_player_item_list_obj);
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

}
// 自身のアイテムUIのみ開く
void ItemUi::openItemUi() {

}
// オブジェクトからのアイテム取得時に使う
void ItemUi::openItemUiToObj(){

}

// 更新処理
void ItemUi::Update() {
	if (this->_draw_flag != true) {
		return;
	}

	this->_player_item_list_obj->Update();
}