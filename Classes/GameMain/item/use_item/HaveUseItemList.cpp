#include "HaveUseItemList.h"
#include "../ItemBase.h"
#include "UseItem.h"

#include "hp_heal/TestHpHeal.h"

HaveUseItemList::HaveUseItemList() : HaveItemListBase() {

	//this->_item_list[useItemId::testHpHeal] = new TestHpHeal(chara_obj);
//	this->setItem("test_hp_heal", 5);

}
void HaveUseItemList::testItemList() {
//	this->setItem("test_hp_heal", 5);
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
void HaveUseItemList::setItem(UseItem* item_obj, int item_num) {

	string item_id = item_obj->getUseItemId();
//	int item_num = 0;
	if (this->_item_list[item_id] == nullptr) {
		// @TODO
		UseItem* set_item_obj = new UseItem();
		set_item_obj->setUseItemId(item_id);
		set_item_obj->setCharaObj(this->_chara_obj);
		set_item_obj->setItemName(item_obj->getItemName());
		set_item_obj->addNum(item_num);
		set_item_obj->setHaveItemType(item_obj->getHaveItemType());

		set_item_obj->setStateData(item_obj->getStateData());
		set_item_obj->setCorrectStateData(item_obj->getCorrectData());
		set_item_obj->setEffectFrame(item_obj->getEffectFrame());

		this->_item_list[item_id] = set_item_obj;
		this->_item_type_list[set_item_obj->getHaveItemType()][set_item_obj->getUseItemId()] = set_item_obj;
	}
	else {
		this->_item_list[item_id]->addNum(item_num);
	}

}
unordered_map<haveItemType, unordered_map<string, UseItem*>>* HaveUseItemList::getItemTypeList() {
	return &this->_item_type_list;
}

unordered_map<string, UseItem*> HaveUseItemList::getItemTypeDetailList(haveItemType item_type) {
	return this->_item_type_list[item_type];
}