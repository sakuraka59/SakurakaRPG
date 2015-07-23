#include "UseItem.h"
#include "../../chara/CharaBase.h"
UseItem::UseItem() : ItemBase() {

}
int UseItem::getNum() {
	return this->_num;
}
void UseItem::addNum(int add_num) {
	this->_num += add_num;
}
bool UseItem::useItem() {
	if (this->_chara_obj == nullptr) {
		return false;
	}
	if (this->_chara_obj->checkActionFlag() != true) {
		return false;
	}
	if (this->_num >= 1) {
		if (this->useSkill() == true) {
			this->_num -= 1;
		}
		else {
			return false;
		}
		return true;
	}
	return false;
}
// use item to invocation skill
bool UseItem::useSkill() {
	return false;
}

string UseItem::getUseItemId() {
	return this->_use_item_id;
}
void UseItem::setUseItemId(string use_item_id) {
	this->_use_item_id = use_item_id;
}