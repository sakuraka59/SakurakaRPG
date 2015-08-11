#include "HpEffect.h"
#include "../../CharaBase.h"

HpEffect::HpEffect(CharaBase* chara_obj) : StatusEffectBase(chara_obj) {
	this->_state_name = "持続効果・HP";
}
void HpEffect::stateEffectDetail(int effect_num) {
	this->_chara_obj->healHp(effect_num);
}