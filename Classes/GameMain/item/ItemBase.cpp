#include "itemBase.h";
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
// */