#include "Oestrus.h"
#include "../../CharaBase.h"
#include "../abnormalStateType.h"
#include "../StateList.h"

Oestrus::Oestrus(CharaBase* chara_obj) : StateAuto(chara_obj) {
	this->_state_name = "”­î";

	// state heal time
	this->_repair_frame = 60 * 10;

	// state effect interval
	this->_effect_interval = 30;
}
void Oestrus::stateEffect() {
	StateList* chara_state_list = this->_chara_obj->getStateList();

	// ‰ÎÆ‚è’†+”­î’†‚¾‚ÆA”­î‚ª¡‚ç‚È‚¢
	if (chara_state_list->getStateEndFlag(abnormalStateType::feel_hot) == false) {
		//Debug.WriteLine("hoe2");
		this->_now_frame = 0;
	}
}
void Oestrus::EveryFrameEffect() {
	StateList* state_list = this->_chara_obj->getStateList();

	if (state_list->getStateEndFlag(abnormalStateType::extasy)) {
//		this->_chara_obj->setSkill(new OnanismVagina(this->_chara_obj, this->_chara_obj->getAllCharaList()));

		// test
		this->_chara_obj->normalDamageSexual(10, 0.3, true);
	}
}
void Oestrus::endStateEffect() {
	StateList* state_list = this->_chara_obj->getStateList();
	if (state_list->getStateEndFlag(abnormalStateType::feel_hot)) {
		state_list->setState(abnormalStateType::absent_mindedness, 1);
	}
}