#include "SatietyEffect.h"
#include "../../CharaBase.h"

SatietyEffect::SatietyEffect(CharaBase* chara_obj) : StatusEffectBase(chara_obj) {
	this->_state_name = "Ž‘±Œø‰Ê:–ž• “x";
}
void SatietyEffect::stateEffectDetail(int effect_num) {
	this->_chara_obj->healSatiety(effect_num);
}