#pragma once
#include "StatusEffectBase.h"

class CharaBase;

class SpEffect : public StatusEffectBase {

public: SpEffect(CharaBase* chara_obj);
protected: void stateEffectDetail(int effect_num) override;

};