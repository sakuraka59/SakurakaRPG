#include "EffectBase.h"

EffectBase::EffectBase(CharaBase* chara_obj) : MagicBase(chara_obj){
	this->_hit_check_flag = false;
}