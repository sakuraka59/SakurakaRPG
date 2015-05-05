#include "Poison.h"
#include "../../CharaBase.h"

Poison::Poison(CharaBase* chara_obj) : StateAuto(chara_obj)
{
	this->_state_name = "“Å";
	// state heal time
	this->_repair_frame = 60;

	// state effect interval
	this->_effect_interval = 1;
}
void Poison::stateEffect() {
	
	//this->_chara_obj->slipDamageHp(10);
//	this->_chara_obj->slipDamageHp(10);
}