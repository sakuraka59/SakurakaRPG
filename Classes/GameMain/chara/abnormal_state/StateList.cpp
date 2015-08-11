#include "StateList.h"
#include "default/Poison.h"

#include "sexual/FeelHot.h"				// 火照り
#include "sexual/Oestrus.h"				// 発情
#include "sexual/Extasy.h"				// 絶頂
#include "sexual/AbsentMindedness.h"	// 放心

#include "status_effect/HpEffect.h"
#include "status_effect/SpEffect.h"
#include "status_effect/HoneyEffect.h"
#include "status_effect/ExcitationEffect.h"

#include "../mainStateType.h"
#include "status_correction/StatusCorrectionBase.h"

StateList::StateList(CharaBase* chara_obj) {
	// テスト用
	this->_state_list[abnormalStateType::poison] = new Poison(chara_obj);

	this->_state_list[abnormalStateType::feel_hot] = new FeelHot(chara_obj);
	this->_state_list[abnormalStateType::oestrus] = new Oestrus(chara_obj);
	this->_state_list[abnormalStateType::extasy] = new Extasy(chara_obj);
	this->_state_list[abnormalStateType::absent_mindedness] = new AbsentMindedness(chara_obj);

	this->_state_list[abnormalStateType::hp_effect] = new HpEffect(chara_obj);
	this->_state_list[abnormalStateType::sp_effect] = new SpEffect(chara_obj);
	this->_state_list[abnormalStateType::honey_effect] = new HoneyEffect(chara_obj);
	this->_state_list[abnormalStateType::excitation_effect] = new ExcitationEffect(chara_obj);

	this->_state_list[abnormalStateType::hp_correct] = new StatusCorrectionBase(chara_obj, mainStateType::hp);
	this->_state_list[abnormalStateType::sp_correct] = new StatusCorrectionBase(chara_obj, mainStateType::sp);
	this->_state_list[abnormalStateType::atk_correct] = new StatusCorrectionBase(chara_obj, mainStateType::atk);
	this->_state_list[abnormalStateType::def_correct] = new StatusCorrectionBase(chara_obj, mainStateType::def);
	this->_state_list[abnormalStateType::magic_correct] = new StatusCorrectionBase(chara_obj, mainStateType::magic);
	this->_state_list[abnormalStateType::mdef_correct] = new StatusCorrectionBase(chara_obj, mainStateType::mdef);

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
	for (auto state_obj : this->_state_list) {
		state_obj.second->Update();
	}
}
void StateList::setState(abnormalStateType state_type, int state_level, int effect_num, int effect_frame) {

	// リストにある場合、状態異常にならない
	if (this->_guard_state_list.find(state_type) != this->_guard_state_list.end()) {
		return;
	}
	this->_state_list[state_type]->setState(state_level, effect_num, effect_frame);


}
void StateList::endState(abnormalStateType state_type) {
	//setState(1);
	this->_state_list[state_type]->endState();
}

bool StateList::checkToSetState(abnormalStateType state_type, int state_level, int state_rate, int effect_num, int effect_frame) {
	//setState(1);
//	System.Random rand_obj = new System.Random();
	//int rand_num = rand_obj.Next(10000);
	int rand_num = 0;
	int state_now_rate = state_rate - this->_state_list[state_type]->getStateResist();


	if (rand_num <= state_now_rate) {
		this->setState(state_type, state_level, effect_num, effect_frame);
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