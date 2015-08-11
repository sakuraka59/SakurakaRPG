#include "AbsentMindedness.h"
#include "../../CharaBase.h"

AbsentMindedness::AbsentMindedness(CharaBase* chara_obj) : StateAuto(chara_obj) {
	this->_state_name = "•úS";
	// state heal time
	this->_repair_frame = 60 * 3;

	// state effect interval
	this->_effect_interval = 30;
}
void AbsentMindedness::stateEffect() {

}