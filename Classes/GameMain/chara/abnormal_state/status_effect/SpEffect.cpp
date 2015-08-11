#include "SpEffect.h"
#include "../../CharaBase.h"

SpEffect::SpEffect(CharaBase* chara_obj) : StatusEffectBase(chara_obj) {
	this->_state_name = "持続効果・SP";
}
void SpEffect::stateEffectDetail(int effect_num) {
	this->_chara_obj->healSp(effect_num);
}