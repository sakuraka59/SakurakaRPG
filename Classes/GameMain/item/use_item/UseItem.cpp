#include "UseItem.h"
#include "../../chara/CharaBase.h"
UseItem::UseItem(CharaBase* chara_obj) : ItemBase(chara_obj) {

}
int UseItem::getNum() {
	return this->_num;
}
void UseItem::addNum(int add_num) {
	this->_num += add_num;
}
bool UseItem::useItem() {
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