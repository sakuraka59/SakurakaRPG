#include "HaveEquipItemList.h"
#include "EquipItem.h"
#include "../../chara/CharaBase.h"
#include "weapon\sword\TestSword.h"
HaveEquipItemList::HaveEquipItemList(CharaBase* chara_obj) : HaveItemList(chara_obj) {
	
	// テスト用アイテム追加
	EquipItem* item_obj = new TestSword(chara_obj);
	int item_index = this->setListToItem(item_obj);
	chara_obj->setWeaponTestIndex(item_index);
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
	this->_item_list[this->_list_index] = item_obj;
	int ret_index = this->_list_index;
	this->_list_index++;
	return ret_index;
}
bool HaveEquipItemList::itemUse(int index) {
	//	this._use_item_list.IndexOf();
	//	this._chara_obj.setSkill;

	return this->_item_list[index]->useItem();

}