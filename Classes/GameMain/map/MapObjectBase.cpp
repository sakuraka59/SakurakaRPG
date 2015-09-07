#include "MapObjectBase.h"
#include "../GAME_SETTING.h"
#include "../hit/HitSquare.h"
#include "../../Random.h"
#include "../chara/CharaBase.h"

#include "../GameUi/ItemUi.h"
#include "../GameMain.h"

#include "../../Input/Gamepad.h"

#include "../item/ItemMasterList.h"

#include "../item/equip_item/HaveEquipItemList.h"
#include "../item/use_item/HaveUseItemList.h"

#include "../item/use_item/UseItem.h"

MapObjectBase::MapObjectBase(int map_block_x, int map_block_y, GameCamera* camera_obj, bool item_box_flag) {
	this->_draw_x = (map_block_x * MAP_BLOCK_WIDTH);
	this->_draw_y = (map_block_y * MAP_BLOCK_HEIGHT);

	double test_angle = 0;

	this->_hit_square_obj = new HitSquare(this->_draw_x, this->_draw_y, MAP_BLOCK_WIDTH, MAP_BLOCK_HEIGHT, test_angle);

	this->setPosition((float)(this->_draw_x), 0);

}
void MapObjectBase::Update() {
	
	return;

	//test anime
	Random* random_obj = new Random();

	double anime_move_base = 0.005;
	if (this->_anime_num >= 0) {
		this->_anime_move_speed -= (anime_move_base + (anime_move_base * (random_obj->getRandNum(100) / 100)));
	} else {
		this->_anime_move_speed += (anime_move_base + (anime_move_base * (random_obj->getRandNum(100) / 100)));
	}
	this->_anime_num += this->_anime_move_speed;
	this->setRotationSkewX(this->_anime_num);
	/*
	double anime_move = 0.2;
	double anime_max = 5;
	if (this->anime_statue == 0) {
		this->anime_num += anime_move;
		if (this->anime_num >= anime_max) {
			this->anime_statue = 1;
		}
	} else {
		this->anime_num -= anime_move;
		if (this->anime_num <= anime_max *(-1)) {
			this->anime_statue = 0;
		}
	}
	this->setRotationX((int)this->anime_num);
	//this->setPosition((float)(this->_draw_x), 0);
	*/

	delete random_obj;
}
int MapObjectBase::getHitCheckType() {
	return this->_hit_check_type;
}
HitSquare* MapObjectBase::getHitSquare() {
	return this->_hit_square_obj;
}


void MapObjectBase::resetDrawObject() {
	if (this->_DRAW_FLAG == false) {
		this->_DRAW_FLAG = true;
		//	Debug.WriteLine("[MapObjectBase]add child");		
		//				this.AddChild(this._object_sprite);
	}
}
void MapObjectBase::removeDrawObject() {
	if (this->_DRAW_FLAG == true) {
		this->_DRAW_FLAG = false;
		//	Debug.WriteLine("[MapObjectBase]remove child");
		//				this.RemoveChild(this._object_sprite, true);
	}
}

void MapObjectBase::actionActive(CharaBase* chara_obj) {
	// TEST
	//	this->actionPushActive(chara_obj);
	this->actionCountActive(chara_obj);

}
void MapObjectBase::actionPushActive(CharaBase* chara_obj) {
	if (chara_obj->checkGroundFlag() != true) {
		return;
	}
	if (this->getActionFlag() == true) {
		this->actionObjBehavior(chara_obj);
	}
}
void MapObjectBase::actionCountActive(CharaBase* chara_obj) {
	if (chara_obj->checkGroundFlag() != true) {
		return;
	}
	if (this->_action_num == 0){
		return;
	}
	if (this->getActionFlag() == true) {
		this->_action_num--;
		if (this->_action_num == 0){
			this->_action_flag = false;
		}
		this->actionObjBehavior(chara_obj);
	}
}
void MapObjectBase::actionObjBehavior(CharaBase* chara_obj) {
//	chara_obj->sendComment("どーん！");
	//chara_obj->healHp(1000);
//	this->openItemUi();
}
bool MapObjectBase::getActionFlag() {
	return this->_action_flag;
}

// アイテムBOX系 ------------------------------------------
// 初期化系
void MapObjectBase::setItemList() {
}
void MapObjectBase::setItemObj(ItemBase* item_obj) {

	if (item_obj == nullptr) {
//		return;
	}
	haveItemType item_type = item_obj->getHaveItemType();

	if (this->_item_type_count[item_type] <= 0) {
		this->_item_type_count[item_type] = 0;
	}

	switch (item_type) {
	case haveItemType::weapon:
	case haveItemType::armour:
		//this->_equip_item_list[item_type][this->_item_type_count[item_type]] = (EquipItem*)item_obj;
		this->_equip_item_list->setListToItem((EquipItem*)item_obj);
		break;
	default:
		this->_use_item_list->setItem((UseItem*)item_obj, 1);
//		UseItem* test_load_item_to_use = (UseItem*)item_obj;
//		test_load_item_to_use->addNum(1);
		
		//this->_use_item_list[item_type][test_load_item_to_use->getUseItemId()] = test_load_item_to_use;
		//this->_use_item_list
		break;
	}


	this->_item_type_count[item_type]++;
}
// 調べてUI開く
void MapObjectBase::openItemUi() {
	GameMain::_item_ui_obj->setSearchObjItemList(this->_equip_item_list, this->_use_item_list);
	Gamepad::GameControll->setControllType(gamePadControllType::item_ui, 1);
}

