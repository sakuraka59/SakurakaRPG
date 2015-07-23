#include "HaveEquipItemList.h"
#include "EquipItem.h"
#include "../../chara/CharaBase.h"
#include "../haveItemType.h"
#include "weapon/sword/TestSword.h"
#include "weapon/sheath/TestSheath.h"

#include "weapon/rapier/WeaponRapierBase.h"

#include "../ItemMasterList.h"
HaveEquipItemList::HaveEquipItemList() : HaveItemListBase() {
	
	
}
void HaveEquipItemList::testItemList() {
	/*
	// テスト用アイテム追加
	EquipItem* item_obj = new TestSword();
	item_obj->setCharaObj(chara_obj);
	int item_index = this->setListToItem(item_obj);
	chara_obj->setWeaponTestIndex(item_index);


	EquipItem* sheath_obj = new TestSheath();
	sheath_obj->setCharaObj(chara_obj);
	item_index = this->setListToItem(sheath_obj);
	chara_obj->setWeaponTestIndex(item_index);

	// ロードからの読み込み
	ItemBase* test_load_item = ItemMasterList::getItemObjToMaster("test_sword");

	if (test_load_item != nullptr) {
	EquipItem* test_load_obj = (EquipItem*)test_load_item;
	test_load_obj->setCharaObj(chara_obj);
	item_index = this->setListToItem(test_load_obj);
	}

	ItemBase* test_load_item2 = ItemMasterList::getItemObjToMaster("test_rapier");

	//	ItemBase* hoge2 = this->ItemMaterialToItemBase(test_load_item2);
	if (test_load_item2 != nullptr) {
	EquipItem* test_load_obj2 = (EquipItem*)test_load_item2;
	test_load_obj2->setCharaObj(chara_obj);
	item_index = this->setListToItem(test_load_obj2);
	}
	/*
	// テスト用アイテム追加
	EquipItem item_obj2 = new TestSheath(chara_obj);
	int item_index2 = this.setListToItem(item_obj2);


	// テスト用アイテム追加
	EquipItem item_obj3 = new TestRapier(chara_obj);
	int item_index3 = this.setListToItem(item_obj3);


	*/
	//this._item_list.Add(item_obj);

	//			this._item_list
	//this._item_list[useItemId.testHpHeal] = new TestHpHeal(chara_obj);
}
int HaveEquipItemList::setListToItem(EquipItem* item_obj) {

	if (this->_chara_obj != nullptr) {
		item_obj->setCharaObj(this->_chara_obj);
	}
	
	item_obj->setListIndex(this->_list_index);

	this->_item_list[this->_list_index] = item_obj;
	this->_item_type_list[item_obj->getHaveItemType()][this->_list_index] = item_obj;
	
	int ret_index = this->_list_index;
	this->_list_index++;
	return ret_index;
}
void HaveEquipItemList::removeListToItem(EquipItem* item_obj) {
	int item_index = item_obj->getListIndex();
	
	// 要素を削除する
	auto item_list_itr = this->_item_list.find(item_index);
	if (item_list_itr != this->_item_list.end()){		// キーの要素が存在している場合
		this->_item_list.erase(item_list_itr);
	}
	unordered_map<haveItemType, unordered_map<int, EquipItem*>>* ret_data = &this->_item_type_list;

	auto item_type_list_itr = this->_item_type_list[item_obj->getHaveItemType()].find(item_index);
	if (item_type_list_itr != this->_item_type_list[item_obj->getHaveItemType()].end()){		// キーの要素が存在している場合
		this->_item_type_list[item_obj->getHaveItemType()].erase(item_type_list_itr);

		

		int num = this->_item_type_list[item_obj->getHaveItemType()].size();
		if (num <= 0) {
			auto item_type_itr = this->_item_type_list.find(item_obj->getHaveItemType());
			if (item_type_itr != this->_item_type_list.end()){
				this->_item_type_list.erase(item_type_itr);
			}
		}
		int hoge = 0;
//		this->_list_index--;
	}
//	this->_item_list[item_index] = nullptr;
//	this->_item_type_list[item_obj->getHaveItemType()][item_index] = nullptr;
}
bool HaveEquipItemList::itemUse(int index) {
	//	this._use_item_list.IndexOf();
	//	this._chara_obj.setSkill;

	return this->_item_list[index]->useItem();

}
unordered_map<haveItemType, unordered_map<int, EquipItem*>>* HaveEquipItemList::getItemTypeList() {
	unordered_map<haveItemType, unordered_map<int, EquipItem*>>* ret_data = &this->_item_type_list;
	return ret_data;
}
ItemBase* HaveEquipItemList::ItemMaterialToItemBase(ItemLoadOnlyMaterial* load_item) {
	if (load_item == nullptr) {
		return nullptr;
	}
	WeaponSwordBase* sword_obj = new WeaponSwordBase();
	WeaponRapierBase* rapier_obj = new WeaponRapierBase();
	switch (load_item->_item_type) {
	case itemDetailType::sword:

		sword_obj->setItemName(load_item->_item_name);
		sword_obj->setStateData(load_item->_default_state);
		return (ItemBase*)sword_obj;
		break;
	case itemDetailType::rapier:
		
		rapier_obj->setItemName(load_item->_item_name);
		rapier_obj->setStateData(load_item->_default_state);
		return (ItemBase*)rapier_obj;
	}
	return nullptr;
}
