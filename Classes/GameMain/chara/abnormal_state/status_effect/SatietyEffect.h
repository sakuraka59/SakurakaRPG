#pragma once
#include "StatusEffectBase.h"

class CharaBase;

class SatietyEffect : public StatusEffectBase {

public: SatietyEffect(CharaBase* chara_obj);
protected: void stateEffectDetail(int effect_num) override;

};