#include "Extasy.h"
#include "../../CharaBase.h"

Extasy::Extasy(CharaBase* chara_obj) : StateAuto(chara_obj) {
	this->_state_name = "â’¸";
	// state heal time
	this->_repair_frame = 120;

	// state effect interval
	this->_effect_interval = 1;
}
void Extasy::stateEffect() {

}
void Extasy::endStateEffect() {
	this->_chara_obj->setExtasy();
}