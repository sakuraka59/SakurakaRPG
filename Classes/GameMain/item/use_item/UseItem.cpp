#include "UseItem.h"
#include "../../chara/CharaBase.h"

#include "../../skill/use_item/ItemEffect.h"
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
void UseItem::setStateData(unordered_map<mainStateType, int> default_state) {
	this->_default_state = default_state;
}
void UseItem::setCorrectStateData(unordered_map<mainStateType, int> correct_state) {
	this->_correct_state = correct_state;
}
void UseItem::setEffectFrame(int effect_frame) {
	this->_effect_frame = effect_frame;
}
unordered_map<mainStateType, int> UseItem::getStateData() {
	return this->_default_state;
}
unordered_map<mainStateType, int> UseItem::getCorrectData() {
	return this->_correct_state;
}
int UseItem::getEffectFrame() {
	return this->_effect_frame;
}

// use item to invocation skill
bool UseItem::useSkill() {
	bool use_flag = this->_chara_obj->setSkill(new ItemEffect(this->_chara_obj, this->_chara_obj->getAllCharaList(),
		this->_default_state, this->_correct_state, this->_effect_frame));

	return use_flag;

//	return false;
}

string UseItem::getUseItemId() {
	return this->_use_item_id;
}
void UseItem::setUseItemId(string use_item_id) {
	this->_use_item_id = use_item_id;
}

bool UseItem::removeUseItem(int num) {
	if (num > this->_num) {
		return false;
	}
	this->_num -= num;
	return true;
}