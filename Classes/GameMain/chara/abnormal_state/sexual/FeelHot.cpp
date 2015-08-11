#include "FeelHot.h"
#include "../../CharaBase.h"

FeelHot::FeelHot(CharaBase* chara_obj) : StateAuto(chara_obj) {
	this->_state_name = "‰ÎÆ‚è";

	// state heal time
	this->_repair_frame = 60 * 20;

	// state effect interval
	this->_effect_interval = 1;
}
void FeelHot::stateEffect() {
//	StateList chara_state_list = this->_chara_obj.getStateList();
//	Debug.WriteLine(chara_state_list.getStateEndFlag(abnormalStateType.oestrus));
}
void FeelHot::EveryFrameEffect() {
	this->_chara_obj->honeyOnlyDamage(100);
}