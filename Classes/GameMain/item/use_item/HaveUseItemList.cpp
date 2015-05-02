#include "HaveUseItemList.h"
#include "../ItemBase.h"

HaveUseItemList::HaveUseItemList(CharaBase* chara_obj) : HaveItemList(chara_obj) {
//	this->_item_list[useItemId.testHpHeal] = new TestHpHeal(chara_obj);
}
bool HaveUseItemList::itemUse(useItemId* item_id) {
	
	return this->_item_list[item_id]->useItem();;
}
