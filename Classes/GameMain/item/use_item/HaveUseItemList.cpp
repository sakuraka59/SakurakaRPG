#include "HaveUseItemList.h"
#include "../ItemBase.h"
#include "UseItem.h"

#include "hp_heal/TestHpHeal.h"

HaveUseItemList::HaveUseItemList() : HaveItemListBase() {

	//this->_item_list[useItemId::testHpHeal] = new TestHpHeal(chara_obj);
//	this->setItem("test_hp_heal", 5);

}
void HaveUseItemList::testItemList() {
	this->setItem("test_hp_heal", 5);
}
bool HaveUseItemList::itemUse(string item_id) {
	/*
	if (this->_item_list.find(item_id) == this->_item_list.end()) {
		return false;
	}
	*/
	if (this->_item_list.empty() == true) {
		return false;
	}

	if (this->_item_list[item_id] == nullptr) {
		return false;
	}
	
	return this->_item_list[item_id]->useItem();
}
void HaveUseItemList::setItem(string item_id, int item_num) {
	if (this->_item_list[item_id] == nullptr) {
		// @TODO
		UseItem* item_obj = new TestHpHeal();
		item_obj->setCharaObj(this->_chara_obj);
		item_obj->addNum(item_num);

		this->_item_list[item_id] = item_obj;
		this->_item_type_list[item_obj->getHaveItemType()][item_obj->getUseItemId()] = item_obj;
	}
	else {
		this->_item_list[item_id]->addNum(item_num);
	}

}
unordered_map<haveItemType, unordered_map<string, UseItem*>>* HaveUseItemList::getItemTypeList() {
	return &this->_item_type_list;
}