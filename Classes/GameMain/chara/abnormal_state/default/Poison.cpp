#include "Poison.h"
#include "../../CharaBase.h"

Poison::Poison(CharaBase* chara_obj) : StateAuto(chara_obj)
{
	this->_state_name = "��";
	// state heal time
	this->_repair_frame = 60;

	// state effect interval
	this->_effect_interval = 1;
}
/*
public override bool Update() {

if(base.Update() == false){
return false;
}
this.stateEffect();
return true;
}
*/
void Poison::stateEffect() {
	
	//this->_chara_obj->slipDamageHp(10);
}