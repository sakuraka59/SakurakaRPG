#include "ItemBase.h";
//#include "../chara/CharaBase.h"

ItemBase::ItemBase(CharaBase* chara_obj){
	this->_chara_obj = chara_obj;
}

//*
bool ItemBase::useItem() {
	return false;
}
// */
std::string ItemBase::getItemName() {
	return this->_item_name;
}

haveItemType ItemBase::getHaveItemType() {
	return this->_have_item_type;
}
// */