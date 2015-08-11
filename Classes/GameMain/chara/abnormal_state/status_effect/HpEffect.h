#pragma once
#include "StatusEffectBase.h"

class CharaBase;

class HpEffect : public StatusEffectBase {

public: HpEffect(CharaBase* chara_obj);
protected: void stateEffectDetail(int effect_num) override;

};