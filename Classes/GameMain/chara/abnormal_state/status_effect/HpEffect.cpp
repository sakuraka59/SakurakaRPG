#include "HpEffect.h"
#include "../../CharaBase.h"

HpEffect::HpEffect(CharaBase* chara_obj) : StatusEffectBase(chara_obj) {
	this->_state_name = "Ž‘±Œø‰Ê:HP";
}
void HpEffect::stateEffectDetail(int effect_num) {
	this->_chara_obj->healHp(effect_num);
}