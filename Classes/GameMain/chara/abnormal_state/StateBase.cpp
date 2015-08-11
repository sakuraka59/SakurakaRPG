#include "StateBase.h"
#include "../CharaBase.h"
#include "../../item/equip_item/EquipItem.h"

StateBase::StateBase(CharaBase* chara_obj) {
	this->_chara_obj = chara_obj;
}

bool StateBase::Update() {

	// no state
	if (this->_end_flag == true) {

		return false;
	}
	this->stateUpdate();
	this->stateEffectCheck();

	return true;
}
void StateBase::stateUpdate() {

}
void StateBase::stateEffectCheck() {
	this->EveryFrameEffect();
	if (this->_effect_count >= this->_effect_interval) {
		this->_effect_count -= this->_effect_interval;
		this->stateEffect();
	}
}
// 毎フレーム発生
void StateBase::EveryFrameEffect() {

}
// 設定フレームごとに発生
void StateBase::stateEffect() {

}
// 終了時に発生
void StateBase::endStateEffect() {
	if (this->_state_type != (int)stateType::eventOnly) {
		return;
	}
	// no heal to event only heal
	return;
}
void StateBase::setState(int state_level, int effect_num, int effect_frame) {
	this->_now_frame = 0;
	this->_manual_state = (int)manualState::releaseNg;
	this->_end_flag = false;
	this->_state_level = state_level;

	// 継続効果用
	if (effect_num != 0 && effect_frame > 0) {
		this->_repair_frame = effect_frame;
		this->_max_effect_num = effect_num;
		if (this->_repair_frame == 0) {
			this->_effect_num = 0;
		} else {
			this->_effect_num = (double)this->_max_effect_num / this->_repair_frame;
		}

	}
	this->startStateEffect();

}
void StateBase::startStateEffect() {

}
void StateBase::endState() {
	this->_now_frame = this->_repair_frame;
	this->_end_flag = true;
}
void StateBase::setEquipItem(EquipItem* equip_item) {
	this->_equip_list.push_back(equip_item);
}
void StateBase::removeEquipItem(EquipItem* equip_item) {
	this->_equip_list.remove(equip_item);
}

bool StateBase::getEndFlag() {
	return this->_end_flag;
}
std::string StateBase::getStateName() {
	return this->_state_name;
}
int StateBase::getRepairFrame() {
	return this->_repair_frame;
}
int StateBase::getNowFrame() {
	return this->_now_frame;
}
// resist ---------------------------------------------------
int StateBase::getStateResist() {
	return this->_state_resist + this->_state_resist_correction;
}
void StateBase::setSeedStateResist(int seed_rate) {
	this->_state_resist = seed_rate;
}