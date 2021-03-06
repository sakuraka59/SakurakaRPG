#include "ExcitationEffect.h"
#include "../../CharaBase.h"

ExcitationEffect::ExcitationEffect(CharaBase* chara_obj) : StatusEffectBase(chara_obj) {
	this->_state_name = "持続効果:快感";
}
void ExcitationEffect::stateEffectDetail(int effect_num) {
	this->_chara_obj->healExcitation(effect_num);
}