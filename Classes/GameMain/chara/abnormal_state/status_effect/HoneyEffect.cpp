#include "HoneyEffect.h"
#include "../../CharaBase.h"

HoneyEffect::HoneyEffect(CharaBase* chara_obj) : StatusEffectBase(chara_obj) {
	this->_state_name = "Ž‘±Œø‰ÊE‹»•±";
}
void HoneyEffect::stateEffectDetail(int effect_num) {
	this->_chara_obj->healHoney(effect_num);
}