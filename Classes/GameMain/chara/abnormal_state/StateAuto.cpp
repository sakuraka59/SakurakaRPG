#include "StateAuto.h"
#include "../CharaBase.h"

StateAuto::StateAuto(std::unique_ptr<CharaBase>& chara_obj) : StateBase(chara_obj)
{

}
void StateAuto::stateUpdate(){
	if (this->_state_type != (int)stateType::autoHeal) {
		return;
	}
	if (this->_equip_list.size() == 0) {
		this->_now_frame += 1;
	}

	// check end
	if (this->_now_frame >= this->_repair_frame) {
		this->_end_flag = true;
		this->endStateEffect();
	}
	this->_effect_count++;
	return;
}