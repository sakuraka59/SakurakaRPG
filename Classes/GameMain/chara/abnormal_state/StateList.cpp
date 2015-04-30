#include "StateList.h"


StateList::StateList(CharaBase* chara_obj) {
	// テスト用
//	this->_state_list[abnormalStateType::poison] = new Poison(chara_obj);
//	this->_state_list[abnormalStateType.feel_hot] = new Poison(chara_obj);
//	this->_state_list[abnormalStateType.oestrus] = new Poison(chara_obj);
//	this->_state_list[abnormalStateType.extasy] = new Poison(chara_obj);
//	this->_state_list[abnormalStateType.absent_mindedness] = new Poison(chara_obj);

	/*
	this->_state_list[abnormalStateType.feel_hot] = new FeelHot(chara_obj);
	this->_state_list[abnormalStateType.oestrus] = new Oestrus(chara_obj);
	this->_state_list[abnormalStateType.extasy] = new Extasy(chara_obj);
	this->_state_list[abnormalStateType.absent_mindedness] = new AbsentMindedness(chara_obj);
	*/
}
void StateList::Update(){
	/*
	foreach(abnormalStateType state in Enum.GetValues(typeof(abnormalStateType))) {
		if (state == abnormalStateType.none || state == abnormalStateType.sexual) {
			continue;
		}
		this->_state_list[state].Update();
	}
	*/
}
void StateList::setState(abnormalStateType state_type, int state_level) {

	// リストにある場合、状態異常にならない
	if (this->_guard_state_list.find(state_type) != this->_guard_state_list.end()) {
		return;
	}
	this->_state_list[state_type]->setState(state_level);
}
void StateList::endState(abnormalStateType state_type) {
	//setState(1);
	this->_state_list[state_type]->endState();
}


bool StateList::checkToSetState(abnormalStateType state_type, int state_level, int state_rate) {
	//setState(1);
//	System.Random rand_obj = new System.Random();
	//int rand_num = rand_obj.Next(10000);
	int rand_num = 0;
	int state_now_rate = state_rate - this->_state_list[state_type]->getStateResist();


	if (rand_num <= state_now_rate) {
		this->setState(state_type, state_level);
		return true;
	}
	return false;
}
// ステートが終了（機能してない）状態かどうかを返す
bool StateList::getStateEndFlag(abnormalStateType state_type) {
	return this->_state_list[state_type]->getEndFlag();
}
std::unordered_map<abnormalStateType, StateBase*> StateList::getStateList() {
	return this->_state_list;
}
//-----------------------------------------------------------
//	equip item to abnormal state default
//-----------------------------------------------------------
void StateList::setEquipItemToState(abnormalStateType state_type, EquipItem* item_obj) {
	this->_state_list[state_type]->setEquipItem(item_obj);
}
void StateList::removeEquipItemToState(abnormalStateType state_type, EquipItem* item_obj) {
	this->_state_list[state_type]->removeEquipItem(item_obj);
}
// guard ----------------------------------------------------
void StateList::setStateGuard(abnormalStateType state_type) {
	this->_guard_state_list[state_type] = state_type;
}
// resist ---------------------------------------------------
void StateList::setSeedStateResist(abnormalStateType state_type, int state_rate) {
	this->_state_list[state_type]->setSeedStateResist(state_rate);
}