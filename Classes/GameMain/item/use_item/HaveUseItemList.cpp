#include "HaveUseItemList.h"
#include "../ItemBase.h"

#include "hp_heal/TestHpHeal.h"

HaveUseItemList::HaveUseItemList(CharaBase* chara_obj) : HaveItemListBase(chara_obj) {

	this->_item_list[useItemId::testHpHeal] = new TestHpHeal(chara_obj);

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

unordered_map<haveItemType, unordered_map<useItemId, ItemBase*>>* HaveUseItemList::getItemTypeList() {
	return &this->_item_type_list;
}