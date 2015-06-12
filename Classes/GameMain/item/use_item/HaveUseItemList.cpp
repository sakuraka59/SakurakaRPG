#include "HaveUseItemList.h"
#include "../ItemBase.h"
#include "UseItem.h"

#include "hp_heal/TestHpHeal.h"

HaveUseItemList::HaveUseItemList(CharaBase* chara_obj) : HaveItemListBase(chara_obj) {

	//this->_item_list[useItemId::testHpHeal] = new TestHpHeal(chara_obj);
	this->setItem(useItemId::testHpHeal, 5);

}
bool HaveUseItemList::itemUse(useItemId item_id) {
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
void HaveUseItemList::setItem(useItemId item_id, int item_num) {
	if (this->_item_list[item_id] == nullptr) {
		UseItem* item_obj = new TestHpHeal(this->_chara_obj);
		item_obj->addNum(item_num);
		this->_item_list[useItemId::testHpHeal] = item_obj;
		this->_item_type_list[item_obj->getHaveItemType()][useItemId::testHpHeal] = item_obj;
	}
	else {
		this->_item_list[useItemId::testHpHeal]->addNum(item_num);
	}

}
unordered_map<haveItemType, unordered_map<useItemId, UseItem*>>* HaveUseItemList::getItemTypeList() {
	return &this->_item_type_list;
}