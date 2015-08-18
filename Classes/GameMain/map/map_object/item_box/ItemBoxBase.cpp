#include "ItemBoxBase.h"

#include "../../../item/ItemMasterList.h"
#include "../../../item/equip_item/HaveEquipItemList.h"
#include "../../../item/use_item/HaveUseItemList.h"

#include "../../../item/equip_item/EquipItem.h"
#include "../../../item/use_item/UseItem.h"

ItemBoxBase::ItemBoxBase(int map_block_x, int map_block_y, GameCamera* camera_obj) :
	MapObjectBase(map_block_x, map_block_y, camera_obj, true) {

	// /*
	int sprite_one_width = 102;
	int sprite_one_height = 171;
	int sprite_x = sprite_one_width * 5;
	int sprite_y = sprite_one_height * 2;

	cocos2d::Rect clip_rect = cocos2d::Rect(sprite_x, sprite_y, sprite_one_width, sprite_one_height);
	cocos2d::Sprite* sprite_data = cocos2d::Sprite::create("img/map/test_objects.png", clip_rect);

	// /*
	int particle_width = 64;
	int particle_height = 64;
	sprite_data->setPosition((particle_width / 2), 55);
	sprite_data->setScale(0.65f);
	this->addChild(sprite_data);
	// */

	this->_action_flag = true;
	this->_item_box_flag = true;

	this->_equip_item_list = new HaveEquipItemList();
	this->_use_item_list = new HaveUseItemList();
	this->setItemList();

}
void ItemBoxBase::actionObjBehavior(CharaBase* chara_obj) {
	
	this->openItemUi();
}
void ItemBoxBase::setItemList() {
	if (this->_item_box_flag != true) {
		return;
	}
	int load_item_rate = 1;
	for (int i = 0; i < 3; i++) {
		ItemBase* load_rand_item = ItemMasterList::getItemObjToRateRandom(load_item_rate);
		if (load_rand_item != nullptr) {
			this->setItemObj(load_rand_item);
		}
	}
	for (int i = 0; i < 3; i++) {
		//aphrodisiac_1
		UseItem* test_load_item3 = (UseItem*)ItemMasterList::getItemObjToMaster("test_hp_heal");
		this->setItemObj(test_load_item3);
	}
	// @TODO test
	/*
	EquipItem* test_load_item = (EquipItem*)ItemMasterList::getItemObjToMaster("test_sword");
	this->setItemObj(test_load_item);

	EquipItem* test_load_item2 = (EquipItem*)ItemMasterList::getItemObjToMaster("aphrodisiac_1");
	this->setItemObj(test_load_item2);

	//aphrodisiac_1
	UseItem* test_load_item3 = (UseItem*)ItemMasterList::getItemObjToMaster("test_hp_heal");
	this->setItemObj(test_load_item3);

	//aphrodisiac_1
	UseItem* test_load_item4 = (UseItem*)ItemMasterList::getItemObjToMaster("attack_potion_1");
	this->setItemObj(test_load_item4);
	*/

	//	this->_use_item_list->setItem(test_load_item3, 1);
	//	this->_use_item_list->setItem("test_hp_heal", 3);
	//	ItemBase* test_load_use_item = new TestHpHeal();
	//	this->setItemObj(test_load_use_item);
}
