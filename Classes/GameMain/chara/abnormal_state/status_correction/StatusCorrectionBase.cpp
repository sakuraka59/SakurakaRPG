#include "StatusCorrectionBase.h"
#include "../../CharaBase.h"

#include <math.h>
StatusCorrectionBase::StatusCorrectionBase(CharaBase* chara_obj, mainStateType correction_state) : StateAuto(chara_obj) {

	
	switch (correction_state) {
		case mainStateType::hp:
			this->_state_name = "•â•Œø‰Ê:HP";
			break;
		case mainStateType::sp:
			this->_state_name = "•â•Œø‰Ê:SP";
			break;
		case mainStateType::atk:
			this->_state_name = "•â•Œø‰Ê:UŒ‚—Í";
			break;
		case mainStateType::def:
			this->_state_name = "•â•Œø‰Ê:–hŒä—Í";
			break;
		case mainStateType::magic:
			this->_state_name = "•â•Œø‰Ê:–‚—Í";
			break;
		case mainStateType::mdef:
			this->_state_name = "•â•Œø‰Ê:–‚–@–hŒä—Í";
			break;
	}
	this->_repair_frame = 0;

	// state effect interval
	this->_effect_interval = 1;

	this->_correction_state = correction_state;
}
int StatusCorrectionBase::getCorrectionNum() {
	if (this->_end_flag != true) {
		return 0;
	}
	return this->_max_effect_num;
}

void StatusCorrectionBase::startStateEffect() {
	if (this->_before_frame_state != 0) {
		this->_chara_obj->sadCorrectionStatus(this->_correction_state, this->_before_frame_state);
	}
	this->_chara_obj->addCorrectionStatus(this->_correction_state, this->_max_effect_num);
	
}
void StatusCorrectionBase::stateEffect() {
	this->_before_frame_state = this->_max_effect_num;
}
void StatusCorrectionBase::endStateEffect() {
	this->_chara_obj->sadCorrectionStatus(this->_correction_state, this->_max_effect_num);
	this->_max_effect_num = 0;
	this->_before_frame_state = 0;
}
/*
void StatusCorrectionBase::stateEffectDetail(int effect_num) {

}
*/