#include "ItemBase.h";
//#include "../chara/CharaBase.h"

ItemBase::ItemBase(){
//	this->_chara_obj = chara_obj;
}

//*
bool ItemBase::useItem() {
	return false;
}
// */
void ItemBase::setItemName(string item_name) {
	this->_item_name = item_name;
}
std::string ItemBase::getItemName() {
	return this->_item_name;
}

haveItemType ItemBase::getHaveItemType() {
	return this->_have_item_type;
}
// */
void ItemBase::setCharaObj(CharaBase* chara_obj){
	this->_chara_obj = chara_obj;
}