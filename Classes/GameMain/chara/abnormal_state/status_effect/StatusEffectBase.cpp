#include "StatusEffectBase.h"
#include "../../CharaBase.h"

#include <math.h>
StatusEffectBase::StatusEffectBase(CharaBase* chara_obj) : StateAuto(chara_obj) {

	this->_repair_frame = 0;

	// state effect interval
	this->_effect_interval = 1;
}
void StatusEffectBase::stateEffect() {

	int effect_num = floor(this->_effect_num);

	this->_effect_fraction += this->_effect_num - effect_num;

	// 端数が1以上になった場合
	if (this->_effect_fraction >= 1) {
		effect_num += 1;
		this->_effect_fraction -= 1.0;
	}

	// 最終フレーム到達時
	if (this->_now_frame >= this->_repair_frame) {

		if (this->_effect_fraction >= 0.5) {
			effect_num += 1;
			this->_effect_fraction -= 1.0;
		}
	}
	this->stateEffectDetail(effect_num);
}
void StatusEffectBase::stateEffectDetail(int effect_num) {

}