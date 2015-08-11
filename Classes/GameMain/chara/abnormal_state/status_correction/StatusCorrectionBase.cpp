#include "StatusCorrectionBase.h"
#include "../../CharaBase.h"

#include <math.h>
StatusCorrectionBase::StatusCorrectionBase(CharaBase* chara_obj, mainStateType correction_state) : StateAuto(chara_obj) {

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